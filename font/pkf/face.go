// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package pkf

import (
	"image"

	"golang.org/x/image/font"
	"golang.org/x/image/math/fixed"

	tfix "star-tex.org/x/tex/font/fixed"
	"star-tex.org/x/tex/font/tfm"
)

// Face implements the font.Face interface for PK fonts.
type Face struct {
	font  *Font
	tfm   *tfm.Font
	scale fixed.Int26_6

	glyphs map[rune]int
}

// FaceOptions describes the possible options given to NewFace when
// creating a new Face from a Font.
type FaceOptions struct {
	Size float64 // Size is the font size in DVI points.
	DPI  float64 // DPI is the dots per inch resolution
}

func defaultFaceOptions(font *tfm.Font) *FaceOptions {
	return &FaceOptions{
		Size: font.DesignSize().Float64(),
		DPI:  72,
	}
}

func NewFace(font *Font, metrics *tfm.Font, opts *FaceOptions) *Face {
	if opts == nil {
		opts = defaultFaceOptions(metrics)
	}
	return &Face{
		font:   font,
		tfm:    metrics,
		scale:  fixed.Int26_6(0.5 + (opts.Size * opts.DPI * 64 / 72)),
		glyphs: make(map[rune]int, len(font.glyphs)/4),
	}
}

// xscale returns x divided by unitsPerEm, rounded to the nearest fixed.Int26_6
// value (1/64th of a pixel).
func xscale(x fixed.Int26_6, unitsPerEm Units) fixed.Int26_6 {
	u := fixed.Int26_6(unitsPerEm)
	v := u / 2
	switch {
	case x >= 0:
		x += v
	default:
		x -= v
	}
	return x / u
}

// Close satisfies the font.Face interface.
func (*Face) Close() error {
	return nil
}

// Name returns the name of the font face.
func (face *Face) Name() string {
	return face.tfm.Name()
}

// Glyph returns the draw.DrawMask parameters (dr, mask, maskp) to draw r's
// glyph at the sub-pixel destination location dot, and that glyph's
// advance width.
//
// It returns !ok if the face does not contain a glyph for r.
//
// The contents of the mask image returned by one Glyph call may change
// after the next Glyph call. Callers that want to cache the mask must make
// a copy.
func (face *Face) Glyph(dot fixed.Point26_6, r rune) (dr image.Rectangle, mask image.Image, maskp image.Point, advance fixed.Int26_6, ok bool) {

	g, ok := face.glyph(r)
	if !ok {
		return
	}

	g.unpack()

	advance, ok = face.glyphAdvance(r, g)
	if !ok {
		return
	}

	dr = image.Rect(
		-int(g.xoff),
		-int(g.yoff),
		-int(g.xoff)+int(g.width),
		-int(g.yoff)+int(g.height),
	).Add(image.Pt(dot.X.Floor(), dot.Y.Floor()))

	msk := g.Mask()
	mask = &msk
	ok = true
	return
}

// GlyphBounds returns the bounding box of r's glyph, drawn at a dot equal
// to the origin, and that glyph's advance width.
//
// It returns !ok if the face does not contain a glyph for r.
//
// The glyph's ascent and descent are equal to -bounds.Min.Y and
// +bounds.Max.Y. The glyph's left-side and right-side bearings are equal
// to bounds.Min.X and advance-bounds.Max.X. A visual depiction of what
// these metrics are is at
// https://developer.apple.com/library/archive/documentation/TextFonts/Conceptual/CocoaTextArchitecture/Art/glyphterms_2x.png
func (face *Face) GlyphBounds(r rune) (bounds fixed.Rectangle26_6, advance fixed.Int26_6, ok bool) {
	g, ok := face.glyph(r)
	if !ok {
		return
	}
	return face.glyphBounds(r, g)
}

