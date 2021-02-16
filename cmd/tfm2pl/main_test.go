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
		"../../tfm/testdata/simple.tfm",
	} {
		t.Run(filepath.Base(name), func(t *testing.T) {
			f, err := os.Open(name)
			if err != nil {
				t.Fatalf("could not open TFM file: %+v", err)
			}
			defer f.Close()

			o := new(bytes.Buffer)
			err = process(o, f)
			if err != nil {
				t.Fatalf("could not process TFM file: %+v", err)
			}

			want, err := ioutil.ReadFile(strings.Replace(name, ".tfm", "_golden.pl", 1))
			if err != nil {
				t.Fatalf("could not open reference PL file: %+v", err)
			}

			if got, want := o.Bytes(), want; !bytes.Equal(got, want) {
				t.Fatalf("PL files differ")
			}
		})
	}
}
