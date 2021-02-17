// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef CTEX_CAPI_CONSTS_H
#define CTEX_CAPI_CONSTS_H 1

#ifdef __cplusplus
extern "C" {
#endif


#define mem_max 1000000
#define mem_min 0
#define buf_size 3000
#define error_line 79
#define half_error_line 50
#define max_print_line 79
#define stack_size  300
#define max_in_open  15
#define font_max  255
#define font_mem_size  72000
#define param_size  60
#define nest_size  40
#define max_strings  7500
#define string_vacancies  74000
#define pool_size  100000
#define save_size  4000
#define trie_size  24000
#define trie_op_size  750
#define dvi_buf_size  16384
#define file_name_size  FILENAME_MAX
#define pool_name  "tex/tex.pool"

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CTEX_CAPI_CONSTS_H */

