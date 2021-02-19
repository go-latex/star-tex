// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "ctex-capi-font-info.h"
#include "ctex-capi-consts.h"

void ctex_font_info_init(ctex_font_info_t *fnt_infos) {
  for (int k = 0; k <= font_max; k++) {
    fnt_infos->font_used[k] = 0;
  }
  fnt_infos->font_name[0] = 800;
  fnt_infos->font_area[0] = 338;
  fnt_infos->hyphen_char[0] = 45;
  fnt_infos->skew_char[0] = -1;
  fnt_infos->bchar_label[0] = 0;
  fnt_infos->font_bchar[0] = 256;
  fnt_infos->font_false_bchar[0] = 256;
  fnt_infos->font_bc[0] = 1;
  fnt_infos->font_ec[0] = 0;
  fnt_infos->font_size[0] = 0;
  fnt_infos->font_dsize[0] = 0;
  fnt_infos->char_base[0] = 0;
  fnt_infos->width_base[0] = 0;
  fnt_infos->height_base[0] = 0;
  fnt_infos->depth_base[0] = 0;
  fnt_infos->italic_base[0] = 0;
  fnt_infos->lig_kern_base[0] = 0;
  fnt_infos->kern_base[0] = 0;
  fnt_infos->exten_base[0] = 0;
  fnt_infos->font_glue[0] = -1073741824;
  fnt_infos->font_params[0] = 7;
  fnt_infos->param_base[0] = -1;
}
