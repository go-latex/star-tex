// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Command dvi-dump displays the content of a DVI file in a human readable
// format or JSON.
package main // import "star-tex.org/x/tex/cmd/dvi-dump"

import (
	"encoding/json"
	"flag"
	"fmt"
	"io"
	"log"
	"os"

	"star-tex.org/x/tex/dvi"
	"star-tex.org/x/tex/kpath"
)

func main() {
	log.SetFlags(0)
	log.SetPrefix("dvi-dump: ")

	var (
		doJSON = flag.Bool("json", false, "enable JSON output")
		texmf  = flag.String("texmf", "", "path to TexMF root")
	)

	flag.Parse()

	if flag.NArg() == 0 {
		flag.Usage()
		log.Fatalf("missing input dvi file")
	}

	xmain(flag.Arg(0), *doJSON, *texmf)
}

func xmain(fname string, doJSON bool, texmf string) {
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

	switch {
	case doJSON:
		err = jsonProcess(f)
	default:
		err = interp(ctx, os.Stdout, f)
	}
	if err != nil {
		log.Fatalf("could not process DVI file %q: %+v", fname, err)
	}
}

func jsonProcess(f *os.File) error {
	w := os.Stdout
	o := json.NewEncoder(w)

	err := dvi.Dump(f, func(cmd dvi.Cmd) error {
		var v struct {
			Cmd  string  `json:"cmd"`
			Args dvi.Cmd `json:"args,omitempty"`
		}
		v.Cmd = cmd.Name()
		v.Args = cmd
		return o.Encode(v)
	})

	if err != nil {
		return fmt.Errorf("could not read DVI file: %w", err)
	}

	return nil
}

func interp(ctx kpath.Context, w io.Writer, f *os.File) error {
	vm := dvi.NewMachine(dvi.WithContext(ctx), dvi.WithLogOutput(w))
	raw, err := io.ReadAll(f)
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

	return nil
}
