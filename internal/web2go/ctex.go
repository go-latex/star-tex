// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"log"
	"os"
	"os/exec"
)

func (state *State) moveToC() {
	buf := new(bytes.Buffer)
	cmd := exec.Command("python", "-c", pycode)
	cmd.Stdout = buf
	cmd.Stderr = os.Stderr

	err := cmd.Run()
	if err != nil {
		log.Fatalf("error: %v\ncould not retrieve methods offsets: %+v", buf, err)
	}

	type Offset struct {
		Beg int `json:"beg"`
		End int `json:"end"`
	}

	var methods []struct {
		Name string `json:"name"`
		Decl Offset `json:"decl"`
		Impl Offset `json:"impl"`
	}

	err = json.NewDecoder(buf).Decode(&methods)
	if err != nil {
		log.Fatalf("could not decode methods offsets: %+v", err)
	}

	hdr, err := os.ReadFile(state.texHdr)
	if err != nil {
		log.Fatalf("could not read tex C++ header: %+v", err)
	}
	src, err := os.ReadFile(state.texCxx)
	if err != nil {
		log.Fatalf("could not read tex C++ impl: %+v", err)
	}

	fhdr, err := os.Create("./internal/ctex/ctex-methods.h")
	if err != nil {
		log.Fatalf("could not create methods decl file: %+v", err)
	}
	defer fhdr.Close()

	fmt.Fprintf(fhdr, `// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef CTEX_METHODS_H
#define CTEX_METHODS_H 1

#include "ctex.h"

#ifdef __cplusplus
extern "C" {
#endif

`)

	fsrc, err := os.Create("./internal/ctex/ctex-methods.c")
	if err != nil {
		log.Fatalf("could not create methods impl file: %+v", err)
	}
	defer fsrc.Close()

	fmt.Fprintf(fsrc, `// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "ctex-io.h"
#include "ctex-methods.h"

#define true  1
#define false 0

`)

	for _, meth := range methods {
		decl := hdr[meth.Decl.Beg:meth.Decl.End]
		impl := src[meth.Impl.Beg:meth.Impl.End]

		impl = bytes.Replace(
			impl,
			[]byte("tex::"+meth.Name+"("),
			[]byte(meth.Name+"("),
			1,
		)
		impl = bytes.Replace(
			impl,
			[]byte(" or "),
			[]byte(" || "),
			-1,
		)
		impl = bytes.Replace(
			impl,
			[]byte(" and "),
			[]byte(" && "),
			-1,
		)
		impl = bytes.Replace(
			impl,
			[]byte("nullptr"),
			[]byte("NULL"),
			-1,
		)

		fmt.Fprintf(fhdr, "%s;\n", decl)
		fmt.Fprintf(fsrc, "%s\n\n", impl)
	}

	fmt.Fprintf(fhdr, `

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CTEX_METHODS_H */
`)

	err = fhdr.Close()
	if err != nil {
		log.Fatalf("could not save methods decl file: %+v", err)
	}

	err = fsrc.Close()
	if err != nil {
		log.Fatalf("could not save methods impl file: %+v", err)
	}
}

const pycode = `
import json
import clang.cindex

import collections
odict = collections.OrderedDict

def get_diag_info(diag):
    return { 'severity' : diag.severity,
             'location' : diag.location,
             'spelling' : diag.spelling,
             'ranges' : diag.ranges,
             'fixits' : diag.fixits }

def get_cursor_id(cursor, cursor_list = []):
    if not opts.showIDs:
        return None

    if cursor is None:
        return None

    # FIXME: This is really slow. It would be nice if the index API exposed
    # something that let us hash cursors.
    for i,c in enumerate(cursor_list):
        if cursor == c:
            return i
    cursor_list.append(cursor)
    return len(cursor_list) - 1

def show_node(node, children):
    return { 'id' : get_cursor_id(node),
             'kind' : node.kind,
             'usr' : node.get_usr(),
             'spelling' : node.spelling,
             'location' : node.location,
             'extent.start' : node.extent.start.offset,
             'extent.end' : node.extent.end.offset,
             'is_definition' : node.is_definition(),
             'definition id' : get_cursor_id(node.get_definition()),
             'children' : children }


mdecls = []
mimpls = []
def get_info(node, depth=0):
    if opts.maxDepth is not None and depth >= opts.maxDepth:
        children = None
    else:
        children = [get_info(c, depth+1)
                    for c in node.get_children()]
    if node.kind == clang.cindex.CursorKind.CXX_METHOD:
        loc = node.location.file.name
        if loc.endswith("tex.hpp"):
            mdecls.append(node)
        if loc.endswith("tex.cpp"):
            mimpls.append(node)
        pass
    return show_node(node, children)

def main(fname):
    from clang.cindex import Index
    from pprint import pprint

    global opts
    opts = collections.namedtuple("Opts", ["showIDs", "maxDepth"])
    opts.showIDs = False
    opts.maxDepth = None

    index = Index.create()
    tu = index.parse(None, [fname])
    if not tu:
        raise RuntimeError("unable to load input")

    _ = get_info(tu.cursor)

    methods = odict()
    for m in mdecls:
        try:
            o = methods[m.spelling]
        except KeyError:
            methods[m.spelling] = {
                    "name": m.spelling,
                    "impl": {"beg": 0, "end": 0},
                    "decl": {"beg": 0, "end": 0},
                    }
            
            o = methods[m.spelling]
            pass
        o["decl"]["beg"] = m.extent.start.offset
        o["decl"]["end"] = m.extent.end.offset
        pass

    for m in mimpls:
        try:
            o = methods[m.spelling]
        except KeyError:
            methods[m.spelling] = {
                    "name": m.spelling,
                    "impl": {"beg": 0, "end": 0},
                    "decl": {"beg": 0, "end": 0},
                    }
            
            o = methods[m.spelling]
            pass
        o["impl"]["beg"] = m.extent.start.offset
        o["impl"]["end"] = m.extent.end.offset
        pass

    print("%s" % (json.dumps([methods[k] for k in methods]),))

if __name__ == '__main__':
    main("./internal/ctex/tex.cpp")
`
