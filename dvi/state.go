// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package dvi

import (
	"star-tex.org/x/tex/font/tfm"
)

// regs is the set of DVI registers.
type regs struct {
	h int32 // h is the current horizontal position on the page.
	v int32 // v is the current vertical position on the page.

	w int32 // horizontal spacing
	x int32 // horizontal spacing
	y int32 // vertical spacing
	z int32 // vertical spacing

	hh int32 // hh is the current horizontal position on the page, in pixels.
	vv int32 // vv is the current vertical position on the page, in pixels.
}

type fntdef struct {
	ID       int
	Checksum uint32
	Size     int32
	Design   int32
	Area     string
	Name     string

	mag  int32
	font *tfm.Font
	face *tfm.Face
}

type state struct {
	fonts map[int]fntdef
	f     int // current font
	stack []regs
}

func newState() state {
	return state{
		fonts: make(map[int]fntdef),
		stack: make([]regs, 1),
	}
}

func (st *state) reset() {
	st.stack = st.stack[:1]
	st.stack[0] = regs{}
	st.f = -1
}

func (st *state) cur() *regs {
	return &st.stack[len(st.stack)-1]
}

func (st *state) push() {
	stk := st.cur()
	st.stack = append(st.stack, *stk)
}

func (st *state) pop() {
	if len(st.stack) == 0 {
		panic("dvi: unbalanced push/pop")
	}
	st.stack = st.stack[:len(st.stack)-1]
}
