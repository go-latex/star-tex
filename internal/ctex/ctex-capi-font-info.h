// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef CTEX_CAPI_FONT_INFO_H
#define CTEX_CAPI_FONT_INFO_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include "ctex-capi-types.h"

typedef struct {
  four_quarters font_check[font_max + 1];
  scaled font_size[font_max + 1], font_dsize[font_max + 1];
  font_index font_params[font_max + 1];
  str_number font_name[font_max + 1], font_area[font_max + 1];
  eight_bits font_bc[font_max + 1], font_ec[font_max + 1];
  halfword font_glue[font_max + 1];
  bool font_used[font_max + 1];
  integer hyphen_char[font_max + 1], skew_char[font_max + 1];
  font_index bchar_label[font_max + 1];
  short font_bchar[font_max + 1], font_false_bchar[font_max + 1];
  integer char_base[font_max + 1], width_base[font_max + 1],
      height_base[font_max + 1], depth_base[font_max + 1],
      italic_base[font_max + 1], lig_kern_base[font_max + 1],
      kern_base[font_max + 1], exten_base[font_max + 1],
      param_base[font_max + 1];

} ctex_font_info_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CTEX_CAPI_FONT_INFO_H */

