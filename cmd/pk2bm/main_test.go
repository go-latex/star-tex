// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main // import "star-tex.org/x/tex/cmd/pk2bm"

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
	"strconv"
	"testing"

	"star-tex.org/x/tex/kpath"
)

func TestPK2BM(t *testing.T) {
	ktx := kpath.New()

	fname, err := ktx.Find("cmr10.pk")
	if err != nil {
		t.Fatalf("could not find cmr10: %+v", err)
	}

	pkf, err := ktx.Open(fname)
	if err != nil {
		t.Fatalf("could not open cmr10: %+v", err)
	}
	defer pkf.Close()

	const (
		bitmap = true
		hexmap = false
		h      = 0
		w      = 0
		c      = 'a'
	)

	got := new(bytes.Buffer)
	err = process(got, pkf, rune(c), h, w, bitmap, hexmap)
	if err != nil {
		t.Fatalf("could not process char=%c: %+v", c, err)
	}

	if got, want := got.String(), wantA; got != want {
		t.Fatalf("invalid pkf2bm output:\ngot:\n%s\nwant:\n%s", got, want)
	}
}

func TestTeXPK2BM(t *testing.T) {
	if cmd, err := exec.LookPath("/usr/bin/pk2bm"); err != nil || cmd == "" {
		t.Skipf("skipping comparison against TeX pk2bm")
	}

	const chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`!@#$%^&*()_+-=[]{};'\\:\"|/.,<>?"
	const cmdir = "../../internal/tds/fonts/pk/ljfour/public/cm/dpi600"

	files, err := os.ReadDir(cmdir)
	if err != nil {
		t.Fatalf("could not open cm PK dir: %+v", err)
	}

	for _, file := range files {
		cmr10 := filepath.Join(cmdir, file.Name())
		pkf, err := os.ReadFile(cmr10)
		if err != nil {
			t.Fatalf("could not open cmr10 PK file: %+v", err)
		}
		t.Run(cmr10, func(t *testing.T) {

			for _, tc := range []byte(chars) {
				t.Run(string(tc), func(t *testing.T) {
					const (
						bitmap = true
						hexmap = false
						h      = 0
						w      = 0
					)
					got := new(bytes.Buffer)
					err := process(got, bytes.NewReader(pkf), rune(tc), h, w, bitmap, hexmap)
					if err != nil {
						t.Fatalf("could not process char=%c: %+v", tc, err)
					}

					args := []string{
						"-c", string(tc),
						"-H", strconv.Itoa(h),
						"-W", strconv.Itoa(w),
						cmr10,
					}

					switch {
					case bitmap:
						args = append([]string{"-b"}, args...)
					case hexmap:
						args = append([]string{"-h"}, args...)
					}

					want := new(bytes.Buffer)
					cmd := exec.Command(
						"/usr/bin/pk2bm",
						args...,
					)
					cmd.Stdout = want
					cmd.Stderr = want

					err = cmd.Run()
					if err != nil {
						t.Logf("===\n%s\n===\n", want.String())
						t.Fatalf("could not run TeX pk2bm: %+v", err)
					}

					if got, want := got.String(), want.String(); got != want {
						t.Fatalf("invalid pkf2bm output:\ngot:\n%s\nwant:\n%s", got, want)
					}
				})
			}
		})
	}
}

const wantA = `
character : 97 (a)
   height : 39
    width : 38
     xoff : -3
     yoff : 37

  ...........********...................
  ........**************................
  ......*****.......******..............
  .....***............*****.............
  ....*****............******...........
  ...*******............******..........
  ...********...........******..........
  ...********............******.........
  ...********............******.........
  ...********.............******........
  ....******..............******........
  .....****...............******........
  ........................******........
  ........................******........
  ........................******........
  ........................******........
  .................*************........
  .............*****************........
  ..........*********.....******........
  ........*******.........******........
  ......*******...........******........
  ....********............******........
  ...*******..............******........
  ..********..............******........
  .********...............******........
  .*******................******........
  .*******................******......**
  *******.................******......**
  *******.................******......**
  *******.................******......**
  *******................*******......**
  *******................*******......**
  ********..............********......**
  .*******.............***.*****......**
  .********............**...*****....**.
  ..********.........****...*****....**.
  ....*******......****......*********..
  ......**************........*******...
  .........********............*****....
`
