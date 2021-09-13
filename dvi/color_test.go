// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package dvi

import (
	"bytes"
	"errors"
	"image/color"
	"reflect"
	"testing"

	"star-tex.org/x/tex/kpath"
)

func TestColorHandler(t *testing.T) {
	ch := NewColorHandler(kpath.New())
	if !reflect.DeepEqual(ch.stack, []color.Color{color.White, color.Black}) {
		t.Fatalf("invalid color-handler stack: %+v", ch.stack)
	}
	for _, tc := range []struct {
		data  []byte
		stack []color.Color
		want  error
	}{
		{
			data:  []byte("background red"),
			stack: []color.Color{color.RGBA{R: 255, A: 255}, color.Black},
		},
		{
			data:  []byte("xxx some unknown special"),
			want:  ErrSkipHandler,
			stack: []color.Color{color.RGBA{R: 255, A: 255}, color.Black},
		},
		{
			data:  []byte("background white"),
			stack: []color.Color{color.Gray{Y: 255}, color.Black},
		},
		{
			data:  []byte("background White"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color push Black"),
			stack: []color.Color{color.White, color.Black, color.Black},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color push White"),
			stack: []color.Color{color.White, color.Black, color.White},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color push gray 0.5"),
			stack: []color.Color{color.White, color.Black, color.Gray{Y: 128}},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color push rgb 1 0 0"),
			stack: []color.Color{color.White, color.Black, color.RGBA{R: 255, A: 255}},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color push Gray 100"),
			stack: []color.Color{color.White, color.Black, color.Gray{Y: 100}},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color push RGB 0 0 100"),
			stack: []color.Color{color.White, color.Black, color.RGBA{B: 100, A: 255}},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color push HTML ffaadd"),
			stack: []color.Color{color.White, color.Black, color.RGBA{R: 255, G: 170, B: 221, A: 255}},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color push cmy 0.2 0.3 0.4"),
			stack: []color.Color{color.White, color.Black, color.CMYK{C: 51, M: 77, Y: 102}},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color push cmyk 0.2 0.3 0.4 0.5"),
			stack: []color.Color{color.White, color.Black, color.CMYK{C: 51, M: 77, Y: 102, K: 128}},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color push hsb .66667 1 1"), // blue
			stack: []color.Color{color.White, color.Black, color.RGBA{B: 255, A: 255}},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color push hsb .5 1 .5"), // teal
			stack: []color.Color{color.White, color.Black, color.RGBA{G: 128, B: 128, A: 255}},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color push HSB 128 255 128"), // teal
			stack: []color.Color{color.White, color.Black, color.RGBA{G: 126, B: 128, A: 255}},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color push  BurntOrange"),
			stack: []color.Color{color.White, color.Black, color.CMYK{M: 130, Y: 255}},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{color.White, color.Black},
		},
		{
			data:  []byte("color  BurntOrange"),
			stack: []color.Color{color.CMYK{M: 130, Y: 255}},
		},
		{
			data:  []byte("color pop"),
			stack: []color.Color{},
		},
	} {
		got := ch.Handle(tc.data)
		if !errors.Is(got, tc.want) {
			t.Fatalf("invalid handler output for %q:\ngot= %+v\nwant=%+v", tc.data, got, tc.want)
		}
		if !reflect.DeepEqual(ch.stack, tc.stack) {
			t.Fatalf("invalid handler stack for %q:\ngot= %+v\nwant=%+v", tc.data, ch.stack, tc.stack)
		}
	}
}

func TestBrackets(t *testing.T) {
	for _, tc := range []struct {
		line string
		want []string
	}{
		{
			line: ``,
			want: nil,
		},
		{
			line: `\DefineNamedColor{named}{GreenYellow}   {cmyk}{0.15,0,0.69,0}`,
			want: []string{`\DefineNamedColor`, "named", "GreenYellow", "cmyk", "0.15,0,0.69,0"},
		},
		{
			line: `\DefineNamedColor{named}{GreenYellow}   {cmyk}{0.15, 0, 0.69, 0}`,
			want: []string{`\DefineNamedColor`, "named", "GreenYellow", "cmyk", "0.15,0,0.69,0"},
		},
	} {
		t.Run("", func(t *testing.T) {
			got := brackets(tc.line)
			if !reflect.DeepEqual(got, tc.want) {
				t.Fatalf(
					"invalid tokens. line: %q\ngot= %q\nwant=%q",
					tc.line,
					got, tc.want,
				)
			}
		})
	}
}

func TestParsePrepareColorSet(t *testing.T) {
	raw := `%% in the same archive or directory.)
%%
\ProvidesFile{svgnam.def}
 [2016/05/11 v2.12 Predefined colors according to SVG 1.1 (UK)]
%%
%% ----------------------------------------------------------------
%% Copyright (C) 2003-2016 by Dr. Uwe Kern <xcolor at ukern dot de>
%% ----------------------------------------------------------------
%%
\def\colornameprefix{XC@}
\preparecolorset{rgb}{}{}{%
AliceBlue,.94,.972,1;%
AntiqueWhite,.98,.92,.844;%
YellowGreen,.604,.804,.196}
\endinput
%%
%% End of file
`
	got := make(map[string]color.Color)
	colorNamesFrom(&colorReader{}, bytes.NewReader([]byte(raw)), "file.def", &got)
	want := map[string]color.Color{
		"AliceBlue":    color.RGBA{R: 240, G: 248, B: 248, A: 255},
		"AntiqueWhite": color.RGBA{R: 250, G: 235, B: 235, A: 255},
		"YellowGreen":  color.RGBA{R: 154, G: 205, B: 205, A: 255},
	}

	if !reflect.DeepEqual(got, want) {
		t.Fatalf("invalid color names map:\ngot= %+v\nwant= %+v", got, want)
	}
}

func TestColorNames(t *testing.T) {
	ktx := kpath.New()
	names := newColorNames(ktx, &colorReader{})

	for _, tc := range []struct {
		name string
		want color.Color
	}{
		// from xcolor.sty.
		{
			name: "blue",
			want: color.RGBA{B: 255, A: 255},
		},
		{
			name: "cyan",
			want: color.CMYK{C: 255},
		},
		{
			name: "magenta",
			want: color.CMYK{M: 255},
		},
		{
			name: "darkgray",
			want: color.Gray{Y: 64},
		},
		{
			name: "gray",
			want: color.Gray{Y: 128},
		},
		// from dvipsnam.def
		{
			name: "BurntOrange",
			want: color.CMYK{M: 130, Y: 255},
		},
		// from svgnam.def
		{
			name: "YellowGreen",
			want: color.RGBA{R: 154, G: 205, B: 205, A: 255},
		},
		// from x11nam.def
		{
			name: "Purple0",
			want: color.RGBA{R: 160, G: 32, B: 32, A: 255},
		},
	} {
		t.Run(tc.name, func(t *testing.T) {
			got, ok := names[tc.name]
			if !ok {
				t.Fatalf("could not find %q", tc.name)
			}
			if !reflect.DeepEqual(got, tc.want) {
				t.Fatalf("invalid color:\ngot= %+v\nwant=%+v", got, tc.want)
			}
		})
	}
}
