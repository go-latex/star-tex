// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Package ctex provides CGo bindings to a C implementation of TeX.
package ctex // import "git.sr.ht/~sbinet/star-tex/internal/ctex"

// #include "ctex-api.h"
//
// #include <stdlib.h>
// #include <string.h>
//
// #cgo !windows LDFLAGS: -lm
import "C"

import (
	"embed"
	"fmt"
	"io"
	"io/ioutil"
	"os"
	"path/filepath"
	"unsafe"
)

//go:embed tex/tex.pool tex/plain.tex tex/hyphen.tex
//go:embed tfm/*.tfm
var bundle embed.FS

type Context struct {
	ctx *C.ctex_t

	search string    // search dir for TeX engine.
	work   string    // work dir for TeX engine.
	stderr io.Writer // stderr is where the C-TeX engine logs errors.
}

func New(stderr io.Writer) Context {
	root, err := unpack()
	if err != nil {
		panic(fmt.Errorf("could not create work dir: %+v", err))
	}
	work := filepath.Join(root, "work")

	ctx := C.ctex_new_context()
	return Context{
		ctx:    ctx,
		search: root,
		work:   work,
		stderr: stderr,
	}
}

func (ctx Context) Free() {
	C.ctex_del_context(&ctx.ctx)

	_ = os.RemoveAll(ctx.work)
}

func (ctx *Context) Process(dvi io.Writer, f io.Reader) error {

	tmp, err := ioutil.TempDir("", "go-ctex-")
	if err != nil {
		return fmt.Errorf("could not create tmp dir: %w", err)
	}
	defer os.RemoveAll(tmp)

	in, err := os.Create(filepath.Join(tmp, "input.tex"))
	if err != nil {
		return fmt.Errorf("could not create input TeX document: %w", err)
	}
	defer in.Close()

	_, err = io.Copy(in, f)
	if err != nil {
		return fmt.Errorf("could not fill input TeX document: %w", err)
	}

	c_name := C.CString(in.Name())
	defer C.free(unsafe.Pointer(c_name))

	oname := filepath.Join(tmp, "out.dvi")
	c_dvi := C.CString(oname)
	defer C.free(unsafe.Pointer(c_dvi))

	c_search := C.CString(ctx.search)
	defer C.free(unsafe.Pointer(c_search))

	c_work := C.CString(ctx.work)
	defer C.free(unsafe.Pointer(c_work))

	ename := filepath.Join(tmp, "err.log")
	c_cerr := C.CString(ename)
	defer C.free(unsafe.Pointer(c_cerr))

	defer func() {
		if err == nil {
			return
		}
		raw, werr := ioutil.ReadFile(ename)
		if werr != nil {
			return
		}
		if len(raw) == 0 {
			return
		}
		_, _ = ctx.stderr.Write(raw)
		fmt.Fprintf(ctx.stderr, "\n")
	}()

	// update "kpath"-like global variables.
	// TODO(sbinet): get rid of these globals.
	g_ipath = ctx.search
	g_opath = ctx.work
	defer func() {
		g_ipath = ""
		g_opath = ""
	}()

	o := C.ctex_context_typeset(
		ctx.ctx,
		c_name, c_dvi,
		c_search, c_work,
		c_cerr,
	)

	if o != 0 {
		err = fmt.Errorf("could not run TeX engine: rc=%d", int(o))
		return err
	}

	out, err := os.Open(oname)
	if err != nil {
		return fmt.Errorf("could not open output DVI document: %w", err)
	}
	defer out.Close()

	_, err = io.Copy(dvi, out)
	if err != nil {
		return fmt.Errorf("could not produce DVI file: %w", err)
	}

	return nil
}

