// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package tfm

import (
	"io/ioutil"
	"os"
	"reflect"
	"strings"
	"testing"
)

func TestFont(t *testing.T) {
	for _, tc := range []struct {
		name      string
		numglyphs int
		family    string
		scheme    string
		size      Int12_20
	}{
		{
			name:      "testdata/simple.tfm",
			numglyphs: 1,
			family:    "hi parc",
			scheme:    "testing",
			size:      Int12_20(5 << 20),
		},
		{
			name:      "testdata/cmr10.tfm",
			numglyphs: 128,
			family:    "CMR",
			scheme:    "TeX text",
			size:      Int12_20(10 << 20),
		},
		{
			name:      "testdata/cmex10.tfm",
			numglyphs: 128,
			family:    "CMEX",
			scheme:    "TeX math extension",
			size:      Int12_20(10 << 20),
		},
		{
			name:      "testdata/cmbsy10.tfm",
			numglyphs: 128,
			family:    "CMBSY",
			scheme:    "TeX math symbols",
			size:      Int12_20(10 << 20),
		},
		{
			name:      "testdata/lmroman10-regular.tfm",
			numglyphs: 256,
			family:    "lmroman10-regular",
			scheme:    "Unspecified",
			size:      Int12_20(10 << 20),
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			tfm, err := os.Open(tc.name)
			if err != nil {
				t.Fatalf("could not open TFM font file: %+v", err)
			}
			defer tfm.Close()

			fnt, err := Parse(tfm)
			if err != nil {
				t.Fatalf("could not parse TFM font file: %+v", err)
			}

			if got, want := fnt.NumGlyphs(), tc.numglyphs; got != want {
				t.Fatalf("invalid number of fonts: got=%d, want=%d", got, want)
			}

			if got, want := fnt.Name(), tc.family; got != want {
				t.Fatalf("invalid font family: got=%q, want=%q", got, want)
			}

			if got, want := fnt.CodingScheme(), tc.scheme; got != want {
				t.Fatalf("invalid coding schema: got=%q, want=%q", got, want)
			}

			if got, want := fnt.DesignSize(), tc.size; got != want {
				t.Fatalf(
					"invalid design size: got=%v (%d), want=%v (%d)",
					got, got, want, want,
				)
			}

			txt, err := fnt.MarshalText()
			if err != nil {
				t.Fatalf("could not marshal font to PL: %+v", err)
			}

			fname := strings.Replace(tc.name, ".tfm", "_golden.pl", 1)
			pl, err := ioutil.ReadFile(fname)
			if err != nil {
				t.Fatalf("could not open PL reference file: %+v", err)
			}

			if got, want := txt, pl; !reflect.DeepEqual(got, want) {
				oname := strings.Replace(tc.name, ".tfm", ".pl", 1)
				_ = ioutil.WriteFile(oname, got, 0644)
				t.Fatalf(
					"invalid PL serialization",
				)
			}
		})
	}
}

