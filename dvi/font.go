// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package dvi

import (
	"star-tex.org/x/tex/font/fixed"
	"star-tex.org/x/tex/font/tfm"
)

// Font describes a DVI font, with TeX Font Metrics and its
// associated font glyph data.
type Font struct {
	font  tfm.Font
	scale fixed.Int12_20
}

func (fnt *Font) name() string {
	return fnt.font.Name()
}

func (fnt *Font) advance(r rune) (fixed.Int12_20, bool) {
	w, _, _, ok := fnt.font.Box(r)
	if !ok {
		return 0, ok
	}
	return fixed.Int12_20((int64(w) * int64(fnt.scale)) >> 20), true
}
