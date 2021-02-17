// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef CTEX_CAPI_TYPES_H
#define CTEX_CAPI_TYPES_H 1

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


  typedef uint8_t ASCII_code;
  typedef uint8_t eight_bits;
  typedef int pool_pointer;
  typedef int str_number;
  typedef uint8_t packed_ASCII_code;
  typedef int scaled;
  typedef int integer;
  typedef int nonnegative_integer;
  typedef char small_number;
  typedef double glue_ratio;
  typedef unsigned short quarterword;
  typedef int halfword;
  typedef char two_choices;
  typedef char four_choices;
  typedef struct two_halves {
    halfword rh;
    union {
      halfword lh;
      struct {
        quarterword b0, b1;
      } U2;
    };
  } two_halves;
  typedef struct four_quarters {
    quarterword b0, b1, b2, b3;
  } four_quarters;
  typedef union memory_word {
    integer int_;
    glue_ratio gr;
    two_halves hh;
    four_quarters qqqq;
  } memory_word;
  typedef char glue_ord;
  typedef struct list_state_record {
    short mode_field;
    halfword head_field, tail_field;
    integer pg_field, ml_field;
    memory_word aux_field;
  } list_state_record;
  typedef char group_code;
  typedef struct in_state_record {
    quarterword state_field, index_field;
    halfword start_field, loc_field, limit_field, name_field;
  } in_state_record;
  typedef int internal_font_number;
  typedef int font_index;
  typedef int dvi_index;
  typedef int trie_pointer;
  typedef short hyph_pointer;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CTEX_CAPI_TYPES_H */

