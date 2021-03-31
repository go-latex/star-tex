// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package pkf

import (
	"star-tex.org/x/tex/internal/iobuf"
)

// Cmd is a PK command.
type Cmd interface {
	opcode() opCode
	Name() string

	read(r *iobuf.Reader)
}

type CmdXXX1 struct {
	Value []byte
}

func (CmdXXX1) opcode() opCode { return opXXX1 }
func (CmdXXX1) Name() string   { return "pk_xxx1" }
func (cmd *CmdXXX1) read(r *iobuf.Reader) {
	_ = r.ReadU8()
	n := int(r.ReadU8())
	cmd.Value = r.ReadBuf(n)
}

type CmdXXX2 struct {
	Value []byte
}

func (CmdXXX2) opcode() opCode { return opXXX2 }
func (CmdXXX2) Name() string   { return "pk_xxx2" }
func (cmd *CmdXXX2) read(r *iobuf.Reader) {
	_ = r.ReadU8()
	n := int(r.ReadU16())
	cmd.Value = r.ReadBuf(n)
}

type CmdXXX3 struct {
	Value []byte
}

func (CmdXXX3) opcode() opCode { return opXXX3 }
func (CmdXXX3) Name() string   { return "pk_xxx3" }
func (cmd *CmdXXX3) read(r *iobuf.Reader) {
	_ = r.ReadU8()
	n := int(r.ReadU24())
	cmd.Value = r.ReadBuf(n)
}

type CmdXXX4 struct {
	Value []byte
}

func (CmdXXX4) opcode() opCode { return opXXX4 }
func (CmdXXX4) Name() string   { return "pk_xxx4" }
func (cmd *CmdXXX4) read(r *iobuf.Reader) {
	_ = r.ReadU8()
	n := int(r.ReadU32())
	cmd.Value = r.ReadBuf(n)
}

type CmdYYY struct {
	Value uint32
}

func (CmdYYY) opcode() opCode { return opYYY }
func (CmdYYY) Name() string   { return "pk_yyy" }
func (cmd *CmdYYY) read(r *iobuf.Reader) {
	_ = r.ReadU8()
	cmd.Value = r.ReadU32()
}

type CmdPost struct{}

func (CmdPost) opcode() opCode { return opPost }
func (CmdPost) Name() string   { return "pk_post" }
func (CmdPost) read(r *iobuf.Reader) {
	_ = r.ReadU8()
}

type CmdNOP struct{}

func (CmdNOP) opcode() opCode { return opNOP }
func (CmdNOP) Name() string   { return "pk_nop" }
func (CmdNOP) read(r *iobuf.Reader) {
	_ = r.ReadU8()
}

type CmdPre struct {
	Version  uint8
	Msg      string
	Design   uint32
	Checksum uint32
	Hppp     uint32
	Vppp     uint32
}

func (CmdPre) opcode() opCode { return opPre }
func (CmdPre) Name() string   { return "pk_pre" }
func (cmd *CmdPre) read(r *iobuf.Reader) {
	_ = r.ReadU8()
	cmd.Version = r.ReadU8()
	n := int(r.ReadU8())
	cmd.Msg = string(r.ReadBuf(n))
	cmd.Design = r.ReadU32()
	cmd.Checksum = r.ReadU32()
	cmd.Hppp = r.ReadU32()
	cmd.Vppp = r.ReadU32()
}

var (
	_ Cmd = (*CmdXXX1)(nil)
	_ Cmd = (*CmdXXX2)(nil)
	_ Cmd = (*CmdXXX3)(nil)
	_ Cmd = (*CmdXXX4)(nil)
	_ Cmd = (*CmdYYY)(nil)
	_ Cmd = (*CmdPost)(nil)
	_ Cmd = (*CmdNOP)(nil)
	_ Cmd = (*CmdPre)(nil)
)
