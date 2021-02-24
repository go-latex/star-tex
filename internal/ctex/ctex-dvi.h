// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef CTEX_CAPI_DVI_H
#define CTEX_CAPI_DVI_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include "ctex-consts.h"
#include "ctex-types.h"

#include <stdio.h>

typedef int dvi_index;
typedef struct {
  integer total_pages;
  integer dvi_offset;
  integer dvi_gone;

  scaled dvi_h;
  scaled dvi_v;

  FILE *dvi_file;

  uint8_t dvi_buf[dvi_buf_size + 1];
  dvi_index half_buf;
  dvi_index dvi_limit;
  dvi_index dvi_ptr;

  internal_font_number dvi_f;
} ctex_dvi_t;

void ctex_dvi_init(ctex_dvi_t *self);

void ctex_dvi_add_page(ctex_dvi_t *self);

integer ctex_dvi_pages(ctex_dvi_t *self);

integer ctex_dvi_offset(ctex_dvi_t *self);

integer ctex_dvi_gone(ctex_dvi_t *self);

void ctex_dvi_flush(ctex_dvi_t *self);

void ctex_dvi_wU8(ctex_dvi_t *self, uint8_t v);

void ctex_dvi_swap(ctex_dvi_t *self);

void ctex_dvi_write_dvi(ctex_dvi_t *self, dvi_index a, dvi_index b);

void ctex_dvi_four(ctex_dvi_t *self, integer x);

void ctex_dvi_pop(ctex_dvi_t *self, integer l);

integer ctex_dvi_pos(ctex_dvi_t *self);

integer ctex_dvi_cap(ctex_dvi_t *self);

void ctex_dvi_set_font(ctex_dvi_t *self, internal_font_number f);

internal_font_number ctex_dvi_get_font(ctex_dvi_t *self);

void ctex_dvi_set_h(ctex_dvi_t *self, scaled h);

void ctex_dvi_set_v(ctex_dvi_t *self, scaled v);

scaled ctex_dvi_get_h(ctex_dvi_t *self);

scaled ctex_dvi_get_v(ctex_dvi_t *self);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CTEX_CAPI_DVI_H */
