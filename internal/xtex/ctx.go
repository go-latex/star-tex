// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package xtex

import (
	"fmt"
	"io"
	"io/ioutil"
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

func (ctx *Context) Process(dvi io.Writer, f io.Reader) (err error) {
	tmp, err := ioutil.TempDir("", "go-xtex-")
	if err != nil {
		return fmt.Errorf("could not create tmp dir: %w", err)
	}
	defer os.RemoveAll(tmp)

	tex, err := os.Create(filepath.Join(tmp, "input.tex"))
	if err != nil {
		return fmt.Errorf("could not create input TeX document: %w", err)
	}
	defer tex.Close()

	_, err = io.Copy(tex, f)
	if err != nil {
		return fmt.Errorf("could not fill input TeX document: %w", err)
	}

	err = tex.Close()
	if err != nil {
		return fmt.Errorf("could not save input TeX document: %w", err)
	}

	cmd := strings.NewReader(fmt.Sprintf(
		` \nonstopmode \input plain \input %s \end`,
		strings.Replace(tex.Name(), string(os.PathSeparator), "/", -1),
	))

	ctx.dviFile.ioFile = &ioFile{
		eof:           true,
		erstat:        0,
		componentSize: 1,
		name:          "out.dvi",
		out:           &nopWriteCloser{dvi},
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

	ctx.stdin = io.NopCloser(cmd)
	ctx.main()

	return nil
}

type nopWriteCloser struct {
	io.Writer
}

func (*nopWriteCloser) Close() error { return nil }
