// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "ctex.h"

#define true 1
#define false 0

void ctex_init_ctx(ctex_t *ctx) {
  ctx->fmt_file_value.int_ = 0;
  ctx->tfm_file_mode = 0;
  ctx->tfm_file_value = 0;
  ctx->fmt_file_mode = 0; // clear members added above
  ctx->fmt_file = NULL;
  ctx->tfm_file = NULL;
  ctx->log_file = NULL;
  ctx->pool_file = NULL;
  ctx->term_out = NULL;
  ctx->term_in = NULL; // clear file pointers

  ctx->input_stream_buf = NULL;
  ctx->input_stream_len = 0;
  ctx->input_stream = NULL;

  ctex_dvi_init(&ctx->dvi_mgr);
}
