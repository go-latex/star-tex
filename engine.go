// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package tex

import (
	"io"

	"git.sr.ht/~sbinet/star-tex/internal/xtex"
)

// Engine is a TeX engine.
type Engine struct {
	stdin  io.ReadCloser
	stdout io.WriteCloser
}

// NewEngine creates a new TeX engine connected to the provided
// stdin and stdout file descriptors.
func NewEngine(stdout io.Writer, stdin io.Reader) *Engine {
	return &Engine{
		stdout: writerCloser(stdout),
		stdin:  io.NopCloser(stdin),
	}
}

// Process reads the provided TeX document and
// compiles it to the provided writer.
func (engine *Engine) Process(w io.Writer, r io.Reader) error {
	ctx := xtex.New(engine.stdout, engine.stdin)
	return ctx.Process(writerCloser(w), r)
}

func writerCloser(w io.Writer) io.WriteCloser {
	if w, ok := w.(io.WriteCloser); ok {
		return w
	}
	return nopWriteCloser{w}
}

type nopWriteCloser struct {
	io.Writer
}

func (nopWriteCloser) Close() error { return nil }
