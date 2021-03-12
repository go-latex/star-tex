// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Command star-tex compiles TeX documents.
package main // import "git.sr.ht/~sbinet/star-tex/cmd/star-tex"

import (
	"flag"
	"io"
	"log"
	"os"
	"path/filepath"
	"strings"

	tex "git.sr.ht/~sbinet/star-tex"
)

func main() {
	log.SetPrefix("star-tex: ")
	log.SetFlags(0)

	flag.Parse()

	if flag.NArg() < 1 {
		flag.Usage()
		log.Fatalf("missing file arguments")
	}

	xmain(flag.Args())
}

func xmain(args []string) {
	f, err := os.Open(args[0])
	if err != nil {
		log.Fatalf("could not open input TeX file: %+v", err)
	}
	defer f.Close()

	oname := strings.Replace(filepath.Base(f.Name()), ".tex", ".dvi", 1)
	if len(args) > 1 {
		oname = args[1]
	}

	o, err := os.Create(oname)
	if err != nil {
		log.Fatalf("could not open output DVI file: %+v", err)
	}
	defer o.Close()

	err = process(o, f, os.Stderr)
	if err != nil {
		log.Fatalf("could not run star-tex: %+v", err)
	}

	err = o.Close()
	if err != nil {
		log.Fatalf("could not close output DVI file: %+v", err)
	}
}

func process(o io.Writer, f io.Reader, stderr io.Writer) error {
	ctx := tex.NewEngine(stderr, os.Stdin)
	ctx.Jobname = jobNameFrom(o)
	return ctx.Process(o, f)
}

func jobNameFrom(w io.Writer) (job string) {
	o, ok := w.(interface{ Name() string })
	if !ok {
		return job
	}
	job = o.Name()
	job = job[:len(job)-len(filepath.Ext(job))]
	return job
}
