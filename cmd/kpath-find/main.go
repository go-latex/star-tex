// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Command kpath-find finds files in a TeX Directory Structure.
package main

import (
	"flag"
	"fmt"
	"io/fs"
	"log"
	"os"

	"star-tex.org/x/tex/internal/tds"
	"star-tex.org/x/tex/kpath"
)

func main() {
	log.SetPrefix("kpath-find: ")
	log.SetFlags(0)

	var (
		texmf = flag.String("texmf", "", "path to TEXMF distribution")
		all   = flag.Bool("all", false, "display all matches")
	)

	flag.Parse()

	if flag.NArg() <= 0 {
		flag.Usage()
		log.Fatalf("missing input file name")
	}

	if *texmf == "" {
	loop:
		for _, env := range []string{"TEXMF", "TEXMFROOT", "TEXMFDIST", "TEXMFHOME"} {
			v := os.Getenv(env)
			if v != "" {
				*texmf = v
				break loop
			}
		}
	}

	dir := *texmf
	xmain(flag.Arg(0), dir, *all)
}

func xmain(name, dbdir string, all bool) {
	var db fs.FS
	switch dbdir {
	case "":
		db = tds.FS
	default:
		db = os.DirFS(dbdir)
	}
	fnames, err := process(name, db, all)
	if err != nil {
		log.Fatal(err)
	}
	for _, fname := range fnames {
		fmt.Printf("%s\n", fname)
	}
}

func process(name string, fsys fs.FS, all bool) ([]string, error) {
	var (
		ctx kpath.Context
		err error
	)

	ctx, err = kpath.NewFromFS(fsys)
	if err != nil {
		return nil, fmt.Errorf("could not create kpath context: %w", err)
	}

	if all {
		return ctx.FindAll(name)
	}

	fname, err := ctx.Find(name)
	return []string{fname}, err
}