func (face *Face) glyphBounds(r rune, g *Glyph) (bounds fixed.Rectangle26_6, advance fixed.Int26_6, ok bool) {
	bounds, _, ok = face.tfm.GlyphBounds(r)
	if !ok {
		return
	}
	advance, ok = face.glyphAdvance(r, g)
	if !ok {
		return
	}

	em := face.font.UnitsPerEm()
	rescale := func(v fixed.Int26_6) fixed.Int26_6 {
		v *= fixed.Int26_6(em)
		v /= 1 << 6
		return v
	}

	bounds.Min.X = rescale(bounds.Min.X)
	bounds.Min.Y = rescale(bounds.Min.Y)
	bounds.Max.X = rescale(bounds.Max.X)
	bounds.Max.Y = rescale(bounds.Max.Y)

	bounds.Min.X = xscale(bounds.Min.X*face.scale, em)
	bounds.Min.Y = xscale(bounds.Min.Y*face.scale, em)
	bounds.Max.X = xscale(bounds.Max.X*face.scale, em)
	bounds.Max.Y = xscale(bounds.Max.Y*face.scale, em)

	dx := tfix.Int12_20(g.dx).ToInt26_6()
	dy := tfix.Int12_20(g.dy).ToInt26_6()

	bounds.Min.X += dx
	bounds.Max.X -= dx
	bounds.Min.Y += dy // FIXME(sbinet): check sign of vertical displacement
	bounds.Max.Y -= dy // FIXME(sbinet): check sign of vertical displacement

	return bounds, advance, ok
}

// GlyphAdvance returns the advance width of r's glyph.
//
// It returns !ok if the face does not contain a glyph for r.
func (face *Face) GlyphAdvance(r rune) (advance fixed.Int26_6, ok bool) {
	g, ok := face.glyph(r)
	if !ok {
		return
	}
	return face.glyphAdvance(r, g)
}

func (face *Face) glyphAdvance(r rune, g *Glyph) (advance fixed.Int26_6, ok bool) {
	advance, ok = face.tfm.GlyphAdvance(r)
	if !ok {
		return 0, false
	}

	em := face.font.UnitsPerEm()
	advance *= fixed.Int26_6(em) // FIXME(sbinet): by trial and error.
	advance /= 1 << 6            // figure out why we need this.

	advance = xscale(advance*face.scale, em)
	return advance, true
}

// Kern returns the horizontal adjustment for the kerning pair (r0, r1). A
// positive kern means to move the glyphs further apart.
func (face *Face) Kern(r0, r1 rune) fixed.Int26_6 {
	k := face.tfm.Kern(r0, r1)
	return xscale(k*face.scale, face.font.UnitsPerEm())
}

// Metrics returns the metrics for this Face.
func (face *Face) Metrics() font.Metrics {
	em := face.font.UnitsPerEm()

	met := face.tfm.Metrics()

	rescale := func(v fixed.Int26_6) fixed.Int26_6 {
		v *= fixed.Int26_6(em)
		v /= 1 << 6
		return v
	}

	met.Height = rescale(met.Height)
	met.Ascent = rescale(met.Ascent)
	met.Descent = rescale(met.Descent)
	met.XHeight = rescale(met.XHeight)
	met.CapHeight = rescale(met.CapHeight)

	met.Height = xscale(met.Height*face.scale, em)
	met.Ascent = xscale(met.Ascent*face.scale, em)
	met.Descent = xscale(met.Descent*face.scale, em)
	met.XHeight = xscale(met.XHeight*face.scale, em)
	met.CapHeight = xscale(met.CapHeight*face.scale, em)

	return met
}

func (face *Face) glyph(r rune) (*Glyph, bool) {
	if i, ok := face.glyphs[r]; ok {
		return &face.font.glyphs[i], true
	}
	i := face.font.index(r)
	if i < 0 {
		return nil, false
	}
	face.glyphs[r] = i
	return &face.font.glyphs[i], true

}

var (
	_ font.Face = (*Face)(nil)
)
