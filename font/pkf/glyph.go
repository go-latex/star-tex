// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package pkf

import (
	"fmt"
	"image"

	"star-tex.org/x/tex/internal/iobuf"
)

// Glyph represents a glyph contained in a PK font file.
type Glyph struct {
	flag   uint8
	code   uint32 // character code
	wtfm   uint32 // TFM width
	dx     uint32 // horizontal escapement
	dy     uint32 // vertical escapement
	width  uint32 // width in pixels of the minimum bounding box
	height uint32 // height in pixels of the minimum bounding box
	xoff   int32  // horizontal offset from the upper left pixel
	yoff   int32  // vertical offset from the upper left pixel

	data []byte
	mask []byte
}

func (g *Glyph) unpack() {
	if g.mask != nil {
		return
	}

	gr := glyphReader{
		r: iobuf.NewReader(g.data),
		g: g,
	}
	g.mask = gr.unpack()
}

func (g *Glyph) Mask() image.Alpha {
	g.unpack()
	h := int(g.height)
	w := int(g.width)
	pix := make([]byte, 0, h*w)
	var i int
	for row := 0; row < h; row++ {
		for col := 0; col < w; col += 8 {
			v := g.mask[i]
			n := clip(w-col, 8)
			bit := uint8(1 << 7)
			for ; n > 0; n-- {
				switch {
				case v&bit != 0:
					pix = append(pix, 0xff)
				default:
					pix = append(pix, 0x00)
				}
				bit >>= 1
			}
			i++
		}
	}

	return image.Alpha{
		Stride: w,
		Pix:    pix,
		Rect:   image.Rect(0, 0, w, h),
	}
}

func (g *Glyph) Bounds() image.Rectangle {
	h := int(g.height)
	w := int(g.width)
	return image.Rect(0, 0, w, h)
}

func readGlyph(r *iobuf.Reader) (g Glyph, err error) {
	var (
		pos    = r.Pos()
		raster uint32
	)

	g.flag = r.ReadU8()
	switch g.flag & 7 {
	case 0, 1, 2, 3:
		// 'short' character description.
		// flag[1] pl[1] cc[1] tfm[3] dm[1] w[1] h[1] hoff[+1] voff[+1]
		raster = uint32(g.flag&7)*(2<<7) + uint32(r.ReadU8()) - 4
		g.code = uint32(r.ReadU8())
		g.wtfm = r.ReadU24()
		g.dx = uint32(r.ReadU8()) * 65536
		g.dy = 0
		g.width = uint32(r.ReadU8())
		g.height = uint32(r.ReadU8())
		g.xoff = int32(r.ReadI8())
		g.yoff = int32(r.ReadI8())
		raster -= 4
	case 4, 5, 6:
		// 'extended short' character description.
		// flag[1] pl[2] cc[1] tfm[3] dm[2] w[2] h[2] hoff[+2] voff[+2].
		raster = uint32(g.flag&3)*(2<<15) + uint32(r.ReadU16()) - 5
		g.code = uint32(r.ReadU8())
		g.wtfm = r.ReadU24()
		g.dx = uint32(r.ReadU16()) * 65536
		g.dy = 0
		g.width = uint32(r.ReadU16())
		g.height = uint32(r.ReadU16())
		g.xoff = int32(r.ReadI16())
		g.yoff = int32(r.ReadI16())
		raster -= 4 * 2
	case 7:
		// 'long' character description.
		// flag[1] pl[4] cc[4] tfm[4] dx[4] dy[4] w[4] h[4] hoff[4] voff[4]
		raster = r.ReadU32() - 12
		g.code = r.ReadU32()
		g.wtfm = r.ReadU32()
		g.dx = r.ReadU32()
		g.dy = r.ReadU32()
		g.width = r.ReadU32()
		g.height = r.ReadU32()
		g.xoff = int32(r.ReadU32())
		g.yoff = int32(r.ReadU32())
		raster -= 4 * 4
	}
	g.data = r.ReadBuf(int(raster))
	g.mask = nil

	if false {
		dynf := g.flag / 16

		fmt.Printf(
			"%d:  Flag byte = %d  Character = %d  Packet length = %d\n"+
				"  Dynamic packing variable = %d\n"+
				"  TFM width = %d  dx = %d%s\n"+
				"  Height = %d  Width = %d  X-offset = %d  Y-offset = %d\n",
			pos, g.flag, g.code, raster,
			dynf,
			g.wtfm, g.dx, func() string {
				switch g.dy {
				case 0:
					return " "
				default:
					return fmt.Sprintf("  dy = %d", g.dy)
				}
			}(),
			g.height, g.width, g.xoff, g.yoff,
		)
	}

	return g, err
}

type glyphReader struct {
	r *iobuf.Reader
	g *Glyph

	inputbyte uint16
	bitweight uint16
	dynf      uint32
	repeat    uint32
	remainder int32
	read      func() uint32
}

func (gr *glyphReader) init() {
	gr.r.SetPos(0)
	gr.repeat = 0

	gr.inputbyte = 0
	gr.bitweight = 0
	gr.dynf = uint32(gr.g.flag / 16)
	gr.read = gr.pknum
}

var gpower = [17]uint16{
	0, 1, 3, 7, 15, 31, 63, 127,
	255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535,
}

