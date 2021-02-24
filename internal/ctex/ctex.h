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

#include "ctex-cgo.h"
#include "ctex-consts.h"
#include "ctex-dvi.h"
#include "ctex-font-info.h"
#include "ctex-types.h"

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

void initialize(ctex_t *ctx);
void print_ln(ctex_t *ctx);
void print_char(ctex_t *ctx, ASCII_code s);
void print(ctex_t *ctx, integer s);
void slow_print(ctex_t *ctx, integer s);
void print_nl(ctex_t *ctx, str_number s);
void print_esc(ctex_t *ctx, str_number s);
void print_the_digs(ctex_t *ctx, uint8_t k);
void print_int(ctex_t *ctx, integer n);
void print_cs(ctex_t *ctx, integer p);
void sprint_cs(ctex_t *ctx, halfword p);
void print_file_name(ctex_t *ctx, integer n, integer a, integer e);
void print_size(ctex_t *ctx, integer s);
void print_write_whatsit(ctex_t *ctx, str_number s, halfword p);
void jump_out(ctex_t *ctx);
void error(ctex_t *ctx);
void fatal_error(ctex_t *ctx, str_number s);
void overflow(ctex_t *ctx, str_number s, integer n);
void confusion(ctex_t *ctx, str_number s);
bool_t a_open_in(ctex_t *ctx, FILE **f);
bool_t a_open_out(ctex_t *ctx, FILE **f);
bool_t b_open_in(ctex_t *ctx, FILE **f);
bool_t b_open_out(ctex_t *ctx, FILE **f);
bool_t w_open_in(ctex_t *ctx, FILE **f);
bool_t w_open_out(ctex_t *ctx, FILE **f);
void a_close(ctex_t *ctx, FILE **f);
void b_close(ctex_t *ctx, FILE **f);
void w_close(ctex_t *ctx, FILE **f);
bool_t input_ln(ctex_t *ctx, FILE *f, bool_t bypass_eoln);
bool_t init_terminal(ctex_t *ctx);
str_number make_string(ctex_t *ctx);
bool_t str_eq_buf(ctex_t *ctx, str_number s, integer k);
bool_t str_eq_str(ctex_t *ctx, str_number s, str_number t);
bool_t get_strings_started(ctex_t *ctx);
void print_two(ctex_t *ctx, integer n);
void print_hex(ctex_t *ctx, integer n);
void print_roman_int(ctex_t *ctx, integer n);
void print_current_string(ctex_t *ctx);
void term_input(ctex_t *ctx);
void int_error(ctex_t *ctx, integer n);
void normalize_selector(ctex_t *ctx);
void pause_for_instructions(ctex_t *ctx);
integer half(ctex_t *ctx, integer x);
scaled round_decimals(ctex_t *ctx, small_number k);
void print_scaled(ctex_t *ctx, scaled s);
scaled mult_and_add(ctex_t *ctx, integer n, scaled x, scaled y,
                    scaled max_answer);
