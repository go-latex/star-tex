// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package tfm

import (
	"bytes"
	"fmt"
	"io"
)

type fontFamily string

const (
	fontTypeVanilla fontFamily = "TEX TEXT"
	fontTypeMathSym fontFamily = "TEX MATH SYMBOLS"
	fontTypeMathExt fontFamily = "TEX MATH EXTENSION"
)

// Font is a TeX Font metrics.
type Font struct {
	hdr  fileHeader
	body fileBody
}

type fileHeader struct {
	lf uint16 // length of the entire file, in words
	lh uint16 // length of the header data, in words
	bc uint16 // smallest character code in the font
	ec uint16 // largest character code in the font
	nw uint16 // number of words in the width table
	nh uint16 // number of words in the height table
	nd uint16 // number of words in the depth table
	ni uint16 // number of words in the italic correction table
	nl uint16 // number of words in the lig/kern table
	nk uint16 // number of words in the kern table
	ne uint16 // number of words in the extensible character table
	np uint16 // number of font parameter words
}

// Parse parses a TFM file.
func Parse(r io.Reader) (Font, error) {
	var (
		rr  = newReader(r)
		fnt Font
		err error
	)

	err = fnt.readHeader(rr)
	if err != nil {
		return fnt, fmt.Errorf("could not parse TFM file header: %w", err)
	}

	err = fnt.readBody(rr)
	if err != nil {
		return fnt, fmt.Errorf("could not parse TFM file body: %w", err)
	}

	return fnt, nil
}

func (fnt *Font) DesignSize() Int12_20 {
	return fnt.body.header.designSize
}

func (fnt *Font) CodingScheme() string {
	return fnt.body.header.codingScheme
}

func (fnt *Font) Name() string {
	return fnt.body.header.fontID
}

// NumGlyphs returns the number of glyphs in this font.
func (fnt *Font) NumGlyphs() int {
	return int(fnt.hdr.ec) + 1 - int(fnt.hdr.bc)
}

// GlyphIndex returns the GlyphIndex for the given rune.
//
// GlyphIndex returns -1 if there is no such rune.
func (fnt *Font) GlyphIndex(x rune) GlyphIndex {
	i := int(x)
	if !(int(fnt.hdr.bc) <= i && i <= int(fnt.hdr.ec)) {
		panic(fmt.Errorf("glyph out of range"))
	}
	i -= int(fnt.hdr.bc)
	return GlyphIndex(i)
}

func (fnt *Font) glyph(x GlyphIndex) glyphInfo {
	return fnt.body.glyphs[x]
}

// GlyphAdvance returns the advance width of r's glyph.
//
// It returns !ok if the face does not contain a glyph for r.
func (fnt *Font) GlyphAdvance(x rune) (Int12_20, bool) {
	i := int(x)
	if !(int(fnt.hdr.bc) <= i && i <= int(fnt.hdr.ec)) {
		return 0, false
	}
	i -= int(fnt.hdr.bc)
	g := fnt.body.glyphs[i]
	return fnt.body.width[g.wd()], true
}

func (fnt *Font) readHeader(r *reader) error {
	hdr := &fnt.hdr
	err := r.readHeader(hdr)
	if err != nil {
		return fmt.Errorf("could not parse TFM file header: %w", err)
	}

	if !(int32(hdr.bc)-1 <= int32(hdr.ec) && hdr.ec <= 255) {
		return fmt.Errorf("invalid TFM file header glyph code range")
	}

	if !(hdr.ne <= 256) {
		return fmt.Errorf("invalid TFM file header extensible character table")
	}

	sum := 6 + hdr.lh + (hdr.ec - hdr.bc + 1) + hdr.nw + hdr.nh + hdr.nd + hdr.ni + hdr.nl + hdr.nk + hdr.ne + hdr.np
	if hdr.lf != sum {
		return fmt.Errorf("invalid TFM file length")
	}

	return nil
}

type fileBody struct {
	header  header
	glyphs  []glyphInfo
	width   []Int12_20
	height  []Int12_20
	depth   []Int12_20
	italic  []Int12_20
	ligKern []ligKernCmd
	kern    []Int12_20
	exten   []extensible
	param   []Int12_20
}

type header struct {
	chksum       uint32
	designSize   Int12_20
	codingScheme string
	fontID       string
	sevenBitSafe bool
	face         byte

	extra []Int12_20
}

func (fnt *Font) readBody(r *reader) error {
	if r.err != nil {
		return r.err
	}

	{
		raw := make([]byte, fnt.hdr.lh*4)
		_, err := io.ReadFull(r, raw)
		if err != nil {
			return fmt.Errorf("could not read TFM file body header: %w", err)
		}

		r := newReader(bytes.NewReader(raw))
		fnt.body.header.chksum = r.readU32()
		fnt.body.header.designSize = Int12_20(r.readU32())
		if fnt.hdr.lh > 2 {
			fnt.body.header.codingScheme = r.readStr(40)
			fnt.body.header.fontID = r.readStr(20)
			fnt.body.header.sevenBitSafe = r.readU8() == 0b1000_0000
			_ = r.readU16() // unused
			fnt.body.header.face = r.readU8()
		}
		if lh := int(fnt.hdr.lh); lh > 18 {
			n := lh - 18
			fnt.body.header.extra = r.readFWs(n)
		}
		if r.err != nil {
			return r.err
		}
	}

	fnt.body.glyphs = r.readCharInfos(int(fnt.hdr.ec - fnt.hdr.bc + 1))
	fnt.body.width = r.readFWs(int(fnt.hdr.nw))
	fnt.body.height = r.readFWs(int(fnt.hdr.nh))
	fnt.body.depth = r.readFWs(int(fnt.hdr.nd))
	fnt.body.italic = r.readFWs(int(fnt.hdr.ni))
	fnt.body.ligKern = r.readLigKerns(int(fnt.hdr.nl))
	fnt.body.kern = r.readFWs(int(fnt.hdr.nk))
	fnt.body.exten = r.readExtens(int(fnt.hdr.ne))
	fnt.body.param = r.readFWs(int(fnt.hdr.np))

	return nil
}

func (fnt *Font) MarshalText() ([]byte, error) {
	var (
		buf = new(bytes.Buffer)
		err = newTextEncoder(buf).encode(fnt)
	)
	return buf.Bytes(), err
}
