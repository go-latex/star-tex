// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Package dvi implements encoding and decoding DVI documents.
//
// More informations about the DVI standard can be found here:
//
//  - https://ctan.crest.fr/tex-archive/dviware/driv-standard/level-0/dvistd0.pdf
//
package dvi // import "star-tex.org/x/tex/dvi"

import (
	"fmt"
	"image/color"
	"io"

	"star-tex.org/x/tex/internal/iobuf"
)

// Renderer defines the protocol to draw a DVI document.
type Renderer interface {
	Init(pre *CmdPre, post *CmdPost)
	BOP(bop *CmdBOP)
	EOP()

	DrawGlyph(x, y int32, font Font, glyph rune, c color.Color)
	DrawRule(x, y, w, h int32, c color.Color)
}

type nopRenderer struct{}

func (nopRenderer) Init(pre *CmdPre, post *CmdPost) {}
func (nopRenderer) BOP(cmd *CmdBOP)                 {}
func (nopRenderer) EOP()                            {}

func (nopRenderer) DrawGlyph(x, y int32, font Font, glyph rune, c color.Color) {}
func (nopRenderer) DrawRule(x, y, w, h int32, c color.Color)                   {}

var (
	_ Renderer = (*nopRenderer)(nil)
)

// Dump reads r until EOF and calls f for each decoded DVI command.
func Dump(r io.Reader, f func(cmd Cmd) error) error {
	buf, err := io.ReadAll(r)
	if err != nil {
		return fmt.Errorf("dvi: could not read DVI program: %w", err)
	}

	rr := iobuf.NewReader(buf)

	for {
		var (
			op  = opCode(rr.PeekU8())
			cmd = op.cmd()
		)
		if cmd == nil {
			return fmt.Errorf("dvi: unknown opcode %v (v=0x%x)", op, op)
		}

		cmd.read(rr)

		err = f(cmd)
		if err != nil {
			return fmt.Errorf("dvi: could not call user provided function: %w", err)
		}

		if cmd.opcode() == opPostPost {
			break
		}
	}

	return nil
}