scaled x_over_n(ctex_t *ctx, scaled x, integer n);
scaled xn_over_d(ctex_t *ctx, scaled x, integer n, integer d);
halfword badness(ctex_t *ctx, scaled t, scaled s);
void show_token_list(ctex_t *ctx, integer p, integer q, integer l);
void runaway(ctex_t *ctx);
halfword get_avail(ctex_t *ctx);
void flush_list(ctex_t *ctx, halfword p);
halfword get_node(ctex_t *ctx, integer s);
void free_node(ctex_t *ctx, halfword p, halfword s);
void sort_avail(ctex_t *ctx);
halfword new_null_box(ctex_t *ctx);
halfword new_rule(ctex_t *ctx);
halfword new_ligature(ctex_t *ctx, quarterword f, quarterword c, halfword q);
halfword new_lig_item(ctex_t *ctx, quarterword c);
halfword new_disc(ctex_t *ctx);
halfword new_math(ctex_t *ctx, scaled w, small_number s);
halfword new_spec(ctex_t *ctx, halfword p);
halfword new_param_glue(ctex_t *ctx, small_number n);
halfword new_glue(ctex_t *ctx, halfword q);
halfword new_skip_param(ctex_t *ctx, small_number n);
halfword new_kern(ctex_t *ctx, scaled w);
halfword new_penalty(ctex_t *ctx, integer m);
void short_display(ctex_t *ctx, integer p);
void print_font_and_char(ctex_t *ctx, integer p);
void print_mark(ctex_t *ctx, integer p);
void print_rule_dimen(ctex_t *ctx, scaled d);
void print_glue(ctex_t *ctx, scaled d, integer order, str_number s);
void print_spec(ctex_t *ctx, integer p, str_number s);
void print_fam_and_char(ctex_t *ctx, halfword p);
void print_delimiter(ctex_t *ctx, halfword p);
void print_subsidiary_data(ctex_t *ctx, halfword p, ASCII_code c);
void print_style(ctex_t *ctx, integer c);
void print_skip_param(ctex_t *ctx, integer n);
void show_node_list(ctex_t *ctx, integer p);
void show_box(ctex_t *ctx, halfword p);
void delete_token_ref(ctex_t *ctx, halfword p);
void delete_glue_ref(ctex_t *ctx, halfword p);
void flush_node_list(ctex_t *ctx, halfword p);
halfword copy_node_list(ctex_t *ctx, halfword p);
void print_mode(ctex_t *ctx, integer m);
void push_nest(ctex_t *ctx);
void pop_nest(ctex_t *ctx);
void show_activities(ctex_t *ctx);
void print_param(ctex_t *ctx, integer n);
void fix_date_and_time(ctex_t *ctx);
void begin_diagnostic(ctex_t *ctx);
void end_diagnostic(ctex_t *ctx, bool_t blank_line);
void print_length_param(ctex_t *ctx, integer n);
void print_cmd_chr(ctex_t *ctx, quarterword cmd, halfword chr_code);
halfword id_lookup(ctex_t *ctx, integer j, integer l);
void primitive(ctex_t *ctx, str_number s, quarterword c, halfword o);
void new_save_level(ctex_t *ctx, group_code c);
void eq_destroy(ctex_t *ctx, memory_word w);
void eq_save(ctex_t *ctx, halfword p, quarterword l);
void eq_define(ctex_t *ctx, halfword p, quarterword t, halfword e);
void eq_word_define(ctex_t *ctx, halfword p, integer w);
void geq_define(ctex_t *ctx, halfword p, quarterword t, halfword e);
void geq_word_define(ctex_t *ctx, halfword p, integer w);
void save_for_after(ctex_t *ctx, halfword t);
void unsave(ctex_t *ctx);
void prepare_mag(ctex_t *ctx);
void token_show(ctex_t *ctx, halfword p);
void print_meaning(ctex_t *ctx);
void show_cur_cmd_chr(ctex_t *ctx);
void show_context(ctex_t *ctx);
void begin_token_list(ctex_t *ctx, halfword p, quarterword t);
void end_token_list(ctex_t *ctx);
void back_input(ctex_t *ctx);
void back_error(ctex_t *ctx);
void ins_error(ctex_t *ctx);
void begin_file_reading(ctex_t *ctx);
void end_file_reading(ctex_t *ctx);
void clear_for_error_prompt(ctex_t *ctx);
void check_outer_validity(ctex_t *ctx);
void get_next(ctex_t *ctx);
void firm_up_the_line(ctex_t *ctx);
void get_token(ctex_t *ctx);
void macro_call(ctex_t *ctx);
void insert_relax(ctex_t *ctx);
void expand(ctex_t *ctx);
void get_x_token(ctex_t *ctx);
void x_token(ctex_t *ctx);
void scan_left_brace(ctex_t *ctx);
void scan_optional_equals(ctex_t *ctx);
bool_t scan_keyword(ctex_t *ctx, str_number s);
void mu_error(ctex_t *ctx);
void scan_eight_bit_int(ctex_t *ctx);
void scan_char_num(ctex_t *ctx);
void scan_four_bit_int(ctex_t *ctx);
void scan_fifteen_bit_int(ctex_t *ctx);
void scan_twenty_seven_bit_int(ctex_t *ctx);
void scan_font_ident(ctex_t *ctx);
void find_font_dimen(ctex_t *ctx, bool_t writing);
void scan_something_internal(ctex_t *ctx, small_number level, bool_t negative);
void scan_int(ctex_t *ctx);
void scan_dimen(ctex_t *ctx, bool_t mu, bool_t inf, bool_t shortcut);
void scan_glue(ctex_t *ctx, small_number level);
halfword scan_rule_spec(ctex_t *ctx);
halfword str_toks(ctex_t *ctx, pool_pointer b);
halfword the_toks(ctex_t *ctx);
void ins_the_toks(ctex_t *ctx);
void conv_toks(ctex_t *ctx);
halfword scan_toks(ctex_t *ctx, bool_t macro_def, bool_t xpand);
void read_toks(ctex_t *ctx, integer n, halfword r);
void pass_text(ctex_t *ctx);
void change_if_limit(ctex_t *ctx, small_number l, halfword p);
void conditional(ctex_t *ctx);
void begin_name(ctex_t *ctx);
bool_t more_name(ctex_t *ctx, ASCII_code c);
void end_name(ctex_t *ctx);
void pack_file_name(ctex_t *ctx, str_number n, str_number a, str_number e);
void pack_buffered_name(ctex_t *ctx, small_number n, integer a, integer b);
str_number make_name_string(ctex_t *ctx);
str_number a_make_name_string(ctex_t *ctx, FILE *f);
str_number b_make_name_string(ctex_t *ctx, FILE *f);
str_number w_make_name_string(ctex_t *ctx, FILE *f);
void scan_file_name(ctex_t *ctx);
void pack_job_name(ctex_t *ctx, str_number s);
void prompt_file_name(ctex_t *ctx, str_number s, str_number e);
void open_log_file(ctex_t *ctx);
void start_input(ctex_t *ctx);
internal_font_number read_font_info(ctex_t *ctx, halfword u, str_number nom,
                                    str_number aire, scaled s);
