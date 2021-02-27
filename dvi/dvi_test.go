// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package dvi

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io"
	"os"
	"strings"
	"testing"

	"star-tex.org/x/tex/internal/iobuf"
)

func TestOpCode(t *testing.T) {
	if opSet1 != 128 {
		t.Fatalf("invalid set1 opcode %d", opSet1)
	}
	if opY1 != 162 {
		t.Fatalf("invalid y1 opcode %d", opY1)
	}
	if opZ1 != 167 {
		t.Fatalf("invalid z1 opcode %d", opZ1)
	}
	if opFntNum63 != 234 {
		t.Fatalf("invalid fnt_num_63 opcode %d", opFntNum63)
	}
	if opPre != 247 {
		t.Fatalf("invalid pre opcode %d", opPre)
	}
	if opPost != 248 {
		t.Fatalf("invalid post opcode %d", opPost)
	}
	if opPostPost != 249 {
		t.Fatalf("invalid post_post opcode %d", opPostPost)
	}

	// these facts are used in the TeX 'movement' procedure
	if opY1-opDown1 != opW1-opRight1 {
		t.Fatal("movement lemme #1 invalid")
	}
	if opZ1-opDown1 != opX1-opRight1 {
		t.Fatal("movement lemme #2 invalid")
	}
}

func TestCompiler(t *testing.T) {
	for _, tc := range []struct {
		json string
		want string
	}{
		// FIXME(sbinet): enable auto-optimization, so we get the same
		// output .dvi file.
		// {
		// 	json: "testdata/hello-no-opt.json",
		// 	want: "../testdata/hello_golden.dvi",
		// },
		{
			json: "testdata/hello-opt.json",
			want: "../testdata/hello_golden.dvi",
		},
	} {
		t.Run(tc.json, func(t *testing.T) {
			f, err := os.Open(tc.json)
			if err != nil {
				t.Fatal(err)
			}
			defer f.Close()

			buf := new(bytes.Buffer)
			c := compiler{
				r: f,
				w: buf,
			}
			err = c.compile()
			if err != nil {
				t.Fatalf("could not compile JSON document: %+v", err)
			}

			want, err := os.ReadFile(tc.want)
			if err != nil {
				t.Fatalf("could not read reference file: %+v", err)
			}

			if got, want := buf.Bytes(), want; !bytes.Equal(got, want) {
				oname := strings.Replace(tc.json, ".json", ".dvi", 1)
				_ = os.WriteFile(oname, got, 0644)
				t.Fatalf("DVI files differ: got=%d, want=%d", len(got), len(want))
			}
		})
	}
}

type compiler struct {
	r io.Reader
	w io.Writer
}

func (c compiler) compile() error {
	var (
		dec  = json.NewDecoder(c.r)
		msg  jsonCmd
		cmd  Cmd
		err  error
		line int

		w = iobuf.NewWriter(c.w)
	)
loop:
	for {
		line++
		err = dec.Decode(&msg)
		if err != nil {
			if err == io.EOF {
				err = nil
			}
			if err != nil {
				err = fmt.Errorf("line:%d: %w", line, err)
			}
			break loop
		}
		cmd, err = msg.cmd()
		if err != nil {
			break loop
		}
		cmd.write(w)
	}

	return err
}

type jsonCmd struct {
	Cmd  string          `json:"cmd"`
	Args json.RawMessage `json:"args"`
}

func (c jsonCmd) cmd() (Cmd, error) {
	var (
		raw  = bytes.NewReader([]byte(c.Args))
		dec  = json.NewDecoder(raw)
		err  error
		cmd  Cmd
		name = c.Cmd
	)
	switch name {
	case "pre":
		var c CmdPre
		err = dec.Decode(&c)
		cmd = &c
	case "bop":
		var c CmdBOP
		err = dec.Decode(&c)
		cmd = &c
	case "eop":
		var c CmdEOP
		err = dec.Decode(&c)
		cmd = &c
	case "push":
		var c CmdPush
		err = dec.Decode(&c)
		cmd = &c
	case "pop":
		var c CmdPop
		err = dec.Decode(&c)
		cmd = &c
	case "down1":
		var c CmdDown1
		err = dec.Decode(&c)
		cmd = &c
	case "down3":
		var c CmdDown3
		err = dec.Decode(&c)
		cmd = &c
	case "down4":
		var c CmdDown4
		err = dec.Decode(&c)
		cmd = &c
	case "right1":
		var c CmdRight1
		err = dec.Decode(&c)
		cmd = &c
	case "right2":
		var c CmdRight2
		err = dec.Decode(&c)
		cmd = &c
	case "right3":
		var c CmdRight3
		err = dec.Decode(&c)
		cmd = &c
	case "right4":
		var c CmdRight4
		err = dec.Decode(&c)
		cmd = &c
	case "w0":
		var c CmdW0
		err = dec.Decode(&c)
		cmd = &c
	case "w1":
		var c CmdW1
		err = dec.Decode(&c)
		cmd = &c
	case "w2":
		var c CmdW2
		err = dec.Decode(&c)
		cmd = &c
	case "w3":
		var c CmdW3
		err = dec.Decode(&c)
		cmd = &c
	case "w4":
		var c CmdW4
		err = dec.Decode(&c)
		cmd = &c
	case "x0":
		var c CmdX0
		err = dec.Decode(&c)
		cmd = &c
	case "x1":
		var c CmdX1
		err = dec.Decode(&c)
		cmd = &c
	case "x2":
		var c CmdX2
		err = dec.Decode(&c)
		cmd = &c
	case "x3":
		var c CmdX3
		err = dec.Decode(&c)
		cmd = &c
	case "x4":
		var c CmdX4
		err = dec.Decode(&c)
		cmd = &c
	case "y0":
		var c CmdY0
		err = dec.Decode(&c)
		cmd = &c
	case "y1":
		var c CmdY1
		err = dec.Decode(&c)
		cmd = &c
	case "y2":
		var c CmdY2
		err = dec.Decode(&c)
		cmd = &c
	case "y3":
		var c CmdY3
		err = dec.Decode(&c)
		cmd = &c
	case "y4":
		var c CmdY4
		err = dec.Decode(&c)
		cmd = &c
	case "z0":
		var c CmdZ0
		err = dec.Decode(&c)
		cmd = &c
	case "z1":
		var c CmdZ1
		err = dec.Decode(&c)
		cmd = &c
	case "z2":
		var c CmdZ2
		err = dec.Decode(&c)
		cmd = &c
	case "z3":
		var c CmdZ3
		err = dec.Decode(&c)
		cmd = &c
	case "z4":
		var c CmdZ4
		err = dec.Decode(&c)
		cmd = &c
	case "fnt_def1":
		var c CmdFntDef1
		err = dec.Decode(&c)
		cmd = &c
	case "post":
		var c CmdPost
		err = dec.Decode(&c)
		cmd = &c
	case "post_post":
		var c CmdPostPost
		err = dec.Decode(&c)
		cmd = &c
	default:
		str := c.Cmd
		switch {
		case strings.HasPrefix(str, "set_char_"):
			var c CmdSetChar
			fmt.Sscanf(str, "set_char_%d", &c.Value)
			cmd = &c
		case strings.HasPrefix(str, "fnt_num_"):
			var c CmdFntNum
			fmt.Sscanf(str, "fnt_num_%d", &c.ID)
			cmd = &c

		default:
			panic(fmt.Errorf("unknown cmd %q", c.Cmd))
		}
	}

	return cmd, err
}
