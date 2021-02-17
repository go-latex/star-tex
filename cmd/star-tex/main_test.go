// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"bytes"
	"io/ioutil"
	"os"
	"path/filepath"
	"strings"
	"testing"
)

func TestProcess(t *testing.T) {
	for _, name := range []string{
		"testdata/hello.tex",
	} {
		t.Run(filepath.Base(name), func(t *testing.T) {
			r, err := os.Open(name)
			if err != nil {
				t.Fatalf("could not open TeX document: %+v", err)
			}
			defer r.Close()
			oname := strings.Replace(name, ".tex", ".dvi", 1)
			_ = os.RemoveAll(oname)

			o := new(bytes.Buffer)
			msg := new(bytes.Buffer)

			err = process(o, r, msg)
			if err != nil {
				t.Fatalf("could not process TeX document: %+v", err)
			}

			want, err := ioutil.ReadFile(strings.Replace(name, ".tex", "_golden.dvi", 1))
			if err != nil {
				t.Fatalf("could not read reference DVI file: %+v", err)
			}

			if got, want := o.Bytes(), want; !bytes.Equal(got, want) {
				_ = os.WriteFile(oname, got, 0644)
				t.Fatalf("DVI files compare different")
			}
		})
	}
}