void char_warning(ctex_t *ctx, internal_font_number f, uint8_t c);
halfword new_character(ctex_t *ctx, internal_font_number f, uint8_t c);
void write_dvi(ctex_t *ctx, dvi_index a, dvi_index b);
void dvi_swap(ctex_t *ctx);
void dvi_four(ctex_t *ctx, integer x);
void dvi_pop(ctex_t *ctx, integer l);
void dvi_font_def(ctex_t *ctx, internal_font_number f);
void movement(ctex_t *ctx, scaled w, uint8_t o);
void prune_movements(ctex_t *ctx, integer l);
void special_out(ctex_t *ctx, halfword p);
void write_out(ctex_t *ctx, halfword p);
void out_what(ctex_t *ctx, halfword p);
void hlist_out(ctex_t *ctx);
void vlist_out(ctex_t *ctx);
void ship_out(ctex_t *ctx, halfword p);
void scan_spec(ctex_t *ctx, group_code c, bool_t three_codes);
halfword hpack(ctex_t *ctx, halfword p, scaled w, small_number m);
halfword vpackage(ctex_t *ctx, halfword p, scaled h, small_number m, scaled l);
void append_to_vlist(ctex_t *ctx, halfword b);
halfword new_noad(ctex_t *ctx);
halfword new_style(ctex_t *ctx, small_number s);
halfword new_choice(ctex_t *ctx);
void show_info(ctex_t *ctx);
halfword fraction_rule(ctex_t *ctx, scaled t);
halfword overbar(ctex_t *ctx, halfword b, scaled k, scaled t);
halfword char_box(ctex_t *ctx, internal_font_number f, quarterword c);
void stack_into_box(ctex_t *ctx, halfword b, internal_font_number f,
                    quarterword c);