func TestParse(t *testing.T) {
	for _, tc := range []struct {
		fname string
		want  Font
		glyph glyphInfo
		err   error
	}{
		{
			fname: "testdata/simple.tfm",
			want: Font{
				hdr: fileHeader{
					lf: 40, lh: 18, bc: 97, ec: 97,
					nw: 2, nh: 2, nd: 2, ni: 2,
					nl: 0, nk: 0, ne: 0, np: 7,
				},
				body: fileBody{
					header: header{
						chksum:       0xABCDEFAB,
						designSize:   Int12_20(5 << 20),
						codingScheme: "testing",
						fontID:       "hi parc",
						sevenBitSafe: true,
						face:         171,
					},
				},
			},
			glyph: glyphInfo{raw: [4]uint8{0x1, 0x11, 0x4, 0x0}},
		},
		{
			fname: "testdata/cmr10.tfm",
			want: Font{
				hdr: fileHeader{
					lf: 324, lh: 18, bc: 0, ec: 127,
					nw: 36, nh: 16, nd: 10, ni: 5,
					nl: 88, nk: 10, ne: 0, np: 7,
				},
				body: fileBody{
					header: header{
						chksum:       1274110073,
						designSize:   Int12_20(10 << 20),
						codingScheme: "TeX text",
						fontID:       "CMR",
						sevenBitSafe: false,
						face:         234,
					},
				},
			},
			glyph: glyphInfo{raw: [4]uint8{0xa, 0x30, 0x1, 0x48}},
		},
		{
			fname: "testdata/cmex10.tfm",
			want: Font{
				hdr: fileHeader{
					lf: 248, lh: 18, bc: 0, ec: 127,
					nw: 32, nh: 6, nd: 14, ni: 3,
					nl: 0, nk: 0, ne: 28, np: 13,
				},
				body: fileBody{
					header: header{
						chksum:       4205933842,
						designSize:   Int12_20(10 << 20),
						codingScheme: "TeX math extension",
						fontID:       "CMEX",
						sevenBitSafe: false,
						face:         234,
					},
				},
			},
			glyph: glyphInfo{raw: [4]uint8{0x1d, 0x28, 0x0, 0x0}},
		},
		{
			fname: "testdata/cmbsy10.tfm",
			want: Font{
				hdr: fileHeader{
					lf: 279, lh: 18, bc: 0, ec: 127,
					nw: 44, nh: 15, nd: 16, ni: 16,
					nl: 7, nk: 7, ne: 0, np: 22,
				},
				body: fileBody{
					header: header{
						chksum:       3771304972,
						designSize:   Int12_20(10 << 20),
						codingScheme: "TeX math symbols",
						fontID:       "CMBSY",
						sevenBitSafe: false,
						face:         234,
					},
				},
			},
			glyph: glyphInfo{raw: [4]uint8{0x10, 0xc0, 0x0, 0x0}},
		},
		{
			fname: "testdata/lmroman10-regular.tfm",
			want: Font{
				hdr: fileHeader{
					lf: 411, lh: 60, bc: 0, ec: 255,
					nw: 39, nh: 16, nd: 16, ni: 12,
					nl: 0, nk: 0, ne: 0, np: 6,
				},
				body: fileBody{
					header: header{
						chksum:       1674865313,
						designSize:   Int12_20(10 << 20),
						codingScheme: "Unspecified",
						fontID:       "lmroman10-regular",
						sevenBitSafe: false,
						face:         0,
						extra: []Int12_20{
							2806215269, 1635018084, 543324448, 1618244710,
							846489197, 539977839, 1835347810, 1768842612,
							796356466, 1798268783, 1853189423, 1936876335,
							1734964328, 1969368675, 1869426535, 1865246319,
							1853125423, 1818326121, 1848470895, 1684370030,
							794784877, 1882154607, 1853125423, 1869636974,
							1954115685, 795899234, 1818845999, 1819094892,
							1836216173, 1634611504, 762471783, 1970037106,
							779056230, 544499309, 796157299, 1952735604,
							1630497901, 1919905121, 1848717357, 1919248245,
							1818325550, 1952869671,
						},
					},
				},
			},
			glyph: glyphInfo{raw: [4]uint8{0x18, 0x74, 0x0, 0x0}},
		},
	} {
		t.Run(tc.fname, func(t *testing.T) {
			r, err := os.Open(tc.fname)
			if err != nil {
				t.Fatalf("could not open TFM file: %+v", err)
			}
			defer r.Close()

			fnt, err := Parse(r)
			switch {
			case err == nil && tc.err == nil:
				// ok.
			case err == nil && tc.err != nil:
				t.Fatalf("expected error %+v", tc.err)
			case err != nil && tc.err == nil:
				t.Fatalf("could not parse TFM file: %+v", err)
			case err != nil && tc.err != nil:
				if got, want := err.Error(), tc.err.Error(); got != want {
					t.Fatalf("invalid error:\ngot= %q\nwant=%q", got, want)
				}
				return
			}

			if got, want := fnt.hdr, tc.want.hdr; !reflect.DeepEqual(got, want) {
				t.Fatalf("invalid TFM file header:\ngot= %+v\nwant=%+v\n", got, want)
			}

			if got, want := fnt.body.header, tc.want.body.header; !reflect.DeepEqual(got, want) {
				t.Fatalf("invalid TFM body header:\ngot= %+v\nwant=%+v\n", got, want)
			}

			if got, want := fnt.body.width[0], Int12_20(0); got != want {
				t.Fatalf("invalid TFM width: got=%v, want=%v", got, want)
			}

			if got, want := fnt.body.height[0], Int12_20(0); got != want {
				t.Fatalf("invalid TFM height: got=%v, want=%v", got, want)
			}

			if got, want := fnt.body.depth[0], Int12_20(0); got != want {
				t.Fatalf("invalid TFM depth: got=%v, want=%v", got, want)
			}

			x := fnt.GlyphIndex('a')
			if x < 0 {
				t.Fatalf("could not find glyph")
			}

			glyph := fnt.glyph(x)
			if got, want := glyph, tc.glyph; got != want {
				t.Fatalf("invalid glyph-info:\ngot= %#v\nwant%#v", got, want)
			}
		})
	}
}
