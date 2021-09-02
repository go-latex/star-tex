// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"bytes"
	"io"
	"os"
	"path/filepath"
	"strings"
	"testing"

	"star-tex.org/x/tex/kpath"
)

func TestPNG(t *testing.T) {
	tmp, err := os.MkdirTemp("", "dvi-cnv-")
	if err != nil {
		t.Fatalf("could not create tmp dir: %+v", err)
	}
	defer os.RemoveAll(tmp)

	for _, tc := range []struct {
		name string
	}{
		{"../../testdata/hello_golden.dvi"},
		{"../../testdata/xcolor_golden.dvi"},
		// {"../../testdata/pages_golden.dvi"}, // FIXME(sbinet): better handling of multi-pages-PNGs.
	} {
		t.Run(filepath.Base(tc.name), func(t *testing.T) {
			f, err := os.Open(tc.name)
			if err != nil {
				t.Fatalf("could not open DVI file: %+v", err)
			}
			defer f.Close()

			name := filepath.Base(tc.name)
			name = strings.Replace(name, "_golden.dvi", ".png", 1)

			oname := filepath.Join(tmp, name)
			err = interp(kpath.New(), io.Discard, oname, f)
			if err != nil {
				t.Fatalf("could not convert DVI to PNG: %+v", err)
			}

			got, err := os.ReadFile(strings.Replace(oname, ".png", "_1.png", 1))
			if err != nil {
				t.Fatalf("could not read output PNG: %+v", err)
			}

			name = strings.Replace(name, ".png", "_golden.png", 1)
			want, err := os.ReadFile(filepath.Join("testdata", name))
			if err != nil {
				t.Fatalf("could not read reference file: %+v", err)
			}

			if !bytes.Equal(got, want) {
				chk := filepath.Base(oname)
				chk = strings.Replace(chk, ".png", "_1.png", 1)
				_ = os.WriteFile(filepath.Join("testdata", chk), got, 0644)
				t.Fatalf("files compare different")
			}
		})
	}
}
