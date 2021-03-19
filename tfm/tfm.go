// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Package tfm implements a decoder for TFM (TeX Font Metrics) files.
package tfm // import "star-tex.org/x/tex/tfm"

import (
	"fmt"
)

// Int12_20 is a signed 26.6 fixed-point number.
//
// The integer part ranges from -2048 to 2047, inclusive. The
// fractional part has 20 bits of precision.
type Int12_20 uint32

func (x Int12_20) Float64() float64 {
	v := int32(x)
	return float64(v) / (1 << 20)

	//	const (
	//		signMask = 0b1000_0000_0000_0000_0000_0000_0000_0000
	//		intMask  = 0b0111_1111_1111_0000_0000_0000_0000_0000
	//		fracMask = 0b0000_0000_0000_1111_1111_1111_1111_1111
	//	)
	//
	//	var (
	//		num  = uint32(x)
	//		sign = 1.0
	//	)
	//	if num&signMask == signMask {
	//		num = ^num + 1
	//		sign = -1
	//	}
	//
	//	ip := float64((num & intMask) >> 20)
	//	fp := float64(num&fracMask) / float64(1<<20)
	//	return sign * (ip + fp)
}

// String returns a human-readable representation of a 12.20 fixed-point number.
func (x Int12_20) String() string {
	const (
		shift = 12
		mask  = 1<<shift - 1
	)
	if x >= 0 {
		return fmt.Sprintf("%d:%02d", int32(x>>shift), int32(x&mask))
	}
	x = -x
	if x >= 0 {
		return fmt.Sprintf("-%d:%02d", int32(x>>shift), int32(x&mask))
	}
	return "-2048:00" // The minimum value is -(1<<(12-1)).
}

type glyphKind uint8

const (
	gkInvalid glyphKind = iota
	gkVanilla
	gkLigKern
	gkGlyphList
	gkExtensible
)

func (ck glyphKind) String() string {
	switch ck {
	case gkVanilla:
		return "vanilla"
	case gkLigKern:
		return "ligkern"
	case gkGlyphList:
		return "glyphlist"
	case gkExtensible:
		return "extglyph"
	case gkInvalid:
		return "invalid"
	default:
		return fmt.Sprintf("glyphKind(%d)", int(ck))
	}
}

// GlyphIndex is a glyph index in a Font.
type GlyphIndex int

// glyphInfo provides informations about a glyph.
type glyphInfo struct {
	raw [4]uint8
}

func (g glyphInfo) wd() int {
	return int(g.raw[0])
}

func (g glyphInfo) ht() int {
	return int((g.raw[1] & 0b1111_0000) >> 4)
}

func (g glyphInfo) dp() int {
	return int(g.raw[1] & 0b0000_1111)
}

func (g glyphInfo) ic() int {
	return int((g.raw[2] & 0b1111_1100) >> 2)
}

func (g glyphInfo) kind() (glyphKind, int) {
	i := int(g.raw[3])
	switch g.raw[2] & 0b0000_0011 {
	case 0:
		return gkVanilla, i
	case 1:
		return gkLigKern, i
	case 2:
		return gkGlyphList, i
	case 3:
		return gkExtensible, i
	default:
		return gkInvalid, -i
	}
}

type ligKernCmd struct {
	raw [4]uint8
}

func (lk ligKernCmd) skipByte() bool {
	return lk.raw[0] > 128
}

func (lk ligKernCmd) nextChar() int {
	return int(lk.raw[1])
}

func (lk ligKernCmd) op() ligKernOp {
	if lk.raw[2] < 128 {
		return ligCmd
	}
	return krnCmd
}

type ligKernOp uint8

const (
	lkUknown ligKernOp = iota
	ligCmd
	krnCmd
)

func (lk ligKernOp) String() string {
	switch lk {
	default:
		return "invalid"
	case ligCmd:
		return "LIG"
	case krnCmd:
		return "KRN"
	}
}

type extensible struct {
	raw [4]uint8
}
