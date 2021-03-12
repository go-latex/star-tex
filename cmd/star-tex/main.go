// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Command star-tex compiles TeX documents.
package main // import "git.sr.ht/~sbinet/star-tex/cmd/star-tex"

import (
	"errors"
	"flag"
	"fmt"
	"io"
	"log"
	"os"
	"path/filepath"
	"strings"

	tex "git.sr.ht/~sbinet/star-tex"
)

var (
	fset = flag.NewFlagSet("star-tex", flag.ContinueOnError)

	usage = `Usage: star-tex [options] FILE.tex [FILE.dvi]

ex:
 $> star-tex ./testdata/hello.tex
 $> star-tex ./testdata/hello.tex ./out.dvi

options:
`
)

func main() {
	os.Exit(xmain(os.Stdout, os.Stderr, os.Args[1:]))
}

func xmain(stdout, stderr io.Writer, args []string) int {
	msg := log.New(stderr, "star-tex: ", 0)

	fset.Usage = func() {
		fmt.Fprintf(stderr, usage)
		fset.PrintDefaults()
	}

	err := fset.Parse(args)
	if err != nil {
		if errors.Is(err, flag.ErrHelp) {
			return 0
		}
		msg.Printf("could not parse args %q: %+v", args, err)
		return 1
	}

	if fset.NArg() < 1 {
		msg.Printf("missing file argument")
		fset.Usage()
		return 1
	}

	f, err := os.Open(args[0])
	if err != nil {
		msg.Printf("could not open input TeX file: %+v", err)
		return 1
	}
	defer f.Close()

	oname := strings.Replace(filepath.Base(f.Name()), ".tex", ".dvi", 1)
	if len(args) > 1 {
		oname = args[1]
	}

	o, err := os.Create(oname)
	if err != nil {
		msg.Printf("could not open output DVI file: %+v", err)
		return 1
	}
	defer o.Close()

	err = process(o, f, os.Stderr)
	if err != nil {
		msg.Printf("could not run star-tex: %+v", err)
		return 1
	}

	err = o.Close()
	if err != nil {
		msg.Printf("could not close output DVI file: %+v", err)
		return 1
	}

	return 0
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
