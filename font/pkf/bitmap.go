// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package pkf

import (
	"fmt"
	"io"
)

// Bitmap displays the rune c as an ASCII bitmap to the provided writer.
func (fnt *Font) Bitmap(o io.Writer, c rune, h, w int) error {
	const raw = false
	return fnt.displayGlyph(o, c, h, w, raw, func(w io.Writer, u uint8, n int) {
		bit := uint8(1 << 7)
		for ; n > 0; n-- {
			switch {
			case u&bit != 0:
				fmt.Fprintf(w, "*")
			default:
				fmt.Fprintf(w, ".")
			}
			bit >>= 1
		}
	})
}

// Hexmap displays the rune c as an ASCII hexmap to the provided writer.
func (fnt *Font) Hexmap(o io.Writer, c rune, h, w int) error {
	const raw = false
	return fnt.displayGlyph(o, c, h, w, raw, func(w io.Writer, v uint8, n int) {
		fmt.Fprintf(w, "%02x", v)
	})
}

// Rawmap displays the rune c as an ASCII rawmap to the provided writer.
func (fnt *Font) Rawmap(o io.Writer, c rune, h, w int) error {
	const raw = true
	return fnt.displayGlyph(o, c, h, w, raw, func(w io.Writer, v uint8, n int) {
		fmt.Fprintf(w, "0x%02x, ", lsbf(v))
	})
}

func (fnt *Font) displayGlyph(o io.Writer, c rune, h, w int, raw bool, fun func(w io.Writer, u uint8, n int)) error {
	var g *Glyph
	for i := range fnt.glyphs {
		if fnt.glyphs[i].code == uint32(c) {
			g = &fnt.glyphs[i]
			g.unpack()
			break
		}
	}
	if g == nil {
		return fmt.Errorf("could not find glyph 0x%x", c)
	}

	var (
		H, dh int
		W, dw int
	)

	H = int(g.height)
	if h == 0 {
		h = H
	}
	dh = (h - H) / 2

	W = int(g.width)
	if w == 0 {
		w = W
	}
	dw = (w - W) / 2

	fmt.Fprintf(o, "\n")
	switch {
	case raw:
		fmt.Fprintf(o, "#define %s_%c_width \t %d\n", "fname", g.code, w)
		fmt.Fprintf(o, "#define %s_%c_height \t %d\n", "fname", g.code, h)
		fmt.Fprintf(o, "#define %s_%c_xoff \t %d\n", "fname", g.code, dw)
		fmt.Fprintf(o, "#define %s_%c_yoff \t %d\n", "fname", g.code, dh)
		fmt.Fprintf(o, "static char %s_%c_bits[] = {", "fname", g.code)
	default:
		fmt.Fprintf(o, "character : %d (%c)\n", g.code, g.code)
		fmt.Fprintf(o, "   height : %d\n", g.height)
		fmt.Fprintf(o, "    width : %d\n", g.width)
		fmt.Fprintf(o, "     xoff : %d\n", g.xoff)
		fmt.Fprintf(o, "     yoff : %d\n", g.yoff)
	}

	for row := 0; row < h-H-dh; row++ {
		fmt.Fprintf(o, "\n  ")
		for col := 0; col < w; col += 8 {
			n := clip(w-col, 8)
			fun(o, 0, n)
		}
	}

	var i int
	for row := 0; row < int(g.height); row++ {
		fmt.Fprintf(o, "\n  ")
		for col := 0; col < int(g.width); col += 8 {
			v := g.mask[i]
			n := clip(int(g.width)-col, 8)
			fun(o, v, n)
			i++
		}
	}

	for row := h - dh; row < h; row++ {
		fmt.Fprintf(o, "\n  ")
		for col := 0; col < w; col += 8 {
			n := clip(w-col, 8)
			fun(o, 0, n)
		}
	}

	switch {
	case raw:
		fmt.Fprintf(o, "};\n")
	default:
		fmt.Fprintf(o, "\n")
	}

	return nil
}

func clip(v, max int) int {
	if v >= max {
		return max
	}
	return v
}

func lsbf(u uint8) uint8 {
	var (
		bit, o uint8
	)
	for i := 0; i < 8; i++ {
		bit = u & 0o1
		o = (o << 1) | bit
		u = u >> 1
	}
	return o
}
