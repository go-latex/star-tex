// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package tex

import (
	"io"

	"star-tex.org/x/tex/internal/xtex"
)

const (
	defaultJobname = "output"
)

// Engine is a TeX engine.
type Engine struct {
	stdin  io.ReadCloser
	stdout io.WriteCloser

	// Jobname used for TeX output.
	// Default is "output".
	Jobname string
}

// NewEngine creates a new TeX engine connected to the provided
// stdin and stdout file descriptors.
func NewEngine(stdout io.Writer, stdin io.Reader) *Engine {
	return &Engine{
		stdout:  writerCloser(stdout),
		stdin:   io.NopCloser(stdin),
		Jobname: defaultJobname,
	}
}

// Process reads the provided TeX document and
// compiles it to the provided writer.
func (engine *Engine) Process(w io.Writer, r io.Reader) error {
	jobname := engine.Jobname
	if jobname == "" {
		jobname = defaultJobname
	}

	ctx := xtex.New(engine.stdout, engine.stdin)
	return ctx.Process(writerCloser(w), r, jobname)
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
