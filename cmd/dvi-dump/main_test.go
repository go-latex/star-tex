// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"bytes"
	"os"
	"path/filepath"
	"strings"
	"testing"

	"star-tex.org/x/tex/kpath"
)

func TestInterp(t *testing.T) {
	for _, tc := range []struct {
		name string
		want string
	}{
		{
			name: "../../testdata/hello_golden.dvi",
			want: "testdata/hello_golden.txt",
		},
		{
			name: "../../testdata/pages_golden.dvi",
			want: "testdata/pages_golden.txt",
		},
		{
			name: "../../testdata/xcolor_golden.dvi",
			want: "testdata/xcolor_golden.txt",
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			f, err := os.Open(tc.name)
			if err != nil {
				t.Fatalf("could not open input DVI file: %+v", err)
			}
			defer f.Close()

			got := new(bytes.Buffer)
			err = interp(kpath.New(), got, f)
			if err != nil {
				t.Fatalf("could not interpret DVI file: %+v", err)
			}

			want, err := os.ReadFile(tc.want)
			if err != nil {
				t.Fatalf("could not read reference file: %+v", err)
			}

			if got, want := got.Bytes(), want; !bytes.Equal(got, want) {
				oname := strings.Replace(filepath.Base(tc.want), "_golden", "", -1)
				oname = filepath.Join("testdata", oname)
				_ = os.WriteFile(oname, got, 0644)
				t.Fatalf("interpreted logs differ: got=%q, want=%q", oname, tc.want)
			}
		})
	}
}
