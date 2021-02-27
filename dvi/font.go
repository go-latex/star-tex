// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package dvi

import "star-tex.org/x/tex/tfm"

// Font describes a DVI font, with TeX Font Metrics and its
// associated font glyph data.
type Font struct {
	font *tfm.Font
	face *tfm.Face
}
