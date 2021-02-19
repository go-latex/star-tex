// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef CTEX_H
#define CTEX_H 1

//
// Copyright (c) 2013 Bryan Woods
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include <limits.h>
#include <math.h>

#include <errno.h>
#include <setjmp.h>

#include "ctex-capi-cgo.h"
#include "ctex-capi-consts.h"
#include "ctex-capi-dvi.h"
#include "ctex-capi-font-info.h"
#include "ctex-capi-types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  // Output from p2c 1.21alpha-07.Dec.93, the Pascal-to-C translator
  integer bad;
  integer tally;
  integer trick_count;
  integer first_count;
  integer interrupt;
  integer var_used;
  integer dyn_used;
  integer font_in_short_display;
  integer depth_threshold;
  integer breadth_max;
  integer cs_count;
  integer mag_set;
  integer line;
  integer max_param_stack;
  integer align_state;
  integer cur_val;
  integer if_line;
  integer skip_line;
  integer max_push;
  integer last_bop;
  integer dead_cycles;
  integer lq;
  integer lr;
  integer cur_s;
  integer last_badness;
  integer pack_begin_line;
  integer magic_offset;
  integer threshold;
  integer minimum_demerits;
  integer fewest_demerits;
  integer actual_looseness;
  integer line_diff;
  integer hyf_char;
  integer l_hyf;
  integer r_hyf;
  integer init_l_hyf;
  integer init_r_hyf;
  integer least_page_cost;
  integer last_penalty;
  integer insert_penalties;
  integer main_s;
  integer ready_already;

  ctex_dvi_t dvi_mgr;
  ASCII_code xord[256];
  char xchr[256], name_of_file[file_name_size];
  int name_length;

  ASCII_code buffer[buf_size + 1];
  packed_ASCII_code str_pool[pool_size + 1];
  pool_pointer str_start[max_strings + 1];

  int first, last, max_buf_stack;
  FILE *term_in;
  FILE *term_out;
  pool_pointer pool_ptr;
  str_number str_ptr;
  pool_pointer init_pool_ptr;
  str_number init_str_ptr;
  FILE *pool_file;
  FILE *log_file;
  char selector, dig[23];
  int term_offset, file_offset;
  ASCII_code trick_buf[error_line + 1];
  char interaction;
  bool_t deletions_allowed, set_box_allowed;
  char history;
  int8_t error_count;
  str_number help_line[6];
  char help_ptr;
  bool_t use_err_help, OK_to_interrupt, arith_error;
  scaled remainder_, max_v, max_h, rule_ht, rule_dp, rule_wd, cur_h, cur_v,
      cur_mu, disc_width, first_width, second_width, first_indent,
      second_indent, best_height_plus_depth, page_max_depth, best_size,
      last_kern;
  halfword temp_ptr;
  memory_word mem[mem_max - mem_min + 1];
  halfword lo_mem_max, hi_mem_min, avail, mem_end, rover;
  list_state_record nest[nest_size + 1];
  int nest_ptr, max_nest_stack;
  list_state_record cur_list;
  short shown_mode;
  char old_setting;
  memory_word eqtb[13007];
  quarterword xeq_level[844];
  two_halves hash[9267];
  halfword hash_used;
  bool_t no_new_control_sequence;
  memory_word save_stack[save_size + 1];
  int save_ptr, max_save_stack;
  quarterword cur_level;
  group_code cur_group;
  int cur_boundary;
  uint8_t cur_cmd;
  halfword cur_chr, cur_cs, cur_tok;
  in_state_record input_stack[stack_size + 1];
  int input_ptr, max_in_stack;
  in_state_record cur_input;
  int in_open, open_parens;
  FILE *(input_file[max_in_open + 1]);
  integer line_stack[max_in_open + 1];
  char scanner_status;
  halfword warning_index, def_ref, param_stack[param_size + 1];
  int param_ptr, base_ptr;
  halfword par_loc, par_token;
  bool_t force_eof;
  halfword cur_mark[5];
  char long_state;
  halfword pstack[9];
  char cur_val_level;
  small_number radix;
  glue_ord cur_order;
  FILE *(read_file[16]);
  char read_open[17];
  halfword cond_ptr;
  char if_limit;
  small_number cur_if;
  str_number cur_name, cur_area, cur_ext;
  pool_pointer area_delimiter, ext_delimiter;
  char TEX_format_default[20];
  bool_t name_in_progress;
  str_number job_name;
  bool_t log_opened;
  str_number output_file_name, log_name;
  FILE *tfm_file;

  memory_word font_info[font_mem_size + 1];
  font_index fmem_ptr;
  internal_font_number font_ptr;
  ctex_font_info_t fnt_infos;

  four_quarters null_character;
  bool_t doing_leaders;
  quarterword c, f;
  halfword g;
  halfword down_ptr, right_ptr;
  scaled total_stretch[4], total_shrink[4];
  halfword adjust_tail;
  two_halves empty_field;
  four_quarters null_delimiter;
  halfword cur_mlist;
  small_number cur_style, cur_size;
  bool_t mlist_penalties;
  internal_font_number cur_f;
  quarterword cur_c;
  four_quarters cur_i;
  halfword cur_align, cur_span, cur_loop, align_ptr, cur_head, cur_tail,
      just_box, passive, printed_node, pass_number;
  scaled active_width[7], cur_active_width[7], background[7], break_width[7];
  bool_t no_shrink_error_yet;
  halfword cur_p;
  bool_t second_pass, final_pass;
  integer minimal_demerits[4];
  halfword best_place[4], best_pl_line[4], easy_line, last_special_line,
      best_bet, best_line;
  short hc[66];
  small_number hn;
  halfword ha, hb;
  internal_font_number hf;
  short hu[64];
  ASCII_code cur_lang, init_cur_lang;
  halfword hyf_bchar;
  char hyf[65];
  halfword init_list;
  bool_t init_lig, init_lft;
  small_number hyphen_passed;
  halfword cur_l, cur_r, cur_q, lig_stack;
  bool_t ligature_present, lft_hit, rt_hit;
  two_halves trie[trie_size + 1];
  small_number hyf_distance[trie_op_size + 1], hyf_num[trie_op_size + 1];
  quarterword hyf_next[trie_op_size + 1];
  int op_start[256];
  str_number hyph_word[308];
  halfword hyph_list[308];
  hyph_pointer hyph_count;
  int trie_op_hash[trie_op_size + trie_op_size + 1];
  quarterword trie_used[256];
  ASCII_code trie_op_lang[trie_op_size + 1];
  quarterword trie_op_val[trie_op_size + 1];
  int trie_op_ptr;
  packed_ASCII_code trie_c[trie_size + 1];
  quarterword trie_o[trie_size + 1];
  trie_pointer trie_l[trie_size + 1];
  trie_pointer trie_r[trie_size + 1], trie_ptr;
  trie_pointer trie_hash[trie_size + 1];
  uint8_t trie_taken[CTEX_BITNSLOTS(trie_size)];
  trie_pointer trie_min[256], trie_max;
  bool_t trie_not_ready;
  halfword page_tail;
  char page_contents;
  halfword best_page_break;
  scaled page_so_far[8];
  halfword last_glue;
  bool_t output_active;
  internal_font_number main_f;
  four_quarters main_i, main_j;
  font_index main_k;
  halfword main_p, bchar, false_bchar;
  bool_t cancel_boundary, ins_disc;
  halfword cur_box, after_token;
  bool_t long_help_seen;
  str_number format_ident;
  FILE *fmt_file;
  FILE *(write_file[16]);
  bool_t write_open[18];
  halfword write_loc;

  jmp_buf _JL9998;
  jmp_buf _JL9999;
  FILE *output_stream; // displays the logging messages
  char *input_stream_buf;
  size_t input_stream_len;
  FILE *input_stream; // stores the command line args
  //
  // inexplicably, p2c forgets these
  int tfm_file_mode;
  uint8_t tfm_file_value;
  int fmt_file_mode;
  memory_word fmt_file_value;

} ctex_t;

void ctex_init_ctx(ctex_t *ctx);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // CTEX_TEX_H
