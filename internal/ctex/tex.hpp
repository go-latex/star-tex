// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef CTEX_TEX_HPP
#define CTEX_TEX_HPP 1

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

#include "ctex-capi-cgo.h"
#include "ctex-capi-consts.h"
#include "ctex-capi-dvi.h"
#include "ctex-capi-font-info.h"
#include "ctex-capi-types.h"

namespace tex {

class tex {

protected:
  // Output from p2c 1.21alpha-07.Dec.93, the Pascal-to-C translator
  integer bad, tally, trick_count, first_count, interrupt, var_used, dyn_used,
      font_in_short_display, depth_threshold, breadth_max, cs_count, mag_set,
      line, max_param_stack, align_state, cur_val, if_line, skip_line, max_push,
      last_bop, dead_cycles, lq, lr, cur_s, last_badness, pack_begin_line,
      magic_offset, threshold, minimum_demerits, fewest_demerits,
      actual_looseness, line_diff, hyf_char, l_hyf, r_hyf, init_l_hyf,
      init_r_hyf, least_page_cost, last_penalty, insert_penalties, main_s,
      ready_already;

  ctex_dvi_t dvi_mgr;
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
  scaled remainder_, max_v, max_h, rule_ht, rule_dp, rule_wd, cur_h, cur_v,
      cur_mu, disc_width, first_width, second_width, first_indent,
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
  str_number output_file_name, log_name;
  FILE *tfm_file;

  std::vector<memory_word> font_info;
  font_index fmem_ptr;
  internal_font_number font_ptr;
  ctex_font_info_t fnt_infos;

  four_quarters null_character;
  bool doing_leaders;
  quarterword c, f;
  halfword g;
  halfword down_ptr, right_ptr;
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

  void loadU8(FILE *r, int &mode, uint8_t *v) {
    if (mode == 1) {
      fread(v, sizeof(uint8_t), 1, r);
    } else {
      mode = 1;
    }
  }

  uint8_t &readU8(FILE *r, int &mode, uint8_t *v) {
    if (mode == 1) {
      mode = 2;
      fread(v, sizeof(uint8_t), 1, r);
    }
    return *v;
  }

