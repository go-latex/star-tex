// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"fmt"
	"image"
	"image/color"
	"image/draw"
	"image/png"
	"log"
	"os"
	"strconv"

	"golang.org/x/image/font"
	xfix "golang.org/x/image/math/fixed"

	"star-tex.org/x/tex/dvi"
	"star-tex.org/x/tex/font/fixed"
	"star-tex.org/x/tex/font/pkf"
	"star-tex.org/x/tex/kpath"
)

const (
	shrink = 1
)

type pngRenderer struct {
	name string
	page int

	bkg color.Color

	pre   dvi.CmdPre
	post  dvi.CmdPost
	conv  float32 // converts DVI units to pixels
	tconv float32 // converts unmagnified DVI units to pixels
	dpi   float32

	ctx   kpath.Context
	faces map[fntkey]font.Face

	img draw.Image
	err error
}

func newRenderer(ctx kpath.Context, name string) *pngRenderer {
	return &pngRenderer{
		name:  name,
		ctx:   ctx,
		faces: make(map[fntkey]font.Face),
	}
}

func (pr *pngRenderer) Init(pre *dvi.CmdPre, post *dvi.CmdPost) {
	pr.pre = *pre
	pr.post = *post
	if pr.dpi == 0 {
		pr.dpi = 600 // FIXME(sbinet): infer from fonts?
	}
	res := pr.dpi
	conv := float32(pr.pre.Num) / 254000.0 * (res / float32(pr.pre.Den))
	pr.tconv = conv
	pr.conv = conv * float32(pr.pre.Mag) / 1000.0

	conv = 1/(float32(pre.Num)/float32(pre.Den)*
		(float32(pre.Mag)/1000.0)*
		(pr.dpi*shrink/254000.0)) + 0.5

	if pr.bkg == nil {
		pr.bkg = color.White
	}
}

func (pr *pngRenderer) BOP(bop *dvi.CmdBOP) {
	if pr.err != nil {
		return
	}

	pr.page = int(bop.C0)

	bnd := image.Rect(0, 0,
		int(pr.pixels(int32(pr.post.Width))),
		int(pr.pixels(int32(pr.post.Height))),
	)
	pr.img = image.NewRGBA(bnd)
	//pr.img = image.NewPaletted(bnd, color.Palette{pr.bkg, color.Black})
	draw.Draw(pr.img, bnd, image.NewUniform(pr.bkg), image.Point{}, draw.Over)
}

func (pr *pngRenderer) EOP() {
	if pr.err != nil {
		return
	}

	name := pr.name[:len(pr.name)-len(".png")] + "_" + strconv.Itoa(pr.page) + ".png"
	f, err := os.Create(name)
	if err != nil {
		pr.setErr(fmt.Errorf("could not create output PNG file: %w", err))
		return
	}
	defer f.Close()

	err = png.Encode(f, pr.img)
	if err != nil {
		pr.setErr(fmt.Errorf("could not encode PNG image: %w", err))
		return
	}

	err = f.Close()
	if err != nil {
		pr.setErr(fmt.Errorf("could not close output PNG file %q: %w", name, err))
		return
	}
}

func (pr *pngRenderer) DrawGlyph(x, y int32, font dvi.Font, glyph rune, c color.Color) {
	if pr.err != nil {
		return
	}

	dot := xfix.Point26_6{
		X: xfix.I(int(pr.pixels(x))),
		Y: xfix.I(int(pr.pixels(y))),
	}

	face, ok := pr.face(font)
	if !ok {
		return
	}

	dr, mask, maskp, _, ok := face.Glyph(dot, glyph)
	if !ok {
		pr.setErr(fmt.Errorf("could not find glyph 0x%02x", glyph))
		return
	}

	draw.DrawMask(
		pr.img, dr,
		image.NewUniform(c), image.Point{},
		mask, maskp, draw.Over,
	)
}

func (pr *pngRenderer) DrawRule(x, y, w, h int32, c color.Color) {
	if pr.err != nil {
		return
	}

	r := image.Rect(
		int(pr.pixels(x+0)), int(pr.pixels(y+0)),
		int(pr.pixels(x+w)), int(pr.pixels(y-h)),
	)

	draw.Draw(pr.img, r, image.NewUniform(c), image.Point{}, draw.Over)
}

func maxI32(a, b int32) int32 {
	if a > b {
		return a
	}
	return b
}

func roundF32(v float32) int32 {
	if v > 0 {
		return int32(v + 0.5)
	}
	return int32(v - 0.5)
}

func (pr *pngRenderer) pixels(v int32) int32 {
	x := pr.conv * float32(v)
	return roundF32(x / shrink)
}

func (pr *pngRenderer) rulepixels(v int32) int32 {
	x := int32(pr.conv * float32(v))
	if float32(x) < pr.conv*float32(v) {
		return x + 1
	}
	return x
}

type fntkey struct {
	name string
	size fixed.Int12_20
}

func (pr *pngRenderer) face(fnt dvi.Font) (font.Face, bool) {
	key := fntkey{
		name: fnt.Name(),
		size: fnt.Size(),
	}
	if f, ok := pr.faces[key]; ok {
		return f, ok
	}

	fname, err := pr.ctx.Find(fnt.Name() + ".pk")
	if err != nil {
		log.Printf("could not find font face %q: %+v", fnt.Name(), err)
		name := "cmr10"
		log.Printf("replacing with %q", name)
		fname, err = pr.ctx.Find(name + ".pk")
	}
	if err != nil {
		pr.setErr(fmt.Errorf("could not find font face %q: %+v", fnt.Name(), err))
		return nil, false
	}

	f, err := pr.ctx.Open(fname)
	if err != nil {
		pr.setErr(fmt.Errorf("could not open font face %q: %+v", fnt.Name(), err))
		return nil, false
	}
	defer f.Close()

	pk, err := pkf.Parse(f)
	if err != nil {
		pr.setErr(fmt.Errorf("could not parse font face %q: %+v", fnt.Name(), err))
		return nil, false
	}

	tfm := fnt.Metrics()

	if tfm.Checksum() != pk.Checksum() {
		pr.setErr(fmt.Errorf(
			"TFM and PK checksum do not match for %q: tfm=0x%x, pk=0x%x",
			fnt.Name(),
			tfm.Checksum(),
			pk.Checksum(),
		))
		return nil, false
	}

	face := pkf.NewFace(pk, tfm, &pkf.FaceOptions{
		Size: tfm.DesignSize().Float64(),
		DPI:  float64(pr.dpi),
	})
	pr.faces[key] = face

	return face, true
}

func (pr *pngRenderer) setErr(err error) {
	if pr.err != nil {
		return
	}
	pr.err = err
}

var (
	_ dvi.Renderer = (*pngRenderer)(nil)
)
