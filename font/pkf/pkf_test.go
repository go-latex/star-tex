// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package pkf

import (
	"testing"
)

func TestOpCode(t *testing.T) {
	for _, tc := range []struct {
		opcode opCode
		want   opCode
	}{
		{opXXX1, 240},
		{opXXX2, 241},
		{opXXX3, 242},
		{opXXX4, 243},
		{opYYY, 244},
		{opPost, 245},
		{opNOP, 246},
		{opPre, 247},
	} {
		t.Run(tc.opcode.cmd().Name(), func(t *testing.T) {
			if got, want := tc.opcode, tc.want; got != want {
				t.Fatalf("invalid opcode value: got=%d, want=%d", got, want)
			}
		})
	}
}

//func TestReader(t *testing.T) {
//	ctx := kpath.New()
//	for _, tc := range []struct {
//		name string
//		want string
//	}{
//		{
//			name: "fonts/pk/ljfour/public/cm/dpi600/cmr10.pk",
//			want: "xx",
//		},
//	} {
//		t.Run(tc.name, func(t *testing.T) {
//			f, err := ctx.Open(tc.name)
//			if err != nil {
//				t.Fatalf("could not open PK file: %+v", err)
//			}
//			defer f.Close()
//
//			r := NewReader(f)
//			err = r.Read(func(cmd Cmd) error {
//				log.Printf("cmd: %#v", cmd)
//				if cmd, ok := cmd.(*CmdPre); ok {
//					log.Printf("design: %d", cmd.Design)
//					log.Printf("chksum: %d", cmd.Checksum)
//					log.Printf("hppp: %d", cmd.Hppp)
//					log.Printf("vppp: %d", cmd.Vppp)
//				}
//				return nil
//			})
//			if err != nil {
//				t.Fatalf("could not read PK file: %+v", err)
//			}
//		})
//	}
//}
