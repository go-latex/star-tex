// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Package tds provides a minimal TeX Directory Structure for star-tex.
package tds // import "star-tex.org/x/tex/internal/tds"

import "embed"

//go:embed tex/plain/base/plain.tex
//go:embed tex/generic/hyphen/hyphen.tex
//go:embed fonts/tfm/public/cm/*.tfm
//go:embed fonts/pk/ljfour/public/cm/dpi600/*.pk
var FS embed.FS