scaled height_plus_depth(ctex_t *ctx, internal_font_number f, quarterword c);
halfword var_delimiter(ctex_t *ctx, halfword d, small_number s, scaled v);
halfword rebox(ctex_t *ctx, halfword b, scaled w);
halfword math_glue(ctex_t *ctx, halfword g, scaled m);
void math_kern(ctex_t *ctx, halfword p, scaled m);
void flush_math(ctex_t *ctx);
halfword clean_box(ctex_t *ctx, halfword p, small_number s);
void fetch(ctex_t *ctx, halfword a);
void make_over(ctex_t *ctx, halfword q);
void make_under(ctex_t *ctx, halfword q);
void make_vcenter(ctex_t *ctx, halfword q);
void make_radical(ctex_t *ctx, halfword q);
void make_math_accent(ctex_t *ctx, halfword q);
void make_fraction(ctex_t *ctx, halfword q);
scaled make_op(ctex_t *ctx, halfword q);
void make_ord(ctex_t *ctx, halfword q);
void make_scripts(ctex_t *ctx, halfword q, scaled delta);
small_number make_left_right(ctex_t *ctx, halfword q, small_number style,
                             scaled max_d, scaled max_h);
void mlist_to_hlist(ctex_t *ctx);
void push_alignment(ctex_t *ctx);
void pop_alignment(ctex_t *ctx);
void get_preamble_token(ctex_t *ctx);
void init_align(ctex_t *ctx);
void init_span(ctex_t *ctx, halfword p);
void init_row(ctex_t *ctx);
void init_col(ctex_t *ctx);
bool_t fin_col(ctex_t *ctx);
void fin_row(ctex_t *ctx);
void fin_align(ctex_t *ctx);
void align_peek(ctex_t *ctx);
halfword finite_shrink(ctex_t *ctx, halfword p);
void try_break(ctex_t *ctx, integer pi, small_number break_type);
void post_line_break(ctex_t *ctx, integer final_widow_penalty);
small_number reconstitute(ctex_t *ctx, small_number j, small_number n,
                          halfword bchar, halfword hchar);
void hyphenate(ctex_t *ctx);
quarterword new_trie_op(ctex_t *ctx, small_number d, small_number n,
                        quarterword v);