  void loadU32(FILE *r, int &mode, memory_word *v) {
    if (mode == 1) {
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

  static int erstat(FILE *f) { return f == nullptr or (ferror(f) != 0); }

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

  void initialize();

  void print_ln();
  void print_char(ASCII_code s);
  void print(integer s);
  void slow_print(integer s);
  void print_nl(str_number s);
  void print_esc(str_number s);
  void print_the_digs(uint8_t k);
  void print_int(integer n);
  void print_cs(integer p);
  void sprint_cs(halfword p);
  void print_file_name(integer n, integer a, integer e);
  void print_size(integer s);
  void print_write_whatsit(str_number s, halfword p);

  jmp_buf _JL9998;
  void jump_out() { longjmp(_JL9998, 1); }

  void error();
  void fatal_error(str_number s);
  void overflow(str_number s, integer n);
  void confusion(str_number s);

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
  bool input_ln(FILE *f, bool bypass_eoln);
  bool init_terminal();
  str_number make_string();
  bool str_eq_buf(str_number s, integer k);
  bool str_eq_str(str_number s, str_number t);
  bool get_strings_started();
  void print_two(integer n);
  void print_hex(integer n);
  void print_roman_int(integer n);
  void print_current_string();
  void term_input();
  void int_error(integer n);
  void normalize_selector();
  void pause_for_instructions();
  integer half(integer x);
  scaled round_decimals(small_number k);
  void print_scaled(scaled s);
  scaled mult_and_add(integer n, scaled x, scaled y, scaled max_answer);
  scaled x_over_n(scaled x, integer n);
  scaled xn_over_d(scaled x, integer n, integer d);
  halfword badness(scaled t, scaled s);
  void show_token_list(integer p, integer q, integer l);
  void runaway();
  halfword get_avail();
  void flush_list(halfword p);
  halfword get_node(integer s);
  void free_node(halfword p, halfword s);
  void sort_avail();
  halfword new_null_box();
  halfword new_rule();
  halfword new_ligature(quarterword f, quarterword c, halfword q);
  halfword new_lig_item(quarterword c);
  halfword new_disc();
  halfword new_math(scaled w, small_number s);
  halfword new_spec(halfword p);
  halfword new_param_glue(small_number n);
  halfword new_glue(halfword q);
  halfword new_skip_param(small_number n);
  halfword new_kern(scaled w);
  halfword new_penalty(integer m);
  void short_display(integer p);
  void print_font_and_char(integer p);
  void print_mark(integer p);
  void print_rule_dimen(scaled d);
  void print_glue(scaled d, integer order, str_number s);
  void print_spec(integer p, str_number s);
  void print_fam_and_char(halfword p);
  void print_delimiter(halfword p);
  void print_subsidiary_data(halfword p, ASCII_code c);
  void print_style(integer c);
  void print_skip_param(integer n);
  void show_node_list(integer p);
  void show_box(halfword p);
  void delete_token_ref(halfword p);
  void delete_glue_ref(halfword p);
  void flush_node_list(halfword p);
  halfword copy_node_list(halfword p);
  void print_mode(integer m);
  void push_nest();
  void pop_nest();
  void show_activities();
  void print_param(integer n);
  void fix_date_and_time();
  void begin_diagnostic();
  void end_diagnostic(bool blank_line);
  void print_length_param(integer n);
  void print_cmd_chr(quarterword cmd, halfword chr_code);
  halfword id_lookup(integer j, integer l);
  void primitive(str_number s, quarterword c, halfword o);
  void new_save_level(group_code c);
  void eq_destroy(memory_word w);
  void eq_save(halfword p, quarterword l);
  void eq_define(halfword p, quarterword t, halfword e);
  void eq_word_define(halfword p, integer w);
  void geq_define(halfword p, quarterword t, halfword e);
  void geq_word_define(halfword p, integer w);
  void save_for_after(halfword t);
  void unsave();
  void prepare_mag();
  void token_show(halfword p);
  void print_meaning();
  void show_cur_cmd_chr();
  void show_context();
  void begin_token_list(halfword p, quarterword t);
  void end_token_list();
  void back_input();
  void back_error();
  void ins_error();
  void begin_file_reading();
  void end_file_reading();
  void clear_for_error_prompt();
  void check_outer_validity();
  void get_next();
  void firm_up_the_line();
  void get_token();
  void macro_call();
  void insert_relax();
  void expand();
  void get_x_token();
  void x_token();
  void scan_left_brace();
  void scan_optional_equals();
  bool scan_keyword(str_number s);
  void mu_error();
  void scan_eight_bit_int();
  void scan_char_num();
  void scan_four_bit_int();
  void scan_fifteen_bit_int();
  void scan_twenty_seven_bit_int();
  void scan_font_ident();
  void find_font_dimen(bool writing);
  void scan_something_internal(small_number level, bool negative);
  void scan_int();
  void scan_dimen(bool mu, bool inf, bool shortcut);
  void scan_glue(small_number level);
  halfword scan_rule_spec();
  halfword str_toks(pool_pointer b);
  halfword the_toks();
  void ins_the_toks();
  void conv_toks();
  halfword scan_toks(bool macro_def, bool xpand);
  void read_toks(integer n, halfword r);
  void pass_text();
  void change_if_limit(small_number l, halfword p);
  void conditional();
  void begin_name();
  bool more_name(ASCII_code c);
  void end_name();
  void pack_file_name(str_number n, str_number a, str_number e);
  void pack_buffered_name(small_number n, integer a, integer b);
  str_number make_name_string();
  str_number a_make_name_string(FILE *f) { return make_name_string(); }
  str_number b_make_name_string(FILE *f) { return make_name_string(); }
  str_number w_make_name_string(FILE *f) { return make_name_string(); }
  void scan_file_name();
  void pack_job_name(str_number s);
  void prompt_file_name(str_number s, str_number e);

  virtual void open_log_file();

  void start_input();
  internal_font_number read_font_info(halfword u, str_number nom,
                                      str_number aire, scaled s);

  void char_warning(internal_font_number f, uint8_t c);
  halfword new_character(internal_font_number f, uint8_t c);

  void write_dvi(dvi_index a, dvi_index b);
  void dvi_swap();
  void dvi_four(integer x);
  void dvi_pop(integer l);
  void dvi_font_def(internal_font_number f);
  void movement(scaled w, uint8_t o);
  void prune_movements(integer l);
  void special_out(halfword p);
  void write_out(halfword p);
  void out_what(halfword p);
  void hlist_out();
  void vlist_out();
  void ship_out(halfword p);
  void scan_spec(group_code c, bool three_codes);
  halfword hpack(halfword p, scaled w, small_number m);
  halfword vpackage(halfword p, scaled h, small_number m, scaled l);
  void append_to_vlist(halfword b);
  halfword new_noad();
  halfword new_style(small_number s);
  halfword new_choice();
  void show_info();
  halfword fraction_rule(scaled t);
  halfword overbar(halfword b, scaled k, scaled t);
  halfword char_box(internal_font_number f, quarterword c);
  void stack_into_box(halfword b, internal_font_number f, quarterword c);
  scaled height_plus_depth(internal_font_number f, quarterword c);
  halfword var_delimiter(halfword d, small_number s, scaled v);
  halfword rebox(halfword b, scaled w);
  halfword math_glue(halfword g, scaled m);
  void math_kern(halfword p, scaled m);
  void flush_math();
  halfword clean_box(halfword p, small_number s);
  void fetch(halfword a);
  void make_over(halfword q);
  void make_under(halfword q);
  void make_vcenter(halfword q);
  void make_radical(halfword q);
  void make_math_accent(halfword q);
  void make_fraction(halfword q);
  scaled make_op(halfword q);
  void make_ord(halfword q);
  void make_scripts(halfword q, scaled delta);
  small_number make_left_right(halfword q, small_number style, scaled max_d,
                               scaled max_h);
  void mlist_to_hlist();
  void push_alignment();
  void pop_alignment();
  void get_preamble_token();
  void init_align();
  void init_span(halfword p);
  void init_row();
  void init_col();
  bool fin_col();
  void fin_row();
  void fin_align();
  void align_peek();
  halfword finite_shrink(halfword p);
  void try_break(integer pi, small_number break_type);
  void post_line_break(integer final_widow_penalty);
  small_number reconstitute(small_number j, small_number n, halfword bchar,
                            halfword hchar);
  void hyphenate();
  quarterword new_trie_op(small_number d, small_number n, quarterword v);
  trie_pointer trie_node(trie_pointer p);
  trie_pointer compress_trie(trie_pointer p);
  void first_fit(trie_pointer p);
  void trie_pack(trie_pointer p);
  void trie_fix(trie_pointer p);
  void new_patterns();
  void init_trie();
  void line_break(integer final_widow_penalty);
  void new_hyph_exceptions();
  halfword prune_page_top(halfword p);
  halfword vert_break(halfword p, scaled h, scaled d);
  halfword vsplit(uint8_t n, scaled h);
  void print_totals();
  void freeze_page_specs(small_number s);
  void box_error(uint8_t n);
  void ensure_vbox(uint8_t n);
  void fire_up(halfword c);
  void build_page();
  void app_space();
  void insert_dollar_sign();
  void you_cant();
  void report_illegal_case();
  bool privileged();
  bool its_all_over();
  void append_glue();
  void append_kern();
  void off_save();
  void extra_right_brace();
  void normal_paragraph();
  void box_end(integer box_context);
  void begin_box(integer box_context);
  void scan_box(integer box_context);
  void package(small_number c);
  small_number norm_min(integer h);
  void new_graf(bool indented);
  void indent_in_hmode();
  void head_for_vmode();
  void end_graf();
  void begin_insert_or_adjust();
  void make_mark();
  void append_penalty();
  void delete_last();
  void unpackage();
  void append_italic_correction();
  void append_discretionary();
  void build_discretionary();
  void make_accent();
  void align_error();
  void no_align_error();
  void omit_error();
  void do_endv();
  void cs_error();
  void push_math(group_code c);
  void init_math();
  void start_eq_no();
  void scan_math(halfword p);
  void set_math_char(integer c);
  void math_limit_switch();
  void scan_delimiter(halfword p, bool r);
  void math_radical();
  void math_ac();
  void append_choices();
  halfword fin_mlist(halfword p);
  void build_choices();
  void sub_sup();
  void math_fraction();
  void math_left_right();
  void after_math();
  void resume_after_display();
  void get_r_token();
  void trap_zero_glue();
  void do_register_command(small_number a);
  void alter_aux();
  void alter_prev_graf();
  void alter_page_so_far();
  void alter_integer();
  void alter_box_dimen();
  void new_font(small_number a);
  void new_interaction();
  void prefixed_command();
  void do_assignments();
  void open_or_close_in();
  void issue_message();
  void shift_case();
  void show_whatever();
  void store_fmt_file();
  void new_whatsit(small_number s, small_number w);
  void new_write_whatsit(small_number w);
  void do_extension();
  void fix_language();
  void handle_right_brace();
  void main_control();
  void give_err_help();
  bool open_fmt_file();
  bool load_fmt_file();
  void close_files_and_terminate();
  void final_cleanup();
  void init_prim();

  virtual void typeset(const std::initializer_list<const char *> &args);

  FILE *output_stream; // displays the logging messages
  char *input_stream_buf;
  size_t input_stream_len;
  FILE *input_stream; // stores the command line args

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
        fmt_file(nullptr), tfm_file(nullptr), log_file(nullptr),
        pool_file(nullptr), term_out(nullptr),
        term_in(nullptr) // clear file pointers
  {
    ctex_dvi_init(&dvi_mgr);
  }

  virtual ~tex() = default;
};

} // namespace tex

#endif // CTEX_TEX_HPP
