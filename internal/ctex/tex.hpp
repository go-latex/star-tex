// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

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

#include <bitset>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

#include "ctex-capi-types.h"
#include "ctex-capi-cgo.h"

namespace tex {

class tex {

protected:
  /* Copyright (C) 1991-2020 Free Software Foundation, Inc.
     This file is part of the GNU C Library.

     The GNU C Library is free software; you can redistribute it and/or
     modify it under the terms of the GNU Lesser General Public
     License as published by the Free Software Foundation; either
     version 2.1 of the License, or (at your option) any later version.

     The GNU C Library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Lesser General Public License for more details.

     You should have received a copy of the GNU Lesser General Public
     License along with the GNU C Library; if not, see
     <https://www.gnu.org/licenses/>.  */
  /* This header is separate from features.h so that the compiler can
     include it implicitly at the start of every compilation.  It must
     not itself include <features.h> or any other header that includes
     <features.h> because the implicit include comes before any feature
     test macros that may be defined in a source file before it first
     explicitly includes a system header.  GCC knows the name of this
     header in order to preinclude it.  */
  /* glibc's intent is to support the IEC 559 math functionality, real
     and complex.  If the GCC (4.9 and later) predefined macros
     specifying compiler intent are available, use them to determine
     whether the overall intent is to support these features; otherwise,
     presume an older compiler has intent to support these features and
     define these macros by default.  */
  /* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
     synchronized with ISO/IEC 10646:2017, fifth edition, plus
     the following additions from Amendment 1 to the fifth edition:
     - 56 emoji characters
     - 285 hentaigana
     - 3 additional Zanabazar Square characters */
  // Output from p2c 1.21alpha-07.Dec.93, the Pascal-to-C translator
  constexpr static auto mem_max = 1000000;
  constexpr static auto mem_min = 0;
  constexpr static auto buf_size = 3000;
  constexpr static auto error_line = 79;
  constexpr static auto half_error_line = 50;
  constexpr static auto max_print_line = 79;
  constexpr static auto stack_size = 300;
  constexpr static auto max_in_open = 15;
  constexpr static auto font_max = 255;
  constexpr static auto font_mem_size = 72000;
  constexpr static auto param_size = 60;
  constexpr static auto nest_size = 40;
  constexpr static auto max_strings = 7500;
  constexpr static auto string_vacancies = 74000;
  constexpr static auto pool_size = 100000;
  constexpr static auto save_size = 4000;
  constexpr static auto trie_size = 24000;
  constexpr static auto trie_op_size = 750;
  constexpr static auto dvi_buf_size = 16384;
  constexpr static auto file_name_size = FILENAME_MAX;
  constexpr static auto pool_name = "tex/tex.pool";
  integer bad, tally, trick_count, first_count, interrupt, var_used, dyn_used,
      font_in_short_display, depth_threshold, breadth_max, cs_count, mag_set,
      line, max_param_stack, align_state, cur_val, if_line, skip_line,
      total_pages, max_push, last_bop, dead_cycles, lq, lr, dvi_offset,
      dvi_gone, cur_s, last_badness, pack_begin_line, magic_offset, threshold,
      minimum_demerits, fewest_demerits, actual_looseness, line_diff, hyf_char,
      l_hyf, r_hyf, init_l_hyf, init_r_hyf, least_page_cost, last_penalty,
      insert_penalties, main_s, ready_already;
  ASCII_code xord[256];
  char xchr[256], name_of_file[file_name_size];
  int name_length;
  std::vector<ASCII_code> buffer;
  int first, last, max_buf_stack;
  FILE *term_in;
  FILE *term_out;
  std::vector<packed_ASCII_code> str_pool;
  std::vector<pool_pointer> str_start;
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
  bool deletions_allowed, set_box_allowed;
  char history;
  int8_t error_count;
  str_number help_line[6];
  char help_ptr;
  bool use_err_help, OK_to_interrupt, arith_error;
  scaled remainder_, max_v, max_h, rule_ht, rule_dp, rule_wd, dvi_h, dvi_v,
      cur_h, cur_v, cur_mu, disc_width, first_width, second_width, first_indent,
      second_indent, best_height_plus_depth, page_max_depth, best_size,
      last_kern;
  halfword temp_ptr;
  std::vector<memory_word> mem;
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
  bool no_new_control_sequence;
  memory_word save_stack[save_size + 1];
  int save_ptr, max_save_stack;
  quarterword cur_level;
  group_code cur_group;
  int cur_boundary;
  eight_bits cur_cmd;
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
  bool force_eof;
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
  bool name_in_progress;
  str_number job_name;
  bool log_opened;
  FILE *dvi_file;
  str_number output_file_name, log_name;
  FILE *tfm_file;
  std::vector<memory_word> font_info;
  font_index fmem_ptr;
  internal_font_number font_ptr;
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
  four_quarters null_character;
  bool doing_leaders;
  quarterword c, f;
  halfword g;
  std::vector<eight_bits> dvi_buf;
  dvi_index half_buf, dvi_limit, dvi_ptr;
  halfword down_ptr, right_ptr;
  internal_font_number dvi_f;
  scaled total_stretch[4], total_shrink[4];
  halfword adjust_tail;
  two_halves empty_field;
  four_quarters null_delimiter;
  halfword cur_mlist;
  small_number cur_style, cur_size;
  bool mlist_penalties;
  internal_font_number cur_f;
  quarterword cur_c;
  four_quarters cur_i;
  halfword cur_align, cur_span, cur_loop, align_ptr, cur_head, cur_tail,
      just_box, passive, printed_node, pass_number;
  scaled active_width[7], cur_active_width[7], background[7], break_width[7];
  bool no_shrink_error_yet;
  halfword cur_p;
  bool second_pass, final_pass;
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
  bool init_lig, init_lft;
  small_number hyphen_passed;
  halfword cur_l, cur_r, cur_q, lig_stack;
  bool ligature_present, lft_hit, rt_hit;
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
  std::bitset<trie_size> trie_taken;
  trie_pointer trie_min[256], trie_max;
  bool trie_not_ready;
  halfword page_tail;
  char page_contents;
  halfword best_page_break;
  scaled page_so_far[8];
  halfword last_glue;
  bool output_active;
  internal_font_number main_f;
  four_quarters main_i, main_j;
  font_index main_k;
  halfword main_p, bchar, false_bchar;
  bool cancel_boundary, ins_disc;
  halfword cur_box, after_token;
  bool long_help_seen;
  str_number format_ident;
  FILE *fmt_file;
  FILE *(write_file[16]);
  bool write_open[18];
  halfword write_loc;


	void loadU8(FILE *r, int &mode, eight_bits *v) {
		if (mode==1) {
			fread(v, sizeof(eight_bits), 1, r);
		} else {
			mode = 1;
		}
	}

	eight_bits &readU8(FILE *r, int &mode, eight_bits *v) {
		if (mode == 1) {
			mode = 2;
			fread(v, sizeof(eight_bits), 1, r);
		}
		return *v;
	}

	void loadU32(FILE *r, int &mode, memory_word *v) {
		if (mode==1) {
			fread(&v, sizeof(memory_word), 1, r);
		} else {
			mode = 1;
		}
	}

	memory_word &readU32(FILE *r, int &mode, memory_word *v) {
		if (mode == 1) {
			mode = 2;
			fread(&v, sizeof(memory_word), 1, r);
		}
		return *v;
	}

	void writeU32(FILE *w, int &mode, memory_word *v) {
		fwrite(v, sizeof(memory_word), 1, w);
		mode = 0;
	}

  static int erstat(FILE *f) {
    return f == nullptr or (ferror(f) != 0);
  }

  static int fpeek(FILE *f) {
	  int c = fgetc(f);
	  ungetc(c, f);
	  return c;
  }

  static void break_in(FILE *ios, bool) {}

  static bool eoln(FILE *f) {
    int c = fpeek(f);
    return (c == EOF or c == '\n');
  }

  static const char *
  trim_name(char *filename, size_t length) // never called on a string literal;
                                           // note the lack of a const
  {
    for (char *p = filename + length - 1; *p == ' '; --p)
      *p = '\0';

    return filename;
  }

  static void io_error(int error, const char *name) {}


  void initialize() {
    integer k;
    hyph_pointer z;
    mem.resize(mem_max - mem_min + 1);
    font_info.resize(font_mem_size + 1);
    str_pool.resize(pool_size + 1);
    dvi_buf.resize(dvi_buf_size + 1);
    str_start.resize(max_strings + 1);
    buffer.resize(buf_size + 1);
    std::iota(xchr, xchr + 255, 0);
    std::iota(xord, xord + 255, 0);
    interaction = 3;
    deletions_allowed = true;
    set_box_allowed = true;
    error_count = 0;
    help_ptr = 0;
    use_err_help = false;
    interrupt = 0;
    OK_to_interrupt = true;
    nest_ptr = 0;
    max_nest_stack = 0;
    cur_list.mode_field = 1;
    cur_list.head_field = mem_max - 1;
    cur_list.tail_field = mem_max - 1;
    cur_list.aux_field.int_ = -65536000;
    cur_list.ml_field = 0;
    cur_list.pg_field = 0;
    shown_mode = 0;
    page_contents = 0;
    page_tail = mem_max - 2;
    mem[mem_max - mem_min - 2].hh.rh = -1073741824;
    last_glue = 1073741824;
    last_penalty = 0;
    last_kern = 0;
    page_so_far[7] = 0;
    page_max_depth = 0;
    for (k = 12163; k <= 13006; ++k)
      xeq_level[k - 12163] = 1;
    no_new_control_sequence = true;
    hash[0].lh = 0;
    hash[0].rh = 0;
    for (k = 515; k <= 9780; ++k)
      hash[k - 514] = hash[0];
    save_ptr = 0;
    cur_level = 1;
    cur_group = 0;
    cur_boundary = 0;
    max_save_stack = 0;
    mag_set = 0;
    cur_mark[0] = -1073741824;
    cur_mark[1] = -1073741824;
    cur_mark[2] = -1073741824;
    cur_mark[3] = -1073741824;
    cur_mark[4] = -1073741824;
    cur_val = 0;
    cur_val_level = 0;
    radix = 0;
    cur_order = 0;
    for (k = 0; k <= 16; ++k)
      read_open[k] = 2;
    cond_ptr = -1073741824;
    if_limit = 0;
    cur_if = 0;
    if_line = 0;
    memcpy(TEX_format_default, "tex/plain.fmt", 14);
    for (k = 0; k <= font_max; ++k)
      font_used[k] = false;
    null_character.b0 = 0;
    null_character.b1 = 0;
    null_character.b2 = 0;
    null_character.b3 = 0;
    total_pages = 0;
    max_v = 0;
    max_h = 0;
    max_push = 0;
    last_bop = -1;
    doing_leaders = false;
    dead_cycles = 0;
    cur_s = -1;
    half_buf = dvi_buf_size / 2;
    dvi_limit = dvi_buf_size;
    dvi_ptr = 0;
    dvi_offset = 0;
    dvi_gone = 0;
    down_ptr = -1073741824;
    right_ptr = -1073741824;
    adjust_tail = -1073741824;
    last_badness = 0;
    pack_begin_line = 0;
    empty_field.rh = 0;
    empty_field.lh = -1073741824;
    null_delimiter.b0 = 0;
    null_delimiter.b1 = 0;
    null_delimiter.b2 = 0;
    null_delimiter.b3 = 0;
    align_ptr = -1073741824;
    cur_align = -1073741824;
    cur_span = -1073741824;
    cur_loop = -1073741824;
    cur_head = -1073741824;
    cur_tail = -1073741824;
    for (z = 0; z <= 307; ++z) {
      hyph_word[z] = 0;
      hyph_list[z] = -1073741824;
    }
    hyph_count = 0;
    output_active = false;
    insert_penalties = 0;
    ligature_present = false;
    cancel_boundary = false;
    lft_hit = false;
    rt_hit = false;
    ins_disc = false;
    after_token = 0;
    long_help_seen = false;
    format_ident = 0;
    for (k = 0; k <= 17; ++k)
      write_open[k] = false;
    for (k = 1; k <= 19; ++k)
      mem[k - mem_min].int_ = 0;
    k = 0;
    while (k <= 19) {
      mem[k - mem_min].hh.rh = -1073741823;
      mem[k - mem_min].hh.U2.b0 = 0;
      mem[k - mem_min].hh.U2.b1 = 0;
      k += 4;
    }
    mem[6 - mem_min].int_ = 65536;
    mem[4 - mem_min].hh.U2.b0 = 1;
    mem[10 - mem_min].int_ = 65536;
    mem[8 - mem_min].hh.U2.b0 = 2;
    mem[14 - mem_min].int_ = 65536;
    mem[12 - mem_min].hh.U2.b0 = 1;
    mem[15 - mem_min].int_ = 65536;
    mem[12 - mem_min].hh.U2.b1 = 1;
    mem[18 - mem_min].int_ = -65536;
    mem[16 - mem_min].hh.U2.b0 = 1;
    rover = 20;
    mem[rover - mem_min].hh.rh = 1073741824;
    mem[rover - mem_min].hh.lh = 1000;
    mem[rover - mem_min + 1].hh.lh = rover;
    mem[rover - mem_min + 1].hh.rh = rover;
    lo_mem_max = rover + 1000;
    mem[lo_mem_max - mem_min].hh.rh = -1073741824;
    mem[lo_mem_max - mem_min].hh.lh = -1073741824;
    for (k = mem_max - 13; k <= mem_max; ++k)
      mem[k - mem_min] = mem[lo_mem_max - mem_min];
    mem[mem_max - mem_min - 10].hh.lh = 13614;
    mem[mem_max - mem_min - 9].hh.rh = 65536;
    mem[mem_max - mem_min - 9].hh.lh = -1073741824;
    mem[mem_max - mem_min - 7].hh.U2.b0 = 1;
    mem[mem_max - mem_min - 6].hh.lh = 1073741824;
    mem[mem_max - mem_min - 7].hh.U2.b1 = 0;
    mem[mem_max - mem_min].hh.U2.b1 = 255;
    mem[mem_max - mem_min].hh.U2.b0 = 1;
    mem[mem_max - mem_min].hh.rh = mem_max;
    mem[mem_max - mem_min - 2].hh.U2.b0 = 10;
    mem[mem_max - mem_min - 2].hh.U2.b1 = 0;
    avail = -1073741824;
    mem_end = mem_max;
    hi_mem_min = mem_max - 13;
    var_used = 20;
    dyn_used = 14;
    eqtb[9781].hh.U2.b0 = 101;
    eqtb[9781].hh.rh = -1073741824;
    eqtb[9781].hh.U2.b1 = 0;
    for (k = 1; k <= 9780; ++k)
      eqtb[k] = eqtb[9781];
    eqtb[9782].hh.rh = 0;
    eqtb[9782].hh.U2.b1 = 1;
    eqtb[9782].hh.U2.b0 = 117;
    for (k = 9783; k <= 10311; ++k)
      eqtb[k] = eqtb[9782];
    mem[-mem_min].hh.rh += 530;
    eqtb[10312].hh.rh = -1073741824;
    eqtb[10312].hh.U2.b0 = 118;
    eqtb[10312].hh.U2.b1 = 1;
    for (k = 10313; k <= 10577; ++k)
      eqtb[k] = eqtb[9781];
    eqtb[10578].hh.rh = -1073741824;
    eqtb[10578].hh.U2.b0 = 119;
    eqtb[10578].hh.U2.b1 = 1;
    for (k = 10579; k <= 10833; ++k)
      eqtb[k] = eqtb[10578];
    eqtb[10834].hh.rh = 0;
    eqtb[10834].hh.U2.b0 = 120;
    eqtb[10834].hh.U2.b1 = 1;
    for (k = 10835; k <= 10882; ++k)
      eqtb[k] = eqtb[10834];
    eqtb[10883].hh.rh = 0;
    eqtb[10883].hh.U2.b0 = 120;
    eqtb[10883].hh.U2.b1 = 1;
    for (k = 10884; k <= 12162; ++k)
      eqtb[k] = eqtb[10883];
    for (k = 0; k <= 255; ++k) {
      eqtb[k + 10883].hh.rh = 12;
      eqtb[k + 11907].hh.rh = k - 1073741824;
      eqtb[k + 11651].hh.rh = 1000;
    }
    eqtb[10896].hh.rh = 5;
    eqtb[10915].hh.rh = 10;
    eqtb[10975].hh.rh = 0;
    eqtb[10920].hh.rh = 14;
    eqtb[11010].hh.rh = 15;
    eqtb[10883].hh.rh = 9;
    for (k = 48; k <= 57; ++k)
      eqtb[k + 11907].hh.rh = k - 1073713152;
    for (k = 65; k <= 90; ++k) {
      eqtb[k + 10883].hh.rh = 11;
      eqtb[k + 10915].hh.rh = 11;
      eqtb[k + 11907].hh.rh = k - 1073712896;
      eqtb[k + 11939].hh.rh = k - 1073712864;
      eqtb[k + 11139].hh.rh = k + 32;
      eqtb[k + 11171].hh.rh = k + 32;
      eqtb[k + 11395].hh.rh = k;
      eqtb[k + 11427].hh.rh = k;
      eqtb[k + 11651].hh.rh = 999;
    }
    for (k = 12163; k <= 12473; ++k)
      eqtb[k].int_ = 0;
    eqtb[12180].int_ = 1000;
    eqtb[12164].int_ = 10000;
    eqtb[12204].int_ = 1;
    eqtb[12203].int_ = 25;
    eqtb[12208].int_ = 92;
    eqtb[12211].int_ = 13;
    for (k = 0; k <= 255; ++k)
      eqtb[k + 12474].int_ = -1;
    eqtb[12520].int_ = 0;
    for (k = 12730; k <= 13006; ++k)
      eqtb[k].int_ = 0;
    hash_used = 9514;
    cs_count = 0;
    eqtb[9523].hh.U2.b0 = 116;
    hash[9009].rh = 502;
    font_ptr = 0;
    fmem_ptr = 7;
    font_name[0] = 800;
    font_area[0] = 338;
    hyphen_char[0] = 45;
    skew_char[0] = -1;
    bchar_label[0] = 0;
    font_bchar[0] = 256;
    font_false_bchar[0] = 256;
    font_bc[0] = 1;
    font_ec[0] = 0;
    font_size[0] = 0;
    font_dsize[0] = 0;
    char_base[0] = 0;
    width_base[0] = 0;
    height_base[0] = 0;
    depth_base[0] = 0;
    italic_base[0] = 0;
    lig_kern_base[0] = 0;
    kern_base[0] = 0;
    exten_base[0] = 0;
    font_glue[0] = -1073741824;
    font_params[0] = 7;
    param_base[0] = -1;
    for (k = 0; k <= 6; ++k)
      font_info[k].int_ = 0;
    for (k = -trie_op_size; k <= trie_op_size; ++k)
      trie_op_hash[k + trie_op_size] = 0;
    for (k = 0; k <= 255; ++k)
      trie_used[k] = 0;
    trie_op_ptr = 0;
    trie_not_ready = true;
    trie_l[0] = 0;
    trie_c[0] = 0;
    trie_ptr = 0;
    hash[9000].rh = 1189;
    format_ident = 1256;
    hash[9008].rh = 1295;
    eqtb[9522].hh.U2.b1 = 1;
    eqtb[9522].hh.U2.b0 = 113;
    eqtb[9522].hh.rh = -1073741824;
  }
  void print_ln() {
    switch (selector) {
    case 19:
      fprintf(term_out, "\n");
      fprintf(log_file, "\n");
      term_offset = 0;
      file_offset = 0;
      break;
    case 18:
      fprintf(log_file, "\n");
      file_offset = 0;
      break;
    case 17:
      fprintf(term_out, "\n");
      term_offset = 0;
      break;
    case 16:
    case 20:
    case 21:
      // blank case
      break;
    default:
      fprintf(write_file[selector], "\n");
      break;
    }
  }
  void print_char(ASCII_code s) {
    if (s == eqtb[12212].int_) {
      if (selector < 20) {
        print_ln();
        goto _L10;
      }
    }
    switch (selector) {
    case 19:
      fprintf(term_out, "%c", xchr[s]);
      fprintf(log_file, "%c", xchr[s]);
      ++term_offset;
      ++file_offset;
      if (term_offset == max_print_line) {
        fprintf(term_out, "\n");
        term_offset = 0;
      }
      if (file_offset == max_print_line) {
        fprintf(log_file, "\n");
        file_offset = 0;
      }
      break;
    case 18:
      fprintf(log_file, "%c", xchr[s]);
      ++file_offset;
      if (file_offset == max_print_line)
        print_ln();
      break;
    case 17:
      fprintf(term_out, "%c", xchr[s]);
      ++term_offset;
      if (term_offset == max_print_line)
        print_ln();
      break;
    case 16:
      // blank case
      break;
    case 20:
      if (tally < trick_count)
        trick_buf[tally % error_line] = s;
      break;
    case 21:
      if (pool_ptr < pool_size) {
        str_pool[pool_ptr] = s;
        ++pool_ptr;
      }
      break;
    default:
      fprintf(write_file[selector], "%c", xchr[s]);
      break;
    }
    ++tally;
  _L10:;
  }
  void print(integer s) {
    pool_pointer j;
    integer nl;
    if (s >= str_ptr) {
      s = 259;
    } else if (s < 256) {
      if (s >= 0) {
        if (selector > 20) {
          print_char(s);
          goto _L10;
        }
        if (s == eqtb[12212].int_) {
          if (selector < 20) {
            print_ln();
            goto _L10;
          }
        }
        nl = eqtb[12212].int_;
        eqtb[12212].int_ = -1;
        j = str_start[s];
        while (j < str_start[s + 1]) {
          print_char(str_pool[j]);
          ++j;
        }
        eqtb[12212].int_ = nl;
        goto _L10;
      }
      s = 259;
    }
    j = str_start[s];
    while (j < str_start[s + 1]) {
      print_char(str_pool[j]);
      ++j;
    }
  _L10:;
  }
  void slow_print(integer s) {
    pool_pointer j;
    if ((s >= str_ptr) || (s < 256)) {
      print(s);
      return;
    }
    j = str_start[s];
    while (j < str_start[s + 1]) {
      print(str_pool[j]);
      ++j;
    }
  }
  void print_nl(str_number s) {
    if (((term_offset > 0) && (selector & 1)) ||
        ((file_offset > 0) && (selector >= 18)))
      print_ln();
    print(s);
  }
  void print_esc(str_number s) {
    integer c = eqtb[12208].int_;
    if (c >= 0) {
      if (c < 256)
        print(c);
    }
    slow_print(s);
  }
  void print_the_digs(eight_bits k) {
    while (k > 0) {
      --k;
      if (dig[k] < 10)
        print_char(dig[k] + 48);
      else
        print_char(dig[k] + 55);
    }
  }
  void print_int(integer n) {
    char k = 0;
    integer m;
    if (n < 0) {
      print_char(45);
      if (n > (-100000000)) {
        n = -n;
      } else {
        m = (-n) - 1;
        n = m / 10;
        m = (m % 10) + 1;
        k = 1;
        if (m < 10) {
          dig[0] = m;
        } else {
          dig[0] = 0;
          ++n;
        }
      }
    }
    do {
      dig[k] = n % 10;
      n /= 10;
      ++k;
    } while (n);
    print_the_digs(k);
  }
  void print_cs(integer p) {
    if (p < 514) {
      if (p >= 257) {
        if (p == 513) {
          print_esc(504);
          print_esc(505);
          print_char(32);
          return;
        }
        print_esc(p - 257);
        if (eqtb[p + 10626].hh.rh == 11)
          print_char(32);
        return;
      }
      if (p < 1)
        print_esc(506);
      else
        print(p - 1);
      return;
    }
    if (p >= 9781) {
      print_esc(506);
      return;
    }
    if (((unsigned)hash[p - 514].rh) >= str_ptr) {
      print_esc(507);
    } else {
      print_esc(hash[p - 514].rh);
      print_char(32);
    }
  }
  void sprint_cs(halfword p) {
    if (p >= 514) {
      print_esc(hash[p - 514].rh);
      return;
    }
    if (p < 257) {
      print(p - 1);
      return;
    }
    if (p < 513) {
      print_esc(p - 257);
    } else {
      print_esc(504);
      print_esc(505);
    }
  }
  void print_file_name(integer n, integer a, integer e) {
    slow_print(a);
    slow_print(n);
    slow_print(e);
  }
  void print_size(integer s) {
    if (!s) {
      print_esc(412);
      return;
    }
    if (s == 16)
      print_esc(413);
    else
      print_esc(414);
  }
  void print_write_whatsit(str_number s, halfword p) {
    print_esc(s);
    if (mem[p - mem_min + 1].hh.lh < 16) {
      print_int(mem[p - mem_min + 1].hh.lh);
      return;
    }
    if (mem[p - mem_min + 1].hh.lh == 16)
      print_char(42);
    else
      print_char(45);
  }
  jmp_buf _JL9998;
  void jump_out() { longjmp(_JL9998, 1); }
  void error() {
    ASCII_code c;
    integer s1, s2, s3, s4;
    if (history < 2)
      history = 2;
    print_char(46);
    show_context();
    if (interaction == 3) {
      while (true) {
      _L22:
        clear_for_error_prompt();
        print(264);
        term_input();
        if (last == first)
          goto _L10;
        c = buffer[first];
        if (c >= 97)
          c -= 32;
        switch (c) {
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
          if (deletions_allowed) {
            s1 = cur_tok;
            s2 = cur_cmd;
            s3 = cur_chr;
            s4 = align_state;
            align_state = 1000000;
            OK_to_interrupt = false;
            if ((last > (first + 1)) && (buffer[first + 1] >= 48) &&
                (buffer[first + 1] <= 57))
              c = (c * 10) + buffer[first + 1] - 528;
            else
              c -= 48;
            while (c > 0) {
              get_token();
              --c;
            }
            cur_tok = s1;
            cur_cmd = s2;
            cur_chr = s3;
            align_state = s4;
            OK_to_interrupt = true;
            help_ptr = 2;
            help_line[1] = 279;
            help_line[0] = 280;
            show_context();
            goto _L22;
          }
          break;
        case 69:
          if (base_ptr > 0) {
            print_nl(265);
            slow_print(input_stack[base_ptr].name_field);
            print(266);
            print_int(line);
            interaction = 2;
            jump_out();
          }
          break;
        case 72:
          if (use_err_help) {
            give_err_help();
            use_err_help = false;
          } else {
            if (!help_ptr) {
              help_ptr = 2;
              help_line[1] = 281;
              help_line[0] = 282;
            }
            do {
              --help_ptr;
              print(help_line[help_ptr]);
              print_ln();
            } while (help_ptr);
          }
          help_ptr = 4;
          help_line[3] = 283;
          help_line[2] = 282;
          help_line[1] = 284;
          help_line[0] = 285;
          goto _L22;
          break;
        case 73:
          begin_file_reading();
          if (last > (first + 1)) {
            cur_input.loc_field = first + 1;
            buffer[first] = 32;
          } else {
            print(278);
            term_input();
            cur_input.loc_field = first;
          }
          first = last;
          cur_input.limit_field = last - 1;
          goto _L10;
          break;
        case 81:
        case 82:
        case 83:
          error_count = 0;
          interaction = c - 81;
          print(273);
          switch (c) {
          case 81:
            print_esc(274);
            --selector;
            break;
          case 82:
            print_esc(275);
            break;
          case 83:
            print_esc(276);
            break;
          }
          print(277);
          print_ln();
          fflush(term_out);
          errno = 0;
          goto _L10;
          break;
        case 88:
          interaction = 2;
          jump_out();
          break;
        default:
          break;
        }
        print(267);
        print_nl(268);
        print_nl(269);
        if (base_ptr > 0)
          print(270);
        if (deletions_allowed)
          print_nl(271);
        print_nl(272);
      }
    }
    ++error_count;
    if (error_count == 100) {
      print_nl(263);
      history = 3;
      jump_out();
    }
    if (interaction > 0)
      --selector;
    if (use_err_help) {
      print_ln();
      give_err_help();
    } else {
      while (help_ptr > 0) {
        --help_ptr;
        print_nl(help_line[help_ptr]);
      }
    }
    print_ln();
    if (interaction > 0)
      ++selector;
    print_ln();
  _L10:;
  }
  void fatal_error(str_number s) {
    normalize_selector();
    print_nl(262);
    print(287);
    help_ptr = 1;
    help_line[0] = s;
    if (interaction == 3)
      interaction = 2;
    if (log_opened)
      error();
    history = 3;
    jump_out();
  }
  void overflow(str_number s, integer n) {
    normalize_selector();
    print_nl(262);
    print(288);
    print(s);
    print_char(61);
    print_int(n);
    print_char(93);
    help_ptr = 2;
    help_line[1] = 289;
    help_line[0] = 290;
    if (interaction == 3)
      interaction = 2;
    if (log_opened)
      error();
    history = 3;
    jump_out();
  }
  void confusion(str_number s) {
    normalize_selector();
    if (history < 2) {
      print_nl(262);
      print(291);
      print(s);
      print_char(41);
      help_ptr = 1;
      help_line[0] = 292;
    } else {
      print_nl(262);
      print(293);
      help_ptr = 2;
      help_line[1] = 294;
      help_line[0] = 295;
    }
    if (interaction == 3)
      interaction = 2;
    if (log_opened)
      error();
    history = 3;
    jump_out();
  }
  virtual bool a_open_in(FILE *&f) {
    f = fopen(trim_name(name_of_file, file_name_size), "rb");
    if (!f)
      io_error(errno, trim_name(name_of_file, file_name_size));
    return erstat(f) == 0;
  }
  virtual bool a_open_out(FILE *&f) {
    f = fopen(trim_name(name_of_file, file_name_size), "wb");
    if (!f)
      io_error(errno, trim_name(name_of_file, file_name_size));
    return erstat(f) == 0;
  }
  virtual bool b_open_in(FILE *&f) {
    f = fopen(trim_name(name_of_file, file_name_size), "rb");
    if (!f)
      io_error(errno, trim_name(name_of_file, file_name_size));
    return erstat(f) == 0;
  }
  virtual bool b_open_out(FILE *&f) {
    f = fopen(trim_name(name_of_file, file_name_size), "wb");
    if (!f)
      io_error(errno, trim_name(name_of_file, file_name_size));
    return erstat(f) == 0;
  }
  virtual bool w_open_in(FILE *&f) {
    f = fopen(trim_name(name_of_file, file_name_size), "rb");
    if (!f)
      io_error(errno, trim_name(name_of_file, file_name_size));
    return erstat(f) == 0;
  }
  virtual bool w_open_out(FILE *&f) {
    f = fopen(trim_name(name_of_file, file_name_size), "wb");
    if (!f)
      io_error(errno, trim_name(name_of_file, file_name_size));
    return erstat(f) == 0;
  }
  virtual void a_close(FILE *&f) {
    if (f)
      fclose(f);
    f = nullptr;
  }
  virtual void b_close(FILE *&f) {
    if (f)
      fclose(f);
    f = nullptr;
  }
  virtual void w_close(FILE *&f) {
    if (f)
      fclose(f);
    f = nullptr;
  }
  jmp_buf _JL9999;
  bool input_ln(FILE *f, bool bypass_eoln) {
    int last_nonblank;
    if (bypass_eoln) {
      if (!feof(f))
        fgetc(f);
    }
    last = first;
    if (feof(f)) {
      return false;
    } else {
      last_nonblank = first;
      while (!eoln(f)) {
        if (last >= max_buf_stack) {
          max_buf_stack = last + 1;
          if (max_buf_stack == buf_size) {
            if (!format_ident) {
              fprintf(term_out, "Buffer size exceeded!\n");
              longjmp(_JL9999, 1);
            } else {
              cur_input.loc_field = first;
              cur_input.limit_field = last - 1;
              overflow(256, buf_size);
            }
          }
        }
        buffer[last] = xord[fpeek(f)];
        fgetc(f);
        ++last;
        if (buffer[last - 1] != 32)
          last_nonblank = last;
      }
      last = last_nonblank;
      return true;
    }
  }
  bool init_terminal() {
    bool result;
    term_in = input_stream;
    if (!term_in)
      io_error(errno, "TTY:");
    while (true) {
      fprintf(term_out, "**");
      fflush(term_out);
      errno = 0;
      if (!input_ln(term_in, true)) {
        fprintf(term_out, "\n! End of file on the terminal... why?");
        result = false;
        goto _L10;
      }
      cur_input.loc_field = first;
      while ((cur_input.loc_field < last) &&
             (buffer[cur_input.loc_field] == 32))
        ++cur_input.loc_field;
      if (cur_input.loc_field < last) {
        result = true;
        goto _L10;
      }
      fprintf(term_out, "Please type the name of your input file.\n");
    }
  _L10:
    return result;
  }
  str_number make_string() {
    if (str_ptr == max_strings)
      overflow(258, max_strings - init_str_ptr);
    ++str_ptr;
    str_start[str_ptr] = pool_ptr;
    return str_ptr - 1;
  }
  bool str_eq_buf(str_number s, integer k) {
    bool result;
    pool_pointer j = str_start[s];
    while (j < str_start[s + 1]) {
      if (str_pool[j] != buffer[k]) {
        result = false;
        goto _L45;
      }
      ++j;
      ++k;
    }
    result = true;
  _L45:
    return result;
  }
  bool str_eq_str(str_number s, str_number t) {
    pool_pointer j, k;
    bool result = false;
    if (str_start[s + 1] - str_start[s] != str_start[t + 1] - str_start[t])
      goto _L45;
    j = str_start[s];
    k = str_start[t];
    while (j < str_start[s + 1]) {
      if (str_pool[j] != str_pool[k])
        goto _L45;
      ++j;
      ++k;
    }
    result = true;
  _L45:
    return result;
  }
  bool get_strings_started() {
    bool result;
    uint8_t k, l;
    char m, n;
    str_number g;
    integer a;
    bool c = false;
    short character;
    pool_ptr = 0;
    str_ptr = 0;
    str_start[0] = 0;
    for (character = 0; character <= 255; ++character) {
      k = character;
      if ((k < 32) || (k > 126)) {
        str_pool[pool_ptr] = 94;
        ++pool_ptr;
        str_pool[pool_ptr] = 94;
        ++pool_ptr;
        if (k < 64) {
          str_pool[pool_ptr] = k + 64;
          ++pool_ptr;
        } else if (k < 128) {
          str_pool[pool_ptr] = k - 64;
          ++pool_ptr;
        } else {
          l = k / 16;
          if (l < 10) {
            str_pool[pool_ptr] = l + 48;
            ++pool_ptr;
          } else {
            str_pool[pool_ptr] = l + 87;
            ++pool_ptr;
          }
          l = k & 15;
          if (l < 10) {
            str_pool[pool_ptr] = l + 48;
            ++pool_ptr;
          } else {
            str_pool[pool_ptr] = l + 87;
            ++pool_ptr;
          }
        }
      } else {
        str_pool[pool_ptr] = k;
        ++pool_ptr;
      }
      g = make_string();
    }
    // memcpy(name_of_file, pool_name, file_name_size); // FIXME(sbinet)
    memcpy(name_of_file, pool_name, 13);
    if (!a_open_in(pool_file)) {
      fprintf(term_out, "! I can't read tex.pool.\n");
      a_close(pool_file);
      result = false;
      goto _L10;
    }
    do {
      if (feof(pool_file)) {
        fprintf(term_out, "! tex.pool has no check sum.\n");
        a_close(pool_file);
        result = false;
        goto _L10;
      }
	  fread(&m, sizeof(char), 1, pool_file);
	  fread(&n, sizeof(char), 1, pool_file);
      if (m == '*') {
        a = 0;
        k = 1;
        while (true) {
          if ((xord[n] < 48) || (xord[n] > 57)) {
            fprintf(term_out, "! tex.pool check sum doesn't have nine digits.\n");
            a_close(pool_file);
            result = false;
            goto _L10;
          }
          a = (a * 10) + xord[n] - 48;
          if (k == 9)
            goto _L30;
          ++k;
		  fread(&n, sizeof(char), 1, pool_file);
        }
      _L30:
        if (a != 117275187) {
          fprintf(term_out, "! tex.pool doesn't match; TANGLE me again.\n");
          a_close(pool_file);
          result = false;
          goto _L10;
        }
        c = true;
      } else {
        if ((xord[m] < 48) || (xord[m] > 57) || (xord[n] < 48) ||
            (xord[n] > 57)) {
          fprintf(term_out, "! tex.pool line doesn't begin with two digits.\n");
          a_close(pool_file);
          result = false;
          goto _L10;
        }
        l = (xord[m] * 10) + xord[n] - 528;
        if (pool_ptr + l + string_vacancies > pool_size) {
          fprintf(term_out, "! You have to increase POOLSIZE.\n");
          a_close(pool_file);
          result = false;
          goto _L10;
        }
        for (k = 1; k <= l; ++k) {
          if (eoln(pool_file))
            m = ' ';
          else
			fread(&m, sizeof(char), 1, pool_file);
          str_pool[pool_ptr] = xord[m];
          ++pool_ptr;
        }
		fgetc(pool_file); // skip the newline
        g = make_string();
      }
    } while (!c);
    a_close(pool_file);
    result = true;
  _L10:
    return result;
  }
  void print_two(integer n) {
    n = abs(n) % 100;
    print_char((n / 10) + 48);
    print_char((n % 10) + 48);
  }
  void print_hex(integer n) {
    char k = 0;
    print_char(34);
    do {
      dig[k] = n & 15;
      n /= 16;
      ++k;
    } while (n);
    print_the_digs(k);
  }
  void print_roman_int(integer n) {
    pool_pointer k;
    nonnegative_integer u, v = 1000;
    pool_pointer j = str_start[260];
    while (true) {
      while (n >= v) {
        print_char(str_pool[j]);
        n -= v;
      }
      if (n <= 0)
        goto _L10;
      k = j + 2;
      u = v / (str_pool[k - 1] - 48);
      if (str_pool[k - 1] == 50) {
        k += 2;
        u /= str_pool[k - 1] - 48;
      }
      if (n + u >= v) {
        print_char(str_pool[k]);
        n += u;
      } else {
        j += 2;
        v /= str_pool[j - 1] - 48;
      }
    }
  _L10:;
  }
  void print_current_string() {
    pool_pointer j = str_start[str_ptr];
    while (j < pool_ptr) {
      print_char(str_pool[j]);
      ++j;
    }
  }
  void term_input() {
    int k, N;
    fflush(term_out);
    errno = 0;
    if (!input_ln(term_in, true))
      fatal_error(261);
    term_offset = 0;
    --selector;
    if (last != first) {
      for (N = last, k = first; k <= (N - 1); ++k)
        print(buffer[k]);
    }
    print_ln();
    ++selector;
  }
  void int_error(integer n) {
    print(286);
    print_int(n);
    print_char(41);
    error();
  }
  void normalize_selector() {
    if (log_opened)
      selector = 19;
    else
      selector = 17;
    if (!job_name)
      open_log_file();
    if (!interaction)
      --selector;
  }
  void pause_for_instructions() {
    if (!OK_to_interrupt)
      return;
    interaction = 3;
    if ((selector == 18) || (selector == 16))
      ++selector;
    print_nl(262);
    print(296);
    help_ptr = 3;
    help_line[2] = 297;
    help_line[1] = 298;
    help_line[0] = 299;
    deletions_allowed = false;
    error();
    deletions_allowed = true;
    interrupt = 0;
  }
  integer half(integer x) {
    if (x & 1)
      return (x + 1) / 2;
    else
      return x / 2;
  }
  scaled round_decimals(small_number k) {
    integer a = 0;
    while (k > 0) {
      --k;
      a = (a + (dig[k] * 131072)) / 10;
    }
    return (a + 1) / 2;
  }
  void print_scaled(scaled s) {
    scaled delta = 10;
    if (s < 0) {
      print_char(45);
      s = -s;
    }
    print_int(s / 65536);
    print_char(46);
    s = ((s & 65535) * 10) + 5;
    do {
      if (delta > 65536)
        s -= 17232;
      print_char((s / 65536) + 48);
      s = (s & 65535) * 10;
      delta *= 10;
    } while (s > delta);
  }
  scaled mult_and_add(integer n, scaled x, scaled y, scaled max_answer) {
    if (n < 0) {
      x = -x;
      n = -n;
    }
    if (!n) {
      return y;
    } else if ((x <= ((max_answer - y) / n)) && (-x <= (max_answer + y) / n)) {
      return (n * x) + y;
    } else {
      arith_error = true;
      return 0;
    }
  }
  scaled x_over_n(scaled x, integer n) {
    int result;
    bool negative = false;
    if (!n) {
      arith_error = true;
      result = 0;
      remainder_ = x;
    } else {
      if (n < 0) {
        x = -x;
        n = -n;
        negative = true;
      }
      if (x >= 0) {
        result = x / n;
        remainder_ = x % n;
      } else {
        result = -((-x) / n);
        remainder_ = -((-x) % n);
      }
    }
    if (negative)
      remainder_ = -remainder_;
    return result;
  }
  scaled xn_over_d(scaled x, integer n, integer d) {
    int result;
    bool positive;
    nonnegative_integer t, u, v;
    if (x >= 0) {
      positive = true;
    } else {
      x = -x;
      positive = false;
    }
    t = (x & 32767) * n;
    u = ((x / 32768) * n) + (t / 32768);
    v = ((u % d) * 32768) + (t & 32767);
    if (u / d >= 32768)
      arith_error = true;
    else
      u = ((u / d) * 32768) + (v / d);
    if (positive) {
      result = u;
      remainder_ = v % d;
    } else {
      result = -u;
      remainder_ = -(v % d);
    }
    return result;
  }
  halfword badness(scaled t, scaled s) {
    integer r;
    if (!t) {
      return 0;
    } else if (s <= 0) {
      return 10000;
    } else {
      if (t <= 7230584) {
        r = t * 297 / s;
      } else if (s >= 1663497)
        r = t / (s / 297);
      else
        r = t;
      if (r > 1290)
        return 10000;
      else
        return ((r * r * r) + 131072) / 262144;
    }
  }
  void show_token_list(integer p, integer q, integer l) {
    integer m, c;
    ASCII_code match_chr = 35, n = 48;
    tally = 0;
    while ((p != (-1073741824)) && (tally < l)) {
      if (p == q) {
        first_count = tally;
        trick_count = tally + error_line - half_error_line + 1;
        if (trick_count < error_line)
          trick_count = error_line;
      }
      if ((p < hi_mem_min) || (p > mem_end)) {
        print_esc(309);
        goto _L10;
      }
      if (mem[p - mem_min].hh.lh >= 4095) {
        print_cs(mem[p - mem_min].hh.lh - 4095);
      } else {
        m = mem[p - mem_min].hh.lh / 256;
        c = mem[p - mem_min].hh.lh & 255;
        if (mem[p - mem_min].hh.lh < 0) {
          print_esc(555);
        } else {
          switch (m) {
          case 1:
          case 2:
          case 3:
          case 4:
          case 7:
          case 8:
          case 10:
          case 11:
          case 12:
            print(c);
            break;
          case 6:
            print(c);
            print(c);
            break;
          case 5:
            print(match_chr);
            if (c > 9) {
              print_char(33);
              goto _L10;
            }
            print_char(c + 48);
            break;
          case 13:
            match_chr = c;
            print(c);
            ++n;
            print_char(n);
            if (n > 57)
              goto _L10;
            break;
          case 14:
            print(556);
            break;
          default:
            print_esc(555);
            break;
          }
        }
      }
      p = mem[p - mem_min].hh.rh;
    }
    if (p != (-1073741824))
      print_esc(554);
  _L10:;
  }
  void runaway() {
    halfword p;
    if (scanner_status <= 1)
      return;
    print_nl(569);
    switch (scanner_status) {
    case 2:
      print(570);
      p = def_ref;
      break;
    case 3:
      print(571);
      p = mem_max - 3;
      break;
    case 4:
      print(572);
      p = mem_max - 4;
      break;
    case 5:
      print(573);
      p = def_ref;
      break;
    }
    print_char(63);
    print_ln();
    show_token_list(mem[p - mem_min].hh.rh, -1073741824, error_line - 10);
  }
  halfword get_avail() {
    halfword p = avail;
    if (p != (-1073741824)) {
      avail = mem[avail - mem_min].hh.rh;
    } else if (mem_end < mem_max) {
      ++mem_end;
      p = mem_end;
    } else {
      --hi_mem_min;
      p = hi_mem_min;
      if (hi_mem_min <= lo_mem_max) {
        runaway();
        overflow(300, mem_max - mem_min + 1);
      }
    }
    mem[p - mem_min].hh.rh = -1073741824;
    return p;
  }
  void flush_list(halfword p) {
    halfword q, r;
    if (p == (-1073741824))
      return;
    r = p;
    do {
      q = r;
      r = mem[r - mem_min].hh.rh;
    } while (r != (-1073741824));
    mem[q - mem_min].hh.rh = avail;
    avail = p;
  }
  halfword get_node(integer s) {
    halfword result, p, q;
    integer r, t;
  _L20:
    p = rover;
    do {
      q = p + mem[p - mem_min].hh.lh;
      while (mem[q - mem_min].hh.rh == 1073741824) {
        t = mem[q - mem_min + 1].hh.rh;
        if (q == rover)
          rover = t;
        mem[t - mem_min + 1].hh.lh = mem[q - mem_min + 1].hh.lh;
        mem[mem[q - mem_min + 1].hh.lh - mem_min + 1].hh.rh = t;
        q += mem[q - mem_min].hh.lh;
      }
      r = q - s;
      if (r > (p + 1)) {
        mem[p - mem_min].hh.lh = r - p;
        rover = p;
        goto _L40;
      }
      if (r == p) {
        if (mem[p - mem_min + 1].hh.rh != p) {
          rover = mem[p - mem_min + 1].hh.rh;
          t = mem[p - mem_min + 1].hh.lh;
          mem[rover - mem_min + 1].hh.lh = t;
          mem[t - mem_min + 1].hh.rh = rover;
          goto _L40;
        }
      }
      mem[p - mem_min].hh.lh = q - p;
      p = mem[p - mem_min + 1].hh.rh;
    } while (p != rover);
    if (s == 1073741824) {
      result = 1073741824;
      goto _L10;
    }
    if (lo_mem_max + 2 < hi_mem_min) {
      if (lo_mem_max <= 1073741822) {
        if (hi_mem_min - lo_mem_max >= 1998)
          t = lo_mem_max + 1000;
        else
          t = lo_mem_max + ((hi_mem_min - lo_mem_max) / 2) + 1;
        p = mem[rover - mem_min + 1].hh.lh;
        q = lo_mem_max;
        mem[p - mem_min + 1].hh.rh = q;
        mem[rover - mem_min + 1].hh.lh = q;
        if (t > 1073741824)
          t = 1073741824;
        mem[q - mem_min + 1].hh.rh = rover;
        mem[q - mem_min + 1].hh.lh = p;
        mem[q - mem_min].hh.rh = 1073741824;
        mem[q - mem_min].hh.lh = t - lo_mem_max;
        lo_mem_max = t;
        mem[lo_mem_max - mem_min].hh.rh = -1073741824;
        mem[lo_mem_max - mem_min].hh.lh = -1073741824;
        rover = q;
        goto _L20;
      }
    }
    overflow(300, mem_max - mem_min + 1);
  _L40:
    mem[r - mem_min].hh.rh = -1073741824;
    result = r;
  _L10:
    return result;
  }
  void free_node(halfword p, halfword s) {
    halfword q;
    mem[p - mem_min].hh.lh = s;
    mem[p - mem_min].hh.rh = 1073741824;
    q = mem[rover - mem_min + 1].hh.lh;
    mem[p - mem_min + 1].hh.lh = q;
    mem[p - mem_min + 1].hh.rh = rover;
    mem[rover - mem_min + 1].hh.lh = p;
    mem[q - mem_min + 1].hh.rh = p;
  }
  void sort_avail() {
    halfword q, r, old_rover;
    halfword p = get_node(1073741824);
    p = mem[rover - mem_min + 1].hh.rh;
    mem[rover - mem_min + 1].hh.rh = 1073741824;
    old_rover = rover;
    while (p != old_rover) {
      if (p < rover) {
        q = p;
        p = mem[q - mem_min + 1].hh.rh;
        mem[q - mem_min + 1].hh.rh = rover;
        rover = q;
        continue;
      }
      q = rover;
      while (mem[q - mem_min + 1].hh.rh < p)
        q = mem[q - mem_min + 1].hh.rh;
      r = mem[p - mem_min + 1].hh.rh;
      mem[p - mem_min + 1].hh.rh = mem[q - mem_min + 1].hh.rh;
      mem[q - mem_min + 1].hh.rh = p;
      p = r;
    }
    p = rover;
    while (mem[p - mem_min + 1].hh.rh != 1073741824) {
      mem[mem[p - mem_min + 1].hh.rh - mem_min + 1].hh.lh = p;
      p = mem[p - mem_min + 1].hh.rh;
    }
    mem[p - mem_min + 1].hh.rh = rover;
    mem[rover - mem_min + 1].hh.lh = p;
  }
  halfword new_null_box() {
    halfword p = get_node(7);
    mem[p - mem_min].hh.U2.b0 = 0;
    mem[p - mem_min].hh.U2.b1 = 0;
    mem[p - mem_min + 1].int_ = 0;
    mem[p - mem_min + 2].int_ = 0;
    mem[p - mem_min + 3].int_ = 0;
    mem[p - mem_min + 4].int_ = 0;
    mem[p - mem_min + 5].hh.rh = -1073741824;
    mem[p - mem_min + 5].hh.U2.b0 = 0;
    mem[p - mem_min + 5].hh.U2.b1 = 0;
    mem[p - mem_min + 6].gr = 0.0;
    return p;
  }
  halfword new_rule() {
    halfword p = get_node(4);
    mem[p - mem_min].hh.U2.b0 = 2;
    mem[p - mem_min].hh.U2.b1 = 0;
    mem[p - mem_min + 1].int_ = -1073741824;
    mem[p - mem_min + 2].int_ = -1073741824;
    mem[p - mem_min + 3].int_ = -1073741824;
    return p;
  }
  halfword new_ligature(quarterword f, quarterword c, halfword q) {
    halfword p = get_node(2);
    mem[p - mem_min].hh.U2.b0 = 6;
    mem[p - mem_min + 1].hh.U2.b0 = f;
    mem[p - mem_min + 1].hh.U2.b1 = c;
    mem[p - mem_min + 1].hh.rh = q;
    mem[p - mem_min].hh.U2.b1 = 0;
    return p;
  }
  halfword new_lig_item(quarterword c) {
    halfword p = get_node(2);
    mem[p - mem_min].hh.U2.b1 = c;
    mem[p - mem_min + 1].hh.rh = -1073741824;
    return p;
  }
  halfword new_disc() {
    halfword p = get_node(2);
    mem[p - mem_min].hh.U2.b0 = 7;
    mem[p - mem_min].hh.U2.b1 = 0;
    mem[p - mem_min + 1].hh.lh = -1073741824;
    mem[p - mem_min + 1].hh.rh = -1073741824;
    return p;
  }
  halfword new_math(scaled w, small_number s) {
    halfword p = get_node(2);
    mem[p - mem_min].hh.U2.b0 = 9;
    mem[p - mem_min].hh.U2.b1 = s;
    mem[p - mem_min + 1].int_ = w;
    return p;
  }
  halfword new_spec(halfword p) {
    halfword q = get_node(4);
    mem[q - mem_min] = mem[p - mem_min];
    mem[q - mem_min].hh.rh = -1073741824;
    mem[q - mem_min + 1].int_ = mem[p - mem_min + 1].int_;
    mem[q - mem_min + 2].int_ = mem[p - mem_min + 2].int_;
    mem[q - mem_min + 3].int_ = mem[p - mem_min + 3].int_;
    return q;
  }
  halfword new_param_glue(small_number n) {
    halfword q;
    halfword p = get_node(2);
    mem[p - mem_min].hh.U2.b0 = 10;
    mem[p - mem_min].hh.U2.b1 = n + 1;
    mem[p - mem_min + 1].hh.rh = -1073741824;
    q = eqtb[n + 9782].hh.rh;
    mem[p - mem_min + 1].hh.lh = q;
    ++mem[q - mem_min].hh.rh;
    return p;
  }
  halfword new_glue(halfword q) {
    halfword p = get_node(2);
    mem[p - mem_min].hh.U2.b0 = 10;
    mem[p - mem_min].hh.U2.b1 = 0;
    mem[p - mem_min + 1].hh.rh = -1073741824;
    mem[p - mem_min + 1].hh.lh = q;
    ++mem[q - mem_min].hh.rh;
    return p;
  }
  halfword new_skip_param(small_number n) {
    halfword p;
    temp_ptr = new_spec(eqtb[n + 9782].hh.rh);
    p = new_glue(temp_ptr);
    mem[temp_ptr - mem_min].hh.rh = -1073741824;
    mem[p - mem_min].hh.U2.b1 = n + 1;
    return p;
  }
  halfword new_kern(scaled w) {
    halfword p = get_node(2);
    mem[p - mem_min].hh.U2.b0 = 11;
    mem[p - mem_min].hh.U2.b1 = 0;
    mem[p - mem_min + 1].int_ = w;
    return p;
  }
  halfword new_penalty(integer m) {
    halfword p = get_node(2);
    mem[p - mem_min].hh.U2.b0 = 12;
    mem[p - mem_min].hh.U2.b1 = 0;
    mem[p - mem_min + 1].int_ = m;
    return p;
  }
  void short_display(integer p) {
    integer n;
    while (p > mem_min) {
      if (p >= hi_mem_min) {
        if (p <= mem_end) {
          if (mem[p - mem_min].hh.U2.b0 != font_in_short_display) {
            if (mem[p - mem_min].hh.U2.b0 > font_max)
              print_char(42);
            else
              print_esc(hash[mem[p - mem_min].hh.U2.b0 + 9010].rh);
            print_char(32);
            font_in_short_display = mem[p - mem_min].hh.U2.b0;
          }
          print(mem[p - mem_min].hh.U2.b1);
        }
      } else {
        switch (mem[p - mem_min].hh.U2.b0) {
        case 0:
        case 1:
        case 3:
        case 8:
        case 4:
        case 5:
        case 13:
          print(308);
          break;
        case 2:
          print_char(124);
          break;
        case 10:
          if (mem[p - mem_min + 1].hh.lh)
            print_char(32);
          break;
        case 9:
          print_char(36);
          break;
        case 6:
          short_display(mem[p - mem_min + 1].hh.rh);
          break;
        case 7:
          short_display(mem[p - mem_min + 1].hh.lh);
          short_display(mem[p - mem_min + 1].hh.rh);
          n = mem[p - mem_min].hh.U2.b1;
          while (n > 0) {
            if (mem[p - mem_min].hh.rh != (-1073741824))
              p = mem[p - mem_min].hh.rh;
            --n;
          }
          break;
        default:
          break;
        }
      }
      p = mem[p - mem_min].hh.rh;
    }
  }
  void print_font_and_char(integer p) {
    if (p > mem_end) {
      print_esc(309);
      return;
    }
    if (mem[p - mem_min].hh.U2.b0 > font_max)
      print_char(42);
    else
      print_esc(hash[mem[p - mem_min].hh.U2.b0 + 9010].rh);
    print_char(32);
    print(mem[p - mem_min].hh.U2.b1);
  }
  void print_mark(integer p) {
    print_char(123);
    if ((p < hi_mem_min) || (p > mem_end))
      print_esc(309);
    else
      show_token_list(mem[p - mem_min].hh.rh, -1073741824, max_print_line - 10);
    print_char(125);
  }
  void print_rule_dimen(scaled d) {
    if (d == (-1073741824))
      print_char(42);
    else
      print_scaled(d);
  }
  void print_glue(scaled d, integer order, str_number s) {
    print_scaled(d);
    if (((unsigned)order) > 3) {
      print(310);
      return;
    }
    if (order <= 0) {
      if (s)
        print(s);
      return;
    }
    print(311);
    while (order > 1) {
      print_char(108);
      --order;
    }
  }
  void print_spec(integer p, str_number s) {
    if ((p < mem_min) || (p >= lo_mem_max)) {
      print_char(42);
      return;
    }
    print_scaled(mem[p - mem_min + 1].int_);
    if (s)
      print(s);
    if (mem[p - mem_min + 2].int_) {
      print(312);
      print_glue(mem[p - mem_min + 2].int_, mem[p - mem_min].hh.U2.b0, s);
    }
    if (mem[p - mem_min + 3].int_) {
      print(313);
      print_glue(mem[p - mem_min + 3].int_, mem[p - mem_min].hh.U2.b1, s);
    }
  }
  void print_fam_and_char(halfword p) {
    print_esc(464);
    print_int(mem[p - mem_min].hh.U2.b0);
    print_char(32);
    print(mem[p - mem_min].hh.U2.b1);
  }
  void print_delimiter(halfword p) {
    integer a = (mem[p - mem_min].qqqq.b0 * 256) + mem[p - mem_min].qqqq.b1;
    a = (a * 4096) + (mem[p - mem_min].qqqq.b2 * 256) +
        mem[p - mem_min].qqqq.b3;
    if (a < 0)
      print_int(a);
    else
      print_hex(a);
  }
  void print_subsidiary_data(halfword p, ASCII_code c) {
    if (pool_ptr - str_start[str_ptr] >= depth_threshold) {
      if (mem[p - mem_min].hh.rh)
        print(314);
      return;
    }
    str_pool[pool_ptr] = c;
    ++pool_ptr;
    temp_ptr = p;
    switch (mem[p - mem_min].hh.rh) {
    case 1:
      print_ln();
      print_current_string();
      print_fam_and_char(p);
      break;
    case 2:
      show_info();
      break;
    case 3:
      if (mem[p - mem_min].hh.lh == (-1073741824)) {
        print_ln();
        print_current_string();
        print(859);
      } else {
        show_info();
      }
      break;
    default:
      break;
    }
    --pool_ptr;
  }
  void print_style(integer c) {
    switch (c / 2) {
    case 0:
      print_esc(860);
      break;
    case 1:
      print_esc(861);
      break;
    case 2:
      print_esc(862);
      break;
    case 3:
      print_esc(863);
      break;
    default:
      print(864);
      break;
    }
  }
  void print_skip_param(integer n) {
    switch (n) {
    case 0:
      print_esc(376);
      break;
    case 1:
      print_esc(377);
      break;
    case 2:
      print_esc(378);
      break;
    case 3:
      print_esc(379);
      break;
    case 4:
      print_esc(380);
      break;
    case 5:
      print_esc(381);
      break;
    case 6:
      print_esc(382);
      break;
    case 7:
      print_esc(383);
      break;
    case 8:
      print_esc(384);
      break;
    case 9:
      print_esc(385);
      break;
    case 10:
      print_esc(386);
      break;
    case 11:
      print_esc(387);
      break;
    case 12:
      print_esc(388);
      break;
    case 13:
      print_esc(389);
      break;
    case 14:
      print_esc(390);
      break;
    case 15:
      print_esc(391);
      break;
    case 16:
      print_esc(392);
      break;
    case 17:
      print_esc(393);
      break;
    default:
      print(394);
      break;
    }
  }
  void show_node_list(integer p) {
    integer n = 0;
    double g;
    if (pool_ptr - str_start[str_ptr] > depth_threshold) {
      if (p > (-1073741824))
        print(314);
      goto _L10;
    }
    while (p > mem_min) {
      print_ln();
      print_current_string();
      if (p > mem_end) {
        print(315);
        goto _L10;
      }
      ++n;
      if (n > breadth_max) {
        print(316);
        goto _L10;
      }
      if (p >= hi_mem_min) {
        print_font_and_char(p);
      } else {
        switch (mem[p - mem_min].hh.U2.b0) {
        case 0:
        case 1:
        case 13:
          if (!mem[p - mem_min].hh.U2.b0) {
            print_esc(104);
          } else if (mem[p - mem_min].hh.U2.b0 == 1)
            print_esc(118);
          else
            print_esc(318);
          print(319);
          print_scaled(mem[p - mem_min + 3].int_);
          print_char(43);
          print_scaled(mem[p - mem_min + 2].int_);
          print(320);
          print_scaled(mem[p - mem_min + 1].int_);
          if (mem[p - mem_min].hh.U2.b0 == 13) {
            if (mem[p - mem_min].hh.U2.b1) {
              print(286);
              print_int(mem[p - mem_min].hh.U2.b1 + 1);
              print(322);
            }
            if (mem[p - mem_min + 6].int_) {
              print(323);
              print_glue(mem[p - mem_min + 6].int_,
                         mem[p - mem_min + 5].hh.U2.b1, 0);
            }
            if (mem[p - mem_min + 4].int_) {
              print(324);
              print_glue(mem[p - mem_min + 4].int_,
                         mem[p - mem_min + 5].hh.U2.b0, 0);
            }
          } else {
            g = mem[p - mem_min + 6].gr;
            if (g && mem[p - mem_min + 5].hh.U2.b0) {
              print(325);
              if (mem[p - mem_min + 5].hh.U2.b0 == 2)
                print(326);
              if (abs(mem[p - mem_min + 6].int_) < 1048576) {
                print(327);
              } else if (fabs(g) > 20000.0) {
                if (g > 0.0)
                  print_char(62);
                else
                  print(328);
                print_glue(1310720000, mem[p - mem_min + 5].hh.U2.b1, 0);
              } else {
                print_glue(int(round(65536 * g)), mem[p - mem_min + 5].hh.U2.b1,
                           0);
              }
            }
            if (mem[p - mem_min + 4].int_) {
              print(321);
              print_scaled(mem[p - mem_min + 4].int_);
            }
          }
          str_pool[pool_ptr] = 46;
          ++pool_ptr;
          show_node_list(mem[p - mem_min + 5].hh.rh);
          --pool_ptr;
          break;
        case 2:
          print_esc(329);
          print_rule_dimen(mem[p - mem_min + 3].int_);
          print_char(43);
          print_rule_dimen(mem[p - mem_min + 2].int_);
          print(320);
          print_rule_dimen(mem[p - mem_min + 1].int_);
          break;
        case 3:
          print_esc(330);
          print_int(mem[p - mem_min].hh.U2.b1);
          print(331);
          print_scaled(mem[p - mem_min + 3].int_);
          print(332);
          print_spec(mem[p - mem_min + 4].hh.rh, 0);
          print_char(44);
          print_scaled(mem[p - mem_min + 2].int_);
          print(333);
          print_int(mem[p - mem_min + 1].int_);
          str_pool[pool_ptr] = 46;
          ++pool_ptr;
          show_node_list(mem[p - mem_min + 4].hh.lh);
          --pool_ptr;
          break;
        case 8:
          switch (mem[p - mem_min].hh.U2.b1) {
          case 0:
            print_write_whatsit(1284, p);
            print_char(61);
            print_file_name(mem[p - mem_min + 1].hh.rh,
                            mem[p - mem_min + 2].hh.lh,
                            mem[p - mem_min + 2].hh.rh);
            break;
          case 1:
            print_write_whatsit(594, p);
            print_mark(mem[p - mem_min + 1].hh.rh);
            break;
          case 2:
            print_write_whatsit(1285, p);
            break;
          case 3:
            print_esc(1286);
            print_mark(mem[p - mem_min + 1].hh.rh);
            break;
          case 4:
            print_esc(1288);
            print_int(mem[p - mem_min + 1].hh.rh);
            print(1291);
            print_int(mem[p - mem_min + 1].hh.U2.b0);
            print_char(44);
            print_int(mem[p - mem_min + 1].hh.U2.b1);
            print_char(41);
            break;
          default:
            print(1292);
            break;
          }
          break;
        case 10:
          if (mem[p - mem_min].hh.U2.b1 >= 100) {
            print_esc(338);
            if (mem[p - mem_min].hh.U2.b1 == 101) {
              print_char(99);
            } else if (mem[p - mem_min].hh.U2.b1 == 102)
              print_char(120);
            print(339);
            print_spec(mem[p - mem_min + 1].hh.lh, 0);
            str_pool[pool_ptr] = 46;
            ++pool_ptr;
            show_node_list(mem[p - mem_min + 1].hh.rh);
            --pool_ptr;
          } else {
            print_esc(334);
            if (mem[p - mem_min].hh.U2.b1) {
              print_char(40);
              if (mem[p - mem_min].hh.U2.b1 < 98) {
                print_skip_param(mem[p - mem_min].hh.U2.b1 - 1);
              } else if (mem[p - mem_min].hh.U2.b1 == 98)
                print_esc(335);
              else
                print_esc(336);
              print_char(41);
            }
            if (mem[p - mem_min].hh.U2.b1 != 98) {
              print_char(32);
              if (mem[p - mem_min].hh.U2.b1 < 98)
                print_spec(mem[p - mem_min + 1].hh.lh, 0);
              else
                print_spec(mem[p - mem_min + 1].hh.lh, 337);
            }
          }
          break;
        case 11:
          if (mem[p - mem_min].hh.U2.b1 != 99) {
            print_esc(340);
            if (mem[p - mem_min].hh.U2.b1)
              print_char(32);
            print_scaled(mem[p - mem_min + 1].int_);
            if (mem[p - mem_min].hh.U2.b1 == 2)
              print(341);
          } else {
            print_esc(342);
            print_scaled(mem[p - mem_min + 1].int_);
            print(337);
          }
          break;
        case 9:
          print_esc(343);
          if (!mem[p - mem_min].hh.U2.b1)
            print(344);
          else
            print(345);
          if (mem[p - mem_min + 1].int_) {
            print(346);
            print_scaled(mem[p - mem_min + 1].int_);
          }
          break;
        case 6:
          print_font_and_char(p + 1);
          print(347);
          if (mem[p - mem_min].hh.U2.b1 > 1)
            print_char(124);
          font_in_short_display = mem[p - mem_min + 1].hh.U2.b0;
          short_display(mem[p - mem_min + 1].hh.rh);
          if (mem[p - mem_min].hh.U2.b1 & 1)
            print_char(124);
          print_char(41);
          break;
        case 12:
          print_esc(348);
          print_int(mem[p - mem_min + 1].int_);
          break;
        case 7:
          print_esc(349);
          if (mem[p - mem_min].hh.U2.b1 > 0) {
            print(350);
            print_int(mem[p - mem_min].hh.U2.b1);
          }
          str_pool[pool_ptr] = 46;
          ++pool_ptr;
          show_node_list(mem[p - mem_min + 1].hh.lh);
          --pool_ptr;
          str_pool[pool_ptr] = 124;
          ++pool_ptr;
          show_node_list(mem[p - mem_min + 1].hh.rh);
          --pool_ptr;
          break;
        case 4:
          print_esc(351);
          print_mark(mem[p - mem_min + 1].int_);
          break;
        case 5:
          print_esc(352);
          str_pool[pool_ptr] = 46;
          ++pool_ptr;
          show_node_list(mem[p - mem_min + 1].int_);
          --pool_ptr;
          break;
        case 14:
          print_style(mem[p - mem_min].hh.U2.b1);
          break;
        case 15:
          print_esc(525);
          str_pool[pool_ptr] = 68;
          ++pool_ptr;
          show_node_list(mem[p - mem_min + 1].hh.lh);
          --pool_ptr;
          str_pool[pool_ptr] = 84;
          ++pool_ptr;
          show_node_list(mem[p - mem_min + 1].hh.rh);
          --pool_ptr;
          str_pool[pool_ptr] = 83;
          ++pool_ptr;
          show_node_list(mem[p - mem_min + 2].hh.lh);
          --pool_ptr;
          str_pool[pool_ptr] = 115;
          ++pool_ptr;
          show_node_list(mem[p - mem_min + 2].hh.rh);
          --pool_ptr;
          break;
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 27:
        case 26:
        case 29:
        case 28:
        case 30:
        case 31:
          switch (mem[p - mem_min].hh.U2.b0) {
          case 16:
            print_esc(865);
            break;
          case 17:
            print_esc(866);
            break;
          case 18:
            print_esc(867);
            break;
          case 19:
            print_esc(868);
            break;
          case 20:
            print_esc(869);
            break;
          case 21:
            print_esc(870);
            break;
          case 22:
            print_esc(871);
            break;
          case 23:
            print_esc(872);
            break;
          case 27:
            print_esc(873);
            break;
          case 26:
            print_esc(874);
            break;
          case 29:
            print_esc(539);
            break;
          case 24:
            print_esc(533);
            print_delimiter(p + 4);
            break;
          case 28:
            print_esc(508);
            print_fam_and_char(p + 4);
            break;
          case 30:
            print_esc(875);
            print_delimiter(p + 1);
            break;
          case 31:
            print_esc(876);
            print_delimiter(p + 1);
            break;
          }
          if (mem[p - mem_min].hh.U2.b1) {
            if (mem[p - mem_min].hh.U2.b1 == 1)
              print_esc(877);
            else
              print_esc(878);
          }
          if (mem[p - mem_min].hh.U2.b0 < 30)
            print_subsidiary_data(p + 1, 46);
          print_subsidiary_data(p + 2, 94);
          print_subsidiary_data(p + 3, 95);
          break;
        case 25:
          print_esc(879);
          if (mem[p - mem_min + 1].int_ == 1073741824)
            print(880);
          else
            print_scaled(mem[p - mem_min + 1].int_);
          if (mem[p - mem_min + 4].qqqq.b0 || mem[p - mem_min + 4].qqqq.b1 ||
              mem[p - mem_min + 4].qqqq.b2 || mem[p - mem_min + 4].qqqq.b3) {
            print(881);
            print_delimiter(p + 4);
          }
          if (mem[p - mem_min + 5].qqqq.b0 || mem[p - mem_min + 5].qqqq.b1 ||
              mem[p - mem_min + 5].qqqq.b2 || mem[p - mem_min + 5].qqqq.b3) {
            print(882);
            print_delimiter(p + 5);
          }
          print_subsidiary_data(p + 2, 92);
          print_subsidiary_data(p + 3, 47);
          break;
        default:
          print(317);
          break;
        }
      }
      p = mem[p - mem_min].hh.rh;
    }
  _L10:;
  }
  void show_box(halfword p) {
    depth_threshold = eqtb[12188].int_;
    breadth_max = eqtb[12187].int_;
    if (breadth_max <= 0)
      breadth_max = 5;
    if (pool_ptr + depth_threshold >= pool_size)
      depth_threshold = pool_size - pool_ptr - 1;
    show_node_list(p);
    print_ln();
  }
  void delete_token_ref(halfword p) {
    if (mem[p - mem_min].hh.lh == (-1073741824))
      flush_list(p);
    else
      --mem[p - mem_min].hh.lh;
  }
  void delete_glue_ref(halfword p) {
    if (mem[p - mem_min].hh.rh == (-1073741824))
      free_node(p, 4);
    else
      --mem[p - mem_min].hh.rh;
  }
  void flush_node_list(halfword p) {
    halfword q;
    while (p != (-1073741824)) {
      q = mem[p - mem_min].hh.rh;
      if (p >= hi_mem_min) {
        mem[p - mem_min].hh.rh = avail;
        avail = p;
      } else {
        switch (mem[p - mem_min].hh.U2.b0) {
        case 0:
        case 1:
        case 13:
          flush_node_list(mem[p - mem_min + 5].hh.rh);
          free_node(p, 7);
          goto _L30;
          break;
        case 2:
          free_node(p, 4);
          goto _L30;
          break;
        case 3:
          flush_node_list(mem[p - mem_min + 4].hh.lh);
          delete_glue_ref(mem[p - mem_min + 4].hh.rh);
          free_node(p, 5);
          goto _L30;
          break;
        case 8:
          switch (mem[p - mem_min].hh.U2.b1) {
          case 0:
            free_node(p, 3);
            break;
          case 1:
          case 3:
            delete_token_ref(mem[p - mem_min + 1].hh.rh);
            free_node(p, 2);
            goto _L30;
            break;
          case 2:
          case 4:
            free_node(p, 2);
            break;
          default:
            confusion(1294);
            break;
          }
          goto _L30;
          break;
        case 10:
          if (mem[mem[p - mem_min + 1].hh.lh - mem_min].hh.rh == (-1073741824))
            free_node(mem[p - mem_min + 1].hh.lh, 4);
          else
            --mem[mem[p - mem_min + 1].hh.lh - mem_min].hh.rh;
          if (mem[p - mem_min + 1].hh.rh != (-1073741824))
            flush_node_list(mem[p - mem_min + 1].hh.rh);
          break;
        case 11:
        case 9:
        case 12:
          // blank case
          break;
        case 6:
          flush_node_list(mem[p - mem_min + 1].hh.rh);
          break;
        case 4:
          delete_token_ref(mem[p - mem_min + 1].int_);
          break;
        case 7:
          flush_node_list(mem[p - mem_min + 1].hh.lh);
          flush_node_list(mem[p - mem_min + 1].hh.rh);
          break;
        case 5:
          flush_node_list(mem[p - mem_min + 1].int_);
          break;
        case 14:
          free_node(p, 3);
          goto _L30;
          break;
        case 15:
          flush_node_list(mem[p - mem_min + 1].hh.lh);
          flush_node_list(mem[p - mem_min + 1].hh.rh);
          flush_node_list(mem[p - mem_min + 2].hh.lh);
          flush_node_list(mem[p - mem_min + 2].hh.rh);
          free_node(p, 3);
          goto _L30;
          break;
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 27:
        case 26:
        case 29:
        case 28:
          if (mem[p - mem_min + 1].hh.rh >= 2)
            flush_node_list(mem[p - mem_min + 1].hh.lh);
          if (mem[p - mem_min + 2].hh.rh >= 2)
            flush_node_list(mem[p - mem_min + 2].hh.lh);
          if (mem[p - mem_min + 3].hh.rh >= 2)
            flush_node_list(mem[p - mem_min + 3].hh.lh);
          if (mem[p - mem_min].hh.U2.b0 == 24) {
            free_node(p, 5);
          } else if (mem[p - mem_min].hh.U2.b0 == 28)
            free_node(p, 5);
          else
            free_node(p, 4);
          goto _L30;
          break;
        case 30:
        case 31:
          free_node(p, 4);
          goto _L30;
          break;
        case 25:
          flush_node_list(mem[p - mem_min + 2].hh.lh);
          flush_node_list(mem[p - mem_min + 3].hh.lh);
          free_node(p, 6);
          goto _L30;
          break;
        default:
          confusion(353);
          break;
        }
        free_node(p, 2);
      _L30:;
      }
      p = q;
    }
  }
  halfword copy_node_list(halfword p) {
    halfword r;
    char words;
    halfword h = get_avail();
    halfword q = h;
    while (p != (-1073741824)) {
      words = 1;
      if (p >= hi_mem_min) {
        r = get_avail();
      } else {
        switch (mem[p - mem_min].hh.U2.b0) {
        case 0:
        case 1:
        case 13:
          r = get_node(7);
          mem[r - mem_min + 6] = mem[p - mem_min + 6];
          mem[r - mem_min + 5] = mem[p - mem_min + 5];
          mem[r - mem_min + 5].hh.rh =
              copy_node_list(mem[p - mem_min + 5].hh.rh);
          words = 5;
          break;
        case 2:
          r = get_node(4);
          words = 4;
          break;
        case 3:
          r = get_node(5);
          mem[r - mem_min + 4] = mem[p - mem_min + 4];
          ++mem[mem[p - mem_min + 4].hh.rh - mem_min].hh.rh;
          mem[r - mem_min + 4].hh.lh =
              copy_node_list(mem[p - mem_min + 4].hh.lh);
          words = 4;
          break;
        case 8:
          switch (mem[p - mem_min].hh.U2.b1) {
          case 0:
            r = get_node(3);
            words = 3;
            break;
          case 1:
          case 3:
            r = get_node(2);
            ++mem[mem[p - mem_min + 1].hh.rh - mem_min].hh.lh;
            words = 2;
            break;
          case 2:
          case 4:
            r = get_node(2);
            words = 2;
            break;
          default:
            confusion(1293);
            break;
          }
          break;
        case 10:
          r = get_node(2);
          ++mem[mem[p - mem_min + 1].hh.lh - mem_min].hh.rh;
          mem[r - mem_min + 1].hh.lh = mem[p - mem_min + 1].hh.lh;
          mem[r - mem_min + 1].hh.rh =
              copy_node_list(mem[p - mem_min + 1].hh.rh);
          break;
        case 11:
        case 9:
        case 12:
          r = get_node(2);
          words = 2;
          break;
        case 6:
          r = get_node(2);
          mem[r - mem_min + 1] = mem[p - mem_min + 1];
          mem[r - mem_min + 1].hh.rh =
              copy_node_list(mem[p - mem_min + 1].hh.rh);
          break;
        case 7:
          r = get_node(2);
          mem[r - mem_min + 1].hh.lh =
              copy_node_list(mem[p - mem_min + 1].hh.lh);
          mem[r - mem_min + 1].hh.rh =
              copy_node_list(mem[p - mem_min + 1].hh.rh);
          break;
        case 4:
          r = get_node(2);
          ++mem[mem[p - mem_min + 1].int_ - mem_min].hh.lh;
          words = 2;
          break;
        case 5:
          r = get_node(2);
          mem[r - mem_min + 1].int_ = copy_node_list(mem[p - mem_min + 1].int_);
          break;
        default:
          confusion(354);
          break;
        }
      }
      while (words > 0) {
        --words;
        mem[r + words - mem_min] = mem[p + words - mem_min];
      }
      mem[q - mem_min].hh.rh = r;
      q = r;
      p = mem[p - mem_min].hh.rh;
    }
    mem[q - mem_min].hh.rh = -1073741824;
    q = mem[h - mem_min].hh.rh;
    mem[h - mem_min].hh.rh = avail;
    avail = h;
    return q;
  }
  void print_mode(integer m) {
    if (m > 0) {
      switch (m / 101) {
      case 0:
        print(355);
        break;
      case 1:
        print(356);
        break;
      case 2:
        print(357);
        break;
      }
    } else if (!m) {
      print(358);
    } else {
      switch ((-m) / 101) {
      case 0:
        print(359);
        break;
      case 1:
        print(360);
        break;
      case 2:
        print(343);
        break;
      }
    }
    print(361);
  }
  void push_nest() {
    if (nest_ptr > max_nest_stack) {
      max_nest_stack = nest_ptr;
      if (nest_ptr == nest_size)
        overflow(362, nest_size);
    }
    nest[nest_ptr] = cur_list;
    ++nest_ptr;
    cur_list.head_field = get_avail();
    cur_list.tail_field = cur_list.head_field;
    cur_list.pg_field = 0;
    cur_list.ml_field = line;
  }
  void pop_nest() {
    mem[cur_list.head_field - mem_min].hh.rh = avail;
    avail = cur_list.head_field;
    --nest_ptr;
    cur_list = nest[nest_ptr];
  }
  void show_activities() {
    int p;
    short m;
    memory_word a;
    halfword q, r;
    integer t;
    nest[nest_ptr] = cur_list;
    print_nl(338);
    print_ln();
    for (p = nest_ptr; p >= 0; --p) {
      m = nest[p].mode_field;
      a = nest[p].aux_field;
      print_nl(363);
      print_mode(m);
      print(364);
      print_int(abs(nest[p].ml_field));
      if (m == 102) {
        if (nest[p].pg_field != 8585216) {
          print(365);
          print_int(nest[p].pg_field & 65535);
          print(366);
          print_int(nest[p].pg_field / 4194304);
          print_char(44);
          print_int((nest[p].pg_field / 65536) & 63);
          print_char(41);
        }
      }
      if (nest[p].ml_field < 0)
        print(367);
      if (!p) {
        if (mem_max - 2 != page_tail) {
          print_nl(979);
          if (output_active)
            print(980);
          show_box(mem[mem_max - mem_min - 2].hh.rh);
          if (page_contents > 0) {
            print_nl(981);
            print_totals();
            print_nl(982);
            print_scaled(page_so_far[0]);
            r = mem[mem_max - mem_min].hh.rh;
            while (r != mem_max) {
              print_ln();
              print_esc(330);
              t = mem[r - mem_min].hh.U2.b1;
              print_int(t);
              print(983);
              if (eqtb[t + 12218].int_ == 1000)
                t = mem[r - mem_min + 3].int_;
              else
                t = x_over_n(mem[r - mem_min + 3].int_, 1000) *
                    eqtb[t + 12218].int_;
              print_scaled(t);
              if (mem[r - mem_min].hh.U2.b0 == 1) {
                q = mem_max - 2;
                t = 0;
                do {
                  q = mem[q - mem_min].hh.rh;
                  if ((mem[q - mem_min].hh.U2.b0 == 3) &&
                      (mem[q - mem_min].hh.U2.b1 == mem[r - mem_min].hh.U2.b1))
                    ++t;
                } while (q != mem[r - mem_min + 1].hh.lh);
                print(984);
                print_int(t);
                print(985);
              }
              r = mem[r - mem_min].hh.rh;
            }
          }
        }
        if (mem[mem_max - mem_min - 1].hh.rh != (-1073741824))
          print_nl(368);
      }
      show_box(mem[nest[p].head_field - mem_min].hh.rh);
      switch (abs(m) / 101) {
      case 0:
        print_nl(369);
        if (a.int_ <= (-65536000))
          print(370);
        else
          print_scaled(a.int_);
        if (nest[p].pg_field) {
          print(371);
          print_int(nest[p].pg_field);
          print(372);
          if (nest[p].pg_field != 1)
            print_char(115);
        }
        break;
      case 1:
        print_nl(373);
        print_int(a.hh.lh);
        if (m > 0) {
          if (a.hh.rh > 0) {
            print(374);
            print_int(a.hh.rh);
          }
        }
        break;
      case 2:
        if (a.int_ != (-1073741824)) {
          print(375);
          show_box(a.int_);
        }
        break;
      }
    }
  }
  void print_param(integer n) {
    switch (n) {
    case 0:
      print_esc(420);
      break;
    case 1:
      print_esc(421);
      break;
    case 2:
      print_esc(422);
      break;
    case 3:
      print_esc(423);
      break;
    case 4:
      print_esc(424);
      break;
    case 5:
      print_esc(425);
      break;
    case 6:
      print_esc(426);
      break;
    case 7:
      print_esc(427);
      break;
    case 8:
      print_esc(428);
      break;
    case 9:
      print_esc(429);
      break;
    case 10:
      print_esc(430);
      break;
    case 11:
      print_esc(431);
      break;
    case 12:
      print_esc(432);
      break;
    case 13:
      print_esc(433);
      break;
    case 14:
      print_esc(434);
      break;
    case 15:
      print_esc(435);
      break;
    case 16:
      print_esc(436);
      break;
    case 17:
      print_esc(437);
      break;
    case 18:
      print_esc(438);
      break;
    case 19:
      print_esc(439);
      break;
    case 20:
      print_esc(440);
      break;
    case 21:
      print_esc(441);
      break;
    case 22:
      print_esc(442);
      break;
    case 23:
      print_esc(443);
      break;
    case 24:
      print_esc(444);
      break;
    case 25:
      print_esc(445);
      break;
    case 26:
      print_esc(446);
      break;
    case 27:
      print_esc(447);
      break;
    case 28:
      print_esc(448);
      break;
    case 29:
      print_esc(449);
      break;
    case 30:
      print_esc(450);
      break;
    case 31:
      print_esc(451);
      break;
    case 32:
      print_esc(452);
      break;
    case 33:
      print_esc(453);
      break;
    case 34:
      print_esc(454);
      break;
    case 35:
      print_esc(455);
      break;
    case 36:
      print_esc(456);
      break;
    case 37:
      print_esc(457);
      break;
    case 38:
      print_esc(458);
      break;
    case 39:
      print_esc(459);
      break;
    case 40:
      print_esc(460);
      break;
    case 41:
      print_esc(461);
      break;
    case 42:
      print_esc(462);
      break;
    case 43:
      print_esc(463);
      break;
    case 44:
      print_esc(464);
      break;
    case 45:
      print_esc(465);
      break;
    case 46:
      print_esc(466);
      break;
    case 47:
      print_esc(467);
      break;
    case 48:
      print_esc(468);
      break;
    case 49:
      print_esc(469);
      break;
    case 50:
      print_esc(470);
      break;
    case 51:
      print_esc(471);
      break;
    case 52:
      print_esc(472);
      break;
    case 53:
      print_esc(473);
      break;
    case 54:
      print_esc(474);
      break;
    default:
      print(475);
      break;
    }
  }
  void fix_date_and_time() {
    eqtb[12183].int_ = 720;
    eqtb[12184].int_ = 4;
    eqtb[12185].int_ = 7;
    eqtb[12186].int_ = 1776;
  }
  void begin_diagnostic() {
    old_setting = selector;
    if ((eqtb[12192].int_ > 0) || (selector != 19))
      return;
    --selector;
    if (!history)
      history = 1;
  }
  void end_diagnostic(bool blank_line) {
    print_nl(338);
    if (blank_line)
      print_ln();
    selector = old_setting;
  }
  void print_length_param(integer n) {
    switch (n) {
    case 0:
      print_esc(478);
      break;
    case 1:
      print_esc(479);
      break;
    case 2:
      print_esc(480);
      break;
    case 3:
      print_esc(481);
      break;
    case 4:
      print_esc(482);
      break;
    case 5:
      print_esc(483);
      break;
    case 6:
      print_esc(484);
      break;
    case 7:
      print_esc(485);
      break;
    case 8:
      print_esc(486);
      break;
    case 9:
      print_esc(487);
      break;
    case 10:
      print_esc(488);
      break;
    case 11:
      print_esc(489);
      break;
    case 12:
      print_esc(490);
      break;
    case 13:
      print_esc(491);
      break;
    case 14:
      print_esc(492);
      break;
    case 15:
      print_esc(493);
      break;
    case 16:
      print_esc(494);
      break;
    case 17:
      print_esc(495);
      break;
    case 18:
      print_esc(496);
      break;
    case 19:
      print_esc(497);
      break;
    case 20:
      print_esc(498);
      break;
    default:
      print(499);
      break;
    }
  }
  void print_cmd_chr(quarterword cmd, halfword chr_code) {
    switch (cmd) {
    case 1:
      print(557);
      print(chr_code);
      break;
    case 2:
      print(558);
      print(chr_code);
      break;
    case 3:
      print(559);
      print(chr_code);
      break;
    case 6:
      print(560);
      print(chr_code);
      break;
    case 7:
      print(561);
      print(chr_code);
      break;
    case 8:
      print(562);
      print(chr_code);
      break;
    case 9:
      print(563);
      break;
    case 10:
      print(564);
      print(chr_code);
      break;
    case 11:
      print(565);
      print(chr_code);
      break;
    case 12:
      print(566);
      print(chr_code);
      break;
    case 75:
    case 76:
      if (chr_code < 9800) {
        print_skip_param(chr_code - 9782);
      } else if (chr_code < 10056) {
        print_esc(395);
        print_int(chr_code - 9800);
      } else {
        print_esc(396);
        print_int(chr_code - 10056);
      }
      break;
    case 72:
      if (chr_code >= 10322) {
        print_esc(407);
        print_int(chr_code - 10322);
      } else {
        switch (chr_code) {
        case 10313:
          print_esc(398);
          break;
        case 10314:
          print_esc(399);
          break;
        case 10315:
          print_esc(400);
          break;
        case 10316:
          print_esc(401);
          break;
        case 10317:
          print_esc(402);
          break;
        case 10318:
          print_esc(403);
          break;
        case 10319:
          print_esc(404);
          break;
        case 10320:
          print_esc(405);
          break;
        default:
          print_esc(406);
          break;
        }
      }
      break;
    case 73:
      if (chr_code < 12218) {
        print_param(chr_code - 12163);
      } else {
        print_esc(476);
        print_int(chr_code - 12218);
      }
      break;
    case 74:
      if (chr_code < 12751) {
        print_length_param(chr_code - 12730);
      } else {
        print_esc(500);
        print_int(chr_code - 12751);
      }
      break;
    case 45:
      print_esc(508);
      break;
    case 90:
      print_esc(509);
      break;
    case 40:
      print_esc(510);
      break;
    case 41:
      print_esc(511);
      break;
    case 77:
      print_esc(519);
      break;
    case 61:
      print_esc(512);
      break;
    case 42:
      print_esc(531);
      break;
    case 16:
      print_esc(513);
      break;
    case 107:
      print_esc(504);
      break;
    case 88:
      print_esc(518);
      break;
    case 15:
      print_esc(514);
      break;
    case 92:
      print_esc(515);
      break;
    case 67:
      print_esc(505);
      break;
    case 62:
      print_esc(516);
      break;
    case 64:
      print_esc(32);
      break;
    case 102:
      print_esc(517);
      break;
    case 32:
      print_esc(520);
      break;
    case 36:
      print_esc(521);
      break;
    case 39:
      print_esc(522);
      break;
    case 37:
      print_esc(330);
      break;
    case 44:
      print_esc(47);
      break;
    case 18:
      print_esc(351);
      break;
    case 46:
      print_esc(523);
      break;
    case 17:
      print_esc(524);
      break;
    case 54:
      print_esc(525);
      break;
    case 91:
      print_esc(526);
      break;
    case 34:
      print_esc(527);
      break;
    case 65:
      print_esc(528);
      break;
    case 103:
      print_esc(529);
      break;
    case 55:
      print_esc(335);
      break;
    case 63:
      print_esc(530);
      break;
    case 66:
      print_esc(533);
      break;
    case 96:
      print_esc(534);
      break;
    case 0:
      print_esc(535);
      break;
    case 98:
      print_esc(536);
      break;
    case 80:
      print_esc(532);
      break;
    case 84:
      print_esc(408);
      break;
    case 109:
      print_esc(537);
      break;
    case 71:
      print_esc(407);
      break;
    case 38:
      print_esc(352);
      break;
    case 33:
      print_esc(538);
      break;
    case 56:
      print_esc(539);
      break;
    case 35:
      print_esc(540);
      break;
    case 13:
      print_esc(597);
      break;
    case 104:
      if (!chr_code)
        print_esc(629);
      else
        print_esc(630);
      break;
    case 110:
      switch (chr_code) {
      case 1:
        print_esc(632);
        break;
      case 2:
        print_esc(633);
        break;
      case 3:
        print_esc(634);
        break;
      case 4:
        print_esc(635);
        break;
      default:
        print_esc(631);
        break;
      }
      break;
    case 89:
      if (!chr_code) {
        print_esc(476);
      } else if (chr_code == 1) {
        print_esc(500);
      } else if (chr_code == 2)
        print_esc(395);
      else
        print_esc(396);
      break;
    case 79:
      if (chr_code == 1)
        print_esc(669);
      else
        print_esc(668);
      break;
    case 82:
      if (!chr_code)
        print_esc(670);
      else
        print_esc(671);
      break;
    case 83:
      if (chr_code == 1) {
        print_esc(672);
      } else if (chr_code == 3)
        print_esc(673);
      else
        print_esc(674);
      break;
    case 70:
      switch (chr_code) {
      case 0:
        print_esc(675);
        break;
      case 1:
        print_esc(676);
        break;
      case 2:
        print_esc(677);
        break;
      case 3:
        print_esc(678);
        break;
      default:
        print_esc(679);
        break;
      }
      break;
    case 108:
      switch (chr_code) {
      case 0:
        print_esc(735);
        break;
      case 1:
        print_esc(736);
        break;
      case 2:
        print_esc(737);
        break;
      case 3:
        print_esc(738);
        break;
      case 4:
        print_esc(739);
        break;
      default:
        print_esc(740);
        break;
      }
      break;
    case 105:
      switch (chr_code) {
      case 1:
        print_esc(757);
        break;
      case 2:
        print_esc(758);
        break;
      case 3:
        print_esc(759);
        break;
      case 4:
        print_esc(760);
        break;
      case 5:
        print_esc(761);
        break;
      case 6:
        print_esc(762);
        break;
      case 7:
        print_esc(763);
        break;
      case 8:
        print_esc(764);
        break;
      case 9:
        print_esc(765);
        break;
      case 10:
        print_esc(766);
        break;
      case 11:
        print_esc(767);
        break;
      case 12:
        print_esc(768);
        break;
      case 13:
        print_esc(769);
        break;
      case 14:
        print_esc(770);
        break;
      case 15:
        print_esc(771);
        break;
      case 16:
        print_esc(772);
        break;
      default:
        print_esc(756);
        break;
      }
      break;
    case 106:
      if (chr_code == 2) {
        print_esc(773);
      } else if (chr_code == 4)
        print_esc(774);
      else
        print_esc(775);
      break;
    case 4:
      if (chr_code == 256) {
        print_esc(897);
      } else {
        print(901);
        print(chr_code);
      }
      break;
    case 5:
      if (chr_code == 257)
        print_esc(898);
      else
        print_esc(899);
      break;
    case 81:
      switch (chr_code) {
      case 0:
        print_esc(969);
        break;
      case 1:
        print_esc(970);
        break;
      case 2:
        print_esc(971);
        break;
      case 3:
        print_esc(972);
        break;
      case 4:
        print_esc(973);
        break;
      case 5:
        print_esc(974);
        break;
      case 6:
        print_esc(975);
        break;
      default:
        print_esc(976);
        break;
      }
      break;
    case 14:
      if (chr_code == 1)
        print_esc(1025);
      else
        print_esc(1024);
      break;
    case 26:
      switch (chr_code) {
      case 4:
        print_esc(1026);
        break;
      case 0:
        print_esc(1027);
        break;
      case 1:
        print_esc(1028);
        break;
      case 2:
        print_esc(1029);
        break;
      default:
        print_esc(1030);
        break;
      }
      break;
    case 27:
      switch (chr_code) {
      case 4:
        print_esc(1031);
        break;
      case 0:
        print_esc(1032);
        break;
      case 1:
        print_esc(1033);
        break;
      case 2:
        print_esc(1034);
        break;
      default:
        print_esc(1035);
        break;
      }
      break;
    case 28:
      print_esc(336);
      break;
    case 29:
      print_esc(340);
      break;
    case 30:
      print_esc(342);
      break;
    case 21:
      if (chr_code == 1)
        print_esc(1053);
      else
        print_esc(1054);
      break;
    case 22:
      if (chr_code == 1)
        print_esc(1055);
      else
        print_esc(1056);
      break;
    case 20:
      switch (chr_code) {
      case 0:
        print_esc(409);
        break;
      case 1:
        print_esc(1057);
        break;
      case 2:
        print_esc(1058);
        break;
      case 3:
        print_esc(964);
        break;
      case 4:
        print_esc(1059);
        break;
      case 5:
        print_esc(966);
        break;
      default:
        print_esc(1060);
        break;
      }
      break;
    case 31:
      if (chr_code == 100) {
        print_esc(1062);
      } else if (chr_code == 101) {
        print_esc(1063);
      } else if (chr_code == 102)
        print_esc(1064);
      else
        print_esc(1061);
      break;
    case 43:
      if (!chr_code)
        print_esc(1080);
      else
        print_esc(1079);
      break;
    case 25:
      if (chr_code == 10) {
        print_esc(1091);
      } else if (chr_code == 11)
        print_esc(1090);
      else
        print_esc(1089);
      break;
    case 23:
      if (chr_code == 1)
        print_esc(1093);
      else
        print_esc(1092);
      break;
    case 24:
      if (chr_code == 1)
        print_esc(1095);
      else
        print_esc(1094);
      break;
    case 47:
      if (chr_code == 1)
        print_esc(45);
      else
        print_esc(349);
      break;
    case 48:
      if (chr_code == 1)
        print_esc(1127);
      else
        print_esc(1126);
      break;
    case 50:
      switch (chr_code) {
      case 16:
        print_esc(865);
        break;
      case 17:
        print_esc(866);
        break;
      case 18:
        print_esc(867);
        break;
      case 19:
        print_esc(868);
        break;
      case 20:
        print_esc(869);
        break;
      case 21:
        print_esc(870);
        break;
      case 22:
        print_esc(871);
        break;
      case 23:
        print_esc(872);
        break;
      case 26:
        print_esc(874);
        break;
      default:
        print_esc(873);
        break;
      }
      break;
    case 51:
      if (chr_code == 1) {
        print_esc(877);
      } else if (chr_code == 2)
        print_esc(878);
      else
        print_esc(1128);
      break;
    case 53:
      print_style(chr_code);
      break;
    case 52:
      switch (chr_code) {
      case 1:
        print_esc(1147);
        break;
      case 2:
        print_esc(1148);
        break;
      case 3:
        print_esc(1149);
        break;
      case 4:
        print_esc(1150);
        break;
      case 5:
        print_esc(1151);
        break;
      default:
        print_esc(1146);
        break;
      }
      break;
    case 49:
      if (chr_code == 30)
        print_esc(875);
      else
        print_esc(876);
      break;
    case 93:
      if (chr_code == 1) {
        print_esc(1170);
      } else if (chr_code == 2)
        print_esc(1171);
      else
        print_esc(1172);
      break;
    case 97:
      if (!chr_code) {
        print_esc(1173);
      } else if (chr_code == 1) {
        print_esc(1174);
      } else if (chr_code == 2)
        print_esc(1175);
      else
        print_esc(1176);
      break;
    case 94:
      if (chr_code)
        print_esc(1191);
      else
        print_esc(1190);
      break;
    case 95:
      switch (chr_code) {
      case 0:
        print_esc(1192);
        break;
      case 1:
        print_esc(1193);
        break;
      case 2:
        print_esc(1194);
        break;
      case 3:
        print_esc(1195);
        break;
      case 4:
        print_esc(1196);
        break;
      case 5:
        print_esc(1197);
        break;
      default:
        print_esc(1198);
        break;
      }
      break;
    case 68:
      print_esc(513);
      print_hex(chr_code);
      break;
    case 69:
      print_esc(524);
      print_hex(chr_code);
      break;
    case 85:
      if (chr_code == 10883) {
        print_esc(415);
      } else if (chr_code == 11907) {
        print_esc(419);
      } else if (chr_code == 11139) {
        print_esc(416);
      } else if (chr_code == 11395) {
        print_esc(417);
      } else if (chr_code == 11651)
        print_esc(418);
      else
        print_esc(477);
      break;
    case 86:
      print_size(chr_code - 10835);
      break;
    case 99:
      if (chr_code == 1)
        print_esc(952);
      else
        print_esc(940);
      break;
    case 78:
      if (!chr_code)
        print_esc(1216);
      else
        print_esc(1217);
      break;
    case 87:
      print(1225);
      slow_print(font_name[chr_code]);
      if (font_size[chr_code] != font_dsize[chr_code]) {
        print(741);
        print_scaled(font_size[chr_code]);
        print(397);
      }
      break;
    case 100:
      switch (chr_code) {
      case 0:
        print_esc(274);
        break;
      case 1:
        print_esc(275);
        break;
      case 2:
        print_esc(276);
        break;
      default:
        print_esc(1226);
        break;
      }
      break;
    case 60:
      if (!chr_code)
        print_esc(1228);
      else
        print_esc(1227);
      break;
    case 58:
      if (!chr_code)
        print_esc(1229);
      else
        print_esc(1230);
      break;
    case 57:
      if (chr_code == 11139)
        print_esc(1236);
      else
        print_esc(1237);
      break;
    case 19:
      switch (chr_code) {
      case 1:
        print_esc(1239);
        break;
      case 2:
        print_esc(1240);
        break;
      case 3:
        print_esc(1241);
        break;
      default:
        print_esc(1238);
        break;
      }
      break;
    case 101:
      print(1248);
      break;
    case 111:
      print(1249);
      break;
    case 112:
      print_esc(1250);
      break;
    case 113:
      print_esc(1251);
      break;
    case 114:
      print_esc(1170);
      print_esc(1251);
      break;
    case 115:
      print_esc(1252);
      break;
    case 59:
      switch (chr_code) {
      case 0:
        print_esc(1284);
        break;
      case 1:
        print_esc(594);
        break;
      case 2:
        print_esc(1285);
        break;
      case 3:
        print_esc(1286);
        break;
      case 4:
        print_esc(1287);
        break;
      case 5:
        print_esc(1288);
        break;
      default:
        print(1289);
        break;
      }
      break;
    default:
      print(567);
      break;
    }
  }
  halfword id_lookup(integer j, integer l) {
    integer d;
    halfword p, k;
    integer h = buffer[j];
    for (k = j + 1; k <= (j + l - 1); ++k) {
      h += h + buffer[k];
      while (h >= 7649)
        h -= 7649;
    }
    p = h + 514;
    while (true) {
      if (hash[p - 514].rh > 0) {
        if (str_start[hash[p - 514].rh + 1] - str_start[hash[p - 514].rh] ==
            l) {
          if (str_eq_buf(hash[p - 514].rh, j))
            goto _L40;
        }
      }
      if (!hash[p - 514].lh) {
        if (no_new_control_sequence) {
          p = 9781;
        } else {
          if (hash[p - 514].rh > 0) {
            do {
              if (hash_used == 514)
                overflow(503, 9000);
              --hash_used;
            } while (hash[hash_used - 514].rh);
            hash[p - 514].lh = hash_used;
            p = hash_used;
          }
          if (pool_ptr + l > pool_size)
            overflow(257, pool_size - init_pool_ptr);
          d = pool_ptr - str_start[str_ptr];
          while (pool_ptr > str_start[str_ptr]) {
            --pool_ptr;
            str_pool[pool_ptr + l] = str_pool[pool_ptr];
          }
          for (k = j; k <= (j + l - 1); ++k) {
            str_pool[pool_ptr] = buffer[k];
            ++pool_ptr;
          }
          hash[p - 514].rh = make_string();
          pool_ptr += d;
        }
        goto _L40;
      }
      p = hash[p - 514].lh;
    }
  _L40:
    return p;
  }
  void primitive(str_number s, quarterword c, halfword o) {
    pool_pointer k;
    small_number j, l;
    if (s < 256) {
      cur_val = s + 257;
    } else {
      k = str_start[s];
      l = str_start[s + 1] - k;
      for (j = 0; j <= (l - 1); ++j)
        buffer[j] = str_pool[k + j];
      cur_val = id_lookup(0, l);
      --str_ptr;
      pool_ptr = str_start[str_ptr];
      hash[cur_val - 514].rh = s;
    }
    eqtb[cur_val].hh.U2.b1 = 1;
    eqtb[cur_val].hh.U2.b0 = c;
    eqtb[cur_val].hh.rh = o;
  }
  void new_save_level(group_code c) {
    if (save_ptr > max_save_stack) {
      max_save_stack = save_ptr;
      if (max_save_stack > (save_size - 6))
        overflow(541, save_size);
    }
    save_stack[save_ptr].hh.U2.b0 = 3;
    save_stack[save_ptr].hh.U2.b1 = cur_group;
    save_stack[save_ptr].hh.rh = cur_boundary;
    if (cur_level == 65535)
      overflow(542, 65535);
    cur_boundary = save_ptr;
    ++cur_level;
    ++save_ptr;
    cur_group = c;
  }
  void eq_destroy(memory_word w) {
    halfword q;
    switch (w.hh.U2.b0) {
    case 111:
    case 112:
    case 113:
    case 114:
      delete_token_ref(w.hh.rh);
      break;
    case 117:
      delete_glue_ref(w.hh.rh);
      break;
    case 118:
      q = w.hh.rh;
      if (q != (-1073741824))
        free_node(q, mem[q - mem_min].hh.lh + mem[q - mem_min].hh.lh + 1);
      break;
    case 119:
      flush_node_list(w.hh.rh);
      break;
    default:
      break;
    }
  }
  void eq_save(halfword p, quarterword l) {
    if (save_ptr > max_save_stack) {
      max_save_stack = save_ptr;
      if (max_save_stack > (save_size - 6))
        overflow(541, save_size);
    }
    if (!l) {
      save_stack[save_ptr].hh.U2.b0 = 1;
    } else {
      save_stack[save_ptr] = eqtb[p];
      ++save_ptr;
      save_stack[save_ptr].hh.U2.b0 = 0;
    }
    save_stack[save_ptr].hh.U2.b1 = l;
    save_stack[save_ptr].hh.rh = p;
    ++save_ptr;
  }
  void eq_define(halfword p, quarterword t, halfword e) {
    if (eqtb[p].hh.U2.b1 == cur_level) {
      eq_destroy(eqtb[p]);
    } else if (cur_level > 1)
      eq_save(p, eqtb[p].hh.U2.b1);
    eqtb[p].hh.U2.b1 = cur_level;
    eqtb[p].hh.U2.b0 = t;
    eqtb[p].hh.rh = e;
  }
  void eq_word_define(halfword p, integer w) {
    if (xeq_level[p - 12163] != cur_level) {
      eq_save(p, xeq_level[p - 12163]);
      xeq_level[p - 12163] = cur_level;
    }
    eqtb[p].int_ = w;
  }
  void geq_define(halfword p, quarterword t, halfword e) {
    eq_destroy(eqtb[p]);
    eqtb[p].hh.U2.b1 = 1;
    eqtb[p].hh.U2.b0 = t;
    eqtb[p].hh.rh = e;
  }
  void geq_word_define(halfword p, integer w) {
    eqtb[p].int_ = w;
    xeq_level[p - 12163] = 1;
  }
  void save_for_after(halfword t) {
    if (cur_level <= 1)
      return;
    if (save_ptr > max_save_stack) {
      max_save_stack = save_ptr;
      if (max_save_stack > (save_size - 6))
        overflow(541, save_size);
    }
    save_stack[save_ptr].hh.U2.b0 = 2;
    save_stack[save_ptr].hh.U2.b1 = 0;
    save_stack[save_ptr].hh.rh = t;
    ++save_ptr;
  }
  void unsave() {
    halfword p;
    quarterword l;
    halfword t;
    if (cur_level <= 1) {
      confusion(543);
      return;
    }
    --cur_level;
    while (true) {
      --save_ptr;
      if (save_stack[save_ptr].hh.U2.b0 == 3)
        goto _L30;
      p = save_stack[save_ptr].hh.rh;
      if (save_stack[save_ptr].hh.U2.b0 == 2) {
        t = cur_tok;
        cur_tok = p;
        back_input();
        cur_tok = t;
        continue;
      }
      if (!save_stack[save_ptr].hh.U2.b0) {
        l = save_stack[save_ptr].hh.U2.b1;
        --save_ptr;
      } else {
        save_stack[save_ptr] = eqtb[9781];
      }
      if (p < 12163) {
        if (eqtb[p].hh.U2.b1 == 1) {
          eq_destroy(save_stack[save_ptr]);
        } else {
          eq_destroy(eqtb[p]);
          eqtb[p] = save_stack[save_ptr];
        }
      } else if (xeq_level[p - 12163] != 1) {
        eqtb[p] = save_stack[save_ptr];
        xeq_level[p - 12163] = l;
      }
    }
  _L30:
    cur_group = save_stack[save_ptr].hh.U2.b1;
    cur_boundary = save_stack[save_ptr].hh.rh;
  }
  void prepare_mag() {
    if ((mag_set > 0) && (eqtb[12180].int_ != mag_set)) {
      print_nl(262);
      print(547);
      print_int(eqtb[12180].int_);
      print(548);
      print_nl(549);
      help_ptr = 2;
      help_line[1] = 550;
      help_line[0] = 551;
      int_error(mag_set);
      geq_word_define(12180, mag_set);
    }
    if ((eqtb[12180].int_ <= 0) || (eqtb[12180].int_ > 32768)) {
      print_nl(262);
      print(552);
      help_ptr = 1;
      help_line[0] = 553;
      int_error(eqtb[12180].int_);
      geq_word_define(12180, 1000);
    }
    mag_set = eqtb[12180].int_;
  }
  void token_show(halfword p) {
    if (p != (-1073741824))
      show_token_list(mem[p - mem_min].hh.rh, -1073741824, 10000000);
  }
  void print_meaning() {
    print_cmd_chr(cur_cmd, cur_chr);
    if (cur_cmd >= 111) {
      print_char(58);
      print_ln();
      token_show(cur_chr);
      return;
    }
    if (cur_cmd != 110)
      return;
    print_char(58);
    print_ln();
    token_show(cur_mark[cur_chr]);
  }
  void show_cur_cmd_chr() {
    begin_diagnostic();
    print_nl(123);
    if (cur_list.mode_field != shown_mode) {
      print_mode(cur_list.mode_field);
      print(568);
      shown_mode = cur_list.mode_field;
    }
    print_cmd_chr(cur_cmd, cur_chr);
    print_char(125);
    end_diagnostic(false);
  }
  void show_context() {
    char old_setting;
    integer nn = -1, m, p, q;
    bool bottom_line = false;
    int i, j, l, n, N1;
    base_ptr = input_ptr;
    input_stack[base_ptr] = cur_input;
    while (true) {
      cur_input = input_stack[base_ptr];
      if (cur_input.state_field) {
        if ((cur_input.name_field > 17) || (!base_ptr))
          bottom_line = true;
      }
      if ((base_ptr == input_ptr) || bottom_line || (nn < eqtb[12217].int_)) {
        if ((base_ptr == input_ptr) || cur_input.state_field ||
            (cur_input.index_field != 3) ||
            (cur_input.loc_field != (-1073741824))) {
          tally = 0;
          old_setting = selector;
          if (cur_input.state_field) {
            if (cur_input.name_field <= 17) {
              if (!cur_input.name_field) {
                if (!base_ptr)
                  print_nl(574);
                else
                  print_nl(575);
              } else {
                print_nl(576);
                if (cur_input.name_field == 17)
                  print_char(42);
                else
                  print_int(cur_input.name_field - 1);
                print_char(62);
              }
            } else {
              print_nl(577);
              print_int(line);
            }
            print_char(32);
            l = tally;
            tally = 0;
            selector = 20;
            trick_count = 1000000;
            if (buffer[cur_input.limit_field] == eqtb[12211].int_)
              j = cur_input.limit_field;
            else
              j = cur_input.limit_field + 1;
            if (j > 0) {
              for (i = cur_input.start_field; i <= (j - 1); ++i) {
                if (i == cur_input.loc_field) {
                  first_count = tally;
                  trick_count = tally + error_line - half_error_line + 1;
                  if (trick_count < error_line)
                    trick_count = error_line;
                }
                print(buffer[i]);
              }
            }
          } else {
            switch (cur_input.index_field) {
            case 0:
              print_nl(578);
              break;
            case 1:
            case 2:
              print_nl(579);
              break;
            case 3:
              if (cur_input.loc_field == (-1073741824))
                print_nl(580);
              else
                print_nl(581);
              break;
            case 4:
              print_nl(582);
              break;
            case 5:
              print_ln();
              print_cs(cur_input.name_field);
              break;
            case 6:
              print_nl(583);
              break;
            case 7:
              print_nl(584);
              break;
            case 8:
              print_nl(585);
              break;
            case 9:
              print_nl(586);
              break;
            case 10:
              print_nl(587);
              break;
            case 11:
              print_nl(588);
              break;
            case 12:
              print_nl(589);
              break;
            case 13:
              print_nl(590);
              break;
            case 14:
              print_nl(591);
              break;
            case 15:
              print_nl(592);
              break;
            default:
              print_nl(63);
              break;
            }
            l = tally;
            tally = 0;
            selector = 20;
            trick_count = 1000000;
            if (cur_input.index_field < 5)
              show_token_list(cur_input.start_field, cur_input.loc_field,
                              100000);
            else
              show_token_list(mem[cur_input.start_field - mem_min].hh.rh,
                              cur_input.loc_field, 100000);
          }
          selector = old_setting;
          if (trick_count == 1000000) {
            first_count = tally;
            trick_count = tally + error_line - half_error_line + 1;
            if (trick_count < error_line)
              trick_count = error_line;
          }
          if (tally < trick_count)
            m = tally - first_count;
          else
            m = trick_count - first_count;
          if (l + first_count <= half_error_line) {
            p = 0;
            n = l + first_count;
          } else {
            print(277);
            p = l + first_count - half_error_line + 3;
            n = half_error_line;
          }
          for (N1 = first_count, q = p; q < N1; ++q)
            print_char(trick_buf[q % error_line]);
          print_ln();
          for (q = 1; q <= n; ++q)
            print_char(32);
          if (m + n <= error_line)
            p = first_count + m;
          else
            p = first_count + error_line - n - 3;
          for (q = first_count; q < p; ++q)
            print_char(trick_buf[q % error_line]);
          if (m + n > error_line)
            print(277);
          ++nn;
        }
      } else if (nn == eqtb[12217].int_) {
        print_nl(277);
        ++nn;
      }
      if (bottom_line)
        goto _L30;
      --base_ptr;
    }
  _L30:
    cur_input = input_stack[input_ptr];
  }
  void begin_token_list(halfword p, quarterword t) {
    if (input_ptr > max_in_stack) {
      max_in_stack = input_ptr;
      if (input_ptr == stack_size)
        overflow(593, stack_size);
    }
    input_stack[input_ptr] = cur_input;
    ++input_ptr;
    cur_input.state_field = 0;
    cur_input.start_field = p;
    cur_input.index_field = t;
    if (t < 5) {
      cur_input.loc_field = p;
      return;
    }
    ++mem[p - mem_min].hh.lh;
    if (t == 5) {
      cur_input.limit_field = param_ptr;
      return;
    }
    cur_input.loc_field = mem[p - mem_min].hh.rh;
    if (eqtb[12193].int_ <= 1)
      return;
    begin_diagnostic();
    print_nl(338);
    switch (t) {
    case 14:
      print_esc(351);
      break;
    case 15:
      print_esc(594);
      break;
    default:
      print_cmd_chr(72, t + 10307);
      break;
    }
    print(556);
    token_show(p);
    end_diagnostic(false);
  }
  void end_token_list() {
    if (cur_input.index_field >= 3) {
      if (cur_input.index_field <= 4) {
        flush_list(cur_input.start_field);
      } else {
        delete_token_ref(cur_input.start_field);
        if (cur_input.index_field == 5) {
          while (param_ptr > cur_input.limit_field) {
            --param_ptr;
            flush_list(param_stack[param_ptr]);
          }
        }
      }
    } else if (cur_input.index_field == 1) {
      if (align_state > 500000)
        align_state = 0;
      else
        fatal_error(595);
    }
    --input_ptr;
    cur_input = input_stack[input_ptr];
    if (interrupt)
      pause_for_instructions();
  }
  void back_input() {
    halfword p;
    while ((!cur_input.state_field) && (cur_input.loc_field == (-1073741824)) &&
           (cur_input.index_field != 2))
      end_token_list();
    p = get_avail();
    mem[p - mem_min].hh.lh = cur_tok;
    if (cur_tok < 768) {
      if (cur_tok < 512)
        --align_state;
      else
        ++align_state;
    }
    if (input_ptr > max_in_stack) {
      max_in_stack = input_ptr;
      if (input_ptr == stack_size)
        overflow(593, stack_size);
    }
    input_stack[input_ptr] = cur_input;
    ++input_ptr;
    cur_input.state_field = 0;
    cur_input.start_field = p;
    cur_input.index_field = 3;
    cur_input.loc_field = p;
  }
  void back_error() {
    OK_to_interrupt = false;
    back_input();
    OK_to_interrupt = true;
    error();
  }
  void ins_error() {
    OK_to_interrupt = false;
    back_input();
    cur_input.index_field = 4;
    OK_to_interrupt = true;
    error();
  }
  void begin_file_reading() {
    if (in_open == max_in_open)
      overflow(596, max_in_open);
    if (first == buf_size)
      overflow(256, buf_size);
    ++in_open;
    if (input_ptr > max_in_stack) {
      max_in_stack = input_ptr;
      if (input_ptr == stack_size)
        overflow(593, stack_size);
    }
    input_stack[input_ptr] = cur_input;
    ++input_ptr;
    cur_input.index_field = in_open;
    line_stack[cur_input.index_field] = line;
    cur_input.start_field = first;
    cur_input.state_field = 1;
    cur_input.name_field = 0;
  }
  void end_file_reading() {
    first = cur_input.start_field;
    line = line_stack[cur_input.index_field];
    if (cur_input.name_field > 17)
      a_close(input_file[cur_input.index_field]);
    --input_ptr;
    cur_input = input_stack[input_ptr];
    --in_open;
  }
  void clear_for_error_prompt() {
    while (cur_input.state_field && (!cur_input.name_field) &&
           (input_ptr > 0) && (cur_input.loc_field > cur_input.limit_field))
      end_file_reading();
    print_ln();
    break_in(term_in, true);
  }
  void check_outer_validity() {
    halfword p, q;
    if (!scanner_status)
      return;
    deletions_allowed = false;
    if (cur_cs) {
      if ((!cur_input.state_field) || (cur_input.name_field < 1) ||
          (cur_input.name_field > 17)) {
        p = get_avail();
        mem[p - mem_min].hh.lh = cur_cs + 4095;
        begin_token_list(p, 3);
      }
      cur_cmd = 10;
      cur_chr = 32;
    }
    if (scanner_status > 1) {
      runaway();
      if (!cur_cs) {
        print_nl(262);
        print(604);
      } else {
        cur_cs = 0;
        print_nl(262);
        print(605);
      }
      print(606);
      p = get_avail();
      switch (scanner_status) {
      case 2:
        print(570);
        mem[p - mem_min].hh.lh = 637;
        break;
      case 3:
        print(612);
        mem[p - mem_min].hh.lh = par_token;
        long_state = 113;
        break;
      case 4:
        print(572);
        mem[p - mem_min].hh.lh = 637;
        q = p;
        p = get_avail();
        mem[p - mem_min].hh.rh = q;
        mem[p - mem_min].hh.lh = 13610;
        align_state = -1000000;
        break;
      case 5:
        print(573);
        mem[p - mem_min].hh.lh = 637;
        break;
      }
      begin_token_list(p, 4);
      print(607);
      sprint_cs(warning_index);
      help_ptr = 4;
      help_line[3] = 608;
      help_line[2] = 609;
      help_line[1] = 610;
      help_line[0] = 611;
      error();
    } else {
      print_nl(262);
      print(598);
      print_cmd_chr(105, cur_if);
      print(599);
      print_int(skip_line);
      help_ptr = 3;
      help_line[2] = 600;
      help_line[1] = 601;
      help_line[0] = 602;
      if (cur_cs)
        cur_cs = 0;
      else
        help_line[2] = 603;
      cur_tok = 13613;
      ins_error();
    }
    deletions_allowed = true;
  }
  void get_next() {
    int k;
    halfword t;
    char cat;
    ASCII_code c, cc;
    char d;
  _L20:
    cur_cs = 0;
    if (cur_input.state_field) {
    _L25:
      if (cur_input.loc_field > cur_input.limit_field) {
        cur_input.state_field = 33;
        if (cur_input.name_field > 17) {
          ++line;
          first = cur_input.start_field;
          if (!force_eof) {
            if (input_ln(input_file[cur_input.index_field], true))
              firm_up_the_line();
            else
              force_eof = true;
          }
          if (force_eof) {
            print_char(41);
            --open_parens;
            fflush(term_out);
            errno = 0;
            force_eof = false;
            end_file_reading();
            check_outer_validity();
            goto _L20;
          }
          if (((unsigned)eqtb[12211].int_) > 255)
            --cur_input.limit_field;
          else
            buffer[cur_input.limit_field] = eqtb[12211].int_;
          first = cur_input.limit_field + 1;
          cur_input.loc_field = cur_input.start_field;
        } else {
          if (cur_input.name_field) {
            cur_cmd = 0;
            cur_chr = 0;
            goto _L10;
          }
          if (input_ptr > 0) {
            end_file_reading();
            goto _L20;
          }
          if (selector < 18)
            open_log_file();
          if (interaction > 1) {
            if (((unsigned)eqtb[12211].int_) > 255)
              ++cur_input.limit_field;
            if (cur_input.limit_field == cur_input.start_field)
              print_nl(616);
            print_ln();
            first = cur_input.start_field;
            print(42);
            term_input();
            cur_input.limit_field = last;
            if (((unsigned)eqtb[12211].int_) > 255)
              --cur_input.limit_field;
            else
              buffer[cur_input.limit_field] = eqtb[12211].int_;
            first = cur_input.limit_field + 1;
            cur_input.loc_field = cur_input.start_field;
          } else {
            fatal_error(617);
          }
        }
        if (interrupt)
          pause_for_instructions();
        goto _L25;
      }
      cur_chr = buffer[cur_input.loc_field];
      ++cur_input.loc_field;
    _L21:
      cur_cmd = eqtb[cur_chr + 10883].hh.rh;
      switch (cur_input.state_field + cur_cmd) {
      case 10:
      case 26:
      case 42:
      case 27:
      case 43:
        goto _L25;
        break;
      case 1:
      case 17:
      case 33:
        if (cur_input.loc_field > cur_input.limit_field) {
          cur_cs = 513;
        } else {
        _L26:
          k = cur_input.loc_field;
          cur_chr = buffer[k];
          cat = eqtb[cur_chr + 10883].hh.rh;
          ++k;
          if (cat == 11) {
            cur_input.state_field = 17;
          } else if (cat == 10)
            cur_input.state_field = 17;
          else
            cur_input.state_field = 1;
          if ((cat == 11) && (k <= cur_input.limit_field)) {
            do {
              cur_chr = buffer[k];
              cat = eqtb[cur_chr + 10883].hh.rh;
              ++k;
            } while ((cat == 11) && (k <= cur_input.limit_field));
            if (buffer[k] == cur_chr) {
              if (cat == 7) {
                if (k < cur_input.limit_field) {
                  c = buffer[k + 1];
                  if (c < 128) {
                    d = 2;
                    if (((c >= 48) && (c <= 57)) || ((c >= 97) && (c <= 102))) {
                      if (k + 2 <= cur_input.limit_field) {
                        cc = buffer[k + 2];
                        if (((cc >= 48) && (cc <= 57)) ||
                            ((cc >= 97) && (cc <= 102)))
                          ++d;
                      }
                    }
                    if (d > 2) {
                      if (c <= 57)
                        cur_chr = c - 48;
                      else
                        cur_chr = c - 87;
                      if (cc <= 57)
                        cur_chr = (cur_chr * 16) + cc - 48;
                      else
                        cur_chr = (cur_chr * 16) + cc - 87;
                      buffer[k - 1] = cur_chr;
                    } else if (c < 64)
                      buffer[k - 1] = c + 64;
                    else
                      buffer[k - 1] = c - 64;
                    cur_input.limit_field -= d;
                    first -= d;
                    while (k <= cur_input.limit_field) {
                      buffer[k] = buffer[k + d];
                      ++k;
                    }
                    goto _L26;
                  }
                }
              }
            }
            if (cat != 11)
              --k;
            if (k > (cur_input.loc_field + 1)) {
              cur_cs = id_lookup(cur_input.loc_field, k - cur_input.loc_field);
              cur_input.loc_field = k;
              goto _L40;
            }
          } else if (buffer[k] == cur_chr) {
            if (cat == 7) {
              if (k < cur_input.limit_field) {
                c = buffer[k + 1];
                if (c < 128) {
                  d = 2;
                  if (((c >= 48) && (c <= 57)) || ((c >= 97) && (c <= 102))) {
                    if (k + 2 <= cur_input.limit_field) {
                      cc = buffer[k + 2];
                      if (((cc >= 48) && (cc <= 57)) ||
                          ((cc >= 97) && (cc <= 102)))
                        ++d;
                    }
                  }
                  if (d > 2) {
                    if (c <= 57)
                      cur_chr = c - 48;
                    else
                      cur_chr = c - 87;
                    if (cc <= 57)
                      cur_chr = (cur_chr * 16) + cc - 48;
                    else
                      cur_chr = (cur_chr * 16) + cc - 87;
                    buffer[k - 1] = cur_chr;
                  } else if (c < 64)
                    buffer[k - 1] = c + 64;
                  else
                    buffer[k - 1] = c - 64;
                  cur_input.limit_field -= d;
                  first -= d;
                  while (k <= cur_input.limit_field) {
                    buffer[k] = buffer[k + d];
                    ++k;
                  }
                  goto _L26;
                }
              }
            }
          }
          cur_cs = buffer[cur_input.loc_field] + 257;
          ++cur_input.loc_field;
        }
      _L40:
        cur_cmd = eqtb[cur_cs].hh.U2.b0;
        cur_chr = eqtb[cur_cs].hh.rh;
        if (cur_cmd >= 113)
          check_outer_validity();
        break;
      case 14:
      case 30:
      case 46:
        cur_cs = cur_chr + 1;
        cur_cmd = eqtb[cur_cs].hh.U2.b0;
        cur_chr = eqtb[cur_cs].hh.rh;
        cur_input.state_field = 1;
        if (cur_cmd >= 113)
          check_outer_validity();
        break;
      case 8:
      case 24:
      case 40:
        if (cur_chr == buffer[cur_input.loc_field]) {
          if (cur_input.loc_field < cur_input.limit_field) {
            c = buffer[cur_input.loc_field + 1];
            if (c < 128) {
              cur_input.loc_field += 2;
              if (((c >= 48) && (c <= 57)) || ((c >= 97) && (c <= 102))) {
                if (cur_input.loc_field <= cur_input.limit_field) {
                  cc = buffer[cur_input.loc_field];
                  if (((cc >= 48) && (cc <= 57)) ||
                      ((cc >= 97) && (cc <= 102))) {
                    ++cur_input.loc_field;
                    if (c <= 57)
                      cur_chr = c - 48;
                    else
                      cur_chr = c - 87;
                    if (cc <= 57)
                      cur_chr = (cur_chr * 16) + cc - 48;
                    else
                      cur_chr = (cur_chr * 16) + cc - 87;
                    goto _L21;
                  }
                }
              }
              if (c < 64)
                cur_chr = c + 64;
              else
                cur_chr = c - 64;
              goto _L21;
            }
          }
        }
        cur_input.state_field = 1;
        break;
      case 16:
      case 32:
      case 48:
        print_nl(262);
        print(613);
        help_ptr = 2;
        help_line[1] = 614;
        help_line[0] = 615;
        deletions_allowed = false;
        error();
        deletions_allowed = true;
        goto _L20;
        break;
      case 11:
        cur_input.state_field = 17;
        cur_chr = 32;
        break;
      case 6:
        cur_input.loc_field = cur_input.limit_field + 1;
        cur_cmd = 10;
        cur_chr = 32;
        break;
      case 22:
      case 15:
      case 31:
      case 47:
        cur_input.loc_field = cur_input.limit_field + 1;
        goto _L25;
        break;
      case 38:
        cur_input.loc_field = cur_input.limit_field + 1;
        cur_cs = par_loc;
        cur_cmd = eqtb[cur_cs].hh.U2.b0;
        cur_chr = eqtb[cur_cs].hh.rh;
        if (cur_cmd >= 113)
          check_outer_validity();
        break;
      case 2:
        ++align_state;
        break;
      case 18:
      case 34:
        cur_input.state_field = 1;
        ++align_state;
        break;
      case 3:
        --align_state;
        break;
      case 19:
      case 35:
        cur_input.state_field = 1;
        --align_state;
        break;
      case 20:
      case 21:
      case 23:
      case 25:
      case 28:
      case 29:
      case 36:
      case 37:
      case 39:
      case 41:
      case 44:
      case 45:
        cur_input.state_field = 1;
        break;
      default:
        break;
      }
    } else if (cur_input.loc_field != (-1073741824)) {
      t = mem[cur_input.loc_field - mem_min].hh.lh;
      cur_input.loc_field = mem[cur_input.loc_field - mem_min].hh.rh;
      if (t >= 4095) {
        cur_cs = t - 4095;
        cur_cmd = eqtb[cur_cs].hh.U2.b0;
        cur_chr = eqtb[cur_cs].hh.rh;
        if (cur_cmd >= 113) {
          if (cur_cmd == 116) {
            cur_cs = mem[cur_input.loc_field - mem_min].hh.lh - 4095;
            cur_input.loc_field = -1073741824;
            cur_cmd = eqtb[cur_cs].hh.U2.b0;
            cur_chr = eqtb[cur_cs].hh.rh;
            if (cur_cmd > 100) {
              cur_cmd = 0;
              cur_chr = 257;
            }
          } else {
            check_outer_validity();
          }
        }
      } else {
        cur_cmd = t / 256;
        cur_chr = t & 255;
        switch (cur_cmd) {
        case 1:
          ++align_state;
          break;
        case 2:
          --align_state;
          break;
        case 5:
          begin_token_list(param_stack[cur_input.limit_field + cur_chr - 1], 0);
          goto _L20;
          break;
        default:
          break;
        }
      }
    } else {
      end_token_list();
      goto _L20;
    }
    if (cur_cmd <= 5) {
      if (cur_cmd >= 4) {
        if (!align_state) {
          if ((scanner_status == 4) || (cur_align == (-1073741824)))
            fatal_error(595);
          cur_cmd = mem[cur_align - mem_min + 5].hh.lh;
          mem[cur_align - mem_min + 5].hh.lh = cur_chr;
          if (cur_cmd == 63)
            begin_token_list(mem_max - 10, 2);
          else
            begin_token_list(mem[cur_align - mem_min + 2].int_, 2);
          align_state = 1000000;
          goto _L20;
        }
      }
    }
  _L10:;
  }
  void firm_up_the_line() {
    int k, N;
    cur_input.limit_field = last;
    if (eqtb[12191].int_ <= 0)
      return;
    if (interaction <= 1)
      return;
    print_ln();
    if (cur_input.start_field < cur_input.limit_field) {
      for (N = cur_input.limit_field, k = cur_input.start_field; k <= (N - 1);
           ++k)
        print(buffer[k]);
    }
    first = cur_input.limit_field;
    print(618);
    term_input();
    if (last <= first)
      return;
    for (N = last, k = first; k <= (N - 1); ++k)
      buffer[k + cur_input.start_field - first] = buffer[k];
    cur_input.limit_field = cur_input.start_field + last - first;
  }
  void get_token() {
    no_new_control_sequence = false;
    get_next();
    no_new_control_sequence = true;
    if (!cur_cs)
      cur_tok = (cur_cmd * 256) + cur_chr;
    else
      cur_tok = cur_cs + 4095;
  }
  void macro_call() {
    halfword r, p, q, s, t, u, v, rbrace_ptr;
    small_number n = 0;
    halfword unbalance, m, ref_count;
    ASCII_code match_chr;
    small_number save_scanner_status = scanner_status;
    halfword save_warning_index = warning_index;
    warning_index = cur_cs;
    ref_count = cur_chr;
    r = mem[ref_count - mem_min].hh.rh;
    if (eqtb[12193].int_ > 0) {
      begin_diagnostic();
      print_ln();
      print_cs(warning_index);
      token_show(ref_count);
      end_diagnostic(false);
    }
    if (mem[r - mem_min].hh.lh != 3584) {
      scanner_status = 3;
      unbalance = 0;
      long_state = eqtb[cur_cs].hh.U2.b0;
      if (long_state >= 113)
        long_state -= 2;
      do {
        mem[mem_max - mem_min - 3].hh.rh = -1073741824;
        if ((mem[r - mem_min].hh.lh > 3583) ||
            (mem[r - mem_min].hh.lh < 3328)) {
          s = -1073741824;
        } else {
          match_chr = mem[r - mem_min].hh.lh - 3328;
          s = mem[r - mem_min].hh.rh;
          r = s;
          p = mem_max - 3;
          m = 0;
        }
      _L22:
        get_token();
        if (cur_tok == mem[r - mem_min].hh.lh) {
          r = mem[r - mem_min].hh.rh;
          if ((mem[r - mem_min].hh.lh >= 3328) &&
              (mem[r - mem_min].hh.lh <= 3584)) {
            if (cur_tok < 512)
              --align_state;
            goto _L40;
          } else {
            goto _L22;
          }
        }
        if (s != r) {
          if (s == (-1073741824)) {
            print_nl(262);
            print(650);
            sprint_cs(warning_index);
            print(651);
            help_ptr = 4;
            help_line[3] = 652;
            help_line[2] = 653;
            help_line[1] = 654;
            help_line[0] = 655;
            error();
            goto _L10;
          }
          t = s;
          do {
            q = get_avail();
            mem[p - mem_min].hh.rh = q;
            mem[q - mem_min].hh.lh = mem[t - mem_min].hh.lh;
            p = q;
            ++m;
            u = mem[t - mem_min].hh.rh;
            v = s;
            while (true) {
              if (u == r) {
                if (cur_tok != mem[v - mem_min].hh.lh) {
                  goto _L30;
                } else {
                  r = mem[v - mem_min].hh.rh;
                  goto _L22;
                }
              }
              if (mem[u - mem_min].hh.lh != mem[v - mem_min].hh.lh)
                goto _L30;
              u = mem[u - mem_min].hh.rh;
              v = mem[v - mem_min].hh.rh;
            }
          _L30:
            t = mem[t - mem_min].hh.rh;
          } while (t != r);
          r = s;
        }
        if (cur_tok == par_token) {
          if (long_state != 112) {
            if (long_state == 111) {
              runaway();
              print_nl(262);
              print(645);
              sprint_cs(warning_index);
              print(646);
              help_ptr = 3;
              help_line[2] = 647;
              help_line[1] = 648;
              help_line[0] = 649;
              back_error();
            }
            pstack[n] = mem[mem_max - mem_min - 3].hh.rh;
            align_state -= unbalance;
            for (m = 0; m <= n; ++m)
              flush_list(pstack[m]);
            goto _L10;
          }
        }
        if (cur_tok < 768) {
          if (cur_tok >= 512) {
            back_input();
            print_nl(262);
            print(637);
            sprint_cs(warning_index);
            print(638);
            help_ptr = 6;
            help_line[5] = 639;
            help_line[4] = 640;
            help_line[3] = 641;
            help_line[2] = 642;
            help_line[1] = 643;
            help_line[0] = 644;
            ++align_state;
            long_state = 111;
            cur_tok = par_token;
            ins_error();
            goto _L22;
          }
          unbalance = 1;
          while (true) {
            q = avail;
            if (q == (-1073741824)) {
              q = get_avail();
            } else {
              avail = mem[q - mem_min].hh.rh;
              mem[q - mem_min].hh.rh = -1073741824;
            }
            mem[p - mem_min].hh.rh = q;
            mem[q - mem_min].hh.lh = cur_tok;
            p = q;
            get_token();
            if (cur_tok == par_token) {
              if (long_state != 112) {
                if (long_state == 111) {
                  runaway();
                  print_nl(262);
                  print(645);
                  sprint_cs(warning_index);
                  print(646);
                  help_ptr = 3;
                  help_line[2] = 647;
                  help_line[1] = 648;
                  help_line[0] = 649;
                  back_error();
                }
                pstack[n] = mem[mem_max - mem_min - 3].hh.rh;
                align_state -= unbalance;
                for (m = 0; m <= n; ++m)
                  flush_list(pstack[m]);
                goto _L10;
              }
            }
            if (cur_tok >= 768)
              continue;
            if (cur_tok < 512) {
              ++unbalance;
            } else {
              --unbalance;
              if (!unbalance)
                goto _L31;
            }
          }
        _L31:
          rbrace_ptr = p;
          q = get_avail();
          mem[p - mem_min].hh.rh = q;
          mem[q - mem_min].hh.lh = cur_tok;
          p = q;
        } else {
          if (cur_tok == 2592) {
            if (mem[r - mem_min].hh.lh <= 3584) {
              if (mem[r - mem_min].hh.lh >= 3328)
                goto _L22;
            }
          }
          q = get_avail();
          mem[p - mem_min].hh.rh = q;
          mem[q - mem_min].hh.lh = cur_tok;
          p = q;
        }
        ++m;
        if (mem[r - mem_min].hh.lh > 3584)
          goto _L22;
        if (mem[r - mem_min].hh.lh < 3328)
          goto _L22;
      _L40:
        if (s != (-1073741824)) {
          if ((m == 1) && (mem[p - mem_min].hh.lh < 768) &&
              (p != (mem_max - 3))) {
            mem[rbrace_ptr - mem_min].hh.rh = -1073741824;
            mem[p - mem_min].hh.rh = avail;
            avail = p;
            p = mem[mem_max - mem_min - 3].hh.rh;
            pstack[n] = mem[p - mem_min].hh.rh;
            mem[p - mem_min].hh.rh = avail;
            avail = p;
          } else {
            pstack[n] = mem[mem_max - mem_min - 3].hh.rh;
          }
          ++n;
          if (eqtb[12193].int_ > 0) {
            begin_diagnostic();
            print_nl(match_chr);
            print_int(n);
            print(656);
            show_token_list(pstack[n - 1], -1073741824, 1000);
            end_diagnostic(false);
          }
        }
      } while (mem[r - mem_min].hh.lh != 3584);
    }
    while ((!cur_input.state_field) && (cur_input.loc_field == (-1073741824)) &&
           (cur_input.index_field != 2))
      end_token_list();
    begin_token_list(ref_count, 5);
    cur_input.name_field = warning_index;
    cur_input.loc_field = mem[r - mem_min].hh.rh;
    if (n > 0) {
      if (param_ptr + n > max_param_stack) {
        max_param_stack = param_ptr + n;
        if (max_param_stack > param_size)
          overflow(636, param_size);
      }
      for (m = 0; m <= (n - 1); ++m)
        param_stack[param_ptr + m] = pstack[m];
      param_ptr += n;
    }
  _L10:
    scanner_status = save_scanner_status;
    warning_index = save_warning_index;
  }
  void insert_relax() {
    cur_tok = cur_cs + 4095;
    back_input();
    cur_tok = 13616;
    back_input();
    cur_input.index_field = 4;
  }
  void expand() {
    halfword t, p, q, r;
    int j;
    small_number save_scanner_status;
    integer cv_backup = cur_val;
    small_number cvl_backup = cur_val_level;
    small_number radix_backup = radix;
    small_number co_backup = cur_order;
    halfword backup_backup = mem[mem_max - mem_min - 13].hh.rh;
    if (cur_cmd < 111) {
      if (eqtb[12199].int_ > 1)
        show_cur_cmd_chr();
      switch (cur_cmd) {
      case 110:
        if (cur_mark[cur_chr] != (-1073741824))
          begin_token_list(cur_mark[cur_chr], 14);
        break;
      case 102:
        get_token();
        t = cur_tok;
        get_token();
        if (cur_cmd > 100)
          expand();
        else
          back_input();
        cur_tok = t;
        back_input();
        break;
      case 103:
        save_scanner_status = scanner_status;
        scanner_status = 0;
        get_token();
        scanner_status = save_scanner_status;
        t = cur_tok;
        back_input();
        if (t >= 4095) {
          p = get_avail();
          mem[p - mem_min].hh.lh = 13618;
          mem[p - mem_min].hh.rh = cur_input.loc_field;
          cur_input.start_field = p;
          cur_input.loc_field = p;
        }
        break;
      case 107:
        r = get_avail();
        p = r;
        do {
          get_x_token();
          if (!cur_cs) {
            q = get_avail();
            mem[p - mem_min].hh.rh = q;
            mem[q - mem_min].hh.lh = cur_tok;
            p = q;
          }
        } while (!cur_cs);
        if (cur_cmd != 67) {
          print_nl(262);
          print(625);
          print_esc(505);
          print(626);
          help_ptr = 2;
          help_line[1] = 627;
          help_line[0] = 628;
          back_error();
        }
        j = first;
        p = mem[r - mem_min].hh.rh;
        while (p != (-1073741824)) {
          if (j >= max_buf_stack) {
            max_buf_stack = j + 1;
            if (max_buf_stack == buf_size)
              overflow(256, buf_size);
          }
          buffer[j] = mem[p - mem_min].hh.lh & 255;
          ++j;
          p = mem[p - mem_min].hh.rh;
        }
        if (j > (first + 1)) {
          no_new_control_sequence = false;
          cur_cs = id_lookup(first, j - first);
          no_new_control_sequence = true;
        } else if (j == first)
          cur_cs = 513;
        else
          cur_cs = buffer[first] + 257;
        flush_list(r);
        if (eqtb[cur_cs].hh.U2.b0 == 101)
          eq_define(cur_cs, 0, 256);
        cur_tok = cur_cs + 4095;
        back_input();
        break;
      case 108:
        conv_toks();
        break;
      case 109:
        ins_the_toks();
        break;
      case 105:
        conditional();
        break;
      case 106:
        if (cur_chr > if_limit) {
          if (if_limit == 1) {
            insert_relax();
          } else {
            print_nl(262);
            print(776);
            print_cmd_chr(106, cur_chr);
            help_ptr = 1;
            help_line[0] = 777;
            error();
          }
        } else {
          while (cur_chr != 2)
            pass_text();
          p = cond_ptr;
          if_line = mem[p - mem_min + 1].int_;
          cur_if = mem[p - mem_min].hh.U2.b1;
          if_limit = mem[p - mem_min].hh.U2.b0;
          cond_ptr = mem[p - mem_min].hh.rh;
          free_node(p, 2);
        }
        break;
      case 104:
        if (cur_chr > 0) {
          force_eof = true;
        } else if (name_in_progress)
          insert_relax();
        else
          start_input();
        break;
      default:
        print_nl(262);
        print(619);
        help_ptr = 5;
        help_line[4] = 620;
        help_line[3] = 621;
        help_line[2] = 622;
        help_line[1] = 623;
        help_line[0] = 624;
        error();
        break;
      }
    } else if (cur_cmd < 115) {
      macro_call();
    } else {
      cur_tok = 13615;
      back_input();
    }
    cur_val = cv_backup;
    cur_val_level = cvl_backup;
    radix = radix_backup;
    cur_order = co_backup;
    mem[mem_max - mem_min - 13].hh.rh = backup_backup;
  }
  void get_x_token() {
  _L20:
    get_next();
    if (cur_cmd <= 100)
      goto _L30;
    if (cur_cmd >= 111) {
      if (cur_cmd >= 115) {
        cur_cs = 9520;
        cur_cmd = 9;
        goto _L30;
      }
      macro_call();
    } else {
      expand();
    }
    goto _L20;
  _L30:
    if (!cur_cs)
      cur_tok = (cur_cmd * 256) + cur_chr;
    else
      cur_tok = cur_cs + 4095;
  }
  void x_token() {
    while (cur_cmd > 100) {
      expand();
      get_next();
    }
    if (!cur_cs)
      cur_tok = (cur_cmd * 256) + cur_chr;
    else
      cur_tok = cur_cs + 4095;
  }
  void scan_left_brace() {
    do {
      get_x_token();
    } while ((cur_cmd == 10) || (!cur_cmd));
    if (cur_cmd == 1)
      return;
    print_nl(262);
    print(657);
    help_ptr = 4;
    help_line[3] = 658;
    help_line[2] = 659;
    help_line[1] = 660;
    help_line[0] = 661;
    back_error();
    cur_tok = 379;
    cur_cmd = 1;
    cur_chr = 123;
    ++align_state;
  }
  void scan_optional_equals() {
    do {
      get_x_token();
    } while (cur_cmd == 10);
    if (cur_tok != 3133)
      back_input();
  }
  bool scan_keyword(str_number s) {
    bool result;
    halfword p = mem_max - 13, q;
    pool_pointer k;
    mem[p - mem_min].hh.rh = -1073741824;
    k = str_start[s];
    while (k < str_start[s + 1]) {
      get_x_token();
      if ((!cur_cs) &&
          ((cur_chr == str_pool[k]) || (cur_chr == (str_pool[k] - 32)))) {
        q = get_avail();
        mem[p - mem_min].hh.rh = q;
        mem[q - mem_min].hh.lh = cur_tok;
        p = q;
        ++k;
        continue;
      } else {
        if ((cur_cmd == 10) && (p == (mem_max - 13)))
          continue;
        back_input();
        if (p != (mem_max - 13))
          begin_token_list(mem[mem_max - mem_min - 13].hh.rh, 3);
        result = false;
        goto _L10;
      }
    }
    flush_list(mem[mem_max - mem_min - 13].hh.rh);
    result = true;
  _L10:
    return result;
  }
  void mu_error() {
    print_nl(262);
    print(662);
    help_ptr = 1;
    help_line[0] = 663;
    error();
  }
  void scan_eight_bit_int() {
    scan_int();
    if (((unsigned)cur_val) <= 255)
      return;
    print_nl(262);
    print(687);
    help_ptr = 2;
    help_line[1] = 688;
    help_line[0] = 689;
    int_error(cur_val);
    cur_val = 0;
  }
  void scan_char_num() {
    scan_int();
    if (((unsigned)cur_val) <= 255)
      return;
    print_nl(262);
    print(690);
    help_ptr = 2;
    help_line[1] = 691;
    help_line[0] = 689;
    int_error(cur_val);
    cur_val = 0;
  }
  void scan_four_bit_int() {
    scan_int();
    if (((unsigned)cur_val) <= 15)
      return;
    print_nl(262);
    print(692);
    help_ptr = 2;
    help_line[1] = 693;
    help_line[0] = 689;
    int_error(cur_val);
    cur_val = 0;
  }
  void scan_fifteen_bit_int() {
    scan_int();
    if (((unsigned)cur_val) <= 32767)
      return;
    print_nl(262);
    print(694);
    help_ptr = 2;
    help_line[1] = 695;
    help_line[0] = 689;
    int_error(cur_val);
    cur_val = 0;
  }
  void scan_twenty_seven_bit_int() {
    scan_int();
    if (((unsigned)cur_val) <= 134217727)
      return;
    print_nl(262);
    print(696);
    help_ptr = 2;
    help_line[1] = 697;
    help_line[0] = 689;
    int_error(cur_val);
    cur_val = 0;
  }
  void scan_font_ident() {
    internal_font_number f;
    halfword m;
    do {
      get_x_token();
    } while (cur_cmd == 10);
    if (cur_cmd == 88) {
      f = eqtb[10834].hh.rh;
    } else if (cur_cmd == 87) {
      f = cur_chr;
    } else if (cur_cmd == 86) {
      m = cur_chr;
      scan_four_bit_int();
      f = eqtb[m + cur_val].hh.rh;
    } else {
      print_nl(262);
      print(816);
      help_ptr = 2;
      help_line[1] = 817;
      help_line[0] = 818;
      back_error();
      f = 0;
    }
    cur_val = f;
  }
  void find_font_dimen(bool writing) {
    internal_font_number f;
    integer n;
    scan_int();
    n = cur_val;
    scan_font_ident();
    f = cur_val;
    if (n <= 0) {
      cur_val = fmem_ptr;
    } else {
      if (writing && (n <= 4) && (n >= 2) && (font_glue[f] != (-1073741824))) {
        delete_glue_ref(font_glue[f]);
        font_glue[f] = -1073741824;
      }
      if (n > font_params[f]) {
        if (f < font_ptr) {
          cur_val = fmem_ptr;
        } else {
          do {
            if (fmem_ptr == font_mem_size)
              overflow(823, font_mem_size);
            font_info[fmem_ptr].int_ = 0;
            ++fmem_ptr;
            ++font_params[f];
          } while (n != font_params[f]);
          cur_val = fmem_ptr - 1;
        }
      } else {
        cur_val = n + param_base[f];
      }
    }
    if (cur_val != fmem_ptr)
      return;
    print_nl(262);
    print(801);
    print_esc(hash[f + 9010].rh);
    print(819);
    print_int(font_params[f]);
    print(820);
    help_ptr = 2;
    help_line[1] = 821;
    help_line[0] = 822;
    error();
  }
  void scan_something_internal(small_number level, bool negative) {
    int p;
    halfword m = cur_chr;
    switch (cur_cmd) {
    case 85:
      scan_char_num();
      if (m == 11907) {
        cur_val = eqtb[cur_val + 11907].hh.rh + 1073741824;
        cur_val_level = 0;
      } else if (m < 11907) {
        cur_val = eqtb[m + cur_val].hh.rh;
        cur_val_level = 0;
      } else {
        cur_val = eqtb[m + cur_val].int_;
        cur_val_level = 0;
      }
      break;
    case 71:
    case 72:
    case 86:
    case 87:
    case 88:
      if (level != 5) {
        print_nl(262);
        print(664);
        help_ptr = 3;
        help_line[2] = 665;
        help_line[1] = 666;
        help_line[0] = 667;
        back_error();
        cur_val = 0;
        cur_val_level = 1;
      } else if (cur_cmd <= 72) {
        if (cur_cmd < 72) {
          scan_eight_bit_int();
          m = cur_val + 10322;
        }
        cur_val = eqtb[m].hh.rh;
        cur_val_level = 5;
      } else {
        back_input();
        scan_font_ident();
        cur_val += 9524;
        cur_val_level = 4;
      }
      break;
    case 73:
      cur_val = eqtb[m].int_;
      cur_val_level = 0;
      break;
    case 74:
      cur_val = eqtb[m].int_;
      cur_val_level = 1;
      break;
    case 75:
      cur_val = eqtb[m].hh.rh;
      cur_val_level = 2;
      break;
    case 76:
      cur_val = eqtb[m].hh.rh;
      cur_val_level = 3;
      break;
    case 79:
      if (abs(cur_list.mode_field) != m) {
        print_nl(262);
        print(680);
        print_cmd_chr(79, m);
        help_ptr = 4;
        help_line[3] = 681;
        help_line[2] = 682;
        help_line[1] = 683;
        help_line[0] = 684;
        error();
        if (level != 5) {
          cur_val = 0;
          cur_val_level = 1;
        } else {
          cur_val = 0;
          cur_val_level = 0;
        }
      } else if (m == 1) {
        cur_val = cur_list.aux_field.int_;
        cur_val_level = 1;
      } else {
        cur_val = cur_list.aux_field.hh.lh;
        cur_val_level = 0;
      }
      break;
    case 80:
      if (!cur_list.mode_field) {
        cur_val = 0;
        cur_val_level = 0;
      } else {
        nest[nest_ptr] = cur_list;
        p = nest_ptr;
        while (abs(nest[p].mode_field) != 1)
          --p;
        cur_val = nest[p].pg_field;
        cur_val_level = 0;
      }
      break;
    case 82:
      if (!m)
        cur_val = dead_cycles;
      else
        cur_val = insert_penalties;
      cur_val_level = 0;
      break;
    case 81:
      if ((!page_contents) && (!output_active)) {
        if (!m)
          cur_val = 1073741823;
        else
          cur_val = 0;
      } else {
        cur_val = page_so_far[m];
      }
      cur_val_level = 1;
      break;
    case 84:
      if (eqtb[10312].hh.rh == (-1073741824))
        cur_val = 0;
      else
        cur_val = mem[eqtb[10312].hh.rh - mem_min].hh.lh;
      cur_val_level = 0;
      break;
    case 83:
      scan_eight_bit_int();
      if (eqtb[cur_val + 10578].hh.rh == (-1073741824))
        cur_val = 0;
      else
        cur_val = mem[eqtb[cur_val + 10578].hh.rh + m - mem_min].int_;
      cur_val_level = 1;
      break;
    case 68:
    case 69:
      cur_val = cur_chr;
      cur_val_level = 0;
      break;
    case 77:
      find_font_dimen(false);
      font_info[fmem_ptr].int_ = 0;
      cur_val = font_info[cur_val].int_;
      cur_val_level = 1;
      break;
    case 78:
      scan_font_ident();
      if (!m) {
        cur_val = hyphen_char[cur_val];
        cur_val_level = 0;
      } else {
        cur_val = skew_char[cur_val];
        cur_val_level = 0;
      }
      break;
    case 89:
      scan_eight_bit_int();
      switch (m) {
      case 0:
        cur_val = eqtb[cur_val + 12218].int_;
        break;
      case 1:
        cur_val = eqtb[cur_val + 12751].int_;
        break;
      case 2:
        cur_val = eqtb[cur_val + 9800].hh.rh;
        break;
      case 3:
        cur_val = eqtb[cur_val + 10056].hh.rh;
        break;
      }
      cur_val_level = m;
      break;
    case 70:
      if (cur_chr > 2) {
        if (cur_chr == 3)
          cur_val = line;
        else
          cur_val = last_badness;
        cur_val_level = 0;
      } else {
        if (cur_chr == 2)
          cur_val = 0;
        else
          cur_val = 0;
        cur_val_level = cur_chr;
        if ((cur_list.tail_field < hi_mem_min) && cur_list.mode_field) {
          switch (cur_chr) {
          case 0:
            if (mem[cur_list.tail_field - mem_min].hh.U2.b0 == 12)
              cur_val = mem[cur_list.tail_field - mem_min + 1].int_;
            break;
          case 1:
            if (mem[cur_list.tail_field - mem_min].hh.U2.b0 == 11)
              cur_val = mem[cur_list.tail_field - mem_min + 1].int_;
            break;
          case 2:
            if (mem[cur_list.tail_field - mem_min].hh.U2.b0 == 10) {
              cur_val = mem[cur_list.tail_field - mem_min + 1].hh.lh;
              if (mem[cur_list.tail_field - mem_min].hh.U2.b1 == 99)
                cur_val_level = 3;
            }
            break;
          }
        } else if ((cur_list.mode_field == 1) &&
                   (cur_list.tail_field == cur_list.head_field)) {
          switch (cur_chr) {
          case 0:
            cur_val = last_penalty;
            break;
          case 1:
            cur_val = last_kern;
            break;
          case 2:
            if (last_glue != 1073741824)
              cur_val = last_glue;
            break;
          }
        }
      }
      break;
    default:
      print_nl(262);
      print(685);
      print_cmd_chr(cur_cmd, cur_chr);
      print(686);
      print_esc(537);
      help_ptr = 1;
      help_line[0] = 684;
      error();
      if (level != 5) {
        cur_val = 0;
        cur_val_level = 1;
      } else {
        cur_val = 0;
        cur_val_level = 0;
      }
      break;
    }
    while (cur_val_level > level) {
      if (cur_val_level == 2) {
        cur_val = mem[cur_val - mem_min + 1].int_;
      } else if (cur_val_level == 3)
        mu_error();
      --cur_val_level;
    }
    if (!negative) {
      if ((cur_val_level >= 2) && (cur_val_level <= 3))
        ++mem[cur_val - mem_min].hh.rh;
      return;
    }
    if (cur_val_level < 2) {
      cur_val = -cur_val;
      return;
    }
    cur_val = new_spec(cur_val);
    mem[cur_val - mem_min + 1].int_ = -mem[cur_val - mem_min + 1].int_;
    mem[cur_val - mem_min + 2].int_ = -mem[cur_val - mem_min + 2].int_;
    mem[cur_val - mem_min + 3].int_ = -mem[cur_val - mem_min + 3].int_;
  }
  void scan_int() {
    bool negative = false;
    integer m;
    small_number d;
    bool vacuous, OK_so_far = true;
    radix = 0;
    do {
      do {
        get_x_token();
      } while (cur_cmd == 10);
      if (cur_tok == 3117) {
        negative = !negative;
        cur_tok = 3115;
      }
    } while (cur_tok == 3115);
    if (cur_tok == 3168) {
      get_token();
      if (cur_tok < 4095) {
        cur_val = cur_chr;
        if (cur_cmd <= 2) {
          if (cur_cmd == 2)
            ++align_state;
          else
            --align_state;
        }
      } else if (cur_tok < 4352)
        cur_val = cur_tok - 4096;
      else
        cur_val = cur_tok - 4352;
      if (cur_val > 255) {
        print_nl(262);
        print(698);
        help_ptr = 2;
        help_line[1] = 699;
        help_line[0] = 700;
        cur_val = 48;
        back_error();
      } else {
        get_x_token();
        if (cur_cmd != 10)
          back_input();
      }
    } else if ((cur_cmd >= 68) && (cur_cmd <= 89)) {
      scan_something_internal(0, false);
    } else {
      radix = 10;
      m = 214748364;
      if (cur_tok == 3111) {
        radix = 8;
        m = 268435456;
        get_x_token();
      } else if (cur_tok == 3106) {
        radix = 16;
        m = 134217728;
        get_x_token();
      }
      vacuous = true;
      cur_val = 0;
      while (true) {
        if ((cur_tok < (radix + 3120)) && (cur_tok >= 3120) &&
            (cur_tok <= 3129)) {
          d = cur_tok - 3120;
        } else if (radix == 16) {
          if ((cur_tok <= 2886) && (cur_tok >= 2881)) {
            d = cur_tok - 2871;
          } else if ((cur_tok <= 3142) && (cur_tok >= 3137))
            d = cur_tok - 3127;
          else
            goto _L30;
        } else {
          goto _L30;
        }
        vacuous = false;
        if ((cur_val >= m) && ((cur_val > m) || (d > 7) || (radix != 10))) {
          if (OK_so_far) {
            print_nl(262);
            print(701);
            help_ptr = 2;
            help_line[1] = 702;
            help_line[0] = 703;
            error();
            cur_val = 2147483647;
            OK_so_far = false;
          }
        } else {
          cur_val = (cur_val * radix) + d;
        }
        get_x_token();
      }
    _L30:
      if (vacuous) {
        print_nl(262);
        print(664);
        help_ptr = 3;
        help_line[2] = 665;
        help_line[1] = 666;
        help_line[0] = 667;
        back_error();
      } else if (cur_cmd != 10)
        back_input();
    }
    if (negative)
      cur_val = -cur_val;
  }
  void scan_dimen(bool mu, bool inf, bool shortcut) {
    bool negative = false;
    integer f = 0, save_cur_val;
    int num, denom;
    small_number k, kk;
    halfword p, q;
    scaled v;
    arith_error = false;
    cur_order = 0;
    if (!shortcut) {
      do {
        do {
          get_x_token();
        } while (cur_cmd == 10);
        if (cur_tok == 3117) {
          negative = !negative;
          cur_tok = 3115;
        }
      } while (cur_tok == 3115);
      if ((cur_cmd >= 68) && (cur_cmd <= 89)) {
        if (mu) {
          scan_something_internal(3, false);
          if (cur_val_level >= 2) {
            v = mem[cur_val - mem_min + 1].int_;
            delete_glue_ref(cur_val);
            cur_val = v;
          }
          if (cur_val_level == 3)
            goto _L89;
          if (cur_val_level)
            mu_error();
        } else {
          scan_something_internal(1, false);
          if (cur_val_level == 1)
            goto _L89;
        }
      } else {
        back_input();
        if (cur_tok == 3116)
          cur_tok = 3118;
        if (cur_tok != 3118) {
          scan_int();
        } else {
          radix = 10;
          cur_val = 0;
        }
        if (cur_tok == 3116)
          cur_tok = 3118;
        if ((radix == 10) && (cur_tok == 3118)) {
          k = 0;
          p = -1073741824;
          get_token();
          while (true) {
            get_x_token();
            if ((cur_tok > 3129) || (cur_tok < 3120))
              goto _L31;
            if (k >= 17)
              continue;
            q = get_avail();
            mem[q - mem_min].hh.rh = p;
            mem[q - mem_min].hh.lh = cur_tok - 3120;
            p = q;
            ++k;
          }
        _L31:
          for (kk = k; kk >= 1; --kk) {
            dig[kk - 1] = mem[p - mem_min].hh.lh;
            q = p;
            p = mem[p - mem_min].hh.rh;
            mem[q - mem_min].hh.rh = avail;
            avail = q;
          }
          f = round_decimals(k);
          if (cur_cmd != 10)
            back_input();
        }
      }
    }
    if (cur_val < 0) {
      negative = !negative;
      cur_val = -cur_val;
    }
    if (inf) {
      if (scan_keyword(311)) {
        cur_order = 1;
        while (scan_keyword(108)) {
          if (cur_order != 3) {
            ++cur_order;
            continue;
          }
          print_nl(262);
          print(705);
          print(706);
          help_ptr = 1;
          help_line[0] = 707;
          error();
        }
        goto _L88;
      }
    }
    save_cur_val = cur_val;
    do {
      get_x_token();
    } while (cur_cmd == 10);
    if ((cur_cmd >= 68) && (cur_cmd <= 89)) {
      if (mu) {
        scan_something_internal(3, false);
        if (cur_val_level >= 2) {
          v = mem[cur_val - mem_min + 1].int_;
          delete_glue_ref(cur_val);
          cur_val = v;
        }
        if (cur_val_level != 3)
          mu_error();
      } else {
        scan_something_internal(1, false);
      }
      v = cur_val;
      goto _L40;
    }
    back_input();
    if (mu)
      goto _L45;
    if (scan_keyword(708)) {
      v = font_info[param_base[eqtb[10834].hh.rh] + 6].int_;
    } else if (scan_keyword(709))
      v = font_info[param_base[eqtb[10834].hh.rh] + 5].int_;
    else
      goto _L45;
    get_x_token();
    if (cur_cmd != 10)
      back_input();
  _L40:
    cur_val = mult_and_add(save_cur_val, v, xn_over_d(v, f, 65536), 1073741823);
    goto _L89;
  _L45:
    if (mu) {
      if (scan_keyword(337)) {
        goto _L88;
      } else {
        print_nl(262);
        print(705);
        print(710);
        help_ptr = 4;
        help_line[3] = 711;
        help_line[2] = 712;
        help_line[1] = 713;
        help_line[0] = 714;
        error();
        goto _L88;
      }
    }
    if (scan_keyword(704)) {
      prepare_mag();
      if (eqtb[12180].int_ != 1000) {
        cur_val = xn_over_d(cur_val, 1000, eqtb[12180].int_);
        f = ((f * 1000) + (remainder_ * 65536)) / eqtb[12180].int_;
        cur_val += f / 65536;
        f &= 65535;
      }
    }
    if (scan_keyword(397))
      goto _L88;
    if (scan_keyword(715)) {
      num = 7227;
      denom = 100;
    } else if (scan_keyword(716)) {
      num = 12;
      denom = 1;
    } else if (scan_keyword(717)) {
      num = 7227;
      denom = 254;
    } else if (scan_keyword(718)) {
      num = 7227;
      denom = 2540;
    } else if (scan_keyword(719)) {
      num = 7227;
      denom = 7200;
    } else if (scan_keyword(720)) {
      num = 1238;
      denom = 1157;
    } else if (scan_keyword(721)) {
      num = 14856;
      denom = 1157;
    } else if (scan_keyword(722)) {
      goto _L30;
    } else {
      print_nl(262);
      print(705);
      print(723);
      help_ptr = 6;
      help_line[5] = 724;
      help_line[4] = 725;
      help_line[3] = 726;
      help_line[2] = 712;
      help_line[1] = 713;
      help_line[0] = 714;
      error();
      goto _L32;
    }
    cur_val = xn_over_d(cur_val, num, denom);
    f = ((num * f) + (remainder_ * 65536)) / denom;
    cur_val += f / 65536;
    f &= 65535;
  _L32:
  _L88:
    if (cur_val >= 16384)
      arith_error = true;
    else
      cur_val = (cur_val * 65536) + f;
  _L30:
    get_x_token();
    if (cur_cmd != 10)
      back_input();
  _L89:
    if (arith_error || (abs(cur_val) >= 1073741824)) {
      print_nl(262);
      print(727);
      help_ptr = 2;
      help_line[1] = 728;
      help_line[0] = 729;
      error();
      cur_val = 1073741823;
      arith_error = false;
    }
    if (negative)
      cur_val = -cur_val;
  }
  void scan_glue(small_number level) {
    bool negative = false;
    halfword q;
    bool mu = level == 3;
    do {
      do {
        get_x_token();
      } while (cur_cmd == 10);
      if (cur_tok == 3117) {
        negative = !negative;
        cur_tok = 3115;
      }
    } while (cur_tok == 3115);
    if ((cur_cmd >= 68) && (cur_cmd <= 89)) {
      scan_something_internal(level, negative);
      if (cur_val_level >= 2) {
        if (cur_val_level != level)
          mu_error();
        goto _L10;
      }
      if (!cur_val_level) {
        scan_dimen(mu, false, true);
      } else if (level == 3)
        mu_error();
    } else {
      back_input();
      scan_dimen(mu, false, false);
      if (negative)
        cur_val = -cur_val;
    }
    q = new_spec(0);
    mem[q - mem_min + 1].int_ = cur_val;
    if (scan_keyword(730)) {
      scan_dimen(mu, true, false);
      mem[q - mem_min + 2].int_ = cur_val;
      mem[q - mem_min].hh.U2.b0 = cur_order;
    }
    if (scan_keyword(731)) {
      scan_dimen(mu, true, false);
      mem[q - mem_min + 3].int_ = cur_val;
      mem[q - mem_min].hh.U2.b1 = cur_order;
    }
    cur_val = q;
  _L10:;
  }
  halfword scan_rule_spec() {
    halfword q = new_rule();
    if (cur_cmd == 35) {
      mem[q - mem_min + 1].int_ = 26214;
    } else {
      mem[q - mem_min + 3].int_ = 26214;
      mem[q - mem_min + 2].int_ = 0;
    }
  _L21:
    if (scan_keyword(732)) {
      scan_dimen(false, false, false);
      mem[q - mem_min + 1].int_ = cur_val;
      goto _L21;
    }
    if (scan_keyword(733)) {
      scan_dimen(false, false, false);
      mem[q - mem_min + 3].int_ = cur_val;
      goto _L21;
    }
    if (!scan_keyword(734))
      return q;
    scan_dimen(false, false, false);
    mem[q - mem_min + 2].int_ = cur_val;
    goto _L21;
  }
  halfword str_toks(pool_pointer b) {
    halfword p = mem_max - 3, q, t;
    pool_pointer k;
    if (pool_ptr + 1 > pool_size)
      overflow(257, pool_size - init_pool_ptr);
    mem[p - mem_min].hh.rh = -1073741824;
    k = b;
    while (k < pool_ptr) {
      t = str_pool[k];
      if (t == 32)
        t = 2592;
      else
        t += 3072;
      q = avail;
      if (q == (-1073741824)) {
        q = get_avail();
      } else {
        avail = mem[q - mem_min].hh.rh;
        mem[q - mem_min].hh.rh = -1073741824;
      }
      mem[p - mem_min].hh.rh = q;
      mem[q - mem_min].hh.lh = t;
      p = q;
      ++k;
    }
    pool_ptr = b;
    return p;
  }
  halfword the_toks() {
    char old_setting;
    halfword p, q, r;
    pool_pointer b;
    get_x_token();
    scan_something_internal(5, false);
    if (cur_val_level >= 4) {
      p = mem_max - 3;
      mem[p - mem_min].hh.rh = -1073741824;
      if (cur_val_level == 4) {
        q = get_avail();
        mem[p - mem_min].hh.rh = q;
        mem[q - mem_min].hh.lh = cur_val + 4095;
        p = q;
        return p;
      }
      if (cur_val == (-1073741824))
        return p;
      r = mem[cur_val - mem_min].hh.rh;
      while (r != (-1073741824)) {
        q = avail;
        if (q == (-1073741824)) {
          q = get_avail();
        } else {
          avail = mem[q - mem_min].hh.rh;
          mem[q - mem_min].hh.rh = -1073741824;
        }
        mem[p - mem_min].hh.rh = q;
        mem[q - mem_min].hh.lh = mem[r - mem_min].hh.lh;
        p = q;
        r = mem[r - mem_min].hh.rh;
      }
      return p;
    } else {
      old_setting = selector;
      selector = 21;
      b = pool_ptr;
      switch (cur_val_level) {
      case 0:
        print_int(cur_val);
        break;
      case 1:
        print_scaled(cur_val);
        print(397);
        break;
      case 2:
        print_spec(cur_val, 397);
        delete_glue_ref(cur_val);
        break;
      case 3:
        print_spec(cur_val, 337);
        delete_glue_ref(cur_val);
        break;
      }
      selector = old_setting;
      return str_toks(b);
    }
  }
  void ins_the_toks() {
    mem[mem_max - mem_min - 12].hh.rh = the_toks();
    begin_token_list(mem[mem_max - mem_min - 3].hh.rh, 4);
  }
  void conv_toks() {
    char old_setting;
    small_number save_scanner_status;
    pool_pointer b;
    char c = cur_chr;
    switch (c) {
    case 0:
    case 1:
      scan_int();
      break;
    case 2:
    case 3:
      save_scanner_status = scanner_status;
      scanner_status = 0;
      get_token();
      scanner_status = save_scanner_status;
      break;
    case 4:
      scan_font_ident();
      break;
    case 5:
      if (!job_name)
        open_log_file();
      break;
    }
    old_setting = selector;
    selector = 21;
    b = pool_ptr;
    switch (c) {
    case 0:
      print_int(cur_val);
      break;
    case 1:
      print_roman_int(cur_val);
      break;
    case 2:
      if (cur_cs)
        sprint_cs(cur_cs);
      else
        print_char(cur_chr);
      break;
    case 3:
      print_meaning();
      break;
    case 4:
      print(font_name[cur_val]);
      if (font_size[cur_val] != font_dsize[cur_val]) {
        print(741);
        print_scaled(font_size[cur_val]);
        print(397);
      }
      break;
    case 5:
      print(job_name);
      break;
    }
    selector = old_setting;
    mem[mem_max - mem_min - 12].hh.rh = str_toks(b);
    begin_token_list(mem[mem_max - mem_min - 3].hh.rh, 4);
  }
  halfword scan_toks(bool macro_def, bool xpand) {
    halfword t = 3120, s, p, q, unbalance = 1, hash_brace = 0;
    if (macro_def)
      scanner_status = 2;
    else
      scanner_status = 5;
    warning_index = cur_cs;
    def_ref = get_avail();
    mem[def_ref - mem_min].hh.lh = -1073741824;
    p = def_ref;
    if (macro_def) {
      while (true) {
        get_token();
        if (cur_tok < 768)
          goto _L31;
        if (cur_cmd == 6) {
          s = cur_chr + 3328;
          get_token();
          if (cur_cmd == 1) {
            hash_brace = cur_tok;
            q = get_avail();
            mem[p - mem_min].hh.rh = q;
            mem[q - mem_min].hh.lh = cur_tok;
            p = q;
            q = get_avail();
            mem[p - mem_min].hh.rh = q;
            mem[q - mem_min].hh.lh = 3584;
            p = q;
            goto _L30;
          }
          if (t == 3129) {
            print_nl(262);
            print(744);
            help_ptr = 1;
            help_line[0] = 745;
            error();
          } else {
            ++t;
            if (cur_tok != t) {
              print_nl(262);
              print(746);
              help_ptr = 2;
              help_line[1] = 747;
              help_line[0] = 748;
              back_error();
            }
            cur_tok = s;
          }
        }
        q = get_avail();
        mem[p - mem_min].hh.rh = q;
        mem[q - mem_min].hh.lh = cur_tok;
        p = q;
      }
    _L31:
      q = get_avail();
      mem[p - mem_min].hh.rh = q;
      mem[q - mem_min].hh.lh = 3584;
      p = q;
      if (cur_cmd == 2) {
        print_nl(262);
        print(657);
        ++align_state;
        help_ptr = 2;
        help_line[1] = 742;
        help_line[0] = 743;
        error();
        goto _L40;
      }
    _L30:;
    } else {
      scan_left_brace();
    }
    while (true) {
      if (xpand) {
        while (true) {
          get_next();
          if (cur_cmd <= 100)
            goto _L32;
          if (cur_cmd != 109) {
            expand();
          } else {
            q = the_toks();
            if (mem[mem_max - mem_min - 3].hh.rh != (-1073741824)) {
              mem[p - mem_min].hh.rh = mem[mem_max - mem_min - 3].hh.rh;
              p = q;
            }
          }
        }
      _L32:
        x_token();
      } else {
        get_token();
      }
      if (cur_tok < 768) {
        if (cur_cmd < 2) {
          ++unbalance;
        } else {
          --unbalance;
          if (!unbalance)
            goto _L40;
        }
      } else if (cur_cmd == 6) {
        if (macro_def) {
          s = cur_tok;
          if (xpand)
            get_x_token();
          else
            get_token();
          if (cur_cmd != 6) {
            if ((cur_tok <= 3120) || (cur_tok > t)) {
              print_nl(262);
              print(749);
              sprint_cs(warning_index);
              help_ptr = 3;
              help_line[2] = 750;
              help_line[1] = 751;
              help_line[0] = 752;
              back_error();
              cur_tok = s;
            } else {
              cur_tok = cur_chr + 1232;
            }
          }
        }
      }
      q = get_avail();
      mem[p - mem_min].hh.rh = q;
      mem[q - mem_min].hh.lh = cur_tok;
      p = q;
    }
  _L40:
    scanner_status = 0;
    if (!hash_brace)
      return p;
    q = get_avail();
    mem[p - mem_min].hh.rh = q;
    mem[q - mem_min].hh.lh = hash_brace;
    p = q;
    return p;
  }
  void read_toks(integer n, halfword r) {
    halfword p, q;
    integer s;
    small_number m;
    scanner_status = 2;
    warning_index = r;
    def_ref = get_avail();
    mem[def_ref - mem_min].hh.lh = -1073741824;
    p = def_ref;
    q = get_avail();
    mem[p - mem_min].hh.rh = q;
    mem[q - mem_min].hh.lh = 3584;
    p = q;
    if (((unsigned)n) > 15)
      m = 16;
    else
      m = n;
    s = align_state;
    align_state = 1000000;
    do {
      begin_file_reading();
      cur_input.name_field = m + 1;
      if (read_open[m] == 2) {
        if (interaction > 1) {
          if (n < 0) {
            print(338);
            term_input();
          } else {
            print_ln();
            sprint_cs(r);
            print(61);
            term_input();
            n = -1;
          }
        } else {
          fatal_error(753);
        }
      } else if (read_open[m] == 1) {
        if (input_ln(read_file[m], false)) {
          read_open[m] = 0;
        } else {
          a_close(read_file[m]);
          read_open[m] = 2;
        }
      } else if (!input_ln(read_file[m], true)) {
        a_close(read_file[m]);
        read_open[m] = 2;
        if (align_state != 1000000) {
          runaway();
          print_nl(262);
          print(754);
          print_esc(534);
          help_ptr = 1;
          help_line[0] = 755;
          align_state = 1000000;
          error();
        }
      }
      cur_input.limit_field = last;
      if (((unsigned)eqtb[12211].int_) > 255)
        --cur_input.limit_field;
      else
        buffer[cur_input.limit_field] = eqtb[12211].int_;
      first = cur_input.limit_field + 1;
      cur_input.loc_field = cur_input.start_field;
      cur_input.state_field = 33;
      while (true) {
        get_token();
        if (!cur_tok)
          goto _L30;
        if (align_state < 1000000) {
          do {
            get_token();
          } while (cur_tok);
          align_state = 1000000;
          goto _L30;
        }
        q = get_avail();
        mem[p - mem_min].hh.rh = q;
        mem[q - mem_min].hh.lh = cur_tok;
        p = q;
      }
    _L30:
      end_file_reading();
    } while (align_state != 1000000);
    cur_val = def_ref;
    scanner_status = 0;
    align_state = s;
  }
  void pass_text() {
    integer l = 0;
    small_number save_scanner_status = scanner_status;
    scanner_status = 1;
    skip_line = line;
    while (true) {
      get_next();
      if (cur_cmd == 106) {
        if (!l)
          goto _L30;
        if (cur_chr == 2)
          --l;
      } else if (cur_cmd == 105)
        ++l;
    }
  _L30:
    scanner_status = save_scanner_status;
  }
  void change_if_limit(small_number l, halfword p) {
    halfword q;
    if (p == cond_ptr) {
      if_limit = l;
    } else {
      q = cond_ptr;
      while (true) {
        if (q == (-1073741824))
          confusion(756);
        if (mem[q - mem_min].hh.rh == p) {
          mem[q - mem_min].hh.U2.b0 = l;
          goto _L10;
        }
        q = mem[q - mem_min].hh.rh;
      }
    }
  _L10:;
  }
  void conditional() {
    bool b;
    char r;
    integer m, n;
    halfword q;
    small_number save_scanner_status;
    halfword save_cond_ptr;
    small_number this_if;
    halfword p = get_node(2);
    mem[p - mem_min].hh.rh = cond_ptr;
    mem[p - mem_min].hh.U2.b0 = if_limit;
    mem[p - mem_min].hh.U2.b1 = cur_if;
    mem[p - mem_min + 1].int_ = if_line;
    cond_ptr = p;
    cur_if = cur_chr;
    if_limit = 1;
    if_line = line;
    save_cond_ptr = cond_ptr;
    this_if = cur_chr;
    switch (this_if) {
    case 0:
    case 1:
      get_x_token();
      if (!cur_cmd) {
        if (cur_chr == 257) {
          cur_cmd = 13;
          cur_chr = cur_tok - 4096;
        }
      }
      if ((cur_cmd > 13) || (cur_chr > 255)) {
        m = 0;
        n = 256;
      } else {
        m = cur_cmd;
        n = cur_chr;
      }
      get_x_token();
      if (!cur_cmd) {
        if (cur_chr == 257) {
          cur_cmd = 13;
          cur_chr = cur_tok - 4096;
        }
      }
      if ((cur_cmd > 13) || (cur_chr > 255)) {
        cur_cmd = 0;
        cur_chr = 256;
      }
      if (!this_if)
        b = (n == cur_chr);
      else
        b = (m == cur_cmd);
      break;
    case 2:
    case 3:
      if (this_if == 2)
        scan_int();
      else
        scan_dimen(false, false, false);
      n = cur_val;
      do {
        get_x_token();
      } while (cur_cmd == 10);
      if ((cur_tok >= 3132) && (cur_tok <= 3134)) {
        r = cur_tok - 3072;
      } else {
        print_nl(262);
        print(780);
        print_cmd_chr(105, this_if);
        help_ptr = 1;
        help_line[0] = 781;
        back_error();
        r = 61;
      }
      if (this_if == 2)
        scan_int();
      else
        scan_dimen(false, false, false);
      switch (r) {
      case 60:
        b = (n < cur_val);
        break;
      case 61:
        b = (n == cur_val);
        break;
      case 62:
        b = (n > cur_val);
        break;
      }
      break;
    case 4:
      scan_int();
      b = cur_val & 1;
      break;
    case 5:
      b = (abs(cur_list.mode_field) == 1);
      break;
    case 6:
      b = (abs(cur_list.mode_field) == 102);
      break;
    case 7:
      b = (abs(cur_list.mode_field) == 203);
      break;
    case 8:
      b = (cur_list.mode_field < 0);
      break;
    case 9:
    case 10:
    case 11:
      scan_eight_bit_int();
      p = eqtb[cur_val + 10578].hh.rh;
      if (this_if == 9) {
        b = (p == (-1073741824));
      } else if (p == (-1073741824)) {
        b = false;
      } else if (this_if == 10)
        b = (mem[p - mem_min].hh.U2.b0 == 0);
      else
        b = (mem[p - mem_min].hh.U2.b0 == 1);
      break;
    case 12:
      save_scanner_status = scanner_status;
      scanner_status = 0;
      get_next();
      n = cur_cs;
      p = cur_cmd;
      q = cur_chr;
      get_next();
      if (cur_cmd != p) {
        b = false;
      } else if (cur_cmd < 111) {
        b = (cur_chr == q);
      } else {
        p = mem[cur_chr - mem_min].hh.rh;
        q = mem[eqtb[n].hh.rh - mem_min].hh.rh;
        if (p == q) {
          b = true;
        } else {
          while ((p != (-1073741824)) && (q != (-1073741824))) {
            if (mem[p - mem_min].hh.lh != mem[q - mem_min].hh.lh) {
              p = -1073741824;
            } else {
              p = mem[p - mem_min].hh.rh;
              q = mem[q - mem_min].hh.rh;
            }
          }
          b = ((p == (-1073741824)) && (q == (-1073741824)));
        }
      }
      scanner_status = save_scanner_status;
      break;
    case 13:
      scan_four_bit_int();
      b = (read_open[cur_val] == 2);
      break;
    case 14:
      b = true;
      break;
    case 15:
      b = false;
      break;
    case 16:
      scan_int();
      n = cur_val;
      if (eqtb[12199].int_ > 1) {
        begin_diagnostic();
        print(782);
        print_int(n);
        print_char(125);
        end_diagnostic(false);
      }
      while (n) {
        pass_text();
        if (cond_ptr == save_cond_ptr) {
          if (cur_chr != 4)
            goto _L50;
          --n;
          continue;
        }
        if (cur_chr != 2)
          continue;
        p = cond_ptr;
        if_line = mem[p - mem_min + 1].int_;
        cur_if = mem[p - mem_min].hh.U2.b1;
        if_limit = mem[p - mem_min].hh.U2.b0;
        cond_ptr = mem[p - mem_min].hh.rh;
        free_node(p, 2);
      }
      change_if_limit(4, save_cond_ptr);
      goto _L10;
      break;
    }
    if (eqtb[12199].int_ > 1) {
      begin_diagnostic();
      if (b)
        print(778);
      else
        print(779);
      end_diagnostic(false);
    }
    if (b) {
      change_if_limit(3, save_cond_ptr);
      goto _L10;
    }
    while (true) {
      pass_text();
      if (cond_ptr == save_cond_ptr) {
        if (cur_chr != 4)
          goto _L50;
        print_nl(262);
        print(776);
        print_esc(774);
        help_ptr = 1;
        help_line[0] = 777;
        error();
        continue;
      }
      if (cur_chr != 2)
        continue;
      p = cond_ptr;
      if_line = mem[p - mem_min + 1].int_;
      cur_if = mem[p - mem_min].hh.U2.b1;
      if_limit = mem[p - mem_min].hh.U2.b0;
      cond_ptr = mem[p - mem_min].hh.rh;
      free_node(p, 2);
    }
  _L50:
    if (cur_chr == 2) {
      p = cond_ptr;
      if_line = mem[p - mem_min + 1].int_;
      cur_if = mem[p - mem_min].hh.U2.b1;
      if_limit = mem[p - mem_min].hh.U2.b0;
      cond_ptr = mem[p - mem_min].hh.rh;
      free_node(p, 2);
    } else {
      if_limit = 2;
    }
  _L10:;
  }
  void begin_name() {
    area_delimiter = 0;
    ext_delimiter = 0;
  }
  bool more_name(ASCII_code c) {
    if (c == 32) {
      return false;
    } else {
      if (pool_ptr + 1 > pool_size)
        overflow(257, pool_size - init_pool_ptr);
      str_pool[pool_ptr] = c;
      ++pool_ptr;
      if ((c == 62) || (c == 58)) {
        area_delimiter = pool_ptr - str_start[str_ptr];
        ext_delimiter = 0;
      } else if ((c == 46) && (!ext_delimiter))
        ext_delimiter = pool_ptr - str_start[str_ptr];
      return true;
    }
  }
  void end_name() {
    if (str_ptr + 3 > max_strings)
      overflow(258, max_strings - init_str_ptr);
    if (!area_delimiter) {
      cur_area = 338;
    } else {
      cur_area = str_ptr;
      str_start[str_ptr + 1] = str_start[str_ptr] + area_delimiter;
      ++str_ptr;
    }
    if (!ext_delimiter) {
      cur_ext = 338;
      cur_name = make_string();
      return;
    }
    cur_name = str_ptr;
    str_start[str_ptr + 1] =
        str_start[str_ptr] + ext_delimiter - area_delimiter - 1;
    ++str_ptr;
    cur_ext = make_string();
  }
  void pack_file_name(str_number n, str_number a, str_number e) {
    integer k = 0;
    ASCII_code c;
    pool_pointer j, N1;
    for (N1 = str_start[a + 1], j = str_start[a]; j <= (N1 - 1); ++j) {
      c = str_pool[j];
      ++k;
      if (k <= file_name_size)
        name_of_file[k - 1] = xchr[c];
    }
    for (N1 = str_start[n + 1], j = str_start[n]; j <= (N1 - 1); ++j) {
      c = str_pool[j];
      ++k;
      if (k <= file_name_size)
        name_of_file[k - 1] = xchr[c];
    }
    for (N1 = str_start[e + 1], j = str_start[e]; j <= (N1 - 1); ++j) {
      c = str_pool[j];
      ++k;
      if (k <= file_name_size)
        name_of_file[k - 1] = xchr[c];
    }
    if (k <= file_name_size)
      name_length = k;
    else
      name_length = file_name_size;
    for (k = name_length + 1; k <= file_name_size; ++k)
      name_of_file[k - 1] = ' ';
  }
  void pack_buffered_name(small_number n, integer a, integer b) {
    integer k = 0, j;
    ASCII_code c;
    if (n + b - a + 5 > file_name_size)
      b = a + file_name_size - n - 5;
    for (j = 1; j <= n; ++j) {
      c = xord[TEX_format_default[j - 1]];
      ++k;
      if (k <= file_name_size)
        name_of_file[k - 1] = xchr[c];
    }
    for (j = a; j <= b; ++j) {
      c = buffer[j];
      ++k;
      if (k <= file_name_size)
        name_of_file[k - 1] = xchr[c];
    }
    for (j = 17; j <= 20; ++j) {
      c = xord[TEX_format_default[j - 1]];
      ++k;
      if (k <= file_name_size)
        name_of_file[k - 1] = xchr[c];
    }
    if (k <= file_name_size)
      name_length = k;
    else
      name_length = file_name_size;
    for (k = name_length + 1; k <= file_name_size; ++k)
      name_of_file[k - 1] = ' ';
  }
  str_number make_name_string() {
    int k, N;
    if ((pool_ptr + name_length > pool_size) || (str_ptr == max_strings) ||
        (pool_ptr - str_start[str_ptr] > 0)) {
      return 63;
    } else {
      for (N = name_length, k = 1; k <= N; ++k) {
        str_pool[pool_ptr] = xord[name_of_file[k - 1]];
        ++pool_ptr;
      }
      return make_string();
    }
  }
  str_number a_make_name_string(FILE *f) { return make_name_string(); }
  str_number b_make_name_string(FILE *f) { return make_name_string(); }
  str_number w_make_name_string(FILE *f) { return make_name_string(); }
  void scan_file_name() {
    name_in_progress = true;
    begin_name();
    do {
      get_x_token();
    } while (cur_cmd == 10);
    while (true) {
      if ((cur_cmd > 12) || (cur_chr > 255)) {
        back_input();
        goto _L30;
      }
      if (!more_name(cur_chr))
        goto _L30;
      get_x_token();
    }
  _L30:
    end_name();
    name_in_progress = false;
  }
  void pack_job_name(str_number s) {
    cur_area = 338;
    cur_ext = s;
    cur_name = job_name;
    pack_file_name(cur_name, cur_area, cur_ext);
  }
  void prompt_file_name(str_number s, str_number e) {
    int k;
    if (s == 786) {
      print_nl(262);
      print(787);
    } else {
      print_nl(262);
      print(788);
    }
    print_file_name(cur_name, cur_area, cur_ext);
    print(789);
    if (e == 790)
      show_context();
    print_nl(791);
    print(s);
    if (interaction < 2)
      fatal_error(792);
    break_in(term_in, true);
    print(568);
    term_input();
    begin_name();
    k = first;
    while ((buffer[k] == 32) && (k < last))
      ++k;
    while (true) {
      if (k == last)
        goto _L30;
      if (!more_name(buffer[k]))
        goto _L30;
      ++k;
    }
  _L30:
    end_name();
    if (cur_ext == 338)
      cur_ext = e;
    pack_file_name(cur_name, cur_area, cur_ext);
  }
  virtual void open_log_file() {
    int k, l;
    char months[36];
    int N;
    char old_setting = selector;
    if (!job_name)
      job_name = 795;
    pack_job_name(796);
    while (!a_open_out(log_file)) {
      selector = 17;
      prompt_file_name(798, 796);
    }
    log_name = a_make_name_string(log_file);
    selector = 18;
    log_opened = true;
    fprintf(log_file, "This is TeX, Version 3.14159265");
    slow_print(format_ident);
    print(799);
    print_int(eqtb[12184].int_);
    print_char(32);
    memcpy(months, "JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC", 36);
    for (N = eqtb[12185].int_ * 3, k = (eqtb[12185].int_ * 3) - 2; k <= N; ++k)
      fprintf(log_file, "%c", months[k - 1]);
    print_char(32);
    print_int(eqtb[12186].int_);
    print_char(32);
    print_two(eqtb[12183].int_ / 60);
    print_char(58);
    print_two(eqtb[12183].int_ % 60);
    input_stack[input_ptr] = cur_input;
    print_nl(797);
    l = input_stack[0].limit_field;
    if (buffer[l] == eqtb[12211].int_)
      --l;
    for (k = 1; k <= l; ++k)
      print(buffer[k]);
    print_ln();
    selector = old_setting + 2;
  }
  void start_input() {
    scan_file_name();
    if (cur_ext == 338)
      cur_ext = 790;
    pack_file_name(cur_name, cur_area, cur_ext);
    while (true) {
      begin_file_reading();
      if (a_open_in(input_file[cur_input.index_field]))
        goto _L30;
      if (cur_area == 338) {
        pack_file_name(cur_name, 783, cur_ext);
        if (a_open_in(input_file[cur_input.index_field]))
          goto _L30;
      }
      end_file_reading();
      prompt_file_name(786, 790);
    }
  _L30:
    cur_input.name_field =
        a_make_name_string(input_file[cur_input.index_field]);
    if (!job_name) {
      job_name = cur_name;
      open_log_file();
    }
    if (term_offset + str_start[cur_input.name_field + 1] -
            str_start[cur_input.name_field] >
        max_print_line - 2) {
      print_ln();
    } else if ((term_offset > 0) || (file_offset > 0))
      print_char(32);
    print_char(40);
    ++open_parens;
    slow_print(cur_input.name_field);
    fflush(term_out);
    errno = 0;
    cur_input.state_field = 33;
    if (cur_input.name_field == (str_ptr - 1)) {
      --str_ptr;
      pool_ptr = str_start[str_ptr];
      cur_input.name_field = cur_name;
    }
    line = 1;
    input_ln(input_file[cur_input.index_field], false);
    firm_up_the_line();
    if (((unsigned)eqtb[12211].int_) > 255)
      --cur_input.limit_field;
    else
      buffer[cur_input.limit_field] = eqtb[12211].int_;
    first = cur_input.limit_field + 1;
    cur_input.loc_field = cur_input.start_field;
  }

  internal_font_number read_font_info(halfword u, str_number nom,
                                      str_number aire, scaled s);

 void char_warning(internal_font_number f, eight_bits c) {
    if (eqtb[12198].int_ <= 0)
      return;
    begin_diagnostic();
    print_nl(824);
    print(c);
    print(825);
    slow_print(font_name[f]);
    print_char(33);
    end_diagnostic(false);
  }
  halfword new_character(internal_font_number f, eight_bits c) {
    halfword result, p;
    if (font_bc[f] <= c) {
      if (font_ec[f] >= c) {
        if (font_info[char_base[f] + c].qqqq.b0 > 0) {
          p = get_avail();
          mem[p - mem_min].hh.U2.b0 = f;
          mem[p - mem_min].hh.U2.b1 = c;
          result = p;
          goto _L10;
        }
      }
    }
    char_warning(f, c);
    result = -1073741824;
  _L10:
    return result;
  }
  void write_dvi(dvi_index a, dvi_index b) {
    dvi_index k;
    for (k = a; k <= b; ++k)
      fprintf(dvi_file, "%c", dvi_buf[k]);
  }
  void dvi_swap() {
    if (dvi_limit == dvi_buf_size) {
      write_dvi(0, half_buf - 1);
      dvi_limit = half_buf;
      dvi_offset += dvi_buf_size;
      dvi_ptr = 0;
    } else {
      write_dvi(half_buf, dvi_buf_size - 1);
      dvi_limit = dvi_buf_size;
    }
    dvi_gone += half_buf;
  }
  void dvi_four(integer x) {
    if (x >= 0) {
      dvi_buf[dvi_ptr] = x / 16777216;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
    } else {
      x += 1073741824;
      x += 1073741824;
      dvi_buf[dvi_ptr] = (x / 16777216) + 128;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
    }
    x &= 16777215;
    dvi_buf[dvi_ptr] = x / 65536;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    x &= 65535;
    dvi_buf[dvi_ptr] = x / 256;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    dvi_buf[dvi_ptr] = x & 255;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
  }
  void dvi_pop(integer l) {
    if ((l == (dvi_offset + dvi_ptr)) && (dvi_ptr > 0)) {
      --dvi_ptr;
      return;
    }
    dvi_buf[dvi_ptr] = 142;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
  }
  void dvi_font_def(internal_font_number f) {
    pool_pointer k, N;
    dvi_buf[dvi_ptr] = 243;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    dvi_buf[dvi_ptr] = f - 1;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    dvi_buf[dvi_ptr] = font_check[f].b0;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    dvi_buf[dvi_ptr] = font_check[f].b1;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    dvi_buf[dvi_ptr] = font_check[f].b2;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    dvi_buf[dvi_ptr] = font_check[f].b3;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    dvi_four(font_size[f]);
    dvi_four(font_dsize[f]);
    dvi_buf[dvi_ptr] = str_start[font_area[f] + 1] - str_start[font_area[f]];
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    dvi_buf[dvi_ptr] = str_start[font_name[f] + 1] - str_start[font_name[f]];
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    for (N = str_start[font_area[f] + 1], k = str_start[font_area[f]];
         k <= (N - 1); ++k) {
      dvi_buf[dvi_ptr] = str_pool[k];
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
    }
    for (N = str_start[font_name[f] + 1], k = str_start[font_name[f]];
         k <= (N - 1); ++k) {
      dvi_buf[dvi_ptr] = str_pool[k];
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
    }
  }
  void movement(scaled w, eight_bits o) {
    small_number mstate = 0;
    halfword p;
    integer k;
    halfword q = get_node(3);
    mem[q - mem_min + 1].int_ = w;
    mem[q - mem_min + 2].int_ = dvi_offset + dvi_ptr;
    if (o == 157) {
      mem[q - mem_min].hh.rh = down_ptr;
      down_ptr = q;
    } else {
      mem[q - mem_min].hh.rh = right_ptr;
      right_ptr = q;
    }
    p = mem[q - mem_min].hh.rh;
    while (p != (-1073741824)) {
      if (mem[p - mem_min + 1].int_ == w) {
        switch (mstate + mem[p - mem_min].hh.lh) {
        case 3:
        case 4:
        case 15:
        case 16:
          if (mem[p - mem_min + 2].int_ < dvi_gone) {
            goto _L45;
          } else {
            k = mem[p - mem_min + 2].int_ - dvi_offset;
            if (k < 0)
              k += dvi_buf_size;
            dvi_buf[k] += 5;
            mem[p - mem_min].hh.lh = 1;
            goto _L40;
          }
          break;
        case 5:
        case 9:
        case 11:
          if (mem[p - mem_min + 2].int_ < dvi_gone) {
            goto _L45;
          } else {
            k = mem[p - mem_min + 2].int_ - dvi_offset;
            if (k < 0)
              k += dvi_buf_size;
            dvi_buf[k] += 10;
            mem[p - mem_min].hh.lh = 2;
            goto _L40;
          }
          break;
        case 1:
        case 2:
        case 8:
        case 13:
          goto _L40;
          break;
        default:
          break;
        }
      } else {
        switch (mstate + mem[p - mem_min].hh.lh) {
        case 1:
          mstate = 6;
          break;
        case 2:
          mstate = 12;
          break;
        case 8:
        case 13:
          goto _L45;
          break;
        default:
          break;
        }
      }
      p = mem[p - mem_min].hh.rh;
    }
  _L45:
    mem[q - mem_min].hh.lh = 3;
    if (abs(w) >= 8388608) {
      dvi_buf[dvi_ptr] = o + 3;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      dvi_four(w);
      goto _L10;
    }
    if (abs(w) >= 32768) {
      dvi_buf[dvi_ptr] = o + 2;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      if (w < 0)
        w += 16777216;
      dvi_buf[dvi_ptr] = w / 65536;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      w &= 65535;
      goto _L2;
    }
    if (abs(w) >= 128) {
      dvi_buf[dvi_ptr] = o + 1;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      if (w < 0)
        w += 65536;
      goto _L2;
    }
    dvi_buf[dvi_ptr] = o;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    if (w < 0)
      w += 256;
    goto _L1;
  _L2:
    dvi_buf[dvi_ptr] = w / 256;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
  _L1:
    dvi_buf[dvi_ptr] = w & 255;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    goto _L10;
  _L40:
    mem[q - mem_min].hh.lh = mem[p - mem_min].hh.lh;
    if (mem[q - mem_min].hh.lh == 1) {
      dvi_buf[dvi_ptr] = o + 4;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      while (mem[q - mem_min].hh.rh != p) {
        q = mem[q - mem_min].hh.rh;
        switch (mem[q - mem_min].hh.lh) {
        case 3:
          mem[q - mem_min].hh.lh = 5;
          break;
        case 4:
          mem[q - mem_min].hh.lh = 6;
          break;
        default:
          break;
        }
      }
    } else {
      dvi_buf[dvi_ptr] = o + 9;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      while (mem[q - mem_min].hh.rh != p) {
        q = mem[q - mem_min].hh.rh;
        switch (mem[q - mem_min].hh.lh) {
        case 3:
          mem[q - mem_min].hh.lh = 4;
          break;
        case 5:
          mem[q - mem_min].hh.lh = 6;
          break;
        default:
          break;
        }
      }
    }
  _L10:;
  }
  void prune_movements(integer l) {
    halfword p;
    while (down_ptr != (-1073741824)) {
      if (mem[down_ptr - mem_min + 2].int_ < l)
        goto _L30;
      p = down_ptr;
      down_ptr = mem[p - mem_min].hh.rh;
      free_node(p, 3);
    }
  _L30:
    while (right_ptr != (-1073741824)) {
      if (mem[right_ptr - mem_min + 2].int_ < l)
        goto _L10;
      p = right_ptr;
      right_ptr = mem[p - mem_min].hh.rh;
      free_node(p, 3);
    }
  _L10:;
  }
  void special_out(halfword p) {
    char old_setting;
    pool_pointer k, N;
    if (cur_h != dvi_h) {
      movement(cur_h - dvi_h, 143);
      dvi_h = cur_h;
    }
    if (cur_v != dvi_v) {
      movement(cur_v - dvi_v, 157);
      dvi_v = cur_v;
    }
    old_setting = selector;
    selector = 21;
    show_token_list(mem[mem[p - mem_min + 1].hh.rh - mem_min].hh.rh,
                    -1073741824, pool_size - pool_ptr);
    selector = old_setting;
    if (pool_ptr + 1 > pool_size)
      overflow(257, pool_size - init_pool_ptr);
    if (pool_ptr - str_start[str_ptr] < 256) {
      dvi_buf[dvi_ptr] = 239;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      dvi_buf[dvi_ptr] = pool_ptr - str_start[str_ptr];
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
    } else {
      dvi_buf[dvi_ptr] = 242;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      dvi_four(pool_ptr - str_start[str_ptr]);
    }
    for (N = pool_ptr, k = str_start[str_ptr]; k <= (N - 1); ++k) {
      dvi_buf[dvi_ptr] = str_pool[k];
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
    }
    pool_ptr = str_start[str_ptr];
  }
  void write_out(halfword p) {
    char old_setting;
    integer old_mode;
    small_number j;
    halfword r;
    halfword q = get_avail();
    mem[q - mem_min].hh.lh = 637;
    r = get_avail();
    mem[q - mem_min].hh.rh = r;
    mem[r - mem_min].hh.lh = 13617;
    begin_token_list(q, 4);
    begin_token_list(mem[p - mem_min + 1].hh.rh, 15);
    q = get_avail();
    mem[q - mem_min].hh.lh = 379;
    begin_token_list(q, 4);
    old_mode = cur_list.mode_field;
    cur_list.mode_field = 0;
    cur_cs = write_loc;
    q = scan_toks(false, true);
    get_token();
    if (cur_tok != 13617) {
      print_nl(262);
      print(1296);
      help_ptr = 2;
      help_line[1] = 1297;
      help_line[0] = 1011;
      error();
      do {
        get_token();
      } while (cur_tok != 13617);
    }
    cur_list.mode_field = old_mode;
    end_token_list();
    old_setting = selector;
    j = mem[p - mem_min + 1].hh.lh;
    if (write_open[j]) {
      selector = j;
    } else {
      if ((j == 17) && (selector == 19))
        selector = 18;
      print_nl(338);
    }
    token_show(def_ref);
    print_ln();
    flush_list(def_ref);
    selector = old_setting;
  }
  void out_what(halfword p) {
    small_number j;
    switch (mem[p - mem_min].hh.U2.b1) {
    case 0:
    case 1:
    case 2:
      if (!doing_leaders) {
        j = mem[p - mem_min + 1].hh.lh;
        if (mem[p - mem_min].hh.U2.b1 == 1) {
          write_out(p);
        } else {
          if (write_open[j])
            a_close(write_file[j]);
          if (mem[p - mem_min].hh.U2.b1 == 2) {
            write_open[j] = false;
          } else if (j < 16) {
            cur_name = mem[p - mem_min + 1].hh.rh;
            cur_area = mem[p - mem_min + 2].hh.lh;
            cur_ext = mem[p - mem_min + 2].hh.rh;
            if (cur_ext == 338)
              cur_ext = 790;
            pack_file_name(cur_name, cur_area, cur_ext);
            while (!a_open_out(write_file[j]))
              prompt_file_name(1299, 790);
            write_open[j] = true;
          }
        }
      }
      break;
    case 3:
      special_out(p);
      break;
    case 4:
      // blank case
      break;
    default:
      confusion(1298);
      break;
    }
  }
  void hlist_out() {
    scaled base_line, left_edge, save_h, save_v, leader_wd, lx, edge, cur_g = 0;
    integer save_loc;
    halfword leader_box;
    bool outer_doing_leaders;
    double glue_temp, cur_glue = 0.0;
    halfword this_box = temp_ptr;
    glue_ord g_order = mem[this_box - mem_min + 5].hh.U2.b1;
    char g_sign = mem[this_box - mem_min + 5].hh.U2.b0;
    halfword p = mem[this_box - mem_min + 5].hh.rh;
    ++cur_s;
    if (cur_s > 0) {
      dvi_buf[dvi_ptr] = 141;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
    }
    if (cur_s > max_push)
      max_push = cur_s;
    save_loc = dvi_offset + dvi_ptr;
    base_line = cur_v;
    left_edge = cur_h;
    while (p != (-1073741824)) {
    _L21:
      if (p >= hi_mem_min) {
        if (cur_h != dvi_h) {
          movement(cur_h - dvi_h, 143);
          dvi_h = cur_h;
        }
        if (cur_v != dvi_v) {
          movement(cur_v - dvi_v, 157);
          dvi_v = cur_v;
        }
        do {
          f = mem[p - mem_min].hh.U2.b0;
          c = mem[p - mem_min].hh.U2.b1;
          if (f != dvi_f) {
            if (!font_used[f]) {
              dvi_font_def(f);
              font_used[f] = true;
            }
            if (f <= 64) {
              dvi_buf[dvi_ptr] = f + 170;
              ++dvi_ptr;
              if (dvi_ptr == dvi_limit)
                dvi_swap();
            } else {
              dvi_buf[dvi_ptr] = 235;
              ++dvi_ptr;
              if (dvi_ptr == dvi_limit)
                dvi_swap();
              dvi_buf[dvi_ptr] = f - 1;
              ++dvi_ptr;
              if (dvi_ptr == dvi_limit)
                dvi_swap();
            }
            dvi_f = f;
          }
          if (c >= 128) {
            dvi_buf[dvi_ptr] = 128;
            ++dvi_ptr;
            if (dvi_ptr == dvi_limit)
              dvi_swap();
          }
          dvi_buf[dvi_ptr] = c;
          ++dvi_ptr;
          if (dvi_ptr == dvi_limit)
            dvi_swap();
          cur_h +=
              font_info[width_base[f] + font_info[char_base[f] + c].qqqq.b0]
                  .int_;
          p = mem[p - mem_min].hh.rh;
        } while (p >= hi_mem_min);
        dvi_h = cur_h;
        continue;
      }
      switch (mem[p - mem_min].hh.U2.b0) {
      case 0:
      case 1:
        if (mem[p - mem_min + 5].hh.rh == (-1073741824)) {
          cur_h += mem[p - mem_min + 1].int_;
        } else {
          save_h = dvi_h;
          save_v = dvi_v;
          cur_v = base_line + mem[p - mem_min + 4].int_;
          temp_ptr = p;
          edge = cur_h;
          if (mem[p - mem_min].hh.U2.b0 == 1)
            vlist_out();
          else
            hlist_out();
          dvi_h = save_h;
          dvi_v = save_v;
          cur_h = edge + mem[p - mem_min + 1].int_;
          cur_v = base_line;
        }
        break;
      case 2:
        rule_ht = mem[p - mem_min + 3].int_;
        rule_dp = mem[p - mem_min + 2].int_;
        rule_wd = mem[p - mem_min + 1].int_;
        goto _L14;
        break;
      case 8:
        out_what(p);
        break;
      case 10:
        g = mem[p - mem_min + 1].hh.lh;
        rule_wd = mem[g - mem_min + 1].int_ - cur_g;
        if (g_sign) {
          if (g_sign == 1) {
            if (mem[g - mem_min].hh.U2.b0 == g_order) {
              cur_glue += mem[g - mem_min + 2].int_;
              glue_temp = mem[this_box - mem_min + 6].gr * cur_glue;
              if (glue_temp > 1000000000.0) {
                glue_temp = 1000000000.0;
              } else if (glue_temp < (-1000000000.0))
                glue_temp = -1000000000.0;
              cur_g = int(round(glue_temp));
            }
          } else if (mem[g - mem_min].hh.U2.b1 == g_order) {
            cur_glue -= mem[g - mem_min + 3].int_;
            glue_temp = mem[this_box - mem_min + 6].gr * cur_glue;
            if (glue_temp > 1000000000.0) {
              glue_temp = 1000000000.0;
            } else if (glue_temp < (-1000000000.0))
              glue_temp = -1000000000.0;
            cur_g = int(round(glue_temp));
          }
        }
        rule_wd += cur_g;
        if (mem[p - mem_min].hh.U2.b1 >= 100) {
          leader_box = mem[p - mem_min + 1].hh.rh;
          if (mem[leader_box - mem_min].hh.U2.b0 == 2) {
            rule_ht = mem[leader_box - mem_min + 3].int_;
            rule_dp = mem[leader_box - mem_min + 2].int_;
            goto _L14;
          }
          leader_wd = mem[leader_box - mem_min + 1].int_;
          if ((leader_wd > 0) && (rule_wd > 0)) {
            rule_wd += 10;
            edge = cur_h + rule_wd;
            lx = 0;
            if (mem[p - mem_min].hh.U2.b1 == 100) {
              save_h = cur_h;
              cur_h =
                  left_edge + (leader_wd * ((cur_h - left_edge) / leader_wd));
              if (cur_h < save_h)
                cur_h += leader_wd;
            } else {
              lq = rule_wd / leader_wd;
              lr = rule_wd % leader_wd;
              if (mem[p - mem_min].hh.U2.b1 == 101) {
                cur_h += lr / 2;
              } else {
                lx = lr / (lq + 1);
                cur_h += (lr - ((lq - 1) * lx)) / 2;
              }
            }
            while (cur_h + leader_wd <= edge) {
              cur_v = base_line + mem[leader_box - mem_min + 4].int_;
              if (cur_v != dvi_v) {
                movement(cur_v - dvi_v, 157);
                dvi_v = cur_v;
              }
              save_v = dvi_v;
              if (cur_h != dvi_h) {
                movement(cur_h - dvi_h, 143);
                dvi_h = cur_h;
              }
              save_h = dvi_h;
              temp_ptr = leader_box;
              outer_doing_leaders = doing_leaders;
              doing_leaders = true;
              if (mem[leader_box - mem_min].hh.U2.b0 == 1)
                vlist_out();
              else
                hlist_out();
              doing_leaders = outer_doing_leaders;
              dvi_v = save_v;
              dvi_h = save_h;
              cur_v = base_line;
              cur_h = save_h + leader_wd + lx;
            }
            cur_h = edge - 10;
            goto _L15;
          }
        }
        goto _L13;
        break;
      case 11:
      case 9:
        cur_h += mem[p - mem_min + 1].int_;
        break;
      case 6:
        mem[mem_max - mem_min - 12] = mem[p - mem_min + 1];
        mem[mem_max - mem_min - 12].hh.rh = mem[p - mem_min].hh.rh;
        p = mem_max - 12;
        goto _L21;
        break;
      default:
        break;
      }
      goto _L15;
    _L14:
      if (rule_ht == (-1073741824))
        rule_ht = mem[this_box - mem_min + 3].int_;
      if (rule_dp == (-1073741824))
        rule_dp = mem[this_box - mem_min + 2].int_;
      rule_ht += rule_dp;
      if ((rule_ht > 0) && (rule_wd > 0)) {
        if (cur_h != dvi_h) {
          movement(cur_h - dvi_h, 143);
          dvi_h = cur_h;
        }
        cur_v = base_line + rule_dp;
        if (cur_v != dvi_v) {
          movement(cur_v - dvi_v, 157);
          dvi_v = cur_v;
        }
        dvi_buf[dvi_ptr] = 132;
        ++dvi_ptr;
        if (dvi_ptr == dvi_limit)
          dvi_swap();
        dvi_four(rule_ht);
        dvi_four(rule_wd);
        cur_v = base_line;
        dvi_h += rule_wd;
      }
    _L13:
      cur_h += rule_wd;
    _L15:
      p = mem[p - mem_min].hh.rh;
    }
    prune_movements(save_loc);
    if (cur_s > 0)
      dvi_pop(save_loc);
    --cur_s;
  }
  void vlist_out() {
    scaled left_edge, top_edge, save_h, save_v, leader_ht, lx, edge, cur_g = 0;
    integer save_loc;
    halfword leader_box;
    bool outer_doing_leaders;
    double glue_temp, cur_glue = 0.0;
    halfword this_box = temp_ptr;
    glue_ord g_order = mem[this_box - mem_min + 5].hh.U2.b1;
    char g_sign = mem[this_box - mem_min + 5].hh.U2.b0;
    halfword p = mem[this_box - mem_min + 5].hh.rh;
    ++cur_s;
    if (cur_s > 0) {
      dvi_buf[dvi_ptr] = 141;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
    }
    if (cur_s > max_push)
      max_push = cur_s;
    save_loc = dvi_offset + dvi_ptr;
    left_edge = cur_h;
    cur_v -= mem[this_box - mem_min + 3].int_;
    top_edge = cur_v;
    while (p != (-1073741824)) {
      if (p >= hi_mem_min) {
        confusion(827);
      } else {
        switch (mem[p - mem_min].hh.U2.b0) {
        case 0:
        case 1:
          if (mem[p - mem_min + 5].hh.rh == (-1073741824)) {
            cur_v += mem[p - mem_min + 3].int_ + mem[p - mem_min + 2].int_;
          } else {
            cur_v += mem[p - mem_min + 3].int_;
            if (cur_v != dvi_v) {
              movement(cur_v - dvi_v, 157);
              dvi_v = cur_v;
            }
            save_h = dvi_h;
            save_v = dvi_v;
            cur_h = left_edge + mem[p - mem_min + 4].int_;
            temp_ptr = p;
            if (mem[p - mem_min].hh.U2.b0 == 1)
              vlist_out();
            else
              hlist_out();
            dvi_h = save_h;
            dvi_v = save_v;
            cur_v = save_v + mem[p - mem_min + 2].int_;
            cur_h = left_edge;
          }
          break;
        case 2:
          rule_ht = mem[p - mem_min + 3].int_;
          rule_dp = mem[p - mem_min + 2].int_;
          rule_wd = mem[p - mem_min + 1].int_;
          goto _L14;
          break;
        case 8:
          out_what(p);
          break;
        case 10:
          g = mem[p - mem_min + 1].hh.lh;
          rule_ht = mem[g - mem_min + 1].int_ - cur_g;
          if (g_sign) {
            if (g_sign == 1) {
              if (mem[g - mem_min].hh.U2.b0 == g_order) {
                cur_glue += mem[g - mem_min + 2].int_;
                glue_temp = mem[this_box - mem_min + 6].gr * cur_glue;
                if (glue_temp > 1000000000.0) {
                  glue_temp = 1000000000.0;
                } else if (glue_temp < (-1000000000.0))
                  glue_temp = -1000000000.0;
                cur_g = int(round(glue_temp));
              }
            } else if (mem[g - mem_min].hh.U2.b1 == g_order) {
              cur_glue -= mem[g - mem_min + 3].int_;
              glue_temp = mem[this_box - mem_min + 6].gr * cur_glue;
              if (glue_temp > 1000000000.0) {
                glue_temp = 1000000000.0;
              } else if (glue_temp < (-1000000000.0))
                glue_temp = -1000000000.0;
              cur_g = int(round(glue_temp));
            }
          }
          rule_ht += cur_g;
          if (mem[p - mem_min].hh.U2.b1 >= 100) {
            leader_box = mem[p - mem_min + 1].hh.rh;
            if (mem[leader_box - mem_min].hh.U2.b0 == 2) {
              rule_wd = mem[leader_box - mem_min + 1].int_;
              rule_dp = 0;
              goto _L14;
            }
            leader_ht = mem[leader_box - mem_min + 3].int_ +
                        mem[leader_box - mem_min + 2].int_;
            if ((leader_ht > 0) && (rule_ht > 0)) {
              rule_ht += 10;
              edge = cur_v + rule_ht;
              lx = 0;
              if (mem[p - mem_min].hh.U2.b1 == 100) {
                save_v = cur_v;
                cur_v =
                    top_edge + (leader_ht * ((cur_v - top_edge) / leader_ht));
                if (cur_v < save_v)
                  cur_v += leader_ht;
              } else {
                lq = rule_ht / leader_ht;
                lr = rule_ht % leader_ht;
                if (mem[p - mem_min].hh.U2.b1 == 101) {
                  cur_v += lr / 2;
                } else {
                  lx = lr / (lq + 1);
                  cur_v += (lr - ((lq - 1) * lx)) / 2;
                }
              }
              while (cur_v + leader_ht <= edge) {
                cur_h = left_edge + mem[leader_box - mem_min + 4].int_;
                if (cur_h != dvi_h) {
                  movement(cur_h - dvi_h, 143);
                  dvi_h = cur_h;
                }
                save_h = dvi_h;
                cur_v += mem[leader_box - mem_min + 3].int_;
                if (cur_v != dvi_v) {
                  movement(cur_v - dvi_v, 157);
                  dvi_v = cur_v;
                }
                save_v = dvi_v;
                temp_ptr = leader_box;
                outer_doing_leaders = doing_leaders;
                doing_leaders = true;
                if (mem[leader_box - mem_min].hh.U2.b0 == 1)
                  vlist_out();
                else
                  hlist_out();
                doing_leaders = outer_doing_leaders;
                dvi_v = save_v;
                dvi_h = save_h;
                cur_h = left_edge;
                cur_v = save_v - mem[leader_box - mem_min + 3].int_ +
                        leader_ht + lx;
              }
              cur_v = edge - 10;
              goto _L15;
            }
          }
          goto _L13;
          break;
        case 11:
          cur_v += mem[p - mem_min + 1].int_;
          break;
        default:
          break;
        }
        goto _L15;
      _L14:
        if (rule_wd == (-1073741824))
          rule_wd = mem[this_box - mem_min + 1].int_;
        rule_ht += rule_dp;
        cur_v += rule_ht;
        if ((rule_ht > 0) && (rule_wd > 0)) {
          if (cur_h != dvi_h) {
            movement(cur_h - dvi_h, 143);
            dvi_h = cur_h;
          }
          if (cur_v != dvi_v) {
            movement(cur_v - dvi_v, 157);
            dvi_v = cur_v;
          }
          dvi_buf[dvi_ptr] = 137;
          ++dvi_ptr;
          if (dvi_ptr == dvi_limit)
            dvi_swap();
          dvi_four(rule_ht);
          dvi_four(rule_wd);
        }
        goto _L15;
      _L13:
        cur_v += rule_ht;
      }
    _L15:
      p = mem[p - mem_min].hh.rh;
    }
    prune_movements(save_loc);
    if (cur_s > 0)
      dvi_pop(save_loc);
    --cur_s;
  }
  void ship_out(halfword p) {
    integer page_loc;
    char j = 9, k;
    pool_pointer s;
    char old_setting;
    pool_pointer N;
    if (eqtb[12197].int_ > 0) {
      print_nl(338);
      print_ln();
      print(828);
    }
    if (term_offset > (max_print_line - 9)) {
      print_ln();
    } else if ((term_offset > 0) || (file_offset > 0))
      print_char(32);
    print_char(91);
    while ((!eqtb[j + 12218].int_) && (j > 0))
      --j;
    for (k = 0; k <= j; ++k) {
      print_int(eqtb[k + 12218].int_);
      if (k < j)
        print_char(46);
    }
    fflush(term_out);
    errno = 0;
    if (eqtb[12197].int_ > 0) {
      print_char(93);
      begin_diagnostic();
      show_box(p);
      end_diagnostic(true);
    }
    if ((mem[p - mem_min + 3].int_ > 1073741823) ||
        (mem[p - mem_min + 2].int_ > 1073741823) ||
        (mem[p - mem_min + 3].int_ + mem[p - mem_min + 2].int_ +
             eqtb[12749].int_ >
         1073741823) ||
        (mem[p - mem_min + 1].int_ + eqtb[12748].int_ > 1073741823)) {
      print_nl(262);
      print(832);
      help_ptr = 2;
      help_line[1] = 833;
      help_line[0] = 834;
      error();
      if (eqtb[12197].int_ <= 0) {
        begin_diagnostic();
        print_nl(835);
        show_box(p);
        end_diagnostic(true);
      }
      goto _L30;
    }
    if (mem[p - mem_min + 3].int_ + mem[p - mem_min + 2].int_ +
            eqtb[12749].int_ >
        max_v)
      max_v = mem[p - mem_min + 3].int_ + mem[p - mem_min + 2].int_ +
              eqtb[12749].int_;
    if (mem[p - mem_min + 1].int_ + eqtb[12748].int_ > max_h)
      max_h = mem[p - mem_min + 1].int_ + eqtb[12748].int_;
    dvi_h = 0;
    dvi_v = 0;
    cur_h = eqtb[12748].int_;
    dvi_f = 0;
    if (!output_file_name) {
      if (!job_name)
        open_log_file();
      pack_job_name(793);
      while (!dvi_file and !b_open_out(dvi_file))
        prompt_file_name(794, 793);
      output_file_name = b_make_name_string(dvi_file);
    }
    if (!total_pages) {
      dvi_buf[dvi_ptr] = 247;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      dvi_buf[dvi_ptr] = 2;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      dvi_four(25400000);
      dvi_four(473628672);
      prepare_mag();
      dvi_four(eqtb[12180].int_);
      old_setting = selector;
      selector = 21;
      print(826);
      print_int(eqtb[12186].int_);
      print_char(46);
      print_two(eqtb[12185].int_);
      print_char(46);
      print_two(eqtb[12184].int_);
      print_char(58);
      print_two(eqtb[12183].int_ / 60);
      print_two(eqtb[12183].int_ % 60);
      selector = old_setting;
      dvi_buf[dvi_ptr] = pool_ptr - str_start[str_ptr];
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      for (N = pool_ptr, s = str_start[str_ptr]; s <= (N - 1); ++s) {
        dvi_buf[dvi_ptr] = str_pool[s];
        ++dvi_ptr;
        if (dvi_ptr == dvi_limit)
          dvi_swap();
      }
      pool_ptr = str_start[str_ptr];
    }
    page_loc = dvi_offset + dvi_ptr;
    dvi_buf[dvi_ptr] = 139;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    for (k = 0; k <= 9; ++k)
      dvi_four(eqtb[k + 12218].int_);
    dvi_four(last_bop);
    last_bop = page_loc;
    cur_v = mem[p - mem_min + 3].int_ + eqtb[12749].int_;
    temp_ptr = p;
    if (mem[p - mem_min].hh.U2.b0 == 1)
      vlist_out();
    else
      hlist_out();
    dvi_buf[dvi_ptr] = 140;
    ++dvi_ptr;
    if (dvi_ptr == dvi_limit)
      dvi_swap();
    ++total_pages;
    cur_s = -1;
  _L30:
    if (eqtb[12197].int_ <= 0)
      print_char(93);
    dead_cycles = 0;
    fflush(term_out);
    errno = 0;
    flush_node_list(p);
  }
  void scan_spec(group_code c, bool three_codes) {
    integer s;
    char spec_code;
    if (three_codes)
      s = save_stack[save_ptr].int_;
    if (scan_keyword(841)) {
      spec_code = 0;
    } else if (scan_keyword(842)) {
      spec_code = 1;
    } else {
      spec_code = 1;
      cur_val = 0;
      goto _L40;
    }
    scan_dimen(false, false, false);
  _L40:
    if (three_codes) {
      save_stack[save_ptr].int_ = s;
      ++save_ptr;
    }
    save_stack[save_ptr].int_ = spec_code;
    save_stack[save_ptr + 1].int_ = cur_val;
    save_ptr += 2;
    new_save_level(c);
    scan_left_brace();
  }
  halfword hpack(halfword p, scaled w, small_number m) {
    halfword r, q, g;
    scaled h = 0, d = 0, x = 0, s;
    glue_ord o;
    internal_font_number f;
    four_quarters i;
    eight_bits hd;
    last_badness = 0;
    r = get_node(7);
    mem[r - mem_min].hh.U2.b0 = 0;
    mem[r - mem_min].hh.U2.b1 = 0;
    mem[r - mem_min + 4].int_ = 0;
    q = r + 5;
    mem[q - mem_min].hh.rh = p;
    total_stretch[0] = 0;
    total_shrink[0] = 0;
    total_stretch[1] = 0;
    total_shrink[1] = 0;
    total_stretch[2] = 0;
    total_shrink[2] = 0;
    total_stretch[3] = 0;
    total_shrink[3] = 0;
    while (p != (-1073741824)) {
    _L21:
      while (p >= hi_mem_min) {
        f = mem[p - mem_min].hh.U2.b0;
        i = font_info[char_base[f] + mem[p - mem_min].hh.U2.b1].qqqq;
        hd = i.b1;
        x += font_info[width_base[f] + i.b0].int_;
        s = font_info[height_base[f] + (hd / 16)].int_;
        if (s > h)
          h = s;
        s = font_info[depth_base[f] + (hd & 15)].int_;
        if (s > d)
          d = s;
        p = mem[p - mem_min].hh.rh;
      }
      if (p == (-1073741824))
        break;
      switch (mem[p - mem_min].hh.U2.b0) {
      case 0:
      case 1:
      case 2:
      case 13:
        x += mem[p - mem_min + 1].int_;
        if (mem[p - mem_min].hh.U2.b0 >= 2)
          s = 0;
        else
          s = mem[p - mem_min + 4].int_;
        if (mem[p - mem_min + 3].int_ - s > h)
          h = mem[p - mem_min + 3].int_ - s;
        if (mem[p - mem_min + 2].int_ + s > d)
          d = mem[p - mem_min + 2].int_ + s;
        break;
      case 3:
      case 4:
      case 5:
        if (adjust_tail != (-1073741824)) {
          while (mem[q - mem_min].hh.rh != p)
            q = mem[q - mem_min].hh.rh;
          if (mem[p - mem_min].hh.U2.b0 == 5) {
            mem[adjust_tail - mem_min].hh.rh = mem[p - mem_min + 1].int_;
            while (mem[adjust_tail - mem_min].hh.rh != (-1073741824))
              adjust_tail = mem[adjust_tail - mem_min].hh.rh;
            p = mem[p - mem_min].hh.rh;
            free_node(mem[q - mem_min].hh.rh, 2);
          } else {
            mem[adjust_tail - mem_min].hh.rh = p;
            adjust_tail = p;
            p = mem[p - mem_min].hh.rh;
          }
          mem[q - mem_min].hh.rh = p;
          p = q;
        }
        break;
      case 8:
        // blank case
        break;
      case 10:
        g = mem[p - mem_min + 1].hh.lh;
        x += mem[g - mem_min + 1].int_;
        o = mem[g - mem_min].hh.U2.b0;
        total_stretch[o] += mem[g - mem_min + 2].int_;
        o = mem[g - mem_min].hh.U2.b1;
        total_shrink[o] += mem[g - mem_min + 3].int_;
        if (mem[p - mem_min].hh.U2.b1 >= 100) {
          g = mem[p - mem_min + 1].hh.rh;
          if (mem[g - mem_min + 3].int_ > h)
            h = mem[g - mem_min + 3].int_;
          if (mem[g - mem_min + 2].int_ > d)
            d = mem[g - mem_min + 2].int_;
        }
        break;
      case 11:
      case 9:
        x += mem[p - mem_min + 1].int_;
        break;
      case 6:
        mem[mem_max - mem_min - 12] = mem[p - mem_min + 1];
        mem[mem_max - mem_min - 12].hh.rh = mem[p - mem_min].hh.rh;
        p = mem_max - 12;
        goto _L21;
        break;
      default:
        break;
      }
      p = mem[p - mem_min].hh.rh;
    }
    if (adjust_tail != (-1073741824))
      mem[adjust_tail - mem_min].hh.rh = -1073741824;
    mem[r - mem_min + 3].int_ = h;
    mem[r - mem_min + 2].int_ = d;
    if (m == 1)
      w += x;
    mem[r - mem_min + 1].int_ = w;
    x = w - x;
    if (!x) {
      mem[r - mem_min + 5].hh.U2.b0 = 0;
      mem[r - mem_min + 5].hh.U2.b1 = 0;
      mem[r - mem_min + 6].gr = 0.0;
      goto _L10;
    } else if (x > 0) {
      if (total_stretch[3]) {
        o = 3;
      } else if (total_stretch[2]) {
        o = 2;
      } else if (total_stretch[1])
        o = 1;
      else
        o = 0;
      mem[r - mem_min + 5].hh.U2.b1 = o;
      mem[r - mem_min + 5].hh.U2.b0 = 1;
      if (total_stretch[o]) {
        mem[r - mem_min + 6].gr = ((double)x) / total_stretch[o];
      } else {
        mem[r - mem_min + 5].hh.U2.b0 = 0;
        mem[r - mem_min + 6].gr = 0.0;
      }
      if (!o) {
        if (mem[r - mem_min + 5].hh.rh != (-1073741824)) {
          last_badness = badness(x, total_stretch[0]);
          if (last_badness > eqtb[12189].int_) {
            print_ln();
            if (last_badness > 100)
              print_nl(843);
            else
              print_nl(844);
            print(845);
            print_int(last_badness);
            goto _L50;
          }
        }
      }
      goto _L10;
    } else {
      if (total_shrink[3]) {
        o = 3;
      } else if (total_shrink[2]) {
        o = 2;
      } else if (total_shrink[1])
        o = 1;
      else
        o = 0;
      mem[r - mem_min + 5].hh.U2.b1 = o;
      mem[r - mem_min + 5].hh.U2.b0 = 2;
      if (total_shrink[o]) {
        mem[r - mem_min + 6].gr = ((double)(-x)) / total_shrink[o];
      } else {
        mem[r - mem_min + 5].hh.U2.b0 = 0;
        mem[r - mem_min + 6].gr = 0.0;
      }
      if ((total_shrink[o] < (-x)) && (!o) &&
          (mem[r - mem_min + 5].hh.rh != (-1073741824))) {
        last_badness = 1000000;
        mem[r - mem_min + 6].gr = 1.0;
        if (((-x) - total_shrink[0] > eqtb[12738].int_) ||
            (eqtb[12189].int_ < 100)) {
          if ((eqtb[12746].int_ > 0) &&
              ((-x) - total_shrink[0] > eqtb[12738].int_)) {
            while (mem[q - mem_min].hh.rh != (-1073741824))
              q = mem[q - mem_min].hh.rh;
            mem[q - mem_min].hh.rh = new_rule();
            mem[mem[q - mem_min].hh.rh - mem_min + 1].int_ = eqtb[12746].int_;
          }
          print_ln();
          print_nl(851);
          print_scaled((-x) - total_shrink[0]);
          print(852);
          goto _L50;
        }
      } else if (!o) {
        if (mem[r - mem_min + 5].hh.rh != (-1073741824)) {
          last_badness = badness(-x, total_shrink[0]);
          if (last_badness > eqtb[12189].int_) {
            print_ln();
            print_nl(853);
            print_int(last_badness);
            goto _L50;
          }
        }
      }
      goto _L10;
    }
  _L50:
    if (output_active) {
      print(846);
    } else {
      if (pack_begin_line) {
        if (pack_begin_line > 0)
          print(847);
        else
          print(848);
        print_int(abs(pack_begin_line));
        print(849);
      } else {
        print(850);
      }
      print_int(line);
    }
    print_ln();
    font_in_short_display = 0;
    short_display(mem[r - mem_min + 5].hh.rh);
    print_ln();
    begin_diagnostic();
    show_box(r);
    end_diagnostic(true);
  _L10:
    return r;
  }
  halfword vpackage(halfword p, scaled h, small_number m, scaled l) {
    halfword r, g;
    scaled w = 0, d = 0, x = 0, s;
    glue_ord o;
    last_badness = 0;
    r = get_node(7);
    mem[r - mem_min].hh.U2.b0 = 1;
    mem[r - mem_min].hh.U2.b1 = 0;
    mem[r - mem_min + 4].int_ = 0;
    mem[r - mem_min + 5].hh.rh = p;
    total_stretch[0] = 0;
    total_shrink[0] = 0;
    total_stretch[1] = 0;
    total_shrink[1] = 0;
    total_stretch[2] = 0;
    total_shrink[2] = 0;
    total_stretch[3] = 0;
    total_shrink[3] = 0;
    while (p != (-1073741824)) {
      if (p >= hi_mem_min) {
        confusion(854);
      } else {
        switch (mem[p - mem_min].hh.U2.b0) {
        case 0:
        case 1:
        case 2:
        case 13:
          x += d + mem[p - mem_min + 3].int_;
          d = mem[p - mem_min + 2].int_;
          if (mem[p - mem_min].hh.U2.b0 >= 2)
            s = 0;
          else
            s = mem[p - mem_min + 4].int_;
          if (mem[p - mem_min + 1].int_ + s > w)
            w = mem[p - mem_min + 1].int_ + s;
          break;
        case 8:
          // blank case
          break;
        case 10:
          x += d;
          d = 0;
          g = mem[p - mem_min + 1].hh.lh;
          x += mem[g - mem_min + 1].int_;
          o = mem[g - mem_min].hh.U2.b0;
          total_stretch[o] += mem[g - mem_min + 2].int_;
          o = mem[g - mem_min].hh.U2.b1;
          total_shrink[o] += mem[g - mem_min + 3].int_;
          if (mem[p - mem_min].hh.U2.b1 >= 100) {
            g = mem[p - mem_min + 1].hh.rh;
            if (mem[g - mem_min + 1].int_ > w)
              w = mem[g - mem_min + 1].int_;
          }
          break;
        case 11:
          x += d + mem[p - mem_min + 1].int_;
          d = 0;
          break;
        default:
          break;
        }
      }
      p = mem[p - mem_min].hh.rh;
    }
    mem[r - mem_min + 1].int_ = w;
    if (d > l) {
      x += d - l;
      mem[r - mem_min + 2].int_ = l;
    } else {
      mem[r - mem_min + 2].int_ = d;
    }
    if (m == 1)
      h += x;
    mem[r - mem_min + 3].int_ = h;
    x = h - x;
    if (!x) {
      mem[r - mem_min + 5].hh.U2.b0 = 0;
      mem[r - mem_min + 5].hh.U2.b1 = 0;
      mem[r - mem_min + 6].gr = 0.0;
      goto _L10;
    } else if (x > 0) {
      if (total_stretch[3]) {
        o = 3;
      } else if (total_stretch[2]) {
        o = 2;
      } else if (total_stretch[1])
        o = 1;
      else
        o = 0;
      mem[r - mem_min + 5].hh.U2.b1 = o;
      mem[r - mem_min + 5].hh.U2.b0 = 1;
      if (total_stretch[o]) {
        mem[r - mem_min + 6].gr = ((double)x) / total_stretch[o];
      } else {
        mem[r - mem_min + 5].hh.U2.b0 = 0;
        mem[r - mem_min + 6].gr = 0.0;
      }
      if (!o) {
        if (mem[r - mem_min + 5].hh.rh != (-1073741824)) {
          last_badness = badness(x, total_stretch[0]);
          if (last_badness > eqtb[12190].int_) {
            print_ln();
            if (last_badness > 100)
              print_nl(843);
            else
              print_nl(844);
            print(855);
            print_int(last_badness);
            goto _L50;
          }
        }
      }
      goto _L10;
    } else {
      if (total_shrink[3]) {
        o = 3;
      } else if (total_shrink[2]) {
        o = 2;
      } else if (total_shrink[1])
        o = 1;
      else
        o = 0;
      mem[r - mem_min + 5].hh.U2.b1 = o;
      mem[r - mem_min + 5].hh.U2.b0 = 2;
      if (total_shrink[o]) {
        mem[r - mem_min + 6].gr = ((double)(-x)) / total_shrink[o];
      } else {
        mem[r - mem_min + 5].hh.U2.b0 = 0;
        mem[r - mem_min + 6].gr = 0.0;
      }
      if ((total_shrink[o] < (-x)) && (!o) &&
          (mem[r - mem_min + 5].hh.rh != (-1073741824))) {
        last_badness = 1000000;
        mem[r - mem_min + 6].gr = 1.0;
        if (((-x) - total_shrink[0] > eqtb[12739].int_) ||
            (eqtb[12190].int_ < 100)) {
          print_ln();
          print_nl(856);
          print_scaled((-x) - total_shrink[0]);
          print(857);
          goto _L50;
        }
      } else if (!o) {
        if (mem[r - mem_min + 5].hh.rh != (-1073741824)) {
          last_badness = badness(-x, total_shrink[0]);
          if (last_badness > eqtb[12190].int_) {
            print_ln();
            print_nl(858);
            print_int(last_badness);
            goto _L50;
          }
        }
      }
      goto _L10;
    }
  _L50:
    if (output_active) {
      print(846);
    } else {
      if (pack_begin_line) {
        print(848);
        print_int(abs(pack_begin_line));
        print(849);
      } else {
        print(850);
      }
      print_int(line);
      print_ln();
    }
    begin_diagnostic();
    show_box(r);
    end_diagnostic(true);
  _L10:
    return r;
  }
  void append_to_vlist(halfword b) {
    scaled d;
    halfword p;
    if (cur_list.aux_field.int_ > (-65536000)) {
      d = mem[eqtb[9783].hh.rh - mem_min + 1].int_ - cur_list.aux_field.int_ -
          mem[b - mem_min + 3].int_;
      if (d < eqtb[12732].int_) {
        p = new_param_glue(0);
      } else {
        p = new_skip_param(1);
        mem[temp_ptr - mem_min + 1].int_ = d;
      }
      mem[cur_list.tail_field - mem_min].hh.rh = p;
      cur_list.tail_field = p;
    }
    mem[cur_list.tail_field - mem_min].hh.rh = b;
    cur_list.tail_field = b;
    cur_list.aux_field.int_ = mem[b - mem_min + 2].int_;
  }
  halfword new_noad() {
    halfword p = get_node(4);
    mem[p - mem_min].hh.U2.b0 = 16;
    mem[p - mem_min].hh.U2.b1 = 0;
    mem[p - mem_min + 1].hh = empty_field;
    mem[p - mem_min + 3].hh = empty_field;
    mem[p - mem_min + 2].hh = empty_field;
    return p;
  }
  halfword new_style(small_number s) {
    halfword p = get_node(3);
    mem[p - mem_min].hh.U2.b0 = 14;
    mem[p - mem_min].hh.U2.b1 = s;
    mem[p - mem_min + 1].int_ = 0;
    mem[p - mem_min + 2].int_ = 0;
    return p;
  }
  halfword new_choice() {
    halfword p = get_node(3);
    mem[p - mem_min].hh.U2.b0 = 15;
    mem[p - mem_min].hh.U2.b1 = 0;
    mem[p - mem_min + 1].hh.lh = -1073741824;
    mem[p - mem_min + 1].hh.rh = -1073741824;
    mem[p - mem_min + 2].hh.lh = -1073741824;
    mem[p - mem_min + 2].hh.rh = -1073741824;
    return p;
  }
  void show_info() { show_node_list(mem[temp_ptr - mem_min].hh.lh); }
  halfword fraction_rule(scaled t) {
    halfword p = new_rule();
    mem[p - mem_min + 3].int_ = t;
    mem[p - mem_min + 2].int_ = 0;
    return p;
  }
  halfword overbar(halfword b, scaled k, scaled t) {
    halfword q;
    halfword p = new_kern(k);
    mem[p - mem_min].hh.rh = b;
    q = fraction_rule(t);
    mem[q - mem_min].hh.rh = p;
    p = new_kern(t);
    mem[p - mem_min].hh.rh = q;
    return vpackage(p, 0, 1, 1073741823);
  }
  halfword char_box(internal_font_number f, quarterword c) {
    halfword p;
    four_quarters q = font_info[char_base[f] + c].qqqq;
    eight_bits hd = q.b1;
    halfword b = new_null_box();
    mem[b - mem_min + 1].int_ = font_info[width_base[f] + q.b0].int_ +
                                font_info[italic_base[f] + (q.b2 / 4)].int_;
    mem[b - mem_min + 3].int_ = font_info[height_base[f] + (hd / 16)].int_;
    mem[b - mem_min + 2].int_ = font_info[depth_base[f] + (hd & 15)].int_;
    p = get_avail();
    mem[p - mem_min].hh.U2.b1 = c;
    mem[p - mem_min].hh.U2.b0 = f;
    mem[b - mem_min + 5].hh.rh = p;
    return b;
  }
  void stack_into_box(halfword b, internal_font_number f, quarterword c) {
    halfword p = char_box(f, c);
    mem[p - mem_min].hh.rh = mem[b - mem_min + 5].hh.rh;
    mem[b - mem_min + 5].hh.rh = p;
    mem[b - mem_min + 3].int_ = mem[p - mem_min + 3].int_;
  }
  scaled height_plus_depth(internal_font_number f, quarterword c) {
    four_quarters q = font_info[char_base[f] + c].qqqq;
    eight_bits hd = q.b1;
    return font_info[height_base[f] + (hd / 16)].int_ +
           font_info[depth_base[f] + (hd & 15)].int_;
  }
  halfword var_delimiter(halfword d, small_number s, scaled v) {
    halfword b;
    internal_font_number f = 0, g;
    quarterword c, y;
    integer m, n;
    scaled u, w = 0;
    four_quarters q;
    eight_bits hd;
    four_quarters r;
    bool large_attempt = false;
    small_number z = mem[d - mem_min].qqqq.b0;
    quarterword x = mem[d - mem_min].qqqq.b1;
    while (true) {
      if (z || x) {
        z += s + 16;
        do {
          z -= 16;
          g = eqtb[z + 10835].hh.rh;
          if (g) {
            y = x;
            if ((y >= font_bc[g]) && (y <= font_ec[g])) {
            _L22:
              q = font_info[char_base[g] + y].qqqq;
              if (q.b0 > 0) {
                if ((q.b2 & 3) == 3) {
                  f = g;
                  c = y;
                  goto _L40;
                }
                hd = q.b1;
                u = font_info[height_base[g] + (hd / 16)].int_ +
                    font_info[depth_base[g] + (hd & 15)].int_;
                if (u > w) {
                  f = g;
                  c = y;
                  w = u;
                  if (u >= v)
                    goto _L40;
                }
                if ((q.b2 & 3) == 2) {
                  y = q.b3;
                  goto _L22;
                }
              }
            }
          }
        } while (z >= 16);
      }
      if (large_attempt)
        goto _L40;
      large_attempt = true;
      z = mem[d - mem_min].qqqq.b2;
      x = mem[d - mem_min].qqqq.b3;
    }
  _L40:
    if (f) {
      if ((q.b2 & 3) == 3) {
        b = new_null_box();
        mem[b - mem_min].hh.U2.b0 = 1;
        r = font_info[exten_base[f] + q.b3].qqqq;
        c = r.b3;
        u = height_plus_depth(f, c);
        w = 0;
        q = font_info[char_base[f] + c].qqqq;
        mem[b - mem_min + 1].int_ = font_info[width_base[f] + q.b0].int_ +
                                    font_info[italic_base[f] + (q.b2 / 4)].int_;
        c = r.b2;
        if (c)
          w += height_plus_depth(f, c);
        c = r.b1;
        if (c)
          w += height_plus_depth(f, c);
        c = r.b0;
        if (c)
          w += height_plus_depth(f, c);
        n = 0;
        if (u > 0) {
          while (w < v) {
            w += u;
            ++n;
            if (r.b1)
              w += u;
          }
        }
        c = r.b2;
        if (c)
          stack_into_box(b, f, c);
        c = r.b3;
        for (m = 1; m <= n; ++m)
          stack_into_box(b, f, c);
        c = r.b1;
        if (c) {
          stack_into_box(b, f, c);
          c = r.b3;
          for (m = 1; m <= n; ++m)
            stack_into_box(b, f, c);
        }
        c = r.b0;
        if (c)
          stack_into_box(b, f, c);
        mem[b - mem_min + 2].int_ = w - mem[b - mem_min + 3].int_;
      } else {
        b = char_box(f, c);
      }
    } else {
      b = new_null_box();
      mem[b - mem_min + 1].int_ = eqtb[12741].int_;
    }
    (mem[b - mem_min + 4].int_ =
         (half(mem[b - mem_min + 3].int_ - mem[b - mem_min + 2].int_) -
          (font_info[(param_base[((eqtb[s + 10837].hh).rh)] + 22)].int_)));
    return b;
  }
  halfword rebox(halfword b, scaled w) {
    halfword p;
    internal_font_number f;
    scaled v;
    if ((mem[b - mem_min + 1].int_ != w) &&
        (mem[b - mem_min + 5].hh.rh != (-1073741824))) {
      if (mem[b - mem_min].hh.U2.b0 == 1)
        b = hpack(b, 0, 1);
      p = mem[b - mem_min + 5].hh.rh;
      if ((p >= hi_mem_min) && (mem[p - mem_min].hh.rh == (-1073741824))) {
        f = mem[p - mem_min].hh.U2.b0;
        v = font_info[width_base[f] +
                      font_info[char_base[f] + mem[p - mem_min].hh.U2.b1]
                          .qqqq.b0]
                .int_;
        if (v != mem[b - mem_min + 1].int_)
          mem[p - mem_min].hh.rh = new_kern(mem[b - mem_min + 1].int_ - v);
      }
      free_node(b, 7);
      b = new_glue(12);
      mem[b - mem_min].hh.rh = p;
      while (mem[p - mem_min].hh.rh != (-1073741824))
        p = mem[p - mem_min].hh.rh;
      mem[p - mem_min].hh.rh = new_glue(12);
      return hpack(b, w, 0);
    } else {
      mem[b - mem_min + 1].int_ = w;
      return b;
    }
  }
  halfword math_glue(halfword g, scaled m) {
    halfword p;
    integer n = x_over_n(m, 65536);
    scaled f = remainder_;
    if (f < 0) {
      --n;
      f += 65536;
    }
    p = get_node(4);
    (mem[p - mem_min + 1].int_ = mult_and_add(
         n, mem[g - mem_min + 1].int_,
         xn_over_d(mem[g - mem_min + 1].int_, f, 65536), 1073741823));
    mem[p - mem_min].hh.U2.b0 = mem[g - mem_min].hh.U2.b0;
    if (!mem[p - mem_min].hh.U2.b0)
      (mem[p - mem_min + 2].int_ = mult_and_add(
           n, mem[g - mem_min + 2].int_,
           xn_over_d(mem[g - mem_min + 2].int_, f, 65536), 1073741823));
    else
      mem[p - mem_min + 2].int_ = mem[g - mem_min + 2].int_;
    mem[p - mem_min].hh.U2.b1 = mem[g - mem_min].hh.U2.b1;
    if (!mem[p - mem_min].hh.U2.b1)
      (mem[p - mem_min + 3].int_ = mult_and_add(
           n, mem[g - mem_min + 3].int_,
           xn_over_d(mem[g - mem_min + 3].int_, f, 65536), 1073741823));
    else
      mem[p - mem_min + 3].int_ = mem[g - mem_min + 3].int_;
    return p;
  }
  void math_kern(halfword p, scaled m) {
    integer n;
    scaled f;
    if (mem[p - mem_min].hh.U2.b1 != 99)
      return;
    n = x_over_n(m, 65536);
    f = remainder_;
    if (f < 0) {
      --n;
      f += 65536;
    }
    (mem[p - mem_min + 1].int_ = mult_and_add(
         n, mem[p - mem_min + 1].int_,
         xn_over_d(mem[p - mem_min + 1].int_, f, 65536), 1073741823));
    mem[p - mem_min].hh.U2.b1 = 1;
  }
  void flush_math() {
    flush_node_list(mem[cur_list.head_field - mem_min].hh.rh);
    flush_node_list(cur_list.aux_field.int_);
    mem[cur_list.head_field - mem_min].hh.rh = -1073741824;
    cur_list.tail_field = cur_list.head_field;
    cur_list.aux_field.int_ = -1073741824;
  }
  halfword clean_box(halfword p, small_number s) {
    halfword q;
    small_number save_style;
    halfword x, r;
    switch (mem[p - mem_min].hh.rh) {
    case 1:
      cur_mlist = new_noad();
      mem[cur_mlist - mem_min + 1] = mem[p - mem_min];
      break;
    case 2:
      q = mem[p - mem_min].hh.lh;
      goto _L40;
      break;
    case 3:
      cur_mlist = mem[p - mem_min].hh.lh;
      break;
    default:
      q = new_null_box();
      goto _L40;
      break;
    }
    save_style = cur_style;
    cur_style = s;
    mlist_penalties = false;
    mlist_to_hlist();
    q = mem[mem_max - mem_min - 3].hh.rh;
    cur_style = save_style;
    if (cur_style < 4)
      cur_size = 0;
    else
      cur_size = ((cur_style - 2) / 2) * 16;
    cur_mu = x_over_n(
        font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 6].int_, 18);
  _L40:
    if ((q >= hi_mem_min) || (q == (-1073741824))) {
      x = hpack(q, 0, 1);
    } else if ((mem[q - mem_min].hh.rh == (-1073741824)) &&
               (mem[q - mem_min].hh.U2.b0 <= 1) && (!mem[q - mem_min + 4].int_))
      x = q;
    else
      x = hpack(q, 0, 1);
    q = mem[x - mem_min + 5].hh.rh;
    if (q < hi_mem_min)
      return x;
    r = mem[q - mem_min].hh.rh;
    if (r == (-1073741824))
      return x;
    if (mem[r - mem_min].hh.rh != (-1073741824))
      return x;
    if (r >= hi_mem_min)
      return x;
    if (mem[r - mem_min].hh.U2.b0 == 11) {
      free_node(r, 2);
      mem[q - mem_min].hh.rh = -1073741824;
    }
    return x;
  }
  void fetch(halfword a) {
    cur_c = mem[a - mem_min].hh.U2.b1;
    cur_f = eqtb[mem[a - mem_min].hh.U2.b0 + cur_size + 10835].hh.rh;
    if (!cur_f) {
      print_nl(262);
      print(338);
      print_size(cur_size);
      print_char(32);
      print_int(mem[a - mem_min].hh.U2.b0);
      print(883);
      print(cur_c);
      print_char(41);
      help_ptr = 4;
      help_line[3] = 884;
      help_line[2] = 885;
      help_line[1] = 886;
      help_line[0] = 887;
      error();
      cur_i = null_character;
      mem[a - mem_min].hh.rh = 0;
      return;
    }
    if ((cur_c >= font_bc[cur_f]) && (cur_c <= font_ec[cur_f]))
      cur_i = font_info[char_base[cur_f] + cur_c].qqqq;
    else
      cur_i = null_character;
    if (cur_i.b0 <= 0) {
      char_warning(cur_f, cur_c);
      mem[a - mem_min].hh.rh = 0;
    }
  }
  void make_over(halfword q) {
    (mem[q - mem_min + 1].hh.lh = overbar(
         clean_box(q + 1, ((cur_style / 2) * 2) + 1),
         font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 8].int_ * 3,
         font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 8].int_));
    mem[q - mem_min + 1].hh.rh = 2;
  }
  void make_under(halfword q) {
    halfword y;
    scaled delta;
    halfword x = clean_box(q + 1, cur_style);
    halfword p = new_kern(
        font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 8].int_ * 3);
    mem[x - mem_min].hh.rh = p;
    mem[p - mem_min].hh.rh = fraction_rule(
        font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 8].int_);
    y = vpackage(x, 0, 1, 1073741823);
    delta = mem[y - mem_min + 3].int_ + mem[y - mem_min + 2].int_ +
            font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 8].int_;
    mem[y - mem_min + 3].int_ = mem[x - mem_min + 3].int_;
    mem[y - mem_min + 2].int_ = delta - mem[y - mem_min + 3].int_;
    mem[q - mem_min + 1].hh.lh = y;
    mem[q - mem_min + 1].hh.rh = 2;
  }
  void make_vcenter(halfword q) {
    scaled delta;
    halfword v = mem[q - mem_min + 1].hh.lh;
    if (mem[v - mem_min].hh.U2.b0 != 1)
      confusion(539);
    delta = mem[v - mem_min + 3].int_ + mem[v - mem_min + 2].int_;
    mem[v - mem_min + 3].int_ =
        font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 22].int_ +
        half(delta);
    mem[v - mem_min + 2].int_ = delta - mem[v - mem_min + 3].int_;
  }
  void make_radical(halfword q) {
    halfword y;
    scaled delta, clr;
    halfword x = clean_box(q + 1, ((cur_style / 2) * 2) + 1);
    if (cur_style < 2) {
      (clr =
           (font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 8].int_ +
            (abs(font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 5].int_) /
             4)));
    } else {
      clr = font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 8].int_;
      clr += abs(clr) / 4;
    }
    (y = var_delimiter(
         q + 4, cur_size,
         (mem[x - mem_min + 3].int_ + mem[x - mem_min + 2].int_ + clr +
          (font_info[(param_base[eqtb[cur_size + 10838].hh.rh] + 8)].int_))));
    delta = mem[y - mem_min + 2].int_ - mem[x - mem_min + 3].int_ -
            mem[x - mem_min + 2].int_ - clr;
    if (delta > 0)
      clr += half(delta);
    mem[y - mem_min + 4].int_ = -(mem[x - mem_min + 3].int_ + clr);
    mem[y - mem_min].hh.rh = overbar(x, clr, mem[y - mem_min + 3].int_);
    mem[q - mem_min + 1].hh.lh = hpack(y, 0, 1);
    mem[q - mem_min + 1].hh.rh = 2;
  }
  void make_math_accent(halfword q) {
    halfword p, x, y;
    integer a;
    quarterword c;
    internal_font_number f;
    four_quarters i;
    scaled s = 0, h, delta, w;
    fetch(q + 4);
    if (cur_i.b0 <= 0)
      return;
    i = cur_i;
    c = cur_c;
    f = cur_f;
    if (mem[q - mem_min + 1].hh.rh == 1) {
      fetch(q + 1);
      if ((cur_i.b2 & 3) == 1) {
        a = lig_kern_base[cur_f] + cur_i.b3;
        cur_i = font_info[a].qqqq;
        if (cur_i.b0 > 128) {
          a = lig_kern_base[cur_f] + (cur_i.b2 * 256) + cur_i.b3;
          cur_i = font_info[a].qqqq;
        }
        while (true) {
          if (cur_i.b1 == skew_char[cur_f]) {
            if (cur_i.b2 >= 128) {
              if (cur_i.b0 <= 128)
                s = font_info[kern_base[cur_f] + (cur_i.b2 * 256) + cur_i.b3]
                        .int_;
            }
            goto _L31;
          }
          if (cur_i.b0 >= 128)
            goto _L31;
          a += cur_i.b0 + 1;
          cur_i = font_info[a].qqqq;
        }
      }
    }
  _L31:
    x = clean_box(q + 1, ((cur_style / 2) * 2) + 1);
    w = mem[x - mem_min + 1].int_;
    h = mem[x - mem_min + 3].int_;
    while (true) {
      if ((i.b2 & 3) != 2)
        goto _L30;
      y = i.b3;
      i = font_info[char_base[f] + y].qqqq;
      if (i.b0 <= 0)
        goto _L30;
      if (font_info[width_base[f] + i.b0].int_ > w)
        goto _L30;
      c = y;
    }
  _L30:
    if (h < font_info[param_base[f] + 5].int_)
      delta = h;
    else
      delta = font_info[param_base[f] + 5].int_;
    if (mem[q - mem_min + 2].hh.rh || mem[q - mem_min + 3].hh.rh) {
      if (mem[q - mem_min + 1].hh.rh == 1) {
        flush_node_list(x);
        x = new_noad();
        mem[x - mem_min + 1] = mem[q - mem_min + 1];
        mem[x - mem_min + 2] = mem[q - mem_min + 2];
        mem[x - mem_min + 3] = mem[q - mem_min + 3];
        mem[q - mem_min + 2].hh = empty_field;
        mem[q - mem_min + 3].hh = empty_field;
        mem[q - mem_min + 1].hh.rh = 3;
        mem[q - mem_min + 1].hh.lh = x;
        x = clean_box(q + 1, cur_style);
        delta += mem[x - mem_min + 3].int_ - h;
        h = mem[x - mem_min + 3].int_;
      }
    }
    y = char_box(f, c);
    mem[y - mem_min + 4].int_ = s + half(w - mem[y - mem_min + 1].int_);
    mem[y - mem_min + 1].int_ = 0;
    p = new_kern(-delta);
    mem[p - mem_min].hh.rh = x;
    mem[y - mem_min].hh.rh = p;
    y = vpackage(y, 0, 1, 1073741823);
    mem[y - mem_min + 1].int_ = mem[x - mem_min + 1].int_;
    if (mem[y - mem_min + 3].int_ < h) {
      p = new_kern(h - mem[y - mem_min + 3].int_);
      mem[p - mem_min].hh.rh = mem[y - mem_min + 5].hh.rh;
      mem[y - mem_min + 5].hh.rh = p;
      mem[y - mem_min + 3].int_ = h;
    }
    mem[q - mem_min + 1].hh.lh = y;
    mem[q - mem_min + 1].hh.rh = 2;
  }
  void make_fraction(halfword q) {
    halfword p, v, x, y, z;
    scaled delta, delta1, delta2, shift_up, shift_down, clr;
    if (mem[q - mem_min + 1].int_ == 1073741824)
      mem[q - mem_min + 1].int_ =
          font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 8].int_;
    x = clean_box(q + 2, cur_style - ((cur_style / 6) * 2) + 2);
    z = clean_box(q + 3, ((cur_style / 2) * 2) - ((cur_style / 6) * 2) + 3);
    if (mem[x - mem_min + 1].int_ < mem[z - mem_min + 1].int_)
      x = rebox(x, mem[z - mem_min + 1].int_);
    else
      z = rebox(z, mem[x - mem_min + 1].int_);
    if (cur_style < 2) {
      shift_up = font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 8].int_;
      shift_down =
          font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 11].int_;
    } else {
      shift_down =
          font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 12].int_;
      if (mem[q - mem_min + 1].int_)
        shift_up = font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 9].int_;
      else
        shift_up =
            font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 10].int_;
    }
    if (!mem[q - mem_min + 1].int_) {
      if (cur_style < 2)
        clr = font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 8].int_ * 7;
      else
        clr = font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 8].int_ * 3;
      delta = half(clr - shift_up + mem[x - mem_min + 2].int_ +
                   mem[z - mem_min + 3].int_ - shift_down);
      if (delta > 0) {
        shift_up += delta;
        shift_down += delta;
      }
    } else {
      if (cur_style < 2)
        clr = mem[q - mem_min + 1].int_ * 3;
      else
        clr = mem[q - mem_min + 1].int_;
      delta = half(mem[q - mem_min + 1].int_);
      (delta1 = (clr - shift_up + mem[x - mem_min + 2].int_ +
                 font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 22].int_ +
                 delta));
      (delta2 = (clr -
                 font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 22].int_ +
                 delta + mem[z - mem_min + 3].int_ - shift_down));
      if (delta1 > 0)
        shift_up += delta1;
      if (delta2 > 0)
        shift_down += delta2;
    }
    v = new_null_box();
    mem[v - mem_min].hh.U2.b0 = 1;
    mem[v - mem_min + 3].int_ = shift_up + mem[x - mem_min + 3].int_;
    mem[v - mem_min + 2].int_ = mem[z - mem_min + 2].int_ + shift_down;
    mem[v - mem_min + 1].int_ = mem[x - mem_min + 1].int_;
    if (!mem[q - mem_min + 1].int_) {
      p = new_kern(shift_up - mem[x - mem_min + 2].int_ -
                   mem[z - mem_min + 3].int_ + shift_down);
      mem[p - mem_min].hh.rh = z;
    } else {
      y = fraction_rule(mem[q - mem_min + 1].int_);
      (p = new_kern(
           font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 22].int_ -
           delta - mem[z - mem_min + 3].int_ + shift_down));
      mem[y - mem_min].hh.rh = p;
      mem[p - mem_min].hh.rh = z;
      p = new_kern(
          shift_up - mem[x - mem_min + 2].int_ -
          font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 22].int_ -
          delta);
      mem[p - mem_min].hh.rh = y;
    }
    mem[x - mem_min].hh.rh = p;
    mem[v - mem_min + 5].hh.rh = x;
    if (cur_style < 2)
      delta = font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 20].int_;
    else
      delta = font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 21].int_;
    x = var_delimiter(q + 4, cur_size, delta);
    mem[x - mem_min].hh.rh = v;
    z = var_delimiter(q + 5, cur_size, delta);
    mem[v - mem_min].hh.rh = z;
    mem[q - mem_min + 1].int_ = hpack(x, 0, 1);
  }
  scaled make_op(halfword q) {
    scaled delta, shift_up, shift_down;
    halfword p, v, x, y, z;
    quarterword c;
    four_quarters i;
    if ((!mem[q - mem_min].hh.U2.b1) && (cur_style < 2))
      mem[q - mem_min].hh.U2.b1 = 1;
    if (mem[q - mem_min + 1].hh.rh == 1) {
      fetch(q + 1);
      if ((cur_style < 2) && ((cur_i.b2 & 3) == 2)) {
        c = cur_i.b3;
        i = font_info[char_base[cur_f] + c].qqqq;
        if (i.b0 > 0) {
          cur_c = c;
          cur_i = i;
          mem[q - mem_min + 1].hh.U2.b1 = c;
        }
      }
      delta = font_info[italic_base[cur_f] + (cur_i.b2 / 4)].int_;
      x = clean_box(q + 1, cur_style);
      if (mem[q - mem_min + 3].hh.rh && (mem[q - mem_min].hh.U2.b1 != 1))
        mem[x - mem_min + 1].int_ -= delta;
      (mem[x - mem_min + 4].int_ =
           (half(mem[x - mem_min + 3].int_ - mem[x - mem_min + 2].int_) -
            (font_info[(param_base[((eqtb[cur_size + 10837].hh).rh)] + 22)]
                 .int_)));
      mem[q - mem_min + 1].hh.rh = 2;
      mem[q - mem_min + 1].hh.lh = x;
    } else {
      delta = 0;
    }
    if (mem[q - mem_min].hh.U2.b1 != 1)
      return delta;
    x = clean_box(q + 2, ((cur_style / 4) * 2) + (cur_style & 1) + 4);
    y = clean_box(q + 1, cur_style);
    z = clean_box(q + 3, ((cur_style / 4) * 2) + 5);
    v = new_null_box();
    mem[v - mem_min].hh.U2.b0 = 1;
    mem[v - mem_min + 1].int_ = mem[y - mem_min + 1].int_;
    if (mem[x - mem_min + 1].int_ > mem[v - mem_min + 1].int_)
      mem[v - mem_min + 1].int_ = mem[x - mem_min + 1].int_;
    if (mem[z - mem_min + 1].int_ > mem[v - mem_min + 1].int_)
      mem[v - mem_min + 1].int_ = mem[z - mem_min + 1].int_;
    x = rebox(x, mem[v - mem_min + 1].int_);
    y = rebox(y, mem[v - mem_min + 1].int_);
    z = rebox(z, mem[v - mem_min + 1].int_);
    mem[x - mem_min + 4].int_ = half(delta);
    mem[z - mem_min + 4].int_ = -mem[x - mem_min + 4].int_;
    mem[v - mem_min + 3].int_ = mem[y - mem_min + 3].int_;
    mem[v - mem_min + 2].int_ = mem[y - mem_min + 2].int_;
    if (!mem[q - mem_min + 2].hh.rh) {
      free_node(x, 7);
      mem[v - mem_min + 5].hh.rh = y;
    } else {
      shift_up = font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 11].int_ -
                 mem[x - mem_min + 2].int_;
      if (shift_up <
          font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 9].int_)
        shift_up = font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 9].int_;
      p = new_kern(shift_up);
      mem[p - mem_min].hh.rh = y;
      mem[x - mem_min].hh.rh = p;
      p = new_kern(
          font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 13].int_);
      mem[p - mem_min].hh.rh = x;
      mem[v - mem_min + 5].hh.rh = p;
      (mem[v - mem_min + 3].int_ +=
       (font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 13].int_ +
        mem[x - mem_min + 3].int_ + (mem[(x - mem_min + 2)].int_) + shift_up));
    }
    if (!mem[q - mem_min + 3].hh.rh) {
      free_node(z, 7);
    } else {
      shift_down =
          font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 12].int_ -
          mem[z - mem_min + 3].int_;
      if (shift_down <
          font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 10].int_)
        shift_down =
            font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 10].int_;
      p = new_kern(shift_down);
      mem[y - mem_min].hh.rh = p;
      mem[p - mem_min].hh.rh = z;
      p = new_kern(
          font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 13].int_);
      mem[z - mem_min].hh.rh = p;
      (mem[v - mem_min + 2].int_ +=
       (font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 13].int_ +
        mem[z - mem_min + 3].int_ + (mem[(z - mem_min + 2)].int_) +
        shift_down));
    }
    mem[q - mem_min + 1].int_ = v;
    return delta;
  }
  void make_ord(halfword q) {
    integer a;
    halfword p, r;
  _L20:
    if (!mem[q - mem_min + 3].hh.rh) {
      if (!mem[q - mem_min + 2].hh.rh) {
        if (mem[q - mem_min + 1].hh.rh == 1) {
          p = mem[q - mem_min].hh.rh;
          if (p != (-1073741824)) {
            if ((mem[p - mem_min].hh.U2.b0 >= 16) &&
                (mem[p - mem_min].hh.U2.b0 <= 22)) {
              if (mem[p - mem_min + 1].hh.rh == 1) {
                if (mem[p - mem_min + 1].hh.U2.b0 ==
                    mem[q - mem_min + 1].hh.U2.b0) {
                  mem[q - mem_min + 1].hh.rh = 4;
                  fetch(q + 1);
                  if ((cur_i.b2 & 3) == 1) {
                    a = lig_kern_base[cur_f] + cur_i.b3;
                    cur_c = mem[p - mem_min + 1].hh.U2.b1;
                    cur_i = font_info[a].qqqq;
                    if (cur_i.b0 > 128) {
                      a = lig_kern_base[cur_f] + (cur_i.b2 * 256) + cur_i.b3;
                      cur_i = font_info[a].qqqq;
                    }
                    while (true) {
                      if (cur_i.b1 == cur_c) {
                        if (cur_i.b0 <= 128) {
                          if (cur_i.b2 >= 128) {
                            p = new_kern(font_info[kern_base[cur_f] +
                                                   (cur_i.b2 * 256) + cur_i.b3]
                                             .int_);
                            mem[p - mem_min].hh.rh = mem[q - mem_min].hh.rh;
                            mem[q - mem_min].hh.rh = p;
                            goto _L10;
                          } else {
                            if (interrupt)
                              pause_for_instructions();
                            switch (cur_i.b2) {
                            case 1:
                            case 5:
                              mem[q - mem_min + 1].hh.U2.b1 = cur_i.b3;
                              break;
                            case 2:
                            case 6:
                              mem[p - mem_min + 1].hh.U2.b1 = cur_i.b3;
                              break;
                            case 3:
                            case 7:
                            case 11:
                              r = new_noad();
                              mem[r - mem_min + 1].hh.U2.b1 = cur_i.b3;
                              mem[r - mem_min + 1].hh.U2.b0 =
                                  mem[q - mem_min + 1].hh.U2.b0;
                              mem[q - mem_min].hh.rh = r;
                              mem[r - mem_min].hh.rh = p;
                              if (cur_i.b2 < 11)
                                mem[r - mem_min + 1].hh.rh = 1;
                              else
                                mem[r - mem_min + 1].hh.rh = 4;
                              break;
                            default:
                              mem[q - mem_min].hh.rh = mem[p - mem_min].hh.rh;
                              mem[q - mem_min + 1].hh.U2.b1 = cur_i.b3;
                              mem[q - mem_min + 3] = mem[p - mem_min + 3];
                              mem[q - mem_min + 2] = mem[p - mem_min + 2];
                              free_node(p, 4);
                              break;
                            }
                            if (cur_i.b2 > 3)
                              goto _L10;
                            mem[q - mem_min + 1].hh.rh = 1;
                            goto _L20;
                          }
                        }
                      }
                      if (cur_i.b0 >= 128)
                        goto _L10;
                      a += cur_i.b0 + 1;
                      cur_i = font_info[a].qqqq;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  _L10:;
  }
  void make_scripts(halfword q, scaled delta) {
    halfword x, y, z;
    scaled shift_up, shift_down, clr;
    small_number t;
    halfword p = mem[q - mem_min + 1].int_;
    if (p >= hi_mem_min) {
      shift_up = 0;
      shift_down = 0;
    } else {
      z = hpack(p, 0, 1);
      if (cur_style < 4)
        t = 16;
      else
        t = 32;
      shift_up = mem[z - mem_min + 3].int_ -
                 font_info[param_base[eqtb[t + 10837].hh.rh] + 18].int_;
      shift_down = mem[z - mem_min + 2].int_ +
                   font_info[param_base[eqtb[t + 10837].hh.rh] + 19].int_;
      free_node(z, 7);
    }
    if (!mem[q - mem_min + 2].hh.rh) {
      x = clean_box(q + 3, ((cur_style / 4) * 2) + 5);
      mem[x - mem_min + 1].int_ += eqtb[12742].int_;
      if (shift_down <
          font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 16].int_)
        shift_down =
            font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 16].int_;
      clr = mem[x - mem_min + 3].int_ -
            (abs(font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 5].int_ *
                 4) /
             5);
      if (shift_down < clr)
        shift_down = clr;
      mem[x - mem_min + 4].int_ = shift_down;
    } else {
      x = clean_box(q + 2, ((cur_style / 4) * 2) + (cur_style & 1) + 4);
      mem[x - mem_min + 1].int_ += eqtb[12742].int_;
      if (cur_style & 1) {
        clr = font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 15].int_;
      } else if (cur_style < 2)
        clr = font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 13].int_;
      else
        clr = font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 14].int_;
      if (shift_up < clr)
        shift_up = clr;
      clr = mem[x - mem_min + 2].int_ +
            (abs(font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 5].int_) /
             4);
      if (shift_up < clr)
        shift_up = clr;
      if (!mem[q - mem_min + 3].hh.rh) {
        mem[x - mem_min + 4].int_ = -shift_up;
      } else {
        y = clean_box(q + 3, ((cur_style / 4) * 2) + 5);
        mem[y - mem_min + 1].int_ += eqtb[12742].int_;
        if (shift_down <
            font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 17].int_)
          shift_down =
              font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 17].int_;
        (clr = ((font_info[param_base[eqtb[cur_size + 10838].hh.rh] + 8].int_ *
                 4) -
                shift_up + mem[x - mem_min + 2].int_ +
                (mem[(y - mem_min + 3)].int_) - shift_down));
        if (clr > 0) {
          shift_down += clr;
          (clr = ((abs(font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 5]
                           .int_ *
                       4) /
                   5) -
                  shift_up + (mem[(x - mem_min + 2)].int_)));
          if (clr > 0) {
            shift_up += clr;
            shift_down -= clr;
          }
        }
        mem[x - mem_min + 4].int_ = delta;
        p = new_kern(shift_up - mem[x - mem_min + 2].int_ -
                     mem[y - mem_min + 3].int_ + shift_down);
        mem[x - mem_min].hh.rh = p;
        mem[p - mem_min].hh.rh = y;
        x = vpackage(x, 0, 1, 1073741823);
        mem[x - mem_min + 4].int_ = shift_down;
      }
    }
    if (mem[q - mem_min + 1].int_ == (-1073741824)) {
      mem[q - mem_min + 1].int_ = x;
      return;
    }
    p = mem[q - mem_min + 1].int_;
    while (mem[p - mem_min].hh.rh != (-1073741824))
      p = mem[p - mem_min].hh.rh;
    mem[p - mem_min].hh.rh = x;
  }
  small_number make_left_right(halfword q, small_number style, scaled max_d,
                               scaled max_h) {
    scaled delta, delta1, delta2;
    if (style < 4)
      cur_size = 0;
    else
      cur_size = ((style - 2) / 2) * 16;
    delta2 =
        max_d + font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 22].int_;
    delta1 = max_h + max_d - delta2;
    if (delta2 > delta1)
      delta1 = delta2;
    delta = (delta1 / 500) * eqtb[12181].int_;
    delta2 = delta1 + delta1 - eqtb[12740].int_;
    if (delta < delta2)
      delta = delta2;
    mem[q - mem_min + 1].int_ = var_delimiter(q + 1, cur_size, delta);
    return mem[q - mem_min].hh.U2.b0 - 10;
  }
  void mlist_to_hlist() {
    small_number save_style;
    halfword r = -1073741824;
    small_number r_type = 17, t;
    halfword p, x, y, z;
    integer pen;
    small_number s;
    scaled max_h = 0, max_d = 0, delta;
    halfword mlist = cur_mlist;
    bool penalties = mlist_penalties;
    small_number style = cur_style;
    halfword q = mlist;
    if (cur_style < 4)
      cur_size = 0;
    else
      cur_size = ((cur_style - 2) / 2) * 16;
    cur_mu = x_over_n(
        font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 6].int_, 18);
    while (q != (-1073741824)) {
    _L21:
      delta = 0;
      switch (mem[q - mem_min].hh.U2.b0) {
      case 18:
        switch (r_type) {
        case 18:
        case 17:
        case 19:
        case 20:
        case 22:
        case 30:
          mem[q - mem_min].hh.U2.b0 = 16;
          goto _L21;
          break;
        default:
          break;
        }
        break;
      case 19:
      case 21:
      case 22:
      case 31:
        if (r_type == 18)
          mem[r - mem_min].hh.U2.b0 = 16;
        if (mem[q - mem_min].hh.U2.b0 == 31)
          goto _L80;
        break;
      case 30:
        goto _L80;
        break;
      case 25:
        make_fraction(q);
        goto _L82;
        break;
      case 17:
        delta = make_op(q);
        if (mem[q - mem_min].hh.U2.b1 == 1)
          goto _L82;
        break;
      case 16:
        make_ord(q);
        break;
      case 20:
      case 23:
        // blank case
        break;
      case 24:
        make_radical(q);
        break;
      case 27:
        make_over(q);
        break;
      case 26:
        make_under(q);
        break;
      case 28:
        make_math_accent(q);
        break;
      case 29:
        make_vcenter(q);
        break;
      case 14:
        cur_style = mem[q - mem_min].hh.U2.b1;
        if (cur_style < 4)
          cur_size = 0;
        else
          cur_size = ((cur_style - 2) / 2) * 16;
        cur_mu = x_over_n(
            font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 6].int_, 18);
        goto _L81;
        break;
      case 15:
        switch (cur_style / 2) {
        case 0:
          p = mem[q - mem_min + 1].hh.lh;
          mem[q - mem_min + 1].hh.lh = -1073741824;
          break;
        case 1:
          p = mem[q - mem_min + 1].hh.rh;
          mem[q - mem_min + 1].hh.rh = -1073741824;
          break;
        case 2:
          p = mem[q - mem_min + 2].hh.lh;
          mem[q - mem_min + 2].hh.lh = -1073741824;
          break;
        case 3:
          p = mem[q - mem_min + 2].hh.rh;
          mem[q - mem_min + 2].hh.rh = -1073741824;
          break;
        }
        flush_node_list(mem[q - mem_min + 1].hh.lh);
        flush_node_list(mem[q - mem_min + 1].hh.rh);
        flush_node_list(mem[q - mem_min + 2].hh.lh);
        flush_node_list(mem[q - mem_min + 2].hh.rh);
        mem[q - mem_min].hh.U2.b0 = 14;
        mem[q - mem_min].hh.U2.b1 = cur_style;
        mem[q - mem_min + 1].int_ = 0;
        mem[q - mem_min + 2].int_ = 0;
        if (p != (-1073741824)) {
          z = mem[q - mem_min].hh.rh;
          mem[q - mem_min].hh.rh = p;
          while (mem[p - mem_min].hh.rh != (-1073741824))
            p = mem[p - mem_min].hh.rh;
          mem[p - mem_min].hh.rh = z;
        }
        goto _L81;
        break;
      case 3:
      case 4:
      case 5:
      case 8:
      case 12:
      case 7:
        goto _L81;
        break;
      case 2:
        if (mem[q - mem_min + 3].int_ > max_h)
          max_h = mem[q - mem_min + 3].int_;
        if (mem[q - mem_min + 2].int_ > max_d)
          max_d = mem[q - mem_min + 2].int_;
        goto _L81;
        break;
      case 10:
        if (mem[q - mem_min].hh.U2.b1 == 99) {
          x = mem[q - mem_min + 1].hh.lh;
          y = math_glue(x, cur_mu);
          delete_glue_ref(x);
          mem[q - mem_min + 1].hh.lh = y;
          mem[q - mem_min].hh.U2.b1 = 0;
        } else if (cur_size && (mem[q - mem_min].hh.U2.b1 == 98)) {
          p = mem[q - mem_min].hh.rh;
          if (p != (-1073741824)) {
            if ((mem[p - mem_min].hh.U2.b0 == 10) ||
                (mem[p - mem_min].hh.U2.b0 == 11)) {
              mem[q - mem_min].hh.rh = mem[p - mem_min].hh.rh;
              mem[p - mem_min].hh.rh = -1073741824;
              flush_node_list(p);
            }
          }
        }
        goto _L81;
        break;
      case 11:
        math_kern(q, cur_mu);
        goto _L81;
        break;
      default:
        confusion(888);
        break;
      }
      switch (mem[q - mem_min + 1].hh.rh) {
      case 1:
      case 4:
        fetch(q + 1);
        if (cur_i.b0 > 0) {
          delta = font_info[italic_base[cur_f] + (cur_i.b2 / 4)].int_;
          p = new_character(cur_f, cur_c);
          if ((mem[q - mem_min + 1].hh.rh == 4) &&
              font_info[param_base[cur_f] + 2].int_)
            delta = 0;
          if ((!mem[q - mem_min + 3].hh.rh) && delta) {
            mem[p - mem_min].hh.rh = new_kern(delta);
            delta = 0;
          }
        } else {
          p = -1073741824;
        }
        break;
      case 0:
        p = -1073741824;
        break;
      case 2:
        p = mem[q - mem_min + 1].hh.lh;
        break;
      case 3:
        cur_mlist = mem[q - mem_min + 1].hh.lh;
        save_style = cur_style;
        mlist_penalties = false;
        mlist_to_hlist();
        cur_style = save_style;
        if (cur_style < 4)
          cur_size = 0;
        else
          cur_size = ((cur_style - 2) / 2) * 16;
        cur_mu = x_over_n(
            font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 6].int_, 18);
        p = hpack(mem[mem_max - mem_min - 3].hh.rh, 0, 1);
        break;
      default:
        confusion(889);
        break;
      }
      mem[q - mem_min + 1].int_ = p;
      if ((!mem[q - mem_min + 3].hh.rh) && (!mem[q - mem_min + 2].hh.rh))
        goto _L82;
      make_scripts(q, delta);
    _L82:
      z = hpack(mem[q - mem_min + 1].int_, 0, 1);
      if (mem[z - mem_min + 3].int_ > max_h)
        max_h = mem[z - mem_min + 3].int_;
      if (mem[z - mem_min + 2].int_ > max_d)
        max_d = mem[z - mem_min + 2].int_;
      free_node(z, 7);
    _L80:
      r = q;
      r_type = mem[r - mem_min].hh.U2.b0;
    _L81:
      q = mem[q - mem_min].hh.rh;
    }
    if (r_type == 18)
      mem[r - mem_min].hh.U2.b0 = 16;
    p = mem_max - 3;
    mem[p - mem_min].hh.rh = -1073741824;
    q = mlist;
    r_type = 0;
    cur_style = style;
    if (cur_style < 4)
      cur_size = 0;
    else
      cur_size = ((cur_style - 2) / 2) * 16;
    cur_mu = x_over_n(
        font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 6].int_, 18);
    while (q != (-1073741824)) {
      t = 16;
      s = 4;
      pen = 10000;
      switch (mem[q - mem_min].hh.U2.b0) {
      case 17:
      case 20:
      case 21:
      case 22:
      case 23:
        t = mem[q - mem_min].hh.U2.b0;
        break;
      case 18:
        t = 18;
        pen = eqtb[12172].int_;
        break;
      case 19:
        t = 19;
        pen = eqtb[12173].int_;
        break;
      case 16:
      case 29:
      case 27:
      case 26:
        // blank case
        break;
      case 24:
        s = 5;
        break;
      case 28:
        s = 5;
        break;
      case 25:
        t = 23;
        s = 6;
        break;
      case 30:
      case 31:
        t = make_left_right(q, style, max_d, max_h);
        break;
      case 14:
        cur_style = mem[q - mem_min].hh.U2.b1;
        s = 3;
        if (cur_style < 4)
          cur_size = 0;
        else
          cur_size = ((cur_style - 2) / 2) * 16;
        cur_mu = x_over_n(
            font_info[param_base[eqtb[cur_size + 10837].hh.rh] + 6].int_, 18);
        goto _L83;
        break;
      case 8:
      case 12:
      case 2:
      case 7:
      case 5:
      case 3:
      case 4:
      case 10:
      case 11:
        mem[p - mem_min].hh.rh = q;
        p = q;
        q = mem[q - mem_min].hh.rh;
        mem[p - mem_min].hh.rh = -1073741824;
        goto _L30;
        break;
      default:
        confusion(890);
        break;
      }
      if (r_type > 0) {
        switch (str_pool[(r_type * 8) + t + magic_offset]) {
        case 48:
          x = 0;
          break;
        case 49:
          if (cur_style < 4)
            x = 15;
          else
            x = 0;
          break;
        case 50:
          x = 15;
          break;
        case 51:
          if (cur_style < 4)
            x = 16;
          else
            x = 0;
          break;
        case 52:
          if (cur_style < 4)
            x = 17;
          else
            x = 0;
          break;
        default:
          confusion(892);
          break;
        }
        if (x) {
          y = math_glue(eqtb[x + 9782].hh.rh, cur_mu);
          z = new_glue(y);
          mem[y - mem_min].hh.rh = -1073741824;
          mem[p - mem_min].hh.rh = z;
          p = z;
          mem[z - mem_min].hh.U2.b1 = x + 1;
        }
      }
      if (mem[q - mem_min + 1].int_ != (-1073741824)) {
        mem[p - mem_min].hh.rh = mem[q - mem_min + 1].int_;
        do {
          p = mem[p - mem_min].hh.rh;
        } while (mem[p - mem_min].hh.rh != (-1073741824));
      }
      if (penalties) {
        if (mem[q - mem_min].hh.rh != (-1073741824)) {
          if (pen < 10000) {
            r_type = mem[mem[q - mem_min].hh.rh - mem_min].hh.U2.b0;
            if (r_type != 12) {
              if (r_type != 19) {
                z = new_penalty(pen);
                mem[p - mem_min].hh.rh = z;
                p = z;
              }
            }
          }
        }
      }
      r_type = t;
    _L83:
      r = q;
      q = mem[q - mem_min].hh.rh;
      free_node(r, s);
    _L30:;
    }
  }
  void push_alignment() {
    halfword p = get_node(5);
    mem[p - mem_min].hh.rh = align_ptr;
    mem[p - mem_min].hh.lh = cur_align;
    mem[p - mem_min + 1].hh.lh = mem[mem_max - mem_min - 8].hh.rh;
    mem[p - mem_min + 1].hh.rh = cur_span;
    mem[p - mem_min + 2].int_ = cur_loop;
    mem[p - mem_min + 3].int_ = align_state;
    mem[p - mem_min + 4].hh.lh = cur_head;
    mem[p - mem_min + 4].hh.rh = cur_tail;
    align_ptr = p;
    cur_head = get_avail();
  }
  void pop_alignment() {
    halfword p;
    mem[cur_head - mem_min].hh.rh = avail;
    avail = cur_head;
    p = align_ptr;
    cur_tail = mem[p - mem_min + 4].hh.rh;
    cur_head = mem[p - mem_min + 4].hh.lh;
    align_state = mem[p - mem_min + 3].int_;
    cur_loop = mem[p - mem_min + 2].int_;
    cur_span = mem[p - mem_min + 1].hh.rh;
    mem[mem_max - mem_min - 8].hh.rh = mem[p - mem_min + 1].hh.lh;
    cur_align = mem[p - mem_min].hh.lh;
    align_ptr = mem[p - mem_min].hh.rh;
    free_node(p, 5);
  }
  void get_preamble_token() {
  _L20:
    get_token();
    while ((cur_chr == 256) && (cur_cmd == 4)) {
      get_token();
      if (cur_cmd > 100) {
        expand();
        get_token();
      }
    }
    if (cur_cmd == 9)
      fatal_error(595);
    if ((cur_cmd != 75) || (cur_chr != 9793))
      return;
    scan_optional_equals();
    scan_glue(2);
    if (eqtb[12206].int_ > 0)
      geq_define(9793, 117, cur_val);
    else
      eq_define(9793, 117, cur_val);
    goto _L20;
  }
  void init_align() {
    halfword p;
    halfword save_cs_ptr = cur_cs;
    push_alignment();
    align_state = -1000000;
    if ((cur_list.mode_field == 203) &&
        ((cur_list.tail_field != cur_list.head_field) ||
         (cur_list.aux_field.int_ != (-1073741824)))) {
      print_nl(262);
      print(680);
      print_esc(520);
      print(893);
      help_ptr = 3;
      help_line[2] = 894;
      help_line[1] = 895;
      help_line[0] = 896;
      error();
      flush_math();
    }
    push_nest();
    if (cur_list.mode_field == 203) {
      cur_list.mode_field = -1;
      cur_list.aux_field.int_ = nest[nest_ptr - 2].aux_field.int_;
    } else if (cur_list.mode_field > 0)
      cur_list.mode_field = -cur_list.mode_field;
    scan_spec(6, false);
    mem[mem_max - mem_min - 8].hh.rh = -1073741824;
    cur_align = mem_max - 8;
    cur_loop = -1073741824;
    scanner_status = 4;
    warning_index = save_cs_ptr;
    align_state = -1000000;
    while (true) {
      mem[cur_align - mem_min].hh.rh = new_param_glue(11);
      cur_align = mem[cur_align - mem_min].hh.rh;
      if (cur_cmd == 5)
        goto _L30;
      p = mem_max - 4;
      mem[p - mem_min].hh.rh = -1073741824;
      while (true) {
        get_preamble_token();
        if (cur_cmd == 6)
          goto _L31;
        if ((cur_cmd <= 5) && (cur_cmd >= 4) && (align_state == (-1000000))) {
          if ((p == (mem_max - 4)) && (cur_loop == (-1073741824)) &&
              (cur_cmd == 4)) {
            cur_loop = cur_align;
            continue;
          } else {
            print_nl(262);
            print(902);
            help_ptr = 3;
            help_line[2] = 903;
            help_line[1] = 904;
            help_line[0] = 905;
            back_error();
            goto _L31;
          }
        } else {
          if ((cur_cmd != 10) || (p != (mem_max - 4))) {
            mem[p - mem_min].hh.rh = get_avail();
            p = mem[p - mem_min].hh.rh;
            mem[p - mem_min].hh.lh = cur_tok;
          }
          continue;
        }
      }
    _L31:
      mem[cur_align - mem_min].hh.rh = new_null_box();
      cur_align = mem[cur_align - mem_min].hh.rh;
      mem[cur_align - mem_min].hh.lh = mem_max - 9;
      mem[cur_align - mem_min + 1].int_ = -1073741824;
      mem[cur_align - mem_min + 3].int_ = mem[mem_max - mem_min - 4].hh.rh;
      p = mem_max - 4;
      mem[p - mem_min].hh.rh = -1073741824;
      while (true) {
      _L22:
        get_preamble_token();
        if ((cur_cmd <= 5) && (cur_cmd >= 4) && (align_state == (-1000000)))
          goto _L32;
        if (cur_cmd == 6) {
          print_nl(262);
          print(906);
          help_ptr = 3;
          help_line[2] = 903;
          help_line[1] = 904;
          help_line[0] = 907;
          error();
          goto _L22;
        }
        mem[p - mem_min].hh.rh = get_avail();
        p = mem[p - mem_min].hh.rh;
        mem[p - mem_min].hh.lh = cur_tok;
      }
    _L32:
      mem[p - mem_min].hh.rh = get_avail();
      p = mem[p - mem_min].hh.rh;
      mem[p - mem_min].hh.lh = 13614;
      mem[cur_align - mem_min + 2].int_ = mem[mem_max - mem_min - 4].hh.rh;
    }
  _L30:
    scanner_status = 0;
    new_save_level(6);
    if (eqtb[10320].hh.rh != (-1073741824))
      begin_token_list(eqtb[10320].hh.rh, 13);
    align_peek();
  }
  void init_span(halfword p) {
    push_nest();
    if (cur_list.mode_field == (-102)) {
      cur_list.aux_field.hh.lh = 1000;
    } else {
      cur_list.aux_field.int_ = -65536000;
      normal_paragraph();
    }
    cur_span = p;
  }
  void init_row() {
    push_nest();
    cur_list.mode_field = (-cur_list.mode_field) - 103;
    if (cur_list.mode_field == (-102))
      cur_list.aux_field.hh.lh = 0;
    else
      cur_list.aux_field.int_ = 0;
    mem[cur_list.tail_field - mem_min].hh.rh =
        new_glue(mem[mem[mem_max - mem_min - 8].hh.rh - mem_min + 1].hh.lh);
    cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    mem[cur_list.tail_field - mem_min].hh.U2.b1 = 12;
    cur_align = mem[mem[mem_max - mem_min - 8].hh.rh - mem_min].hh.rh;
    cur_tail = cur_head;
    init_span(cur_align);
  }
  void init_col() {
    mem[cur_align - mem_min + 5].hh.lh = cur_cmd;
    if (cur_cmd == 63) {
      align_state = 0;
    } else {
      back_input();
      begin_token_list(mem[cur_align - mem_min + 3].int_, 1);
    }
  }
  bool fin_col() {
    bool result;
    halfword p, q, r, s, u;
    scaled w;
    glue_ord o;
    halfword n;
    if (cur_align == (-1073741824))
      confusion(908);
    q = mem[cur_align - mem_min].hh.rh;
    if (q == (-1073741824))
      confusion(908);
    if (align_state < 500000)
      fatal_error(595);
    p = mem[q - mem_min].hh.rh;
    if ((p == (-1073741824)) && (mem[cur_align - mem_min + 5].hh.lh < 257)) {
      if (cur_loop != (-1073741824)) {
        mem[q - mem_min].hh.rh = new_null_box();
        p = mem[q - mem_min].hh.rh;
        mem[p - mem_min].hh.lh = mem_max - 9;
        mem[p - mem_min + 1].int_ = -1073741824;
        cur_loop = mem[cur_loop - mem_min].hh.rh;
        q = mem_max - 4;
        r = mem[cur_loop - mem_min + 3].int_;
        while (r != (-1073741824)) {
          mem[q - mem_min].hh.rh = get_avail();
          q = mem[q - mem_min].hh.rh;
          mem[q - mem_min].hh.lh = mem[r - mem_min].hh.lh;
          r = mem[r - mem_min].hh.rh;
        }
        mem[q - mem_min].hh.rh = -1073741824;
        mem[p - mem_min + 3].int_ = mem[mem_max - mem_min - 4].hh.rh;
        q = mem_max - 4;
        r = mem[cur_loop - mem_min + 2].int_;
        while (r != (-1073741824)) {
          mem[q - mem_min].hh.rh = get_avail();
          q = mem[q - mem_min].hh.rh;
          mem[q - mem_min].hh.lh = mem[r - mem_min].hh.lh;
          r = mem[r - mem_min].hh.rh;
        }
        mem[q - mem_min].hh.rh = -1073741824;
        mem[p - mem_min + 2].int_ = mem[mem_max - mem_min - 4].hh.rh;
        cur_loop = mem[cur_loop - mem_min].hh.rh;
        mem[p - mem_min].hh.rh = new_glue(mem[cur_loop - mem_min + 1].hh.lh);
      } else {
        print_nl(262);
        print(909);
        print_esc(898);
        help_ptr = 3;
        help_line[2] = 910;
        help_line[1] = 911;
        help_line[0] = 912;
        mem[cur_align - mem_min + 5].hh.lh = 257;
        error();
      }
    }
    if (mem[cur_align - mem_min + 5].hh.lh != 256) {
      unsave();
      new_save_level(6);
      if (cur_list.mode_field == (-102)) {
        adjust_tail = cur_tail;
        u = hpack(mem[cur_list.head_field - mem_min].hh.rh, 0, 1);
        w = mem[u - mem_min + 1].int_;
        cur_tail = adjust_tail;
        adjust_tail = -1073741824;
      } else {
        u = vpackage(mem[cur_list.head_field - mem_min].hh.rh, 0, 1, 0);
        w = mem[u - mem_min + 3].int_;
      }
      n = 0;
      if (cur_span != cur_align) {
        q = cur_span;
        do {
          ++n;
          q = mem[mem[q - mem_min].hh.rh - mem_min].hh.rh;
        } while (q != cur_align);
        if (n > 65535)
          confusion(913);
        q = cur_span;
        while (mem[mem[q - mem_min].hh.lh - mem_min].hh.rh < n)
          q = mem[q - mem_min].hh.lh;
        if (mem[mem[q - mem_min].hh.lh - mem_min].hh.rh > n) {
          s = get_node(2);
          mem[s - mem_min].hh.lh = mem[q - mem_min].hh.lh;
          mem[s - mem_min].hh.rh = n;
          mem[q - mem_min].hh.lh = s;
          mem[s - mem_min + 1].int_ = w;
        } else if (mem[mem[q - mem_min].hh.lh - mem_min + 1].int_ < w)
          mem[mem[q - mem_min].hh.lh - mem_min + 1].int_ = w;
      } else if (w > mem[cur_align - mem_min + 1].int_)
        mem[cur_align - mem_min + 1].int_ = w;
      mem[u - mem_min].hh.U2.b0 = 13;
      mem[u - mem_min].hh.U2.b1 = n;
      if (total_stretch[3]) {
        o = 3;
      } else if (total_stretch[2]) {
        o = 2;
      } else if (total_stretch[1])
        o = 1;
      else
        o = 0;
      mem[u - mem_min + 5].hh.U2.b1 = o;
      mem[u - mem_min + 6].int_ = total_stretch[o];
      if (total_shrink[3]) {
        o = 3;
      } else if (total_shrink[2]) {
        o = 2;
      } else if (total_shrink[1])
        o = 1;
      else
        o = 0;
      mem[u - mem_min + 5].hh.U2.b0 = o;
      mem[u - mem_min + 4].int_ = total_shrink[o];
      pop_nest();
      mem[cur_list.tail_field - mem_min].hh.rh = u;
      cur_list.tail_field = u;
      mem[cur_list.tail_field - mem_min].hh.rh =
          new_glue(mem[mem[cur_align - mem_min].hh.rh - mem_min + 1].hh.lh);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      mem[cur_list.tail_field - mem_min].hh.U2.b1 = 12;
      if (mem[cur_align - mem_min + 5].hh.lh >= 257) {
        result = true;
        goto _L10;
      }
      init_span(p);
    }
    align_state = 1000000;
    do {
      get_x_token();
    } while (cur_cmd == 10);
    cur_align = p;
    init_col();
    result = false;
  _L10:
    return result;
  }
  void fin_row() {
    halfword p;
    if (cur_list.mode_field == (-102)) {
      p = hpack(mem[cur_list.head_field - mem_min].hh.rh, 0, 1);
      pop_nest();
      append_to_vlist(p);
      if (cur_head != cur_tail) {
        mem[cur_list.tail_field - mem_min].hh.rh =
            mem[cur_head - mem_min].hh.rh;
        cur_list.tail_field = cur_tail;
      }
    } else {
      p = vpackage(mem[cur_list.head_field - mem_min].hh.rh, 0, 1, 1073741823);
      pop_nest();
      mem[cur_list.tail_field - mem_min].hh.rh = p;
      cur_list.tail_field = p;
      cur_list.aux_field.hh.lh = 1000;
    }
    mem[p - mem_min].hh.U2.b0 = 13;
    mem[p - mem_min + 6].int_ = 0;
    if (eqtb[10320].hh.rh != (-1073741824))
      begin_token_list(eqtb[10320].hh.rh, 13);
    align_peek();
  }
  void fin_align() {
    halfword p, q, r, s, u, v, n;
    scaled t, w, o, rule_save;
    memory_word aux_save;
    if (cur_group != 6)
      confusion(914);
    unsave();
    if (cur_group != 6)
      confusion(915);
    unsave();
    if (nest[nest_ptr - 1].mode_field == 203)
      o = eqtb[12745].int_;
    else
      o = 0;
    q = mem[mem[mem_max - mem_min - 8].hh.rh - mem_min].hh.rh;
    do {
      flush_list(mem[q - mem_min + 3].int_);
      flush_list(mem[q - mem_min + 2].int_);
      p = mem[mem[q - mem_min].hh.rh - mem_min].hh.rh;
      if (mem[q - mem_min + 1].int_ == (-1073741824)) {
        mem[q - mem_min + 1].int_ = 0;
        r = mem[q - mem_min].hh.rh;
        s = mem[r - mem_min + 1].hh.lh;
        if (s) {
          ++mem[-mem_min].hh.rh;
          delete_glue_ref(s);
          mem[r - mem_min + 1].hh.lh = 0;
        }
      }
      if (mem[q - mem_min].hh.lh != (mem_max - 9)) {
        t = mem[q - mem_min + 1].int_ +
            mem[mem[mem[q - mem_min].hh.rh - mem_min + 1].hh.lh - mem_min + 1]
                .int_;
        r = mem[q - mem_min].hh.lh;
        s = mem_max - 9;
        mem[s - mem_min].hh.lh = p;
        n = 1;
        do {
          mem[r - mem_min + 1].int_ -= t;
          u = mem[r - mem_min].hh.lh;
          while (mem[r - mem_min].hh.rh > n) {
            s = mem[s - mem_min].hh.lh;
            n = mem[mem[s - mem_min].hh.lh - mem_min].hh.rh + 1;
          }
          if (mem[r - mem_min].hh.rh < n) {
            mem[r - mem_min].hh.lh = mem[s - mem_min].hh.lh;
            mem[s - mem_min].hh.lh = r;
            --mem[r - mem_min].hh.rh;
            s = r;
          } else {
            if (mem[r - mem_min + 1].int_ >
                mem[mem[s - mem_min].hh.lh - mem_min + 1].int_)
              mem[mem[s - mem_min].hh.lh - mem_min + 1].int_ =
                  mem[r - mem_min + 1].int_;
            free_node(r, 2);
          }
          r = u;
        } while (r != (mem_max - 9));
      }
      mem[q - mem_min].hh.U2.b0 = 13;
      mem[q - mem_min].hh.U2.b1 = 0;
      mem[q - mem_min + 3].int_ = 0;
      mem[q - mem_min + 2].int_ = 0;
      mem[q - mem_min + 5].hh.U2.b1 = 0;
      mem[q - mem_min + 5].hh.U2.b0 = 0;
      mem[q - mem_min + 6].int_ = 0;
      mem[q - mem_min + 4].int_ = 0;
      q = p;
    } while (q != (-1073741824));
    save_ptr -= 2;
    pack_begin_line = -cur_list.ml_field;
    if (cur_list.mode_field == (-1)) {
      rule_save = eqtb[12746].int_;
      eqtb[12746].int_ = 0;
      p = hpack(mem[mem_max - mem_min - 8].hh.rh, save_stack[save_ptr + 1].int_,
                save_stack[save_ptr].int_);
      eqtb[12746].int_ = rule_save;
    } else {
      q = mem[mem[mem_max - mem_min - 8].hh.rh - mem_min].hh.rh;
      do {
        mem[q - mem_min + 3].int_ = mem[q - mem_min + 1].int_;
        mem[q - mem_min + 1].int_ = 0;
        q = mem[mem[q - mem_min].hh.rh - mem_min].hh.rh;
      } while (q != (-1073741824));
      p = vpackage(mem[mem_max - mem_min - 8].hh.rh,
                   save_stack[save_ptr + 1].int_, save_stack[save_ptr].int_,
                   1073741823);
      q = mem[mem[mem_max - mem_min - 8].hh.rh - mem_min].hh.rh;
      do {
        mem[q - mem_min + 1].int_ = mem[q - mem_min + 3].int_;
        mem[q - mem_min + 3].int_ = 0;
        q = mem[mem[q - mem_min].hh.rh - mem_min].hh.rh;
      } while (q != (-1073741824));
    }
    pack_begin_line = 0;
    q = mem[cur_list.head_field - mem_min].hh.rh;
    s = cur_list.head_field;
    while (q != (-1073741824)) {
      if (q < hi_mem_min) {
        if (mem[q - mem_min].hh.U2.b0 == 13) {
          if (cur_list.mode_field == (-1)) {
            mem[q - mem_min].hh.U2.b0 = 0;
            mem[q - mem_min + 1].int_ = mem[p - mem_min + 1].int_;
          } else {
            mem[q - mem_min].hh.U2.b0 = 1;
            mem[q - mem_min + 3].int_ = mem[p - mem_min + 3].int_;
          }
          mem[q - mem_min + 5].hh.U2.b1 = mem[p - mem_min + 5].hh.U2.b1;
          mem[q - mem_min + 5].hh.U2.b0 = mem[p - mem_min + 5].hh.U2.b0;
          mem[q - mem_min + 6].gr = mem[p - mem_min + 6].gr;
          mem[q - mem_min + 4].int_ = o;
          r = mem[mem[q - mem_min + 5].hh.rh - mem_min].hh.rh;
          s = mem[mem[p - mem_min + 5].hh.rh - mem_min].hh.rh;
          do {
            n = mem[r - mem_min].hh.U2.b1;
            t = mem[s - mem_min + 1].int_;
            w = t;
            u = mem_max - 4;
            while (n > 0) {
              --n;
              s = mem[s - mem_min].hh.rh;
              v = mem[s - mem_min + 1].hh.lh;
              mem[u - mem_min].hh.rh = new_glue(v);
              u = mem[u - mem_min].hh.rh;
              mem[u - mem_min].hh.U2.b1 = 12;
              t += mem[v - mem_min + 1].int_;
              if (mem[p - mem_min + 5].hh.U2.b0 == 1) {
                if (mem[v - mem_min].hh.U2.b0 == mem[p - mem_min + 5].hh.U2.b1)
                  t += int(round(mem[p - mem_min + 6].gr *
                                 mem[v - mem_min + 2].int_));
              } else if (mem[p - mem_min + 5].hh.U2.b0 == 2) {
                if (mem[v - mem_min].hh.U2.b1 == mem[p - mem_min + 5].hh.U2.b1)
                  t -= int(round(mem[p - mem_min + 6].gr *
                                 mem[v - mem_min + 3].int_));
              }
              s = mem[s - mem_min].hh.rh;
              mem[u - mem_min].hh.rh = new_null_box();
              u = mem[u - mem_min].hh.rh;
              t += mem[s - mem_min + 1].int_;
              if (cur_list.mode_field == (-1)) {
                mem[u - mem_min + 1].int_ = mem[s - mem_min + 1].int_;
              } else {
                mem[u - mem_min].hh.U2.b0 = 1;
                mem[u - mem_min + 3].int_ = mem[s - mem_min + 1].int_;
              }
            }
            if (cur_list.mode_field == (-1)) {
              mem[r - mem_min + 3].int_ = mem[q - mem_min + 3].int_;
              mem[r - mem_min + 2].int_ = mem[q - mem_min + 2].int_;
              if (t == mem[r - mem_min + 1].int_) {
                mem[r - mem_min + 5].hh.U2.b0 = 0;
                mem[r - mem_min + 5].hh.U2.b1 = 0;
                mem[r - mem_min + 6].gr = 0.0;
              } else if (t > mem[r - mem_min + 1].int_) {
                mem[r - mem_min + 5].hh.U2.b0 = 1;
                if (!mem[r - mem_min + 6].int_)
                  mem[r - mem_min + 6].gr = 0.0;
                else
                  mem[r - mem_min + 6].gr =
                      ((double)(t - mem[r - mem_min + 1].int_)) /
                      mem[r - mem_min + 6].int_;
              } else {
                mem[r - mem_min + 5].hh.U2.b1 = mem[r - mem_min + 5].hh.U2.b0;
                mem[r - mem_min + 5].hh.U2.b0 = 2;
                if (!mem[r - mem_min + 4].int_) {
                  mem[r - mem_min + 6].gr = 0.0;
                } else if ((!mem[r - mem_min + 5].hh.U2.b1) &&
                           (mem[r - mem_min + 1].int_ - t >
                            mem[r - mem_min + 4].int_))
                  mem[r - mem_min + 6].gr = 1.0;
                else
                  mem[r - mem_min + 6].gr =
                      ((double)(mem[r - mem_min + 1].int_ - t)) /
                      mem[r - mem_min + 4].int_;
              }
              mem[r - mem_min + 1].int_ = w;
              mem[r - mem_min].hh.U2.b0 = 0;
            } else {
              mem[r - mem_min + 1].int_ = mem[q - mem_min + 1].int_;
              if (t == mem[r - mem_min + 3].int_) {
                mem[r - mem_min + 5].hh.U2.b0 = 0;
                mem[r - mem_min + 5].hh.U2.b1 = 0;
                mem[r - mem_min + 6].gr = 0.0;
              } else if (t > mem[r - mem_min + 3].int_) {
                mem[r - mem_min + 5].hh.U2.b0 = 1;
                if (!mem[r - mem_min + 6].int_)
                  mem[r - mem_min + 6].gr = 0.0;
                else
                  mem[r - mem_min + 6].gr =
                      ((double)(t - mem[r - mem_min + 3].int_)) /
                      mem[r - mem_min + 6].int_;
              } else {
                mem[r - mem_min + 5].hh.U2.b1 = mem[r - mem_min + 5].hh.U2.b0;
                mem[r - mem_min + 5].hh.U2.b0 = 2;
                if (!mem[r - mem_min + 4].int_) {
                  mem[r - mem_min + 6].gr = 0.0;
                } else if ((!mem[r - mem_min + 5].hh.U2.b1) &&
                           (mem[r - mem_min + 3].int_ - t >
                            mem[r - mem_min + 4].int_))
                  mem[r - mem_min + 6].gr = 1.0;
                else
                  mem[r - mem_min + 6].gr =
                      ((double)(mem[r - mem_min + 3].int_ - t)) /
                      mem[r - mem_min + 4].int_;
              }
              mem[r - mem_min + 3].int_ = w;
              mem[r - mem_min].hh.U2.b0 = 1;
            }
            mem[r - mem_min + 4].int_ = 0;
            if (u != (mem_max - 4)) {
              mem[u - mem_min].hh.rh = mem[r - mem_min].hh.rh;
              mem[r - mem_min].hh.rh = mem[mem_max - mem_min - 4].hh.rh;
              r = u;
            }
            r = mem[mem[r - mem_min].hh.rh - mem_min].hh.rh;
            s = mem[mem[s - mem_min].hh.rh - mem_min].hh.rh;
          } while (r != (-1073741824));
        } else if (mem[q - mem_min].hh.U2.b0 == 2) {
          if (mem[q - mem_min + 1].int_ == (-1073741824))
            mem[q - mem_min + 1].int_ = mem[p - mem_min + 1].int_;
          if (mem[q - mem_min + 3].int_ == (-1073741824))
            mem[q - mem_min + 3].int_ = mem[p - mem_min + 3].int_;
          if (mem[q - mem_min + 2].int_ == (-1073741824))
            mem[q - mem_min + 2].int_ = mem[p - mem_min + 2].int_;
          if (o) {
            r = mem[q - mem_min].hh.rh;
            mem[q - mem_min].hh.rh = -1073741824;
            q = hpack(q, 0, 1);
            mem[q - mem_min + 4].int_ = o;
            mem[q - mem_min].hh.rh = r;
            mem[s - mem_min].hh.rh = q;
          }
        }
      }
      s = q;
      q = mem[q - mem_min].hh.rh;
    }
    flush_node_list(p);
    pop_alignment();
    aux_save = cur_list.aux_field;
    p = mem[cur_list.head_field - mem_min].hh.rh;
    q = cur_list.tail_field;
    pop_nest();
    if (cur_list.mode_field == 203) {
      do_assignments();
      if (cur_cmd != 3) {
        print_nl(262);
        print(1169);
        help_ptr = 2;
        help_line[1] = 894;
        help_line[0] = 895;
        back_error();
      } else {
        get_x_token();
        if (cur_cmd != 3) {
          print_nl(262);
          print(1165);
          help_ptr = 2;
          help_line[1] = 1166;
          help_line[0] = 1167;
          back_error();
        }
      }
      pop_nest();
      mem[cur_list.tail_field - mem_min].hh.rh = new_penalty(eqtb[12174].int_);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      mem[cur_list.tail_field - mem_min].hh.rh = new_param_glue(3);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      mem[cur_list.tail_field - mem_min].hh.rh = p;
      if (p != (-1073741824))
        cur_list.tail_field = q;
      mem[cur_list.tail_field - mem_min].hh.rh = new_penalty(eqtb[12175].int_);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      mem[cur_list.tail_field - mem_min].hh.rh = new_param_glue(4);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      cur_list.aux_field.int_ = aux_save.int_;
      resume_after_display();
      return;
    }
    cur_list.aux_field = aux_save;
    mem[cur_list.tail_field - mem_min].hh.rh = p;
    if (p != (-1073741824))
      cur_list.tail_field = q;
    if (cur_list.mode_field == 1)
      build_page();
  }
  void align_peek() {
  _L20:
    align_state = 1000000;
    do {
      get_x_token();
    } while (cur_cmd == 10);
    if (cur_cmd == 34) {
      scan_left_brace();
      new_save_level(7);
      if (cur_list.mode_field == (-1))
        normal_paragraph();
      return;
    }
    if (cur_cmd == 2) {
      fin_align();
      return;
    }
    if ((cur_cmd == 5) && (cur_chr == 258))
      goto _L20;
    init_row();
    init_col();
  }
  halfword finite_shrink(halfword p) {
    halfword q;
    if (no_shrink_error_yet) {
      no_shrink_error_yet = false;
      print_nl(262);
      print(916);
      help_ptr = 5;
      help_line[4] = 917;
      help_line[3] = 918;
      help_line[2] = 919;
      help_line[1] = 920;
      help_line[0] = 921;
      error();
    }
    q = new_spec(p);
    mem[q - mem_min].hh.U2.b1 = 0;
    delete_glue_ref(p);
    return q;
  }
  void try_break(integer pi, small_number break_type) {
    halfword r, prev_r = mem_max - 7, old_l = 0;
    bool no_break_yet = true;
    halfword prev_prev_r, s, q, v;
    integer t, d;
    internal_font_number f;
    halfword l;
    bool node_r_stays_active;
    scaled line_width, shortfall;
    char fit_class;
    halfword b;
    bool artificial_demerits;
    if (abs(pi) >= 10000) {
      if (pi > 0)
        goto _L10;
      pi = -10000;
    }
    cur_active_width[1] = active_width[1];
    cur_active_width[2] = active_width[2];
    cur_active_width[3] = active_width[3];
    cur_active_width[4] = active_width[4];
    cur_active_width[5] = active_width[5];
    cur_active_width[6] = active_width[6];
    while (true) {
    _L22:
      r = mem[prev_r - mem_min].hh.rh;
      if (mem[r - mem_min].hh.U2.b0 == 2) {
        cur_active_width[1] += mem[r - mem_min + 1].int_;
        cur_active_width[2] += mem[r - mem_min + 2].int_;
        cur_active_width[3] += mem[r - mem_min + 3].int_;
        cur_active_width[4] += mem[r - mem_min + 4].int_;
        cur_active_width[5] += mem[r - mem_min + 5].int_;
        cur_active_width[6] += mem[r - mem_min + 6].int_;
        prev_prev_r = prev_r;
        prev_r = r;
        goto _L22;
      }
      l = mem[r - mem_min + 1].hh.lh;
      if (l > old_l) {
        if ((minimum_demerits < 1073741823) &&
            ((old_l != easy_line) || (r == (mem_max - 7)))) {
          if (no_break_yet) {
            no_break_yet = false;
            break_width[1] = background[1];
            break_width[2] = background[2];
            break_width[3] = background[3];
            break_width[4] = background[4];
            break_width[5] = background[5];
            break_width[6] = background[6];
            s = cur_p;
            if (break_type > 0) {
              if (cur_p != (-1073741824)) {
                t = mem[cur_p - mem_min].hh.U2.b1;
                v = cur_p;
                s = mem[cur_p - mem_min + 1].hh.rh;
                while (t > 0) {
                  --t;
                  v = mem[v - mem_min].hh.rh;
                  if (v >= hi_mem_min) {
                    f = mem[v - mem_min].hh.U2.b0;
                    (break_width[1] -=
                     (font_info[(width_base[f] +
                                 ((font_info[(char_base[f] +
                                              ((mem[v - mem_min].hh).U2.b1))]
                                       .qqqq)
                                      .b0))]
                          .int_));
                    continue;
                  }
                  switch (mem[v - mem_min].hh.U2.b0) {
                  case 6:
                    f = mem[v - mem_min + 1].hh.U2.b0;
                    (break_width[1] -=
                     (font_info
                          [(width_base[f] +
                            ((font_info[(char_base[f] +
                                         ((mem[(v - mem_min + 1)].hh).U2.b1))]
                                  .qqqq)
                                 .b0))]
                              .int_));
                    break;
                  case 0:
                  case 1:
                  case 2:
                  case 11:
                    break_width[1] -= mem[v - mem_min + 1].int_;
                    break;
                  default:
                    confusion(922);
                    break;
                  }
                }
                while (s != (-1073741824)) {
                  if (s >= hi_mem_min) {
                    f = mem[s - mem_min].hh.U2.b0;
                    (break_width[1] +=
                     (font_info[(width_base[f] +
                                 ((font_info[(char_base[f] +
                                              ((mem[s - mem_min].hh).U2.b1))]
                                       .qqqq)
                                      .b0))]
                          .int_));
                  } else {
                    switch (mem[s - mem_min].hh.U2.b0) {
                    case 6:
                      f = mem[s - mem_min + 1].hh.U2.b0;
                      (break_width[1] +=
                       (font_info
                            [(width_base[f] +
                              ((font_info[(char_base[f] +
                                           ((mem[(s - mem_min + 1)].hh).U2.b1))]
                                    .qqqq)
                                   .b0))]
                                .int_));
                      break;
                    case 0:
                    case 1:
                    case 2:
                    case 11:
                      break_width[1] += mem[s - mem_min + 1].int_;
                      break;
                    default:
                      confusion(923);
                      break;
                    }
                  }
                  s = mem[s - mem_min].hh.rh;
                }
                break_width[1] += disc_width;
                if (mem[cur_p - mem_min + 1].hh.rh == (-1073741824))
                  s = mem[v - mem_min].hh.rh;
              }
            }
            while (s != (-1073741824)) {
              if (s >= hi_mem_min)
                goto _L30;
              switch (mem[s - mem_min].hh.U2.b0) {
              case 10:
                v = mem[s - mem_min + 1].hh.lh;
                break_width[1] -= mem[v - mem_min + 1].int_;
                break_width[mem[v - mem_min].hh.U2.b0 + 2] -=
                    mem[v - mem_min + 2].int_;
                break_width[6] -= mem[v - mem_min + 3].int_;
                break;
              case 12:
                // blank case
                break;
              case 9:
                break_width[1] -= mem[s - mem_min + 1].int_;
                break;
              case 11:
                if (mem[s - mem_min].hh.U2.b1 != 1)
                  goto _L30;
                break_width[1] -= mem[s - mem_min + 1].int_;
                break;
              default:
                goto _L30;
                break;
              }
              s = mem[s - mem_min].hh.rh;
            }
          _L30:;
          }
          if (mem[prev_r - mem_min].hh.U2.b0 == 2) {
            mem[prev_r - mem_min + 1].int_ +=
                break_width[1] - cur_active_width[1];
            mem[prev_r - mem_min + 2].int_ +=
                break_width[2] - cur_active_width[2];
            mem[prev_r - mem_min + 3].int_ +=
                break_width[3] - cur_active_width[3];
            mem[prev_r - mem_min + 4].int_ +=
                break_width[4] - cur_active_width[4];
            mem[prev_r - mem_min + 5].int_ +=
                break_width[5] - cur_active_width[5];
            mem[prev_r - mem_min + 6].int_ +=
                break_width[6] - cur_active_width[6];
          } else if (prev_r == (mem_max - 7)) {
            active_width[1] = break_width[1];
            active_width[2] = break_width[2];
            active_width[3] = break_width[3];
            active_width[4] = break_width[4];
            active_width[5] = break_width[5];
            active_width[6] = break_width[6];
          } else {
            q = get_node(7);
            mem[q - mem_min].hh.rh = r;
            mem[q - mem_min].hh.U2.b0 = 2;
            mem[q - mem_min].hh.U2.b1 = 0;
            mem[q - mem_min + 1].int_ = break_width[1] - cur_active_width[1];
            mem[q - mem_min + 2].int_ = break_width[2] - cur_active_width[2];
            mem[q - mem_min + 3].int_ = break_width[3] - cur_active_width[3];
            mem[q - mem_min + 4].int_ = break_width[4] - cur_active_width[4];
            mem[q - mem_min + 5].int_ = break_width[5] - cur_active_width[5];
            mem[q - mem_min + 6].int_ = break_width[6] - cur_active_width[6];
            mem[prev_r - mem_min].hh.rh = q;
            prev_prev_r = prev_r;
            prev_r = q;
          }
          if (abs(eqtb[12179].int_) >= (1073741823 - minimum_demerits))
            minimum_demerits = 1073741822;
          else
            minimum_demerits += abs(eqtb[12179].int_);
          for (fit_class = 0; fit_class <= 3; ++fit_class) {
            if (minimal_demerits[fit_class] <= minimum_demerits) {
              q = get_node(2);
              mem[q - mem_min].hh.rh = passive;
              passive = q;
              mem[q - mem_min + 1].hh.rh = cur_p;
              mem[q - mem_min + 1].hh.lh = best_place[fit_class];
              q = get_node(3);
              mem[q - mem_min + 1].hh.rh = passive;
              mem[q - mem_min + 1].hh.lh = best_pl_line[fit_class] + 1;
              mem[q - mem_min].hh.U2.b1 = fit_class;
              mem[q - mem_min].hh.U2.b0 = break_type;
              mem[q - mem_min + 2].int_ = minimal_demerits[fit_class];
              mem[q - mem_min].hh.rh = r;
              mem[prev_r - mem_min].hh.rh = q;
              prev_r = q;
            }
            minimal_demerits[fit_class] = 1073741823;
          }
          minimum_demerits = 1073741823;
          if (r != (mem_max - 7)) {
            q = get_node(7);
            mem[q - mem_min].hh.rh = r;
            mem[q - mem_min].hh.U2.b0 = 2;
            mem[q - mem_min].hh.U2.b1 = 0;
            mem[q - mem_min + 1].int_ = cur_active_width[1] - break_width[1];
            mem[q - mem_min + 2].int_ = cur_active_width[2] - break_width[2];
            mem[q - mem_min + 3].int_ = cur_active_width[3] - break_width[3];
            mem[q - mem_min + 4].int_ = cur_active_width[4] - break_width[4];
            mem[q - mem_min + 5].int_ = cur_active_width[5] - break_width[5];
            mem[q - mem_min + 6].int_ = cur_active_width[6] - break_width[6];
            mem[prev_r - mem_min].hh.rh = q;
            prev_prev_r = prev_r;
            prev_r = q;
          }
        }
        if (r == (mem_max - 7))
          goto _L10;
        if (l > easy_line) {
          line_width = second_width;
          old_l = 1073741823;
        } else {
          old_l = l;
          if (l > last_special_line) {
            line_width = second_width;
          } else if (eqtb[10312].hh.rh == (-1073741824))
            line_width = first_width;
          else
            line_width = mem[eqtb[10312].hh.rh + (l * 2) - mem_min].int_;
        }
      }
      artificial_demerits = false;
      shortfall = line_width - cur_active_width[1];
      if (shortfall > 0) {
        if (cur_active_width[3] || cur_active_width[4] || cur_active_width[5]) {
          b = 0;
          fit_class = 2;
        } else {
          if (shortfall > 7230584) {
            if (cur_active_width[2] < 1663497) {
              b = 10000;
              fit_class = 0;
              goto _L31;
            }
          }
          b = badness(shortfall, cur_active_width[2]);
          if (b > 12) {
            if (b > 99)
              fit_class = 0;
            else
              fit_class = 1;
          } else {
            fit_class = 2;
          }
        _L31:;
        }
      } else {
        if (-shortfall > cur_active_width[6])
          b = 10001;
        else
          b = badness(-shortfall, cur_active_width[6]);
        if (b > 12)
          fit_class = 3;
        else
          fit_class = 2;
      }
      if ((b > 10000) || (pi == (-10000))) {
        if (final_pass && (minimum_demerits == 1073741823) &&
            (mem[r - mem_min].hh.rh == (mem_max - 7)) &&
            (prev_r == (mem_max - 7))) {
          artificial_demerits = true;
        } else if (b > threshold)
          goto _L60;
        node_r_stays_active = false;
      } else {
        prev_r = r;
        if (b > threshold)
          goto _L22;
        node_r_stays_active = true;
      }
      if (artificial_demerits) {
        d = 0;
      } else {
        d = eqtb[12165].int_ + b;
        if (abs(d) >= 10000)
          d = 100000000;
        else
          d *= d;
        if (pi) {
          if (pi > 0) {
            d += pi * pi;
          } else if (pi > (-10000))
            d -= pi * pi;
        }
        if ((break_type == 1) && (mem[r - mem_min].hh.U2.b0 == 1)) {
          if (cur_p != (-1073741824))
            d += eqtb[12177].int_;
          else
            d += eqtb[12178].int_;
        }
        if (abs(fit_class - mem[r - mem_min].hh.U2.b1) > 1)
          d += eqtb[12179].int_;
      }
      d += mem[r - mem_min + 2].int_;
      if (d <= minimal_demerits[fit_class]) {
        minimal_demerits[fit_class] = d;
        best_place[fit_class] = mem[r - mem_min + 1].hh.rh;
        best_pl_line[fit_class] = l;
        if (d < minimum_demerits)
          minimum_demerits = d;
      }
      if (node_r_stays_active)
        goto _L22;
    _L60:
      mem[prev_r - mem_min].hh.rh = mem[r - mem_min].hh.rh;
      free_node(r, 3);
      if (prev_r == (mem_max - 7)) {
        r = mem[mem_max - mem_min - 7].hh.rh;
        if (mem[r - mem_min].hh.U2.b0 != 2)
          continue;
        active_width[1] += mem[r - mem_min + 1].int_;
        active_width[2] += mem[r - mem_min + 2].int_;
        active_width[3] += mem[r - mem_min + 3].int_;
        active_width[4] += mem[r - mem_min + 4].int_;
        active_width[5] += mem[r - mem_min + 5].int_;
        active_width[6] += mem[r - mem_min + 6].int_;
        cur_active_width[1] = active_width[1];
        cur_active_width[2] = active_width[2];
        cur_active_width[3] = active_width[3];
        cur_active_width[4] = active_width[4];
        cur_active_width[5] = active_width[5];
        cur_active_width[6] = active_width[6];
        mem[mem_max - mem_min - 7].hh.rh = mem[r - mem_min].hh.rh;
        free_node(r, 7);
        continue;
      }
      if (mem[prev_r - mem_min].hh.U2.b0 != 2)
        continue;
      r = mem[prev_r - mem_min].hh.rh;
      if (r == (mem_max - 7)) {
        cur_active_width[1] -= mem[prev_r - mem_min + 1].int_;
        cur_active_width[2] -= mem[prev_r - mem_min + 2].int_;
        cur_active_width[3] -= mem[prev_r - mem_min + 3].int_;
        cur_active_width[4] -= mem[prev_r - mem_min + 4].int_;
        cur_active_width[5] -= mem[prev_r - mem_min + 5].int_;
        cur_active_width[6] -= mem[prev_r - mem_min + 6].int_;
        mem[prev_prev_r - mem_min].hh.rh = mem_max - 7;
        free_node(prev_r, 7);
        prev_r = prev_prev_r;
        continue;
      }
      if (mem[r - mem_min].hh.U2.b0 != 2)
        continue;
      cur_active_width[1] += mem[r - mem_min + 1].int_;
      cur_active_width[2] += mem[r - mem_min + 2].int_;
      cur_active_width[3] += mem[r - mem_min + 3].int_;
      cur_active_width[4] += mem[r - mem_min + 4].int_;
      cur_active_width[5] += mem[r - mem_min + 5].int_;
      cur_active_width[6] += mem[r - mem_min + 6].int_;
      mem[prev_r - mem_min + 1].int_ += mem[r - mem_min + 1].int_;
      mem[prev_r - mem_min + 2].int_ += mem[r - mem_min + 2].int_;
      mem[prev_r - mem_min + 3].int_ += mem[r - mem_min + 3].int_;
      mem[prev_r - mem_min + 4].int_ += mem[r - mem_min + 4].int_;
      mem[prev_r - mem_min + 5].int_ += mem[r - mem_min + 5].int_;
      mem[prev_r - mem_min + 6].int_ += mem[r - mem_min + 6].int_;
      mem[prev_r - mem_min].hh.rh = mem[r - mem_min].hh.rh;
      free_node(r, 7);
    }
  _L10:;
  }
  void post_line_break(integer final_widow_penalty) {
    halfword r, s;
    bool disc_break, post_disc_break;
    scaled cur_width, cur_indent;
    quarterword t;
    integer pen;
    halfword cur_line;
    halfword q = mem[best_bet - mem_min + 1].hh.rh;
    cur_p = -1073741824;
    do {
      r = q;
      q = mem[q - mem_min + 1].hh.lh;
      mem[r - mem_min + 1].hh.lh = cur_p;
      cur_p = r;
    } while (q != (-1073741824));
    cur_line = cur_list.pg_field + 1;
    do {
      q = mem[cur_p - mem_min + 1].hh.rh;
      disc_break = false;
      post_disc_break = false;
      if (q != (-1073741824)) {
        if (mem[q - mem_min].hh.U2.b0 == 10) {
          delete_glue_ref(mem[q - mem_min + 1].hh.lh);
          mem[q - mem_min + 1].hh.lh = eqtb[9790].hh.rh;
          mem[q - mem_min].hh.U2.b1 = 9;
          ++mem[eqtb[9790].hh.rh - mem_min].hh.rh;
          goto _L30;
        }
        if (mem[q - mem_min].hh.U2.b0 == 7) {
          t = mem[q - mem_min].hh.U2.b1;
          if (!t) {
            r = mem[q - mem_min].hh.rh;
          } else {
            r = q;
            while (t > 1) {
              r = mem[r - mem_min].hh.rh;
              --t;
            }
            s = mem[r - mem_min].hh.rh;
            r = mem[s - mem_min].hh.rh;
            mem[s - mem_min].hh.rh = -1073741824;
            flush_node_list(mem[q - mem_min].hh.rh);
            mem[q - mem_min].hh.U2.b1 = 0;
          }
          if (mem[q - mem_min + 1].hh.rh != (-1073741824)) {
            s = mem[q - mem_min + 1].hh.rh;
            while (mem[s - mem_min].hh.rh != (-1073741824))
              s = mem[s - mem_min].hh.rh;
            mem[s - mem_min].hh.rh = r;
            r = mem[q - mem_min + 1].hh.rh;
            mem[q - mem_min + 1].hh.rh = -1073741824;
            post_disc_break = true;
          }
          if (mem[q - mem_min + 1].hh.lh != (-1073741824)) {
            s = mem[q - mem_min + 1].hh.lh;
            mem[q - mem_min].hh.rh = s;
            while (mem[s - mem_min].hh.rh != (-1073741824))
              s = mem[s - mem_min].hh.rh;
            mem[q - mem_min + 1].hh.lh = -1073741824;
            q = s;
          }
          mem[q - mem_min].hh.rh = r;
          disc_break = true;
        } else if ((mem[q - mem_min].hh.U2.b0 == 9) ||
                   (mem[q - mem_min].hh.U2.b0 == 11))
          mem[q - mem_min + 1].int_ = 0;
      } else {
        q = mem_max - 3;
        while (mem[q - mem_min].hh.rh != (-1073741824))
          q = mem[q - mem_min].hh.rh;
      }
      r = new_param_glue(8);
      mem[r - mem_min].hh.rh = mem[q - mem_min].hh.rh;
      mem[q - mem_min].hh.rh = r;
      q = r;
    _L30:
      r = mem[q - mem_min].hh.rh;
      mem[q - mem_min].hh.rh = -1073741824;
      q = mem[mem_max - mem_min - 3].hh.rh;
      mem[mem_max - mem_min - 3].hh.rh = r;
      if (eqtb[9789].hh.rh) {
        r = new_param_glue(7);
        mem[r - mem_min].hh.rh = q;
        q = r;
      }
      if (cur_line > last_special_line) {
        cur_width = second_width;
        cur_indent = second_indent;
      } else if (eqtb[10312].hh.rh == (-1073741824)) {
        cur_width = first_width;
        cur_indent = first_indent;
      } else {
        cur_width = mem[eqtb[10312].hh.rh + (cur_line * 2) - mem_min].int_;
        cur_indent = mem[eqtb[10312].hh.rh + (cur_line * 2) - mem_min - 1].int_;
      }
      adjust_tail = mem_max - 5;
      just_box = hpack(q, cur_width, 0);
      mem[just_box - mem_min + 4].int_ = cur_indent;
      append_to_vlist(just_box);
      if (mem_max - 5 != adjust_tail) {
        mem[cur_list.tail_field - mem_min].hh.rh =
            mem[mem_max - mem_min - 5].hh.rh;
        cur_list.tail_field = adjust_tail;
      }
      adjust_tail = -1073741824;
      if (cur_line + 1 != best_line) {
        pen = eqtb[12176].int_;
        if (cur_line == (cur_list.pg_field + 1))
          pen += eqtb[12168].int_;
        if (cur_line + 2 == best_line)
          pen += final_widow_penalty;
        if (disc_break)
          pen += eqtb[12171].int_;
        if (pen) {
          r = new_penalty(pen);
          mem[cur_list.tail_field - mem_min].hh.rh = r;
          cur_list.tail_field = r;
        }
      }
      ++cur_line;
      cur_p = mem[cur_p - mem_min + 1].hh.lh;
      if (cur_p != (-1073741824)) {
        if (!post_disc_break) {
          r = mem_max - 3;
          while (true) {
            q = mem[r - mem_min].hh.rh;
            if (q == mem[cur_p - mem_min + 1].hh.rh)
              goto _L31;
            if (q >= hi_mem_min)
              goto _L31;
            if (mem[q - mem_min].hh.U2.b0 < 9)
              goto _L31;
            if (mem[q - mem_min].hh.U2.b0 == 11) {
              if (mem[q - mem_min].hh.U2.b1 != 1)
                goto _L31;
            }
            r = q;
          }
        _L31:
          if (r != (mem_max - 3)) {
            mem[r - mem_min].hh.rh = -1073741824;
            flush_node_list(mem[mem_max - mem_min - 3].hh.rh);
            mem[mem_max - mem_min - 3].hh.rh = q;
          }
        }
      }
    } while (cur_p != (-1073741824));
    if ((cur_line != best_line) ||
        (mem[mem_max - mem_min - 3].hh.rh != (-1073741824)))
      confusion(938);
    cur_list.pg_field = best_line - 1;
  }
  small_number reconstitute(small_number j, small_number n, halfword bchar,
                            halfword hchar) {
    halfword p, t = mem_max - 4;
    four_quarters q;
    halfword cur_rh, test_char;
    scaled w = 0;
    font_index k;
    hyphen_passed = 0;
    mem[mem_max - mem_min - 4].hh.rh = -1073741824;
    cur_l = hu[j];
    cur_q = t;
    if (!j) {
      ligature_present = init_lig;
      p = init_list;
      if (ligature_present)
        lft_hit = init_lft;
      while (p > (-1073741824)) {
        mem[t - mem_min].hh.rh = get_avail();
        t = mem[t - mem_min].hh.rh;
        mem[t - mem_min].hh.U2.b0 = hf;
        mem[t - mem_min].hh.U2.b1 = mem[p - mem_min].hh.U2.b1;
        p = mem[p - mem_min].hh.rh;
      }
    } else if (cur_l < 256) {
      mem[t - mem_min].hh.rh = get_avail();
      t = mem[t - mem_min].hh.rh;
      mem[t - mem_min].hh.U2.b0 = hf;
      mem[t - mem_min].hh.U2.b1 = cur_l;
    }
    lig_stack = -1073741824;
    if (j < n)
      cur_r = hu[j + 1];
    else
      cur_r = bchar;
    if (hyf[j] & 1)
      cur_rh = hchar;
    else
      cur_rh = 256;
  _L22:
    if (cur_l == 256) {
      k = bchar_label[hf];
      if (!k)
        goto _L30;
      q = font_info[k].qqqq;
    } else {
      q = font_info[char_base[hf] + cur_l].qqqq;
      if ((q.b2 & 3) != 1)
        goto _L30;
      k = lig_kern_base[hf] + q.b3;
      q = font_info[k].qqqq;
      if (q.b0 > 128) {
        k = lig_kern_base[hf] + (q.b2 * 256) + q.b3;
        q = font_info[k].qqqq;
      }
    }
    if (cur_rh < 256)
      test_char = cur_rh;
    else
      test_char = cur_r;
    while (true) {
      if (q.b1 == test_char) {
        if (q.b0 <= 128) {
          if (cur_rh < 256) {
            hyphen_passed = j;
            hchar = 256;
            cur_rh = 256;
            goto _L22;
          } else {
            if (hchar < 256) {
              if (hyf[j] & 1) {
                hyphen_passed = j;
                hchar = 256;
              }
            }
            if (q.b2 < 128) {
              if (cur_l == 256)
                lft_hit = true;
              if (j == n) {
                if (lig_stack == (-1073741824))
                  rt_hit = true;
              }
              if (interrupt)
                pause_for_instructions();
              switch (q.b2) {
              case 1:
              case 5:
                cur_l = q.b3;
                ligature_present = true;
                break;
              case 2:
              case 6:
                cur_r = q.b3;
                if (lig_stack > (-1073741824)) {
                  mem[lig_stack - mem_min].hh.U2.b1 = cur_r;
                } else {
                  lig_stack = new_lig_item(cur_r);
                  if (j == n) {
                    bchar = 256;
                  } else {
                    p = get_avail();
                    mem[lig_stack - mem_min + 1].hh.rh = p;
                    mem[p - mem_min].hh.U2.b1 = hu[j + 1];
                    mem[p - mem_min].hh.U2.b0 = hf;
                  }
                }
                break;
              case 3:
                cur_r = q.b3;
                p = lig_stack;
                lig_stack = new_lig_item(cur_r);
                mem[lig_stack - mem_min].hh.rh = p;
                break;
              case 7:
              case 11:
                if (ligature_present) {
                  p = new_ligature(hf, cur_l, mem[cur_q - mem_min].hh.rh);
                  if (lft_hit) {
                    mem[p - mem_min].hh.U2.b1 = 2;
                    lft_hit = false;
                  }
                  mem[cur_q - mem_min].hh.rh = p;
                  t = p;
                  ligature_present = false;
                }
                cur_q = t;
                cur_l = q.b3;
                ligature_present = true;
                break;
              default:
                cur_l = q.b3;
                ligature_present = true;
                if (lig_stack > (-1073741824)) {
                  if (mem[lig_stack - mem_min + 1].hh.rh > (-1073741824)) {
                    mem[t - mem_min].hh.rh = mem[lig_stack - mem_min + 1].hh.rh;
                    t = mem[t - mem_min].hh.rh;
                    ++j;
                  }
                  p = lig_stack;
                  lig_stack = mem[p - mem_min].hh.rh;
                  free_node(p, 2);
                  if (lig_stack == (-1073741824)) {
                    if (j < n)
                      cur_r = hu[j + 1];
                    else
                      cur_r = bchar;
                    if (hyf[j] & 1)
                      cur_rh = hchar;
                    else
                      cur_rh = 256;
                  } else {
                    cur_r = mem[lig_stack - mem_min].hh.U2.b1;
                  }
                } else if (j == n) {
                  goto _L30;
                } else {
                  mem[t - mem_min].hh.rh = get_avail();
                  t = mem[t - mem_min].hh.rh;
                  mem[t - mem_min].hh.U2.b0 = hf;
                  mem[t - mem_min].hh.U2.b1 = cur_r;
                  ++j;
                  if (j < n)
                    cur_r = hu[j + 1];
                  else
                    cur_r = bchar;
                  if (hyf[j] & 1)
                    cur_rh = hchar;
                  else
                    cur_rh = 256;
                }
                break;
              }
              if (q.b2 > 4) {
                if (q.b2 != 7)
                  goto _L30;
              }
              goto _L22;
            }
            w = font_info[kern_base[hf] + (q.b2 * 256) + q.b3].int_;
            goto _L30;
          }
        }
      }
      if (q.b0 >= 128) {
        if (cur_rh == 256) {
          goto _L30;
        } else {
          cur_rh = 256;
          goto _L22;
        }
      }
      k += q.b0 + 1;
      q = font_info[k].qqqq;
    }
  _L30:
    if (ligature_present) {
      p = new_ligature(hf, cur_l, mem[cur_q - mem_min].hh.rh);
      if (lft_hit) {
        mem[p - mem_min].hh.U2.b1 = 2;
        lft_hit = false;
      }
      if (rt_hit) {
        if (lig_stack == (-1073741824)) {
          ++mem[p - mem_min].hh.U2.b1;
          rt_hit = false;
        }
      }
      mem[cur_q - mem_min].hh.rh = p;
      t = p;
      ligature_present = false;
    }
    if (w) {
      mem[t - mem_min].hh.rh = new_kern(w);
      t = mem[t - mem_min].hh.rh;
      w = 0;
    }
    if (lig_stack <= (-1073741824))
      return j;
    cur_q = t;
    cur_l = mem[lig_stack - mem_min].hh.U2.b1;
    ligature_present = true;
    if (mem[lig_stack - mem_min + 1].hh.rh > (-1073741824)) {
      mem[t - mem_min].hh.rh = mem[lig_stack - mem_min + 1].hh.rh;
      t = mem[t - mem_min].hh.rh;
      ++j;
    }
    p = lig_stack;
    lig_stack = mem[p - mem_min].hh.rh;
    free_node(p, 2);
    if (lig_stack == (-1073741824)) {
      if (j < n)
        cur_r = hu[j + 1];
      else
        cur_r = bchar;
      if (hyf[j] & 1)
        cur_rh = hchar;
      else
        cur_rh = 256;
    } else {
      cur_r = mem[lig_stack - mem_min].hh.U2.b1;
    }
    goto _L22;
  }
  void hyphenate() {
    char i, j, l;
    halfword q, r, s, bchar, major_tail, minor_tail;
    ASCII_code c;
    char c_loc;
    integer r_count, v;
    halfword hyf_node;
    trie_pointer z;
    hyph_pointer h;
    str_number k;
    pool_pointer u;
    char N;
    for (N = hn, j = 0; j <= N; ++j)
      hyf[j] = 0;
    h = hc[1];
    ++hn;
    hc[hn] = cur_lang;
    for (N = hn, j = 2; j <= N; ++j)
      h = (h + h + hc[j]) % 307;
    while (true) {
      k = hyph_word[h];
      if (!k)
        goto _L45;
      if (str_start[k + 1] - str_start[k] < hn)
        goto _L45;
      if (str_start[k + 1] - str_start[k] == hn) {
        j = 1;
        u = str_start[k];
        do {
          if (str_pool[u] < hc[j])
            goto _L45;
          if (str_pool[u] > hc[j])
            goto _L30;
          ++j;
          ++u;
        } while (j <= hn);
        s = hyph_list[h];
        while (s != (-1073741824)) {
          hyf[mem[s - mem_min].hh.lh] = 1;
          s = mem[s - mem_min].hh.rh;
        }
        --hn;
        goto _L40;
      }
    _L30:
      if (h > 0)
        --h;
      else
        h = 307;
    }
  _L45:
    --hn;
    if (trie[cur_lang + 1].U2.b1 != cur_lang)
      goto _L10;
    hc[0] = 0;
    hc[hn + 1] = 0;
    hc[hn + 2] = 256;
    for (N = hn - r_hyf + 1, j = 0; j <= N; ++j) {
      z = trie[cur_lang + 1].rh + hc[j];
      l = j;
      while (hc[l] == trie[z].U2.b1) {
        if (trie[z].U2.b0) {
          v = trie[z].U2.b0;
          do {
            v += op_start[cur_lang];
            i = l - hyf_distance[v];
            if (hyf_num[v] > hyf[i])
              hyf[i] = hyf_num[v];
            v = hyf_next[v];
          } while (v);
        }
        ++l;
        z = trie[z].rh + hc[l];
      }
    }
  _L40:
    for (N = l_hyf, j = 0; j <= (N - 1); ++j)
      hyf[j] = 0;
    for (N = r_hyf, j = 0; j <= (N - 1); ++j)
      hyf[hn - j] = 0;
    for (N = hn - r_hyf, j = l_hyf; j <= N; ++j) {
      if (hyf[j] & 1)
        goto _L41;
    }
    goto _L10;
  _L41:
    q = mem[hb - mem_min].hh.rh;
    mem[hb - mem_min].hh.rh = -1073741824;
    r = mem[ha - mem_min].hh.rh;
    mem[ha - mem_min].hh.rh = -1073741824;
    bchar = hyf_bchar;
    if (ha >= hi_mem_min) {
      if (mem[ha - mem_min].hh.U2.b0 != hf)
        goto _L42;
      init_list = ha;
      init_lig = false;
      hu[0] = mem[ha - mem_min].hh.U2.b1;
    } else if (mem[ha - mem_min].hh.U2.b0 == 6) {
      if (mem[ha - mem_min + 1].hh.U2.b0 != hf)
        goto _L42;
      init_list = mem[ha - mem_min + 1].hh.rh;
      init_lig = true;
      init_lft = (mem[ha - mem_min].hh.U2.b1 > 1);
      hu[0] = mem[ha - mem_min + 1].hh.U2.b1;
      if (init_list == (-1073741824)) {
        if (init_lft) {
          hu[0] = 256;
          init_lig = false;
        }
      }
      free_node(ha, 2);
    } else {
      if (r < hi_mem_min) {
        if (mem[r - mem_min].hh.U2.b0 == 6) {
          if (mem[r - mem_min].hh.U2.b1 > 1)
            goto _L42;
        }
      }
      j = 1;
      s = ha;
      init_list = -1073741824;
      goto _L50;
    }
    s = cur_p;
    while (mem[s - mem_min].hh.rh != ha)
      s = mem[s - mem_min].hh.rh;
    j = 0;
    goto _L50;
  _L42:
    s = ha;
    j = 0;
    hu[0] = 256;
    init_lig = false;
    init_list = -1073741824;
  _L50:
    flush_node_list(r);
    do {
      l = j;
      j = reconstitute(j, hn, bchar, hyf_char) + 1;
      if (!hyphen_passed) {
        mem[s - mem_min].hh.rh = mem[mem_max - mem_min - 4].hh.rh;
        while (mem[s - mem_min].hh.rh > (-1073741824))
          s = mem[s - mem_min].hh.rh;
        if (hyf[j - 1] & 1) {
          l = j;
          hyphen_passed = j - 1;
          mem[mem_max - mem_min - 4].hh.rh = -1073741824;
        }
      }
      if (hyphen_passed > 0) {
        do {
          r = get_node(2);
          mem[r - mem_min].hh.rh = mem[mem_max - mem_min - 4].hh.rh;
          mem[r - mem_min].hh.U2.b0 = 7;
          major_tail = r;
          r_count = 0;
          while (mem[major_tail - mem_min].hh.rh > (-1073741824)) {
            major_tail = mem[major_tail - mem_min].hh.rh;
            ++r_count;
          }
          i = hyphen_passed;
          hyf[i] = 0;
          minor_tail = -1073741824;
          mem[r - mem_min + 1].hh.lh = -1073741824;
          hyf_node = new_character(hf, hyf_char);
          if (hyf_node != (-1073741824)) {
            ++i;
            c = hu[i];
            hu[i] = hyf_char;
            mem[hyf_node - mem_min].hh.rh = avail;
            avail = hyf_node;
          }
          while (l <= i) {
            l = reconstitute(l, i, font_bchar[hf], 256) + 1;
            if (mem[mem_max - mem_min - 4].hh.rh <= (-1073741824))
              continue;
            if (minor_tail == (-1073741824))
              mem[r - mem_min + 1].hh.lh = mem[mem_max - mem_min - 4].hh.rh;
            else
              mem[minor_tail - mem_min].hh.rh =
                  mem[mem_max - mem_min - 4].hh.rh;
            minor_tail = mem[mem_max - mem_min - 4].hh.rh;
            while (mem[minor_tail - mem_min].hh.rh > (-1073741824))
              minor_tail = mem[minor_tail - mem_min].hh.rh;
          }
          if (hyf_node != (-1073741824)) {
            hu[i] = c;
            l = i;
            --i;
          }
          minor_tail = -1073741824;
          mem[r - mem_min + 1].hh.rh = -1073741824;
          c_loc = 0;
          if (bchar_label[hf]) {
            --l;
            c = hu[l];
            c_loc = l;
            hu[l] = 256;
          }
          while (l < j) {
            do {
              l = reconstitute(l, hn, bchar, 256) + 1;
              if (c_loc > 0) {
                hu[c_loc] = c;
                c_loc = 0;
              }
              if (mem[mem_max - mem_min - 4].hh.rh > (-1073741824)) {
                if (minor_tail == (-1073741824))
                  mem[r - mem_min + 1].hh.rh = mem[mem_max - mem_min - 4].hh.rh;
                else
                  mem[minor_tail - mem_min].hh.rh =
                      mem[mem_max - mem_min - 4].hh.rh;
                minor_tail = mem[mem_max - mem_min - 4].hh.rh;
                while (mem[minor_tail - mem_min].hh.rh > (-1073741824))
                  minor_tail = mem[minor_tail - mem_min].hh.rh;
              }
            } while (l < j);
            while (l > j) {
              j = reconstitute(j, hn, bchar, 256) + 1;
              mem[major_tail - mem_min].hh.rh =
                  mem[mem_max - mem_min - 4].hh.rh;
              while (mem[major_tail - mem_min].hh.rh > (-1073741824)) {
                major_tail = mem[major_tail - mem_min].hh.rh;
                ++r_count;
              }
            }
          }
          if (r_count > 127) {
            mem[s - mem_min].hh.rh = mem[r - mem_min].hh.rh;
            mem[r - mem_min].hh.rh = -1073741824;
            flush_node_list(r);
          } else {
            mem[s - mem_min].hh.rh = r;
            mem[r - mem_min].hh.U2.b1 = r_count;
          }
          s = major_tail;
          hyphen_passed = j - 1;
          mem[mem_max - mem_min - 4].hh.rh = -1073741824;
        } while (hyf[j - 1] & 1);
      }
    } while (j <= hn);
    mem[s - mem_min].hh.rh = q;
    flush_list(init_list);
  _L10:;
  }
  quarterword new_trie_op(small_number d, small_number n, quarterword v) {
    quarterword result, u;
    int l;
    int h = (abs(n + (d * 313) + (v * 361) + (cur_lang * 1009)) %
             (trie_op_size + trie_op_size)) -
            trie_op_size;
    while (true) {
      l = trie_op_hash[h + trie_op_size];
      if (!l) {
        if (trie_op_ptr == trie_op_size)
          overflow(948, trie_op_size);
        u = trie_used[cur_lang];
        if (u == 65535)
          overflow(949, 65535);
        ++trie_op_ptr;
        ++u;
        trie_used[cur_lang] = u;
        hyf_distance[trie_op_ptr] = d;
        hyf_num[trie_op_ptr] = n;
        hyf_next[trie_op_ptr] = v;
        trie_op_lang[trie_op_ptr] = cur_lang;
        trie_op_hash[h + trie_op_size] = trie_op_ptr;
        trie_op_val[trie_op_ptr] = u;
        result = u;
        goto _L10;
      }
      if ((hyf_distance[l] == d) && (hyf_num[l] == n) && (hyf_next[l] == v) &&
          (trie_op_lang[l] == cur_lang)) {
        result = trie_op_val[l];
        goto _L10;
      }
      if (h > (-trie_op_size))
        --h;
      else
        h = trie_op_size;
    }
  _L10:
    return result;
  }
  trie_pointer trie_node(trie_pointer p) {
    trie_pointer result, q;
    trie_pointer h = abs(trie_c[p] + (trie_o[p] * 1009) + (trie_l[p] * 2718) +
                         (trie_r[p] * 3142)) %
                     trie_size;
    while (true) {
      q = trie_hash[h];
      if (!q) {
        trie_hash[h] = p;
        result = p;
        goto _L10;
      }
      if ((trie_c[q] == trie_c[p]) && (trie_o[q] == trie_o[p]) &&
          (trie_l[q] == trie_l[p]) && (trie_r[q] == trie_r[p])) {
        result = q;
        goto _L10;
      }
      if (h > 0)
        --h;
      else
        h = trie_size;
    }
  _L10:
    return result;
  }
  trie_pointer compress_trie(trie_pointer p) {
    if (!p) {
      return 0;
    } else {
      trie_l[p] = compress_trie(trie_l[p]);
      trie_r[p] = compress_trie(trie_r[p]);
      return trie_node(p);
    }
  }
  void first_fit(trie_pointer p) {
    trie_pointer h, q, l, r;
    short ll;
    ASCII_code c = trie_c[p];
    trie_pointer z = trie_min[c];
    while (true) {
      h = z - c;
      if (trie_max < (h + 256)) {
        if (trie_size <= (h + 256))
          overflow(950, trie_size);
        do {
          ++trie_max;
          trie_taken[trie_max - 1] = 0;
          trie[trie_max].rh = trie_max + 1;
          trie[trie_max].lh = trie_max - 1;
        } while (trie_max != (h + 256));
      }
      if (trie_taken[h - 1])
        goto _L45;
      q = trie_r[p];
      while (q > 0) {
        if (!trie[h + trie_c[q]].rh)
          goto _L45;
        q = trie_r[q];
      }
      goto _L40;
    _L45:
      z = trie[z].rh;
    }
  _L40:
    trie_taken[h - 1] = 1;
    trie_hash[p] = h;
    q = p;
    do {
      z = h + trie_c[q];
      l = trie[z].lh;
      r = trie[z].rh;
      trie[r].lh = l;
      trie[l].rh = r;
      trie[z].rh = 0;
      if (l < 256) {
        if (z < 256)
          ll = z;
        else
          ll = 256;
        do {
          trie_min[l] = r;
          ++l;
        } while (l != ll);
      }
      q = trie_r[q];
    } while (q);
  }
  void trie_pack(trie_pointer p) {
    trie_pointer q;
    do {
      q = trie_l[p];
      if ((q > 0) && (!trie_hash[q])) {
        first_fit(q);
        trie_pack(q);
      }
      p = trie_r[p];
    } while (p);
  }
  void trie_fix(trie_pointer p) {
    trie_pointer q;
    ASCII_code c;
    trie_pointer z = trie_hash[p];
    do {
      q = trie_l[p];
      c = trie_c[p];
      trie[z + c].rh = trie_hash[q];
      trie[z + c].U2.b1 = c;
      trie[z + c].U2.b0 = trie_o[p];
      if (q > 0)
        trie_fix(q);
      p = trie_r[p];
    } while (p);
  }
  void new_patterns() {
    char k, l;
    bool digit_sensed;
    quarterword v;
    trie_pointer p, q;
    bool first_child;
    ASCII_code c;
    if (trie_not_ready) {
      if (eqtb[12213].int_ <= 0) {
        cur_lang = 0;
      } else if (eqtb[12213].int_ > 255)
        cur_lang = 0;
      else
        cur_lang = eqtb[12213].int_;
      scan_left_brace();
      k = 0;
      hyf[0] = 0;
      digit_sensed = false;
      while (true) {
        get_x_token();
        switch (cur_cmd) {
        case 11:
        case 12:
          if (digit_sensed || (cur_chr < 48) || (cur_chr > 57)) {
            if (cur_chr == 46) {
              cur_chr = 0;
            } else {
              cur_chr = eqtb[cur_chr + 11139].hh.rh;
              if (!cur_chr) {
                print_nl(262);
                print(956);
                help_ptr = 1;
                help_line[0] = 955;
                error();
              }
            }
            if (k < 63) {
              ++k;
              hc[k] = cur_chr;
              hyf[k] = 0;
              digit_sensed = false;
            }
          } else if (k < 63) {
            hyf[k] = cur_chr - 48;
            digit_sensed = true;
          }
          break;
        case 10:
        case 2:
          if (k > 0) {
            if (!hc[1])
              hyf[0] = 0;
            if (!hc[k])
              hyf[k] = 0;
            l = k;
            v = 0;
            while (true) {
              if (hyf[l])
                v = new_trie_op(k - l, hyf[l], v);
              if (l <= 0)
                goto _L31;
              --l;
            }
          _L31:
            q = 0;
            hc[0] = cur_lang;
            while (l <= k) {
              c = hc[l];
              ++l;
              p = trie_l[q];
              first_child = true;
              while ((p > 0) && (c > trie_c[p])) {
                q = p;
                p = trie_r[q];
                first_child = false;
              }
              if ((!p) || (c < trie_c[p])) {
                if (trie_ptr == trie_size)
                  overflow(950, trie_size);
                ++trie_ptr;
                trie_r[trie_ptr] = p;
                p = trie_ptr;
                trie_l[p] = 0;
                if (first_child)
                  trie_l[q] = p;
                else
                  trie_r[q] = p;
                trie_c[p] = c;
                trie_o[p] = 0;
              }
              q = p;
            }
            if (trie_o[q]) {
              print_nl(262);
              print(957);
              help_ptr = 1;
              help_line[0] = 955;
              error();
            }
            trie_o[q] = v;
          }
          if (cur_cmd == 2)
            goto _L30;
          k = 0;
          hyf[0] = 0;
          digit_sensed = false;
          break;
        default:
          print_nl(262);
          print(954);
          print_esc(952);
          help_ptr = 1;
          help_line[0] = 955;
          error();
          break;
        }
      }
    _L30:
      return;
    }
    print_nl(262);
    print(951);
    print_esc(952);
    help_ptr = 1;
    help_line[0] = 953;
    error();
    mem[mem_max - mem_min - 12].hh.rh = scan_toks(false, false);
    flush_list(def_ref);
  }
  void init_trie() {
    trie_pointer p, r, s;
    integer j, k, t;
    two_halves h;
    int N;
    trie_pointer N1;
    op_start[0] = 0;
    for (j = 1; j <= 255; ++j)
      op_start[j] = op_start[j - 1] + trie_used[j - 1];
    for (N = trie_op_ptr, j = 1; j <= N; ++j)
      trie_op_hash[j + trie_op_size] =
          op_start[trie_op_lang[j]] + trie_op_val[j];
    for (N = trie_op_ptr, j = 1; j <= N; ++j) {
      while (trie_op_hash[j + trie_op_size] > j) {
        k = trie_op_hash[j + trie_op_size];
        t = hyf_distance[k];
        hyf_distance[k] = hyf_distance[j];
        hyf_distance[j] = t;
        t = hyf_num[k];
        hyf_num[k] = hyf_num[j];
        hyf_num[j] = t;
        t = hyf_next[k];
        hyf_next[k] = hyf_next[j];
        hyf_next[j] = t;
        trie_op_hash[j + trie_op_size] = trie_op_hash[k + trie_op_size];
        trie_op_hash[k + trie_op_size] = k;
      }
    }
    for (p = 0; p <= trie_size; ++p)
      trie_hash[p] = 0;
    trie_l[0] = compress_trie(trie_l[0]);
    for (N1 = trie_ptr, p = 0; p <= N1; ++p)
      trie_hash[p] = 0;
    for (p = 0; p <= 255; ++p)
      trie_min[p] = p + 1;
    trie[0].rh = 1;
    trie_max = 0;
    if (trie_l[0]) {
      first_fit(trie_l[0]);
      trie_pack(trie_l[0]);
    }
    h.rh = 0;
    h.U2.b0 = 0;
    h.U2.b1 = 0;
    if (!trie_l[0]) {
      for (r = 0; r <= 256; ++r)
        trie[r] = h;
      trie_max = 256;
    } else {
      trie_fix(trie_l[0]);
      r = 0;
      do {
        s = trie[r].rh;
        trie[r] = h;
        r = s;
      } while (r <= trie_max);
    }
    trie[0].U2.b1 = 63;
    trie_not_ready = false;
  }
  void line_break(integer final_widow_penalty) {
    bool auto_breaking;
    halfword prev_p, q, r, s, prev_s;
    internal_font_number f;
    small_number j;
    uint8_t c;
    pack_begin_line = cur_list.ml_field;
    mem[mem_max - mem_min - 3].hh.rh = mem[cur_list.head_field - mem_min].hh.rh;
    if (cur_list.tail_field >= hi_mem_min) {
      mem[cur_list.tail_field - mem_min].hh.rh = new_penalty(10000);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    } else if (mem[cur_list.tail_field - mem_min].hh.U2.b0 != 10) {
      mem[cur_list.tail_field - mem_min].hh.rh = new_penalty(10000);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    } else {
      mem[cur_list.tail_field - mem_min].hh.U2.b0 = 12;
      delete_glue_ref(mem[cur_list.tail_field - mem_min + 1].hh.lh);
      flush_node_list(mem[cur_list.tail_field - mem_min + 1].hh.rh);
      mem[cur_list.tail_field - mem_min + 1].int_ = 10000;
    }
    mem[cur_list.tail_field - mem_min].hh.rh = new_param_glue(14);
    init_cur_lang = cur_list.pg_field & 65535;
    init_l_hyf = cur_list.pg_field / 4194304;
    init_r_hyf = (cur_list.pg_field / 65536) & 63;
    pop_nest();
    no_shrink_error_yet = true;
    if (mem[eqtb[9789].hh.rh - mem_min].hh.U2.b1 &&
        mem[eqtb[9789].hh.rh - mem_min + 3].int_)
      eqtb[9789].hh.rh = finite_shrink(eqtb[9789].hh.rh);
    if (mem[eqtb[9790].hh.rh - mem_min].hh.U2.b1 &&
        mem[eqtb[9790].hh.rh - mem_min + 3].int_)
      eqtb[9790].hh.rh = finite_shrink(eqtb[9790].hh.rh);
    q = eqtb[9789].hh.rh;
    r = eqtb[9790].hh.rh;
    background[1] = mem[q - mem_min + 1].int_ + mem[r - mem_min + 1].int_;
    background[2] = 0;
    background[3] = 0;
    background[4] = 0;
    background[5] = 0;
    background[mem[q - mem_min].hh.U2.b0 + 2] = mem[q - mem_min + 2].int_;
    background[mem[r - mem_min].hh.U2.b0 + 2] += mem[r - mem_min + 2].int_;
    background[6] = mem[q - mem_min + 3].int_ + mem[r - mem_min + 3].int_;
    minimum_demerits = 1073741823;
    minimal_demerits[3] = 1073741823;
    minimal_demerits[2] = 1073741823;
    minimal_demerits[1] = 1073741823;
    minimal_demerits[0] = 1073741823;
    if (eqtb[10312].hh.rh == (-1073741824)) {
      if (!eqtb[12747].int_) {
        last_special_line = 0;
        second_width = eqtb[12733].int_;
        second_indent = 0;
      } else {
        last_special_line = abs(eqtb[12204].int_);
        if (eqtb[12204].int_ < 0) {
          first_width = eqtb[12733].int_ - abs(eqtb[12747].int_);
          if (eqtb[12747].int_ >= 0)
            first_indent = eqtb[12747].int_;
          else
            first_indent = 0;
          second_width = eqtb[12733].int_;
          second_indent = 0;
        } else {
          first_width = eqtb[12733].int_;
          first_indent = 0;
          second_width = eqtb[12733].int_ - abs(eqtb[12747].int_);
          if (eqtb[12747].int_ >= 0)
            second_indent = eqtb[12747].int_;
          else
            second_indent = 0;
        }
      }
    } else {
      last_special_line = mem[eqtb[10312].hh.rh - mem_min].hh.lh - 1;
      second_width =
          mem[eqtb[10312].hh.rh + ((last_special_line + 1) * 2) - mem_min].int_;
      second_indent =
          mem[eqtb[10312].hh.rh + (last_special_line * 2) - mem_min + 1].int_;
    }
    if (!eqtb[12182].int_)
      easy_line = last_special_line;
    else
      easy_line = 1073741824;
    threshold = eqtb[12163].int_;
    if (threshold >= 0) {
      second_pass = false;
      final_pass = false;
    } else {
      threshold = eqtb[12164].int_;
      second_pass = true;
      final_pass = (eqtb[12750].int_ <= 0);
    }
    while (true) {
      if (threshold > 10000)
        threshold = 10000;
      if (second_pass) {
        if (trie_not_ready)
          init_trie();
        cur_lang = init_cur_lang;
        l_hyf = init_l_hyf;
        r_hyf = init_r_hyf;
      }
      q = get_node(3);
      mem[q - mem_min].hh.U2.b0 = 0;
      mem[q - mem_min].hh.U2.b1 = 2;
      mem[q - mem_min].hh.rh = mem_max - 7;
      mem[q - mem_min + 1].hh.rh = -1073741824;
      mem[q - mem_min + 1].hh.lh = cur_list.pg_field + 1;
      mem[q - mem_min + 2].int_ = 0;
      mem[mem_max - mem_min - 7].hh.rh = q;
      active_width[1] = background[1];
      active_width[2] = background[2];
      active_width[3] = background[3];
      active_width[4] = background[4];
      active_width[5] = background[5];
      active_width[6] = background[6];
      passive = -1073741824;
      printed_node = mem_max - 3;
      pass_number = 0;
      font_in_short_display = 0;
      cur_p = mem[mem_max - mem_min - 3].hh.rh;
      auto_breaking = true;
      prev_p = cur_p;
      while ((cur_p != (-1073741824)) &&
             (mem[mem_max - mem_min - 7].hh.rh != (mem_max - 7))) {
        if (cur_p >= hi_mem_min) {
          prev_p = cur_p;
          do {
            f = mem[cur_p - mem_min].hh.U2.b0;
            (active_width[1] +=
             (font_info[(width_base[f] +
                         ((font_info[char_base[f] +
                                     mem[cur_p - mem_min].hh.U2.b1]
                               .qqqq)
                              .b0))]
                  .int_));
            cur_p = mem[cur_p - mem_min].hh.rh;
          } while (cur_p >= hi_mem_min);
        }
        switch (mem[cur_p - mem_min].hh.U2.b0) {
        case 0:
        case 1:
        case 2:
          active_width[1] += mem[cur_p - mem_min + 1].int_;
          break;
        case 8:
          if (mem[cur_p - mem_min].hh.U2.b1 == 4) {
            cur_lang = mem[cur_p - mem_min + 1].hh.rh;
            l_hyf = mem[cur_p - mem_min + 1].hh.U2.b0;
            r_hyf = mem[cur_p - mem_min + 1].hh.U2.b1;
          }
          break;
        case 10:
          if (auto_breaking) {
            if (prev_p >= hi_mem_min) {
              try_break(0, 0);
            } else if (mem[prev_p - mem_min].hh.U2.b0 < 9) {
              try_break(0, 0);
            } else if ((mem[prev_p - mem_min].hh.U2.b0 == 11) &&
                       (mem[prev_p - mem_min].hh.U2.b1 != 1))
              try_break(0, 0);
          }
          if (mem[mem[cur_p - mem_min + 1].hh.lh - mem_min].hh.U2.b1 &&
              mem[mem[cur_p - mem_min + 1].hh.lh - mem_min + 3].int_)
            mem[cur_p - mem_min + 1].hh.lh =
                finite_shrink(mem[cur_p - mem_min + 1].hh.lh);
          q = mem[cur_p - mem_min + 1].hh.lh;
          active_width[1] += mem[q - mem_min + 1].int_;
          active_width[mem[q - mem_min].hh.U2.b0 + 2] +=
              mem[q - mem_min + 2].int_;
          active_width[6] += mem[q - mem_min + 3].int_;
          if (second_pass && auto_breaking) {
            prev_s = cur_p;
            s = mem[prev_s - mem_min].hh.rh;
            if (s != (-1073741824)) {
              while (true) {
                if (s >= hi_mem_min) {
                  c = mem[s - mem_min].hh.U2.b1;
                  hf = mem[s - mem_min].hh.U2.b0;
                } else if (mem[s - mem_min].hh.U2.b0 == 6) {
                  if (mem[s - mem_min + 1].hh.rh == (-1073741824))
                    goto _L22;
                  q = mem[s - mem_min + 1].hh.rh;
                  c = mem[q - mem_min].hh.U2.b1;
                  hf = mem[q - mem_min].hh.U2.b0;
                } else if ((mem[s - mem_min].hh.U2.b0 == 11) &&
                           (!mem[s - mem_min].hh.U2.b1)) {
                  goto _L22;
                } else if (mem[s - mem_min].hh.U2.b0 == 8) {
                  if (mem[s - mem_min].hh.U2.b1 == 4) {
                    cur_lang = mem[s - mem_min + 1].hh.rh;
                    l_hyf = mem[s - mem_min + 1].hh.U2.b0;
                    r_hyf = mem[s - mem_min + 1].hh.U2.b1;
                  }
                  goto _L22;
                } else {
                  goto _L31;
                }
                if (eqtb[c + 11139].hh.rh) {
                  if ((eqtb[c + 11139].hh.rh == c) || (eqtb[12201].int_ > 0))
                    goto _L32;
                  else
                    goto _L31;
                }
              _L22:
                prev_s = s;
                s = mem[prev_s - mem_min].hh.rh;
              }
            _L32:
              hyf_char = hyphen_char[hf];
              if (hyf_char < 0)
                goto _L31;
              if (hyf_char > 255)
                goto _L31;
              ha = prev_s;
              if (l_hyf + r_hyf > 63)
                goto _L31;
              hn = 0;
              while (true) {
                if (s >= hi_mem_min) {
                  if (mem[s - mem_min].hh.U2.b0 != hf)
                    goto _L33;
                  hyf_bchar = mem[s - mem_min].hh.U2.b1;
                  c = hyf_bchar;
                  if (!eqtb[c + 11139].hh.rh)
                    goto _L33;
                  if (hn == 63)
                    goto _L33;
                  hb = s;
                  ++hn;
                  hu[hn] = c;
                  hc[hn] = eqtb[c + 11139].hh.rh;
                  hyf_bchar = 256;
                } else if (mem[s - mem_min].hh.U2.b0 == 6) {
                  if (mem[s - mem_min + 1].hh.U2.b0 != hf)
                    goto _L33;
                  j = hn;
                  q = mem[s - mem_min + 1].hh.rh;
                  if (q > (-1073741824))
                    hyf_bchar = mem[q - mem_min].hh.U2.b1;
                  while (q > (-1073741824)) {
                    c = mem[q - mem_min].hh.U2.b1;
                    if (!eqtb[c + 11139].hh.rh)
                      goto _L33;
                    if (j == 63)
                      goto _L33;
                    ++j;
                    hu[j] = c;
                    hc[j] = eqtb[c + 11139].hh.rh;
                    q = mem[q - mem_min].hh.rh;
                  }
                  hb = s;
                  hn = j;
                  if (mem[s - mem_min].hh.U2.b1 & 1)
                    hyf_bchar = font_bchar[hf];
                  else
                    hyf_bchar = 256;
                } else if ((mem[s - mem_min].hh.U2.b0 == 11) &&
                           (!mem[s - mem_min].hh.U2.b1)) {
                  hb = s;
                  hyf_bchar = font_bchar[hf];
                } else {
                  goto _L33;
                }
                s = mem[s - mem_min].hh.rh;
              }
            _L33:
              if (hn < (l_hyf + r_hyf))
                goto _L31;
              while (true) {
                if (s < hi_mem_min) {
                  switch (mem[s - mem_min].hh.U2.b0) {
                  case 6:
                    // blank case
                    break;
                  case 11:
                    if (mem[s - mem_min].hh.U2.b1)
                      goto _L34;
                    break;
                  case 8:
                  case 10:
                  case 12:
                  case 3:
                  case 5:
                  case 4:
                    goto _L34;
                    break;
                  default:
                    goto _L31;
                    break;
                  }
                }
                s = mem[s - mem_min].hh.rh;
              }
            _L34:
              hyphenate();
            }
          _L31:;
          }
          break;
        case 11:
          if (mem[cur_p - mem_min].hh.U2.b1 == 1) {
            if ((mem[cur_p - mem_min].hh.rh < hi_mem_min) && auto_breaking) {
              if (mem[mem[cur_p - mem_min].hh.rh - mem_min].hh.U2.b0 == 10)
                try_break(0, 0);
            }
            active_width[1] += mem[cur_p - mem_min + 1].int_;
          } else {
            active_width[1] += mem[cur_p - mem_min + 1].int_;
          }
          break;
        case 6:
          f = mem[cur_p - mem_min + 1].hh.U2.b0;
          (active_width[1] +=
           (font_info[(width_base[f] +
                       ((font_info[char_base[f] +
                                   mem[cur_p - mem_min + 1].hh.U2.b1]
                             .qqqq)
                            .b0))]
                .int_));
          break;
        case 7:
          s = mem[cur_p - mem_min + 1].hh.lh;
          disc_width = 0;
          if (s == (-1073741824)) {
            try_break(eqtb[12167].int_, 1);
          } else {
            do {
              if (s >= hi_mem_min) {
                f = mem[s - mem_min].hh.U2.b0;
                (disc_width += (font_info[(width_base[f] +
                                           (font_info[char_base[f] +
                                                      mem[s - mem_min].hh.U2.b1]
                                                .qqqq.b0))]
                                    .int_));
              } else {
                switch (mem[s - mem_min].hh.U2.b0) {
                case 6:
                  f = mem[s - mem_min + 1].hh.U2.b0;
                  (disc_width +=
                   (font_info[(width_base[f] +
                               ((font_info[(char_base[f] +
                                            (mem[s - mem_min + 1].hh.U2.b1))]
                                     .qqqq)
                                    .b0))]
                        .int_));
                  break;
                case 0:
                case 1:
                case 2:
                case 11:
                  disc_width += mem[s - mem_min + 1].int_;
                  break;
                default:
                  confusion(936);
                  break;
                }
              }
              s = mem[s - mem_min].hh.rh;
            } while (s != (-1073741824));
            active_width[1] += disc_width;
            try_break(eqtb[12166].int_, 1);
            active_width[1] -= disc_width;
          }
          r = mem[cur_p - mem_min].hh.U2.b1;
          s = mem[cur_p - mem_min].hh.rh;
          while (r > 0) {
            if (s >= hi_mem_min) {
              f = mem[s - mem_min].hh.U2.b0;
              (active_width[1] +=
               (font_info[(width_base[f] +
                           ((font_info[char_base[f] + mem[s - mem_min].hh.U2.b1]
                                 .qqqq)
                                .b0))]
                    .int_));
            } else {
              switch (mem[s - mem_min].hh.U2.b0) {
              case 6:
                f = mem[s - mem_min + 1].hh.U2.b0;
                (active_width[1] +=
                 (font_info[(width_base[f] +
                             ((font_info[(char_base[f] +
                                          (mem[s - mem_min + 1].hh.U2.b1))]
                                   .qqqq)
                                  .b0))]
                      .int_));
                break;
              case 0:
              case 1:
              case 2:
              case 11:
                active_width[1] += mem[s - mem_min + 1].int_;
                break;
              default:
                confusion(937);
                break;
              }
            }
            --r;
            s = mem[s - mem_min].hh.rh;
          }
          prev_p = cur_p;
          cur_p = s;
          goto _L35;
          break;
        case 9:
          auto_breaking = (mem[cur_p - mem_min].hh.U2.b1 == 1);
          if ((mem[cur_p - mem_min].hh.rh < hi_mem_min) && auto_breaking) {
            if (mem[mem[cur_p - mem_min].hh.rh - mem_min].hh.U2.b0 == 10)
              try_break(0, 0);
          }
          active_width[1] += mem[cur_p - mem_min + 1].int_;
          break;
        case 12:
          try_break(mem[cur_p - mem_min + 1].int_, 0);
          break;
        case 4:
        case 3:
        case 5:
          // blank case
          break;
        default:
          confusion(935);
          break;
        }
        prev_p = cur_p;
        cur_p = mem[cur_p - mem_min].hh.rh;
      _L35:;
      }
      if (cur_p == (-1073741824)) {
        try_break(-10000, 1);
        if (mem[mem_max - mem_min - 7].hh.rh != (mem_max - 7)) {
          r = mem[mem_max - mem_min - 7].hh.rh;
          fewest_demerits = 1073741823;
          do {
            if (mem[r - mem_min].hh.U2.b0 != 2) {
              if (mem[r - mem_min + 2].int_ < fewest_demerits) {
                fewest_demerits = mem[r - mem_min + 2].int_;
                best_bet = r;
              }
            }
            r = mem[r - mem_min].hh.rh;
          } while (r != (mem_max - 7));
          best_line = mem[best_bet - mem_min + 1].hh.lh;
          if (!eqtb[12182].int_)
            goto _L30;
          r = mem[mem_max - mem_min - 7].hh.rh;
          actual_looseness = 0;
          do {
            if (mem[r - mem_min].hh.U2.b0 != 2) {
              line_diff = mem[r - mem_min + 1].hh.lh - best_line;
              if (((line_diff < actual_looseness) &&
                   (eqtb[12182].int_ <= line_diff)) ||
                  ((line_diff > actual_looseness) &&
                   (eqtb[12182].int_ >= line_diff))) {
                best_bet = r;
                actual_looseness = line_diff;
                fewest_demerits = mem[r - mem_min + 2].int_;
              } else if ((line_diff == actual_looseness) &&
                         (mem[r - mem_min + 2].int_ < fewest_demerits)) {
                best_bet = r;
                fewest_demerits = mem[r - mem_min + 2].int_;
              }
            }
            r = mem[r - mem_min].hh.rh;
          } while (r != (mem_max - 7));
          best_line = mem[best_bet - mem_min + 1].hh.lh;
          if ((actual_looseness == eqtb[12182].int_) || final_pass)
            goto _L30;
        }
      }
      q = mem[mem_max - mem_min - 7].hh.rh;
      while (q != (mem_max - 7)) {
        cur_p = mem[q - mem_min].hh.rh;
        if (mem[q - mem_min].hh.U2.b0 == 2)
          free_node(q, 7);
        else
          free_node(q, 3);
        q = cur_p;
      }
      q = passive;
      while (q != (-1073741824)) {
        cur_p = mem[q - mem_min].hh.rh;
        free_node(q, 2);
        q = cur_p;
      }
      if (!second_pass) {
        threshold = eqtb[12164].int_;
        second_pass = true;
        final_pass = (eqtb[12750].int_ <= 0);
      } else {
        background[2] += eqtb[12750].int_;
        final_pass = true;
      }
    }
  _L30:
    post_line_break(final_widow_penalty);
    q = mem[mem_max - mem_min - 7].hh.rh;
    while (q != (mem_max - 7)) {
      cur_p = mem[q - mem_min].hh.rh;
      if (mem[q - mem_min].hh.U2.b0 == 2)
        free_node(q, 7);
      else
        free_node(q, 3);
      q = cur_p;
    }
    q = passive;
    while (q != (-1073741824)) {
      cur_p = mem[q - mem_min].hh.rh;
      free_node(q, 2);
      q = cur_p;
    }
    pack_begin_line = 0;
  }
  void new_hyph_exceptions() {
    char n = 0, j;
    hyph_pointer h;
    str_number k;
    halfword p = -1073741824, q;
    str_number s, t;
    pool_pointer u, v;
    scan_left_brace();
    if (eqtb[12213].int_ <= 0) {
      cur_lang = 0;
    } else if (eqtb[12213].int_ > 255)
      cur_lang = 0;
    else
      cur_lang = eqtb[12213].int_;
    while (true) {
      get_x_token();
    _L21:
      switch (cur_cmd) {
      case 11:
      case 12:
      case 68:
        if (cur_chr == 45) {
          if (n < 63) {
            q = get_avail();
            mem[q - mem_min].hh.rh = p;
            mem[q - mem_min].hh.lh = n;
            p = q;
          }
        } else if (!eqtb[cur_chr + 11139].hh.rh) {
          print_nl(262);
          print(944);
          help_ptr = 2;
          help_line[1] = 945;
          help_line[0] = 946;
          error();
        } else if (n < 63) {
          ++n;
          hc[n] = eqtb[cur_chr + 11139].hh.rh;
        }
        break;
      case 16:
        scan_char_num();
        cur_chr = cur_val;
        cur_cmd = 68;
        goto _L21;
        break;
      case 10:
      case 2:
        if (n > 1) {
          ++n;
          hc[n] = cur_lang;
          if (pool_ptr + n > pool_size)
            overflow(257, pool_size - init_pool_ptr);
          h = 0;
          for (j = 1; j <= n; ++j) {
            h = (h + h + hc[j]) % 307;
            str_pool[pool_ptr] = hc[j];
            ++pool_ptr;
          }
          s = make_string();
          if (hyph_count == 307)
            overflow(947, 307);
          ++hyph_count;
          while (hyph_word[h]) {
            k = hyph_word[h];
            if (str_start[k + 1] - str_start[k] <
                str_start[s + 1] - str_start[s])
              goto _L40;
            if (str_start[k + 1] - str_start[k] >
                str_start[s + 1] - str_start[s])
              goto _L45;
            u = str_start[k];
            v = str_start[s];
            do {
              if (str_pool[u] < str_pool[v])
                goto _L40;
              if (str_pool[u] > str_pool[v])
                goto _L45;
              ++u;
              ++v;
            } while (u != str_start[k + 1]);
          _L40:
            q = hyph_list[h];
            hyph_list[h] = p;
            p = q;
            t = hyph_word[h];
            hyph_word[h] = s;
            s = t;
          _L45:
            if (h > 0)
              --h;
            else
              h = 307;
          }
          hyph_word[h] = s;
          hyph_list[h] = p;
        }
        if (cur_cmd == 2)
          goto _L10;
        n = 0;
        p = -1073741824;
        break;
      default:
        print_nl(262);
        print(680);
        print_esc(940);
        print(941);
        help_ptr = 2;
        help_line[1] = 942;
        help_line[0] = 943;
        error();
        break;
      }
    }
  _L10:;
  }
  halfword prune_page_top(halfword p) {
    halfword prev_p = mem_max - 3, q;
    mem[mem_max - mem_min - 3].hh.rh = p;
    while (p != (-1073741824)) {
      switch (mem[p - mem_min].hh.U2.b0) {
      case 0:
      case 1:
      case 2:
        q = new_skip_param(10);
        mem[prev_p - mem_min].hh.rh = q;
        mem[q - mem_min].hh.rh = p;
        if (mem[temp_ptr - mem_min + 1].int_ > mem[p - mem_min + 3].int_)
          mem[temp_ptr - mem_min + 1].int_ -= mem[p - mem_min + 3].int_;
        else
          mem[temp_ptr - mem_min + 1].int_ = 0;
        p = -1073741824;
        break;
      case 8:
      case 4:
      case 3:
        prev_p = p;
        p = mem[prev_p - mem_min].hh.rh;
        break;
      case 10:
      case 11:
      case 12:
        q = p;
        p = mem[q - mem_min].hh.rh;
        mem[q - mem_min].hh.rh = -1073741824;
        mem[prev_p - mem_min].hh.rh = p;
        flush_node_list(q);
        break;
      default:
        confusion(958);
        break;
      }
    }
    return mem[mem_max - mem_min - 3].hh.rh;
  }
  halfword vert_break(halfword p, scaled h, scaled d) {
    halfword prev_p = p, q, r, best_place;
    integer pi, b, least_cost = 1073741823;
    scaled prev_dp = 0;
    small_number t;
    active_width[1] = 0;
    active_width[2] = 0;
    active_width[3] = 0;
    active_width[4] = 0;
    active_width[5] = 0;
    active_width[6] = 0;
    while (true) {
      if (p == (-1073741824)) {
        pi = -10000;
      } else {
        switch (mem[p - mem_min].hh.U2.b0) {
        case 0:
        case 1:
        case 2:
          active_width[1] += prev_dp + mem[p - mem_min + 3].int_;
          prev_dp = mem[p - mem_min + 2].int_;
          goto _L45;
          break;
        case 8:
          goto _L45;
          break;
        case 10:
          if (mem[prev_p - mem_min].hh.U2.b0 >= 9)
            goto _L90;
          pi = 0;
          break;
        case 11:
          if (mem[p - mem_min].hh.rh == (-1073741824))
            t = 12;
          else
            t = mem[mem[p - mem_min].hh.rh - mem_min].hh.U2.b0;
          if (t != 10)
            goto _L90;
          pi = 0;
          break;
        case 12:
          pi = mem[p - mem_min + 1].int_;
          break;
        case 4:
        case 3:
          goto _L45;
          break;
        default:
          confusion(959);
          break;
        }
      }
      if (pi < 10000) {
        if (active_width[1] < h) {
          if (active_width[3] || active_width[4] || active_width[5])
            b = 0;
          else
            b = badness(h - active_width[1], active_width[2]);
        } else if (active_width[1] - h > active_width[6])
          b = 1073741823;
        else
          b = badness(active_width[1] - h, active_width[6]);
        if (b < 1073741823) {
          if (pi <= (-10000)) {
            b = pi;
          } else if (b < 10000)
            b += pi;
          else
            b = 100000;
        }
        if (b <= least_cost) {
          best_place = p;
          least_cost = b;
          best_height_plus_depth = active_width[1] + prev_dp;
        }
        if ((b == 1073741823) || (pi <= (-10000)))
          goto _L30;
      }
      if ((mem[p - mem_min].hh.U2.b0 < 10) || (mem[p - mem_min].hh.U2.b0 > 11))
        goto _L45;
    _L90:
      if (mem[p - mem_min].hh.U2.b0 == 11) {
        q = p;
      } else {
        q = mem[p - mem_min + 1].hh.lh;
        active_width[mem[q - mem_min].hh.U2.b0 + 2] +=
            mem[q - mem_min + 2].int_;
        active_width[6] += mem[q - mem_min + 3].int_;
        if (mem[q - mem_min].hh.U2.b1 && mem[q - mem_min + 3].int_) {
          print_nl(262);
          print(960);
          help_ptr = 4;
          help_line[3] = 961;
          help_line[2] = 962;
          help_line[1] = 963;
          help_line[0] = 921;
          error();
          r = new_spec(q);
          mem[r - mem_min].hh.U2.b1 = 0;
          delete_glue_ref(q);
          mem[p - mem_min + 1].hh.lh = r;
          q = r;
        }
      }
      active_width[1] += prev_dp + mem[q - mem_min + 1].int_;
      prev_dp = 0;
    _L45:
      if (prev_dp > d) {
        active_width[1] += prev_dp - d;
        prev_dp = d;
      }
      prev_p = p;
      p = mem[prev_p - mem_min].hh.rh;
    }
  _L30:
    return best_place;
  }
  halfword vsplit(eight_bits n, scaled h) {
    halfword result, p, q;
    halfword v = eqtb[n + 10578].hh.rh;
    if (cur_mark[3] != (-1073741824)) {
      delete_token_ref(cur_mark[3]);
      cur_mark[3] = -1073741824;
      delete_token_ref(cur_mark[4]);
      cur_mark[4] = -1073741824;
    }
    if (v == (-1073741824)) {
      result = -1073741824;
      goto _L10;
    }
    if (mem[v - mem_min].hh.U2.b0 != 1) {
      print_nl(262);
      print(338);
      print_esc(964);
      print(965);
      print_esc(966);
      help_ptr = 2;
      help_line[1] = 967;
      help_line[0] = 968;
      error();
      result = -1073741824;
      goto _L10;
    }
    q = vert_break(mem[v - mem_min + 5].hh.rh, h, eqtb[12736].int_);
    p = mem[v - mem_min + 5].hh.rh;
    if (p == q) {
      mem[v - mem_min + 5].hh.rh = -1073741824;
    } else {
      while (true) {
        if (mem[p - mem_min].hh.U2.b0 == 4) {
          if (cur_mark[3] == (-1073741824)) {
            cur_mark[3] = mem[p - mem_min + 1].int_;
            cur_mark[4] = cur_mark[3];
            mem[cur_mark[3] - mem_min].hh.lh += 2;
          } else {
            delete_token_ref(cur_mark[4]);
            cur_mark[4] = mem[p - mem_min + 1].int_;
            ++mem[cur_mark[4] - mem_min].hh.lh;
          }
        }
        if (mem[p - mem_min].hh.rh == q) {
          mem[p - mem_min].hh.rh = -1073741824;
          goto _L30;
        }
        p = mem[p - mem_min].hh.rh;
      }
    }
  _L30:
    q = prune_page_top(q);
    p = mem[v - mem_min + 5].hh.rh;
    free_node(v, 7);
    if (q == (-1073741824))
      eqtb[n + 10578].hh.rh = -1073741824;
    else
      eqtb[n + 10578].hh.rh = vpackage(q, 0, 1, 1073741823);
    result = vpackage(p, h, 0, eqtb[12736].int_);
  _L10:
    return result;
  }
  void print_totals() {
    print_scaled(page_so_far[1]);
    if (page_so_far[2]) {
      print(312);
      print_scaled(page_so_far[2]);
      print(338);
    }
    if (page_so_far[3]) {
      print(312);
      print_scaled(page_so_far[3]);
      print(311);
    }
    if (page_so_far[4]) {
      print(312);
      print_scaled(page_so_far[4]);
      print(977);
    }
    if (page_so_far[5]) {
      print(312);
      print_scaled(page_so_far[5]);
      print(978);
    }
    if (page_so_far[6]) {
      print(313);
      print_scaled(page_so_far[6]);
    }
  }
  void freeze_page_specs(small_number s) {
    page_contents = s;
    page_so_far[0] = eqtb[12734].int_;
    page_max_depth = eqtb[12735].int_;
    page_so_far[7] = 0;
    page_so_far[1] = 0;
    page_so_far[2] = 0;
    page_so_far[3] = 0;
    page_so_far[4] = 0;
    page_so_far[5] = 0;
    page_so_far[6] = 0;
    least_page_cost = 1073741823;
  }
  void box_error(eight_bits n) {
    error();
    begin_diagnostic();
    print_nl(835);
    show_box(eqtb[n + 10578].hh.rh);
    end_diagnostic(true);
    flush_node_list(eqtb[n + 10578].hh.rh);
    eqtb[n + 10578].hh.rh = -1073741824;
  }
  void ensure_vbox(eight_bits n) {
    halfword p = eqtb[n + 10578].hh.rh;
    if (p == (-1073741824))
      return;
    if (mem[p - mem_min].hh.U2.b0)
      return;
    print_nl(262);
    print(988);
    help_ptr = 3;
    help_line[2] = 989;
    help_line[1] = 990;
    help_line[0] = 991;
    box_error(n);
  }
  void fire_up(halfword c) {
    halfword p, q = mem_max - 4, r, s, prev_p = mem_max - 2;
    uint8_t n;
    bool wait;
    integer save_vbadness;
    scaled save_vfuzz;
    halfword save_split_top_skip;
    if (mem[best_page_break - mem_min].hh.U2.b0 == 12) {
      geq_word_define(12202, mem[best_page_break - mem_min + 1].int_);
      mem[best_page_break - mem_min + 1].int_ = 10000;
    } else {
      geq_word_define(12202, 10000);
    }
    if (cur_mark[2] != (-1073741824)) {
      if (cur_mark[0] != (-1073741824))
        delete_token_ref(cur_mark[0]);
      cur_mark[0] = cur_mark[2];
      ++mem[cur_mark[0] - mem_min].hh.lh;
      delete_token_ref(cur_mark[1]);
      cur_mark[1] = -1073741824;
    }
    if (c == best_page_break)
      best_page_break = -1073741824;
    if (eqtb[10833].hh.rh != (-1073741824)) {
      print_nl(262);
      print(338);
      print_esc(409);
      print(1002);
      help_ptr = 2;
      help_line[1] = 1003;
      help_line[0] = 991;
      box_error(255);
    }
    insert_penalties = 0;
    save_split_top_skip = eqtb[9792].hh.rh;
    if (eqtb[12216].int_ <= 0) {
      r = mem[mem_max - mem_min].hh.rh;
      while (r != mem_max) {
        if (mem[r - mem_min + 2].hh.lh != (-1073741824)) {
          n = mem[r - mem_min].hh.U2.b1;
          ensure_vbox(n);
          if (eqtb[n + 10578].hh.rh == (-1073741824))
            eqtb[n + 10578].hh.rh = new_null_box();
          p = eqtb[n + 10578].hh.rh + 5;
          while (mem[p - mem_min].hh.rh != (-1073741824))
            p = mem[p - mem_min].hh.rh;
          mem[r - mem_min + 2].hh.rh = p;
        }
        r = mem[r - mem_min].hh.rh;
      }
    }
    mem[q - mem_min].hh.rh = -1073741824;
    p = mem[prev_p - mem_min].hh.rh;
    while (p != best_page_break) {
      if (mem[p - mem_min].hh.U2.b0 == 3) {
        if (eqtb[12216].int_ <= 0) {
          r = mem[mem_max - mem_min].hh.rh;
          while (mem[r - mem_min].hh.U2.b1 != mem[p - mem_min].hh.U2.b1)
            r = mem[r - mem_min].hh.rh;
          if (mem[r - mem_min + 2].hh.lh == (-1073741824)) {
            wait = true;
          } else {
            wait = false;
            s = mem[r - mem_min + 2].hh.rh;
            mem[s - mem_min].hh.rh = mem[p - mem_min + 4].hh.lh;
            if (mem[r - mem_min + 2].hh.lh == p) {
              if (mem[r - mem_min].hh.U2.b0 == 1) {
                if ((mem[r - mem_min + 1].hh.lh == p) &&
                    (mem[r - mem_min + 1].hh.rh != (-1073741824))) {
                  while (mem[s - mem_min].hh.rh != mem[r - mem_min + 1].hh.rh)
                    s = mem[s - mem_min].hh.rh;
                  mem[s - mem_min].hh.rh = -1073741824;
                  eqtb[9792].hh.rh = mem[p - mem_min + 4].hh.rh;
                  mem[p - mem_min + 4].hh.lh =
                      prune_page_top(mem[r - mem_min + 1].hh.rh);
                  if (mem[p - mem_min + 4].hh.lh != (-1073741824)) {
                    temp_ptr =
                        vpackage(mem[p - mem_min + 4].hh.lh, 0, 1, 1073741823);
                    (mem[p - mem_min + 3].int_ =
                         (mem[temp_ptr - mem_min + 3].int_ +
                          (mem[temp_ptr - mem_min + 2].int_)));
                    free_node(temp_ptr, 7);
                    wait = true;
                  }
                }
              }
              mem[r - mem_min + 2].hh.lh = -1073741824;
              n = mem[r - mem_min].hh.U2.b1;
              temp_ptr = mem[eqtb[n + 10578].hh.rh - mem_min + 5].hh.rh;
              free_node(eqtb[n + 10578].hh.rh, 7);
              eqtb[n + 10578].hh.rh = vpackage(temp_ptr, 0, 1, 1073741823);
            } else {
              while (mem[s - mem_min].hh.rh != (-1073741824))
                s = mem[s - mem_min].hh.rh;
              mem[r - mem_min + 2].hh.rh = s;
            }
          }
          mem[prev_p - mem_min].hh.rh = mem[p - mem_min].hh.rh;
          mem[p - mem_min].hh.rh = -1073741824;
          if (wait) {
            mem[q - mem_min].hh.rh = p;
            q = p;
            ++insert_penalties;
          } else {
            delete_glue_ref(mem[p - mem_min + 4].hh.rh);
            free_node(p, 5);
          }
          p = prev_p;
        }
      } else if (mem[p - mem_min].hh.U2.b0 == 4) {
        if (cur_mark[1] == (-1073741824)) {
          cur_mark[1] = mem[p - mem_min + 1].int_;
          ++mem[cur_mark[1] - mem_min].hh.lh;
        }
        if (cur_mark[2] != (-1073741824))
          delete_token_ref(cur_mark[2]);
        cur_mark[2] = mem[p - mem_min + 1].int_;
        ++mem[cur_mark[2] - mem_min].hh.lh;
      }
      prev_p = p;
      p = mem[prev_p - mem_min].hh.rh;
    }
    eqtb[9792].hh.rh = save_split_top_skip;
    if (p != (-1073741824)) {
      if (mem[mem_max - mem_min - 1].hh.rh == (-1073741824)) {
        if (!nest_ptr)
          cur_list.tail_field = page_tail;
        else
          nest[0].tail_field = page_tail;
      }
      mem[page_tail - mem_min].hh.rh = mem[mem_max - mem_min - 1].hh.rh;
      mem[mem_max - mem_min - 1].hh.rh = p;
      mem[prev_p - mem_min].hh.rh = -1073741824;
    }
    save_vbadness = eqtb[12190].int_;
    eqtb[12190].int_ = 10000;
    save_vfuzz = eqtb[12739].int_;
    eqtb[12739].int_ = 1073741823;
    eqtb[10833].hh.rh = vpackage(mem[mem_max - mem_min - 2].hh.rh, best_size, 0,
                                 page_max_depth);
    eqtb[12190].int_ = save_vbadness;
    eqtb[12739].int_ = save_vfuzz;
    if (last_glue != 1073741824)
      delete_glue_ref(last_glue);
    page_contents = 0;
    page_tail = mem_max - 2;
    mem[mem_max - mem_min - 2].hh.rh = -1073741824;
    last_glue = 1073741824;
    last_penalty = 0;
    last_kern = 0;
    page_so_far[7] = 0;
    page_max_depth = 0;
    if (q != (mem_max - 4)) {
      mem[mem_max - mem_min - 2].hh.rh = mem[mem_max - mem_min - 4].hh.rh;
      page_tail = q;
    }
    r = mem[mem_max - mem_min].hh.rh;
    while (r != mem_max) {
      q = mem[r - mem_min].hh.rh;
      free_node(r, 4);
      r = q;
    }
    mem[mem_max - mem_min].hh.rh = mem_max;
    if ((cur_mark[0] != (-1073741824)) && (cur_mark[1] == (-1073741824))) {
      cur_mark[1] = cur_mark[0];
      ++mem[cur_mark[0] - mem_min].hh.lh;
    }
    if (eqtb[10313].hh.rh != (-1073741824)) {
      if (dead_cycles < eqtb[12203].int_) {
        output_active = true;
        ++dead_cycles;
        push_nest();
        cur_list.mode_field = -1;
        cur_list.aux_field.int_ = -65536000;
        cur_list.ml_field = -line;
        begin_token_list(eqtb[10313].hh.rh, 6);
        new_save_level(8);
        normal_paragraph();
        scan_left_brace();
        goto _L10;
      }
      print_nl(262);
      print(1004);
      print_int(dead_cycles);
      print(1005);
      help_ptr = 3;
      help_line[2] = 1006;
      help_line[1] = 1007;
      help_line[0] = 1008;
      error();
    }
    if (mem[mem_max - mem_min - 2].hh.rh != (-1073741824)) {
      if (mem[mem_max - mem_min - 1].hh.rh == (-1073741824)) {
        if (!nest_ptr)
          cur_list.tail_field = page_tail;
        else
          nest[0].tail_field = page_tail;
      } else {
        mem[page_tail - mem_min].hh.rh = mem[mem_max - mem_min - 1].hh.rh;
      }
      mem[mem_max - mem_min - 1].hh.rh = mem[mem_max - mem_min - 2].hh.rh;
      mem[mem_max - mem_min - 2].hh.rh = -1073741824;
      page_tail = mem_max - 2;
    }
    ship_out(eqtb[10833].hh.rh);
    eqtb[10833].hh.rh = -1073741824;
  _L10:;
  }
  void build_page() {
    halfword p, q, r;
    integer b, c, pi;
    uint8_t n;
    scaled delta, h, w;
    if ((mem[mem_max - mem_min - 1].hh.rh == (-1073741824)) || output_active)
      goto _L10;
    do {
    _L22:
      p = mem[mem_max - mem_min - 1].hh.rh;
      if (last_glue != 1073741824)
        delete_glue_ref(last_glue);
      last_penalty = 0;
      last_kern = 0;
      if (mem[p - mem_min].hh.U2.b0 == 10) {
        last_glue = mem[p - mem_min + 1].hh.lh;
        ++mem[last_glue - mem_min].hh.rh;
      } else {
        last_glue = 1073741824;
        if (mem[p - mem_min].hh.U2.b0 == 12) {
          last_penalty = mem[p - mem_min + 1].int_;
        } else if (mem[p - mem_min].hh.U2.b0 == 11)
          last_kern = mem[p - mem_min + 1].int_;
      }
      switch (mem[p - mem_min].hh.U2.b0) {
      case 0:
      case 1:
      case 2:
        if (page_contents < 2) {
          if (!page_contents)
            freeze_page_specs(2);
          else
            page_contents = 2;
          q = new_skip_param(9);
          if (mem[temp_ptr - mem_min + 1].int_ > mem[p - mem_min + 3].int_)
            mem[temp_ptr - mem_min + 1].int_ -= mem[p - mem_min + 3].int_;
          else
            mem[temp_ptr - mem_min + 1].int_ = 0;
          mem[q - mem_min].hh.rh = p;
          mem[mem_max - mem_min - 1].hh.rh = q;
          goto _L22;
        } else {
          page_so_far[1] += page_so_far[7] + mem[p - mem_min + 3].int_;
          page_so_far[7] = mem[p - mem_min + 2].int_;
          goto _L80;
        }
        break;
      case 8:
        goto _L80;
        break;
      case 10:
        if (page_contents < 2)
          goto _L31;
        if (mem[page_tail - mem_min].hh.U2.b0 >= 9)
          goto _L90;
        pi = 0;
        break;
      case 11:
        if (page_contents < 2)
          goto _L31;
        if (mem[p - mem_min].hh.rh == (-1073741824))
          goto _L10;
        if (mem[mem[p - mem_min].hh.rh - mem_min].hh.U2.b0 != 10)
          goto _L90;
        pi = 0;
        break;
      case 12:
        if (page_contents < 2)
          goto _L31;
        pi = mem[p - mem_min + 1].int_;
        break;
      case 4:
        goto _L80;
        break;
      case 3:
        if (!page_contents)
          freeze_page_specs(1);
        n = mem[p - mem_min].hh.U2.b1;
        r = mem_max;
        while (n >= mem[mem[r - mem_min].hh.rh - mem_min].hh.U2.b1)
          r = mem[r - mem_min].hh.rh;
        if (mem[r - mem_min].hh.U2.b1 != n) {
          q = get_node(4);
          mem[q - mem_min].hh.rh = mem[r - mem_min].hh.rh;
          mem[r - mem_min].hh.rh = q;
          r = q;
          mem[r - mem_min].hh.U2.b1 = n;
          mem[r - mem_min].hh.U2.b0 = 0;
          ensure_vbox(n);
          if (eqtb[n + 10578].hh.rh == (-1073741824))
            mem[r - mem_min + 3].int_ = 0;
          else
            (mem[r - mem_min + 3].int_ =
                 (mem[eqtb[n + 10578].hh.rh - mem_min + 3].int_ +
                  (mem[(eqtb[n + 10578].hh.rh - mem_min + 2)].int_)));
          mem[r - mem_min + 2].hh.lh = -1073741824;
          q = eqtb[n + 9800].hh.rh;
          if (eqtb[n + 12218].int_ == 1000)
            h = mem[r - mem_min + 3].int_;
          else
            h = x_over_n(mem[r - mem_min + 3].int_, 1000) *
                eqtb[n + 12218].int_;
          page_so_far[0] += (-h) - mem[q - mem_min + 1].int_;
          page_so_far[mem[q - mem_min].hh.U2.b0 + 2] +=
              mem[q - mem_min + 2].int_;
          page_so_far[6] += mem[q - mem_min + 3].int_;
          if (mem[q - mem_min].hh.U2.b1 && mem[q - mem_min + 3].int_) {
            print_nl(262);
            print(997);
            print_esc(395);
            print_int(n);
            help_ptr = 3;
            help_line[2] = 998;
            help_line[1] = 999;
            help_line[0] = 921;
            error();
          }
        }
        if (mem[r - mem_min].hh.U2.b0 == 1) {
          insert_penalties += mem[p - mem_min + 1].int_;
        } else {
          mem[r - mem_min + 2].hh.rh = p;
          delta =
              page_so_far[0] - page_so_far[1] - page_so_far[7] + page_so_far[6];
          if (eqtb[n + 12218].int_ == 1000)
            h = mem[p - mem_min + 3].int_;
          else
            h = x_over_n(mem[p - mem_min + 3].int_, 1000) *
                eqtb[n + 12218].int_;
          if (((h <= 0) || (h <= delta)) &&
              (mem[p - mem_min + 3].int_ + mem[r - mem_min + 3].int_ <=
               eqtb[n + 12751].int_)) {
            page_so_far[0] -= h;
            mem[r - mem_min + 3].int_ += mem[p - mem_min + 3].int_;
          } else {
            if (eqtb[n + 12218].int_ <= 0) {
              w = 1073741823;
            } else {
              w = page_so_far[0] - page_so_far[1] - page_so_far[7];
              if (eqtb[n + 12218].int_ != 1000)
                w = x_over_n(w, eqtb[n + 12218].int_) * 1000;
            }
            if (w > (eqtb[n + 12751].int_ - mem[r - mem_min + 3].int_))
              w = eqtb[n + 12751].int_ - mem[r - mem_min + 3].int_;
            q = vert_break(mem[p - mem_min + 4].hh.lh, w,
                           mem[p - mem_min + 2].int_);
            mem[r - mem_min + 3].int_ += best_height_plus_depth;
            if (eqtb[n + 12218].int_ != 1000)
              best_height_plus_depth =
                  x_over_n(best_height_plus_depth, 1000) * eqtb[n + 12218].int_;
            page_so_far[0] -= best_height_plus_depth;
            mem[r - mem_min].hh.U2.b0 = 1;
            mem[r - mem_min + 1].hh.rh = q;
            mem[r - mem_min + 1].hh.lh = p;
            if (q == (-1073741824)) {
              insert_penalties -= 10000;
            } else if (mem[q - mem_min].hh.U2.b0 == 12)
              insert_penalties += mem[q - mem_min + 1].int_;
          }
        }
        goto _L80;
        break;
      default:
        confusion(992);
        break;
      }
      if (pi < 10000) {
        if (page_so_far[1] < page_so_far[0]) {
          if (page_so_far[3] || page_so_far[4] || page_so_far[5])
            b = 0;
          else
            b = badness(page_so_far[0] - page_so_far[1], page_so_far[2]);
        } else if (page_so_far[1] - page_so_far[0] > page_so_far[6])
          b = 1073741823;
        else
          b = badness(page_so_far[1] - page_so_far[0], page_so_far[6]);
        if (b < 1073741823) {
          if (pi <= (-10000)) {
            c = pi;
          } else if (b < 10000)
            c = b + pi + insert_penalties;
          else
            c = 100000;
        } else {
          c = b;
        }
        if (insert_penalties >= 10000)
          c = 1073741823;
        if (c <= least_page_cost) {
          best_page_break = p;
          best_size = page_so_far[0];
          least_page_cost = c;
          r = mem[mem_max - mem_min].hh.rh;
          while (r != mem_max) {
            mem[r - mem_min + 2].hh.lh = mem[r - mem_min + 2].hh.rh;
            r = mem[r - mem_min].hh.rh;
          }
        }
        if ((c == 1073741823) || (pi <= (-10000))) {
          fire_up(p);
          if (output_active)
            goto _L10;
          goto _L30;
        }
      }
      if ((mem[p - mem_min].hh.U2.b0 < 10) || (mem[p - mem_min].hh.U2.b0 > 11))
        goto _L80;
    _L90:
      if (mem[p - mem_min].hh.U2.b0 == 11) {
        q = p;
      } else {
        q = mem[p - mem_min + 1].hh.lh;
        page_so_far[mem[q - mem_min].hh.U2.b0 + 2] += mem[q - mem_min + 2].int_;
        page_so_far[6] += mem[q - mem_min + 3].int_;
        if (mem[q - mem_min].hh.U2.b1 && mem[q - mem_min + 3].int_) {
          print_nl(262);
          print(993);
          help_ptr = 4;
          help_line[3] = 994;
          help_line[2] = 962;
          help_line[1] = 963;
          help_line[0] = 921;
          error();
          r = new_spec(q);
          mem[r - mem_min].hh.U2.b1 = 0;
          delete_glue_ref(q);
          mem[p - mem_min + 1].hh.lh = r;
          q = r;
        }
      }
      page_so_far[1] += page_so_far[7] + mem[q - mem_min + 1].int_;
      page_so_far[7] = 0;
    _L80:
      if (page_so_far[7] > page_max_depth) {
        page_so_far[1] += page_so_far[7] - page_max_depth;
        page_so_far[7] = page_max_depth;
      }
      mem[page_tail - mem_min].hh.rh = p;
      page_tail = p;
      mem[mem_max - mem_min - 1].hh.rh = mem[p - mem_min].hh.rh;
      mem[p - mem_min].hh.rh = -1073741824;
      goto _L30;
    _L31:
      mem[mem_max - mem_min - 1].hh.rh = mem[p - mem_min].hh.rh;
      mem[p - mem_min].hh.rh = -1073741824;
      flush_node_list(p);
    _L30:;
    } while (mem[mem_max - mem_min - 1].hh.rh != (-1073741824));
    if (!nest_ptr)
      cur_list.tail_field = mem_max - 1;
    else
      nest[0].tail_field = mem_max - 1;
  _L10:;
  }
  void app_space() {
    halfword q;
    if ((cur_list.aux_field.hh.lh >= 2000) && eqtb[9795].hh.rh) {
      q = new_param_glue(13);
    } else {
      if (eqtb[9794].hh.rh) {
        main_p = eqtb[9794].hh.rh;
      } else {
        main_p = font_glue[eqtb[10834].hh.rh];
        if (main_p == (-1073741824)) {
          main_p = new_spec(0);
          main_k = param_base[eqtb[10834].hh.rh] + 2;
          mem[main_p - mem_min + 1].int_ = font_info[main_k].int_;
          mem[main_p - mem_min + 2].int_ = font_info[main_k + 1].int_;
          mem[main_p - mem_min + 3].int_ = font_info[main_k + 2].int_;
          font_glue[eqtb[10834].hh.rh] = main_p;
        }
      }
      main_p = new_spec(main_p);
      if (cur_list.aux_field.hh.lh >= 2000)
        mem[main_p - mem_min + 1].int_ +=
            font_info[param_base[eqtb[10834].hh.rh] + 7].int_;
      mem[main_p - mem_min + 2].int_ = xn_over_d(
          mem[main_p - mem_min + 2].int_, cur_list.aux_field.hh.lh, 1000);
      mem[main_p - mem_min + 3].int_ = xn_over_d(
          mem[main_p - mem_min + 3].int_, 1000, cur_list.aux_field.hh.lh);
      q = new_glue(main_p);
      mem[main_p - mem_min].hh.rh = -1073741824;
    }
    mem[cur_list.tail_field - mem_min].hh.rh = q;
    cur_list.tail_field = q;
  }
  void insert_dollar_sign() {
    back_input();
    cur_tok = 804;
    print_nl(262);
    print(1016);
    help_ptr = 2;
    help_line[1] = 1017;
    help_line[0] = 1018;
    ins_error();
  }
  void you_cant() {
    print_nl(262);
    print(685);
    print_cmd_chr(cur_cmd, cur_chr);
    print(1019);
    print_mode(cur_list.mode_field);
  }
  void report_illegal_case() {
    you_cant();
    help_ptr = 4;
    help_line[3] = 1020;
    help_line[2] = 1021;
    help_line[1] = 1022;
    help_line[0] = 1023;
    error();
  }
  bool privileged() {
    if (cur_list.mode_field > 0) {
      return true;
    } else {
      report_illegal_case();
      return false;
    }
  }
  bool its_all_over() {
    bool result;
    if (privileged()) {
      if ((mem_max - 2 == page_tail) &&
          (cur_list.head_field == cur_list.tail_field) && (!dead_cycles)) {
        result = true;
        goto _L10;
      }
      back_input();
      mem[cur_list.tail_field - mem_min].hh.rh = new_null_box();
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      mem[cur_list.tail_field - mem_min + 1].int_ = eqtb[12733].int_;
      mem[cur_list.tail_field - mem_min].hh.rh = new_glue(8);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      mem[cur_list.tail_field - mem_min].hh.rh = new_penalty(-1073741824);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      build_page();
    }
    result = false;
  _L10:
    return result;
  }
  void append_glue() {
    small_number s = cur_chr;
    switch (s) {
    case 0:
      cur_val = 4;
      break;
    case 1:
      cur_val = 8;
      break;
    case 2:
      cur_val = 12;
      break;
    case 3:
      cur_val = 16;
      break;
    case 4:
      scan_glue(2);
      break;
    case 5:
      scan_glue(3);
      break;
    }
    mem[cur_list.tail_field - mem_min].hh.rh = new_glue(cur_val);
    cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    if (s < 4)
      return;
    --mem[cur_val - mem_min].hh.rh;
    if (s > 4)
      mem[cur_list.tail_field - mem_min].hh.U2.b1 = 99;
  }
  void append_kern() {
    quarterword s = cur_chr;
    scan_dimen(s == 99, false, false);
    mem[cur_list.tail_field - mem_min].hh.rh = new_kern(cur_val);
    cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    mem[cur_list.tail_field - mem_min].hh.U2.b1 = s;
  }
  void off_save() {
    halfword p;
    if (!cur_group) {
      print_nl(262);
      print(776);
      print_cmd_chr(cur_cmd, cur_chr);
      help_ptr = 1;
      help_line[0] = 1042;
      error();
      return;
    }
    back_input();
    p = get_avail();
    mem[mem_max - mem_min - 3].hh.rh = p;
    print_nl(262);
    print(625);
    switch (cur_group) {
    case 14:
      mem[p - mem_min].hh.lh = 13611;
      print_esc(516);
      break;
    case 15:
      mem[p - mem_min].hh.lh = 804;
      print_char(36);
      break;
    case 16:
      mem[p - mem_min].hh.lh = 13612;
      mem[p - mem_min].hh.rh = get_avail();
      p = mem[p - mem_min].hh.rh;
      mem[p - mem_min].hh.lh = 3118;
      print_esc(1041);
      break;
    default:
      mem[p - mem_min].hh.lh = 637;
      print_char(125);
      break;
    }
    print(626);
    begin_token_list(mem[mem_max - mem_min - 3].hh.rh, 4);
    help_ptr = 5;
    help_line[4] = 1036;
    help_line[3] = 1037;
    help_line[2] = 1038;
    help_line[1] = 1039;
    help_line[0] = 1040;
    error();
  }
  void extra_right_brace() {
    print_nl(262);
    print(1047);
    switch (cur_group) {
    case 14:
      print_esc(516);
      break;
    case 15:
      print_char(36);
      break;
    case 16:
      print_esc(876);
      break;
    }
    help_ptr = 5;
    help_line[4] = 1048;
    help_line[3] = 1049;
    help_line[2] = 1050;
    help_line[1] = 1051;
    help_line[0] = 1052;
    error();
    ++align_state;
  }
  void normal_paragraph() {
    if (eqtb[12182].int_)
      eq_word_define(12182, 0);
    if (eqtb[12747].int_)
      eq_word_define(12747, 0);
    if (eqtb[12204].int_ != 1)
      eq_word_define(12204, 1);
    if (eqtb[10312].hh.rh != (-1073741824))
      eq_define(10312, 118, -1073741824);
  }
  void box_end(integer box_context) {
    halfword p;
    if (box_context < 1073741824) {
      if (cur_box == (-1073741824))
        return;
      mem[cur_box - mem_min + 4].int_ = box_context;
      if (abs(cur_list.mode_field) == 1) {
        append_to_vlist(cur_box);
        if (adjust_tail != (-1073741824)) {
          if (mem_max - 5 != adjust_tail) {
            mem[cur_list.tail_field - mem_min].hh.rh =
                mem[mem_max - mem_min - 5].hh.rh;
            cur_list.tail_field = adjust_tail;
          }
          adjust_tail = -1073741824;
        }
        if (cur_list.mode_field > 0)
          build_page();
        return;
      }
      if (abs(cur_list.mode_field) == 102) {
        cur_list.aux_field.hh.lh = 1000;
      } else {
        p = new_noad();
        mem[p - mem_min + 1].hh.rh = 2;
        mem[p - mem_min + 1].hh.lh = cur_box;
        cur_box = p;
      }
      mem[cur_list.tail_field - mem_min].hh.rh = cur_box;
      cur_list.tail_field = cur_box;
      return;
    }
    if (box_context < 1073742336) {
      if (box_context < 1073742080)
        eq_define(box_context - 1073731246, 119, cur_box);
      else
        geq_define(box_context - 1073731502, 119, cur_box);
      return;
    }
    if (cur_box == (-1073741824))
      return;
    if (box_context <= 1073742336) {
      ship_out(cur_box);
      return;
    }
    do {
      get_x_token();
    } while ((cur_cmd == 10) || (!cur_cmd));
    if (((cur_cmd == 26) && (abs(cur_list.mode_field) != 1)) ||
        ((cur_cmd == 27) && (abs(cur_list.mode_field) == 1))) {
      append_glue();
      mem[cur_list.tail_field - mem_min].hh.U2.b1 = box_context - 1073742237;
      mem[cur_list.tail_field - mem_min + 1].hh.rh = cur_box;
      return;
    }
    print_nl(262);
    print(1065);
    help_ptr = 3;
    help_line[2] = 1066;
    help_line[1] = 1067;
    help_line[0] = 1068;
    back_error();
    flush_node_list(cur_box);
  }
  void begin_box(integer box_context) {
    halfword p, q;
    quarterword m;
    halfword k;
    eight_bits n;
    quarterword N1;
    switch (cur_chr) {
    case 0:
      scan_eight_bit_int();
      cur_box = eqtb[cur_val + 10578].hh.rh;
      eqtb[cur_val + 10578].hh.rh = -1073741824;
      break;
    case 1:
      scan_eight_bit_int();
      cur_box = copy_node_list(eqtb[cur_val + 10578].hh.rh);
      break;
    case 2:
      cur_box = -1073741824;
      if (abs(cur_list.mode_field) == 203) {
        you_cant();
        help_ptr = 1;
        help_line[0] = 1069;
        error();
      } else if ((cur_list.mode_field == 1) &&
                 (cur_list.head_field == cur_list.tail_field)) {
        you_cant();
        help_ptr = 2;
        help_line[1] = 1070;
        help_line[0] = 1071;
        error();
      } else if (cur_list.tail_field < hi_mem_min) {
        if ((!mem[cur_list.tail_field - mem_min].hh.U2.b0) ||
            (mem[cur_list.tail_field - mem_min].hh.U2.b0 == 1)) {
          q = cur_list.head_field;
          do {
            p = q;
            if (q < hi_mem_min) {
              if (mem[q - mem_min].hh.U2.b0 == 7) {
                for (N1 = mem[q - mem_min].hh.U2.b1, m = 1; m <= N1; ++m)
                  p = mem[p - mem_min].hh.rh;
                if (p == cur_list.tail_field)
                  goto _L30;
              }
            }
            q = mem[p - mem_min].hh.rh;
          } while (q != cur_list.tail_field);
          cur_box = cur_list.tail_field;
          mem[cur_box - mem_min + 4].int_ = 0;
          cur_list.tail_field = p;
          mem[p - mem_min].hh.rh = -1073741824;
        _L30:;
        }
      }
      break;
    case 3:
      scan_eight_bit_int();
      n = cur_val;
      if (!scan_keyword(841)) {
        print_nl(262);
        print(1072);
        help_ptr = 2;
        help_line[1] = 1073;
        help_line[0] = 1074;
        error();
      }
      scan_dimen(false, false, false);
      cur_box = vsplit(n, cur_val);
      break;
    default:
      k = cur_chr - 4;
      save_stack[save_ptr].int_ = box_context;
      if (k == 102) {
        if ((box_context < 1073741824) && (abs(cur_list.mode_field) == 1))
          scan_spec(3, true);
        else
          scan_spec(2, true);
      } else {
        if (k == 1) {
          scan_spec(4, true);
        } else {
          scan_spec(5, true);
          k = 1;
        }
        normal_paragraph();
      }
      push_nest();
      cur_list.mode_field = -k;
      if (k == 1) {
        cur_list.aux_field.int_ = -65536000;
        if (eqtb[10318].hh.rh != (-1073741824))
          begin_token_list(eqtb[10318].hh.rh, 11);
      } else {
        cur_list.aux_field.hh.lh = 1000;
        if (eqtb[10317].hh.rh != (-1073741824))
          begin_token_list(eqtb[10317].hh.rh, 10);
      }
      goto _L10;
      break;
    }
    box_end(box_context);
  _L10:;
  }
  void scan_box(integer box_context) {
    do {
      get_x_token();
    } while ((cur_cmd == 10) || (!cur_cmd));
    if (cur_cmd == 20) {
      begin_box(box_context);
      return;
    }
    if ((box_context >= 1073742337) && ((cur_cmd == 36) || (cur_cmd == 35))) {
      cur_box = scan_rule_spec();
      box_end(box_context);
      return;
    }
    print_nl(262);
    print(1075);
    help_ptr = 3;
    help_line[2] = 1076;
    help_line[1] = 1077;
    help_line[0] = 1078;
    back_error();
  }
  void package(small_number c) {
    scaled h;
    halfword p;
    scaled d = eqtb[12737].int_;
    unsave();
    save_ptr -= 3;
    if (cur_list.mode_field == (-102)) {
      cur_box =
          hpack(mem[cur_list.head_field - mem_min].hh.rh,
                save_stack[save_ptr + 2].int_, save_stack[save_ptr + 1].int_);
    } else {
      (cur_box = vpackage(mem[cur_list.head_field - mem_min].hh.rh,
                          save_stack[save_ptr + 2].int_,
                          save_stack[save_ptr + 1].int_, d));
      if (c == 4) {
        h = 0;
        p = mem[cur_box - mem_min + 5].hh.rh;
        if (p != (-1073741824)) {
          if (mem[p - mem_min].hh.U2.b0 <= 2)
            h = mem[p - mem_min + 3].int_;
        }
        mem[cur_box - mem_min + 2].int_ += mem[cur_box - mem_min + 3].int_ - h;
        mem[cur_box - mem_min + 3].int_ = h;
      }
    }
    pop_nest();
    box_end(save_stack[save_ptr].int_);
  }
  small_number norm_min(integer h) {
    if (h <= 0) {
      return 1;
    } else if (h >= 63)
      return 63;
    else
      return h;
  }
  void new_graf(bool indented) {
    cur_list.pg_field = 0;
    if ((cur_list.mode_field == 1) ||
        (cur_list.head_field != cur_list.tail_field)) {
      mem[cur_list.tail_field - mem_min].hh.rh = new_param_glue(2);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    }
    push_nest();
    cur_list.mode_field = 102;
    cur_list.aux_field.hh.lh = 1000;
    if (eqtb[12213].int_ <= 0) {
      cur_lang = 0;
    } else if (eqtb[12213].int_ > 255)
      cur_lang = 0;
    else
      cur_lang = eqtb[12213].int_;
    cur_list.aux_field.hh.rh = cur_lang;
    cur_list.pg_field =
        (((norm_min(eqtb[12214].int_) * 64) + norm_min(eqtb[12215].int_)) *
         65536) +
        cur_lang;
    if (indented) {
      cur_list.tail_field = new_null_box();
      mem[cur_list.head_field - mem_min].hh.rh = cur_list.tail_field;
      mem[cur_list.tail_field - mem_min + 1].int_ = eqtb[12730].int_;
    }
    if (eqtb[10314].hh.rh != (-1073741824))
      begin_token_list(eqtb[10314].hh.rh, 7);
    if (nest_ptr == 1)
      build_page();
  }
  void indent_in_hmode() {
    halfword p, q;
    if (cur_chr <= 0)
      return;
    p = new_null_box();
    mem[p - mem_min + 1].int_ = eqtb[12730].int_;
    if (abs(cur_list.mode_field) == 102) {
      cur_list.aux_field.hh.lh = 1000;
    } else {
      q = new_noad();
      mem[q - mem_min + 1].hh.rh = 2;
      mem[q - mem_min + 1].hh.lh = p;
      p = q;
    }
    mem[cur_list.tail_field - mem_min].hh.rh = p;
    cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
  }
  void head_for_vmode() {
    if (cur_list.mode_field < 0) {
      if (cur_cmd != 36) {
        off_save();
        return;
      }
      print_nl(262);
      print(685);
      print_esc(521);
      print(1081);
      help_ptr = 2;
      help_line[1] = 1082;
      help_line[0] = 1083;
      error();
      return;
    }
    back_input();
    cur_tok = par_token;
    back_input();
    cur_input.index_field = 4;
  }
  void end_graf() {
    if (cur_list.mode_field != 102)
      return;
    if (cur_list.head_field == cur_list.tail_field)
      pop_nest();
    else
      line_break(eqtb[12169].int_);
    normal_paragraph();
    error_count = 0;
  }
  void begin_insert_or_adjust() {
    if (cur_cmd == 38) {
      cur_val = 255;
    } else {
      scan_eight_bit_int();
      if (cur_val == 255) {
        print_nl(262);
        print(1084);
        print_esc(330);
        print_int(255);
        help_ptr = 1;
        help_line[0] = 1085;
        error();
        cur_val = 0;
      }
    }
    save_stack[save_ptr].int_ = cur_val;
    ++save_ptr;
    new_save_level(11);
    scan_left_brace();
    normal_paragraph();
    push_nest();
    cur_list.mode_field = -1;
    cur_list.aux_field.int_ = -65536000;
  }
  void make_mark() {
    halfword p = scan_toks(false, true);
    p = get_node(2);
    mem[p - mem_min].hh.U2.b0 = 4;
    mem[p - mem_min].hh.U2.b1 = 0;
    mem[p - mem_min + 1].int_ = def_ref;
    mem[cur_list.tail_field - mem_min].hh.rh = p;
    cur_list.tail_field = p;
  }
  void append_penalty() {
    scan_int();
    mem[cur_list.tail_field - mem_min].hh.rh = new_penalty(cur_val);
    cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    if (cur_list.mode_field == 1)
      build_page();
  }
  void delete_last() {
    halfword p, q;
    quarterword m, N;
    if ((cur_list.mode_field == 1) &&
        (cur_list.tail_field == cur_list.head_field)) {
      if ((cur_chr != 10) || (last_glue != 1073741824)) {
        you_cant();
        help_ptr = 2;
        help_line[1] = 1070;
        help_line[0] = 1086;
        if (cur_chr == 11) {
          help_line[0] = 1087;
        } else if (cur_chr != 10)
          help_line[0] = 1088;
        error();
      }
    } else if (cur_list.tail_field < hi_mem_min) {
      if (mem[cur_list.tail_field - mem_min].hh.U2.b0 == cur_chr) {
        q = cur_list.head_field;
        do {
          p = q;
          if (q < hi_mem_min) {
            if (mem[q - mem_min].hh.U2.b0 == 7) {
              for (N = mem[q - mem_min].hh.U2.b1, m = 1; m <= N; ++m)
                p = mem[p - mem_min].hh.rh;
              if (p == cur_list.tail_field)
                goto _L10;
            }
          }
          q = mem[p - mem_min].hh.rh;
        } while (q != cur_list.tail_field);
        mem[p - mem_min].hh.rh = -1073741824;
        flush_node_list(cur_list.tail_field);
        cur_list.tail_field = p;
      }
    }
  _L10:;
  }
  void unpackage() {
    halfword p;
    char c = cur_chr;
    scan_eight_bit_int();
    p = eqtb[cur_val + 10578].hh.rh;
    if (p == (-1073741824))
      goto _L10;
    if ((abs(cur_list.mode_field) == 203) ||
        ((abs(cur_list.mode_field) == 1) && (mem[p - mem_min].hh.U2.b0 != 1)) ||
        ((abs(cur_list.mode_field) == 102) && mem[p - mem_min].hh.U2.b0)) {
      print_nl(262);
      print(1096);
      help_ptr = 3;
      help_line[2] = 1097;
      help_line[1] = 1098;
      help_line[0] = 1099;
      error();
      goto _L10;
    }
    if (c == 1) {
      mem[cur_list.tail_field - mem_min].hh.rh =
          copy_node_list(mem[p - mem_min + 5].hh.rh);
    } else {
      mem[cur_list.tail_field - mem_min].hh.rh = mem[p - mem_min + 5].hh.rh;
      eqtb[cur_val + 10578].hh.rh = -1073741824;
      free_node(p, 7);
    }
    while (mem[cur_list.tail_field - mem_min].hh.rh != (-1073741824))
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
  _L10:;
  }
  void append_italic_correction() {
    halfword p;
    internal_font_number f;
    if (cur_list.tail_field != cur_list.head_field) {
      if (cur_list.tail_field >= hi_mem_min) {
        p = cur_list.tail_field;
      } else if (mem[cur_list.tail_field - mem_min].hh.U2.b0 == 6)
        p = cur_list.tail_field + 1;
      else
        goto _L10;
      f = mem[p - mem_min].hh.U2.b0;
      (mem[cur_list.tail_field - mem_min].hh.rh = new_kern(
           font_info[italic_base[f] +
                     (font_info[char_base[f] + mem[p - mem_min].hh.U2.b1]
                          .qqqq.b2 /
                      4)]
               .int_));
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      mem[cur_list.tail_field - mem_min].hh.U2.b1 = 1;
    }
  _L10:;
  }
  void append_discretionary() {
    integer c;
    mem[cur_list.tail_field - mem_min].hh.rh = new_disc();
    cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    if (cur_chr == 1) {
      c = hyphen_char[eqtb[10834].hh.rh];
      if (c >= 0) {
        if (c < 256)
          mem[cur_list.tail_field - mem_min + 1].hh.lh =
              new_character(eqtb[10834].hh.rh, c);
      }
      return;
    }
    ++save_ptr;
    save_stack[save_ptr - 1].int_ = 0;
    new_save_level(10);
    scan_left_brace();
    push_nest();
    cur_list.mode_field = -102;
    cur_list.aux_field.hh.lh = 1000;
  }
  void build_discretionary() {
    halfword p, q;
    integer n = 0;
    unsave();
    q = cur_list.head_field;
    p = mem[q - mem_min].hh.rh;
    while (p != (-1073741824)) {
      if (p < hi_mem_min) {
        if (mem[p - mem_min].hh.U2.b0 > 2) {
          if (mem[p - mem_min].hh.U2.b0 != 11) {
            if (mem[p - mem_min].hh.U2.b0 != 6) {
              print_nl(262);
              print(1106);
              help_ptr = 1;
              help_line[0] = 1107;
              error();
              begin_diagnostic();
              print_nl(1108);
              show_box(p);
              end_diagnostic(true);
              flush_node_list(p);
              mem[q - mem_min].hh.rh = -1073741824;
              goto _L30;
            }
          }
        }
      }
      q = p;
      p = mem[q - mem_min].hh.rh;
      ++n;
    }
  _L30:
    p = mem[cur_list.head_field - mem_min].hh.rh;
    pop_nest();
    switch (save_stack[save_ptr - 1].int_) {
    case 0:
      mem[cur_list.tail_field - mem_min + 1].hh.lh = p;
      break;
    case 1:
      mem[cur_list.tail_field - mem_min + 1].hh.rh = p;
      break;
    case 2:
      if ((n > 0) && (abs(cur_list.mode_field) == 203)) {
        print_nl(262);
        print(1100);
        print_esc(349);
        help_ptr = 2;
        help_line[1] = 1101;
        help_line[0] = 1102;
        flush_node_list(p);
        n = 0;
        error();
      } else {
        mem[cur_list.tail_field - mem_min].hh.rh = p;
      }
      if (n <= 65535) {
        mem[cur_list.tail_field - mem_min].hh.U2.b1 = n;
      } else {
        print_nl(262);
        print(1103);
        help_ptr = 2;
        help_line[1] = 1104;
        help_line[0] = 1105;
        error();
      }
      if (n > 0)
        cur_list.tail_field = q;
      --save_ptr;
      goto _L10;
      break;
    }
    ++save_stack[save_ptr - 1].int_;
    new_save_level(10);
    scan_left_brace();
    push_nest();
    cur_list.mode_field = -102;
    cur_list.aux_field.hh.lh = 1000;
  _L10:;
  }
  void make_accent() {
    double s, t;
    halfword p, q = -1073741824, r;
    internal_font_number f;
    scaled a, h, x, w, delta;
    four_quarters i;
    scan_char_num();
    f = eqtb[10834].hh.rh;
    p = new_character(f, cur_val);
    if (p == (-1073741824))
      return;
    x = font_info[param_base[f] + 5].int_;
    s = font_info[param_base[f] + 1].int_ / 65536.0;
    a = font_info[width_base[f] +
                  font_info[char_base[f] + mem[p - mem_min].hh.U2.b1].qqqq.b0]
            .int_;
    do_assignments();
    f = eqtb[10834].hh.rh;
    if ((cur_cmd == 11) || (cur_cmd == 12) || (cur_cmd == 68)) {
      q = new_character(f, cur_chr);
    } else if (cur_cmd == 16) {
      scan_char_num();
      q = new_character(f, cur_val);
    } else {
      back_input();
    }
    if (q != (-1073741824)) {
      t = font_info[param_base[f] + 1].int_ / 65536.0;
      i = font_info[char_base[f] + mem[q - mem_min].hh.U2.b1].qqqq;
      w = font_info[width_base[f] + i.b0].int_;
      h = font_info[height_base[f] + (i.b1 / 16)].int_;
      if (h != x) {
        p = hpack(p, 0, 1);
        mem[p - mem_min + 4].int_ = x - h;
      }
      delta = int(round(((w - a) / 2.0) + (h * t) - (x * s)));
      r = new_kern(delta);
      mem[r - mem_min].hh.U2.b1 = 2;
      mem[cur_list.tail_field - mem_min].hh.rh = r;
      mem[r - mem_min].hh.rh = p;
      cur_list.tail_field = new_kern((-a) - delta);
      mem[cur_list.tail_field - mem_min].hh.U2.b1 = 2;
      mem[p - mem_min].hh.rh = cur_list.tail_field;
      p = q;
    }
    mem[cur_list.tail_field - mem_min].hh.rh = p;
    cur_list.tail_field = p;
    cur_list.aux_field.hh.lh = 1000;
  }
  void align_error() {
    if (abs(align_state) > 2) {
      print_nl(262);
      print(1113);
      print_cmd_chr(cur_cmd, cur_chr);
      if (cur_tok == 1062) {
        help_ptr = 6;
        help_line[5] = 1114;
        help_line[4] = 1115;
        help_line[3] = 1116;
        help_line[2] = 1117;
        help_line[1] = 1118;
        help_line[0] = 1119;
      } else {
        help_ptr = 5;
        help_line[4] = 1114;
        help_line[3] = 1120;
        help_line[2] = 1117;
        help_line[1] = 1118;
        help_line[0] = 1119;
      }
      error();
      return;
    }
    back_input();
    if (align_state < 0) {
      print_nl(262);
      print(657);
      ++align_state;
      cur_tok = 379;
    } else {
      print_nl(262);
      print(1109);
      --align_state;
      cur_tok = 637;
    }
    help_ptr = 3;
    help_line[2] = 1110;
    help_line[1] = 1111;
    help_line[0] = 1112;
    ins_error();
  }
  void no_align_error() {
    print_nl(262);
    print(1113);
    print_esc(527);
    help_ptr = 2;
    help_line[1] = 1121;
    help_line[0] = 1122;
    error();
  }
  void omit_error() {
    print_nl(262);
    print(1113);
    print_esc(530);
    help_ptr = 2;
    help_line[1] = 1123;
    help_line[0] = 1122;
    error();
  }
  void do_endv() {
    base_ptr = input_ptr;
    input_stack[base_ptr] = cur_input;
    while ((input_stack[base_ptr].index_field != 2) &&
           (input_stack[base_ptr].loc_field == (-1073741824)) &&
           (!input_stack[base_ptr].state_field))
      --base_ptr;
    if ((input_stack[base_ptr].index_field != 2) ||
        (input_stack[base_ptr].loc_field != (-1073741824)) ||
        input_stack[base_ptr].state_field)
      fatal_error(595);
    if (cur_group != 6) {
      off_save();
      return;
    }
    end_graf();
    if (fin_col())
      fin_row();
  }
  void cs_error() {
    print_nl(262);
    print(776);
    print_esc(505);
    help_ptr = 1;
    help_line[0] = 1125;
    error();
  }
  void push_math(group_code c) {
    push_nest();
    cur_list.mode_field = -203;
    cur_list.aux_field.int_ = -1073741824;
    new_save_level(c);
  }
  void init_math() {
    scaled w, l, s, v, d;
    halfword p, q;
    internal_font_number f;
    integer n;
    get_token();
    if ((cur_cmd == 3) && (cur_list.mode_field > 0)) {
      if (cur_list.head_field == cur_list.tail_field) {
        pop_nest();
        w = -1073741823;
      } else {
        line_break(eqtb[12170].int_);
        v = mem[just_box - mem_min + 4].int_ +
            (font_info[param_base[eqtb[10834].hh.rh] + 6].int_ * 2);
        w = -1073741823;
        p = mem[just_box - mem_min + 5].hh.rh;
        while (p != (-1073741824)) {
        _L21:
          if (p >= hi_mem_min) {
            f = mem[p - mem_min].hh.U2.b0;
            d = font_info[width_base[f] +
                          font_info[char_base[f] + mem[p - mem_min].hh.U2.b1]
                              .qqqq.b0]
                    .int_;
            goto _L40;
          }
          switch (mem[p - mem_min].hh.U2.b0) {
          case 0:
          case 1:
          case 2:
            d = mem[p - mem_min + 1].int_;
            goto _L40;
            break;
          case 6:
            mem[mem_max - mem_min - 12] = mem[p - mem_min + 1];
            mem[mem_max - mem_min - 12].hh.rh = mem[p - mem_min].hh.rh;
            p = mem_max - 12;
            goto _L21;
            break;
          case 11:
          case 9:
            d = mem[p - mem_min + 1].int_;
            break;
          case 10:
            q = mem[p - mem_min + 1].hh.lh;
            d = mem[q - mem_min + 1].int_;
            if (mem[just_box - mem_min + 5].hh.U2.b0 == 1) {
              if ((mem[just_box - mem_min + 5].hh.U2.b1 ==
                   mem[q - mem_min].hh.U2.b0) &&
                  mem[q - mem_min + 2].int_)
                v = 1073741823;
            } else if (mem[just_box - mem_min + 5].hh.U2.b0 == 2) {
              if ((mem[just_box - mem_min + 5].hh.U2.b1 ==
                   mem[q - mem_min].hh.U2.b1) &&
                  mem[q - mem_min + 3].int_)
                v = 1073741823;
            }
            if (mem[p - mem_min].hh.U2.b1 >= 100)
              goto _L40;
            break;
          case 8:
            d = 0;
            break;
          default:
            d = 0;
            break;
          }
          if (v < 1073741823)
            v += d;
          goto _L45;
        _L40:
          if (v >= 1073741823) {
            w = 1073741823;
            goto _L30;
          }
          v += d;
          w = v;
        _L45:
          p = mem[p - mem_min].hh.rh;
        }
      _L30:;
      }
      if (eqtb[10312].hh.rh == (-1073741824)) {
        if (eqtb[12747].int_ && (((eqtb[12204].int_ >= 0) &&
                                  (cur_list.pg_field + 2 > eqtb[12204].int_)) ||
                                 (cur_list.pg_field + 1 < -eqtb[12204].int_))) {
          l = eqtb[12733].int_ - abs(eqtb[12747].int_);
          if (eqtb[12747].int_ > 0)
            s = eqtb[12747].int_;
          else
            s = 0;
        } else {
          l = eqtb[12733].int_;
          s = 0;
        }
      } else {
        n = mem[eqtb[10312].hh.rh - mem_min].hh.lh;
        if (cur_list.pg_field + 2 >= n)
          p = eqtb[10312].hh.rh + (n * 2);
        else
          p = eqtb[10312].hh.rh + ((cur_list.pg_field + 2) * 2);
        s = mem[p - mem_min - 1].int_;
        l = mem[p - mem_min].int_;
      }
      push_math(15);
      cur_list.mode_field = 203;
      eq_word_define(12207, -1);
      eq_word_define(12743, w);
      eq_word_define(12744, l);
      eq_word_define(12745, s);
      if (eqtb[10316].hh.rh != (-1073741824))
        begin_token_list(eqtb[10316].hh.rh, 9);
      if (nest_ptr == 1)
        build_page();
      return;
    }
    back_input();
    push_math(15);
    eq_word_define(12207, -1);
    if (eqtb[10315].hh.rh != (-1073741824))
      begin_token_list(eqtb[10315].hh.rh, 8);
  }
  void start_eq_no() {
    save_stack[save_ptr].int_ = cur_chr;
    ++save_ptr;
    push_math(15);
    eq_word_define(12207, -1);
    if (eqtb[10315].hh.rh != (-1073741824))
      begin_token_list(eqtb[10315].hh.rh, 8);
  }
  void scan_math(halfword p) {
    integer c;
  _L20:
    do {
      get_x_token();
    } while ((cur_cmd == 10) || (!cur_cmd));
  _L21:
    switch (cur_cmd) {
    case 11:
    case 12:
    case 68:
      c = eqtb[cur_chr + 11907].hh.rh + 1073741824;
      if (c == 32768) {
        cur_cs = cur_chr + 1;
        cur_cmd = eqtb[cur_cs].hh.U2.b0;
        cur_chr = eqtb[cur_cs].hh.rh;
        x_token();
        back_input();
        goto _L20;
      }
      break;
    case 16:
      scan_char_num();
      cur_chr = cur_val;
      cur_cmd = 68;
      goto _L21;
      break;
    case 17:
      scan_fifteen_bit_int();
      c = cur_val;
      break;
    case 69:
      c = cur_chr;
      break;
    case 15:
      scan_twenty_seven_bit_int();
      c = cur_val / 4096;
      break;
    default:
      back_input();
      scan_left_brace();
      save_stack[save_ptr].int_ = p;
      ++save_ptr;
      push_math(9);
      goto _L10;
      break;
    }
    mem[p - mem_min].hh.rh = 1;
    mem[p - mem_min].hh.U2.b1 = c & 255;
    if ((c >= 28672) && (((unsigned)eqtb[12207].int_) < 16))
      mem[p - mem_min].hh.U2.b0 = eqtb[12207].int_;
    else
      mem[p - mem_min].hh.U2.b0 = (c / 256) & 15;
  _L10:;
  }
  void set_math_char(integer c) {
    halfword p;
    if (c >= 32768) {
      cur_cs = cur_chr + 1;
      cur_cmd = eqtb[cur_cs].hh.U2.b0;
      cur_chr = eqtb[cur_cs].hh.rh;
      x_token();
      back_input();
      return;
    }
    p = new_noad();
    mem[p - mem_min + 1].hh.rh = 1;
    mem[p - mem_min + 1].hh.U2.b1 = c & 255;
    mem[p - mem_min + 1].hh.U2.b0 = (c / 256) & 15;
    if (c >= 28672) {
      if (((unsigned)eqtb[12207].int_) < 16)
        mem[p - mem_min + 1].hh.U2.b0 = eqtb[12207].int_;
      mem[p - mem_min].hh.U2.b0 = 16;
    } else {
      mem[p - mem_min].hh.U2.b0 = (c / 4096) + 16;
    }
    mem[cur_list.tail_field - mem_min].hh.rh = p;
    cur_list.tail_field = p;
  }
  void math_limit_switch() {
    if (cur_list.head_field != cur_list.tail_field) {
      if (mem[cur_list.tail_field - mem_min].hh.U2.b0 == 17) {
        mem[cur_list.tail_field - mem_min].hh.U2.b1 = cur_chr;
        goto _L10;
      }
    }
    print_nl(262);
    print(1129);
    help_ptr = 1;
    help_line[0] = 1130;
    error();
  _L10:;
  }
  void scan_delimiter(halfword p, bool r) {
    if (r) {
      scan_twenty_seven_bit_int();
    } else {
      do {
        get_x_token();
      } while ((cur_cmd == 10) || (!cur_cmd));
      switch (cur_cmd) {
      case 11:
      case 12:
        cur_val = eqtb[cur_chr + 12474].int_;
        break;
      case 15:
        scan_twenty_seven_bit_int();
        break;
      default:
        cur_val = -1;
        break;
      }
    }
    if (cur_val < 0) {
      print_nl(262);
      print(1131);
      help_ptr = 6;
      help_line[5] = 1132;
      help_line[4] = 1133;
      help_line[3] = 1134;
      help_line[2] = 1135;
      help_line[1] = 1136;
      help_line[0] = 1137;
      back_error();
      cur_val = 0;
    }
    mem[p - mem_min].qqqq.b0 = (cur_val / 1048576) & 15;
    mem[p - mem_min].qqqq.b1 = (cur_val / 4096) & 255;
    mem[p - mem_min].qqqq.b2 = (cur_val / 256) & 15;
    mem[p - mem_min].qqqq.b3 = cur_val & 255;
  }
  void math_radical() {
    mem[cur_list.tail_field - mem_min].hh.rh = get_node(5);
    cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    mem[cur_list.tail_field - mem_min].hh.U2.b0 = 24;
    mem[cur_list.tail_field - mem_min].hh.U2.b1 = 0;
    mem[cur_list.tail_field - mem_min + 1].hh = empty_field;
    mem[cur_list.tail_field - mem_min + 3].hh = empty_field;
    mem[cur_list.tail_field - mem_min + 2].hh = empty_field;
    scan_delimiter(cur_list.tail_field + 4, true);
    scan_math(cur_list.tail_field + 1);
  }
  void math_ac() {
    if (cur_cmd == 45) {
      print_nl(262);
      print(1138);
      print_esc(523);
      print(1139);
      help_ptr = 2;
      help_line[1] = 1140;
      help_line[0] = 1141;
      error();
    }
    mem[cur_list.tail_field - mem_min].hh.rh = get_node(5);
    cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    mem[cur_list.tail_field - mem_min].hh.U2.b0 = 28;
    mem[cur_list.tail_field - mem_min].hh.U2.b1 = 0;
    mem[cur_list.tail_field - mem_min + 1].hh = empty_field;
    mem[cur_list.tail_field - mem_min + 3].hh = empty_field;
    mem[cur_list.tail_field - mem_min + 2].hh = empty_field;
    mem[cur_list.tail_field - mem_min + 4].hh.rh = 1;
    scan_fifteen_bit_int();
    mem[cur_list.tail_field - mem_min + 4].hh.U2.b1 = cur_val & 255;
    if ((cur_val >= 28672) && (((unsigned)eqtb[12207].int_) < 16))
      mem[cur_list.tail_field - mem_min + 4].hh.U2.b0 = eqtb[12207].int_;
    else
      mem[cur_list.tail_field - mem_min + 4].hh.U2.b0 = (cur_val / 256) & 15;
    scan_math(cur_list.tail_field + 1);
  }
  void append_choices() {
    mem[cur_list.tail_field - mem_min].hh.rh = new_choice();
    cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    ++save_ptr;
    save_stack[save_ptr - 1].int_ = 0;
    push_math(13);
    scan_left_brace();
  }
  halfword fin_mlist(halfword p) {
    halfword q;
    if (cur_list.aux_field.int_ != (-1073741824)) {
      mem[cur_list.aux_field.int_ - mem_min + 3].hh.rh = 3;
      mem[cur_list.aux_field.int_ - mem_min + 3].hh.lh =
          mem[cur_list.head_field - mem_min].hh.rh;
      if (p == (-1073741824)) {
        q = cur_list.aux_field.int_;
      } else {
        q = mem[cur_list.aux_field.int_ - mem_min + 2].hh.lh;
        if (mem[q - mem_min].hh.U2.b0 != 30)
          confusion(876);
        mem[cur_list.aux_field.int_ - mem_min + 2].hh.lh =
            mem[q - mem_min].hh.rh;
        mem[q - mem_min].hh.rh = cur_list.aux_field.int_;
        mem[cur_list.aux_field.int_ - mem_min].hh.rh = p;
      }
    } else {
      mem[cur_list.tail_field - mem_min].hh.rh = p;
      q = mem[cur_list.head_field - mem_min].hh.rh;
    }
    pop_nest();
    return q;
  }
  void build_choices() {
    halfword p;
    unsave();
    p = fin_mlist(-1073741824);
    switch (save_stack[save_ptr - 1].int_) {
    case 0:
      mem[cur_list.tail_field - mem_min + 1].hh.lh = p;
      break;
    case 1:
      mem[cur_list.tail_field - mem_min + 1].hh.rh = p;
      break;
    case 2:
      mem[cur_list.tail_field - mem_min + 2].hh.lh = p;
      break;
    case 3:
      mem[cur_list.tail_field - mem_min + 2].hh.rh = p;
      --save_ptr;
      goto _L10;
      break;
    }
    ++save_stack[save_ptr - 1].int_;
    push_math(13);
    scan_left_brace();
  _L10:;
  }
  void sub_sup() {
    small_number t = 0;
    halfword p = -1073741824;
    if (cur_list.tail_field != cur_list.head_field) {
      if ((mem[cur_list.tail_field - mem_min].hh.U2.b0 >= 16) &&
          (mem[cur_list.tail_field - mem_min].hh.U2.b0 < 30)) {
        p = cur_list.tail_field + cur_cmd - 5;
        t = mem[p - mem_min].hh.rh;
      }
    }
    if ((p == (-1073741824)) || t) {
      mem[cur_list.tail_field - mem_min].hh.rh = new_noad();
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      p = cur_list.tail_field + cur_cmd - 5;
      if (t) {
        if (cur_cmd == 7) {
          print_nl(262);
          print(1142);
          help_ptr = 1;
          help_line[0] = 1143;
        } else {
          print_nl(262);
          print(1144);
          help_ptr = 1;
          help_line[0] = 1145;
        }
        error();
      }
    }
    scan_math(p);
  }
  void math_fraction() {
    small_number c = cur_chr;
    if (cur_list.aux_field.int_ != (-1073741824)) {
      if (c >= 3) {
        scan_delimiter(mem_max - 12, false);
        scan_delimiter(mem_max - 12, false);
      }
      if (!(c % 3))
        scan_dimen(false, false, false);
      print_nl(262);
      print(1152);
      help_ptr = 3;
      help_line[2] = 1153;
      help_line[1] = 1154;
      help_line[0] = 1155;
      error();
      return;
    }
    cur_list.aux_field.int_ = get_node(6);
    mem[cur_list.aux_field.int_ - mem_min].hh.U2.b0 = 25;
    mem[cur_list.aux_field.int_ - mem_min].hh.U2.b1 = 0;
    mem[cur_list.aux_field.int_ - mem_min + 2].hh.rh = 3;
    mem[cur_list.aux_field.int_ - mem_min + 2].hh.lh =
        mem[cur_list.head_field - mem_min].hh.rh;
    mem[cur_list.aux_field.int_ - mem_min + 3].hh = empty_field;
    mem[cur_list.aux_field.int_ - mem_min + 4].qqqq = null_delimiter;
    mem[cur_list.aux_field.int_ - mem_min + 5].qqqq = null_delimiter;
    mem[cur_list.head_field - mem_min].hh.rh = -1073741824;
    cur_list.tail_field = cur_list.head_field;
    if (c >= 3) {
      scan_delimiter(cur_list.aux_field.int_ + 4, false);
      scan_delimiter(cur_list.aux_field.int_ + 5, false);
    }
    switch (c % 3) {
    case 0:
      scan_dimen(false, false, false);
      mem[cur_list.aux_field.int_ - mem_min + 1].int_ = cur_val;
      break;
    case 1:
      mem[cur_list.aux_field.int_ - mem_min + 1].int_ = 1073741824;
      break;
    case 2:
      mem[cur_list.aux_field.int_ - mem_min + 1].int_ = 0;
      break;
    }
  }
  void math_left_right() {
    halfword p;
    small_number t = cur_chr;
    if ((t == 31) && (cur_group != 16)) {
      if (cur_group != 15) {
        off_save();
        return;
      }
      scan_delimiter(mem_max - 12, false);
      print_nl(262);
      print(776);
      print_esc(876);
      help_ptr = 1;
      help_line[0] = 1156;
      error();
      return;
    }
    p = new_noad();
    mem[p - mem_min].hh.U2.b0 = t;
    scan_delimiter(p + 1, false);
    if (t == 30) {
      push_math(16);
      mem[cur_list.head_field - mem_min].hh.rh = p;
      cur_list.tail_field = p;
      return;
    }
    p = fin_mlist(p);
    unsave();
    mem[cur_list.tail_field - mem_min].hh.rh = new_noad();
    cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    mem[cur_list.tail_field - mem_min].hh.U2.b0 = 23;
    mem[cur_list.tail_field - mem_min + 1].hh.rh = 3;
    mem[cur_list.tail_field - mem_min + 1].hh.lh = p;
  }
  void after_math() {
    bool l = false, danger = false;
    integer m;
    halfword p, a, b;
    scaled w, z, e, q, d, s;
    small_number g1, g2;
    halfword r, t;
    if ((font_params[eqtb[10837].hh.rh] < 22) ||
        (font_params[eqtb[10853].hh.rh] < 22) ||
        (font_params[eqtb[10869].hh.rh] < 22)) {
      print_nl(262);
      print(1157);
      help_ptr = 3;
      help_line[2] = 1158;
      help_line[1] = 1159;
      help_line[0] = 1160;
      error();
      flush_math();
      danger = true;
    } else if ((font_params[eqtb[10838].hh.rh] < 13) ||
               (font_params[eqtb[10854].hh.rh] < 13) ||
               (font_params[eqtb[10870].hh.rh] < 13)) {
      print_nl(262);
      print(1161);
      help_ptr = 3;
      help_line[2] = 1162;
      help_line[1] = 1163;
      help_line[0] = 1164;
      error();
      flush_math();
      danger = true;
    }
    m = cur_list.mode_field;
    p = fin_mlist(-1073741824);
    if (cur_list.mode_field == (-m)) {
      get_x_token();
      if (cur_cmd != 3) {
        print_nl(262);
        print(1165);
        help_ptr = 2;
        help_line[1] = 1166;
        help_line[0] = 1167;
        back_error();
      }
      cur_mlist = p;
      cur_style = 2;
      mlist_penalties = false;
      mlist_to_hlist();
      a = hpack(mem[mem_max - mem_min - 3].hh.rh, 0, 1);
      unsave();
      --save_ptr;
      if (save_stack[save_ptr].int_ == 1)
        l = true;
      danger = false;
      if ((font_params[eqtb[10837].hh.rh] < 22) ||
          (font_params[eqtb[10853].hh.rh] < 22) ||
          (font_params[eqtb[10869].hh.rh] < 22)) {
        print_nl(262);
        print(1157);
        help_ptr = 3;
        help_line[2] = 1158;
        help_line[1] = 1159;
        help_line[0] = 1160;
        error();
        flush_math();
        danger = true;
      } else if ((font_params[eqtb[10838].hh.rh] < 13) ||
                 (font_params[eqtb[10854].hh.rh] < 13) ||
                 (font_params[eqtb[10870].hh.rh] < 13)) {
        print_nl(262);
        print(1161);
        help_ptr = 3;
        help_line[2] = 1162;
        help_line[1] = 1163;
        help_line[0] = 1164;
        error();
        flush_math();
        danger = true;
      }
      m = cur_list.mode_field;
      p = fin_mlist(-1073741824);
    } else {
      a = -1073741824;
    }
    if (m < 0) {
      mem[cur_list.tail_field - mem_min].hh.rh = new_math(eqtb[12731].int_, 0);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      cur_mlist = p;
      cur_style = 2;
      mlist_penalties = (cur_list.mode_field > 0);
      mlist_to_hlist();
      mem[cur_list.tail_field - mem_min].hh.rh =
          mem[mem_max - mem_min - 3].hh.rh;
      while (mem[cur_list.tail_field - mem_min].hh.rh != (-1073741824))
        cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      mem[cur_list.tail_field - mem_min].hh.rh = new_math(eqtb[12731].int_, 1);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      cur_list.aux_field.hh.lh = 1000;
      unsave();
      return;
    }
    if (a == (-1073741824)) {
      get_x_token();
      if (cur_cmd != 3) {
        print_nl(262);
        print(1165);
        help_ptr = 2;
        help_line[1] = 1166;
        help_line[0] = 1167;
        back_error();
      }
    }
    cur_mlist = p;
    cur_style = 0;
    mlist_penalties = false;
    mlist_to_hlist();
    p = mem[mem_max - mem_min - 3].hh.rh;
    adjust_tail = mem_max - 5;
    b = hpack(p, 0, 1);
    p = mem[b - mem_min + 5].hh.rh;
    t = adjust_tail;
    adjust_tail = -1073741824;
    w = mem[b - mem_min + 1].int_;
    z = eqtb[12744].int_;
    s = eqtb[12745].int_;
    if ((a == (-1073741824)) || danger) {
      e = 0;
      q = 0;
    } else {
      e = mem[a - mem_min + 1].int_;
      q = e + font_info[param_base[eqtb[10837].hh.rh] + 6].int_;
    }
    if (w + q > z) {
      if (e && ((w - total_shrink[0] + q <= z) || total_shrink[1] ||
                total_shrink[2] || total_shrink[3])) {
        free_node(b, 7);
        b = hpack(p, z - q, 0);
      } else {
        e = 0;
        if (w > z) {
          free_node(b, 7);
          b = hpack(p, z, 0);
        }
      }
      w = mem[b - mem_min + 1].int_;
    }
    d = half(z - w);
    if ((e > 0) && (d < (e * 2))) {
      d = half(z - w - e);
      if (p != (-1073741824)) {
        if (p < hi_mem_min) {
          if (mem[p - mem_min].hh.U2.b0 == 10)
            d = 0;
        }
      }
    }
    mem[cur_list.tail_field - mem_min].hh.rh = new_penalty(eqtb[12174].int_);
    cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    if ((d + s <= eqtb[12743].int_) || l) {
      g1 = 3;
      g2 = 4;
    } else {
      g1 = 5;
      g2 = 6;
    }
    if (l && (!e)) {
      mem[a - mem_min + 4].int_ = s;
      append_to_vlist(a);
      mem[cur_list.tail_field - mem_min].hh.rh = new_penalty(10000);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    } else {
      mem[cur_list.tail_field - mem_min].hh.rh = new_param_glue(g1);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    }
    if (e) {
      r = new_kern(z - w - e - d);
      if (l) {
        mem[a - mem_min].hh.rh = r;
        mem[r - mem_min].hh.rh = b;
        b = a;
        d = 0;
      } else {
        mem[b - mem_min].hh.rh = r;
        mem[r - mem_min].hh.rh = a;
      }
      b = hpack(b, 0, 1);
    }
    mem[b - mem_min + 4].int_ = s + d;
    append_to_vlist(b);
    if ((a != (-1073741824)) && (!e) && (!l)) {
      mem[cur_list.tail_field - mem_min].hh.rh = new_penalty(10000);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      mem[a - mem_min + 4].int_ = s + z - mem[a - mem_min + 1].int_;
      append_to_vlist(a);
      g2 = 0;
    }
    if (t != (mem_max - 5)) {
      mem[cur_list.tail_field - mem_min].hh.rh =
          mem[mem_max - mem_min - 5].hh.rh;
      cur_list.tail_field = t;
    }
    mem[cur_list.tail_field - mem_min].hh.rh = new_penalty(eqtb[12175].int_);
    cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    if (g2 > 0) {
      mem[cur_list.tail_field - mem_min].hh.rh = new_param_glue(g2);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    }
    resume_after_display();
  }
  void resume_after_display() {
    if (cur_group != 15)
      confusion(1168);
    unsave();
    cur_list.pg_field += 3;
    push_nest();
    cur_list.mode_field = 102;
    cur_list.aux_field.hh.lh = 1000;
    if (eqtb[12213].int_ <= 0) {
      cur_lang = 0;
    } else if (eqtb[12213].int_ > 255)
      cur_lang = 0;
    else
      cur_lang = eqtb[12213].int_;
    cur_list.aux_field.hh.rh = cur_lang;
    cur_list.pg_field =
        (((norm_min(eqtb[12214].int_) * 64) + norm_min(eqtb[12215].int_)) *
         65536) +
        cur_lang;
    get_x_token();
    if (cur_cmd != 10)
      back_input();
    if (nest_ptr == 1)
      build_page();
  }
  void get_r_token() {
  _L20:
    do {
      get_token();
    } while (cur_tok == 2592);
    if (cur_cs && (cur_cs <= 9514))
      return;
    print_nl(262);
    print(1183);
    help_ptr = 5;
    help_line[4] = 1184;
    help_line[3] = 1185;
    help_line[2] = 1186;
    help_line[1] = 1187;
    help_line[0] = 1188;
    if (!cur_cs)
      back_input();
    cur_tok = 13609;
    ins_error();
    goto _L20;
  }
  void trap_zero_glue() {
    if (mem[cur_val - mem_min + 1].int_ || mem[cur_val - mem_min + 2].int_ ||
        mem[cur_val - mem_min + 3].int_)
      return;
    ++mem[-mem_min].hh.rh;
    delete_glue_ref(cur_val);
    cur_val = 0;
  }
  void do_register_command(small_number a) {
    halfword l, r, s;
    char p;
    halfword q = cur_cmd;
    if (q != 89) {
      get_x_token();
      if ((cur_cmd >= 73) && (cur_cmd <= 76)) {
        l = cur_chr;
        p = cur_cmd - 73;
        goto _L40;
      }
      if (cur_cmd != 89) {
        print_nl(262);
        print(685);
        print_cmd_chr(cur_cmd, cur_chr);
        print(686);
        print_cmd_chr(q, 0);
        help_ptr = 1;
        help_line[0] = 1209;
        error();
        goto _L10;
      }
    }
    p = cur_chr;
    scan_eight_bit_int();
    switch (p) {
    case 0:
      l = cur_val + 12218;
      break;
    case 1:
      l = cur_val + 12751;
      break;
    case 2:
      l = cur_val + 9800;
      break;
    case 3:
      l = cur_val + 10056;
      break;
    }
  _L40:
    if (q == 89)
      scan_optional_equals();
    else
      scan_keyword(1205);
    arith_error = false;
    if (q < 91) {
      if (p < 2) {
        if (!p)
          scan_int();
        else
          scan_dimen(false, false, false);
        if (q == 90)
          cur_val += eqtb[l].int_;
      } else {
        scan_glue(p);
        if (q == 90) {
          q = new_spec(cur_val);
          r = eqtb[l].hh.rh;
          delete_glue_ref(cur_val);
          mem[q - mem_min + 1].int_ += mem[r - mem_min + 1].int_;
          if (!mem[q - mem_min + 2].int_)
            mem[q - mem_min].hh.U2.b0 = 0;
          if (mem[q - mem_min].hh.U2.b0 == mem[r - mem_min].hh.U2.b0) {
            mem[q - mem_min + 2].int_ += mem[r - mem_min + 2].int_;
          } else if ((mem[q - mem_min].hh.U2.b0 < mem[r - mem_min].hh.U2.b0) &&
                     mem[r - mem_min + 2].int_) {
            mem[q - mem_min + 2].int_ = mem[r - mem_min + 2].int_;
            mem[q - mem_min].hh.U2.b0 = mem[r - mem_min].hh.U2.b0;
          }
          if (!mem[q - mem_min + 3].int_)
            mem[q - mem_min].hh.U2.b1 = 0;
          if (mem[q - mem_min].hh.U2.b1 == mem[r - mem_min].hh.U2.b1) {
            mem[q - mem_min + 3].int_ += mem[r - mem_min + 3].int_;
          } else if ((mem[q - mem_min].hh.U2.b1 < mem[r - mem_min].hh.U2.b1) &&
                     mem[r - mem_min + 3].int_) {
            mem[q - mem_min + 3].int_ = mem[r - mem_min + 3].int_;
            mem[q - mem_min].hh.U2.b1 = mem[r - mem_min].hh.U2.b1;
          }
          cur_val = q;
        }
      }
    } else {
      scan_int();
      if (p < 2) {
        if (q == 91) {
          if (!p)
            cur_val = mult_and_add(eqtb[l].int_, cur_val, 0, 2147483647);
          else
            cur_val = mult_and_add(eqtb[l].int_, cur_val, 0, 1073741823);
        } else {
          cur_val = x_over_n(eqtb[l].int_, cur_val);
        }
      } else {
        s = eqtb[l].hh.rh;
        r = new_spec(s);
        if (q == 91) {
          mem[r - mem_min + 1].int_ =
              mult_and_add(mem[s - mem_min + 1].int_, cur_val, 0, 1073741823);
          mem[r - mem_min + 2].int_ =
              mult_and_add(mem[s - mem_min + 2].int_, cur_val, 0, 1073741823);
          mem[r - mem_min + 3].int_ =
              mult_and_add(mem[s - mem_min + 3].int_, cur_val, 0, 1073741823);
        } else {
          mem[r - mem_min + 1].int_ =
              x_over_n(mem[s - mem_min + 1].int_, cur_val);
          mem[r - mem_min + 2].int_ =
              x_over_n(mem[s - mem_min + 2].int_, cur_val);
          mem[r - mem_min + 3].int_ =
              x_over_n(mem[s - mem_min + 3].int_, cur_val);
        }
        cur_val = r;
      }
    }
    if (arith_error) {
      print_nl(262);
      print(1206);
      help_ptr = 2;
      help_line[1] = 1207;
      help_line[0] = 1208;
      if (p >= 2)
        delete_glue_ref(cur_val);
      error();
      goto _L10;
    }
    if (p < 2) {
      if (a >= 4)
        geq_word_define(l, cur_val);
      else
        eq_word_define(l, cur_val);
    } else {
      trap_zero_glue();
      if (a >= 4)
        geq_define(l, 117, cur_val);
      else
        eq_define(l, 117, cur_val);
    }
  _L10:;
  }
  void alter_aux() {
    halfword c;
    if (cur_chr != abs(cur_list.mode_field)) {
      report_illegal_case();
      return;
    }
    c = cur_chr;
    scan_optional_equals();
    if (c == 1) {
      scan_dimen(false, false, false);
      cur_list.aux_field.int_ = cur_val;
      return;
    }
    scan_int();
    if ((cur_val > 0) && (cur_val <= 32767)) {
      cur_list.aux_field.hh.lh = cur_val;
      return;
    }
    print_nl(262);
    print(1212);
    help_ptr = 1;
    help_line[0] = 1213;
    int_error(cur_val);
  }
  void alter_prev_graf() {
    int p;
    nest[nest_ptr] = cur_list;
    p = nest_ptr;
    while (abs(nest[p].mode_field) != 1)
      --p;
    scan_optional_equals();
    scan_int();
    if (cur_val >= 0) {
      nest[p].pg_field = cur_val;
      cur_list = nest[nest_ptr];
      return;
    }
    print_nl(262);
    print(954);
    print_esc(532);
    help_ptr = 1;
    help_line[0] = 1214;
    int_error(cur_val);
  }
  void alter_page_so_far() {
    char c = cur_chr;
    scan_optional_equals();
    scan_dimen(false, false, false);
    page_so_far[c] = cur_val;
  }
  void alter_integer() {
    char c = cur_chr;
    scan_optional_equals();
    scan_int();
    if (!c)
      dead_cycles = cur_val;
    else
      insert_penalties = cur_val;
  }
  void alter_box_dimen() {
    eight_bits b;
    small_number c = cur_chr;
    scan_eight_bit_int();
    b = cur_val;
    scan_optional_equals();
    scan_dimen(false, false, false);
    if (eqtb[b + 10578].hh.rh != (-1073741824))
      mem[eqtb[b + 10578].hh.rh + c - mem_min].int_ = cur_val;
  }
  void new_font(small_number a) {
    halfword u;
    scaled s;
    internal_font_number f;
    str_number t;
    char old_setting;
    str_number flushable_string;
    internal_font_number N;
    if (!job_name)
      open_log_file();
    get_r_token();
    u = cur_cs;
    if (u >= 514) {
      t = hash[u - 514].rh;
    } else if (u >= 257) {
      if (u == 513)
        t = 1218;
      else
        t = u - 257;
    } else {
      old_setting = selector;
      selector = 21;
      print(1218);
      print(u - 1);
      selector = old_setting;
      if (pool_ptr + 1 > pool_size)
        overflow(257, pool_size - init_pool_ptr);
      t = make_string();
    }
    if (a >= 4)
      geq_define(u, 87, 0);
    else
      eq_define(u, 87, 0);
    scan_optional_equals();
    scan_file_name();
    name_in_progress = true;
    if (scan_keyword(1219)) {
      scan_dimen(false, false, false);
      s = cur_val;
      if ((s <= 0) || (s >= 134217728)) {
        print_nl(262);
        print(1221);
        print_scaled(s);
        print(1222);
        help_ptr = 2;
        help_line[1] = 1223;
        help_line[0] = 1224;
        error();
        s = 655360;
      }
    } else if (scan_keyword(1220)) {
      scan_int();
      s = -cur_val;
      if ((cur_val <= 0) || (cur_val > 32768)) {
        print_nl(262);
        print(552);
        help_ptr = 1;
        help_line[0] = 553;
        int_error(cur_val);
        s = -1000;
      }
    } else {
      s = -1000;
    }
    name_in_progress = false;
    flushable_string = str_ptr - 1;
    for (N = font_ptr, f = 1; f <= N; ++f) {
      if (str_eq_str(font_name[f], cur_name) &
          str_eq_str(font_area[f], cur_area)) {
        if (cur_name == flushable_string) {
          --str_ptr;
          pool_ptr = str_start[str_ptr];
          cur_name = font_name[f];
        }
        if (s > 0) {
          if (s == font_size[f])
            goto _L50;
        } else if (font_size[f] == xn_over_d(font_dsize[f], -s, 1000))
          goto _L50;
      }
    }
    f = read_font_info(u, cur_name, cur_area, s);
  _L50:
    eqtb[u].hh.rh = f;
    eqtb[f + 9524] = eqtb[u];
    hash[f + 9010].rh = t;
  }
  void new_interaction() {
    print_ln();
    interaction = cur_chr;
    if (!interaction)
      selector = 16;
    else
      selector = 17;
    if (log_opened)
      selector += 2;
  }
  void prefixed_command() {
    small_number a = 0;
    internal_font_number f;
    halfword j;
    font_index k;
    halfword p, q;
    integer n;
    bool e;
    while (cur_cmd == 93) {
      if (!((a / cur_chr) & 1))
        a += cur_chr;
      do {
        get_x_token();
      } while ((cur_cmd == 10) || (!cur_cmd));
      if (cur_cmd > 70)
        continue;
      print_nl(262);
      print(1178);
      print_cmd_chr(cur_cmd, cur_chr);
      print_char(39);
      help_ptr = 1;
      help_line[0] = 1179;
      back_error();
      goto _L10;
    }
    if ((cur_cmd != 97) && (a & 3)) {
      print_nl(262);
      print(685);
      print_esc(1170);
      print(1180);
      print_esc(1171);
      print(1181);
      print_cmd_chr(cur_cmd, cur_chr);
      print_char(39);
      help_ptr = 1;
      help_line[0] = 1182;
      error();
    }
    if (eqtb[12206].int_) {
      if (eqtb[12206].int_ < 0) {
        if (a >= 4)
          a -= 4;
      } else if (a < 4)
        a += 4;
    }
    switch (cur_cmd) {
    case 87:
      if (a >= 4)
        geq_define(10834, 120, cur_chr);
      else
        eq_define(10834, 120, cur_chr);
      break;
    case 97:
      if ((cur_chr & 1) && (a < 4) && (eqtb[12206].int_ >= 0))
        a += 4;
      e = (cur_chr >= 2);
      get_r_token();
      p = cur_cs;
      q = scan_toks(true, e);
      if (a >= 4)
        geq_define(p, (a & 3) + 111, def_ref);
      else
        eq_define(p, (a & 3) + 111, def_ref);
      break;
    case 94:
      n = cur_chr;
      get_r_token();
      p = cur_cs;
      if (!n) {
        do {
          get_token();
        } while (cur_cmd == 10);
        if (cur_tok == 3133) {
          get_token();
          if (cur_cmd == 10)
            get_token();
        }
      } else {
        get_token();
        q = cur_tok;
        get_token();
        back_input();
        cur_tok = q;
        back_input();
      }
      if (cur_cmd >= 111)
        ++mem[cur_chr - mem_min].hh.lh;
      if (a >= 4)
        geq_define(p, cur_cmd, cur_chr);
      else
        eq_define(p, cur_cmd, cur_chr);
      break;
    case 95:
      n = cur_chr;
      get_r_token();
      p = cur_cs;
      if (a >= 4)
        geq_define(p, 0, 256);
      else
        eq_define(p, 0, 256);
      scan_optional_equals();
      switch (n) {
      case 0:
        scan_char_num();
        if (a >= 4)
          geq_define(p, 68, cur_val);
        else
          eq_define(p, 68, cur_val);
        break;
      case 1:
        scan_fifteen_bit_int();
        if (a >= 4)
          geq_define(p, 69, cur_val);
        else
          eq_define(p, 69, cur_val);
        break;
      default:
        scan_eight_bit_int();
        switch (n) {
        case 2:
          if (a >= 4)
            geq_define(p, 73, cur_val + 12218);
          else
            eq_define(p, 73, cur_val + 12218);
          break;
        case 3:
          if (a >= 4)
            geq_define(p, 74, cur_val + 12751);
          else
            eq_define(p, 74, cur_val + 12751);
          break;
        case 4:
          if (a >= 4)
            geq_define(p, 75, cur_val + 9800);
          else
            eq_define(p, 75, cur_val + 9800);
          break;
        case 5:
          if (a >= 4)
            geq_define(p, 76, cur_val + 10056);
          else
            eq_define(p, 76, cur_val + 10056);
          break;
        case 6:
          if (a >= 4)
            geq_define(p, 72, cur_val + 10322);
          else
            eq_define(p, 72, cur_val + 10322);
          break;
        }
        break;
      }
      break;
    case 96:
      scan_int();
      n = cur_val;
      if (!scan_keyword(841)) {
        print_nl(262);
        print(1072);
        help_ptr = 2;
        help_line[1] = 1199;
        help_line[0] = 1200;
        error();
      }
      get_r_token();
      p = cur_cs;
      read_toks(n, p);
      if (a >= 4)
        geq_define(p, 111, cur_val);
      else
        eq_define(p, 111, cur_val);
      break;
    case 71:
    case 72:
      q = cur_cs;
      if (cur_cmd == 71) {
        scan_eight_bit_int();
        p = cur_val + 10322;
      } else {
        p = cur_chr;
      }
      scan_optional_equals();
      do {
        get_x_token();
      } while ((cur_cmd == 10) || (!cur_cmd));
      if (cur_cmd != 1) {
        if (cur_cmd == 71) {
          scan_eight_bit_int();
          cur_cmd = 72;
          cur_chr = cur_val + 10322;
        }
        if (cur_cmd == 72) {
          q = eqtb[cur_chr].hh.rh;
          if (q == (-1073741824)) {
            if (a >= 4)
              geq_define(p, 101, -1073741824);
            else
              eq_define(p, 101, -1073741824);
          } else {
            ++mem[q - mem_min].hh.lh;
            if (a >= 4)
              geq_define(p, 111, q);
            else
              eq_define(p, 111, q);
          }
          goto _L30;
        }
      }
      back_input();
      cur_cs = q;
      q = scan_toks(false, false);
      if (mem[def_ref - mem_min].hh.rh == (-1073741824)) {
        if (a >= 4)
          geq_define(p, 101, -1073741824);
        else
          eq_define(p, 101, -1073741824);
        mem[def_ref - mem_min].hh.rh = avail;
        avail = def_ref;
      } else {
        if (p == 10313) {
          mem[q - mem_min].hh.rh = get_avail();
          q = mem[q - mem_min].hh.rh;
          mem[q - mem_min].hh.lh = 637;
          q = get_avail();
          mem[q - mem_min].hh.lh = 379;
          mem[q - mem_min].hh.rh = mem[def_ref - mem_min].hh.rh;
          mem[def_ref - mem_min].hh.rh = q;
        }
        if (a >= 4)
          geq_define(p, 111, def_ref);
        else
          eq_define(p, 111, def_ref);
      }
      break;
    case 73:
      p = cur_chr;
      scan_optional_equals();
      scan_int();
      if (a >= 4)
        geq_word_define(p, cur_val);
      else
        eq_word_define(p, cur_val);
      break;
    case 74:
      p = cur_chr;
      scan_optional_equals();
      scan_dimen(false, false, false);
      if (a >= 4)
        geq_word_define(p, cur_val);
      else
        eq_word_define(p, cur_val);
      break;
    case 75:
    case 76:
      p = cur_chr;
      n = cur_cmd;
      scan_optional_equals();
      if (n == 76)
        scan_glue(3);
      else
        scan_glue(2);
      trap_zero_glue();
      if (a >= 4)
        geq_define(p, 117, cur_val);
      else
        eq_define(p, 117, cur_val);
      break;
    case 85:
      if (cur_chr == 10883) {
        n = 15;
      } else if (cur_chr == 11907) {
        n = 32768;
      } else if (cur_chr == 11651) {
        n = 32767;
      } else if (cur_chr == 12474)
        n = 16777215;
      else
        n = 255;
      p = cur_chr;
      scan_char_num();
      p += cur_val;
      scan_optional_equals();
      scan_int();
      if (((cur_val < 0) && (p < 12474)) || (cur_val > n)) {
        print_nl(262);
        print(1201);
        print_int(cur_val);
        if (p < 12474)
          print(1202);
        else
          print(1203);
        print_int(n);
        help_ptr = 1;
        help_line[0] = 1204;
        error();
        cur_val = 0;
      }
      if (p < 11907) {
        if (a >= 4)
          geq_define(p, 120, cur_val);
        else
          eq_define(p, 120, cur_val);
      } else if (p < 12474) {
        if (a >= 4)
          geq_define(p, 120, cur_val - 1073741824);
        else
          eq_define(p, 120, cur_val - 1073741824);
      } else if (a >= 4)
        geq_word_define(p, cur_val);
      else
        eq_word_define(p, cur_val);
      break;
    case 86:
      p = cur_chr;
      scan_four_bit_int();
      p += cur_val;
      scan_optional_equals();
      scan_font_ident();
      if (a >= 4)
        geq_define(p, 120, cur_val);
      else
        eq_define(p, 120, cur_val);
      break;
    case 89:
    case 90:
    case 91:
    case 92:
      do_register_command(a);
      break;
    case 98:
      scan_eight_bit_int();
      if (a >= 4)
        n = cur_val + 256;
      else
        n = cur_val;
      scan_optional_equals();
      if (set_box_allowed) {
        scan_box(n + 1073741824);
      } else {
        print_nl(262);
        print(680);
        print_esc(536);
        help_ptr = 2;
        help_line[1] = 1210;
        help_line[0] = 1211;
        error();
      }
      break;
    case 79:
      alter_aux();
      break;
    case 80:
      alter_prev_graf();
      break;
    case 81:
      alter_page_so_far();
      break;
    case 82:
      alter_integer();
      break;
    case 83:
      alter_box_dimen();
      break;
    case 84:
      scan_optional_equals();
      scan_int();
      n = cur_val;
      if (n <= 0) {
        p = -1073741824;
      } else {
        p = get_node((n * 2) + 1);
        mem[p - mem_min].hh.lh = n;
        for (j = 1; j <= n; ++j) {
          scan_dimen(false, false, false);
          mem[p + (j * 2) - mem_min - 1].int_ = cur_val;
          scan_dimen(false, false, false);
          mem[p + (j * 2) - mem_min].int_ = cur_val;
        }
      }
      if (a >= 4)
        geq_define(10312, 118, p);
      else
        eq_define(10312, 118, p);
      break;
    case 99:
      if (cur_chr == 1) {
        new_patterns();
        goto _L30;
      } else {
        new_hyph_exceptions();
        goto _L30;
      }
      break;
    case 77:
      find_font_dimen(true);
      k = cur_val;
      scan_optional_equals();
      scan_dimen(false, false, false);
      font_info[k].int_ = cur_val;
      break;
    case 78:
      n = cur_chr;
      scan_font_ident();
      f = cur_val;
      scan_optional_equals();
      scan_int();
      if (!n)
        hyphen_char[f] = cur_val;
      else
        skew_char[f] = cur_val;
      break;
    case 88:
      new_font(a);
      break;
    case 100:
      new_interaction();
      break;
    default:
      confusion(1177);
      break;
    }
  _L30:
    if (after_token) {
      cur_tok = after_token;
      back_input();
      after_token = 0;
    }
  _L10:;
  }
  void do_assignments() {
    while (true) {
      do {
        get_x_token();
      } while ((cur_cmd == 10) || (!cur_cmd));
      if (cur_cmd <= 70)
        goto _L10;
      set_box_allowed = false;
      prefixed_command();
      set_box_allowed = true;
    }
  _L10:;
  }
  void open_or_close_in() {
    char n;
    char c = cur_chr;
    scan_four_bit_int();
    n = cur_val;
    if (read_open[n] != 2) {
      a_close(read_file[n]);
      read_open[n] = 2;
    }
    if (!c)
      return;
    scan_optional_equals();
    scan_file_name();
    if (cur_ext == 338)
      cur_ext = 790;
    pack_file_name(cur_name, cur_area, cur_ext);
    if (a_open_in(read_file[n]))
      read_open[n] = 1;
  }
  void issue_message() {
    char old_setting;
    str_number s;
    char c = cur_chr;
    mem[mem_max - mem_min - 12].hh.rh = scan_toks(false, true);
    old_setting = selector;
    selector = 21;
    token_show(def_ref);
    selector = old_setting;
    flush_list(def_ref);
    if (pool_ptr + 1 > pool_size)
      overflow(257, pool_size - init_pool_ptr);
    s = make_string();
    if (!c) {
      if (term_offset + str_start[s + 1] - str_start[s] > max_print_line - 2) {
        print_ln();
      } else if ((term_offset > 0) || (file_offset > 0))
        print_char(32);
      slow_print(s);
      fflush(term_out);
      errno = 0;
    } else {
      print_nl(262);
      print(338);
      slow_print(s);
      if (eqtb[10321].hh.rh != (-1073741824)) {
        use_err_help = true;
      } else if (long_help_seen) {
        help_ptr = 1;
        help_line[0] = 1231;
      } else {
        if (interaction < 3)
          long_help_seen = true;
        help_ptr = 4;
        help_line[3] = 1232;
        help_line[2] = 1233;
        help_line[1] = 1234;
        help_line[0] = 1235;
      }
      error();
      use_err_help = false;
    }
    --str_ptr;
    pool_ptr = str_start[str_ptr];
  }
  void shift_case() {
    halfword t;
    eight_bits c;
    halfword b = cur_chr;
    halfword p = scan_toks(false, false);
    p = mem[def_ref - mem_min].hh.rh;
    while (p != (-1073741824)) {
      t = mem[p - mem_min].hh.lh;
      if (t < 4352) {
        c = t & 255;
        if (eqtb[b + c].hh.rh)
          mem[p - mem_min].hh.lh = t - c + eqtb[b + c].hh.rh;
      }
      p = mem[p - mem_min].hh.rh;
    }
    begin_token_list(mem[def_ref - mem_min].hh.rh, 3);
    mem[def_ref - mem_min].hh.rh = avail;
    avail = def_ref;
  }
  void show_whatever() {
    halfword p;
    switch (cur_chr) {
    case 3:
      begin_diagnostic();
      show_activities();
      break;
    case 1:
      scan_eight_bit_int();
      begin_diagnostic();
      print_nl(1253);
      print_int(cur_val);
      print_char(61);
      if (eqtb[cur_val + 10578].hh.rh == (-1073741824))
        print(410);
      else
        show_box(eqtb[cur_val + 10578].hh.rh);
      break;
    case 0:
      get_token();
      print_nl(1247);
      if (cur_cs) {
        sprint_cs(cur_cs);
        print_char(61);
      }
      print_meaning();
      goto _L50;
      break;
    default:
      p = the_toks();
      print_nl(1247);
      token_show(mem_max - 3);
      flush_list(mem[mem_max - mem_min - 3].hh.rh);
      goto _L50;
      break;
    }
    end_diagnostic(true);
    print_nl(262);
    print(1254);
    if (selector == 19) {
      if (eqtb[12192].int_ <= 0) {
        selector = 17;
        print(1255);
        selector = 19;
      }
    }
  _L50:
    if (interaction < 3) {
      help_ptr = 0;
      --error_count;
    } else if (eqtb[12192].int_ > 0) {
      help_ptr = 3;
      help_line[2] = 1242;
      help_line[1] = 1243;
      help_line[0] = 1244;
    } else {
      help_ptr = 5;
      help_line[4] = 1242;
      help_line[3] = 1243;
      help_line[2] = 1244;
      help_line[1] = 1245;
      help_line[0] = 1246;
    }
    error();
  }
  void store_fmt_file() {
    integer j, k, l, x = 0;
    halfword p = 0, q;
    four_quarters w;
    int N;
    halfword N1;
    if (save_ptr) {
      print_nl(262);
      print(1257);
      help_ptr = 1;
      help_line[0] = 1258;
      if (interaction == 3)
        interaction = 2;
      if (log_opened)
        error();
      history = 3;
      jump_out();
    }
    selector = 21;
    print(1271);
    print(job_name);
    print_char(32);
    print_int(eqtb[12186].int_);
    print_char(46);
    print_int(eqtb[12185].int_);
    print_char(46);
    print_int(eqtb[12184].int_);
    print_char(41);
    if (!interaction)
      selector = 18;
    else
      selector = 19;
    if (pool_ptr + 1 > pool_size)
      overflow(257, pool_size - init_pool_ptr);
    format_ident = make_string();
    pack_job_name(785);
    while (!w_open_out(fmt_file))
      prompt_file_name(1272, 785);
    print_nl(1273);
    slow_print(w_make_name_string(fmt_file));
    --str_ptr;
    pool_ptr = str_start[str_ptr];
    print_nl(338);
    slow_print(format_ident);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        117275187;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ = 0;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        mem_max;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ = 13006;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ = 7649;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ = 307;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        pool_ptr;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        str_ptr;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    for (N = str_ptr, k = 0; k <= N; ++k) {
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          str_start[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    }
    k = 0;
    while (k + 4 < pool_ptr) {
      w.b0 = str_pool[k];
      w.b1 = str_pool[k + 1];
      w.b2 = str_pool[k + 2];
      w.b3 = str_pool[k + 3];
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).qqqq = w;
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      k += 4;
    }
    k = pool_ptr - 4;
    w.b0 = str_pool[k];
    w.b1 = str_pool[k + 1];
    w.b2 = str_pool[k + 2];
    w.b3 = str_pool[k + 3];
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).qqqq = w;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    print_ln();
    print_int(str_ptr);
    print(1259);
    print_int(pool_ptr);
    sort_avail();
    var_used = 0;
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        lo_mem_max;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ = rover;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    q = rover;
    do {
      for (k = p; k <= (q + 1); ++k)
        fwrite((&mem[k - mem_min]), sizeof(memory_word), 1, fmt_file);

      x += q - p + 2;
      var_used += q - p;
      p = q + mem[q - mem_min].hh.lh;
      q = mem[q - mem_min + 1].hh.rh;
    } while (q != rover);
    var_used += lo_mem_max - p;
    dyn_used = mem_end - hi_mem_min + 1;
    for (N = lo_mem_max, k = p; k <= N; ++k)
      fwrite((&mem[k - mem_min]), sizeof(memory_word), 1, fmt_file);
    x += lo_mem_max - p + 1;
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        hi_mem_min;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ = avail;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    for (N = mem_end, k = hi_mem_min; k <= N; ++k)
      fwrite((&mem[k - mem_min]), sizeof(memory_word), 1, fmt_file);
    x += mem_end - hi_mem_min + 1;
    p = avail;
    while (p != (-1073741824)) {
      --dyn_used;
      p = mem[p - mem_min].hh.rh;
    }
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        var_used;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        dyn_used;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    print_ln();
    print_int(x);
    print(1260);
    print_int(var_used);
    print_char(38);
    print_int(dyn_used);
    k = 1;
    do {
      j = k;
      while (j < 12162) {
        if ((eqtb[j].hh.rh == eqtb[j + 1].hh.rh) &&
            (eqtb[j].hh.U2.b0 == eqtb[j + 1].hh.U2.b0) &&
            (eqtb[j].hh.U2.b1 == eqtb[j + 1].hh.U2.b1))
          goto _L41;
        ++j;
      }
      l = 12163;
      goto _L31;
    _L41:
      ++j;
      l = j;
      while (j < 12162) {
        if ((eqtb[j].hh.rh != eqtb[j + 1].hh.rh) ||
            (eqtb[j].hh.U2.b0 != eqtb[j + 1].hh.U2.b0) ||
            (eqtb[j].hh.U2.b1 != eqtb[j + 1].hh.U2.b1))
          goto _L31;
        ++j;
      }
    _L31:
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          l - k;
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      while (k < l) {
        fwrite((&eqtb[k]), sizeof(memory_word), 1, fmt_file);
        ++k;
      }
      k = j + 1;
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          k - l;
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    } while (k != 12163);
    do {
      j = k;
      while (j < 13006) {
        if (eqtb[j].int_ == eqtb[j + 1].int_)
          goto _L42;
        ++j;
      }
      l = 13007;
      goto _L32;
    _L42:
      ++j;
      l = j;
      while (j < 13006) {
        if (eqtb[j].int_ != eqtb[j + 1].int_)
          goto _L32;
        ++j;
      }
    _L32:
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          l - k;
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      while (k < l) {
        fwrite((&eqtb[k]), sizeof(memory_word), 1, fmt_file);
        ++k;
      }
      k = j + 1;
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          k - l;
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    } while (k <= 13006);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        par_loc;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        write_loc;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        hash_used;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    cs_count = 9513 - hash_used;
    for (N1 = hash_used, p = 514; p <= N1; ++p) {
      if (hash[p - 514].rh) {
        readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ = p;
        writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
        readU32(fmt_file, fmt_file_mode, &fmt_file_value).hh =
            hash[p - 514];
        writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
        ++cs_count;
      }
    }
    for (p = hash_used + 1; p <= 9780; ++p) {
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).hh =
          hash[p - 514];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    }
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        cs_count;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    print_ln();
    print_int(cs_count);
    print(1261);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        fmem_ptr;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    for (N = fmem_ptr, k = 0; k < N; ++k)
      fwrite((&font_info[k]), sizeof(memory_word), 1, fmt_file);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        font_ptr;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    for (N = font_ptr, k = 0; k <= N; ++k) {
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).qqqq =
          font_check[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          font_size[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          font_dsize[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          font_params[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          hyphen_char[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          skew_char[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          font_name[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          font_area[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          font_bc[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          font_ec[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          char_base[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          width_base[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          height_base[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          depth_base[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          italic_base[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          lig_kern_base[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          kern_base[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          exten_base[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          param_base[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          font_glue[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          bchar_label[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          font_bchar[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          font_false_bchar[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      print_nl(1264);
      print_esc(hash[k + 9010].rh);
      print_char(61);
      print_file_name(font_name[k], font_area[k], 338);
      if (font_size[k] != font_dsize[k]) {
        print(741);
        print_scaled(font_size[k]);
        print(397);
      }
    }
    print_ln();
    print_int(fmem_ptr - 7);
    print(1262);
    print_int(font_ptr);
    print(1263);
    if (font_ptr != 1)
      print_char(115);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        hyph_count;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    for (k = 0; k <= 307; ++k) {
      if (hyph_word[k]) {
        readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ = k;
        writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
        readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
            hyph_word[k];
        writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
        readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
            hyph_list[k];
        writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      }
    }
    print_ln();
    print_int(hyph_count);
    print(1265);
    if (hyph_count != 1)
      print_char(115);
    if (trie_not_ready)
      init_trie();
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        trie_max;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    for (N = trie_max, k = 0; k <= N; ++k) {
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).hh =
          trie[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    }
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        trie_op_ptr;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    for (N = trie_op_ptr, k = 1; k <= N; ++k) {
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          hyf_distance[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          hyf_num[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
          hyf_next[k];
      writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    }
    print_nl(1266);
    print_int(trie_max);
    print(1267);
    print_int(trie_op_ptr);
    print(1268);
    if (trie_op_ptr != 1)
      print_char(115);
    print(1269);
    print_int(trie_op_size);
    for (k = 255; k >= 0; --k) {
      if (trie_used[k] > 0) {
        print_nl(799);
        print_int(trie_used[k]);
        print(1270);
        print_int(k);
        readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ = k;
        writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
        readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
            trie_used[k];
        writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
      }
    }
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        interaction;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ =
        format_ident;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_ = 69069;
    writeU32(fmt_file, fmt_file_mode, &fmt_file_value);
    eqtb[12194].int_ = 0;
    w_close(fmt_file);
  }
  void new_whatsit(small_number s, small_number w) {
    halfword p = get_node(w);
    mem[p - mem_min].hh.U2.b0 = 8;
    mem[p - mem_min].hh.U2.b1 = s;
    mem[cur_list.tail_field - mem_min].hh.rh = p;
    cur_list.tail_field = p;
  }
  void new_write_whatsit(small_number w) {
    new_whatsit(cur_chr, w);
    if (w != 2) {
      scan_four_bit_int();
    } else {
      scan_int();
      if (cur_val < 0) {
        cur_val = 17;
      } else if (cur_val > 15)
        cur_val = 16;
    }
    mem[cur_list.tail_field - mem_min + 1].hh.lh = cur_val;
  }
  void do_extension() {
    integer k;
    halfword p;
    switch (cur_chr) {
    case 0:
      new_write_whatsit(3);
      scan_optional_equals();
      scan_file_name();
      mem[cur_list.tail_field - mem_min + 1].hh.rh = cur_name;
      mem[cur_list.tail_field - mem_min + 2].hh.lh = cur_area;
      mem[cur_list.tail_field - mem_min + 2].hh.rh = cur_ext;
      break;
    case 1:
      k = cur_cs;
      new_write_whatsit(2);
      cur_cs = k;
      p = scan_toks(false, false);
      mem[cur_list.tail_field - mem_min + 1].hh.rh = def_ref;
      break;
    case 2:
      new_write_whatsit(2);
      mem[cur_list.tail_field - mem_min + 1].hh.rh = -1073741824;
      break;
    case 3:
      new_whatsit(3, 2);
      mem[cur_list.tail_field - mem_min + 1].hh.lh = -1073741824;
      p = scan_toks(false, true);
      mem[cur_list.tail_field - mem_min + 1].hh.rh = def_ref;
      break;
    case 4:
      get_x_token();
      if ((cur_cmd == 59) && (cur_chr <= 2)) {
        p = cur_list.tail_field;
        do_extension();
        out_what(cur_list.tail_field);
        flush_node_list(cur_list.tail_field);
        cur_list.tail_field = p;
        mem[p - mem_min].hh.rh = -1073741824;
      } else {
        back_input();
      }
      break;
    case 5:
      if (abs(cur_list.mode_field) != 102) {
        report_illegal_case();
      } else {
        new_whatsit(4, 2);
        scan_int();
        if (cur_val <= 0) {
          cur_list.aux_field.hh.rh = 0;
        } else if (cur_val > 255)
          cur_list.aux_field.hh.rh = 0;
        else
          cur_list.aux_field.hh.rh = cur_val;
        mem[cur_list.tail_field - mem_min + 1].hh.rh = cur_list.aux_field.hh.rh;
        mem[cur_list.tail_field - mem_min + 1].hh.U2.b0 =
            norm_min(eqtb[12214].int_);
        mem[cur_list.tail_field - mem_min + 1].hh.U2.b1 =
            norm_min(eqtb[12215].int_);
      }
      break;
    default:
      confusion(1290);
      break;
    }
  }
  void fix_language() {
    ASCII_code l;
    if (eqtb[12213].int_ <= 0) {
      l = 0;
    } else if (eqtb[12213].int_ > 255)
      l = 0;
    else
      l = eqtb[12213].int_;
    if (l == cur_list.aux_field.hh.rh)
      return;
    new_whatsit(4, 2);
    mem[cur_list.tail_field - mem_min + 1].hh.rh = l;
    cur_list.aux_field.hh.rh = l;
    mem[cur_list.tail_field - mem_min + 1].hh.U2.b0 =
        norm_min(eqtb[12214].int_);
    mem[cur_list.tail_field - mem_min + 1].hh.U2.b1 =
        norm_min(eqtb[12215].int_);
  }
  void handle_right_brace() {
    halfword p, q;
    scaled d;
    integer f;
    switch (cur_group) {
    case 1:
      unsave();
      break;
    case 0:
      print_nl(262);
      print(1043);
      help_ptr = 2;
      help_line[1] = 1044;
      help_line[0] = 1045;
      error();
      break;
    case 14:
    case 15:
    case 16:
      extra_right_brace();
      break;
    case 2:
      package(0);
      break;
    case 3:
      adjust_tail = mem_max - 5;
      package(0);
      break;
    case 4:
      end_graf();
      package(0);
      break;
    case 5:
      end_graf();
      package(4);
      break;
    case 11:
      end_graf();
      q = eqtb[9792].hh.rh;
      ++mem[q - mem_min].hh.rh;
      d = eqtb[12736].int_;
      f = eqtb[12205].int_;
      unsave();
      --save_ptr;
      p = vpackage(mem[cur_list.head_field - mem_min].hh.rh, 0, 1, 1073741823);
      pop_nest();
      if (save_stack[save_ptr].int_ < 255) {
        mem[cur_list.tail_field - mem_min].hh.rh = get_node(5);
        cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
        mem[cur_list.tail_field - mem_min].hh.U2.b0 = 3;
        mem[cur_list.tail_field - mem_min].hh.U2.b1 = save_stack[save_ptr].int_;
        mem[cur_list.tail_field - mem_min + 3].int_ =
            mem[p - mem_min + 3].int_ + mem[p - mem_min + 2].int_;
        mem[cur_list.tail_field - mem_min + 4].hh.lh =
            mem[p - mem_min + 5].hh.rh;
        mem[cur_list.tail_field - mem_min + 4].hh.rh = q;
        mem[cur_list.tail_field - mem_min + 2].int_ = d;
        mem[cur_list.tail_field - mem_min + 1].int_ = f;
      } else {
        mem[cur_list.tail_field - mem_min].hh.rh = get_node(2);
        cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
        mem[cur_list.tail_field - mem_min].hh.U2.b0 = 5;
        mem[cur_list.tail_field - mem_min].hh.U2.b1 = 0;
        mem[cur_list.tail_field - mem_min + 1].int_ =
            mem[p - mem_min + 5].hh.rh;
        delete_glue_ref(q);
      }
      free_node(p, 7);
      if (!nest_ptr)
        build_page();
      break;
    case 8:
      if ((cur_input.loc_field != (-1073741824)) ||
          ((cur_input.index_field != 6) && (cur_input.index_field != 3))) {
        print_nl(262);
        print(1009);
        help_ptr = 2;
        help_line[1] = 1010;
        help_line[0] = 1011;
        error();
        do {
          get_token();
        } while (cur_input.loc_field != (-1073741824));
      }
      end_token_list();
      end_graf();
      unsave();
      output_active = false;
      insert_penalties = 0;
      if (eqtb[10833].hh.rh != (-1073741824)) {
        print_nl(262);
        print(1012);
        print_esc(409);
        print_int(255);
        help_ptr = 3;
        help_line[2] = 1013;
        help_line[1] = 1014;
        help_line[0] = 1015;
        box_error(255);
      }
      if (cur_list.tail_field != cur_list.head_field) {
        mem[page_tail - mem_min].hh.rh =
            mem[cur_list.head_field - mem_min].hh.rh;
        page_tail = cur_list.tail_field;
      }
      if (mem[mem_max - mem_min - 2].hh.rh != (-1073741824)) {
        if (mem[mem_max - mem_min - 1].hh.rh == (-1073741824))
          nest[0].tail_field = page_tail;
        mem[page_tail - mem_min].hh.rh = mem[mem_max - mem_min - 1].hh.rh;
        mem[mem_max - mem_min - 1].hh.rh = mem[mem_max - mem_min - 2].hh.rh;
        mem[mem_max - mem_min - 2].hh.rh = -1073741824;
        page_tail = mem_max - 2;
      }
      pop_nest();
      build_page();
      break;
    case 10:
      build_discretionary();
      break;
    case 6:
      back_input();
      cur_tok = 13610;
      print_nl(262);
      print(625);
      print_esc(898);
      print(626);
      help_ptr = 1;
      help_line[0] = 1124;
      ins_error();
      break;
    case 7:
      end_graf();
      unsave();
      align_peek();
      break;
    case 12:
      end_graf();
      unsave();
      save_ptr -= 2;
      (p = vpackage(mem[cur_list.head_field - mem_min].hh.rh,
                    save_stack[save_ptr + 1].int_, save_stack[save_ptr].int_,
                    1073741823));
      pop_nest();
      mem[cur_list.tail_field - mem_min].hh.rh = new_noad();
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      mem[cur_list.tail_field - mem_min].hh.U2.b0 = 29;
      mem[cur_list.tail_field - mem_min + 1].hh.rh = 2;
      mem[cur_list.tail_field - mem_min + 1].hh.lh = p;
      break;
    case 13:
      build_choices();
      break;
    case 9:
      unsave();
      --save_ptr;
      mem[save_stack[save_ptr].int_ - mem_min].hh.rh = 3;
      p = fin_mlist(-1073741824);
      mem[save_stack[save_ptr].int_ - mem_min].hh.lh = p;
      if (p != (-1073741824)) {
        if (mem[p - mem_min].hh.rh == (-1073741824)) {
          if (mem[p - mem_min].hh.U2.b0 == 16) {
            if (!mem[p - mem_min + 3].hh.rh) {
              if (!mem[p - mem_min + 2].hh.rh) {
                mem[save_stack[save_ptr].int_ - mem_min].hh =
                    mem[p - mem_min + 1].hh;
                free_node(p, 4);
              }
            }
          } else if (mem[p - mem_min].hh.U2.b0 == 28) {
            if (save_stack[save_ptr].int_ == (cur_list.tail_field + 1)) {
              if (mem[cur_list.tail_field - mem_min].hh.U2.b0 == 16) {
                q = cur_list.head_field;
                while (mem[q - mem_min].hh.rh != cur_list.tail_field)
                  q = mem[q - mem_min].hh.rh;
                mem[q - mem_min].hh.rh = p;
                free_node(cur_list.tail_field, 4);
                cur_list.tail_field = p;
              }
            }
          }
        }
      }
      break;
    default:
      confusion(1046);
      break;
    }
  }
  void main_control() {
    integer t;
    if (eqtb[10319].hh.rh != (-1073741824))
      begin_token_list(eqtb[10319].hh.rh, 12);
  _L60:
    get_x_token();
  _L21:
    if (interrupt) {
      if (OK_to_interrupt) {
        back_input();
        if (interrupt)
          pause_for_instructions();
        goto _L60;
      }
    }
    if (eqtb[12199].int_ > 0)
      show_cur_cmd_chr();
    switch (abs(cur_list.mode_field) + cur_cmd) {
    case 113:
    case 114:
    case 170:
      goto _L70;
      break;
    case 118:
      scan_char_num();
      cur_chr = cur_val;
      goto _L70;
      break;
    case 167:
      get_x_token();
      if ((cur_cmd == 11) || (cur_cmd == 12) || (cur_cmd == 68) ||
          (cur_cmd == 16))
        cancel_boundary = true;
      goto _L21;
      break;
    case 112:
      if (cur_list.aux_field.hh.lh == 1000)
        goto _L120;
      app_space();
      break;
    case 166:
    case 267:
      goto _L120;
      break;
    case 1:
    case 102:
    case 203:
    case 11:
    case 213:
    case 268:
      // blank case
      break;
    case 40:
    case 141:
    case 242:
      do {
        get_x_token();
      } while (cur_cmd == 10);
      goto _L21;
      break;
    case 15:
      if (its_all_over())
        goto _L10;
      break;
    case 23:
    case 123:
    case 224:
    case 71:
    case 172:
    case 273:
    case 39:
    case 45:
    case 49:
    case 150:
    case 7:
    case 108:
    case 209:
      report_illegal_case();
      break;
    case 8:
    case 109:
    case 9:
    case 110:
    case 18:
    case 119:
    case 70:
    case 171:
    case 51:
    case 152:
    case 16:
    case 117:
    case 50:
    case 151:
    case 53:
    case 154:
    case 67:
    case 168:
    case 54:
    case 155:
    case 55:
    case 156:
    case 57:
    case 158:
    case 56:
    case 157:
    case 31:
    case 132:
    case 52:
    case 153:
    case 29:
    case 130:
    case 47:
    case 148:
    case 212:
    case 216:
    case 217:
    case 230:
    case 227:
    case 236:
    case 239:
      insert_dollar_sign();
      break;
    case 37:
    case 137:
    case 238:
      mem[cur_list.tail_field - mem_min].hh.rh = scan_rule_spec();
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      if (abs(cur_list.mode_field) == 1) {
        cur_list.aux_field.int_ = -65536000;
      } else if (abs(cur_list.mode_field) == 102)
        cur_list.aux_field.hh.lh = 1000;
      break;
    case 28:
    case 128:
    case 229:
    case 231:
      append_glue();
      break;
    case 30:
    case 131:
    case 232:
    case 233:
      append_kern();
      break;
    case 2:
    case 103:
      new_save_level(1);
      break;
    case 62:
    case 163:
    case 264:
      new_save_level(14);
      break;
    case 63:
    case 164:
    case 265:
      if (cur_group == 14)
        unsave();
      else
        off_save();
      break;
    case 3:
    case 104:
    case 205:
      handle_right_brace();
      break;
    case 22:
    case 124:
    case 225:
      t = cur_chr;
      scan_dimen(false, false, false);
      if (!t)
        scan_box(cur_val);
      else
        scan_box(-cur_val);
      break;
    case 32:
    case 133:
    case 234:
      scan_box(cur_chr + 1073742237);
      break;
    case 21:
    case 122:
    case 223:
      begin_box(0);
      break;
    case 44:
      new_graf(cur_chr > 0);
      break;
    case 12:
    case 13:
    case 17:
    case 69:
    case 4:
    case 24:
    case 36:
    case 46:
    case 48:
    case 27:
    case 34:
    case 65:
    case 66:
      back_input();
      new_graf(true);
      break;
    case 145:
    case 246:
      indent_in_hmode();
      break;
    case 14:
      normal_paragraph();
      if (cur_list.mode_field > 0)
        build_page();
      break;
    case 115:
      if (align_state < 0)
        off_save();
      end_graf();
      if (cur_list.mode_field == 1)
        build_page();
      break;
    case 116:
    case 129:
    case 138:
    case 126:
    case 134:
      head_for_vmode();
      break;
    case 38:
    case 139:
    case 240:
    case 140:
    case 241:
      begin_insert_or_adjust();
      break;
    case 19:
    case 120:
    case 221:
      make_mark();
      break;
    case 43:
    case 144:
    case 245:
      append_penalty();
      break;
    case 26:
    case 127:
    case 228:
      delete_last();
      break;
    case 25:
    case 125:
    case 226:
      unpackage();
      break;
    case 146:
      append_italic_correction();
      break;
    case 247:
      mem[cur_list.tail_field - mem_min].hh.rh = new_kern(0);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      break;
    case 149:
    case 250:
      append_discretionary();
      break;
    case 147:
      make_accent();
      break;
    case 6:
    case 107:
    case 208:
    case 5:
    case 106:
    case 207:
      align_error();
      break;
    case 35:
    case 136:
    case 237:
      no_align_error();
      break;
    case 64:
    case 165:
    case 266:
      omit_error();
      break;
    case 33:
    case 135:
      init_align();
      break;
    case 235:
      if (privileged()) {
        if (cur_group == 15)
          init_align();
        else
          off_save();
      }
      break;
    case 10:
    case 111:
      do_endv();
      break;
    case 68:
    case 169:
    case 270:
      cs_error();
      break;
    case 105:
      init_math();
      break;
    case 251:
      if (privileged()) {
        if (cur_group == 15)
          start_eq_no();
        else
          off_save();
      }
      break;
    case 204:
      mem[cur_list.tail_field - mem_min].hh.rh = new_noad();
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      back_input();
      scan_math(cur_list.tail_field + 1);
      break;
    case 214:
    case 215:
    case 271:
      set_math_char(eqtb[cur_chr + 11907].hh.rh + 1073741824);
      break;
    case 219:
      scan_char_num();
      cur_chr = cur_val;
      set_math_char(eqtb[cur_chr + 11907].hh.rh + 1073741824);
      break;
    case 220:
      scan_fifteen_bit_int();
      set_math_char(cur_val);
      break;
    case 272:
      set_math_char(cur_chr);
      break;
    case 218:
      scan_twenty_seven_bit_int();
      set_math_char(cur_val / 4096);
      break;
    case 253:
      mem[cur_list.tail_field - mem_min].hh.rh = new_noad();
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      mem[cur_list.tail_field - mem_min].hh.U2.b0 = cur_chr;
      scan_math(cur_list.tail_field + 1);
      break;
    case 254:
      math_limit_switch();
      break;
    case 269:
      math_radical();
      break;
    case 248:
    case 249:
      math_ac();
      break;
    case 259:
      scan_spec(12, false);
      normal_paragraph();
      push_nest();
      cur_list.mode_field = -1;
      cur_list.aux_field.int_ = -65536000;
      if (eqtb[10318].hh.rh != (-1073741824))
        begin_token_list(eqtb[10318].hh.rh, 11);
      break;
    case 256:
      mem[cur_list.tail_field - mem_min].hh.rh = new_style(cur_chr);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      break;
    case 258:
      mem[cur_list.tail_field - mem_min].hh.rh = new_glue(0);
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
      mem[cur_list.tail_field - mem_min].hh.U2.b1 = 98;
      break;
    case 257:
      append_choices();
      break;
    case 211:
    case 210:
      sub_sup();
      break;
    case 255:
      math_fraction();
      break;
    case 252:
      math_left_right();
      break;
    case 206:
      if (cur_group == 15)
        after_math();
      else
        off_save();
      break;
    case 72:
    case 173:
    case 274:
    case 73:
    case 174:
    case 275:
    case 74:
    case 175:
    case 276:
    case 75:
    case 176:
    case 277:
    case 76:
    case 177:
    case 278:
    case 77:
    case 178:
    case 279:
    case 78:
    case 179:
    case 280:
    case 79:
    case 180:
    case 281:
    case 80:
    case 181:
    case 282:
    case 81:
    case 182:
    case 283:
    case 82:
    case 183:
    case 284:
    case 83:
    case 184:
    case 285:
    case 84:
    case 185:
    case 286:
    case 85:
    case 186:
    case 287:
    case 86:
    case 187:
    case 288:
    case 87:
    case 188:
    case 289:
    case 88:
    case 189:
    case 290:
    case 89:
    case 190:
    case 291:
    case 90:
    case 191:
    case 292:
    case 91:
    case 192:
    case 293:
    case 92:
    case 193:
    case 294:
    case 93:
    case 194:
    case 295:
    case 94:
    case 195:
    case 296:
    case 95:
    case 196:
    case 297:
    case 96:
    case 197:
    case 298:
    case 97:
    case 198:
    case 299:
    case 98:
    case 199:
    case 300:
    case 99:
    case 200:
    case 301:
    case 100:
    case 201:
    case 302:
    case 101:
    case 202:
    case 303:
      prefixed_command();
      break;
    case 41:
    case 142:
    case 243:
      get_token();
      after_token = cur_tok;
      break;
    case 42:
    case 143:
    case 244:
      get_token();
      save_for_after(cur_tok);
      break;
    case 61:
    case 162:
    case 263:
      open_or_close_in();
      break;
    case 59:
    case 160:
    case 261:
      issue_message();
      break;
    case 58:
    case 159:
    case 260:
      shift_case();
      break;
    case 20:
    case 121:
    case 222:
      show_whatever();
      break;
    case 60:
    case 161:
    case 262:
      do_extension();
      break;
    }
    goto _L60;
  _L70:
    main_s = eqtb[cur_chr + 11651].hh.rh;
    if (main_s == 1000) {
      cur_list.aux_field.hh.lh = 1000;
    } else if (main_s < 1000) {
      if (main_s > 0)
        cur_list.aux_field.hh.lh = main_s;
    } else if (cur_list.aux_field.hh.lh < 1000)
      cur_list.aux_field.hh.lh = 1000;
    else
      cur_list.aux_field.hh.lh = main_s;
    main_f = eqtb[10834].hh.rh;
    bchar = font_bchar[main_f];
    false_bchar = font_false_bchar[main_f];
    if (cur_list.mode_field > 0) {
      if (eqtb[12213].int_ != cur_list.aux_field.hh.rh)
        fix_language();
    }
    lig_stack = avail;
    if (lig_stack == (-1073741824)) {
      lig_stack = get_avail();
    } else {
      avail = mem[lig_stack - mem_min].hh.rh;
      mem[lig_stack - mem_min].hh.rh = -1073741824;
    }
    mem[lig_stack - mem_min].hh.U2.b0 = main_f;
    cur_l = cur_chr;
    mem[lig_stack - mem_min].hh.U2.b1 = cur_l;
    cur_q = cur_list.tail_field;
    if (cancel_boundary) {
      cancel_boundary = false;
      main_k = 0;
    } else {
      main_k = bchar_label[main_f];
    }
    if (!main_k)
      goto _L92;
    cur_r = cur_l;
    cur_l = 256;
    goto _L111;
  _L80:
    if (cur_l < 256) {
      if (mem[cur_q - mem_min].hh.rh > (-1073741824)) {
        if (mem[cur_list.tail_field - mem_min].hh.U2.b1 == hyphen_char[main_f])
          ins_disc = true;
      }
      if (ligature_present) {
        main_p = new_ligature(main_f, cur_l, mem[cur_q - mem_min].hh.rh);
        if (lft_hit) {
          mem[main_p - mem_min].hh.U2.b1 = 2;
          lft_hit = false;
        }
        if (rt_hit) {
          if (lig_stack == (-1073741824)) {
            ++mem[main_p - mem_min].hh.U2.b1;
            rt_hit = false;
          }
        }
        mem[cur_q - mem_min].hh.rh = main_p;
        cur_list.tail_field = main_p;
        ligature_present = false;
      }
      if (ins_disc) {
        ins_disc = false;
        if (cur_list.mode_field > 0) {
          mem[cur_list.tail_field - mem_min].hh.rh = new_disc();
          cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
        }
      }
    }
  _L90:
    if (lig_stack == (-1073741824))
      goto _L21;
    cur_q = cur_list.tail_field;
    cur_l = mem[lig_stack - mem_min].hh.U2.b1;
  _L91:
    if (lig_stack < hi_mem_min)
      goto _L95;
  _L92:
    if ((cur_chr < font_bc[main_f]) || (cur_chr > font_ec[main_f])) {
      char_warning(main_f, cur_chr);
      mem[lig_stack - mem_min].hh.rh = avail;
      avail = lig_stack;
      goto _L60;
    }
    main_i = font_info[char_base[main_f] + cur_l].qqqq;
    if (main_i.b0 <= 0) {
      char_warning(main_f, cur_chr);
      mem[lig_stack - mem_min].hh.rh = avail;
      avail = lig_stack;
      goto _L60;
    }
    mem[cur_list.tail_field - mem_min].hh.rh = lig_stack;
    cur_list.tail_field = lig_stack;
  _L100:
    get_next();
    if (cur_cmd == 11)
      goto _L101;
    if (cur_cmd == 12)
      goto _L101;
    if (cur_cmd == 68)
      goto _L101;
    x_token();
    if (cur_cmd == 11)
      goto _L101;
    if (cur_cmd == 12)
      goto _L101;
    if (cur_cmd == 68)
      goto _L101;
    if (cur_cmd == 16) {
      scan_char_num();
      cur_chr = cur_val;
      goto _L101;
    }
    if (cur_cmd == 65)
      bchar = 256;
    cur_r = bchar;
    lig_stack = -1073741824;
    goto _L110;
  _L101:
    main_s = eqtb[cur_chr + 11651].hh.rh;
    if (main_s == 1000) {
      cur_list.aux_field.hh.lh = 1000;
    } else if (main_s < 1000) {
      if (main_s > 0)
        cur_list.aux_field.hh.lh = main_s;
    } else if (cur_list.aux_field.hh.lh < 1000)
      cur_list.aux_field.hh.lh = 1000;
    else
      cur_list.aux_field.hh.lh = main_s;
    lig_stack = avail;
    if (lig_stack == (-1073741824)) {
      lig_stack = get_avail();
    } else {
      avail = mem[lig_stack - mem_min].hh.rh;
      mem[lig_stack - mem_min].hh.rh = -1073741824;
    }
    mem[lig_stack - mem_min].hh.U2.b0 = main_f;
    cur_r = cur_chr;
    mem[lig_stack - mem_min].hh.U2.b1 = cur_r;
    if (cur_r == false_bchar)
      cur_r = 256;
  _L110:
    if ((main_i.b2 & 3) != 1)
      goto _L80;
    if (cur_r == 256)
      goto _L80;
    main_k = lig_kern_base[main_f] + main_i.b3;
    main_j = font_info[main_k].qqqq;
    if (main_j.b0 <= 128)
      goto _L112;
    main_k = lig_kern_base[main_f] + (main_j.b2 * 256) + main_j.b3;
  _L111:
    main_j = font_info[main_k].qqqq;
  _L112:
    if (main_j.b1 == cur_r) {
      if (main_j.b0 <= 128) {
        if (main_j.b2 >= 128) {
          if (cur_l < 256) {
            if (mem[cur_q - mem_min].hh.rh > (-1073741824)) {
              if (mem[cur_list.tail_field - mem_min].hh.U2.b1 ==
                  hyphen_char[main_f])
                ins_disc = true;
            }
            if (ligature_present) {
              main_p = new_ligature(main_f, cur_l, mem[cur_q - mem_min].hh.rh);
              if (lft_hit) {
                mem[main_p - mem_min].hh.U2.b1 = 2;
                lft_hit = false;
              }
              if (rt_hit) {
                if (lig_stack == (-1073741824)) {
                  ++mem[main_p - mem_min].hh.U2.b1;
                  rt_hit = false;
                }
              }
              mem[cur_q - mem_min].hh.rh = main_p;
              cur_list.tail_field = main_p;
              ligature_present = false;
            }
            if (ins_disc) {
              ins_disc = false;
              if (cur_list.mode_field > 0) {
                mem[cur_list.tail_field - mem_min].hh.rh = new_disc();
                cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
              }
            }
          }
          (mem[cur_list.tail_field - mem_min].hh.rh = new_kern(
               font_info[kern_base[main_f] + (main_j.b2 * 256) + main_j.b3]
                   .int_));
          cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
          goto _L90;
        }
        if (cur_l == 256) {
          lft_hit = true;
        } else if (lig_stack == (-1073741824))
          rt_hit = true;
        if (interrupt)
          pause_for_instructions();
        switch (main_j.b2) {
        case 1:
        case 5:
          cur_l = main_j.b3;
          main_i = font_info[char_base[main_f] + cur_l].qqqq;
          ligature_present = true;
          break;
        case 2:
        case 6:
          cur_r = main_j.b3;
          if (lig_stack == (-1073741824)) {
            lig_stack = new_lig_item(cur_r);
            bchar = 256;
          } else if (lig_stack >= hi_mem_min) {
            main_p = lig_stack;
            lig_stack = new_lig_item(cur_r);
            mem[lig_stack - mem_min + 1].hh.rh = main_p;
          } else {
            mem[lig_stack - mem_min].hh.U2.b1 = cur_r;
          }
          break;
        case 3:
          cur_r = main_j.b3;
          main_p = lig_stack;
          lig_stack = new_lig_item(cur_r);
          mem[lig_stack - mem_min].hh.rh = main_p;
          break;
        case 7:
        case 11:
          if (cur_l < 256) {
            if (mem[cur_q - mem_min].hh.rh > (-1073741824)) {
              if (mem[cur_list.tail_field - mem_min].hh.U2.b1 ==
                  hyphen_char[main_f])
                ins_disc = true;
            }
            if (ligature_present) {
              main_p = new_ligature(main_f, cur_l, mem[cur_q - mem_min].hh.rh);
              if (lft_hit) {
                mem[main_p - mem_min].hh.U2.b1 = 2;
                lft_hit = false;
              }
              mem[cur_q - mem_min].hh.rh = main_p;
              cur_list.tail_field = main_p;
              ligature_present = false;
            }
            if (ins_disc) {
              ins_disc = false;
              if (cur_list.mode_field > 0) {
                mem[cur_list.tail_field - mem_min].hh.rh = new_disc();
                cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
              }
            }
          }
          cur_q = cur_list.tail_field;
          cur_l = main_j.b3;
          main_i = font_info[char_base[main_f] + cur_l].qqqq;
          ligature_present = true;
          break;
        default:
          cur_l = main_j.b3;
          ligature_present = true;
          if (lig_stack == (-1073741824))
            goto _L80;
          else
            goto _L91;
          break;
        }
        if (main_j.b2 > 4) {
          if (main_j.b2 != 7)
            goto _L80;
        }
        if (cur_l < 256)
          goto _L110;
        main_k = bchar_label[main_f];
        goto _L111;
      }
    }
    if (!main_j.b0) {
      ++main_k;
    } else {
      if (main_j.b0 >= 128)
        goto _L80;
      main_k += main_j.b0 + 1;
    }
    goto _L111;
  _L95:
    main_p = mem[lig_stack - mem_min + 1].hh.rh;
    if (main_p > (-1073741824)) {
      mem[cur_list.tail_field - mem_min].hh.rh = main_p;
      cur_list.tail_field = mem[cur_list.tail_field - mem_min].hh.rh;
    }
    temp_ptr = lig_stack;
    lig_stack = mem[temp_ptr - mem_min].hh.rh;
    free_node(temp_ptr, 2);
    main_i = font_info[char_base[main_f] + cur_l].qqqq;
    ligature_present = true;
    if (lig_stack == (-1073741824)) {
      if (main_p > (-1073741824))
        goto _L100;
      cur_r = bchar;
    } else {
      cur_r = mem[lig_stack - mem_min].hh.U2.b1;
    }
    goto _L110;
  _L120:
    if (!eqtb[9794].hh.rh) {
      main_p = font_glue[eqtb[10834].hh.rh];
      if (main_p == (-1073741824)) {
        main_p = new_spec(0);
        main_k = param_base[eqtb[10834].hh.rh] + 2;
        mem[main_p - mem_min + 1].int_ = font_info[main_k].int_;
        mem[main_p - mem_min + 2].int_ = font_info[main_k + 1].int_;
        mem[main_p - mem_min + 3].int_ = font_info[main_k + 2].int_;
        font_glue[eqtb[10834].hh.rh] = main_p;
      }
      temp_ptr = new_glue(main_p);
    } else {
      temp_ptr = new_param_glue(12);
    }
    mem[cur_list.tail_field - mem_min].hh.rh = temp_ptr;
    cur_list.tail_field = temp_ptr;
    goto _L60;
  _L10:;
  }
  void give_err_help() { token_show(eqtb[10321].hh.rh); }
  bool open_fmt_file() {
    bool result;
    int j = cur_input.loc_field;
    if (buffer[cur_input.loc_field] == 38) {
      ++cur_input.loc_field;
      j = cur_input.loc_field;
      buffer[last] = 32;
      while (buffer[j] != 32)
        ++j;
      pack_buffered_name(0, cur_input.loc_field, j - 1);
      if (w_open_in(fmt_file))
        goto _L40;
      pack_buffered_name(11, cur_input.loc_field, j - 1);
      if (w_open_in(fmt_file))
        goto _L40;
      fprintf(term_out, "Sorry, I can't find that format; will try PLAIN.\n");
      fflush(term_out);
      errno = 0;
    }
    pack_buffered_name(16, 1, 0);
    if (!w_open_in(fmt_file)) {
      fprintf(term_out, "I can't find the PLAIN format file!\n");
      result = false;
      goto _L10;
    }
  _L40:
    cur_input.loc_field = j;
    result = true;
  _L10:
    return result;
  }
  bool load_fmt_file() {
    bool result = true;
    integer j, k;
    halfword p = 0, q;
    four_quarters w;
    int N;
    integer x =
        readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (x != 117275187)
      goto _L6666;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (x)
      goto _L6666;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (x != mem_max)
      goto _L6666;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (x != 13006)
      goto _L6666;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (x != 7649)
      goto _L6666;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (x != 307)
      goto _L6666;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (x < 0)
      goto _L6666;
    if (x > pool_size) {
      fprintf(term_out, "---! Must increase the string pool size\n");
      goto _L6666;
    }
    pool_ptr = x;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (x < 0)
      goto _L6666;
    if (x > max_strings) {
      fprintf(term_out, "---! Must increase the max strings\n");
      goto _L6666;
    }
    str_ptr = x;
    for (N = str_ptr, k = 0; k <= N; ++k) {
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) > pool_ptr)
        goto _L6666;
      str_start[k] = x;
    }
    k = 0;
    while (k + 4 < pool_ptr) {
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      w = readU32(fmt_file, fmt_file_mode, &fmt_file_value).qqqq;
      str_pool[k] = w.b0;
      str_pool[k + 1] = w.b1;
      str_pool[k + 2] = w.b2;
      str_pool[k + 3] = w.b3;
      k += 4;
    }
    k = pool_ptr - 4;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    w = readU32(fmt_file, fmt_file_mode, &fmt_file_value).qqqq;
    str_pool[k] = w.b0;
    str_pool[k + 1] = w.b1;
    str_pool[k + 2] = w.b2;
    str_pool[k + 3] = w.b3;
    init_str_ptr = str_ptr;
    init_pool_ptr = pool_ptr;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if ((x < 1019) || (x > (mem_max - 14)))
      goto _L6666;
    lo_mem_max = x;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if ((x < 20) || (x > lo_mem_max))
      goto _L6666;
    rover = x;
    q = rover;
    do {
      for (k = p; k <= (q + 1); ++k) {
        loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
        mem[k - mem_min] =
            readU32(fmt_file, fmt_file_mode, &fmt_file_value);
      }
      p = q + mem[q - mem_min].hh.lh;
      if ((p > lo_mem_max) || ((q >= mem[q - mem_min + 1].hh.rh) &&
                               (mem[q - mem_min + 1].hh.rh != rover)))
        goto _L6666;
      q = mem[q - mem_min + 1].hh.rh;
    } while (q != rover);
    for (N = lo_mem_max, k = p; k <= N; ++k) {
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      mem[k - mem_min] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value);
    }
    if (mem_min < (-2)) {
      p = mem[rover - mem_min + 1].hh.lh;
      q = mem_min + 1;
      mem[0].hh.rh = -1073741824;
      mem[0].hh.lh = -1073741824;
      mem[p - mem_min + 1].hh.rh = q;
      mem[rover - mem_min + 1].hh.lh = q;
      mem[q - mem_min + 1].hh.rh = rover;
      mem[q - mem_min + 1].hh.lh = p;
      mem[q - mem_min].hh.rh = 1073741824;
      mem[q - mem_min].hh.lh = -q;
    }
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if ((x <= lo_mem_max) || (x > (mem_max - 13)))
      goto _L6666;
    hi_mem_min = x;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if ((x < (-1073741824)) || (x > mem_max))
      goto _L6666;
    avail = x;
    mem_end = mem_max;
    for (N = mem_end, k = hi_mem_min; k <= N; ++k) {
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      mem[k - mem_min] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value);
    }
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    var_used =
        readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    dyn_used =
        readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    k = 1;
    do {
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if ((x < 1) || (k + x > 13007))
        goto _L6666;
      for (j = k; j < (k + x); ++j) {
        loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
        eqtb[j] =
            readU32(fmt_file, fmt_file_mode, &fmt_file_value);
      }
      k += x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if ((x < 0) || (k + x > 13007))
        goto _L6666;
      for (j = k; j < (k + x); ++j)
        eqtb[j] = eqtb[k - 1];
      k += x;
    } while (k <= 13006);
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if ((x < 514) || (x > 9514))
      goto _L6666;
    par_loc = x;
    par_token = par_loc + 4095;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if ((x < 514) || (x > 9514))
      goto _L6666;
    write_loc = x;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if ((x < 514) || (x > 9514))
      goto _L6666;
    hash_used = x;
    p = 513;
    do {
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if ((x <= p) || (x > hash_used))
        goto _L6666;
      p = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      hash[p - 514] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).hh;
    } while (p != hash_used);
    for (p = hash_used + 1; p <= 9780; ++p) {
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      hash[p - 514] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).hh;
    }
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    cs_count =
        readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (x < 7)
      goto _L6666;
    if (x > font_mem_size) {
      fprintf(term_out, "---! Must increase the font mem size\n");
      goto _L6666;
    }
    fmem_ptr = x;
    for (N = fmem_ptr, k = 0; k < N; ++k) {
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      font_info[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value);
    }
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (x < 0)
      goto _L6666;
    if (x > font_max) {
      fprintf(term_out, "---! Must increase the font max\n");
      goto _L6666;
    }
    font_ptr = x;
    for (N = font_ptr, k = 0; k <= N; ++k) {
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      font_check[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).qqqq;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      font_size[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      font_dsize[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if ((x < (-1073741824)) || (x > 1073741824))
        goto _L6666;
      font_params[k] = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      hyphen_char[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      skew_char[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) > str_ptr)
        goto _L6666;
      font_name[k] = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) > str_ptr)
        goto _L6666;
      font_area[k] = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) > 255)
        goto _L6666;
      font_bc[k] = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) > 255)
        goto _L6666;
      font_ec[k] = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      char_base[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      width_base[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      height_base[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      depth_base[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      italic_base[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      lig_kern_base[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      kern_base[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      exten_base[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      param_base[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if ((x < (-1073741824)) || (x > lo_mem_max))
        goto _L6666;
      font_glue[k] = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) >= fmem_ptr)
        goto _L6666;
      bchar_label[k] = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) > 256)
        goto _L6666;
      font_bchar[k] = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) > 256)
        goto _L6666;
      font_false_bchar[k] = x;
    }
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (((unsigned)x) > 307)
      goto _L6666;
    hyph_count = x;
    for (N = hyph_count, k = 1; k <= N; ++k) {
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) > 307)
        goto _L6666;
      j = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) > str_ptr)
        goto _L6666;
      hyph_word[j] = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if ((x < (-1073741824)) || (x > 1073741824))
        goto _L6666;
      hyph_list[j] = x;
    }
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (x < 0)
      goto _L6666;
    if (x > trie_size) {
      fprintf(term_out, "---! Must increase the trie size\n");
      goto _L6666;
    }
    j = x;
    trie_max = j;
    for (k = 0; k <= j; ++k) {
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      trie[k] =
          readU32(fmt_file, fmt_file_mode, &fmt_file_value).hh;
    }
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (x < 0)
      goto _L6666;
    if (x > trie_op_size) {
      fprintf(term_out, "---! Must increase the trie op size\n");
      goto _L6666;
    }
    j = x;
    trie_op_ptr = j;
    for (k = 1; k <= j; ++k) {
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) > 63)
        goto _L6666;
      hyf_distance[k] = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) > 63)
        goto _L6666;
      hyf_num[k] = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) > 65535)
        goto _L6666;
      hyf_next[k] = x;
    }
    for (k = 0; k <= 255; ++k)
      trie_used[k] = 0;
    k = 256;
    while (j > 0) {
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if (((unsigned)x) >= k)
        goto _L6666;
      k = x;
      loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
      x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
      if ((x < 1) || (x > j))
        goto _L6666;
      trie_used[k] = x;
      j -= x;
      op_start[k] = j;
    }
    trie_not_ready = false;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (((unsigned)x) > 3)
      goto _L6666;
    interaction = x;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if (((unsigned)x) > str_ptr)
      goto _L6666;
    format_ident = x;
    loadU32(fmt_file, fmt_file_mode, &fmt_file_value);
    x = readU32(fmt_file, fmt_file_mode, &fmt_file_value).int_;
    if ((x != 69069) || feof(fmt_file))
      goto _L6666;
    goto _L10;
  _L6666:
    fprintf(term_out, "(Fatal format file error; I'm stymied)\n");
    result = false;
  _L10:
    return result;
  }
  void close_files_and_terminate() {
    integer k;
    for (k = 0; k <= 15; ++k) {
      if (write_open[k])
        a_close(write_file[k]);
    }
    while (cur_s > (-1)) {
      if (cur_s > 0) {
        dvi_buf[dvi_ptr] = 142;
        ++dvi_ptr;
        if (dvi_ptr == dvi_limit)
          dvi_swap();
      } else {
        dvi_buf[dvi_ptr] = 140;
        ++dvi_ptr;
        if (dvi_ptr == dvi_limit)
          dvi_swap();
        ++total_pages;
      }
      --cur_s;
    }
    if (!total_pages) {
      print_nl(836);
    } else {
      dvi_buf[dvi_ptr] = 248;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      dvi_four(last_bop);
      last_bop = dvi_offset + dvi_ptr - 5;
      dvi_four(25400000);
      dvi_four(473628672);
      prepare_mag();
      dvi_four(eqtb[12180].int_);
      dvi_four(max_v);
      dvi_four(max_h);
      dvi_buf[dvi_ptr] = max_push / 256;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      dvi_buf[dvi_ptr] = max_push & 255;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      dvi_buf[dvi_ptr] = (total_pages / 256) & 255;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      dvi_buf[dvi_ptr] = total_pages & 255;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      while (font_ptr > 0) {
        if (font_used[font_ptr])
          dvi_font_def(font_ptr);
        --font_ptr;
      }
      dvi_buf[dvi_ptr] = 249;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      dvi_four(last_bop);
      dvi_buf[dvi_ptr] = 2;
      ++dvi_ptr;
      if (dvi_ptr == dvi_limit)
        dvi_swap();
      k = ((dvi_buf_size - dvi_ptr) & 3) + 4;
      while (k > 0) {
        dvi_buf[dvi_ptr] = 223;
        ++dvi_ptr;
        if (dvi_ptr == dvi_limit)
          dvi_swap();
        --k;
      }
      if (dvi_limit == half_buf)
        write_dvi(half_buf, dvi_buf_size - 1);
      if (dvi_ptr > 0)
        write_dvi(0, dvi_ptr - 1);
      print_nl(837);
      slow_print(output_file_name);
      print(286);
      print_int(total_pages);
      print(838);
      if (total_pages != 1)
        print_char(115);
      print(839);
      print_int(dvi_offset + dvi_ptr);
      print(840);
      b_close(dvi_file);
    }
    if (!log_opened)
      return;
    fprintf(log_file, "\n");
    a_close(log_file);
    selector -= 2;
    if (selector != 17)
      return;
    print_nl(1274);
    slow_print(log_name);
    print_char(46);
  }
  void final_cleanup() {
    small_number c = cur_chr;
    if (!job_name)
      open_log_file();
    while (input_ptr > 0) {
      if (!cur_input.state_field)
        end_token_list();
      else
        end_file_reading();
    }
    while (open_parens > 0) {
      print(1275);
      --open_parens;
    }
    if (cur_level > 1) {
      print_nl(40);
      print_esc(1276);
      print(1277);
      print_int(cur_level - 1);
      print_char(41);
    }
    while (cond_ptr != (-1073741824)) {
      print_nl(40);
      print_esc(1276);
      print(1278);
      print_cmd_chr(105, cur_if);
      if (if_line) {
        print(1279);
        print_int(if_line);
      }
      print(1280);
      if_line = mem[cond_ptr - mem_min + 1].int_;
      cur_if = mem[cond_ptr - mem_min].hh.U2.b1;
      temp_ptr = cond_ptr;
      cond_ptr = mem[cond_ptr - mem_min].hh.rh;
      free_node(temp_ptr, 2);
    }
    if (history) {
      if ((history == 1) || (interaction < 3)) {
        if (selector == 19) {
          selector = 17;
          print_nl(1281);
          selector = 19;
        }
      }
    }
    if (c == 1) {
      for (c = 0; c <= 4; ++c) {
        if (cur_mark[c] != (-1073741824))
          delete_token_ref(cur_mark[c]);
      }
      if (last_glue != 1073741824)
        delete_glue_ref(last_glue);
      store_fmt_file();
      goto _L10;
    }
  _L10:;
  }
  void init_prim() {
    no_new_control_sequence = false;
    primitive(376, 75, 9782);
    primitive(377, 75, 9783);
    primitive(378, 75, 9784);
    primitive(379, 75, 9785);
    primitive(380, 75, 9786);
    primitive(381, 75, 9787);
    primitive(382, 75, 9788);
    primitive(383, 75, 9789);
    primitive(384, 75, 9790);
    primitive(385, 75, 9791);
    primitive(386, 75, 9792);
    primitive(387, 75, 9793);
    primitive(388, 75, 9794);
    primitive(389, 75, 9795);
    primitive(390, 75, 9796);
    primitive(391, 76, 9797);
    primitive(392, 76, 9798);
    primitive(393, 76, 9799);
    primitive(398, 72, 10313);
    primitive(399, 72, 10314);
    primitive(400, 72, 10315);
    primitive(401, 72, 10316);
    primitive(402, 72, 10317);
    primitive(403, 72, 10318);
    primitive(404, 72, 10319);
    primitive(405, 72, 10320);
    primitive(406, 72, 10321);
    primitive(420, 73, 12163);
    primitive(421, 73, 12164);
    primitive(422, 73, 12165);
    primitive(423, 73, 12166);
    primitive(424, 73, 12167);
    primitive(425, 73, 12168);
    primitive(426, 73, 12169);
    primitive(427, 73, 12170);
    primitive(428, 73, 12171);
    primitive(429, 73, 12172);
    primitive(430, 73, 12173);
    primitive(431, 73, 12174);
    primitive(432, 73, 12175);
    primitive(433, 73, 12176);
    primitive(434, 73, 12177);
    primitive(435, 73, 12178);
    primitive(436, 73, 12179);
    primitive(437, 73, 12180);
    primitive(438, 73, 12181);
    primitive(439, 73, 12182);
    primitive(440, 73, 12183);
    primitive(441, 73, 12184);
    primitive(442, 73, 12185);
    primitive(443, 73, 12186);
    primitive(444, 73, 12187);
    primitive(445, 73, 12188);
    primitive(446, 73, 12189);
    primitive(447, 73, 12190);
    primitive(448, 73, 12191);
    primitive(449, 73, 12192);
    primitive(450, 73, 12193);
    primitive(451, 73, 12194);
    primitive(452, 73, 12195);
    primitive(453, 73, 12196);
    primitive(454, 73, 12197);
    primitive(455, 73, 12198);
    primitive(456, 73, 12199);
    primitive(457, 73, 12200);
    primitive(458, 73, 12201);
    primitive(459, 73, 12202);
    primitive(460, 73, 12203);
    primitive(461, 73, 12204);
    primitive(462, 73, 12205);
    primitive(463, 73, 12206);
    primitive(464, 73, 12207);
    primitive(465, 73, 12208);
    primitive(466, 73, 12209);
    primitive(467, 73, 12210);
    primitive(468, 73, 12211);
    primitive(469, 73, 12212);
    primitive(470, 73, 12213);
    primitive(471, 73, 12214);
    primitive(472, 73, 12215);
    primitive(473, 73, 12216);
    primitive(474, 73, 12217);
    primitive(478, 74, 12730);
    primitive(479, 74, 12731);
    primitive(480, 74, 12732);
    primitive(481, 74, 12733);
    primitive(482, 74, 12734);
    primitive(483, 74, 12735);
    primitive(484, 74, 12736);
    primitive(485, 74, 12737);
    primitive(486, 74, 12738);
    primitive(487, 74, 12739);
    primitive(488, 74, 12740);
    primitive(489, 74, 12741);
    primitive(490, 74, 12742);
    primitive(491, 74, 12743);
    primitive(492, 74, 12744);
    primitive(493, 74, 12745);
    primitive(494, 74, 12746);
    primitive(495, 74, 12747);
    primitive(496, 74, 12748);
    primitive(497, 74, 12749);
    primitive(498, 74, 12750);
    primitive(32, 64, 0);
    primitive(47, 44, 0);
    primitive(508, 45, 0);
    primitive(509, 90, 0);
    primitive(510, 40, 0);
    primitive(511, 41, 0);
    primitive(512, 61, 0);
    primitive(513, 16, 0);
    primitive(504, 107, 0);
    primitive(514, 15, 0);
    primitive(515, 92, 0);
    primitive(505, 67, 0);
    primitive(516, 62, 0);
    hash[9002].rh = 516;
    eqtb[9516] = eqtb[cur_val];
    primitive(517, 102, 0);
    primitive(518, 88, 0);
    primitive(519, 77, 0);
    primitive(520, 32, 0);
    primitive(521, 36, 0);
    primitive(522, 39, 0);
    primitive(330, 37, 0);
    primitive(351, 18, 0);
    primitive(523, 46, 0);
    primitive(524, 17, 0);
    primitive(525, 54, 0);
    primitive(526, 91, 0);
    primitive(527, 34, 0);
    primitive(528, 65, 0);
    primitive(529, 103, 0);
    primitive(335, 55, 0);
    primitive(530, 63, 0);
    primitive(408, 84, 0);
    primitive(531, 42, 0);
    primitive(532, 80, 0);
    primitive(533, 66, 0);
    primitive(534, 96, 0);
    primitive(535, 0, 256);
    hash[9007].rh = 535;
    eqtb[9521] = eqtb[cur_val];
    primitive(536, 98, 0);
    primitive(537, 109, 0);
    primitive(407, 71, 0);
    primitive(352, 38, 0);
    primitive(538, 33, 0);
    primitive(539, 56, 0);
    primitive(540, 35, 0);
    primitive(597, 13, 256);
    par_loc = cur_val;
    par_token = par_loc + 4095;
    primitive(629, 104, 0);
    primitive(630, 104, 1);
    primitive(631, 110, 0);
    primitive(632, 110, 1);
    primitive(633, 110, 2);
    primitive(634, 110, 3);
    primitive(635, 110, 4);
    primitive(476, 89, 0);
    primitive(500, 89, 1);
    primitive(395, 89, 2);
    primitive(396, 89, 3);
    primitive(668, 79, 102);
    primitive(669, 79, 1);
    primitive(670, 82, 0);
    primitive(671, 82, 1);
    primitive(672, 83, 1);
    primitive(673, 83, 3);
    primitive(674, 83, 2);
    primitive(675, 70, 0);
    primitive(676, 70, 1);
    primitive(677, 70, 2);
    primitive(678, 70, 3);
    primitive(679, 70, 4);
    primitive(735, 108, 0);
    primitive(736, 108, 1);
    primitive(737, 108, 2);
    primitive(738, 108, 3);
    primitive(739, 108, 4);
    primitive(740, 108, 5);
    primitive(756, 105, 0);
    primitive(757, 105, 1);
    primitive(758, 105, 2);
    primitive(759, 105, 3);
    primitive(760, 105, 4);
    primitive(761, 105, 5);
    primitive(762, 105, 6);
    primitive(763, 105, 7);
    primitive(764, 105, 8);
    primitive(765, 105, 9);
    primitive(766, 105, 10);
    primitive(767, 105, 11);
    primitive(768, 105, 12);
    primitive(769, 105, 13);
    primitive(770, 105, 14);
    primitive(771, 105, 15);
    primitive(772, 105, 16);
    primitive(773, 106, 2);
    hash[9004].rh = 773;
    eqtb[9518] = eqtb[cur_val];
    primitive(774, 106, 4);
    primitive(775, 106, 3);
    primitive(800, 87, 0);
    hash[9010].rh = 800;
    eqtb[9524] = eqtb[cur_val];
    primitive(897, 4, 256);
    primitive(898, 5, 257);
    hash[9001].rh = 898;
    eqtb[9515] = eqtb[cur_val];
    primitive(899, 5, 258);
    hash[9005].rh = 900;
    hash[9006].rh = 900;
    eqtb[9520].hh.U2.b0 = 9;
    eqtb[9520].hh.rh = mem_max - 11;
    eqtb[9520].hh.U2.b1 = 1;
    eqtb[9519] = eqtb[9520];
    eqtb[9519].hh.U2.b0 = 115;
    primitive(969, 81, 0);
    primitive(970, 81, 1);
    primitive(971, 81, 2);
    primitive(972, 81, 3);
    primitive(973, 81, 4);
    primitive(974, 81, 5);
    primitive(975, 81, 6);
    primitive(976, 81, 7);
    primitive(1024, 14, 0);
    primitive(1025, 14, 1);
    primitive(1026, 26, 4);
    primitive(1027, 26, 0);
    primitive(1028, 26, 1);
    primitive(1029, 26, 2);
    primitive(1030, 26, 3);
    primitive(1031, 27, 4);
    primitive(1032, 27, 0);
    primitive(1033, 27, 1);
    primitive(1034, 27, 2);
    primitive(1035, 27, 3);
    primitive(336, 28, 5);
    primitive(340, 29, 1);
    primitive(342, 30, 99);
    primitive(1053, 21, 1);
    primitive(1054, 21, 0);
    primitive(1055, 22, 1);
    primitive(1056, 22, 0);
    primitive(409, 20, 0);
    primitive(1057, 20, 1);
    primitive(1058, 20, 2);
    primitive(964, 20, 3);
    primitive(1059, 20, 4);
    primitive(966, 20, 5);
    primitive(1060, 20, 106);
    primitive(1061, 31, 99);
    primitive(1062, 31, 100);
    primitive(1063, 31, 101);
    primitive(1064, 31, 102);
    primitive(1079, 43, 1);
    primitive(1080, 43, 0);
    primitive(1089, 25, 12);
    primitive(1090, 25, 11);
    primitive(1091, 25, 10);
    primitive(1092, 23, 0);
    primitive(1093, 23, 1);
    primitive(1094, 24, 0);
    primitive(1095, 24, 1);
    primitive(45, 47, 1);
    primitive(349, 47, 0);
    primitive(1126, 48, 0);
    primitive(1127, 48, 1);
    primitive(865, 50, 16);
    primitive(866, 50, 17);
    primitive(867, 50, 18);
    primitive(868, 50, 19);
    primitive(869, 50, 20);
    primitive(870, 50, 21);
    primitive(871, 50, 22);
    primitive(872, 50, 23);
    primitive(874, 50, 26);
    primitive(873, 50, 27);
    primitive(1128, 51, 0);
    primitive(877, 51, 1);
    primitive(878, 51, 2);
    primitive(860, 53, 0);
    primitive(861, 53, 2);
    primitive(862, 53, 4);
    primitive(863, 53, 6);
    primitive(1146, 52, 0);
    primitive(1147, 52, 1);
    primitive(1148, 52, 2);
    primitive(1149, 52, 3);
    primitive(1150, 52, 4);
    primitive(1151, 52, 5);
    primitive(875, 49, 30);
    primitive(876, 49, 31);
    hash[9003].rh = 876;
    eqtb[9517] = eqtb[cur_val];
    primitive(1170, 93, 1);
    primitive(1171, 93, 2);
    primitive(1172, 93, 4);
    primitive(1173, 97, 0);
    primitive(1174, 97, 1);
    primitive(1175, 97, 2);
    primitive(1176, 97, 3);
    primitive(1190, 94, 0);
    primitive(1191, 94, 1);
    primitive(1192, 95, 0);
    primitive(1193, 95, 1);
    primitive(1194, 95, 2);
    primitive(1195, 95, 3);
    primitive(1196, 95, 4);
    primitive(1197, 95, 5);
    primitive(1198, 95, 6);
    primitive(415, 85, 10883);
    primitive(419, 85, 11907);
    primitive(416, 85, 11139);
    primitive(417, 85, 11395);
    primitive(418, 85, 11651);
    primitive(477, 85, 12474);
    primitive(412, 86, 10835);
    primitive(413, 86, 10851);
    primitive(414, 86, 10867);
    primitive(940, 99, 0);
    primitive(952, 99, 1);
    primitive(1216, 78, 0);
    primitive(1217, 78, 1);
    primitive(274, 100, 0);
    primitive(275, 100, 1);
    primitive(276, 100, 2);
    primitive(1226, 100, 3);
    primitive(1227, 60, 1);
    primitive(1228, 60, 0);
    primitive(1229, 58, 0);
    primitive(1230, 58, 1);
    primitive(1236, 57, 11139);
    primitive(1237, 57, 11395);
    primitive(1238, 19, 0);
    primitive(1239, 19, 1);
    primitive(1240, 19, 2);
    primitive(1241, 19, 3);
    primitive(1284, 59, 0);
    primitive(594, 59, 1);
    write_loc = cur_val;
    primitive(1285, 59, 2);
    primitive(1286, 59, 3);
    primitive(1287, 59, 4);
    primitive(1288, 59, 5);
    no_new_control_sequence = true;
  }
  virtual void typeset(const std::initializer_list<const char *> &args) {
    getopt(args);
    if (setjmp(_JL9998))
      goto _L9998;
    if (setjmp(_JL9999))
      goto _L9999;
    history = 3;
    term_out = output_stream;
    if (!term_out)
      io_error(errno, "TTY:");
    if (ready_already == 314159)
      goto _L1;
    initialize();
    if (!get_strings_started())
      goto _L9999;
    init_prim();
    init_str_ptr = str_ptr;
    init_pool_ptr = pool_ptr;
    fix_date_and_time();
    ready_already = 314159;
  _L1:
    selector = 17;
    tally = 0;
    term_offset = 0;
    file_offset = 0;
    fprintf(term_out, "This is TeX, Version 3.14159265");
    if (!format_ident) {
      fprintf(term_out, " (no format preloaded)\n");
    } else {
      slow_print(format_ident);
      print_ln();
    }
    fflush(term_out);
    errno = 0;
    job_name = 0;
    name_in_progress = false;
    log_opened = false;
    output_file_name = 0;
    input_ptr = 0;
    max_in_stack = 0;
    in_open = 0;
    open_parens = 0;
    max_buf_stack = 0;
    param_ptr = 0;
    max_param_stack = 0;
    first = buf_size;
    do {
      buffer[first] = 0;
      --first;
    } while (first);
    scanner_status = 0;
    warning_index = -1073741824;
    first = 1;
    cur_input.state_field = 33;
    cur_input.start_field = 1;
    cur_input.index_field = 0;
    line = 0;
    cur_input.name_field = 0;
    force_eof = false;
    align_state = 1000000;
    if (!init_terminal())
      goto _L9999;
    cur_input.limit_field = last;
    first = last + 1;
    if ((!format_ident) || (buffer[cur_input.loc_field] == 38)) {
      if (format_ident)
        initialize();
      if (!open_fmt_file())
        goto _L9999;
      if (!load_fmt_file()) {
        w_close(fmt_file);
        goto _L9999;
      }
      w_close(fmt_file);
      while ((cur_input.loc_field < cur_input.limit_field) &&
             (buffer[cur_input.loc_field] == 32))
        ++cur_input.loc_field;
    }
    if (((unsigned)eqtb[12211].int_) > 255)
      --cur_input.limit_field;
    else
      buffer[cur_input.limit_field] = eqtb[12211].int_;
    fix_date_and_time();
    magic_offset = str_start[891] - 144;
    if (!interaction)
      selector = 16;
    else
      selector = 17;
    if ((cur_input.loc_field < cur_input.limit_field) &&
        eqtb[buffer[cur_input.loc_field] + 10883].hh.rh)
      start_input();
    history = 0;
    main_control();
    final_cleanup();
  _L9998:
    close_files_and_terminate();
  _L9999:
    ready_already = 0;
    if (term_in)
      fclose(term_in);
    if (term_out)
      fclose(term_out);
    if (pool_file)
      fclose(pool_file);
    if (log_file)
      fclose(log_file);
    if (dvi_file)
      fclose(dvi_file);
    if (tfm_file)
      fclose(tfm_file);
    if (fmt_file)
      fclose(fmt_file);
    return;
  }
  // End.

  FILE *output_stream; // displays the logging messages
  char *input_stream_buf;
  size_t input_stream_len;
  FILE *input_stream;  // stores the command line args

  virtual void getopt(const std::initializer_list<const char *> &args) {
    for (auto arg : args)
        // ' ' must come first, the first character is always skipped…
		fprintf(input_stream, " %s", arg);
  }

  // inexplicably, p2c forgets these
  int tfm_file_mode;
  uint8_t tfm_file_value;
  int fmt_file_mode;
  memory_word fmt_file_value;

  tex()
      : fmt_file_value({0}), tfm_file_mode(0), tfm_file_value(0),
        fmt_file_mode(0), // clear members added above
        fmt_file(nullptr), tfm_file(nullptr), dvi_file(nullptr),
        log_file(nullptr), pool_file(nullptr), term_out(nullptr),
        term_in(nullptr) // clear file pointers
  {}

  virtual ~tex() = default;
};

class plain : public tex {

  std::string output_path;  // directory to store output files in
  std::string input_path;   // directory to search input files for

  bool a_open_in(FILE *&ios) override {
    bool found = tex::a_open_in(ios);

    if (found == false && strncmp("null.tex", name_of_file, 8) == 0) {
		fprintf(stderr, "invalid case input-stream-buffer!!n");
		throw std::runtime_error("boo");
      found = true;
    }

    if (found == false) {
      const std::string &absolute_path =
          input_path +
          name_of_file; // look relative to the the input directory; user macro
                        // definitions will be found there
      strncpy(name_of_file, absolute_path.c_str(), file_name_size - 1);

      found = tex::a_open_in(ios);
    }

    if (found == false) {
      const std::string &absolute_path =
          output_path + name_of_file; // look in the output directory;
                                      // intermediate files will be found there
      strncpy(name_of_file, absolute_path.c_str(), file_name_size - 1);

      found = tex::a_open_in(ios);
    }

    return found;
  }

  bool b_open_in(FILE *&ios) override {
    bool found = tex::a_open_in(ios);

    if (found == false) {
      const std::string &absolute_path = input_path + name_of_file;
      strncpy(name_of_file, absolute_path.c_str(), file_name_size - 1);

      found = tex::a_open_in(ios);
    }

    return found;
  }

  bool a_open_out(FILE *&ios) override {
    std::string absolute_path = output_path + name_of_file;
    strncpy(name_of_file, absolute_path.c_str(), file_name_size - 1);

    return tex::a_open_out(ios);
  }

  bool b_open_out(FILE *&ios) override {
    std::string absolute_path = output_path + name_of_file;
    strncpy(name_of_file, absolute_path.c_str(), file_name_size - 1);

    return tex::b_open_out(ios);
  }

  bool w_open_out(FILE *&ios) override {
    std::string absolute_path = output_path + name_of_file;
    strncpy(name_of_file, absolute_path.c_str(), file_name_size - 1);

    return tex::w_open_out(ios);
  }

  void open_log_file() override {
   // log_file =
   //     new std::iostream(nullptr); // we already capture the term_out as a
   //                                 // stream; a file based copy is unnecessary
  }

public:
  virtual void typeset(const std::string &filename,
					   const std::string &result,
                       const std::string &search_dir,
                       const std::string &working_dir,
					   const std::string &output) {
    input_path = search_dir;
    if (input_path.empty() == false and input_path.back() != '/')
      input_path.push_back('/');

    output_path = working_dir;
    if (output_path.empty() == false and output_path.back() != '/')
      output_path.push_back('/');

    input_stream = open_memstream(&input_stream_buf, &input_stream_len); // will be closed as term_in
    output_stream = fopen(output.c_str(), "w"); // will be closed as term_out

	dvi_file = fopen(result.c_str(), "w");

    tex::typeset({
        R"(\nonstopmode)", // omits all stops (\batchmode also omits terminal
                           // output)
        R"(\input plain)",
        R"(\input)",
        filename.c_str(),
        R"(\end)",
    });
  }

};

} // namespace tex
