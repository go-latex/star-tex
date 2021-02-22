// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"bytes"
	"flag"
	"fmt"
	"log"
	"os"
	"os/exec"
)

func main() {
	log.SetPrefix("web2go: ")
	log.SetFlags(0)

	flag.Parse()

	state := State{
		texHdr: "./internal/ctex/tex.hpp",
		texCxx: "./internal/ctex/tex.cpp",

		fields:  cxxfields,
		methods: cxxmethods,
	}
	state.init()
	state.process()
}

type State struct {
	texHdr string
	texCxx string

	fields  []string
	methods []string
}

func (state *State) init() {
}

func (state *State) process() {
	state.renameFields()
	state.renameMethods()
	state.moveToC()
}

func (state *State) renameFields() {
	const format = "xxx_field_%010d"
	log.Printf("refactoring %d fields...", len(state.fields))
	f, err := os.CreateTemp("", "clang-rename-")
	if err != nil {
		log.Fatalf("could not create tmp YAML file: %+v", err)

	}
	defer os.Remove(f.Name())
	defer f.Close()

	fmt.Fprintf(f, "---\n")
	for i, field := range state.fields {
		mbr := fmt.Sprintf(format, i)
		fmt.Fprintf(
			f,
			"- QualifiedName:  tex::tex::%s\n  NewName:        %s\n",
			field, mbr,
		)
	}

	buf := new(bytes.Buffer)
	cmd := exec.Command(
		"clang-rename",
		"-i",
		"--input="+f.Name(),

		state.texHdr,
		state.texCxx,
	)
	cmd.Stdout = buf
	cmd.Stderr = buf

	err = cmd.Run()
	if err != nil {
		log.Fatalf("error:\n%s\ncould not rename fields: %+v", buf.String(), err)
	}

	for i, field := range state.fields {
		mbr := fmt.Sprintf(format, i)
		sed := fmt.Sprintf("s@%s@ctx->%s@g", mbr, field)
		cmd = exec.Command("sed", "-i", sed, state.texCxx)
		err = cmd.Run()
		if err != nil {
			log.Fatalf("could not migrate field %q: %+v", field, err)
		}
	}

	log.Printf("refactoring %d fields... [done]", len(state.fields))
}

func (state *State) renameMethods() {
	const format = "xxx_method_%010d"
	log.Printf("refactoring %d methods...", len(state.methods))
	f, err := os.CreateTemp("", "clang-rename-")
	if err != nil {
		log.Fatalf("could not create tmp YAML file: %+v", err)

	}
	defer os.Remove(f.Name())
	defer f.Close()

	fmt.Fprintf(f, "---\n")
	for i, field := range state.methods {
		mbr := fmt.Sprintf(format, i)
		fmt.Fprintf(
			f,
			"- QualifiedName:  tex::tex::%s\n  NewName:        %s\n",
			field, mbr,
		)
	}

	buf := new(bytes.Buffer)
	cmd := exec.Command(
		"clang-rename",
		"-i",
		"--input="+f.Name(),

		state.texHdr,
		state.texCxx,
	)
	cmd.Stdout = buf
	cmd.Stderr = buf

	err = cmd.Run()
	if err != nil {
		log.Fatalf("error:\n%s\ncould not rename methods: %+v", buf.String(), err)
	}

	for i, meth := range state.methods {
		mbr := fmt.Sprintf(format, i)
		hdr := fmt.Sprintf("s@%s(@%s(ctex_t *ctx, @g", mbr, meth)
		cmd = exec.Command("sed", "-i", hdr, state.texHdr)
		err = cmd.Run()
		if err != nil {
			log.Fatalf("could not migrate method decl. %q: %+v", meth, err)
		}

		decl := fmt.Sprintf(
			"s@tex::%[1]s(@tex::%[2]s(ctex_t *ctx, @g",
			mbr, meth,
		)
		cmd = exec.Command("sed", "-i", decl, state.texCxx)
		err = cmd.Run()
		if err != nil {
			log.Fatalf("could not migrate method signature %q: %+v", meth, err)
		}

		impl := fmt.Sprintf("s@%s(@%s(ctx, @g", mbr, meth)
		cmd = exec.Command("sed", "-i", impl, state.texCxx)
		err = cmd.Run()
		if err != nil {
			log.Fatalf("could not migrate method impl. %q: %+v", meth, err)
		}
	}

	// fixups.
	cmd = exec.Command("sed", "-i", "s@ctx, )@ctx)@g",
		state.texCxx, state.texHdr,
	)
	err = cmd.Run()
	if err != nil {
		log.Fatalf("could not apply fixups to unary methods: %+v", err)
	}

	log.Printf("refactoring %d methods... [done]", len(state.methods))
}
