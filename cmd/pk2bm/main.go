// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main // import "star-tex.org/x/tex/cmd/pk2bm"

import (
	"flag"
	"fmt"
	"io"
	"log"
	"os"

	"star-tex.org/x/tex/font/pkf"
)

func main() {
	log.SetPrefix("pk2bm: ")
	log.SetFlags(0)

	var (
		cflag  = flag.String("c", "", "character to display")
		hflag  = flag.Int("H", 0, "height of bitmap")
		wflag  = flag.Int("W", 0, "width of bitmap")
		bitmap = flag.Bool("b", false, "generate a bitmap")
		hexmap = flag.Bool("h", false, "generate a hexmap")
	)

	flag.Parse()

	if *hexmap && *bitmap {
		log.Fatalf("you need to chose either -h or -b")
	}

	f, err := os.Open(flag.Arg(0))
	if err != nil {
		log.Fatalf("could not open PK file: %+v", err)
	}
	defer f.Close()

	err = process(os.Stdout, f, rune((*cflag)[0]), *hflag, *wflag, *bitmap, *hexmap)
	if err != nil {
		log.Fatalf("could not process PK file: %+v", err)
	}
}

func process(o io.Writer, r io.Reader, c rune, h, w int, bitmap, hexmap bool) error {
	f, err := pkf.Parse(r)
	if err != nil {
		return fmt.Errorf("could not parse PK font: %w", err)
	}
	switch {
	case bitmap:
		return f.Bitmap(o, c, h, w)
	case hexmap:
		return f.Hexmap(o, c, h, w)
	default:
		return f.Rawmap(o, c, h, w)
	}
}
