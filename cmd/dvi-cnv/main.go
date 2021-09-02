// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Command dvi-cnv converts a DVI document into a (set of) PNG or PDF file(s).
package main // import "star-tex.org/x/tex/cmd/dvi-cnv"

import (
	"flag"
	"fmt"
	"io"
	"log"
	"os"

	"star-tex.org/x/tex/dvi"
	"star-tex.org/x/tex/kpath"
)

func main() {
	log.SetPrefix("dvi-cnv: ")
	log.SetFlags(0)

	var (
		texmf   = flag.String("texmf", "", "path to TexMF root")
		verbose = flag.Bool("v", false, "enable verbose mode")
		oname   = flag.String("o", "", "path to output file name")
	)

	flag.Parse()

	if flag.NArg() < 1 {
		flag.Usage()
		log.Fatalf("missing DVI input file")
	}

	stdout := io.Discard
	if *verbose {
		stdout = log.Writer()
	}

	if *oname == "" {
		*oname = "out.png"
	}

	xmain(stdout, *oname, flag.Arg(0), *texmf)
}

func xmain(stdout io.Writer, oname, fname, texmf string) {
	f, err := os.Open(fname)
	if err != nil {
		log.Fatalf("could not open DVI file %q: %+v", fname, err)
	}
	defer f.Close()

	ctx := kpath.New()
	if texmf != "" {
		ctx, err = kpath.NewFromFS(os.DirFS(texmf))
		if err != nil {
			log.Fatalf("could not create kpath context: %+v", err)
		}
	}

	err = interp(ctx, stdout, oname, f)
	if err != nil {
		log.Fatalf("could not process DVI file %q: %+v", fname, err)
	}
}

func interp(ctx kpath.Context, stdout io.Writer, oname string, r io.Reader) error {
	renderer := newRenderer(ctx, oname)
	vm := dvi.NewMachine(
		dvi.WithContext(ctx),
		dvi.WithLogOutput(stdout),
		dvi.WithRenderer(renderer),
		dvi.WithHandlers(dvi.NewColorHandler(ctx)),
		dvi.WithOffsetX(0),
		dvi.WithOffsetY(0),
	)

	raw, err := io.ReadAll(r)
	if err != nil {
		return fmt.Errorf("could not read DVI program file: %w", err)
	}

	prog, err := dvi.Compile(raw)
	if err != nil {
		return fmt.Errorf("could not compile DVI program: %w", err)
	}

	err = vm.Run(prog)
	if err != nil {
		return fmt.Errorf("could not interpret DVI program: %w", err)
	}

	if renderer.err != nil {
		return fmt.Errorf("could not render DVI program: %w", renderer.err)
	}

	return nil
}
