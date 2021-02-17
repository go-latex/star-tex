// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package ctex

//
import "C"
import (
	"bytes"
	"log"
	"os"

	"git.sr.ht/~sbinet/star-tex/tfm"
)

//export cgo_load_tfm_file
func cgo_load_tfm_file(name *C.char) C.int {
	fname := C.GoString(name)
	raw, err := os.ReadFile(fname)
	if err != nil {
		log.Printf("::: could not read TFM file [%s]: %+v", fname, err)
		return -1
	}
	fnt, err := tfm.Parse(bytes.NewReader(raw))
	if err != nil {
		log.Printf("::: could not parse TFM file [%s]: %+v", fname, err)
		return -1
	}

	return C.int(fnt.NumGlyphs())
}