trie_pointer trie_node(ctex_t *ctx, trie_pointer p);
trie_pointer compress_trie(ctex_t *ctx, trie_pointer p);
void first_fit(ctex_t *ctx, trie_pointer p);
void trie_pack(ctex_t *ctx, trie_pointer p);
void trie_fix(ctex_t *ctx, trie_pointer p);
void new_patterns(ctex_t *ctx);
void init_trie(ctex_t *ctx);
void line_break(ctex_t *ctx, integer final_widow_penalty);
void new_hyph_exceptions(ctex_t *ctx);
halfword prune_page_top(ctex_t *ctx, halfword p);
halfword vert_break(ctex_t *ctx, halfword p, scaled h, scaled d);
halfword vsplit(ctex_t *ctx, uint8_t n, scaled h);
void print_totals(ctex_t *ctx);
void freeze_page_specs(ctex_t *ctx, small_number s);
void box_error(ctex_t *ctx, uint8_t n);
void ensure_vbox(ctex_t *ctx, uint8_t n);
void fire_up(ctex_t *ctx, halfword c);
void build_page(ctex_t *ctx);
void app_space(ctex_t *ctx);
void insert_dollar_sign(ctex_t *ctx);
void you_cant(ctex_t *ctx);
void report_illegal_case(ctex_t *ctx);
bool_t privileged(ctex_t *ctx);
bool_t its_all_over(ctex_t *ctx);
void append_glue(ctex_t *ctx);
void append_kern(ctex_t *ctx);
void off_save(ctex_t *ctx);
void extra_right_brace(ctex_t *ctx);
void normal_paragraph(ctex_t *ctx);
void box_end(ctex_t *ctx, integer box_context);
void begin_box(ctex_t *ctx, integer box_context);
void scan_box(ctex_t *ctx, integer box_context);
void package(ctex_t *ctx, small_number c);
small_number norm_min(ctex_t *ctx, integer h);
void new_graf(ctex_t *ctx, bool_t indented);
void indent_in_hmode(ctex_t *ctx);
void head_for_vmode(ctex_t *ctx);
void end_graf(ctex_t *ctx);
void begin_insert_or_adjust(ctex_t *ctx);
void make_mark(ctex_t *ctx);
void append_penalty(ctex_t *ctx);
void delete_last(ctex_t *ctx);
void unpackage(ctex_t *ctx);
void append_italic_correction(ctex_t *ctx);
void append_discretionary(ctex_t *ctx);
void build_discretionary(ctex_t *ctx);
void make_accent(ctex_t *ctx);
void align_error(ctex_t *ctx);
void no_align_error(ctex_t *ctx);
void omit_error(ctex_t *ctx);
void do_endv(ctex_t *ctx);
void cs_error(ctex_t *ctx);
void push_math(ctex_t *ctx, group_code c);
void init_math(ctex_t *ctx);
void start_eq_no(ctex_t *ctx);
void scan_math(ctex_t *ctx, halfword p);
void set_math_char(ctex_t *ctx, integer c);
void math_limit_switch(ctex_t *ctx);
void scan_delimiter(ctex_t *ctx, halfword p, bool_t r);
void math_radical(ctex_t *ctx);
void math_ac(ctex_t *ctx);
void append_choices(ctex_t *ctx);
halfword fin_mlist(ctex_t *ctx, halfword p);
void build_choices(ctex_t *ctx);
void sub_sup(ctex_t *ctx);
void math_fraction(ctex_t *ctx);
void math_left_right(ctex_t *ctx);
void after_math(ctex_t *ctx);
void resume_after_display(ctex_t *ctx);
void get_r_token(ctex_t *ctx);
void trap_zero_glue(ctex_t *ctx);
void do_register_command(ctex_t *ctx, small_number a);
void alter_aux(ctex_t *ctx);
void alter_prev_graf(ctex_t *ctx);
void alter_page_so_far(ctex_t *ctx);
void alter_integer(ctex_t *ctx);
void alter_box_dimen(ctex_t *ctx);
void new_font(ctex_t *ctx, small_number a);
void new_interaction(ctex_t *ctx);
void prefixed_command(ctex_t *ctx);
void do_assignments(ctex_t *ctx);
void open_or_close_in(ctex_t *ctx);
void issue_message(ctex_t *ctx);
void shift_case(ctex_t *ctx);
void show_whatever(ctex_t *ctx);
void store_fmt_file(ctex_t *ctx);
void new_whatsit(ctex_t *ctx, small_number s, small_number w);
void new_write_whatsit(ctex_t *ctx, small_number w);
void do_extension(ctex_t *ctx);
void fix_language(ctex_t *ctx);
void handle_right_brace(ctex_t *ctx);
void main_control(ctex_t *ctx);
void give_err_help(ctex_t *ctx);
bool_t open_fmt_file(ctex_t *ctx);
bool_t load_fmt_file(ctex_t *ctx);
void close_files_and_terminate(ctex_t *ctx);
void final_cleanup(ctex_t *ctx);
void init_prim(ctex_t *ctx);
void getopt(ctex_t *ctx, int argc, const char **args);
void typeset(ctex_t *ctx, int argc, const char **args);
void process(ctex_t *ctx, const char *tex_fname, const char *dvi_ofname,
             const char *serach_dir, const char *work_dir,
             const char *err_oname);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // CTEX_TEX_H
