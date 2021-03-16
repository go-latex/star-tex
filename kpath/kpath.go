// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Package kpath provides tools to locate TeX related files.
//
// It loosely mimicks Kpathsea, as described in:
//  - https://texdoc.org/serve/kpathsea/0
package kpath // import "star-tex.org/x/tex/kpath"

import (
	"fmt"
	"io"
	stdpath "path"
	"strings"
)

// Context holds state to efficiently search for files in a TDS
// (TeX Directory Structure), as described in:
//  - http://tug.org/tds/tds.pdf
type Context struct {
	exts strset              // known common suffices
	db   map[string][]string // db of filename->dirs
}

func (ctx *Context) init() {
	if ctx.exts.db == nil {
		ctx.exts = strsets["tex"]
	}
	if ctx.db == nil {
		ctx.db = make(map[string][]string)
	}
}

// func New(root string) Context {
// 	ctx := Context{}
// 	ctx.init()
// 	return ctx
// }
//
// // NewFromDB creates a kpath search from a TeX .cnf configuration file.
// func NewFromConfig(cfg io.Reader) (Context, error) {
// 	ctx, err := parseConfig(cfg)
// 	if err != nil {
// 		return Context{}, fmt.Errorf("kpath: could not parse config: %w", err)
// 	}
//
// 	ctx.init()
// 	return ctx, nil
// }

// NewFromDB creates a kpath search from a TeX ls-R db file.
func NewFromDB(r io.Reader) (Context, error) {
	dir := "/"
	if f, ok := r.(interface{ Name() string }); ok {
		dir = stdpath.Dir(f.Name())
	}
	ctx, err := parseDB(dir, r)
	if err != nil {
		return Context{}, fmt.Errorf("kpath: could not parse db file: %w", err)
	}

	ctx.init()
	return ctx, nil
}

// Find returns the full path to the named file if it could be found within the
// TeXMF distribution system.
// Find returns an error if no file or more than one file were found.
func (ctx Context) Find(name string) (string, error) {
	names, err := ctx.FindAll(name)
	if err != nil {
		return "", err
	}

	switch n := len(names); n {
	case 1:
		return names[0], nil
	case 0:
		return "", fmt.Errorf("kpath: could not find a match for %q", name)
	default:
		return "", fmt.Errorf("kpath: too many hits for file %q (n=%d)", name, n)
	}
}

// FindAll returns the full path to all the files matching name that could be
// found within the TeXMF distribution system.
// Find returns an error if no file was found.
func (ctx Context) FindAll(name string) ([]string, error) {
	// TODO(sbinet): handle (all) standard exts.
	// TODO(sbinet): handle multi-root TEXMFs
	// FIXME(sbinet): normalize all paths to use UNIX path separator ?

	orig := name
	name = strings.Replace(name, "\\", "/", -1)
	var (
		subdir = strings.Contains(name, "/")
		ext    = stdpath.Ext(name)
	)
	switch ext {
	case "":
		// try some extensions.
		for _, ext := range ctx.exts.ks {
			names, ok := ctx.lookup(name+ext, subdir)
			if ok {
				return names, nil
			}
		}

		names, ok := ctx.lookup(name, subdir)
		if ok {
			return names, nil
		}

	default:

		if !ctx.exts.has(ext) {
			for _, ext := range ctx.exts.ks {
				names, ok := ctx.lookup(name+ext, subdir)
				if ok {
					return names, nil
				}
			}
		}

		names, ok := ctx.lookup(name, subdir)
		if ok {
			return names, nil
		}
	}

	return nil, fmt.Errorf("kpath: could not find file %q", orig)
}

func (s Context) lookup(name string, subdir bool) ([]string, bool) {
	if !subdir {
		names, ok := s.db[name]
		return names, ok
	}

	var (
		ok    = false
		names = make([]string, 0, 16)
	)
	for _, vs := range s.db {
		for _, v := range vs {
			if !strings.HasSuffix(v, name) {
				continue
			}
			names = append(names, v)
			ok = true
		}
	}

	return names, ok
}
