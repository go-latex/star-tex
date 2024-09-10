// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package pkf

import "fmt"

// // pkID is the version of the PK file format.
// const pkID = 89

// opCode is a PK file format command identifier.
type opCode uint8

const (
	opXXX1 opCode = iota + 240 // Special command uint8-len large
	opXXX2                     // Special command uint16-len large
	opXXX3                     // Special command uint24-len large
	opXXX4                     // Special command uint32-len large
	opYYY                      // Special command 32b large
	opPost                     // Beginning of the postamble
	opNOP                      // no-op
	opPre                      // Beginning of the preamble
)

func (op opCode) cmd() Cmd {
	switch op {
	case opXXX1:
		return &CmdXXX1{}
	case opXXX2:
		return &CmdXXX2{}
	case opXXX3:
		return &CmdXXX3{}
	case opXXX4:
		return &CmdXXX4{}
	case opYYY:
		return &CmdYYY{}
	case opPost:
		return &CmdPost{}
	case opNOP:
		return &CmdNOP{}
	case opPre:
		return &CmdPre{}
	default:
		panic(fmt.Errorf("pkf: unknown opcode 0x%x (%d)", op, op))
	}
}
