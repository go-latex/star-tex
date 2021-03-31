// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package pkf

import (
	"fmt"
	"io"

	"star-tex.org/x/tex/font/fixed"
	"star-tex.org/x/tex/internal/iobuf"
)

// Units are an integral number of abstract, scalable "font units". The em
// square is typically 1000 or 2048 "font units". This would map to a certain
// number (e.g. 30 pixels) of physical pixels, depending on things like the
// display resolution (DPI) and font size (e.g. a 12 point font).
type Units int32

// Font is a Packed Font.
type Font struct {
	hdr    CmdPre
	glyphs []Glyph
}

// Parse parses a Packed Font file.
func Parse(r io.Reader) (*Font, error) {
	raw, err := io.ReadAll(r)
	if err != nil {
		return nil, err
	}
	rr := iobuf.NewReader(raw)

	if opCode(rr.PeekU8()) != opPre {
		return nil, fmt.Errorf("pkf: invalid PK header")
	}

	var fnt Font
	fnt.hdr.read(rr)

specials:
	for {
		op := opCode(rr.PeekU8())
		if op < opXXX1 || op == opPost {
			break specials
		}
		switch op {
		case opXXX1, opXXX2, opXXX3, opXXX4:
			op.cmd().read(rr)
		case opYYY:
			op.cmd().read(rr)
		case opNOP:
			op.cmd().read(rr)
		case 247, 248, 249, 250, 251, 252, 253, 254, 255:
			return nil, fmt.Errorf("pkf: unexpected PK flagbyte 0x%x (%d)", op, op)
		}
	}

loop:
	for {
		op := opCode(rr.PeekU8())
		switch op {
		case opPost:
			break loop
		case opNOP:
			op.cmd().read(rr)
		case opXXX1, opXXX2, opXXX3, opXXX4:
			op.cmd().read(rr)
		case opYYY:
			op.cmd().read(rr)
		default:
			switch {
			case op < opXXX1:
				glyph, err := readGlyph(rr)
				if err != nil {
					return nil, err
				}
				fnt.glyphs = append(fnt.glyphs, glyph)
			default:
				return nil, fmt.Errorf("pkf: invalid opcode 0x%x (%d)", op, op)
			}
		}
	}
	return &fnt, nil
}

// UnitsPerEm returns the number of units per em for that font.
func (fnt *Font) UnitsPerEm() Units {
	// FIXME(sbinet): extract or infer from TFM.body.param ?
	return 1000
}

// DesignSize returns the TFM/PK font's design size.
func (fnt *Font) DesignSize() fixed.Int12_20 {
	return fixed.Int12_20(fnt.hdr.Design)
}

// Checksum returns the PK font checksum of that font.
// Checksum should be equal to the TFM checksum.
func (fnt *Font) Checksum() uint32 {
	return fnt.hdr.Checksum
}

// NumGlyphs returns the number of glyphs in this font.
func (fnt *Font) NumGlyphs() int {
	return len(fnt.glyphs)
}

// GlyphAt returns the i-th glyph from the PK font.
func (fnt *Font) GlyphAt(i int) *Glyph {
	if i < 0 || len(fnt.glyphs) <= i {
		return nil
	}
	return &fnt.glyphs[i]
}

// Glyph returns the glyph corresponding to the provided rune r,
// or nil if it is not present in the PK font.
func (fnt *Font) Glyph(r rune) *Glyph {
	g, ok := fnt.glyph(r)
	if !ok {
		return nil
	}
	return g
}

func (fnt *Font) index(r rune) int {
	for i := range fnt.glyphs {
		if fnt.glyphs[i].code == uint32(r) {
			return i
		}
	}
	return -1
}

func (fnt *Font) glyph(r rune) (*Glyph, bool) {
	for i := range fnt.glyphs {
		g := &fnt.glyphs[i]
		if g.code == uint32(r) {
			return g, true
		}
	}
	return nil, false
}
