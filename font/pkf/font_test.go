// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package pkf

import (
	"testing"

	"star-tex.org/x/tex/font/fixed"
	"star-tex.org/x/tex/kpath"
)

func TestFont(t *testing.T) {
	ctx := kpath.New()
	for _, tc := range []struct {
		name      string
		numglyphs int
		design    fixed.Int12_20
		chksum    uint32
	}{
		{
			name:      "fonts/pk/ljfour/public/cm/dpi600/cmr10.pk",
			numglyphs: 128,
			design:    10485760,
			chksum:    1274110073,
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			f, err := ctx.Open(tc.name)
			if err != nil {
				t.Fatalf("could not open PK file: %+v", err)
			}
			defer f.Close()

			fnt, err := Parse(f)
			if err != nil {
				t.Fatalf("could not parse PK file: %+v", err)
			}

			if got, want := fnt.DesignSize(), tc.design; got != want {
				t.Fatalf("invalid design size: got=%v, want=%v", got, want)
			}

			if got, want := fnt.Checksum(), tc.chksum; got != want {
				t.Fatalf("invalid checksum: got=%v, want=%v", got, want)
			}

			if got, want := fnt.NumGlyphs(), tc.numglyphs; got != want {
				t.Fatalf("invalid number of glyphs: got=%d, want=%d", got, want)
			}

			for i := 0; i < fnt.NumGlyphs(); i++ {
				g := fnt.GlyphAt(i)
				g.unpack()
			}
		})
	}
}
