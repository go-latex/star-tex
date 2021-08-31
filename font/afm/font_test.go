// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package afm

import (
	"math"
	"os"
	"testing"

	"star-tex.org/x/tex/font/fixed"
	"star-tex.org/x/tex/kpath"
)

func TestParseCMR10(t *testing.T) {
	ktx := kpath.New()
	name, err := ktx.Find("cmr10.afm")
	if err != nil {
		t.Fatalf("could not find cmr10.afm file: %+v", err)
	}

	f, err := ktx.Open(name)
	if err != nil {
		t.Fatalf("could not open afm: %+v", err)
	}
	defer f.Close()

	fnt, err := Parse(f)
	if err != nil {
		t.Fatalf("could not parse afm: %+v", err)
	}

	if fnt.ascender != fixed.I16_16(694) {
		t.Fatalf("invalid ascender: %v", fnt.ascender)
	}
}

func TestParse(t *testing.T) {
	for _, tc := range []string{
		"testdata/fake-vertical.afm",
		"testdata/times-with-composites.afm",
	} {
		t.Run(tc, func(t *testing.T) {
			f, err := os.Open(tc)
			if err != nil {
				t.Fatalf("could not open AFM test file: %+v", err)
			}
			defer f.Close()

			_, err = Parse(f)
			if err != nil {
				t.Fatalf("could not parse AFM test file: %+v", err)
			}
		})
	}
}

func TestInt16_16(t *testing.T) {
	const tol = 1e-5
	for _, tc := range []struct {
		str  string
		want float64
	}{
		{"0", 0},
		{"1.0", 1},
		{"1.2", 1.2},
		{"+1.2", +1.2},
		{"-1.2", -1.2},
	} {
		t.Run("", func(t *testing.T) {
			v := fixedFrom(tc.str)
			got := v.Float64()
			if diff := math.Abs(got - tc.want); diff > tol {
				t.Fatalf("invalid 16:16 value: got=%v, want=%v (diff=%e)", got, tc.want, diff)
			}
		})
	}
}
