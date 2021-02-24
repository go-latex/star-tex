// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "ctex-dvi.h"

#include <stdio.h>

void ctex_dvi_init(ctex_dvi_t *self) {
  self->total_pages = 0;
  self->dvi_offset = 0;
  self->dvi_gone = 0;

  self->dvi_h = 0;
  self->dvi_v = 0;

  self->dvi_file = NULL;

  for (int k = 0; k < dvi_buf_size + 1; k++) {
    self->dvi_buf[k] = 0;
  }
  self->half_buf = dvi_buf_size / 2;
  self->dvi_limit = dvi_buf_size;
  self->dvi_ptr = 0;
  self->dvi_f = 0;
}

void ctex_dvi_add_page(ctex_dvi_t *self) { self->total_pages++; }

integer ctex_dvi_pages(ctex_dvi_t *self) { return self->total_pages; }

integer ctex_dvi_offset(ctex_dvi_t *self) { return self->dvi_offset; }

integer ctex_dvi_gone(ctex_dvi_t *self) { return self->dvi_gone; }

void ctex_dvi_flush(ctex_dvi_t *self) {
  if (self->dvi_limit == self->half_buf) {
    ctex_dvi_write_dvi(self, self->half_buf, dvi_buf_size - 1);
  }
  if (self->dvi_ptr > 0) {
    ctex_dvi_write_dvi(self, 0, self->dvi_ptr - 1);
  }
}

void ctex_dvi_wU8(ctex_dvi_t *self, uint8_t v) {
  self->dvi_buf[self->dvi_ptr] = v;
  ++self->dvi_ptr;
  if (self->dvi_ptr == self->dvi_limit) {
    ctex_dvi_swap(self);
  }
}

void ctex_dvi_swap(ctex_dvi_t *self) {
  if (self->dvi_limit == dvi_buf_size) {
    ctex_dvi_write_dvi(self, 0, self->half_buf - 1);
    self->dvi_limit = self->half_buf;
    self->dvi_offset += dvi_buf_size;
    self->dvi_ptr = 0;
  } else {
    ctex_dvi_write_dvi(self, self->half_buf, dvi_buf_size - 1);
    self->dvi_limit = dvi_buf_size;
  }
  self->dvi_gone += self->half_buf;
}

void ctex_dvi_write_dvi(ctex_dvi_t *self, dvi_index a, dvi_index b) {
  dvi_index k;
  for (k = a; k < b + 1; ++k) {
    fprintf(self->dvi_file, "%c", self->dvi_buf[k]);
  }
}

void ctex_dvi_four(ctex_dvi_t *self, integer x) {
  if (x >= 0) {
    ctex_dvi_wU8(self, x / 16777216);
  } else {
    x += 1073741824;
    x += 1073741824;
    ctex_dvi_wU8(self, (x / 16777216) + 128);
  }

  x &= 16777215;
  ctex_dvi_wU8(self, x / 65536);

  x &= 65535;
  ctex_dvi_wU8(self, x / 256);
  ctex_dvi_wU8(self, x & 255);
}

void ctex_dvi_pop(ctex_dvi_t *self, integer l) {
  if ((l == (self->dvi_offset + self->dvi_ptr)) && (self->dvi_ptr > 0)) {
    --self->dvi_ptr;
    return;
  }
  ctex_dvi_wU8(self, 142);
}

integer ctex_dvi_pos(ctex_dvi_t *self) {
  return self->dvi_offset + self->dvi_ptr;
}

integer ctex_dvi_cap(ctex_dvi_t *self) { return dvi_buf_size - self->dvi_ptr; }

void ctex_dvi_set_font(ctex_dvi_t *self, internal_font_number f) {
  self->dvi_f = f;
}

internal_font_number ctex_dvi_get_font(ctex_dvi_t *self) { return self->dvi_f; }

void ctex_dvi_set_h(ctex_dvi_t *self, scaled h) { self->dvi_h = h; }

void ctex_dvi_set_v(ctex_dvi_t *self, scaled v) { self->dvi_v = v; }

scaled ctex_dvi_get_h(ctex_dvi_t *self) { return self->dvi_h; }

scaled ctex_dvi_get_v(ctex_dvi_t *self) { return self->dvi_v; }
