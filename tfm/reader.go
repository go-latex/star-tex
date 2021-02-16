// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package tfm

import (
	"encoding/binary"
	"fmt"
	"io"
)

type reader struct {
	r   io.Reader
	buf []byte
	err error
}

func newReader(r io.Reader) *reader {
	return &reader{
		r:   r,
		buf: make([]byte, 8),
		err: nil,
	}
}

func (r *reader) Read(p []byte) (int, error) {
	return r.r.Read(p)
}

func (r *reader) read(n int) {
	if r.err != nil {
		return
	}
	_, r.err = r.r.Read(r.buf[:n])
}

func (r *reader) readU8() uint8 {
	const n = 1
	r.read(n)
	if r.err != nil {
		return 0
	}
	return uint8(r.buf[0])
}

func (r *reader) readU16() uint16 {
	const n = 2
	r.read(n)
	if r.err != nil {
		return 0
	}
	return binary.BigEndian.Uint16(r.buf[:n])
}

func (r *reader) readU32() uint32 {
	const n = 4
	r.read(n)
	if r.err != nil {
		return 0
	}
	return binary.BigEndian.Uint32(r.buf[:n])
}

func (r *reader) readStr(max int) string {
	if r.err != nil {
		return ""
	}

	n := int(r.readU8())
	if r.err != nil {
		return ""
	}

	if n > max {
		r.err = fmt.Errorf("invalid string size (got=%d, max=%d)", n, max)
		return ""
	}

	raw := r.readN(max - 1)
	return string(raw[:n])
}

func (r *reader) readN(n int) []byte {
	if r.err != nil {
		return nil
	}
	raw := make([]byte, n)
	n, r.err = io.ReadFull(r.r, raw)
	return raw[:n]
}

func (r *reader) readHeader(hdr *fileHeader) error {
	if r.err != nil {
		return r.err
	}
	hdr.lf = r.readU16()
	hdr.lh = r.readU16()
	hdr.bc = r.readU16()
	hdr.ec = r.readU16()
	hdr.nw = r.readU16()
	hdr.nh = r.readU16()
	hdr.nd = r.readU16()
	hdr.ni = r.readU16()
	hdr.nl = r.readU16()
	hdr.nk = r.readU16()
	hdr.ne = r.readU16()
	hdr.np = r.readU16()
	return r.err
}

func (r *reader) readCharInfos(n int) []glyphInfo {
	if r.err != nil {
		return nil
	}
	out := make([]glyphInfo, n)
	for i := range out {
		out[i].raw[0] = r.readU8()
		out[i].raw[1] = r.readU8()
		out[i].raw[2] = r.readU8()
		out[i].raw[3] = r.readU8()
	}
	return out
}

func (r *reader) readFWs(n int) []Int12_20 {
	if r.err != nil {
		return nil
	}
	out := make([]Int12_20, n)
	for i := range out {
		out[i] = Int12_20(r.readU32())
	}
	return out
}

func (r *reader) readLigKerns(n int) []ligKernCmd {
	if r.err != nil {
		return nil
	}
	out := make([]ligKernCmd, n)
	for i := range out {
		out[i].raw[0] = r.readU8()
		out[i].raw[1] = r.readU8()
		out[i].raw[2] = r.readU8()
		out[i].raw[3] = r.readU8()
	}
	return out
}

func (r *reader) readExtens(n int) []extensible {
	if r.err != nil {
		return nil
	}
	out := make([]extensible, n)
	for i := range out {
		out[i].raw[0] = r.readU8()
		out[i].raw[1] = r.readU8()
		out[i].raw[2] = r.readU8()
		out[i].raw[3] = r.readU8()
	}
	return out
}