func (gr *glyphReader) unpack() []byte {
	var (
		wordwidth  = int16((gr.g.width + 15) / 16)
		word       uint16
		wordweight uint16
		rowsleft   int16
		turnon     = gr.g.flag&8 != 0
		hbit       int16
		count      uint16

		mask []uint8
	)

	gr.init()

	sz := 2 * gr.g.height * uint32(wordwidth)
	if sz <= 0 {
		sz = 2
	}

	var (
		idx    int
		sli    = make([]uint16, sz/2+1) // divide by 2: sz is in bytes
		raster = sli[1:]
	)

	switch gr.dynf {
	case 14:
		gr.bitweight = 0
		for i := 0; i < int(gr.g.height); i++ {
			word = 0
			wordweight = 32768
			for j := 0; j < int(gr.g.width); j++ {
				if gr.getbit() {
					word += wordweight
				}
				wordweight >>= 1
				if wordweight == 0 {
					raster[idx] = word
					idx++
					word = 0
					wordweight = 32768
				}
			}
			if wordweight != 32768 {
				raster[idx] = word
				idx++
			}
		}
	default:
		rowsleft = int16(gr.g.height)
		hbit = int16(gr.g.width)
		wordweight = 16
		word = 0
		for rowsleft > 0 {
			count = uint16(gr.read())
			for count != 0 {
				switch {
				case count < wordweight && count < uint16(hbit):
					if turnon {
						word += gpower[wordweight] - gpower[wordweight-count]
					}
					hbit -= int16(count)
					wordweight -= count
					count = 0

				case count >= uint16(hbit) && uint16(hbit) <= wordweight:
					if turnon {
						word += gpower[wordweight] - gpower[wordweight-uint16(hbit)]
					}
					raster[idx] = word
					idx++
					for i := 0; i < int(gr.repeat); i++ {
						for j := 0; j < int(wordwidth); j++ {
							raster[idx] = raster[idx-int(wordwidth)]
							idx++
						}
					}
					rowsleft -= int16(gr.repeat) + 1
					gr.repeat = 0
					word = 0
					wordweight = 16
					count -= uint16(hbit)
					hbit = int16(gr.g.width)
				default:
					if turnon {
						word += gpower[wordweight]
					}
					raster[idx] = word
					idx++
					word = 0
					count -= wordweight
					hbit -= int16(wordweight)
					wordweight = 16
				}
			}
			turnon = !turnon
		}
		if rowsleft != 0 || hbit != int16(gr.g.width) {
			panic(fmt.Errorf("error while unpacking: more bits than required: rowsleft=%d hbit=%d width=%d",
				rowsleft, hbit, gr.g.width,
			))
		}
	}

	{
		// build raster data
		var (
			widx = 0
			word = sli
		)
		for row := 0; row < int(gr.g.height); row++ {
			var (
				bitsleft uint8
				nextword uint16
				nextbyte uint8
			)
			for col := 0; col < int(gr.g.width); col += 8 {
				switch {
				case bitsleft >= 8:
					nextbyte = uint8(nextword >> (bitsleft - 8) & 0xff)
					bitsleft -= 8
					mask = append(mask, nextbyte)
				default:
					nextbyte = uint8(nextword << (8 - bitsleft) & 0xff)
					widx++
					nextword = word[widx]
					nextbyte = nextbyte | uint8(nextword>>(16-(8-bitsleft))&0xff)
					bitsleft = 16 - (8 - bitsleft)
					mask = append(mask, nextbyte)
				}
			}
		}
	}

	return mask
}

func (gr *glyphReader) pkbyte() uint16 {
	return uint16(gr.r.ReadU8())
}

func (gr *glyphReader) pknum() uint32 {
	var (
		i, j uint16
		dynf = uint16(gr.dynf)
	)
	i = uint16(gr.nyb())
	switch {
	case i == 0:
		for {
			j = uint16(gr.nyb())
			i++
			if j != 0 {
				break
			}
		}
		switch {
		case i > 3:
			return gr.huge(i, j)
		default:
			for i > 0 {
				j = j*16 + uint16(gr.nyb())
				i--
			}
			return uint32(j - 15 + (13-dynf)*16 + dynf)
		}
	case i <= dynf:
		return uint32(i)
	case i < 14:
		v := dynf + 1
		return uint32((i-v)*16 + uint16(gr.nyb()) + v)
	default:
		switch i {
		case 14:
			gr.repeat = gr.pknum()
		default:
			gr.repeat = 1
		}
		return gr.read()
	}
}

func (gr *glyphReader) rest() uint32 {
	switch {
	case gr.remainder < 0:
		gr.remainder = -gr.remainder
		return 0
	case gr.remainder > 0:
		switch {
		case gr.remainder > 4000:
			gr.remainder = 4000 - gr.remainder
			return 4000
		default:
			i := uint32(gr.remainder)
			gr.remainder = 0
			gr.read = gr.pknum
			return i
		}
	}
	panic("impossible")
}

func (gr *glyphReader) huge(i, k uint16) uint32 {
	var (
		j    = k
		dynf = int32(gr.dynf)
	)
	for i != 0 {
		j = (j << 4) + uint16(gr.nyb())
		i--
	}
	gr.remainder = int32(j) - 15 + (13-dynf)*16 + dynf
	gr.read = gr.rest
	return gr.rest()
}

func (gr *glyphReader) nyb() int16 {
	var v uint16
	switch gr.bitweight {
	case 0:
		gr.bitweight = 16
		gr.inputbyte = uint16(gr.pkbyte())
		v = gr.inputbyte >> 4
	default:
		gr.bitweight = 0
		v = gr.inputbyte & 15
	}
	return int16(v)
}

func (gr *glyphReader) getbit() bool {
	gr.bitweight >>= 1
	if gr.bitweight == 0 {
		gr.inputbyte = gr.pkbyte()
		gr.bitweight = 128
	}
	return gr.inputbyte&gr.bitweight != 0
}
