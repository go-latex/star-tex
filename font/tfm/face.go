// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package tfm

import (
	"star-tex.org/x/tex/font/fixed"
)

// Face is a TFM font face.
type Face struct {
	font  *Font
	scale fixed.Int12_20

	buf []byte
}

// FaceOptions describes the possible options given to NewFace when
// creating a new Face from a Font.
type FaceOptions struct {
	Size fixed.Int12_20 // Size is the font size in DVI points.
}

func defaultFaceOptions(font *Font) *FaceOptions {
	return &FaceOptions{
		Size: font.DesignSize(),
	}
}

// NewFace returns a new font.Face for the given Font.
//
// If opts is nil, sensible defaults will be used.
func NewFace(font *Font, opts *FaceOptions) Face {
	if opts == nil {
		opts = defaultFaceOptions(font)
	}
	return Face{
		font:  font,
		scale: opts.Size,
		buf:   make([]byte, 4),
	}
}

// Name returns the name of the font face.
func (face *Face) Name() string {
	return face.font.Name()
}

// GlyphAdvance returns the advance width of r's glyph.
//
// It returns !ok if the face does not contain a glyph for r.
func (face *Face) GlyphAdvance(r rune) (adv fixed.Int12_20, ok bool) {
	adv, ok = face.font.GlyphAdvance(r)
	if !ok {
		return 0, ok
	}
	return fixed.Int12_20((int64(adv) * int64(face.scale)) >> 20), true
}