func unpack() (string, error) {
	tmp, err := ioutil.TempDir("", "star-tex-")
	if err != nil {
		return "", fmt.Errorf("could not create tmp dir: %w", err)
	}
	defer func() {
		if err != nil {
			_ = os.RemoveAll(tmp)
		}
	}()

	work := filepath.Join(tmp, "work")

	err = os.Mkdir(work, 0755)
	if err != nil {
		return "", fmt.Errorf("could not create work dir: %w", err)
	}

	err = os.Mkdir(filepath.Join(tmp, "tex"), 0755)
	if err != nil {
		return "", fmt.Errorf("could not create tex dir: %w", err)
	}

	err = os.Mkdir(filepath.Join(tmp, "tfm"), 0755)
	if err != nil {
		return "", fmt.Errorf("could not create tfm dir: %w", err)
	}

	for _, name := range []string{
		"tex/tex.pool",
		"tex/plain.tex",
		"tex/hyphen.tex",
		"tfm/blackcx.tfm",
		"tfm/black.tfm",
		"tfm/cmb10.tfm",
		"tfm/cmbsy10.tfm",
		"tfm/cmbx10.tfm",
		"tfm/cmbx12.tfm",
		"tfm/cmbx5.tfm",
		"tfm/cmbx6.tfm",
		"tfm/cmbx7.tfm",
		"tfm/cmbx8.tfm",
		"tfm/cmbx9.tfm",
		"tfm/cmbxsl10.tfm",
		"tfm/cmbxti10.tfm",
		"tfm/cmcsc10.tfm",
		"tfm/cmdunh10.tfm",
		"tfm/cmex10.tfm",
		"tfm/cmex9.tfm",
		"tfm/cmff10.tfm",
		"tfm/cmfi10.tfm",
		"tfm/cmfib8.tfm",
		"tfm/cminch.tfm",
		"tfm/cmitt10.tfm",
		"tfm/cmman.tfm",
		"tfm/cmmi10.tfm",
		"tfm/cmmi12.tfm",
		"tfm/cmmi5.tfm",
		"tfm/cmmi6.tfm",
		"tfm/cmmi7.tfm",
		"tfm/cmmi8.tfm",
		"tfm/cmmi9.tfm",
		"tfm/cmmib10.tfm",
		"tfm/cmr10.tfm",
		"tfm/cmr12.tfm",
		"tfm/cmr17.tfm",
		"tfm/cmr5.tfm",
		"tfm/cmr6.tfm",
		"tfm/cmr7.tfm",
		"tfm/cmr8.tfm",
		"tfm/cmr9.tfm",
		"tfm/cmsl10.tfm",
		"tfm/cmsl12.tfm",
		"tfm/cmsl8.tfm",
		"tfm/cmsl9.tfm",
		"tfm/cmsltt10.tfm",
		"tfm/cmss10.tfm",
		"tfm/cmss12.tfm",
		"tfm/cmss17.tfm",
		"tfm/cmss8.tfm",
		"tfm/cmss9.tfm",
		"tfm/cmssbx10.tfm",
		"tfm/cmssdc10.tfm",
		"tfm/cmssi10.tfm",
		"tfm/cmssi12.tfm",
		"tfm/cmssi17.tfm",
		"tfm/cmssi8.tfm",
		"tfm/cmssi9.tfm",
		"tfm/cmssq8.tfm",
		"tfm/cmssqi8.tfm",
		"tfm/cmsy10.tfm",
		"tfm/cmsy5.tfm",
		"tfm/cmsy6.tfm",
		"tfm/cmsy7.tfm",
		"tfm/cmsy8.tfm",
		"tfm/cmsy9.tfm",
		"tfm/cmtcsc10.tfm",
		"tfm/cmtex10.tfm",
		"tfm/cmtex8.tfm",
		"tfm/cmtex9.tfm",
		"tfm/cmti10.tfm",
		"tfm/cmti12.tfm",
		"tfm/cmti7.tfm",
		"tfm/cmti8.tfm",
		"tfm/cmti9.tfm",
		"tfm/cmtt10.tfm",
		"tfm/cmtt12.tfm",
		"tfm/cmtt8.tfm",
		"tfm/cmtt9.tfm",
		"tfm/cmu10.tfm",
		"tfm/cmvtt10.tfm",
		"tfm/graycx.tfm",
		"tfm/grayimagen3.tfm",
		"tfm/gray.tfm",
		"tfm/logo10.tfm",
		"tfm/logo8.tfm",
		"tfm/logo9.tfm",
		"tfm/logobf10.tfm",
		"tfm/logod10.tfm",
		"tfm/logosl10.tfm",
		"tfm/logosl8.tfm",
		"tfm/logosl9.tfm",
		"tfm/manfnt.tfm",
		"tfm/oneone.tfm",
		"tfm/slantcx4.tfm",
		"tfm/slantcx6.tfm",
		"tfm/slantlj4.tfm",
		"tfm/slantlj6.tfm",
	} {
		err = unpackFile(tmp, name)
		if err != nil {
			return "", fmt.Errorf("could not unpack %q: %w", name, err)
		}
	}

	return tmp, nil
}

func unpackFile(root, name string) error {
	f, err := bundle.Open(name)
	if err != nil {
		return err
	}
	defer f.Close()

	o, err := os.Create(filepath.Join(root, name))
	if err != nil {
		return fmt.Errorf("could not create output bundle file %q: %w", name, err)
	}
	defer o.Close()

	_, err = io.Copy(o, f)
	if err != nil {
		return fmt.Errorf("could not unpack bundle file %q: %w", name, err)
	}

	err = o.Close()
	if err != nil {
		return fmt.Errorf("could not save bundle file %q: %w", name, err)
	}

	return nil
}
