// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef CTEX_CAPI_DVI_H
#define CTEX_CAPI_DVI_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "ctex-capi-consts.h"
#include "ctex-capi-types.h"

typedef int dvi_index;
typedef struct {
	integer total_pages;
	integer dvi_offset;
	integer dvi_gone;

	scaled dvi_h;
	scaled dvi_v;

	FILE *dvi_file;

	uint8_t dvi_buf[dvi_buf_size+1];
	dvi_index half_buf;
	dvi_index dvi_limit;
	dvi_index dvi_ptr;

	internal_font_number dvi_f;
} ctex_dvi_t;

void
ctex_dvi_init(ctex_dvi_t *dvi_mgr);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CTEX_CAPI_DVI_H */

