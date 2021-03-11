// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Command kpath-find finds files in a TeX Directory Structure.
package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"path/filepath"

	"git.sr.ht/~sbinet/star-tex/kpath"
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
		if *texmf == "" {
			*texmf = "/usr/share/texmf-dist"
		}
	}

	dbname := filepath.Join(*texmf, "ls-R")
	xmain(flag.Arg(0), dbname, *all)
}

func xmain(name, dbname string, all bool) {
	fnames, err := process(name, dbname, all)
	if err != nil {
		log.Fatal(err)
	}
	for _, fname := range fnames {
		fmt.Printf("%s\n", fname)
	}
}

func process(name, dbname string, all bool) ([]string, error) {
	db, err := os.Open(dbname)
	if err != nil {
		return nil, fmt.Errorf("could not open texmf db %q: %w", dbname, err)
	}
	defer db.Close()

	ctx, err := kpath.NewFromDB(db)
	if err != nil {
		return nil, fmt.Errorf("could not create kpath context: %w", err)
	}

	if all {
		return ctx.FindAll(name)
	}

	fname, err := ctx.Find(name)
	return []string{fname}, err
}
