// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package ctex

//#include <string.h>
//#include <stdlib.h>
//#include <stdio.h> /* for FILENAME_MAX */
import "C"

import (
	"os"
	"path/filepath"
	"strings"
	"unsafe"
)

var (
	g_opath string
	g_ipath string
)

//export ctex_kpath_ifind
func ctex_kpath_ifind(fname *C.char) {
	name := C.GoString(fname)
	idx := strings.Index(name, " ")
	if idx > 0 {
		name = name[:idx]
	}
	oname := name

	defer func() {
		c_name := C.CString(oname)
		C.strncpy(fname, c_name, C.FILENAME_MAX-1)
		C.free(unsafe.Pointer(c_name))
	}()

	_, err := os.Lstat(oname)
	if err == nil {
		return
	}

	oname = filepath.Join(g_ipath, name)
	_, err = os.Lstat(oname)
	if err == nil {
		return
	}

	oname = filepath.Join(g_opath, name)
	_, err = os.Lstat(oname)
	if err == nil {
		return
	}

	oname = name
}

//export ctex_kpath_ofind
func ctex_kpath_ofind(fname *C.char) {
	name := C.GoString(fname)
	idx := strings.Index(name, " ")
	if idx > 0 {
		name = name[:idx]
	}
	oname := filepath.Join(g_opath, name)

	c_name := C.CString(oname)
	C.strncpy(fname, c_name, C.FILENAME_MAX-1)
	C.free(unsafe.Pointer(c_name))
}
