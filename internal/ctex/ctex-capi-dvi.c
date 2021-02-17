// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "ctex-capi-dvi.h"

void
ctex_dvi_init(ctex_dvi_t *mgr) {
	mgr->total_pages = 0;
	mgr->dvi_offset = 0;
	mgr->dvi_gone = 0;

	mgr->dvi_h = 0;
	mgr->dvi_v = 0;

	mgr->dvi_file = NULL;

	for (int k = 0; k<dvi_buf_size+1; k++) {
		mgr->dvi_buf[k] = 0;
	}
    mgr->half_buf = dvi_buf_size / 2;
    mgr->dvi_limit = dvi_buf_size;
    mgr->dvi_ptr = 0;
    mgr->dvi_f = 0;
}
