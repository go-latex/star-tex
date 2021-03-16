// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// tfm2pl converts a TFM file to human-readable property list file or standard output.
//
// Usage: tfm2pl [options] file.tfm [file.pl]
//
// ex:
//  $> tfm2pl testdata/simple.tfm
//  $> tfm2pl testdata/simple.tfm out.pl
package main // import "star-tex.org/x/tex/cmd/tfm2pl"

import (
	"flag"
	"fmt"
	"io"
	"log"
	"os"

	"star-tex.org/x/tex/tfm"
)

func init() {
	log.SetPrefix("tfm2pl: ")
	log.SetFlags(0)

	flag.Usage = func() {
		fmt.Fprintf(
			os.Stderr,
			`Usage: tfm2pl [options] file.tfm [file.pl]

tfm2pl converts a TFM file to human-readable property list file or standard output.

ex:
 $> tfm2pl testdata/simple.tfm
 $> tfm2pl testdata/simple.tfm out.pl

options:
`,
		)
		flag.PrintDefaults()
	}
}

func main() {
	flag.Parse()

	if flag.NArg() < 1 {
		flag.Usage()
		log.Fatalf("missing path to input TFM file")
	}
	xmain(flag.Args())
}

func xmain(args []string) {

	fname := args[0]

	f, err := os.Open(fname)
	if err != nil {
		log.Fatalf("could not open file %q: %+v", fname, err)
	}
	defer f.Close()

	var (
		o     io.Writer = os.Stdout
		oname           = ""
	)

	if len(args) > 1 {
		oname = args[1]
		pl, err := os.Create(oname)
		if err != nil {
			log.Fatalf("could not create output PL file %q: %+v", oname, err)
		}
		defer func() {
			err := pl.Close()
			if err != nil {
				log.Fatalf("could not close output PL file %q: %+v", oname, err)
			}
		}()
		o = pl
	}

	err = process(o, f)
	if err != nil {
		log.Fatalf("could not process TFM file %q: %+v", fname, err)
	}
}

func process(w io.Writer, r io.Reader) error {
	fnt, err := tfm.Parse(r)
	if err != nil {
		return fmt.Errorf("could not parse TFM file: %w", err)
	}

	txt, err := fnt.MarshalText()
	if err != nil {
		return fmt.Errorf("could not marshal TFM font to PL: %w", err)
	}

	_, err = w.Write(txt)
	if err != nil {
		return fmt.Errorf("could not write PL text: %w", err)
	}

	return nil
}
