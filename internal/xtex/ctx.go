// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package xtex

import (
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
)

func New(stdout io.WriteCloser, stdin io.ReadCloser) *Context {
	return &Context{
		stdin:  stdin,
		stdout: stdout,
	}
}

func (ctx *Context) Process(dvi io.WriteCloser, f io.Reader, jobname string) (err error) {
	tmp, err := os.MkdirTemp("", "go-xtex-")
	if err != nil {
		return fmt.Errorf("could not create tmp dir: %w", err)
	}
	defer os.RemoveAll(tmp)

	dir, err := os.Getwd()
	if err != nil {
		return fmt.Errorf("could not retrieve current working directory: %w", err)
	}
	defer os.Chdir(dir)

	err = os.Chdir(tmp)
	if err != nil {
		return fmt.Errorf("could not move to tmp dir: %w", err)
	}

	tex, err := os.Create(filepath.Join(tmp, jobname+".tex"))
	if err != nil {
		return fmt.Errorf("could not create input TeX document: %w", err)
	}
	defer tex.Close()

	fmt.Fprintf(tex, "\\nonstopmode\n\\input plain\n")

	_, err = io.Copy(tex, f)
	if err != nil {
		return fmt.Errorf("could not fill input TeX document: %w", err)
	}

	fmt.Fprintf(tex, "\n\\end")

	err = tex.Close()
	if err != nil {
		return fmt.Errorf("could not save input TeX document: %w", err)
	}

	ctx.dviFile.ioFile = &ioFile{
		eof:           true,
		erstat:        0,
		componentSize: 1,
		name:          "out.dvi",
		out:           dvi,
	}

	stdin := ctx.stdin
	defer func() {
		ctx.stdout.Write([]byte("\n"))

		ctx.stdin = stdin
		e := recover()
		if e != nil {
			err = e.(error)
		}
	}()

	ctx.stdin = io.NopCloser(strings.NewReader(`\input ` + jobname))
	ctx.main()

	return nil
}
