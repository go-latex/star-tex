// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "ctex.h"
#include "ctex-io.h"

#define true 1
#define false 0

void ctex_init_ctx(ctex_t *ctx) {
  ctx->fmt_file_value.int_ = 0;
  ctx->tfm_file_mode = 0;
  ctx->tfm_file_value = 0;
  ctx->fmt_file_mode = 0;
  ctx->fmt_file = NULL;
  ctx->tfm_file = NULL;
  ctx->log_file = NULL;
  ctx->pool_file = NULL;
  ctx->term_out = NULL;
  ctx->term_in = NULL;

  ctx->input_stream_buf = NULL;
  ctx->input_stream_len = 0;
  ctx->input_stream = NULL;

  ctex_dvi_init(&ctx->dvi_mgr);
}

void initialize(ctex_t *ctx) {
  integer k;
  hyph_pointer z;

  memset(ctx->buffer, 0, (buf_size + 1) * sizeof(ASCII_code));
  memset(ctx->str_pool, 0, (pool_size + 1) * sizeof(packed_ASCII_code));
  memset(ctx->str_start, 0, (max_strings + 1) * sizeof(pool_pointer));
  memset(ctx->mem, 0, (mem_max - mem_min + 1) * sizeof(memory_word));
  memset(ctx->font_info, 0, (font_mem_size + 1) * sizeof(memory_word));

  for (int i = 0; i < 256; i++) {
    ctx->xchr[i] = i;
  }
  for (int i = 0; i < 256; i++) {
    ctx->xord[i] = i;
  }

  ctx->interaction = 3;
  ctx->deletions_allowed = true;
  ctx->set_box_allowed = true;
  ctx->error_count = 0;
  ctx->help_ptr = 0;
  ctx->use_err_help = false;
  ctx->interrupt = 0;
  ctx->OK_to_interrupt = true;
  ctx->nest_ptr = 0;
  ctx->max_nest_stack = 0;
  ctx->cur_list.mode_field = 1;
  ctx->cur_list.head_field = mem_max - 1;
  ctx->cur_list.tail_field = mem_max - 1;
  ctx->cur_list.aux_field.int_ = -65536000;
  ctx->cur_list.ml_field = 0;
  ctx->cur_list.pg_field = 0;
  ctx->shown_mode = 0;
  ctx->page_contents = 0;
  ctx->page_tail = mem_max - 2;
  ctx->mem[mem_max - mem_min - 2].hh.rh = -1073741824;
  ctx->last_glue = 1073741824;
  ctx->last_penalty = 0;
  ctx->last_kern = 0;
  ctx->page_so_far[7] = 0;
  ctx->page_max_depth = 0;
  for (k = 12163; k <= 13006; ++k)
    ctx->xeq_level[k - 12163] = 1;
  ctx->no_new_control_sequence = true;
  ctx->hash[0].lh = 0;
  ctx->hash[0].rh = 0;
  for (k = 515; k <= 9780; ++k)
    ctx->hash[k - 514] = ctx->hash[0];
  ctx->save_ptr = 0;
  ctx->cur_level = 1;
  ctx->cur_group = 0;
  ctx->cur_boundary = 0;
  ctx->max_save_stack = 0;
  ctx->mag_set = 0;
  ctx->cur_mark[0] = -1073741824;
  ctx->cur_mark[1] = -1073741824;
  ctx->cur_mark[2] = -1073741824;
  ctx->cur_mark[3] = -1073741824;
  ctx->cur_mark[4] = -1073741824;
  ctx->cur_val = 0;
  ctx->cur_val_level = 0;
  ctx->radix = 0;
  ctx->cur_order = 0;
  for (k = 0; k <= 16; ++k)
    ctx->read_open[k] = 2;
  ctx->cond_ptr = -1073741824;
  ctx->if_limit = 0;
  ctx->cur_if = 0;
  ctx->if_line = 0;
  memcpy(ctx->TEX_format_default, "tex/plain.fmt", 14);
  ctx->null_character.b0 = 0;
  ctx->null_character.b1 = 0;
  ctx->null_character.b2 = 0;
  ctx->null_character.b3 = 0;
  ctx->max_v = 0;
  ctx->max_h = 0;
  ctx->max_push = 0;
  ctx->last_bop = -1;
  ctx->doing_leaders = false;
  ctx->dead_cycles = 0;
  ctx->cur_s = -1;
  ctx->down_ptr = -1073741824;
  ctx->right_ptr = -1073741824;
  ctx->adjust_tail = -1073741824;
  ctx->last_badness = 0;
  ctx->pack_begin_line = 0;
  ctx->empty_field.rh = 0;
  ctx->empty_field.lh = -1073741824;
  ctx->null_delimiter.b0 = 0;
  ctx->null_delimiter.b1 = 0;
  ctx->null_delimiter.b2 = 0;
  ctx->null_delimiter.b3 = 0;
  ctx->align_ptr = -1073741824;
  ctx->cur_align = -1073741824;
  ctx->cur_span = -1073741824;
  ctx->cur_loop = -1073741824;
  ctx->cur_head = -1073741824;
  ctx->cur_tail = -1073741824;
  for (z = 0; z <= 307; ++z) {
    ctx->hyph_word[z] = 0;
    ctx->hyph_list[z] = -1073741824;
  }
  ctx->hyph_count = 0;
  ctx->output_active = false;
  ctx->insert_penalties = 0;
  ctx->ligature_present = false;
  ctx->cancel_boundary = false;
  ctx->lft_hit = false;
  ctx->rt_hit = false;
  ctx->ins_disc = false;
  ctx->after_token = 0;
  ctx->long_help_seen = false;
  ctx->format_ident = 0;
  for (k = 0; k <= 17; ++k)
    ctx->write_open[k] = false;
  for (k = 1; k <= 19; ++k)
    ctx->mem[k - mem_min].int_ = 0;
  k = 0;
  while (k <= 19) {
    ctx->mem[k - mem_min].hh.rh = -1073741823;
    ctx->mem[k - mem_min].hh.U2.b0 = 0;
    ctx->mem[k - mem_min].hh.U2.b1 = 0;
    k += 4;
  }
  ctx->mem[6 - mem_min].int_ = 65536;
  ctx->mem[4 - mem_min].hh.U2.b0 = 1;
  ctx->mem[10 - mem_min].int_ = 65536;
  ctx->mem[8 - mem_min].hh.U2.b0 = 2;
  ctx->mem[14 - mem_min].int_ = 65536;
  ctx->mem[12 - mem_min].hh.U2.b0 = 1;
  ctx->mem[15 - mem_min].int_ = 65536;
  ctx->mem[12 - mem_min].hh.U2.b1 = 1;
  ctx->mem[18 - mem_min].int_ = -65536;
  ctx->mem[16 - mem_min].hh.U2.b0 = 1;
  ctx->rover = 20;
  ctx->mem[ctx->rover - mem_min].hh.rh = 1073741824;
  ctx->mem[ctx->rover - mem_min].hh.lh = 1000;
  ctx->mem[ctx->rover - mem_min + 1].hh.lh = ctx->rover;
  ctx->mem[ctx->rover - mem_min + 1].hh.rh = ctx->rover;
  ctx->lo_mem_max = ctx->rover + 1000;
  ctx->mem[ctx->lo_mem_max - mem_min].hh.rh = -1073741824;
  ctx->mem[ctx->lo_mem_max - mem_min].hh.lh = -1073741824;
  for (k = mem_max - 13; k <= mem_max; ++k)
    ctx->mem[k - mem_min] = ctx->mem[ctx->lo_mem_max - mem_min];
  ctx->mem[mem_max - mem_min - 10].hh.lh = 13614;
  ctx->mem[mem_max - mem_min - 9].hh.rh = 65536;
  ctx->mem[mem_max - mem_min - 9].hh.lh = -1073741824;
  ctx->mem[mem_max - mem_min - 7].hh.U2.b0 = 1;
  ctx->mem[mem_max - mem_min - 6].hh.lh = 1073741824;
  ctx->mem[mem_max - mem_min - 7].hh.U2.b1 = 0;
  ctx->mem[mem_max - mem_min].hh.U2.b1 = 255;
  ctx->mem[mem_max - mem_min].hh.U2.b0 = 1;
  ctx->mem[mem_max - mem_min].hh.rh = mem_max;
  ctx->mem[mem_max - mem_min - 2].hh.U2.b0 = 10;
  ctx->mem[mem_max - mem_min - 2].hh.U2.b1 = 0;
  ctx->avail = -1073741824;
  ctx->mem_end = mem_max;
  ctx->hi_mem_min = mem_max - 13;
  ctx->var_used = 20;
  ctx->dyn_used = 14;
  ctx->eqtb[9781].hh.U2.b0 = 101;
  ctx->eqtb[9781].hh.rh = -1073741824;
  ctx->eqtb[9781].hh.U2.b1 = 0;
  for (k = 1; k <= 9780; ++k)
    ctx->eqtb[k] = ctx->eqtb[9781];
  ctx->eqtb[9782].hh.rh = 0;
  ctx->eqtb[9782].hh.U2.b1 = 1;
  ctx->eqtb[9782].hh.U2.b0 = 117;
  for (k = 9783; k <= 10311; ++k)
    ctx->eqtb[k] = ctx->eqtb[9782];
  ctx->mem[-mem_min].hh.rh += 530;
  ctx->eqtb[10312].hh.rh = -1073741824;
  ctx->eqtb[10312].hh.U2.b0 = 118;
  ctx->eqtb[10312].hh.U2.b1 = 1;
  for (k = 10313; k <= 10577; ++k)
    ctx->eqtb[k] = ctx->eqtb[9781];
  ctx->eqtb[10578].hh.rh = -1073741824;
  ctx->eqtb[10578].hh.U2.b0 = 119;
  ctx->eqtb[10578].hh.U2.b1 = 1;
  for (k = 10579; k <= 10833; ++k)
    ctx->eqtb[k] = ctx->eqtb[10578];
  ctx->eqtb[10834].hh.rh = 0;
  ctx->eqtb[10834].hh.U2.b0 = 120;
  ctx->eqtb[10834].hh.U2.b1 = 1;
  for (k = 10835; k <= 10882; ++k)
    ctx->eqtb[k] = ctx->eqtb[10834];
  ctx->eqtb[10883].hh.rh = 0;
  ctx->eqtb[10883].hh.U2.b0 = 120;
  ctx->eqtb[10883].hh.U2.b1 = 1;
  for (k = 10884; k <= 12162; ++k)
    ctx->eqtb[k] = ctx->eqtb[10883];
  for (k = 0; k <= 255; ++k) {
    ctx->eqtb[k + 10883].hh.rh = 12;
    ctx->eqtb[k + 11907].hh.rh = k - 1073741824;
    ctx->eqtb[k + 11651].hh.rh = 1000;
  }
  ctx->eqtb[10896].hh.rh = 5;
  ctx->eqtb[10915].hh.rh = 10;
  ctx->eqtb[10975].hh.rh = 0;
  ctx->eqtb[10920].hh.rh = 14;
  ctx->eqtb[11010].hh.rh = 15;
  ctx->eqtb[10883].hh.rh = 9;
  for (k = 48; k <= 57; ++k)
    ctx->eqtb[k + 11907].hh.rh = k - 1073713152;
  for (k = 65; k <= 90; ++k) {
    ctx->eqtb[k + 10883].hh.rh = 11;
    ctx->eqtb[k + 10915].hh.rh = 11;
    ctx->eqtb[k + 11907].hh.rh = k - 1073712896;
    ctx->eqtb[k + 11939].hh.rh = k - 1073712864;
    ctx->eqtb[k + 11139].hh.rh = k + 32;
    ctx->eqtb[k + 11171].hh.rh = k + 32;
    ctx->eqtb[k + 11395].hh.rh = k;
    ctx->eqtb[k + 11427].hh.rh = k;
    ctx->eqtb[k + 11651].hh.rh = 999;
  }
  for (k = 12163; k <= 12473; ++k)
    ctx->eqtb[k].int_ = 0;
  ctx->eqtb[12180].int_ = 1000;
  ctx->eqtb[12164].int_ = 10000;
  ctx->eqtb[12204].int_ = 1;
  ctx->eqtb[12203].int_ = 25;
  ctx->eqtb[12208].int_ = 92;
  ctx->eqtb[12211].int_ = 13;
  for (k = 0; k <= 255; ++k)
    ctx->eqtb[k + 12474].int_ = -1;
  ctx->eqtb[12520].int_ = 0;
  for (k = 12730; k <= 13006; ++k)
    ctx->eqtb[k].int_ = 0;
  ctx->hash_used = 9514;
  ctx->cs_count = 0;
  ctx->eqtb[9523].hh.U2.b0 = 116;
  ctx->hash[9009].rh = 502;
  ctx->font_ptr = 0;
  ctx->fmem_ptr = 7;
  ctex_font_info_init(&ctx->fnt_infos);
  for (k = 0; k <= 6; ++k)
    ctx->font_info[k].int_ = 0;
  for (k = -trie_op_size; k <= trie_op_size; ++k)
    ctx->trie_op_hash[k + trie_op_size] = 0;
  for (k = 0; k <= 255; ++k)
    ctx->trie_used[k] = 0;
  ctx->trie_op_ptr = 0;
  ctx->trie_not_ready = true;
  ctx->trie_l[0] = 0;
  ctx->trie_c[0] = 0;
  ctx->trie_ptr = 0;
  ctx->hash[9000].rh = 1189;
  ctx->format_ident = 1256;
  ctx->hash[9008].rh = 1295;
  ctx->eqtb[9522].hh.U2.b1 = 1;
  ctx->eqtb[9522].hh.U2.b0 = 113;
  ctx->eqtb[9522].hh.rh = -1073741824;
}

void print_ln(ctex_t *ctx) {
  switch (ctx->selector) {
  case 19:
    fprintf(ctx->term_out, "\n");
    fprintf(ctx->log_file, "\n");
    ctx->term_offset = 0;
    ctx->file_offset = 0;
    break;
  case 18:
    fprintf(ctx->log_file, "\n");
    ctx->file_offset = 0;
    break;
  case 17:
    fprintf(ctx->term_out, "\n");
    ctx->term_offset = 0;
    break;
  case 16:
  case 20:
  case 21:
    // blank case
    break;
  default:
    fprintf(ctx->write_file[ctx->selector], "\n");
    break;
  }
}

void print_char(ctex_t *ctx, ASCII_code s) {
  if (s == ctx->eqtb[12212].int_) {
    if (ctx->selector < 20) {
      print_ln(ctx);
      goto _L10;
    }
  }
  switch (ctx->selector) {
  case 19:
    fprintf(ctx->term_out, "%c", ctx->xchr[s]);
    fprintf(ctx->log_file, "%c", ctx->xchr[s]);
    ++ctx->term_offset;
    ++ctx->file_offset;
    if (ctx->term_offset == max_print_line) {
      fprintf(ctx->term_out, "\n");
      ctx->term_offset = 0;
    }
    if (ctx->file_offset == max_print_line) {
      fprintf(ctx->log_file, "\n");
      ctx->file_offset = 0;
    }
    break;
  case 18:
    fprintf(ctx->log_file, "%c", ctx->xchr[s]);
    ++ctx->file_offset;
    if (ctx->file_offset == max_print_line)
      print_ln(ctx);
    break;
  case 17:
    fprintf(ctx->term_out, "%c", ctx->xchr[s]);
    ++ctx->term_offset;
    if (ctx->term_offset == max_print_line)
      print_ln(ctx);
    break;
  case 16:
    // blank case
    break;
  case 20:
    if (ctx->tally < ctx->trick_count)
      ctx->trick_buf[ctx->tally % error_line] = s;
    break;
  case 21:
    if (ctx->pool_ptr < pool_size) {
      ctx->str_pool[ctx->pool_ptr] = s;
      ++ctx->pool_ptr;
    }
    break;
  default:
    fprintf(ctx->write_file[ctx->selector], "%c", ctx->xchr[s]);
    break;
  }
  ++ctx->tally;
_L10:;
}

void print(ctex_t *ctx, integer s) {
  pool_pointer j;
  integer nl;
  if (s >= ctx->str_ptr) {
    s = 259;
  } else if (s < 256) {
    if (s >= 0) {
      if (ctx->selector > 20) {
        print_char(ctx, s);
        goto _L10;
      }
      if (s == ctx->eqtb[12212].int_) {
        if (ctx->selector < 20) {
          print_ln(ctx);
          goto _L10;
        }
      }
      nl = ctx->eqtb[12212].int_;
      ctx->eqtb[12212].int_ = -1;
      j = ctx->str_start[s];
      while (j < ctx->str_start[s + 1]) {
        print_char(ctx, ctx->str_pool[j]);
        ++j;
      }
      ctx->eqtb[12212].int_ = nl;
      goto _L10;
    }
    s = 259;
  }
  j = ctx->str_start[s];
  while (j < ctx->str_start[s + 1]) {
    print_char(ctx, ctx->str_pool[j]);
    ++j;
  }
_L10:;
}

void slow_print(ctex_t *ctx, integer s) {
  pool_pointer j;
  if ((s >= ctx->str_ptr) || (s < 256)) {
    print(ctx, s);
    return;
  }
  j = ctx->str_start[s];
  while (j < ctx->str_start[s + 1]) {
    print(ctx, ctx->str_pool[j]);
    ++j;
  }
}

void print_nl(ctex_t *ctx, str_number s) {
  if (((ctx->term_offset > 0) && (ctx->selector & 1)) ||
      ((ctx->file_offset > 0) && (ctx->selector >= 18)))
    print_ln(ctx);
  print(ctx, s);
}

void print_esc(ctex_t *ctx, str_number s) {
  integer c = ctx->eqtb[12208].int_;
  if (c >= 0) {
    if (c < 256)
      print(ctx, c);
  }
  slow_print(ctx, s);
}

void print_the_digs(ctex_t *ctx, uint8_t k) {
  while (k > 0) {
    --k;
    if (ctx->dig[k] < 10)
      print_char(ctx, ctx->dig[k] + 48);
    else
      print_char(ctx, ctx->dig[k] + 55);
  }
}

void print_int(ctex_t *ctx, integer n) {
  char k = 0;
  integer m;
  if (n < 0) {
    print_char(ctx, 45);
    if (n > (-100000000)) {
      n = -n;
    } else {
      m = (-n) - 1;
      n = m / 10;
      m = (m % 10) + 1;
      k = 1;
      if (m < 10) {
        ctx->dig[0] = m;
      } else {
        ctx->dig[0] = 0;
        ++n;
      }
    }
  }
  do {
    ctx->dig[k] = n % 10;
    n /= 10;
    ++k;
  } while (n);
  print_the_digs(ctx, k);
}

void print_cs(ctex_t *ctx, integer p) {
  if (p < 514) {
    if (p >= 257) {
      if (p == 513) {
        print_esc(ctx, 504);
        print_esc(ctx, 505);
        print_char(ctx, 32);
        return;
      }
      print_esc(ctx, p - 257);
      if (ctx->eqtb[p + 10626].hh.rh == 11)
        print_char(ctx, 32);
      return;
    }
    if (p < 1)
      print_esc(ctx, 506);
    else
      print(ctx, p - 1);
    return;
  }
  if (p >= 9781) {
    print_esc(ctx, 506);
    return;
  }
  if (((unsigned)ctx->hash[p - 514].rh) >= ctx->str_ptr) {
    print_esc(ctx, 507);
  } else {
    print_esc(ctx, ctx->hash[p - 514].rh);
    print_char(ctx, 32);
  }
}

void sprint_cs(ctex_t *ctx, halfword p) {
  if (p >= 514) {
    print_esc(ctx, ctx->hash[p - 514].rh);
    return;
  }
  if (p < 257) {
    print(ctx, p - 1);
    return;
  }
  if (p < 513) {
    print_esc(ctx, p - 257);
  } else {
    print_esc(ctx, 504);
    print_esc(ctx, 505);
  }
}

void print_file_name(ctex_t *ctx, integer n, integer a, integer e) {
  slow_print(ctx, a);
  slow_print(ctx, n);
  slow_print(ctx, e);
}

void print_size(ctex_t *ctx, integer s) {
  if (!s) {
    print_esc(ctx, 412);
    return;
  }
  if (s == 16)
    print_esc(ctx, 413);
  else
    print_esc(ctx, 414);
}

void print_write_whatsit(ctex_t *ctx, str_number s, halfword p) {
  print_esc(ctx, s);
  if (ctx->mem[p - mem_min + 1].hh.lh < 16) {
    print_int(ctx, ctx->mem[p - mem_min + 1].hh.lh);
    return;
  }
  if (ctx->mem[p - mem_min + 1].hh.lh == 16)
    print_char(ctx, 42);
  else
    print_char(ctx, 45);
}

void jump_out(ctex_t *ctx) { longjmp(ctx->_JL9998, 1); }

void error(ctex_t *ctx) {
  ASCII_code c;
  integer s1, s2, s3, s4;
  if (ctx->history < 2)
    ctx->history = 2;
  print_char(ctx, 46);
  show_context(ctx);
  if (ctx->interaction == 3) {
    while (true) {
    _L22:
      clear_for_error_prompt(ctx);
      print(ctx, 264);
      term_input(ctx);
      if (ctx->last == ctx->first)
        goto _L10;
      c = ctx->buffer[ctx->first];
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
        if (ctx->deletions_allowed) {
          s1 = ctx->cur_tok;
          s2 = ctx->cur_cmd;
          s3 = ctx->cur_chr;
          s4 = ctx->align_state;
          ctx->align_state = 1000000;
          ctx->OK_to_interrupt = false;
          if ((ctx->last > (ctx->first + 1)) &&
              (ctx->buffer[ctx->first + 1] >= 48) &&
              (ctx->buffer[ctx->first + 1] <= 57))
            c = (c * 10) + ctx->buffer[ctx->first + 1] - 528;
          else
            c -= 48;
          while (c > 0) {
            get_token(ctx);
            --c;
          }
          ctx->cur_tok = s1;
          ctx->cur_cmd = s2;
          ctx->cur_chr = s3;
          ctx->align_state = s4;
          ctx->OK_to_interrupt = true;
          ctx->help_ptr = 2;
          ctx->help_line[1] = 279;
          ctx->help_line[0] = 280;
          show_context(ctx);
          goto _L22;
        }
        break;
      case 69:
        if (ctx->base_ptr > 0) {
          print_nl(ctx, 265);
          slow_print(ctx, ctx->input_stack[ctx->base_ptr].name_field);
          print(ctx, 266);
          print_int(ctx, ctx->line);
          ctx->interaction = 2;
          jump_out(ctx);
        }
        break;
      case 72:
        if (ctx->use_err_help) {
          give_err_help(ctx);
          ctx->use_err_help = false;
        } else {
          if (!ctx->help_ptr) {
            ctx->help_ptr = 2;
            ctx->help_line[1] = 281;
            ctx->help_line[0] = 282;
          }
          do {
            --ctx->help_ptr;
            print(ctx, ctx->help_line[ctx->help_ptr]);
            print_ln(ctx);
          } while (ctx->help_ptr);
        }
        ctx->help_ptr = 4;
        ctx->help_line[3] = 283;
        ctx->help_line[2] = 282;
        ctx->help_line[1] = 284;
        ctx->help_line[0] = 285;
        goto _L22;
        break;
      case 73:
        begin_file_reading(ctx);
        if (ctx->last > (ctx->first + 1)) {
          ctx->cur_input.loc_field = ctx->first + 1;
          ctx->buffer[ctx->first] = 32;
        } else {
          print(ctx, 278);
          term_input(ctx);
          ctx->cur_input.loc_field = ctx->first;
        }
        ctx->first = ctx->last;
        ctx->cur_input.limit_field = ctx->last - 1;
        goto _L10;
        break;
      case 81:
      case 82:
      case 83:
        ctx->error_count = 0;
        ctx->interaction = c - 81;
        print(ctx, 273);
        switch (c) {
        case 81:
          print_esc(ctx, 274);
          --ctx->selector;
          break;
        case 82:
          print_esc(ctx, 275);
          break;
        case 83:
          print_esc(ctx, 276);
          break;
        }
        print(ctx, 277);
        print_ln(ctx);
        fflush(ctx->term_out);
        errno = 0;
        goto _L10;
        break;
      case 88:
        ctx->interaction = 2;
        jump_out(ctx);
        break;
      default:
        break;
      }
      print(ctx, 267);
      print_nl(ctx, 268);
      print_nl(ctx, 269);
      if (ctx->base_ptr > 0)
        print(ctx, 270);
      if (ctx->deletions_allowed)
        print_nl(ctx, 271);
      print_nl(ctx, 272);
    }
  }
  ++ctx->error_count;
  if (ctx->error_count == 100) {
    print_nl(ctx, 263);
    ctx->history = 3;
    jump_out(ctx);
  }
  if (ctx->interaction > 0)
    --ctx->selector;
  if (ctx->use_err_help) {
    print_ln(ctx);
    give_err_help(ctx);
  } else {
    while (ctx->help_ptr > 0) {
      --ctx->help_ptr;
      print_nl(ctx, ctx->help_line[ctx->help_ptr]);
    }
  }
  print_ln(ctx);
  if (ctx->interaction > 0)
    ++ctx->selector;
  print_ln(ctx);
_L10:;
}

void fatal_error(ctex_t *ctx, str_number s) {
  normalize_selector(ctx);
  print_nl(ctx, 262);
  print(ctx, 287);
  ctx->help_ptr = 1;
  ctx->help_line[0] = s;
  if (ctx->interaction == 3)
    ctx->interaction = 2;
  if (ctx->log_opened)
    error(ctx);
  ctx->history = 3;
  jump_out(ctx);
}

void overflow(ctex_t *ctx, str_number s, integer n) {
  normalize_selector(ctx);
  print_nl(ctx, 262);
  print(ctx, 288);
  print(ctx, s);
  print_char(ctx, 61);
  print_int(ctx, n);
  print_char(ctx, 93);
  ctx->help_ptr = 2;
  ctx->help_line[1] = 289;
  ctx->help_line[0] = 290;
  if (ctx->interaction == 3)
    ctx->interaction = 2;
  if (ctx->log_opened)
    error(ctx);
  ctx->history = 3;
  jump_out(ctx);
}

void confusion(ctex_t *ctx, str_number s) {
  normalize_selector(ctx);
  if (ctx->history < 2) {
    print_nl(ctx, 262);
    print(ctx, 291);
    print(ctx, s);
    print_char(ctx, 41);
    ctx->help_ptr = 1;
    ctx->help_line[0] = 292;
  } else {
    print_nl(ctx, 262);
    print(ctx, 293);
    ctx->help_ptr = 2;
    ctx->help_line[1] = 294;
    ctx->help_line[0] = 295;
  }
  if (ctx->interaction == 3)
    ctx->interaction = 2;
  if (ctx->log_opened)
    error(ctx);
  ctx->history = 3;
  jump_out(ctx);
}

bool_t a_open_in(ctex_t *ctx, FILE **f) {
  ctex_kpath_ifind(ctx->name_of_file);
  *f = fopen(trim_name(ctx->name_of_file, file_name_size), "rb");
  if (!*f) {
    io_error(errno, trim_name(ctx->name_of_file, file_name_size));
  }
  return erstat(*f) == 0;
}

bool_t a_open_out(ctex_t *ctx, FILE **f) {
  ctex_kpath_ofind(ctx->name_of_file);
  *f = fopen(trim_name(ctx->name_of_file, file_name_size), "wb");
  if (!*f) {
    io_error(errno, trim_name(ctx->name_of_file, file_name_size));
  }
  return erstat(*f) == 0;
}

bool_t b_open_in(ctex_t *ctx, FILE **f) {
  ctex_kpath_ifind(ctx->name_of_file);
  *f = fopen(trim_name(ctx->name_of_file, file_name_size), "rb");
  if (!*f) {
    io_error(errno, trim_name(ctx->name_of_file, file_name_size));
  }
  return erstat(*f) == 0;
}

bool_t b_open_out(ctex_t *ctx, FILE **f) {
  ctex_kpath_ofind(ctx->name_of_file);
  *f = fopen(trim_name(ctx->name_of_file, file_name_size), "wb");
  if (!*f) {
    io_error(errno, trim_name(ctx->name_of_file, file_name_size));
  }
  return erstat(*f) == 0;
}

bool_t w_open_in(ctex_t *ctx, FILE **f) {
  ctex_kpath_ifind(ctx->name_of_file);
  *f = fopen(trim_name(ctx->name_of_file, file_name_size), "rb");
  if (!*f) {
    io_error(errno, trim_name(ctx->name_of_file, file_name_size));
  }
  return erstat(*f) == 0;
}

bool_t w_open_out(ctex_t *ctx, FILE **f) {
  ctex_kpath_ofind(ctx->name_of_file);
  *f = fopen(trim_name(ctx->name_of_file, file_name_size), "wb");
  if (!*f) {
    io_error(errno, trim_name(ctx->name_of_file, file_name_size));
  }
  return erstat(*f) == 0;
}

void a_close(ctex_t *ctx, FILE **f) {
  if (*f) {
    fclose(*f);
  }
  *f = NULL;
}

void b_close(ctex_t *ctx, FILE **f) {
  if (*f) {
    fclose(*f);
  }
  *f = NULL;
}

void w_close(ctex_t *ctx, FILE **f) {
  if (*f) {
    fclose(*f);
  }
  *f = NULL;
}

bool_t input_ln(ctex_t *ctx, FILE *f, bool_t bypass_eoln) {
  int last_nonblank;
  if (bypass_eoln) {
    if (!feof(f))
      fgetc(f);
  }
  ctx->last = ctx->first;
  if (feof(f)) {
    return false;
  } else {
    last_nonblank = ctx->first;
    while (!eoln(f)) {
      if (ctx->last >= ctx->max_buf_stack) {
        ctx->max_buf_stack = ctx->last + 1;
        if (ctx->max_buf_stack == buf_size) {
          if (!ctx->format_ident) {
            fprintf(ctx->term_out, "Buffer size exceeded!\n");
            longjmp(ctx->_JL9999, 1);
          } else {
            ctx->cur_input.loc_field = ctx->first;
            ctx->cur_input.limit_field = ctx->last - 1;
            overflow(ctx, 256, buf_size);
          }
        }
      }
      ctx->buffer[ctx->last] = ctx->xord[fpeek(f)];
      fgetc(f);
      ++ctx->last;
      if (ctx->buffer[ctx->last - 1] != 32)
        last_nonblank = ctx->last;
    }
    ctx->last = last_nonblank;
    return true;
  }
}

bool_t init_terminal(ctex_t *ctx) {
  bool_t result;
  ctx->term_in = ctx->input_stream;
  if (!ctx->term_in)
    io_error(errno, "TTY:");
  while (true) {
    fprintf(ctx->term_out, "**");
    fflush(ctx->term_out);
    errno = 0;
    if (!input_ln(ctx, ctx->term_in, true)) {
      fprintf(ctx->term_out, "\n! End of file on the terminal... why?");
      result = false;
      goto _L10;
    }
    ctx->cur_input.loc_field = ctx->first;
    while ((ctx->cur_input.loc_field < ctx->last) &&
           (ctx->buffer[ctx->cur_input.loc_field] == 32))
      ++ctx->cur_input.loc_field;
    if (ctx->cur_input.loc_field < ctx->last) {
      result = true;
      goto _L10;
    }
    fprintf(ctx->term_out, "Please type the name of your input file.\n");
  }
_L10:
  return result;
}

str_number make_string(ctex_t *ctx) {
  if (ctx->str_ptr == max_strings)
    overflow(ctx, 258, max_strings - ctx->init_str_ptr);
  ++ctx->str_ptr;
  ctx->str_start[ctx->str_ptr] = ctx->pool_ptr;
  return ctx->str_ptr - 1;
}

bool_t str_eq_buf(ctex_t *ctx, str_number s, integer k) {
  bool_t result;
  pool_pointer j = ctx->str_start[s];
  while (j < ctx->str_start[s + 1]) {
    if (ctx->str_pool[j] != ctx->buffer[k]) {
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

bool_t str_eq_str(ctex_t *ctx, str_number s, str_number t) {
  pool_pointer j, k;
  bool_t result = false;
  if (ctx->str_start[s + 1] - ctx->str_start[s] !=
      ctx->str_start[t + 1] - ctx->str_start[t])
    goto _L45;
  j = ctx->str_start[s];
  k = ctx->str_start[t];
  while (j < ctx->str_start[s + 1]) {
    if (ctx->str_pool[j] != ctx->str_pool[k])
      goto _L45;
    ++j;
    ++k;
  }
  result = true;
_L45:
  return result;
}

bool_t get_strings_started(ctex_t *ctx) {
  bool_t result;
  uint8_t k, l;
  char m, n;
  str_number g;
  integer a;
  bool_t c = false;
  short character;
  ctx->pool_ptr = 0;
  ctx->str_ptr = 0;
  ctx->str_start[0] = 0;
  for (character = 0; character <= 255; ++character) {
    k = character;
    if ((k < 32) || (k > 126)) {
      ctx->str_pool[ctx->pool_ptr] = 94;
      ++ctx->pool_ptr;
      ctx->str_pool[ctx->pool_ptr] = 94;
      ++ctx->pool_ptr;
      if (k < 64) {
        ctx->str_pool[ctx->pool_ptr] = k + 64;
        ++ctx->pool_ptr;
      } else if (k < 128) {
        ctx->str_pool[ctx->pool_ptr] = k - 64;
        ++ctx->pool_ptr;
      } else {
        l = k / 16;
        if (l < 10) {
          ctx->str_pool[ctx->pool_ptr] = l + 48;
          ++ctx->pool_ptr;
        } else {
          ctx->str_pool[ctx->pool_ptr] = l + 87;
          ++ctx->pool_ptr;
        }
        l = k & 15;
        if (l < 10) {
          ctx->str_pool[ctx->pool_ptr] = l + 48;
          ++ctx->pool_ptr;
        } else {
          ctx->str_pool[ctx->pool_ptr] = l + 87;
          ++ctx->pool_ptr;
        }
      }
    } else {
      ctx->str_pool[ctx->pool_ptr] = k;
      ++ctx->pool_ptr;
    }
    g = make_string(ctx);
  }
  // memcpy(name_of_file, pool_name, file_name_size); // FIXME(sbinet)
  memcpy(ctx->name_of_file, pool_name, 13);
  if (!a_open_in(ctx, &ctx->pool_file)) {
    fprintf(ctx->term_out, "! I can't read tex.pool.\n");
    a_close(ctx, &ctx->pool_file);
    result = false;
    goto _L10;
  }
  do {
    if (feof(ctx->pool_file)) {
      fprintf(ctx->term_out, "! tex.pool has no check sum.\n");
      a_close(ctx, &ctx->pool_file);
      result = false;
      goto _L10;
    }
    fread(&m, sizeof(char), 1, ctx->pool_file);
    fread(&n, sizeof(char), 1, ctx->pool_file);
    if (m == '*') {
      a = 0;
      k = 1;
      while (true) {
        if ((ctx->xord[n] < 48) || (ctx->xord[n] > 57)) {
          fprintf(ctx->term_out,
                  "! tex.pool check sum doesn't have nine digits.\n");
          a_close(ctx, &ctx->pool_file);
          result = false;
          goto _L10;
        }
        a = (a * 10) + ctx->xord[n] - 48;
        if (k == 9)
          goto _L30;
        ++k;
        fread(&n, sizeof(char), 1, ctx->pool_file);
      }
    _L30:
      if (a != 117275187) {
        fprintf(ctx->term_out, "! tex.pool doesn't match; TANGLE me again.\n");
        a_close(ctx, &ctx->pool_file);
        result = false;
        goto _L10;
      }
      c = true;
    } else {
      if ((ctx->xord[m] < 48) || (ctx->xord[m] > 57) || (ctx->xord[n] < 48) ||
          (ctx->xord[n] > 57)) {
        fprintf(ctx->term_out,
                "! tex.pool line doesn't begin with two digits.\n");
        a_close(ctx, &ctx->pool_file);
        result = false;
        goto _L10;
      }
      l = (ctx->xord[m] * 10) + ctx->xord[n] - 528;
      if (ctx->pool_ptr + l + string_vacancies > pool_size) {
        fprintf(ctx->term_out, "! You have to increase POOLSIZE.\n");
        a_close(ctx, &ctx->pool_file);
        result = false;
        goto _L10;
      }
      for (k = 1; k <= l; ++k) {
        if (eoln(ctx->pool_file))
          m = ' ';
        else
          fread(&m, sizeof(char), 1, ctx->pool_file);
        ctx->str_pool[ctx->pool_ptr] = ctx->xord[m];
        ++ctx->pool_ptr;
      }
      fgetc(ctx->pool_file); // skip the newline
      g = make_string(ctx);
    }
  } while (!c);
  a_close(ctx, &ctx->pool_file);
  result = true;
_L10:
  return result;
}

void print_two(ctex_t *ctx, integer n) {
  n = abs(n) % 100;
  print_char(ctx, (n / 10) + 48);
  print_char(ctx, (n % 10) + 48);
}

void print_hex(ctex_t *ctx, integer n) {
  char k = 0;
  print_char(ctx, 34);
  do {
    ctx->dig[k] = n & 15;
    n /= 16;
    ++k;
  } while (n);
  print_the_digs(ctx, k);
}

void print_roman_int(ctex_t *ctx, integer n) {
  pool_pointer k;
  nonnegative_integer u, v = 1000;
  pool_pointer j = ctx->str_start[260];
  while (true) {
    while (n >= v) {
      print_char(ctx, ctx->str_pool[j]);
      n -= v;
    }
    if (n <= 0)
      goto _L10;
    k = j + 2;
    u = v / (ctx->str_pool[k - 1] - 48);
    if (ctx->str_pool[k - 1] == 50) {
      k += 2;
      u /= ctx->str_pool[k - 1] - 48;
    }
    if (n + u >= v) {
      print_char(ctx, ctx->str_pool[k]);
      n += u;
    } else {
      j += 2;
      v /= ctx->str_pool[j - 1] - 48;
    }
  }
_L10:;
}

void print_current_string(ctex_t *ctx) {
  pool_pointer j = ctx->str_start[ctx->str_ptr];
  while (j < ctx->pool_ptr) {
    print_char(ctx, ctx->str_pool[j]);
    ++j;
  }
}

void term_input(ctex_t *ctx) {
  int k, N;
  fflush(ctx->term_out);
  errno = 0;
  if (!input_ln(ctx, ctx->term_in, true))
    fatal_error(ctx, 261);
  ctx->term_offset = 0;
  --ctx->selector;
  if (ctx->last != ctx->first) {
    for (N = ctx->last, k = ctx->first; k <= (N - 1); ++k)
      print(ctx, ctx->buffer[k]);
  }
  print_ln(ctx);
  ++ctx->selector;
}

void int_error(ctex_t *ctx, integer n) {
  print(ctx, 286);
  print_int(ctx, n);
  print_char(ctx, 41);
  error(ctx);
}

void normalize_selector(ctex_t *ctx) {
  if (ctx->log_opened)
    ctx->selector = 19;
  else
    ctx->selector = 17;
  if (!ctx->job_name)
    open_log_file(ctx);
  if (!ctx->interaction)
    --ctx->selector;
}

void pause_for_instructions(ctex_t *ctx) {
  if (!ctx->OK_to_interrupt)
    return;
  ctx->interaction = 3;
  if ((ctx->selector == 18) || (ctx->selector == 16))
    ++ctx->selector;
  print_nl(ctx, 262);
  print(ctx, 296);
  ctx->help_ptr = 3;
  ctx->help_line[2] = 297;
  ctx->help_line[1] = 298;
  ctx->help_line[0] = 299;
  ctx->deletions_allowed = false;
  error(ctx);
  ctx->deletions_allowed = true;
  ctx->interrupt = 0;
}

integer half(ctex_t *ctx, integer x) {
  if (x & 1)
    return (x + 1) / 2;
  else
    return x / 2;
}

scaled round_decimals(ctex_t *ctx, small_number k) {
  integer a = 0;
  while (k > 0) {
    --k;
    a = (a + (ctx->dig[k] * 131072)) / 10;
  }
  return (a + 1) / 2;
}

void print_scaled(ctex_t *ctx, scaled s) {
  scaled delta = 10;
  if (s < 0) {
    print_char(ctx, 45);
    s = -s;
  }
  print_int(ctx, s / 65536);
  print_char(ctx, 46);
  s = ((s & 65535) * 10) + 5;
  do {
    if (delta > 65536)
      s -= 17232;
    print_char(ctx, (s / 65536) + 48);
    s = (s & 65535) * 10;
    delta *= 10;
  } while (s > delta);
}

scaled mult_and_add(ctex_t *ctx, integer n, scaled x, scaled y,
                    scaled max_answer) {
  if (n < 0) {
    x = -x;
    n = -n;
  }
  if (!n) {
    return y;
  } else if ((x <= ((max_answer - y) / n)) && (-x <= (max_answer + y) / n)) {
    return (n * x) + y;
  } else {
    ctx->arith_error = true;
    return 0;
  }
}

scaled x_over_n(ctex_t *ctx, scaled x, integer n) {
  int result;
  bool_t negative = false;
  if (!n) {
    ctx->arith_error = true;
    result = 0;
    ctx->remainder_ = x;
  } else {
    if (n < 0) {
      x = -x;
      n = -n;
      negative = true;
    }
    if (x >= 0) {
      result = x / n;
      ctx->remainder_ = x % n;
    } else {
      result = -((-x) / n);
      ctx->remainder_ = -((-x) % n);
    }
  }
  if (negative)
    ctx->remainder_ = -ctx->remainder_;
  return result;
}

scaled xn_over_d(ctex_t *ctx, scaled x, integer n, integer d) {
  int result;
  bool_t positive;
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
    ctx->arith_error = true;
  else
    u = ((u / d) * 32768) + (v / d);
  if (positive) {
    result = u;
    ctx->remainder_ = v % d;
  } else {
    result = -u;
    ctx->remainder_ = -(v % d);
  }
  return result;
}

halfword badness(ctex_t *ctx, scaled t, scaled s) {
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

void show_token_list(ctex_t *ctx, integer p, integer q, integer l) {
  integer m, c;
  ASCII_code match_chr = 35, n = 48;
  ctx->tally = 0;
  while ((p != (-1073741824)) && (ctx->tally < l)) {
    if (p == q) {
      ctx->first_count = ctx->tally;
      ctx->trick_count = ctx->tally + error_line - half_error_line + 1;
      if (ctx->trick_count < error_line)
        ctx->trick_count = error_line;
    }
    if ((p < ctx->hi_mem_min) || (p > ctx->mem_end)) {
      print_esc(ctx, 309);
      goto _L10;
    }
    if (ctx->mem[p - mem_min].hh.lh >= 4095) {
      print_cs(ctx, ctx->mem[p - mem_min].hh.lh - 4095);
    } else {
      m = ctx->mem[p - mem_min].hh.lh / 256;
      c = ctx->mem[p - mem_min].hh.lh & 255;
      if (ctx->mem[p - mem_min].hh.lh < 0) {
        print_esc(ctx, 555);
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
          print(ctx, c);
          break;
        case 6:
          print(ctx, c);
          print(ctx, c);
          break;
        case 5:
          print(ctx, match_chr);
          if (c > 9) {
            print_char(ctx, 33);
            goto _L10;
          }
          print_char(ctx, c + 48);
          break;
        case 13:
          match_chr = c;
          print(ctx, c);
          ++n;
          print_char(ctx, n);
          if (n > 57)
            goto _L10;
          break;
        case 14:
          print(ctx, 556);
          break;
        default:
          print_esc(ctx, 555);
          break;
        }
      }
    }
    p = ctx->mem[p - mem_min].hh.rh;
  }
  if (p != (-1073741824))
    print_esc(ctx, 554);
_L10:;
}

void runaway(ctex_t *ctx) {
  halfword p;
  if (ctx->scanner_status <= 1)
    return;
  print_nl(ctx, 569);
  switch (ctx->scanner_status) {
  case 2:
    print(ctx, 570);
    p = ctx->def_ref;
    break;
  case 3:
    print(ctx, 571);
    p = mem_max - 3;
    break;
  case 4:
    print(ctx, 572);
    p = mem_max - 4;
    break;
  case 5:
    print(ctx, 573);
    p = ctx->def_ref;
    break;
  }
  print_char(ctx, 63);
  print_ln(ctx);
  show_token_list(ctx, ctx->mem[p - mem_min].hh.rh, -1073741824,
                  error_line - 10);
}

halfword get_avail(ctex_t *ctx) {
  halfword p = ctx->avail;
  if (p != (-1073741824)) {
    ctx->avail = ctx->mem[ctx->avail - mem_min].hh.rh;
  } else if (ctx->mem_end < mem_max) {
    ++ctx->mem_end;
    p = ctx->mem_end;
  } else {
    --ctx->hi_mem_min;
    p = ctx->hi_mem_min;
    if (ctx->hi_mem_min <= ctx->lo_mem_max) {
      runaway(ctx);
      overflow(ctx, 300, mem_max - mem_min + 1);
    }
  }
  ctx->mem[p - mem_min].hh.rh = -1073741824;
  return p;
}

void flush_list(ctex_t *ctx, halfword p) {
  halfword q, r;
  if (p == (-1073741824))
    return;
  r = p;
  do {
    q = r;
    r = ctx->mem[r - mem_min].hh.rh;
  } while (r != (-1073741824));
  ctx->mem[q - mem_min].hh.rh = ctx->avail;
  ctx->avail = p;
}

halfword get_node(ctex_t *ctx, integer s) {
  halfword result, p, q;
  integer r, t;
_L20:
  p = ctx->rover;
  do {
    q = p + ctx->mem[p - mem_min].hh.lh;
    while (ctx->mem[q - mem_min].hh.rh == 1073741824) {
      t = ctx->mem[q - mem_min + 1].hh.rh;
      if (q == ctx->rover)
        ctx->rover = t;
      ctx->mem[t - mem_min + 1].hh.lh = ctx->mem[q - mem_min + 1].hh.lh;
      ctx->mem[ctx->mem[q - mem_min + 1].hh.lh - mem_min + 1].hh.rh = t;
      q += ctx->mem[q - mem_min].hh.lh;
    }
    r = q - s;
    if (r > (p + 1)) {
      ctx->mem[p - mem_min].hh.lh = r - p;
      ctx->rover = p;
      goto _L40;
    }
    if (r == p) {
      if (ctx->mem[p - mem_min + 1].hh.rh != p) {
        ctx->rover = ctx->mem[p - mem_min + 1].hh.rh;
        t = ctx->mem[p - mem_min + 1].hh.lh;
        ctx->mem[ctx->rover - mem_min + 1].hh.lh = t;
        ctx->mem[t - mem_min + 1].hh.rh = ctx->rover;
        goto _L40;
      }
    }
    ctx->mem[p - mem_min].hh.lh = q - p;
    p = ctx->mem[p - mem_min + 1].hh.rh;
  } while (p != ctx->rover);
  if (s == 1073741824) {
    result = 1073741824;
    goto _L10;
  }
  if (ctx->lo_mem_max + 2 < ctx->hi_mem_min) {
    if (ctx->lo_mem_max <= 1073741822) {
      if (ctx->hi_mem_min - ctx->lo_mem_max >= 1998)
        t = ctx->lo_mem_max + 1000;
      else
        t = ctx->lo_mem_max + ((ctx->hi_mem_min - ctx->lo_mem_max) / 2) + 1;
      p = ctx->mem[ctx->rover - mem_min + 1].hh.lh;
      q = ctx->lo_mem_max;
      ctx->mem[p - mem_min + 1].hh.rh = q;
      ctx->mem[ctx->rover - mem_min + 1].hh.lh = q;
      if (t > 1073741824)
        t = 1073741824;
      ctx->mem[q - mem_min + 1].hh.rh = ctx->rover;
      ctx->mem[q - mem_min + 1].hh.lh = p;
      ctx->mem[q - mem_min].hh.rh = 1073741824;
      ctx->mem[q - mem_min].hh.lh = t - ctx->lo_mem_max;
      ctx->lo_mem_max = t;
      ctx->mem[ctx->lo_mem_max - mem_min].hh.rh = -1073741824;
      ctx->mem[ctx->lo_mem_max - mem_min].hh.lh = -1073741824;
      ctx->rover = q;
      goto _L20;
    }
  }
  overflow(ctx, 300, mem_max - mem_min + 1);
_L40:
  ctx->mem[r - mem_min].hh.rh = -1073741824;
  result = r;
_L10:
  return result;
}

void free_node(ctex_t *ctx, halfword p, halfword s) {
  halfword q;
  ctx->mem[p - mem_min].hh.lh = s;
  ctx->mem[p - mem_min].hh.rh = 1073741824;
  q = ctx->mem[ctx->rover - mem_min + 1].hh.lh;
  ctx->mem[p - mem_min + 1].hh.lh = q;
  ctx->mem[p - mem_min + 1].hh.rh = ctx->rover;
  ctx->mem[ctx->rover - mem_min + 1].hh.lh = p;
  ctx->mem[q - mem_min + 1].hh.rh = p;
}

void sort_avail(ctex_t *ctx) {
  halfword q, r, old_rover;
  halfword p = get_node(ctx, 1073741824);
  p = ctx->mem[ctx->rover - mem_min + 1].hh.rh;
  ctx->mem[ctx->rover - mem_min + 1].hh.rh = 1073741824;
  old_rover = ctx->rover;
  while (p != old_rover) {
    if (p < ctx->rover) {
      q = p;
      p = ctx->mem[q - mem_min + 1].hh.rh;
      ctx->mem[q - mem_min + 1].hh.rh = ctx->rover;
      ctx->rover = q;
      continue;
    }
    q = ctx->rover;
    while (ctx->mem[q - mem_min + 1].hh.rh < p)
      q = ctx->mem[q - mem_min + 1].hh.rh;
    r = ctx->mem[p - mem_min + 1].hh.rh;
    ctx->mem[p - mem_min + 1].hh.rh = ctx->mem[q - mem_min + 1].hh.rh;
    ctx->mem[q - mem_min + 1].hh.rh = p;
    p = r;
  }
  p = ctx->rover;
  while (ctx->mem[p - mem_min + 1].hh.rh != 1073741824) {
    ctx->mem[ctx->mem[p - mem_min + 1].hh.rh - mem_min + 1].hh.lh = p;
    p = ctx->mem[p - mem_min + 1].hh.rh;
  }
  ctx->mem[p - mem_min + 1].hh.rh = ctx->rover;
  ctx->mem[ctx->rover - mem_min + 1].hh.lh = p;
}

halfword new_null_box(ctex_t *ctx) {
  halfword p = get_node(ctx, 7);
  ctx->mem[p - mem_min].hh.U2.b0 = 0;
  ctx->mem[p - mem_min].hh.U2.b1 = 0;
  ctx->mem[p - mem_min + 1].int_ = 0;
  ctx->mem[p - mem_min + 2].int_ = 0;
  ctx->mem[p - mem_min + 3].int_ = 0;
  ctx->mem[p - mem_min + 4].int_ = 0;
  ctx->mem[p - mem_min + 5].hh.rh = -1073741824;
  ctx->mem[p - mem_min + 5].hh.U2.b0 = 0;
  ctx->mem[p - mem_min + 5].hh.U2.b1 = 0;
  ctx->mem[p - mem_min + 6].gr = 0.0;
  return p;
}

halfword new_rule(ctex_t *ctx) {
  halfword p = get_node(ctx, 4);
  ctx->mem[p - mem_min].hh.U2.b0 = 2;
  ctx->mem[p - mem_min].hh.U2.b1 = 0;
  ctx->mem[p - mem_min + 1].int_ = -1073741824;
  ctx->mem[p - mem_min + 2].int_ = -1073741824;
  ctx->mem[p - mem_min + 3].int_ = -1073741824;
  return p;
}

halfword new_ligature(ctex_t *ctx, quarterword f, quarterword c, halfword q) {
  halfword p = get_node(ctx, 2);
  ctx->mem[p - mem_min].hh.U2.b0 = 6;
  ctx->mem[p - mem_min + 1].hh.U2.b0 = f;
  ctx->mem[p - mem_min + 1].hh.U2.b1 = c;
  ctx->mem[p - mem_min + 1].hh.rh = q;
  ctx->mem[p - mem_min].hh.U2.b1 = 0;
  return p;
}

halfword new_lig_item(ctex_t *ctx, quarterword c) {
  halfword p = get_node(ctx, 2);
  ctx->mem[p - mem_min].hh.U2.b1 = c;
  ctx->mem[p - mem_min + 1].hh.rh = -1073741824;
  return p;
}

halfword new_disc(ctex_t *ctx) {
  halfword p = get_node(ctx, 2);
  ctx->mem[p - mem_min].hh.U2.b0 = 7;
  ctx->mem[p - mem_min].hh.U2.b1 = 0;
  ctx->mem[p - mem_min + 1].hh.lh = -1073741824;
  ctx->mem[p - mem_min + 1].hh.rh = -1073741824;
  return p;
}

halfword new_math(ctex_t *ctx, scaled w, small_number s) {
  halfword p = get_node(ctx, 2);
  ctx->mem[p - mem_min].hh.U2.b0 = 9;
  ctx->mem[p - mem_min].hh.U2.b1 = s;
  ctx->mem[p - mem_min + 1].int_ = w;
  return p;
}

halfword new_spec(ctex_t *ctx, halfword p) {
  halfword q = get_node(ctx, 4);
  ctx->mem[q - mem_min] = ctx->mem[p - mem_min];
  ctx->mem[q - mem_min].hh.rh = -1073741824;
  ctx->mem[q - mem_min + 1].int_ = ctx->mem[p - mem_min + 1].int_;
  ctx->mem[q - mem_min + 2].int_ = ctx->mem[p - mem_min + 2].int_;
  ctx->mem[q - mem_min + 3].int_ = ctx->mem[p - mem_min + 3].int_;
  return q;
}

halfword new_param_glue(ctex_t *ctx, small_number n) {
  halfword q;
  halfword p = get_node(ctx, 2);
  ctx->mem[p - mem_min].hh.U2.b0 = 10;
  ctx->mem[p - mem_min].hh.U2.b1 = n + 1;
  ctx->mem[p - mem_min + 1].hh.rh = -1073741824;
  q = ctx->eqtb[n + 9782].hh.rh;
  ctx->mem[p - mem_min + 1].hh.lh = q;
  ++ctx->mem[q - mem_min].hh.rh;
  return p;
}

halfword new_glue(ctex_t *ctx, halfword q) {
  halfword p = get_node(ctx, 2);
  ctx->mem[p - mem_min].hh.U2.b0 = 10;
  ctx->mem[p - mem_min].hh.U2.b1 = 0;
  ctx->mem[p - mem_min + 1].hh.rh = -1073741824;
  ctx->mem[p - mem_min + 1].hh.lh = q;
  ++ctx->mem[q - mem_min].hh.rh;
  return p;
}

halfword new_skip_param(ctex_t *ctx, small_number n) {
  halfword p;
  ctx->temp_ptr = new_spec(ctx, ctx->eqtb[n + 9782].hh.rh);
  p = new_glue(ctx, ctx->temp_ptr);
  ctx->mem[ctx->temp_ptr - mem_min].hh.rh = -1073741824;
  ctx->mem[p - mem_min].hh.U2.b1 = n + 1;
  return p;
}

halfword new_kern(ctex_t *ctx, scaled w) {
  halfword p = get_node(ctx, 2);
  ctx->mem[p - mem_min].hh.U2.b0 = 11;
  ctx->mem[p - mem_min].hh.U2.b1 = 0;
  ctx->mem[p - mem_min + 1].int_ = w;
  return p;
}

halfword new_penalty(ctex_t *ctx, integer m) {
  halfword p = get_node(ctx, 2);
  ctx->mem[p - mem_min].hh.U2.b0 = 12;
  ctx->mem[p - mem_min].hh.U2.b1 = 0;
  ctx->mem[p - mem_min + 1].int_ = m;
  return p;
}

void short_display(ctex_t *ctx, integer p) {
  integer n;
  while (p > mem_min) {
    if (p >= ctx->hi_mem_min) {
      if (p <= ctx->mem_end) {
        if (ctx->mem[p - mem_min].hh.U2.b0 != ctx->font_in_short_display) {
          if (ctx->mem[p - mem_min].hh.U2.b0 > font_max)
            print_char(ctx, 42);
          else
            print_esc(ctx, ctx->hash[ctx->mem[p - mem_min].hh.U2.b0 + 9010].rh);
          print_char(ctx, 32);
          ctx->font_in_short_display = ctx->mem[p - mem_min].hh.U2.b0;
        }
        print(ctx, ctx->mem[p - mem_min].hh.U2.b1);
      }
    } else {
      switch (ctx->mem[p - mem_min].hh.U2.b0) {
      case 0:
      case 1:
      case 3:
      case 8:
      case 4:
      case 5:
      case 13:
        print(ctx, 308);
        break;
      case 2:
        print_char(ctx, 124);
        break;
      case 10:
        if (ctx->mem[p - mem_min + 1].hh.lh)
          print_char(ctx, 32);
        break;
      case 9:
        print_char(ctx, 36);
        break;
      case 6:
        short_display(ctx, ctx->mem[p - mem_min + 1].hh.rh);
        break;
      case 7:
        short_display(ctx, ctx->mem[p - mem_min + 1].hh.lh);
        short_display(ctx, ctx->mem[p - mem_min + 1].hh.rh);
        n = ctx->mem[p - mem_min].hh.U2.b1;
        while (n > 0) {
          if (ctx->mem[p - mem_min].hh.rh != (-1073741824))
            p = ctx->mem[p - mem_min].hh.rh;
          --n;
        }
        break;
      default:
        break;
      }
    }
    p = ctx->mem[p - mem_min].hh.rh;
  }
}

void print_font_and_char(ctex_t *ctx, integer p) {
  if (p > ctx->mem_end) {
    print_esc(ctx, 309);
    return;
  }
  if (ctx->mem[p - mem_min].hh.U2.b0 > font_max)
    print_char(ctx, 42);
  else
    print_esc(ctx, ctx->hash[ctx->mem[p - mem_min].hh.U2.b0 + 9010].rh);
  print_char(ctx, 32);
  print(ctx, ctx->mem[p - mem_min].hh.U2.b1);
}

void print_mark(ctex_t *ctx, integer p) {
  print_char(ctx, 123);
  if ((p < ctx->hi_mem_min) || (p > ctx->mem_end))
    print_esc(ctx, 309);
  else
    show_token_list(ctx, ctx->mem[p - mem_min].hh.rh, -1073741824,
                    max_print_line - 10);
  print_char(ctx, 125);
}

void print_rule_dimen(ctex_t *ctx, scaled d) {
  if (d == (-1073741824))
    print_char(ctx, 42);
  else
    print_scaled(ctx, d);
}

void print_glue(ctex_t *ctx, scaled d, integer order, str_number s) {
  print_scaled(ctx, d);
  if (((unsigned)order) > 3) {
    print(ctx, 310);
    return;
  }
  if (order <= 0) {
    if (s)
      print(ctx, s);
    return;
  }
  print(ctx, 311);
  while (order > 1) {
    print_char(ctx, 108);
    --order;
  }
}

void print_spec(ctex_t *ctx, integer p, str_number s) {
  if ((p < mem_min) || (p >= ctx->lo_mem_max)) {
    print_char(ctx, 42);
    return;
  }
  print_scaled(ctx, ctx->mem[p - mem_min + 1].int_);
  if (s)
    print(ctx, s);
  if (ctx->mem[p - mem_min + 2].int_) {
    print(ctx, 312);
    print_glue(ctx, ctx->mem[p - mem_min + 2].int_,
               ctx->mem[p - mem_min].hh.U2.b0, s);
  }
  if (ctx->mem[p - mem_min + 3].int_) {
    print(ctx, 313);
    print_glue(ctx, ctx->mem[p - mem_min + 3].int_,
               ctx->mem[p - mem_min].hh.U2.b1, s);
  }
}

void print_fam_and_char(ctex_t *ctx, halfword p) {
  print_esc(ctx, 464);
  print_int(ctx, ctx->mem[p - mem_min].hh.U2.b0);
  print_char(ctx, 32);
  print(ctx, ctx->mem[p - mem_min].hh.U2.b1);
}

void print_delimiter(ctex_t *ctx, halfword p) {
  integer a =
      (ctx->mem[p - mem_min].qqqq.b0 * 256) + ctx->mem[p - mem_min].qqqq.b1;
  a = (a * 4096) + (ctx->mem[p - mem_min].qqqq.b2 * 256) +
      ctx->mem[p - mem_min].qqqq.b3;
  if (a < 0)
    print_int(ctx, a);
  else
    print_hex(ctx, a);
}

void print_subsidiary_data(ctex_t *ctx, halfword p, ASCII_code c) {
  if (ctx->pool_ptr - ctx->str_start[ctx->str_ptr] >= ctx->depth_threshold) {
    if (ctx->mem[p - mem_min].hh.rh)
      print(ctx, 314);
    return;
  }
  ctx->str_pool[ctx->pool_ptr] = c;
  ++ctx->pool_ptr;
  ctx->temp_ptr = p;
  switch (ctx->mem[p - mem_min].hh.rh) {
  case 1:
    print_ln(ctx);
    print_current_string(ctx);
    print_fam_and_char(ctx, p);
    break;
  case 2:
    show_info(ctx);
    break;
  case 3:
    if (ctx->mem[p - mem_min].hh.lh == (-1073741824)) {
      print_ln(ctx);
      print_current_string(ctx);
      print(ctx, 859);
    } else {
      show_info(ctx);
    }
    break;
  default:
    break;
  }
  --ctx->pool_ptr;
}

void print_style(ctex_t *ctx, integer c) {
  switch (c / 2) {
  case 0:
    print_esc(ctx, 860);
    break;
  case 1:
    print_esc(ctx, 861);
    break;
  case 2:
    print_esc(ctx, 862);
    break;
  case 3:
    print_esc(ctx, 863);
    break;
  default:
    print(ctx, 864);
    break;
  }
}

void print_skip_param(ctex_t *ctx, integer n) {
  switch (n) {
  case 0:
    print_esc(ctx, 376);
    break;
  case 1:
    print_esc(ctx, 377);
    break;
  case 2:
    print_esc(ctx, 378);
    break;
  case 3:
    print_esc(ctx, 379);
    break;
  case 4:
    print_esc(ctx, 380);
    break;
  case 5:
    print_esc(ctx, 381);
    break;
  case 6:
    print_esc(ctx, 382);
    break;
  case 7:
    print_esc(ctx, 383);
    break;
  case 8:
    print_esc(ctx, 384);
    break;
  case 9:
    print_esc(ctx, 385);
    break;
  case 10:
    print_esc(ctx, 386);
    break;
  case 11:
    print_esc(ctx, 387);
    break;
  case 12:
    print_esc(ctx, 388);
    break;
  case 13:
    print_esc(ctx, 389);
    break;
  case 14:
    print_esc(ctx, 390);
    break;
  case 15:
    print_esc(ctx, 391);
    break;
  case 16:
    print_esc(ctx, 392);
    break;
  case 17:
    print_esc(ctx, 393);
    break;
  default:
    print(ctx, 394);
    break;
  }
}

void show_node_list(ctex_t *ctx, integer p) {
  integer n = 0;
  double g;
  if (ctx->pool_ptr - ctx->str_start[ctx->str_ptr] > ctx->depth_threshold) {
    if (p > (-1073741824))
      print(ctx, 314);
    goto _L10;
  }
  while (p > mem_min) {
    print_ln(ctx);
    print_current_string(ctx);
    if (p > ctx->mem_end) {
      print(ctx, 315);
      goto _L10;
    }
    ++n;
    if (n > ctx->breadth_max) {
      print(ctx, 316);
      goto _L10;
    }
    if (p >= ctx->hi_mem_min) {
      print_font_and_char(ctx, p);
    } else {
      switch (ctx->mem[p - mem_min].hh.U2.b0) {
      case 0:
      case 1:
      case 13:
        if (!ctx->mem[p - mem_min].hh.U2.b0) {
          print_esc(ctx, 104);
        } else if (ctx->mem[p - mem_min].hh.U2.b0 == 1)
          print_esc(ctx, 118);
        else
          print_esc(ctx, 318);
        print(ctx, 319);
        print_scaled(ctx, ctx->mem[p - mem_min + 3].int_);
        print_char(ctx, 43);
        print_scaled(ctx, ctx->mem[p - mem_min + 2].int_);
        print(ctx, 320);
        print_scaled(ctx, ctx->mem[p - mem_min + 1].int_);
        if (ctx->mem[p - mem_min].hh.U2.b0 == 13) {
          if (ctx->mem[p - mem_min].hh.U2.b1) {
            print(ctx, 286);
            print_int(ctx, ctx->mem[p - mem_min].hh.U2.b1 + 1);
            print(ctx, 322);
          }
          if (ctx->mem[p - mem_min + 6].int_) {
            print(ctx, 323);
            print_glue(ctx, ctx->mem[p - mem_min + 6].int_,
                       ctx->mem[p - mem_min + 5].hh.U2.b1, 0);
          }
          if (ctx->mem[p - mem_min + 4].int_) {
            print(ctx, 324);
            print_glue(ctx, ctx->mem[p - mem_min + 4].int_,
                       ctx->mem[p - mem_min + 5].hh.U2.b0, 0);
          }
        } else {
          g = ctx->mem[p - mem_min + 6].gr;
          if (g && ctx->mem[p - mem_min + 5].hh.U2.b0) {
            print(ctx, 325);
            if (ctx->mem[p - mem_min + 5].hh.U2.b0 == 2)
              print(ctx, 326);
            if (abs(ctx->mem[p - mem_min + 6].int_) < 1048576) {
              print(ctx, 327);
            } else if (fabs(g) > 20000.0) {
              if (g > 0.0)
                print_char(ctx, 62);
              else
                print(ctx, 328);
              print_glue(ctx, 1310720000, ctx->mem[p - mem_min + 5].hh.U2.b1,
                         0);
            } else {
              print_glue(ctx, round(65536 * g),
                         ctx->mem[p - mem_min + 5].hh.U2.b1, 0);
            }
          }
          if (ctx->mem[p - mem_min + 4].int_) {
            print(ctx, 321);
            print_scaled(ctx, ctx->mem[p - mem_min + 4].int_);
          }
        }
        ctx->str_pool[ctx->pool_ptr] = 46;
        ++ctx->pool_ptr;
        show_node_list(ctx, ctx->mem[p - mem_min + 5].hh.rh);
        --ctx->pool_ptr;
        break;
      case 2:
        print_esc(ctx, 329);
        print_rule_dimen(ctx, ctx->mem[p - mem_min + 3].int_);
        print_char(ctx, 43);
        print_rule_dimen(ctx, ctx->mem[p - mem_min + 2].int_);
        print(ctx, 320);
        print_rule_dimen(ctx, ctx->mem[p - mem_min + 1].int_);
        break;
      case 3:
        print_esc(ctx, 330);
        print_int(ctx, ctx->mem[p - mem_min].hh.U2.b1);
        print(ctx, 331);
        print_scaled(ctx, ctx->mem[p - mem_min + 3].int_);
        print(ctx, 332);
        print_spec(ctx, ctx->mem[p - mem_min + 4].hh.rh, 0);
        print_char(ctx, 44);
        print_scaled(ctx, ctx->mem[p - mem_min + 2].int_);
        print(ctx, 333);
        print_int(ctx, ctx->mem[p - mem_min + 1].int_);
        ctx->str_pool[ctx->pool_ptr] = 46;
        ++ctx->pool_ptr;
        show_node_list(ctx, ctx->mem[p - mem_min + 4].hh.lh);
        --ctx->pool_ptr;
        break;
      case 8:
        switch (ctx->mem[p - mem_min].hh.U2.b1) {
        case 0:
          print_write_whatsit(ctx, 1284, p);
          print_char(ctx, 61);
          print_file_name(ctx, ctx->mem[p - mem_min + 1].hh.rh,
                          ctx->mem[p - mem_min + 2].hh.lh,
                          ctx->mem[p - mem_min + 2].hh.rh);
          break;
        case 1:
          print_write_whatsit(ctx, 594, p);
          print_mark(ctx, ctx->mem[p - mem_min + 1].hh.rh);
          break;
        case 2:
          print_write_whatsit(ctx, 1285, p);
          break;
        case 3:
          print_esc(ctx, 1286);
          print_mark(ctx, ctx->mem[p - mem_min + 1].hh.rh);
          break;
        case 4:
          print_esc(ctx, 1288);
          print_int(ctx, ctx->mem[p - mem_min + 1].hh.rh);
          print(ctx, 1291);
          print_int(ctx, ctx->mem[p - mem_min + 1].hh.U2.b0);
          print_char(ctx, 44);
          print_int(ctx, ctx->mem[p - mem_min + 1].hh.U2.b1);
          print_char(ctx, 41);
          break;
        default:
          print(ctx, 1292);
          break;
        }
        break;
      case 10:
        if (ctx->mem[p - mem_min].hh.U2.b1 >= 100) {
          print_esc(ctx, 338);
          if (ctx->mem[p - mem_min].hh.U2.b1 == 101) {
            print_char(ctx, 99);
          } else if (ctx->mem[p - mem_min].hh.U2.b1 == 102)
            print_char(ctx, 120);
          print(ctx, 339);
          print_spec(ctx, ctx->mem[p - mem_min + 1].hh.lh, 0);
          ctx->str_pool[ctx->pool_ptr] = 46;
          ++ctx->pool_ptr;
          show_node_list(ctx, ctx->mem[p - mem_min + 1].hh.rh);
          --ctx->pool_ptr;
        } else {
          print_esc(ctx, 334);
          if (ctx->mem[p - mem_min].hh.U2.b1) {
            print_char(ctx, 40);
            if (ctx->mem[p - mem_min].hh.U2.b1 < 98) {
              print_skip_param(ctx, ctx->mem[p - mem_min].hh.U2.b1 - 1);
            } else if (ctx->mem[p - mem_min].hh.U2.b1 == 98)
              print_esc(ctx, 335);
            else
              print_esc(ctx, 336);
            print_char(ctx, 41);
          }
          if (ctx->mem[p - mem_min].hh.U2.b1 != 98) {
            print_char(ctx, 32);
            if (ctx->mem[p - mem_min].hh.U2.b1 < 98)
              print_spec(ctx, ctx->mem[p - mem_min + 1].hh.lh, 0);
            else
              print_spec(ctx, ctx->mem[p - mem_min + 1].hh.lh, 337);
          }
        }
        break;
      case 11:
        if (ctx->mem[p - mem_min].hh.U2.b1 != 99) {
          print_esc(ctx, 340);
          if (ctx->mem[p - mem_min].hh.U2.b1)
            print_char(ctx, 32);
          print_scaled(ctx, ctx->mem[p - mem_min + 1].int_);
          if (ctx->mem[p - mem_min].hh.U2.b1 == 2)
            print(ctx, 341);
        } else {
          print_esc(ctx, 342);
          print_scaled(ctx, ctx->mem[p - mem_min + 1].int_);
          print(ctx, 337);
        }
        break;
      case 9:
        print_esc(ctx, 343);
        if (!ctx->mem[p - mem_min].hh.U2.b1)
          print(ctx, 344);
        else
          print(ctx, 345);
        if (ctx->mem[p - mem_min + 1].int_) {
          print(ctx, 346);
          print_scaled(ctx, ctx->mem[p - mem_min + 1].int_);
        }
        break;
      case 6:
        print_font_and_char(ctx, p + 1);
        print(ctx, 347);
        if (ctx->mem[p - mem_min].hh.U2.b1 > 1)
          print_char(ctx, 124);
        ctx->font_in_short_display = ctx->mem[p - mem_min + 1].hh.U2.b0;
        short_display(ctx, ctx->mem[p - mem_min + 1].hh.rh);
        if (ctx->mem[p - mem_min].hh.U2.b1 & 1)
          print_char(ctx, 124);
        print_char(ctx, 41);
        break;
      case 12:
        print_esc(ctx, 348);
        print_int(ctx, ctx->mem[p - mem_min + 1].int_);
        break;
      case 7:
        print_esc(ctx, 349);
        if (ctx->mem[p - mem_min].hh.U2.b1 > 0) {
          print(ctx, 350);
          print_int(ctx, ctx->mem[p - mem_min].hh.U2.b1);
        }
        ctx->str_pool[ctx->pool_ptr] = 46;
        ++ctx->pool_ptr;
        show_node_list(ctx, ctx->mem[p - mem_min + 1].hh.lh);
        --ctx->pool_ptr;
        ctx->str_pool[ctx->pool_ptr] = 124;
        ++ctx->pool_ptr;
        show_node_list(ctx, ctx->mem[p - mem_min + 1].hh.rh);
        --ctx->pool_ptr;
        break;
      case 4:
        print_esc(ctx, 351);
        print_mark(ctx, ctx->mem[p - mem_min + 1].int_);
        break;
      case 5:
        print_esc(ctx, 352);
        ctx->str_pool[ctx->pool_ptr] = 46;
        ++ctx->pool_ptr;
        show_node_list(ctx, ctx->mem[p - mem_min + 1].int_);
        --ctx->pool_ptr;
        break;
      case 14:
        print_style(ctx, ctx->mem[p - mem_min].hh.U2.b1);
        break;
      case 15:
        print_esc(ctx, 525);
        ctx->str_pool[ctx->pool_ptr] = 68;
        ++ctx->pool_ptr;
        show_node_list(ctx, ctx->mem[p - mem_min + 1].hh.lh);
        --ctx->pool_ptr;
        ctx->str_pool[ctx->pool_ptr] = 84;
        ++ctx->pool_ptr;
        show_node_list(ctx, ctx->mem[p - mem_min + 1].hh.rh);
        --ctx->pool_ptr;
        ctx->str_pool[ctx->pool_ptr] = 83;
        ++ctx->pool_ptr;
        show_node_list(ctx, ctx->mem[p - mem_min + 2].hh.lh);
        --ctx->pool_ptr;
        ctx->str_pool[ctx->pool_ptr] = 115;
        ++ctx->pool_ptr;
        show_node_list(ctx, ctx->mem[p - mem_min + 2].hh.rh);
        --ctx->pool_ptr;
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
        switch (ctx->mem[p - mem_min].hh.U2.b0) {
        case 16:
          print_esc(ctx, 865);
          break;
        case 17:
          print_esc(ctx, 866);
          break;
        case 18:
          print_esc(ctx, 867);
          break;
        case 19:
          print_esc(ctx, 868);
          break;
        case 20:
          print_esc(ctx, 869);
          break;
        case 21:
          print_esc(ctx, 870);
          break;
        case 22:
          print_esc(ctx, 871);
          break;
        case 23:
          print_esc(ctx, 872);
          break;
        case 27:
          print_esc(ctx, 873);
          break;
        case 26:
          print_esc(ctx, 874);
          break;
        case 29:
          print_esc(ctx, 539);
          break;
        case 24:
          print_esc(ctx, 533);
          print_delimiter(ctx, p + 4);
          break;
        case 28:
          print_esc(ctx, 508);
          print_fam_and_char(ctx, p + 4);
          break;
        case 30:
          print_esc(ctx, 875);
          print_delimiter(ctx, p + 1);
          break;
        case 31:
          print_esc(ctx, 876);
          print_delimiter(ctx, p + 1);
          break;
        }
        if (ctx->mem[p - mem_min].hh.U2.b1) {
          if (ctx->mem[p - mem_min].hh.U2.b1 == 1)
            print_esc(ctx, 877);
          else
            print_esc(ctx, 878);
        }
        if (ctx->mem[p - mem_min].hh.U2.b0 < 30)
          print_subsidiary_data(ctx, p + 1, 46);
        print_subsidiary_data(ctx, p + 2, 94);
        print_subsidiary_data(ctx, p + 3, 95);
        break;
      case 25:
        print_esc(ctx, 879);
        if (ctx->mem[p - mem_min + 1].int_ == 1073741824)
          print(ctx, 880);
        else
          print_scaled(ctx, ctx->mem[p - mem_min + 1].int_);
        if (ctx->mem[p - mem_min + 4].qqqq.b0 ||
            ctx->mem[p - mem_min + 4].qqqq.b1 ||
            ctx->mem[p - mem_min + 4].qqqq.b2 ||
            ctx->mem[p - mem_min + 4].qqqq.b3) {
          print(ctx, 881);
          print_delimiter(ctx, p + 4);
        }
        if (ctx->mem[p - mem_min + 5].qqqq.b0 ||
            ctx->mem[p - mem_min + 5].qqqq.b1 ||
            ctx->mem[p - mem_min + 5].qqqq.b2 ||
            ctx->mem[p - mem_min + 5].qqqq.b3) {
          print(ctx, 882);
          print_delimiter(ctx, p + 5);
        }
        print_subsidiary_data(ctx, p + 2, 92);
        print_subsidiary_data(ctx, p + 3, 47);
        break;
      default:
        print(ctx, 317);
        break;
      }
    }
    p = ctx->mem[p - mem_min].hh.rh;
  }
_L10:;
}

void show_box(ctex_t *ctx, halfword p) {
  ctx->depth_threshold = ctx->eqtb[12188].int_;
  ctx->breadth_max = ctx->eqtb[12187].int_;
  if (ctx->breadth_max <= 0)
    ctx->breadth_max = 5;
  if (ctx->pool_ptr + ctx->depth_threshold >= pool_size)
    ctx->depth_threshold = pool_size - ctx->pool_ptr - 1;
  show_node_list(ctx, p);
  print_ln(ctx);
}

void delete_token_ref(ctex_t *ctx, halfword p) {
  if (ctx->mem[p - mem_min].hh.lh == (-1073741824))
    flush_list(ctx, p);
  else
    --ctx->mem[p - mem_min].hh.lh;
}

void delete_glue_ref(ctex_t *ctx, halfword p) {
  if (ctx->mem[p - mem_min].hh.rh == (-1073741824))
    free_node(ctx, p, 4);
  else
    --ctx->mem[p - mem_min].hh.rh;
}

void flush_node_list(ctex_t *ctx, halfword p) {
  halfword q;
  while (p != (-1073741824)) {
    q = ctx->mem[p - mem_min].hh.rh;
    if (p >= ctx->hi_mem_min) {
      ctx->mem[p - mem_min].hh.rh = ctx->avail;
      ctx->avail = p;
    } else {
      switch (ctx->mem[p - mem_min].hh.U2.b0) {
      case 0:
      case 1:
      case 13:
        flush_node_list(ctx, ctx->mem[p - mem_min + 5].hh.rh);
        free_node(ctx, p, 7);
        goto _L30;
        break;
      case 2:
        free_node(ctx, p, 4);
        goto _L30;
        break;
      case 3:
        flush_node_list(ctx, ctx->mem[p - mem_min + 4].hh.lh);
        delete_glue_ref(ctx, ctx->mem[p - mem_min + 4].hh.rh);
        free_node(ctx, p, 5);
        goto _L30;
        break;
      case 8:
        switch (ctx->mem[p - mem_min].hh.U2.b1) {
        case 0:
          free_node(ctx, p, 3);
          break;
        case 1:
        case 3:
          delete_token_ref(ctx, ctx->mem[p - mem_min + 1].hh.rh);
          free_node(ctx, p, 2);
          goto _L30;
          break;
        case 2:
        case 4:
          free_node(ctx, p, 2);
          break;
        default:
          confusion(ctx, 1294);
          break;
        }
        goto _L30;
        break;
      case 10:
        if (ctx->mem[ctx->mem[p - mem_min + 1].hh.lh - mem_min].hh.rh ==
            (-1073741824))
          free_node(ctx, ctx->mem[p - mem_min + 1].hh.lh, 4);
        else
          --ctx->mem[ctx->mem[p - mem_min + 1].hh.lh - mem_min].hh.rh;
        if (ctx->mem[p - mem_min + 1].hh.rh != (-1073741824))
          flush_node_list(ctx, ctx->mem[p - mem_min + 1].hh.rh);
        break;
      case 11:
      case 9:
      case 12:
        // blank case
        break;
      case 6:
        flush_node_list(ctx, ctx->mem[p - mem_min + 1].hh.rh);
        break;
      case 4:
        delete_token_ref(ctx, ctx->mem[p - mem_min + 1].int_);
        break;
      case 7:
        flush_node_list(ctx, ctx->mem[p - mem_min + 1].hh.lh);
        flush_node_list(ctx, ctx->mem[p - mem_min + 1].hh.rh);
        break;
      case 5:
        flush_node_list(ctx, ctx->mem[p - mem_min + 1].int_);
        break;
      case 14:
        free_node(ctx, p, 3);
        goto _L30;
        break;
      case 15:
        flush_node_list(ctx, ctx->mem[p - mem_min + 1].hh.lh);
        flush_node_list(ctx, ctx->mem[p - mem_min + 1].hh.rh);
        flush_node_list(ctx, ctx->mem[p - mem_min + 2].hh.lh);
        flush_node_list(ctx, ctx->mem[p - mem_min + 2].hh.rh);
        free_node(ctx, p, 3);
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
        if (ctx->mem[p - mem_min + 1].hh.rh >= 2)
          flush_node_list(ctx, ctx->mem[p - mem_min + 1].hh.lh);
        if (ctx->mem[p - mem_min + 2].hh.rh >= 2)
          flush_node_list(ctx, ctx->mem[p - mem_min + 2].hh.lh);
        if (ctx->mem[p - mem_min + 3].hh.rh >= 2)
          flush_node_list(ctx, ctx->mem[p - mem_min + 3].hh.lh);
        if (ctx->mem[p - mem_min].hh.U2.b0 == 24) {
          free_node(ctx, p, 5);
        } else if (ctx->mem[p - mem_min].hh.U2.b0 == 28)
          free_node(ctx, p, 5);
        else
          free_node(ctx, p, 4);
        goto _L30;
        break;
      case 30:
      case 31:
        free_node(ctx, p, 4);
        goto _L30;
        break;
      case 25:
        flush_node_list(ctx, ctx->mem[p - mem_min + 2].hh.lh);
        flush_node_list(ctx, ctx->mem[p - mem_min + 3].hh.lh);
        free_node(ctx, p, 6);
        goto _L30;
        break;
      default:
        confusion(ctx, 353);
        break;
      }
      free_node(ctx, p, 2);
    _L30:;
    }
    p = q;
  }
}

halfword copy_node_list(ctex_t *ctx, halfword p) {
  halfword r;
  char words;
  halfword h = get_avail(ctx);
  halfword q = h;
  while (p != (-1073741824)) {
    words = 1;
    if (p >= ctx->hi_mem_min) {
      r = get_avail(ctx);
    } else {
      switch (ctx->mem[p - mem_min].hh.U2.b0) {
      case 0:
      case 1:
      case 13:
        r = get_node(ctx, 7);
        ctx->mem[r - mem_min + 6] = ctx->mem[p - mem_min + 6];
        ctx->mem[r - mem_min + 5] = ctx->mem[p - mem_min + 5];
        ctx->mem[r - mem_min + 5].hh.rh =
            copy_node_list(ctx, ctx->mem[p - mem_min + 5].hh.rh);
        words = 5;
        break;
      case 2:
        r = get_node(ctx, 4);
        words = 4;
        break;
      case 3:
        r = get_node(ctx, 5);
        ctx->mem[r - mem_min + 4] = ctx->mem[p - mem_min + 4];
        ++ctx->mem[ctx->mem[p - mem_min + 4].hh.rh - mem_min].hh.rh;
        ctx->mem[r - mem_min + 4].hh.lh =
            copy_node_list(ctx, ctx->mem[p - mem_min + 4].hh.lh);
        words = 4;
        break;
      case 8:
        switch (ctx->mem[p - mem_min].hh.U2.b1) {
        case 0:
          r = get_node(ctx, 3);
          words = 3;
          break;
        case 1:
        case 3:
          r = get_node(ctx, 2);
          ++ctx->mem[ctx->mem[p - mem_min + 1].hh.rh - mem_min].hh.lh;
          words = 2;
          break;
        case 2:
        case 4:
          r = get_node(ctx, 2);
          words = 2;
          break;
        default:
          confusion(ctx, 1293);
          break;
        }
        break;
      case 10:
        r = get_node(ctx, 2);
        ++ctx->mem[ctx->mem[p - mem_min + 1].hh.lh - mem_min].hh.rh;
        ctx->mem[r - mem_min + 1].hh.lh = ctx->mem[p - mem_min + 1].hh.lh;
        ctx->mem[r - mem_min + 1].hh.rh =
            copy_node_list(ctx, ctx->mem[p - mem_min + 1].hh.rh);
        break;
      case 11:
      case 9:
      case 12:
        r = get_node(ctx, 2);
        words = 2;
        break;
      case 6:
        r = get_node(ctx, 2);
        ctx->mem[r - mem_min + 1] = ctx->mem[p - mem_min + 1];
        ctx->mem[r - mem_min + 1].hh.rh =
            copy_node_list(ctx, ctx->mem[p - mem_min + 1].hh.rh);
        break;
      case 7:
        r = get_node(ctx, 2);
        ctx->mem[r - mem_min + 1].hh.lh =
            copy_node_list(ctx, ctx->mem[p - mem_min + 1].hh.lh);
        ctx->mem[r - mem_min + 1].hh.rh =
            copy_node_list(ctx, ctx->mem[p - mem_min + 1].hh.rh);
        break;
      case 4:
        r = get_node(ctx, 2);
        ++ctx->mem[ctx->mem[p - mem_min + 1].int_ - mem_min].hh.lh;
        words = 2;
        break;
      case 5:
        r = get_node(ctx, 2);
        ctx->mem[r - mem_min + 1].int_ =
            copy_node_list(ctx, ctx->mem[p - mem_min + 1].int_);
        break;
      default:
        confusion(ctx, 354);
        break;
      }
    }
    while (words > 0) {
      --words;
      ctx->mem[r + words - mem_min] = ctx->mem[p + words - mem_min];
    }
    ctx->mem[q - mem_min].hh.rh = r;
    q = r;
    p = ctx->mem[p - mem_min].hh.rh;
  }
  ctx->mem[q - mem_min].hh.rh = -1073741824;
  q = ctx->mem[h - mem_min].hh.rh;
  ctx->mem[h - mem_min].hh.rh = ctx->avail;
  ctx->avail = h;
  return q;
}

void print_mode(ctex_t *ctx, integer m) {
  if (m > 0) {
    switch (m / 101) {
    case 0:
      print(ctx, 355);
      break;
    case 1:
      print(ctx, 356);
      break;
    case 2:
      print(ctx, 357);
      break;
    }
  } else if (!m) {
    print(ctx, 358);
  } else {
    switch ((-m) / 101) {
    case 0:
      print(ctx, 359);
      break;
    case 1:
      print(ctx, 360);
      break;
    case 2:
      print(ctx, 343);
      break;
    }
  }
  print(ctx, 361);
}

void push_nest(ctex_t *ctx) {
  if (ctx->nest_ptr > ctx->max_nest_stack) {
    ctx->max_nest_stack = ctx->nest_ptr;
    if (ctx->nest_ptr == nest_size)
      overflow(ctx, 362, nest_size);
  }
  ctx->nest[ctx->nest_ptr] = ctx->cur_list;
  ++ctx->nest_ptr;
  ctx->cur_list.head_field = get_avail(ctx);
  ctx->cur_list.tail_field = ctx->cur_list.head_field;
  ctx->cur_list.pg_field = 0;
  ctx->cur_list.ml_field = ctx->line;
}

void pop_nest(ctex_t *ctx) {
  ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh = ctx->avail;
  ctx->avail = ctx->cur_list.head_field;
  --ctx->nest_ptr;
  ctx->cur_list = ctx->nest[ctx->nest_ptr];
}

void show_activities(ctex_t *ctx) {
  int p;
  short m;
  memory_word a;
  halfword q, r;
  integer t;
  ctx->nest[ctx->nest_ptr] = ctx->cur_list;
  print_nl(ctx, 338);
  print_ln(ctx);
  for (p = ctx->nest_ptr; p >= 0; --p) {
    m = ctx->nest[p].mode_field;
    a = ctx->nest[p].aux_field;
    print_nl(ctx, 363);
    print_mode(ctx, m);
    print(ctx, 364);
    print_int(ctx, abs(ctx->nest[p].ml_field));
    if (m == 102) {
      if (ctx->nest[p].pg_field != 8585216) {
        print(ctx, 365);
        print_int(ctx, ctx->nest[p].pg_field & 65535);
        print(ctx, 366);
        print_int(ctx, ctx->nest[p].pg_field / 4194304);
        print_char(ctx, 44);
        print_int(ctx, (ctx->nest[p].pg_field / 65536) & 63);
        print_char(ctx, 41);
      }
    }
    if (ctx->nest[p].ml_field < 0)
      print(ctx, 367);
    if (!p) {
      if (mem_max - 2 != ctx->page_tail) {
        print_nl(ctx, 979);
        if (ctx->output_active)
          print(ctx, 980);
        show_box(ctx, ctx->mem[mem_max - mem_min - 2].hh.rh);
        if (ctx->page_contents > 0) {
          print_nl(ctx, 981);
          print_totals(ctx);
          print_nl(ctx, 982);
          print_scaled(ctx, ctx->page_so_far[0]);
          r = ctx->mem[mem_max - mem_min].hh.rh;
          while (r != mem_max) {
            print_ln(ctx);
            print_esc(ctx, 330);
            t = ctx->mem[r - mem_min].hh.U2.b1;
            print_int(ctx, t);
            print(ctx, 983);
            if (ctx->eqtb[t + 12218].int_ == 1000)
              t = ctx->mem[r - mem_min + 3].int_;
            else
              t = x_over_n(ctx, ctx->mem[r - mem_min + 3].int_, 1000) *
                  ctx->eqtb[t + 12218].int_;
            print_scaled(ctx, t);
            if (ctx->mem[r - mem_min].hh.U2.b0 == 1) {
              q = mem_max - 2;
              t = 0;
              do {
                q = ctx->mem[q - mem_min].hh.rh;
                if ((ctx->mem[q - mem_min].hh.U2.b0 == 3) &&
                    (ctx->mem[q - mem_min].hh.U2.b1 ==
                     ctx->mem[r - mem_min].hh.U2.b1))
                  ++t;
              } while (q != ctx->mem[r - mem_min + 1].hh.lh);
              print(ctx, 984);
              print_int(ctx, t);
              print(ctx, 985);
            }
            r = ctx->mem[r - mem_min].hh.rh;
          }
        }
      }
      if (ctx->mem[mem_max - mem_min - 1].hh.rh != (-1073741824))
        print_nl(ctx, 368);
    }
    show_box(ctx, ctx->mem[ctx->nest[p].head_field - mem_min].hh.rh);
    switch (abs(m) / 101) {
    case 0:
      print_nl(ctx, 369);
      if (a.int_ <= (-65536000))
        print(ctx, 370);
      else
        print_scaled(ctx, a.int_);
      if (ctx->nest[p].pg_field) {
        print(ctx, 371);
        print_int(ctx, ctx->nest[p].pg_field);
        print(ctx, 372);
        if (ctx->nest[p].pg_field != 1)
          print_char(ctx, 115);
      }
      break;
    case 1:
      print_nl(ctx, 373);
      print_int(ctx, a.hh.lh);
      if (m > 0) {
        if (a.hh.rh > 0) {
          print(ctx, 374);
          print_int(ctx, a.hh.rh);
        }
      }
      break;
    case 2:
      if (a.int_ != (-1073741824)) {
        print(ctx, 375);
        show_box(ctx, a.int_);
      }
      break;
    }
  }
}

void print_param(ctex_t *ctx, integer n) {
  switch (n) {
  case 0:
    print_esc(ctx, 420);
    break;
  case 1:
    print_esc(ctx, 421);
    break;
  case 2:
    print_esc(ctx, 422);
    break;
  case 3:
    print_esc(ctx, 423);
    break;
  case 4:
    print_esc(ctx, 424);
    break;
  case 5:
    print_esc(ctx, 425);
    break;
  case 6:
    print_esc(ctx, 426);
    break;
  case 7:
    print_esc(ctx, 427);
    break;
  case 8:
    print_esc(ctx, 428);
    break;
  case 9:
    print_esc(ctx, 429);
    break;
  case 10:
    print_esc(ctx, 430);
    break;
  case 11:
    print_esc(ctx, 431);
    break;
  case 12:
    print_esc(ctx, 432);
    break;
  case 13:
    print_esc(ctx, 433);
    break;
  case 14:
    print_esc(ctx, 434);
    break;
  case 15:
    print_esc(ctx, 435);
    break;
  case 16:
    print_esc(ctx, 436);
    break;
  case 17:
    print_esc(ctx, 437);
    break;
  case 18:
    print_esc(ctx, 438);
    break;
  case 19:
    print_esc(ctx, 439);
    break;
  case 20:
    print_esc(ctx, 440);
    break;
  case 21:
    print_esc(ctx, 441);
    break;
  case 22:
    print_esc(ctx, 442);
    break;
  case 23:
    print_esc(ctx, 443);
    break;
  case 24:
    print_esc(ctx, 444);
    break;
  case 25:
    print_esc(ctx, 445);
    break;
  case 26:
    print_esc(ctx, 446);
    break;
  case 27:
    print_esc(ctx, 447);
    break;
  case 28:
    print_esc(ctx, 448);
    break;
  case 29:
    print_esc(ctx, 449);
    break;
  case 30:
    print_esc(ctx, 450);
    break;
  case 31:
    print_esc(ctx, 451);
    break;
  case 32:
    print_esc(ctx, 452);
    break;
  case 33:
    print_esc(ctx, 453);
    break;
  case 34:
    print_esc(ctx, 454);
    break;
  case 35:
    print_esc(ctx, 455);
    break;
  case 36:
    print_esc(ctx, 456);
    break;
  case 37:
    print_esc(ctx, 457);
    break;
  case 38:
    print_esc(ctx, 458);
    break;
  case 39:
    print_esc(ctx, 459);
    break;
  case 40:
    print_esc(ctx, 460);
    break;
  case 41:
    print_esc(ctx, 461);
    break;
  case 42:
    print_esc(ctx, 462);
    break;
  case 43:
    print_esc(ctx, 463);
    break;
  case 44:
    print_esc(ctx, 464);
    break;
  case 45:
    print_esc(ctx, 465);
    break;
  case 46:
    print_esc(ctx, 466);
    break;
  case 47:
    print_esc(ctx, 467);
    break;
  case 48:
    print_esc(ctx, 468);
    break;
  case 49:
    print_esc(ctx, 469);
    break;
  case 50:
    print_esc(ctx, 470);
    break;
  case 51:
    print_esc(ctx, 471);
    break;
  case 52:
    print_esc(ctx, 472);
    break;
  case 53:
    print_esc(ctx, 473);
    break;
  case 54:
    print_esc(ctx, 474);
    break;
  default:
    print(ctx, 475);
    break;
  }
}

void fix_date_and_time(ctex_t *ctx) {
  ctx->eqtb[12183].int_ = 720;
  ctx->eqtb[12184].int_ = 4;
  ctx->eqtb[12185].int_ = 7;
  ctx->eqtb[12186].int_ = 1776;
}

void begin_diagnostic(ctex_t *ctx) {
  ctx->old_setting = ctx->selector;
  if ((ctx->eqtb[12192].int_ > 0) || (ctx->selector != 19))
    return;
  --ctx->selector;
  if (!ctx->history)
    ctx->history = 1;
}

void end_diagnostic(ctex_t *ctx, bool_t blank_line) {
  print_nl(ctx, 338);
  if (blank_line)
    print_ln(ctx);
  ctx->selector = ctx->old_setting;
}

void print_length_param(ctex_t *ctx, integer n) {
  switch (n) {
  case 0:
    print_esc(ctx, 478);
    break;
  case 1:
    print_esc(ctx, 479);
    break;
  case 2:
    print_esc(ctx, 480);
    break;
  case 3:
    print_esc(ctx, 481);
    break;
  case 4:
    print_esc(ctx, 482);
    break;
  case 5:
    print_esc(ctx, 483);
    break;
  case 6:
    print_esc(ctx, 484);
    break;
  case 7:
    print_esc(ctx, 485);
    break;
  case 8:
    print_esc(ctx, 486);
    break;
  case 9:
    print_esc(ctx, 487);
    break;
  case 10:
    print_esc(ctx, 488);
    break;
  case 11:
    print_esc(ctx, 489);
    break;
  case 12:
    print_esc(ctx, 490);
    break;
  case 13:
    print_esc(ctx, 491);
    break;
  case 14:
    print_esc(ctx, 492);
    break;
  case 15:
    print_esc(ctx, 493);
    break;
  case 16:
    print_esc(ctx, 494);
    break;
  case 17:
    print_esc(ctx, 495);
    break;
  case 18:
    print_esc(ctx, 496);
    break;
  case 19:
    print_esc(ctx, 497);
    break;
  case 20:
    print_esc(ctx, 498);
    break;
  default:
    print(ctx, 499);
    break;
  }
}

void print_cmd_chr(ctex_t *ctx, quarterword cmd, halfword chr_code) {
  switch (cmd) {
  case 1:
    print(ctx, 557);
    print(ctx, chr_code);
    break;
  case 2:
    print(ctx, 558);
    print(ctx, chr_code);
    break;
  case 3:
    print(ctx, 559);
    print(ctx, chr_code);
    break;
  case 6:
    print(ctx, 560);
    print(ctx, chr_code);
    break;
  case 7:
    print(ctx, 561);
    print(ctx, chr_code);
    break;
  case 8:
    print(ctx, 562);
    print(ctx, chr_code);
    break;
  case 9:
    print(ctx, 563);
    break;
  case 10:
    print(ctx, 564);
    print(ctx, chr_code);
    break;
  case 11:
    print(ctx, 565);
    print(ctx, chr_code);
    break;
  case 12:
    print(ctx, 566);
    print(ctx, chr_code);
    break;
  case 75:
  case 76:
    if (chr_code < 9800) {
      print_skip_param(ctx, chr_code - 9782);
    } else if (chr_code < 10056) {
      print_esc(ctx, 395);
      print_int(ctx, chr_code - 9800);
    } else {
      print_esc(ctx, 396);
      print_int(ctx, chr_code - 10056);
    }
    break;
  case 72:
    if (chr_code >= 10322) {
      print_esc(ctx, 407);
      print_int(ctx, chr_code - 10322);
    } else {
      switch (chr_code) {
      case 10313:
        print_esc(ctx, 398);
        break;
      case 10314:
        print_esc(ctx, 399);
        break;
      case 10315:
        print_esc(ctx, 400);
        break;
      case 10316:
        print_esc(ctx, 401);
        break;
      case 10317:
        print_esc(ctx, 402);
        break;
      case 10318:
        print_esc(ctx, 403);
        break;
      case 10319:
        print_esc(ctx, 404);
        break;
      case 10320:
        print_esc(ctx, 405);
        break;
      default:
        print_esc(ctx, 406);
        break;
      }
    }
    break;
  case 73:
    if (chr_code < 12218) {
      print_param(ctx, chr_code - 12163);
    } else {
      print_esc(ctx, 476);
      print_int(ctx, chr_code - 12218);
    }
    break;
  case 74:
    if (chr_code < 12751) {
      print_length_param(ctx, chr_code - 12730);
    } else {
      print_esc(ctx, 500);
      print_int(ctx, chr_code - 12751);
    }
    break;
  case 45:
    print_esc(ctx, 508);
    break;
  case 90:
    print_esc(ctx, 509);
    break;
  case 40:
    print_esc(ctx, 510);
    break;
  case 41:
    print_esc(ctx, 511);
    break;
  case 77:
    print_esc(ctx, 519);
    break;
  case 61:
    print_esc(ctx, 512);
    break;
  case 42:
    print_esc(ctx, 531);
    break;
  case 16:
    print_esc(ctx, 513);
    break;
  case 107:
    print_esc(ctx, 504);
    break;
  case 88:
    print_esc(ctx, 518);
    break;
  case 15:
    print_esc(ctx, 514);
    break;
  case 92:
    print_esc(ctx, 515);
    break;
  case 67:
    print_esc(ctx, 505);
    break;
  case 62:
    print_esc(ctx, 516);
    break;
  case 64:
    print_esc(ctx, 32);
    break;
  case 102:
    print_esc(ctx, 517);
    break;
  case 32:
    print_esc(ctx, 520);
    break;
  case 36:
    print_esc(ctx, 521);
    break;
  case 39:
    print_esc(ctx, 522);
    break;
  case 37:
    print_esc(ctx, 330);
    break;
  case 44:
    print_esc(ctx, 47);
    break;
  case 18:
    print_esc(ctx, 351);
    break;
  case 46:
    print_esc(ctx, 523);
    break;
  case 17:
    print_esc(ctx, 524);
    break;
  case 54:
    print_esc(ctx, 525);
    break;
  case 91:
    print_esc(ctx, 526);
    break;
  case 34:
    print_esc(ctx, 527);
    break;
  case 65:
    print_esc(ctx, 528);
    break;
  case 103:
    print_esc(ctx, 529);
    break;
  case 55:
    print_esc(ctx, 335);
    break;
  case 63:
    print_esc(ctx, 530);
    break;
  case 66:
    print_esc(ctx, 533);
    break;
  case 96:
    print_esc(ctx, 534);
    break;
  case 0:
    print_esc(ctx, 535);
    break;
  case 98:
    print_esc(ctx, 536);
    break;
  case 80:
    print_esc(ctx, 532);
    break;
  case 84:
    print_esc(ctx, 408);
    break;
  case 109:
    print_esc(ctx, 537);
    break;
  case 71:
    print_esc(ctx, 407);
    break;
  case 38:
    print_esc(ctx, 352);
    break;
  case 33:
    print_esc(ctx, 538);
    break;
  case 56:
    print_esc(ctx, 539);
    break;
  case 35:
    print_esc(ctx, 540);
    break;
  case 13:
    print_esc(ctx, 597);
    break;
  case 104:
    if (!chr_code)
      print_esc(ctx, 629);
    else
      print_esc(ctx, 630);
    break;
  case 110:
    switch (chr_code) {
    case 1:
      print_esc(ctx, 632);
      break;
    case 2:
      print_esc(ctx, 633);
      break;
    case 3:
      print_esc(ctx, 634);
      break;
    case 4:
      print_esc(ctx, 635);
      break;
    default:
      print_esc(ctx, 631);
      break;
    }
    break;
  case 89:
    if (!chr_code) {
      print_esc(ctx, 476);
    } else if (chr_code == 1) {
      print_esc(ctx, 500);
    } else if (chr_code == 2)
      print_esc(ctx, 395);
    else
      print_esc(ctx, 396);
    break;
  case 79:
    if (chr_code == 1)
      print_esc(ctx, 669);
    else
      print_esc(ctx, 668);
    break;
  case 82:
    if (!chr_code)
      print_esc(ctx, 670);
    else
      print_esc(ctx, 671);
    break;
  case 83:
    if (chr_code == 1) {
      print_esc(ctx, 672);
    } else if (chr_code == 3)
      print_esc(ctx, 673);
    else
      print_esc(ctx, 674);
    break;
  case 70:
    switch (chr_code) {
    case 0:
      print_esc(ctx, 675);
      break;
    case 1:
      print_esc(ctx, 676);
      break;
    case 2:
      print_esc(ctx, 677);
      break;
    case 3:
      print_esc(ctx, 678);
      break;
    default:
      print_esc(ctx, 679);
      break;
    }
    break;
  case 108:
    switch (chr_code) {
    case 0:
      print_esc(ctx, 735);
      break;
    case 1:
      print_esc(ctx, 736);
      break;
    case 2:
      print_esc(ctx, 737);
      break;
    case 3:
      print_esc(ctx, 738);
      break;
    case 4:
      print_esc(ctx, 739);
      break;
    default:
      print_esc(ctx, 740);
      break;
    }
    break;
  case 105:
    switch (chr_code) {
    case 1:
      print_esc(ctx, 757);
      break;
    case 2:
      print_esc(ctx, 758);
      break;
    case 3:
      print_esc(ctx, 759);
      break;
    case 4:
      print_esc(ctx, 760);
      break;
    case 5:
      print_esc(ctx, 761);
      break;
    case 6:
      print_esc(ctx, 762);
      break;
    case 7:
      print_esc(ctx, 763);
      break;
    case 8:
      print_esc(ctx, 764);
      break;
    case 9:
      print_esc(ctx, 765);
      break;
    case 10:
      print_esc(ctx, 766);
      break;
    case 11:
      print_esc(ctx, 767);
      break;
    case 12:
      print_esc(ctx, 768);
      break;
    case 13:
      print_esc(ctx, 769);
      break;
    case 14:
      print_esc(ctx, 770);
      break;
    case 15:
      print_esc(ctx, 771);
      break;
    case 16:
      print_esc(ctx, 772);
      break;
    default:
      print_esc(ctx, 756);
      break;
    }
    break;
  case 106:
    if (chr_code == 2) {
      print_esc(ctx, 773);
    } else if (chr_code == 4)
      print_esc(ctx, 774);
    else
      print_esc(ctx, 775);
    break;
  case 4:
    if (chr_code == 256) {
      print_esc(ctx, 897);
    } else {
      print(ctx, 901);
      print(ctx, chr_code);
    }
    break;
  case 5:
    if (chr_code == 257)
      print_esc(ctx, 898);
    else
      print_esc(ctx, 899);
    break;
  case 81:
    switch (chr_code) {
    case 0:
      print_esc(ctx, 969);
      break;
    case 1:
      print_esc(ctx, 970);
      break;
    case 2:
      print_esc(ctx, 971);
      break;
    case 3:
      print_esc(ctx, 972);
      break;
    case 4:
      print_esc(ctx, 973);
      break;
    case 5:
      print_esc(ctx, 974);
      break;
    case 6:
      print_esc(ctx, 975);
      break;
    default:
      print_esc(ctx, 976);
      break;
    }
    break;
  case 14:
    if (chr_code == 1)
      print_esc(ctx, 1025);
    else
      print_esc(ctx, 1024);
    break;
  case 26:
    switch (chr_code) {
    case 4:
      print_esc(ctx, 1026);
      break;
    case 0:
      print_esc(ctx, 1027);
      break;
    case 1:
      print_esc(ctx, 1028);
      break;
    case 2:
      print_esc(ctx, 1029);
      break;
    default:
      print_esc(ctx, 1030);
      break;
    }
    break;
  case 27:
    switch (chr_code) {
    case 4:
      print_esc(ctx, 1031);
      break;
    case 0:
      print_esc(ctx, 1032);
      break;
    case 1:
      print_esc(ctx, 1033);
      break;
    case 2:
      print_esc(ctx, 1034);
      break;
    default:
      print_esc(ctx, 1035);
      break;
    }
    break;
  case 28:
    print_esc(ctx, 336);
    break;
  case 29:
    print_esc(ctx, 340);
    break;
  case 30:
    print_esc(ctx, 342);
    break;
  case 21:
    if (chr_code == 1)
      print_esc(ctx, 1053);
    else
      print_esc(ctx, 1054);
    break;
  case 22:
    if (chr_code == 1)
      print_esc(ctx, 1055);
    else
      print_esc(ctx, 1056);
    break;
  case 20:
    switch (chr_code) {
    case 0:
      print_esc(ctx, 409);
      break;
    case 1:
      print_esc(ctx, 1057);
      break;
    case 2:
      print_esc(ctx, 1058);
      break;
    case 3:
      print_esc(ctx, 964);
      break;
    case 4:
      print_esc(ctx, 1059);
      break;
    case 5:
      print_esc(ctx, 966);
      break;
    default:
      print_esc(ctx, 1060);
      break;
    }
    break;
  case 31:
    if (chr_code == 100) {
      print_esc(ctx, 1062);
    } else if (chr_code == 101) {
      print_esc(ctx, 1063);
    } else if (chr_code == 102)
      print_esc(ctx, 1064);
    else
      print_esc(ctx, 1061);
    break;
  case 43:
    if (!chr_code)
      print_esc(ctx, 1080);
    else
      print_esc(ctx, 1079);
    break;
  case 25:
    if (chr_code == 10) {
      print_esc(ctx, 1091);
    } else if (chr_code == 11)
      print_esc(ctx, 1090);
    else
      print_esc(ctx, 1089);
    break;
  case 23:
    if (chr_code == 1)
      print_esc(ctx, 1093);
    else
      print_esc(ctx, 1092);
    break;
  case 24:
    if (chr_code == 1)
      print_esc(ctx, 1095);
    else
      print_esc(ctx, 1094);
    break;
  case 47:
    if (chr_code == 1)
      print_esc(ctx, 45);
    else
      print_esc(ctx, 349);
    break;
  case 48:
    if (chr_code == 1)
      print_esc(ctx, 1127);
    else
      print_esc(ctx, 1126);
    break;
  case 50:
    switch (chr_code) {
    case 16:
      print_esc(ctx, 865);
      break;
    case 17:
      print_esc(ctx, 866);
      break;
    case 18:
      print_esc(ctx, 867);
      break;
    case 19:
      print_esc(ctx, 868);
      break;
    case 20:
      print_esc(ctx, 869);
      break;
    case 21:
      print_esc(ctx, 870);
      break;
    case 22:
      print_esc(ctx, 871);
      break;
    case 23:
      print_esc(ctx, 872);
      break;
    case 26:
      print_esc(ctx, 874);
      break;
    default:
      print_esc(ctx, 873);
      break;
    }
    break;
  case 51:
    if (chr_code == 1) {
      print_esc(ctx, 877);
    } else if (chr_code == 2)
      print_esc(ctx, 878);
    else
      print_esc(ctx, 1128);
    break;
  case 53:
    print_style(ctx, chr_code);
    break;
  case 52:
    switch (chr_code) {
    case 1:
      print_esc(ctx, 1147);
      break;
    case 2:
      print_esc(ctx, 1148);
      break;
    case 3:
      print_esc(ctx, 1149);
      break;
    case 4:
      print_esc(ctx, 1150);
      break;
    case 5:
      print_esc(ctx, 1151);
      break;
    default:
      print_esc(ctx, 1146);
      break;
    }
    break;
  case 49:
    if (chr_code == 30)
      print_esc(ctx, 875);
    else
      print_esc(ctx, 876);
    break;
  case 93:
    if (chr_code == 1) {
      print_esc(ctx, 1170);
    } else if (chr_code == 2)
      print_esc(ctx, 1171);
    else
      print_esc(ctx, 1172);
    break;
  case 97:
    if (!chr_code) {
      print_esc(ctx, 1173);
    } else if (chr_code == 1) {
      print_esc(ctx, 1174);
    } else if (chr_code == 2)
      print_esc(ctx, 1175);
    else
      print_esc(ctx, 1176);
    break;
  case 94:
    if (chr_code)
      print_esc(ctx, 1191);
    else
      print_esc(ctx, 1190);
    break;
  case 95:
    switch (chr_code) {
    case 0:
      print_esc(ctx, 1192);
      break;
    case 1:
      print_esc(ctx, 1193);
      break;
    case 2:
      print_esc(ctx, 1194);
      break;
    case 3:
      print_esc(ctx, 1195);
      break;
    case 4:
      print_esc(ctx, 1196);
      break;
    case 5:
      print_esc(ctx, 1197);
      break;
    default:
      print_esc(ctx, 1198);
      break;
    }
    break;
  case 68:
    print_esc(ctx, 513);
    print_hex(ctx, chr_code);
    break;
  case 69:
    print_esc(ctx, 524);
    print_hex(ctx, chr_code);
    break;
  case 85:
    if (chr_code == 10883) {
      print_esc(ctx, 415);
    } else if (chr_code == 11907) {
      print_esc(ctx, 419);
    } else if (chr_code == 11139) {
      print_esc(ctx, 416);
    } else if (chr_code == 11395) {
      print_esc(ctx, 417);
    } else if (chr_code == 11651)
      print_esc(ctx, 418);
    else
      print_esc(ctx, 477);
    break;
  case 86:
    print_size(ctx, chr_code - 10835);
    break;
  case 99:
    if (chr_code == 1)
      print_esc(ctx, 952);
    else
      print_esc(ctx, 940);
    break;
  case 78:
    if (!chr_code)
      print_esc(ctx, 1216);
    else
      print_esc(ctx, 1217);
    break;
  case 87:
    print(ctx, 1225);
    slow_print(ctx, ctx->fnt_infos.font_name[chr_code]);
    if (ctx->fnt_infos.font_size[chr_code] !=
        ctx->fnt_infos.font_dsize[chr_code]) {
      print(ctx, 741);
      print_scaled(ctx, ctx->fnt_infos.font_size[chr_code]);
      print(ctx, 397);
    }
    break;
  case 100:
    switch (chr_code) {
    case 0:
      print_esc(ctx, 274);
      break;
    case 1:
      print_esc(ctx, 275);
      break;
    case 2:
      print_esc(ctx, 276);
      break;
    default:
      print_esc(ctx, 1226);
      break;
    }
    break;
  case 60:
    if (!chr_code)
      print_esc(ctx, 1228);
    else
      print_esc(ctx, 1227);
    break;
  case 58:
    if (!chr_code)
      print_esc(ctx, 1229);
    else
      print_esc(ctx, 1230);
    break;
  case 57:
    if (chr_code == 11139)
      print_esc(ctx, 1236);
    else
      print_esc(ctx, 1237);
    break;
  case 19:
    switch (chr_code) {
    case 1:
      print_esc(ctx, 1239);
      break;
    case 2:
      print_esc(ctx, 1240);
      break;
    case 3:
      print_esc(ctx, 1241);
      break;
    default:
      print_esc(ctx, 1238);
      break;
    }
    break;
  case 101:
    print(ctx, 1248);
    break;
  case 111:
    print(ctx, 1249);
    break;
  case 112:
    print_esc(ctx, 1250);
    break;
  case 113:
    print_esc(ctx, 1251);
    break;
  case 114:
    print_esc(ctx, 1170);
    print_esc(ctx, 1251);
    break;
  case 115:
    print_esc(ctx, 1252);
    break;
  case 59:
    switch (chr_code) {
    case 0:
      print_esc(ctx, 1284);
      break;
    case 1:
      print_esc(ctx, 594);
      break;
    case 2:
      print_esc(ctx, 1285);
      break;
    case 3:
      print_esc(ctx, 1286);
      break;
    case 4:
      print_esc(ctx, 1287);
      break;
    case 5:
      print_esc(ctx, 1288);
      break;
    default:
      print(ctx, 1289);
      break;
    }
    break;
  default:
    print(ctx, 567);
    break;
  }
}

halfword id_lookup(ctex_t *ctx, integer j, integer l) {
  integer d;
  halfword p, k;
  integer h = ctx->buffer[j];
  for (k = j + 1; k <= (j + l - 1); ++k) {
    h += h + ctx->buffer[k];
    while (h >= 7649)
      h -= 7649;
  }
  p = h + 514;
  while (true) {
    if (ctx->hash[p - 514].rh > 0) {
      if (ctx->str_start[ctx->hash[p - 514].rh + 1] -
              ctx->str_start[ctx->hash[p - 514].rh] ==
          l) {
        if (str_eq_buf(ctx, ctx->hash[p - 514].rh, j))
          goto _L40;
      }
    }
    if (!ctx->hash[p - 514].lh) {
      if (ctx->no_new_control_sequence) {
        p = 9781;
      } else {
        if (ctx->hash[p - 514].rh > 0) {
          do {
            if (ctx->hash_used == 514)
              overflow(ctx, 503, 9000);
            --ctx->hash_used;
          } while (ctx->hash[ctx->hash_used - 514].rh);
          ctx->hash[p - 514].lh = ctx->hash_used;
          p = ctx->hash_used;
        }
        if (ctx->pool_ptr + l > pool_size)
          overflow(ctx, 257, pool_size - ctx->init_pool_ptr);
        d = ctx->pool_ptr - ctx->str_start[ctx->str_ptr];
        while (ctx->pool_ptr > ctx->str_start[ctx->str_ptr]) {
          --ctx->pool_ptr;
          ctx->str_pool[ctx->pool_ptr + l] = ctx->str_pool[ctx->pool_ptr];
        }
        for (k = j; k <= (j + l - 1); ++k) {
          ctx->str_pool[ctx->pool_ptr] = ctx->buffer[k];
          ++ctx->pool_ptr;
        }
        ctx->hash[p - 514].rh = make_string(ctx);
        ctx->pool_ptr += d;
      }
      goto _L40;
    }
    p = ctx->hash[p - 514].lh;
  }
_L40:
  return p;
}

void primitive(ctex_t *ctx, str_number s, quarterword c, halfword o) {
  pool_pointer k;
  small_number j, l;
  if (s < 256) {
    ctx->cur_val = s + 257;
  } else {
    k = ctx->str_start[s];
    l = ctx->str_start[s + 1] - k;
    for (j = 0; j <= (l - 1); ++j)
      ctx->buffer[j] = ctx->str_pool[k + j];
    ctx->cur_val = id_lookup(ctx, 0, l);
    --ctx->str_ptr;
    ctx->pool_ptr = ctx->str_start[ctx->str_ptr];
    ctx->hash[ctx->cur_val - 514].rh = s;
  }
  ctx->eqtb[ctx->cur_val].hh.U2.b1 = 1;
  ctx->eqtb[ctx->cur_val].hh.U2.b0 = c;
  ctx->eqtb[ctx->cur_val].hh.rh = o;
}

void new_save_level(ctex_t *ctx, group_code c) {
  if (ctx->save_ptr > ctx->max_save_stack) {
    ctx->max_save_stack = ctx->save_ptr;
    if (ctx->max_save_stack > (save_size - 6))
      overflow(ctx, 541, save_size);
  }
  ctx->save_stack[ctx->save_ptr].hh.U2.b0 = 3;
  ctx->save_stack[ctx->save_ptr].hh.U2.b1 = ctx->cur_group;
  ctx->save_stack[ctx->save_ptr].hh.rh = ctx->cur_boundary;
  if (ctx->cur_level == 65535)
    overflow(ctx, 542, 65535);
  ctx->cur_boundary = ctx->save_ptr;
  ++ctx->cur_level;
  ++ctx->save_ptr;
  ctx->cur_group = c;
}

void eq_destroy(ctex_t *ctx, memory_word w) {
  halfword q;
  switch (w.hh.U2.b0) {
  case 111:
  case 112:
  case 113:
  case 114:
    delete_token_ref(ctx, w.hh.rh);
    break;
  case 117:
    delete_glue_ref(ctx, w.hh.rh);
    break;
  case 118:
    q = w.hh.rh;
    if (q != (-1073741824))
      free_node(ctx, q,
                ctx->mem[q - mem_min].hh.lh + ctx->mem[q - mem_min].hh.lh + 1);
    break;
  case 119:
    flush_node_list(ctx, w.hh.rh);
    break;
  default:
    break;
  }
}

void eq_save(ctex_t *ctx, halfword p, quarterword l) {
  if (ctx->save_ptr > ctx->max_save_stack) {
    ctx->max_save_stack = ctx->save_ptr;
    if (ctx->max_save_stack > (save_size - 6))
      overflow(ctx, 541, save_size);
  }
  if (!l) {
    ctx->save_stack[ctx->save_ptr].hh.U2.b0 = 1;
  } else {
    ctx->save_stack[ctx->save_ptr] = ctx->eqtb[p];
    ++ctx->save_ptr;
    ctx->save_stack[ctx->save_ptr].hh.U2.b0 = 0;
  }
  ctx->save_stack[ctx->save_ptr].hh.U2.b1 = l;
  ctx->save_stack[ctx->save_ptr].hh.rh = p;
  ++ctx->save_ptr;
}

void eq_define(ctex_t *ctx, halfword p, quarterword t, halfword e) {
  if (ctx->eqtb[p].hh.U2.b1 == ctx->cur_level) {
    eq_destroy(ctx, ctx->eqtb[p]);
  } else if (ctx->cur_level > 1)
    eq_save(ctx, p, ctx->eqtb[p].hh.U2.b1);
  ctx->eqtb[p].hh.U2.b1 = ctx->cur_level;
  ctx->eqtb[p].hh.U2.b0 = t;
  ctx->eqtb[p].hh.rh = e;
}

void eq_word_define(ctex_t *ctx, halfword p, integer w) {
  if (ctx->xeq_level[p - 12163] != ctx->cur_level) {
    eq_save(ctx, p, ctx->xeq_level[p - 12163]);
    ctx->xeq_level[p - 12163] = ctx->cur_level;
  }
  ctx->eqtb[p].int_ = w;
}

void geq_define(ctex_t *ctx, halfword p, quarterword t, halfword e) {
  eq_destroy(ctx, ctx->eqtb[p]);
  ctx->eqtb[p].hh.U2.b1 = 1;
  ctx->eqtb[p].hh.U2.b0 = t;
  ctx->eqtb[p].hh.rh = e;
}

void geq_word_define(ctex_t *ctx, halfword p, integer w) {
  ctx->eqtb[p].int_ = w;
  ctx->xeq_level[p - 12163] = 1;
}

void save_for_after(ctex_t *ctx, halfword t) {
  if (ctx->cur_level <= 1)
    return;
  if (ctx->save_ptr > ctx->max_save_stack) {
    ctx->max_save_stack = ctx->save_ptr;
    if (ctx->max_save_stack > (save_size - 6))
      overflow(ctx, 541, save_size);
  }
  ctx->save_stack[ctx->save_ptr].hh.U2.b0 = 2;
  ctx->save_stack[ctx->save_ptr].hh.U2.b1 = 0;
  ctx->save_stack[ctx->save_ptr].hh.rh = t;
  ++ctx->save_ptr;
}

void unsave(ctex_t *ctx) {
  halfword p;
  quarterword l;
  halfword t;
  if (ctx->cur_level <= 1) {
    confusion(ctx, 543);
    return;
  }
  --ctx->cur_level;
  while (true) {
    --ctx->save_ptr;
    if (ctx->save_stack[ctx->save_ptr].hh.U2.b0 == 3)
      goto _L30;
    p = ctx->save_stack[ctx->save_ptr].hh.rh;
    if (ctx->save_stack[ctx->save_ptr].hh.U2.b0 == 2) {
      t = ctx->cur_tok;
      ctx->cur_tok = p;
      back_input(ctx);
      ctx->cur_tok = t;
      continue;
    }
    if (!ctx->save_stack[ctx->save_ptr].hh.U2.b0) {
      l = ctx->save_stack[ctx->save_ptr].hh.U2.b1;
      --ctx->save_ptr;
    } else {
      ctx->save_stack[ctx->save_ptr] = ctx->eqtb[9781];
    }
    if (p < 12163) {
      if (ctx->eqtb[p].hh.U2.b1 == 1) {
        eq_destroy(ctx, ctx->save_stack[ctx->save_ptr]);
      } else {
        eq_destroy(ctx, ctx->eqtb[p]);
        ctx->eqtb[p] = ctx->save_stack[ctx->save_ptr];
      }
    } else if (ctx->xeq_level[p - 12163] != 1) {
      ctx->eqtb[p] = ctx->save_stack[ctx->save_ptr];
      ctx->xeq_level[p - 12163] = l;
    }
  }
_L30:
  ctx->cur_group = ctx->save_stack[ctx->save_ptr].hh.U2.b1;
  ctx->cur_boundary = ctx->save_stack[ctx->save_ptr].hh.rh;
}

void prepare_mag(ctex_t *ctx) {
  if ((ctx->mag_set > 0) && (ctx->eqtb[12180].int_ != ctx->mag_set)) {
    print_nl(ctx, 262);
    print(ctx, 547);
    print_int(ctx, ctx->eqtb[12180].int_);
    print(ctx, 548);
    print_nl(ctx, 549);
    ctx->help_ptr = 2;
    ctx->help_line[1] = 550;
    ctx->help_line[0] = 551;
    int_error(ctx, ctx->mag_set);
    geq_word_define(ctx, 12180, ctx->mag_set);
  }
  if ((ctx->eqtb[12180].int_ <= 0) || (ctx->eqtb[12180].int_ > 32768)) {
    print_nl(ctx, 262);
    print(ctx, 552);
    ctx->help_ptr = 1;
    ctx->help_line[0] = 553;
    int_error(ctx, ctx->eqtb[12180].int_);
    geq_word_define(ctx, 12180, 1000);
  }
  ctx->mag_set = ctx->eqtb[12180].int_;
}

void token_show(ctex_t *ctx, halfword p) {
  if (p != (-1073741824))
    show_token_list(ctx, ctx->mem[p - mem_min].hh.rh, -1073741824, 10000000);
}

void print_meaning(ctex_t *ctx) {
  print_cmd_chr(ctx, ctx->cur_cmd, ctx->cur_chr);
  if (ctx->cur_cmd >= 111) {
    print_char(ctx, 58);
    print_ln(ctx);
    token_show(ctx, ctx->cur_chr);
    return;
  }
  if (ctx->cur_cmd != 110)
    return;
  print_char(ctx, 58);
  print_ln(ctx);
  token_show(ctx, ctx->cur_mark[ctx->cur_chr]);
}

void show_cur_cmd_chr(ctex_t *ctx) {
  begin_diagnostic(ctx);
  print_nl(ctx, 123);
  if (ctx->cur_list.mode_field != ctx->shown_mode) {
    print_mode(ctx, ctx->cur_list.mode_field);
    print(ctx, 568);
    ctx->shown_mode = ctx->cur_list.mode_field;
  }
  print_cmd_chr(ctx, ctx->cur_cmd, ctx->cur_chr);
  print_char(ctx, 125);
  end_diagnostic(ctx, false);
}

void show_context(ctex_t *ctx) {
  char old_setting;
  integer nn = -1, m, p, q;
  bool_t bottom_line = false;
  int i, j, l, n, N1;
  ctx->base_ptr = ctx->input_ptr;
  ctx->input_stack[ctx->base_ptr] = ctx->cur_input;
  while (true) {
    ctx->cur_input = ctx->input_stack[ctx->base_ptr];
    if (ctx->cur_input.state_field) {
      if ((ctx->cur_input.name_field > 17) || (!ctx->base_ptr))
        bottom_line = true;
    }
    if ((ctx->base_ptr == ctx->input_ptr) || bottom_line ||
        (nn < ctx->eqtb[12217].int_)) {
      if ((ctx->base_ptr == ctx->input_ptr) || ctx->cur_input.state_field ||
          (ctx->cur_input.index_field != 3) ||
          (ctx->cur_input.loc_field != (-1073741824))) {
        ctx->tally = 0;
        old_setting = ctx->selector;
        if (ctx->cur_input.state_field) {
          if (ctx->cur_input.name_field <= 17) {
            if (!ctx->cur_input.name_field) {
              if (!ctx->base_ptr)
                print_nl(ctx, 574);
              else
                print_nl(ctx, 575);
            } else {
              print_nl(ctx, 576);
              if (ctx->cur_input.name_field == 17)
                print_char(ctx, 42);
              else
                print_int(ctx, ctx->cur_input.name_field - 1);
              print_char(ctx, 62);
            }
          } else {
            print_nl(ctx, 577);
            print_int(ctx, ctx->line);
          }
          print_char(ctx, 32);
          l = ctx->tally;
          ctx->tally = 0;
          ctx->selector = 20;
          ctx->trick_count = 1000000;
          if (ctx->buffer[ctx->cur_input.limit_field] == ctx->eqtb[12211].int_)
            j = ctx->cur_input.limit_field;
          else
            j = ctx->cur_input.limit_field + 1;
          if (j > 0) {
            for (i = ctx->cur_input.start_field; i <= (j - 1); ++i) {
              if (i == ctx->cur_input.loc_field) {
                ctx->first_count = ctx->tally;
                ctx->trick_count =
                    ctx->tally + error_line - half_error_line + 1;
                if (ctx->trick_count < error_line)
                  ctx->trick_count = error_line;
              }
              print(ctx, ctx->buffer[i]);
            }
          }
        } else {
          switch (ctx->cur_input.index_field) {
          case 0:
            print_nl(ctx, 578);
            break;
          case 1:
          case 2:
            print_nl(ctx, 579);
            break;
          case 3:
            if (ctx->cur_input.loc_field == (-1073741824))
              print_nl(ctx, 580);
            else
              print_nl(ctx, 581);
            break;
          case 4:
            print_nl(ctx, 582);
            break;
          case 5:
            print_ln(ctx);
            print_cs(ctx, ctx->cur_input.name_field);
            break;
          case 6:
            print_nl(ctx, 583);
            break;
          case 7:
            print_nl(ctx, 584);
            break;
          case 8:
            print_nl(ctx, 585);
            break;
          case 9:
            print_nl(ctx, 586);
            break;
          case 10:
            print_nl(ctx, 587);
            break;
          case 11:
            print_nl(ctx, 588);
            break;
          case 12:
            print_nl(ctx, 589);
            break;
          case 13:
            print_nl(ctx, 590);
            break;
          case 14:
            print_nl(ctx, 591);
            break;
          case 15:
            print_nl(ctx, 592);
            break;
          default:
            print_nl(ctx, 63);
            break;
          }
          l = ctx->tally;
          ctx->tally = 0;
          ctx->selector = 20;
          ctx->trick_count = 1000000;
          if (ctx->cur_input.index_field < 5)
            show_token_list(ctx, ctx->cur_input.start_field,
                            ctx->cur_input.loc_field, 100000);
          else
            show_token_list(
                ctx, ctx->mem[ctx->cur_input.start_field - mem_min].hh.rh,
                ctx->cur_input.loc_field, 100000);
        }
        ctx->selector = old_setting;
        if (ctx->trick_count == 1000000) {
          ctx->first_count = ctx->tally;
          ctx->trick_count = ctx->tally + error_line - half_error_line + 1;
          if (ctx->trick_count < error_line)
            ctx->trick_count = error_line;
        }
        if (ctx->tally < ctx->trick_count)
          m = ctx->tally - ctx->first_count;
        else
          m = ctx->trick_count - ctx->first_count;
        if (l + ctx->first_count <= half_error_line) {
          p = 0;
          n = l + ctx->first_count;
        } else {
          print(ctx, 277);
          p = l + ctx->first_count - half_error_line + 3;
          n = half_error_line;
        }
        for (N1 = ctx->first_count, q = p; q < N1; ++q)
          print_char(ctx, ctx->trick_buf[q % error_line]);
        print_ln(ctx);
        for (q = 1; q <= n; ++q)
          print_char(ctx, 32);
        if (m + n <= error_line)
          p = ctx->first_count + m;
        else
          p = ctx->first_count + error_line - n - 3;
        for (q = ctx->first_count; q < p; ++q)
          print_char(ctx, ctx->trick_buf[q % error_line]);
        if (m + n > error_line)
          print(ctx, 277);
        ++nn;
      }
    } else if (nn == ctx->eqtb[12217].int_) {
      print_nl(ctx, 277);
      ++nn;
    }
    if (bottom_line)
      goto _L30;
    --ctx->base_ptr;
  }
_L30:
  ctx->cur_input = ctx->input_stack[ctx->input_ptr];
}

void begin_token_list(ctex_t *ctx, halfword p, quarterword t) {
  if (ctx->input_ptr > ctx->max_in_stack) {
    ctx->max_in_stack = ctx->input_ptr;
    if (ctx->input_ptr == stack_size)
      overflow(ctx, 593, stack_size);
  }
  ctx->input_stack[ctx->input_ptr] = ctx->cur_input;
  ++ctx->input_ptr;
  ctx->cur_input.state_field = 0;
  ctx->cur_input.start_field = p;
  ctx->cur_input.index_field = t;
  if (t < 5) {
    ctx->cur_input.loc_field = p;
    return;
  }
  ++ctx->mem[p - mem_min].hh.lh;
  if (t == 5) {
    ctx->cur_input.limit_field = ctx->param_ptr;
    return;
  }
  ctx->cur_input.loc_field = ctx->mem[p - mem_min].hh.rh;
  if (ctx->eqtb[12193].int_ <= 1)
    return;
  begin_diagnostic(ctx);
  print_nl(ctx, 338);
  switch (t) {
  case 14:
    print_esc(ctx, 351);
    break;
  case 15:
    print_esc(ctx, 594);
    break;
  default:
    print_cmd_chr(ctx, 72, t + 10307);
    break;
  }
  print(ctx, 556);
  token_show(ctx, p);
  end_diagnostic(ctx, false);
}

void end_token_list(ctex_t *ctx) {
  if (ctx->cur_input.index_field >= 3) {
    if (ctx->cur_input.index_field <= 4) {
      flush_list(ctx, ctx->cur_input.start_field);
    } else {
      delete_token_ref(ctx, ctx->cur_input.start_field);
      if (ctx->cur_input.index_field == 5) {
        while (ctx->param_ptr > ctx->cur_input.limit_field) {
          --ctx->param_ptr;
          flush_list(ctx, ctx->param_stack[ctx->param_ptr]);
        }
      }
    }
  } else if (ctx->cur_input.index_field == 1) {
    if (ctx->align_state > 500000)
      ctx->align_state = 0;
    else
      fatal_error(ctx, 595);
  }
  --ctx->input_ptr;
  ctx->cur_input = ctx->input_stack[ctx->input_ptr];
  if (ctx->interrupt)
    pause_for_instructions(ctx);
}

void back_input(ctex_t *ctx) {
  halfword p;
  while ((!ctx->cur_input.state_field) &&
         (ctx->cur_input.loc_field == (-1073741824)) &&
         (ctx->cur_input.index_field != 2))
    end_token_list(ctx);
  p = get_avail(ctx);
  ctx->mem[p - mem_min].hh.lh = ctx->cur_tok;
  if (ctx->cur_tok < 768) {
    if (ctx->cur_tok < 512)
      --ctx->align_state;
    else
      ++ctx->align_state;
  }
  if (ctx->input_ptr > ctx->max_in_stack) {
    ctx->max_in_stack = ctx->input_ptr;
    if (ctx->input_ptr == stack_size)
      overflow(ctx, 593, stack_size);
  }
  ctx->input_stack[ctx->input_ptr] = ctx->cur_input;
  ++ctx->input_ptr;
  ctx->cur_input.state_field = 0;
  ctx->cur_input.start_field = p;
  ctx->cur_input.index_field = 3;
  ctx->cur_input.loc_field = p;
}

void back_error(ctex_t *ctx) {
  ctx->OK_to_interrupt = false;
  back_input(ctx);
  ctx->OK_to_interrupt = true;
  error(ctx);
}

void ins_error(ctex_t *ctx) {
  ctx->OK_to_interrupt = false;
  back_input(ctx);
  ctx->cur_input.index_field = 4;
  ctx->OK_to_interrupt = true;
  error(ctx);
}

void begin_file_reading(ctex_t *ctx) {
  if (ctx->in_open == max_in_open)
    overflow(ctx, 596, max_in_open);
  if (ctx->first == buf_size)
    overflow(ctx, 256, buf_size);
  ++ctx->in_open;
  if (ctx->input_ptr > ctx->max_in_stack) {
    ctx->max_in_stack = ctx->input_ptr;
    if (ctx->input_ptr == stack_size)
      overflow(ctx, 593, stack_size);
  }
  ctx->input_stack[ctx->input_ptr] = ctx->cur_input;
  ++ctx->input_ptr;
  ctx->cur_input.index_field = ctx->in_open;
  ctx->line_stack[ctx->cur_input.index_field] = ctx->line;
  ctx->cur_input.start_field = ctx->first;
  ctx->cur_input.state_field = 1;
  ctx->cur_input.name_field = 0;
}

void end_file_reading(ctex_t *ctx) {
  ctx->first = ctx->cur_input.start_field;
  ctx->line = ctx->line_stack[ctx->cur_input.index_field];
  if (ctx->cur_input.name_field > 17)
    a_close(ctx, &ctx->input_file[ctx->cur_input.index_field]);
  --ctx->input_ptr;
  ctx->cur_input = ctx->input_stack[ctx->input_ptr];
  --ctx->in_open;
}

void clear_for_error_prompt(ctex_t *ctx) {
  while (ctx->cur_input.state_field && (!ctx->cur_input.name_field) &&
         (ctx->input_ptr > 0) &&
         (ctx->cur_input.loc_field > ctx->cur_input.limit_field))
    end_file_reading(ctx);
  print_ln(ctx);
  break_in(ctx->term_in, true);
}

void check_outer_validity(ctex_t *ctx) {
  halfword p, q;
  if (!ctx->scanner_status)
    return;
  ctx->deletions_allowed = false;
  if (ctx->cur_cs) {
    if ((!ctx->cur_input.state_field) || (ctx->cur_input.name_field < 1) ||
        (ctx->cur_input.name_field > 17)) {
      p = get_avail(ctx);
      ctx->mem[p - mem_min].hh.lh = ctx->cur_cs + 4095;
      begin_token_list(ctx, p, 3);
    }
    ctx->cur_cmd = 10;
    ctx->cur_chr = 32;
  }
  if (ctx->scanner_status > 1) {
    runaway(ctx);
    if (!ctx->cur_cs) {
      print_nl(ctx, 262);
      print(ctx, 604);
    } else {
      ctx->cur_cs = 0;
      print_nl(ctx, 262);
      print(ctx, 605);
    }
    print(ctx, 606);
    p = get_avail(ctx);
    switch (ctx->scanner_status) {
    case 2:
      print(ctx, 570);
      ctx->mem[p - mem_min].hh.lh = 637;
      break;
    case 3:
      print(ctx, 612);
      ctx->mem[p - mem_min].hh.lh = ctx->par_token;
      ctx->long_state = 113;
      break;
    case 4:
      print(ctx, 572);
      ctx->mem[p - mem_min].hh.lh = 637;
      q = p;
      p = get_avail(ctx);
      ctx->mem[p - mem_min].hh.rh = q;
      ctx->mem[p - mem_min].hh.lh = 13610;
      ctx->align_state = -1000000;
      break;
    case 5:
      print(ctx, 573);
      ctx->mem[p - mem_min].hh.lh = 637;
      break;
    }
    begin_token_list(ctx, p, 4);
    print(ctx, 607);
    sprint_cs(ctx, ctx->warning_index);
    ctx->help_ptr = 4;
    ctx->help_line[3] = 608;
    ctx->help_line[2] = 609;
    ctx->help_line[1] = 610;
    ctx->help_line[0] = 611;
    error(ctx);
  } else {
    print_nl(ctx, 262);
    print(ctx, 598);
    print_cmd_chr(ctx, 105, ctx->cur_if);
    print(ctx, 599);
    print_int(ctx, ctx->skip_line);
    ctx->help_ptr = 3;
    ctx->help_line[2] = 600;
    ctx->help_line[1] = 601;
    ctx->help_line[0] = 602;
    if (ctx->cur_cs)
      ctx->cur_cs = 0;
    else
      ctx->help_line[2] = 603;
    ctx->cur_tok = 13613;
    ins_error(ctx);
  }
  ctx->deletions_allowed = true;
}

void get_next(ctex_t *ctx) {
  int k;
  halfword t;
  char cat;
  ASCII_code c, cc;
  char d;
_L20:
  ctx->cur_cs = 0;
  if (ctx->cur_input.state_field) {
  _L25:
    if (ctx->cur_input.loc_field > ctx->cur_input.limit_field) {
      ctx->cur_input.state_field = 33;
      if (ctx->cur_input.name_field > 17) {
        ++ctx->line;
        ctx->first = ctx->cur_input.start_field;
        if (!ctx->force_eof) {
          if (input_ln(ctx, ctx->input_file[ctx->cur_input.index_field], true))
            firm_up_the_line(ctx);
          else
            ctx->force_eof = true;
        }
        if (ctx->force_eof) {
          print_char(ctx, 41);
          --ctx->open_parens;
          fflush(ctx->term_out);
          errno = 0;
          ctx->force_eof = false;
          end_file_reading(ctx);
          check_outer_validity(ctx);
          goto _L20;
        }
        if (((unsigned)ctx->eqtb[12211].int_) > 255)
          --ctx->cur_input.limit_field;
        else
          ctx->buffer[ctx->cur_input.limit_field] = ctx->eqtb[12211].int_;
        ctx->first = ctx->cur_input.limit_field + 1;
        ctx->cur_input.loc_field = ctx->cur_input.start_field;
      } else {
        if (ctx->cur_input.name_field) {
          ctx->cur_cmd = 0;
          ctx->cur_chr = 0;
          goto _L10;
        }
        if (ctx->input_ptr > 0) {
          end_file_reading(ctx);
          goto _L20;
        }
        if (ctx->selector < 18)
          open_log_file(ctx);
        if (ctx->interaction > 1) {
          if (((unsigned)ctx->eqtb[12211].int_) > 255)
            ++ctx->cur_input.limit_field;
          if (ctx->cur_input.limit_field == ctx->cur_input.start_field)
            print_nl(ctx, 616);
          print_ln(ctx);
          ctx->first = ctx->cur_input.start_field;
          print(ctx, 42);
          term_input(ctx);
          ctx->cur_input.limit_field = ctx->last;
          if (((unsigned)ctx->eqtb[12211].int_) > 255)
            --ctx->cur_input.limit_field;
          else
            ctx->buffer[ctx->cur_input.limit_field] = ctx->eqtb[12211].int_;
          ctx->first = ctx->cur_input.limit_field + 1;
          ctx->cur_input.loc_field = ctx->cur_input.start_field;
        } else {
          fatal_error(ctx, 617);
        }
      }
      if (ctx->interrupt)
        pause_for_instructions(ctx);
      goto _L25;
    }
    ctx->cur_chr = ctx->buffer[ctx->cur_input.loc_field];
    ++ctx->cur_input.loc_field;
  _L21:
    ctx->cur_cmd = ctx->eqtb[ctx->cur_chr + 10883].hh.rh;
    switch (ctx->cur_input.state_field + ctx->cur_cmd) {
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
      if (ctx->cur_input.loc_field > ctx->cur_input.limit_field) {
        ctx->cur_cs = 513;
      } else {
      _L26:
        k = ctx->cur_input.loc_field;
        ctx->cur_chr = ctx->buffer[k];
        cat = ctx->eqtb[ctx->cur_chr + 10883].hh.rh;
        ++k;
        if (cat == 11) {
          ctx->cur_input.state_field = 17;
        } else if (cat == 10)
          ctx->cur_input.state_field = 17;
        else
          ctx->cur_input.state_field = 1;
        if ((cat == 11) && (k <= ctx->cur_input.limit_field)) {
          do {
            ctx->cur_chr = ctx->buffer[k];
            cat = ctx->eqtb[ctx->cur_chr + 10883].hh.rh;
            ++k;
          } while ((cat == 11) && (k <= ctx->cur_input.limit_field));
          if (ctx->buffer[k] == ctx->cur_chr) {
            if (cat == 7) {
              if (k < ctx->cur_input.limit_field) {
                c = ctx->buffer[k + 1];
                if (c < 128) {
                  d = 2;
                  if (((c >= 48) && (c <= 57)) || ((c >= 97) && (c <= 102))) {
                    if (k + 2 <= ctx->cur_input.limit_field) {
                      cc = ctx->buffer[k + 2];
                      if (((cc >= 48) && (cc <= 57)) ||
                          ((cc >= 97) && (cc <= 102)))
                        ++d;
                    }
                  }
                  if (d > 2) {
                    if (c <= 57)
                      ctx->cur_chr = c - 48;
                    else
                      ctx->cur_chr = c - 87;
                    if (cc <= 57)
                      ctx->cur_chr = (ctx->cur_chr * 16) + cc - 48;
                    else
                      ctx->cur_chr = (ctx->cur_chr * 16) + cc - 87;
                    ctx->buffer[k - 1] = ctx->cur_chr;
                  } else if (c < 64)
                    ctx->buffer[k - 1] = c + 64;
                  else
                    ctx->buffer[k - 1] = c - 64;
                  ctx->cur_input.limit_field -= d;
                  ctx->first -= d;
                  while (k <= ctx->cur_input.limit_field) {
                    ctx->buffer[k] = ctx->buffer[k + d];
                    ++k;
                  }
                  goto _L26;
                }
              }
            }
          }
          if (cat != 11)
            --k;
          if (k > (ctx->cur_input.loc_field + 1)) {
            ctx->cur_cs = id_lookup(ctx, ctx->cur_input.loc_field,
                                    k - ctx->cur_input.loc_field);
            ctx->cur_input.loc_field = k;
            goto _L40;
          }
        } else if (ctx->buffer[k] == ctx->cur_chr) {
          if (cat == 7) {
            if (k < ctx->cur_input.limit_field) {
              c = ctx->buffer[k + 1];
              if (c < 128) {
                d = 2;
                if (((c >= 48) && (c <= 57)) || ((c >= 97) && (c <= 102))) {
                  if (k + 2 <= ctx->cur_input.limit_field) {
                    cc = ctx->buffer[k + 2];
                    if (((cc >= 48) && (cc <= 57)) ||
                        ((cc >= 97) && (cc <= 102)))
                      ++d;
                  }
                }
                if (d > 2) {
                  if (c <= 57)
                    ctx->cur_chr = c - 48;
                  else
                    ctx->cur_chr = c - 87;
                  if (cc <= 57)
                    ctx->cur_chr = (ctx->cur_chr * 16) + cc - 48;
                  else
                    ctx->cur_chr = (ctx->cur_chr * 16) + cc - 87;
                  ctx->buffer[k - 1] = ctx->cur_chr;
                } else if (c < 64)
                  ctx->buffer[k - 1] = c + 64;
                else
                  ctx->buffer[k - 1] = c - 64;
                ctx->cur_input.limit_field -= d;
                ctx->first -= d;
                while (k <= ctx->cur_input.limit_field) {
                  ctx->buffer[k] = ctx->buffer[k + d];
                  ++k;
                }
                goto _L26;
              }
            }
          }
        }
        ctx->cur_cs = ctx->buffer[ctx->cur_input.loc_field] + 257;
        ++ctx->cur_input.loc_field;
      }
    _L40:
      ctx->cur_cmd = ctx->eqtb[ctx->cur_cs].hh.U2.b0;
      ctx->cur_chr = ctx->eqtb[ctx->cur_cs].hh.rh;
      if (ctx->cur_cmd >= 113)
        check_outer_validity(ctx);
      break;
    case 14:
    case 30:
    case 46:
      ctx->cur_cs = ctx->cur_chr + 1;
      ctx->cur_cmd = ctx->eqtb[ctx->cur_cs].hh.U2.b0;
      ctx->cur_chr = ctx->eqtb[ctx->cur_cs].hh.rh;
      ctx->cur_input.state_field = 1;
      if (ctx->cur_cmd >= 113)
        check_outer_validity(ctx);
      break;
    case 8:
    case 24:
    case 40:
      if (ctx->cur_chr == ctx->buffer[ctx->cur_input.loc_field]) {
        if (ctx->cur_input.loc_field < ctx->cur_input.limit_field) {
          c = ctx->buffer[ctx->cur_input.loc_field + 1];
          if (c < 128) {
            ctx->cur_input.loc_field += 2;
            if (((c >= 48) && (c <= 57)) || ((c >= 97) && (c <= 102))) {
              if (ctx->cur_input.loc_field <= ctx->cur_input.limit_field) {
                cc = ctx->buffer[ctx->cur_input.loc_field];
                if (((cc >= 48) && (cc <= 57)) || ((cc >= 97) && (cc <= 102))) {
                  ++ctx->cur_input.loc_field;
                  if (c <= 57)
                    ctx->cur_chr = c - 48;
                  else
                    ctx->cur_chr = c - 87;
                  if (cc <= 57)
                    ctx->cur_chr = (ctx->cur_chr * 16) + cc - 48;
                  else
                    ctx->cur_chr = (ctx->cur_chr * 16) + cc - 87;
                  goto _L21;
                }
              }
            }
            if (c < 64)
              ctx->cur_chr = c + 64;
            else
              ctx->cur_chr = c - 64;
            goto _L21;
          }
        }
      }
      ctx->cur_input.state_field = 1;
      break;
    case 16:
    case 32:
    case 48:
      print_nl(ctx, 262);
      print(ctx, 613);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 614;
      ctx->help_line[0] = 615;
      ctx->deletions_allowed = false;
      error(ctx);
      ctx->deletions_allowed = true;
      goto _L20;
      break;
    case 11:
      ctx->cur_input.state_field = 17;
      ctx->cur_chr = 32;
      break;
    case 6:
      ctx->cur_input.loc_field = ctx->cur_input.limit_field + 1;
      ctx->cur_cmd = 10;
      ctx->cur_chr = 32;
      break;
    case 22:
    case 15:
    case 31:
    case 47:
      ctx->cur_input.loc_field = ctx->cur_input.limit_field + 1;
      goto _L25;
      break;
    case 38:
      ctx->cur_input.loc_field = ctx->cur_input.limit_field + 1;
      ctx->cur_cs = ctx->par_loc;
      ctx->cur_cmd = ctx->eqtb[ctx->cur_cs].hh.U2.b0;
      ctx->cur_chr = ctx->eqtb[ctx->cur_cs].hh.rh;
      if (ctx->cur_cmd >= 113)
        check_outer_validity(ctx);
      break;
    case 2:
      ++ctx->align_state;
      break;
    case 18:
    case 34:
      ctx->cur_input.state_field = 1;
      ++ctx->align_state;
      break;
    case 3:
      --ctx->align_state;
      break;
    case 19:
    case 35:
      ctx->cur_input.state_field = 1;
      --ctx->align_state;
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
      ctx->cur_input.state_field = 1;
      break;
    default:
      break;
    }
  } else if (ctx->cur_input.loc_field != (-1073741824)) {
    t = ctx->mem[ctx->cur_input.loc_field - mem_min].hh.lh;
    ctx->cur_input.loc_field =
        ctx->mem[ctx->cur_input.loc_field - mem_min].hh.rh;
    if (t >= 4095) {
      ctx->cur_cs = t - 4095;
      ctx->cur_cmd = ctx->eqtb[ctx->cur_cs].hh.U2.b0;
      ctx->cur_chr = ctx->eqtb[ctx->cur_cs].hh.rh;
      if (ctx->cur_cmd >= 113) {
        if (ctx->cur_cmd == 116) {
          ctx->cur_cs =
              ctx->mem[ctx->cur_input.loc_field - mem_min].hh.lh - 4095;
          ctx->cur_input.loc_field = -1073741824;
          ctx->cur_cmd = ctx->eqtb[ctx->cur_cs].hh.U2.b0;
          ctx->cur_chr = ctx->eqtb[ctx->cur_cs].hh.rh;
          if (ctx->cur_cmd > 100) {
            ctx->cur_cmd = 0;
            ctx->cur_chr = 257;
          }
        } else {
          check_outer_validity(ctx);
        }
      }
    } else {
      ctx->cur_cmd = t / 256;
      ctx->cur_chr = t & 255;
      switch (ctx->cur_cmd) {
      case 1:
        ++ctx->align_state;
        break;
      case 2:
        --ctx->align_state;
        break;
      case 5:
        begin_token_list(
            ctx,
            ctx->param_stack[ctx->cur_input.limit_field + ctx->cur_chr - 1], 0);
        goto _L20;
        break;
      default:
        break;
      }
    }
  } else {
    end_token_list(ctx);
    goto _L20;
  }
  if (ctx->cur_cmd <= 5) {
    if (ctx->cur_cmd >= 4) {
      if (!ctx->align_state) {
        if ((ctx->scanner_status == 4) || (ctx->cur_align == (-1073741824)))
          fatal_error(ctx, 595);
        ctx->cur_cmd = ctx->mem[ctx->cur_align - mem_min + 5].hh.lh;
        ctx->mem[ctx->cur_align - mem_min + 5].hh.lh = ctx->cur_chr;
        if (ctx->cur_cmd == 63)
          begin_token_list(ctx, mem_max - 10, 2);
        else
          begin_token_list(ctx, ctx->mem[ctx->cur_align - mem_min + 2].int_, 2);
        ctx->align_state = 1000000;
        goto _L20;
      }
    }
  }
_L10:;
}

void firm_up_the_line(ctex_t *ctx) {
  int k, N;
  ctx->cur_input.limit_field = ctx->last;
  if (ctx->eqtb[12191].int_ <= 0)
    return;
  if (ctx->interaction <= 1)
    return;
  print_ln(ctx);
  if (ctx->cur_input.start_field < ctx->cur_input.limit_field) {
    for (N = ctx->cur_input.limit_field, k = ctx->cur_input.start_field;
         k <= (N - 1); ++k)
      print(ctx, ctx->buffer[k]);
  }
  ctx->first = ctx->cur_input.limit_field;
  print(ctx, 618);
  term_input(ctx);
  if (ctx->last <= ctx->first)
    return;
  for (N = ctx->last, k = ctx->first; k <= (N - 1); ++k)
    ctx->buffer[k + ctx->cur_input.start_field - ctx->first] = ctx->buffer[k];
  ctx->cur_input.limit_field =
      ctx->cur_input.start_field + ctx->last - ctx->first;
}

void get_token(ctex_t *ctx) {
  ctx->no_new_control_sequence = false;
  get_next(ctx);
  ctx->no_new_control_sequence = true;
  if (!ctx->cur_cs)
    ctx->cur_tok = (ctx->cur_cmd * 256) + ctx->cur_chr;
  else
    ctx->cur_tok = ctx->cur_cs + 4095;
}

void macro_call(ctex_t *ctx) {
  halfword r, p, q, s, t, u, v, rbrace_ptr;
  small_number n = 0;
  halfword unbalance, m, ref_count;
  ASCII_code match_chr;
  small_number save_scanner_status = ctx->scanner_status;
  halfword save_warning_index = ctx->warning_index;
  ctx->warning_index = ctx->cur_cs;
  ref_count = ctx->cur_chr;
  r = ctx->mem[ref_count - mem_min].hh.rh;
  if (ctx->eqtb[12193].int_ > 0) {
    begin_diagnostic(ctx);
    print_ln(ctx);
    print_cs(ctx, ctx->warning_index);
    token_show(ctx, ref_count);
    end_diagnostic(ctx, false);
  }
  if (ctx->mem[r - mem_min].hh.lh != 3584) {
    ctx->scanner_status = 3;
    unbalance = 0;
    ctx->long_state = ctx->eqtb[ctx->cur_cs].hh.U2.b0;
    if (ctx->long_state >= 113)
      ctx->long_state -= 2;
    do {
      ctx->mem[mem_max - mem_min - 3].hh.rh = -1073741824;
      if ((ctx->mem[r - mem_min].hh.lh > 3583) ||
          (ctx->mem[r - mem_min].hh.lh < 3328)) {
        s = -1073741824;
      } else {
        match_chr = ctx->mem[r - mem_min].hh.lh - 3328;
        s = ctx->mem[r - mem_min].hh.rh;
        r = s;
        p = mem_max - 3;
        m = 0;
      }
    _L22:
      get_token(ctx);
      if (ctx->cur_tok == ctx->mem[r - mem_min].hh.lh) {
        r = ctx->mem[r - mem_min].hh.rh;
        if ((ctx->mem[r - mem_min].hh.lh >= 3328) &&
            (ctx->mem[r - mem_min].hh.lh <= 3584)) {
          if (ctx->cur_tok < 512)
            --ctx->align_state;
          goto _L40;
        } else {
          goto _L22;
        }
      }
      if (s != r) {
        if (s == (-1073741824)) {
          print_nl(ctx, 262);
          print(ctx, 650);
          sprint_cs(ctx, ctx->warning_index);
          print(ctx, 651);
          ctx->help_ptr = 4;
          ctx->help_line[3] = 652;
          ctx->help_line[2] = 653;
          ctx->help_line[1] = 654;
          ctx->help_line[0] = 655;
          error(ctx);
          goto _L10;
        }
        t = s;
        do {
          q = get_avail(ctx);
          ctx->mem[p - mem_min].hh.rh = q;
          ctx->mem[q - mem_min].hh.lh = ctx->mem[t - mem_min].hh.lh;
          p = q;
          ++m;
          u = ctx->mem[t - mem_min].hh.rh;
          v = s;
          while (true) {
            if (u == r) {
              if (ctx->cur_tok != ctx->mem[v - mem_min].hh.lh) {
                goto _L30;
              } else {
                r = ctx->mem[v - mem_min].hh.rh;
                goto _L22;
              }
            }
            if (ctx->mem[u - mem_min].hh.lh != ctx->mem[v - mem_min].hh.lh)
              goto _L30;
            u = ctx->mem[u - mem_min].hh.rh;
            v = ctx->mem[v - mem_min].hh.rh;
          }
        _L30:
          t = ctx->mem[t - mem_min].hh.rh;
        } while (t != r);
        r = s;
      }
      if (ctx->cur_tok == ctx->par_token) {
        if (ctx->long_state != 112) {
          if (ctx->long_state == 111) {
            runaway(ctx);
            print_nl(ctx, 262);
            print(ctx, 645);
            sprint_cs(ctx, ctx->warning_index);
            print(ctx, 646);
            ctx->help_ptr = 3;
            ctx->help_line[2] = 647;
            ctx->help_line[1] = 648;
            ctx->help_line[0] = 649;
            back_error(ctx);
          }
          ctx->pstack[n] = ctx->mem[mem_max - mem_min - 3].hh.rh;
          ctx->align_state -= unbalance;
          for (m = 0; m <= n; ++m)
            flush_list(ctx, ctx->pstack[m]);
          goto _L10;
        }
      }
      if (ctx->cur_tok < 768) {
        if (ctx->cur_tok >= 512) {
          back_input(ctx);
          print_nl(ctx, 262);
          print(ctx, 637);
          sprint_cs(ctx, ctx->warning_index);
          print(ctx, 638);
          ctx->help_ptr = 6;
          ctx->help_line[5] = 639;
          ctx->help_line[4] = 640;
          ctx->help_line[3] = 641;
          ctx->help_line[2] = 642;
          ctx->help_line[1] = 643;
          ctx->help_line[0] = 644;
          ++ctx->align_state;
          ctx->long_state = 111;
          ctx->cur_tok = ctx->par_token;
          ins_error(ctx);
          goto _L22;
        }
        unbalance = 1;
        while (true) {
          q = ctx->avail;
          if (q == (-1073741824)) {
            q = get_avail(ctx);
          } else {
            ctx->avail = ctx->mem[q - mem_min].hh.rh;
            ctx->mem[q - mem_min].hh.rh = -1073741824;
          }
          ctx->mem[p - mem_min].hh.rh = q;
          ctx->mem[q - mem_min].hh.lh = ctx->cur_tok;
          p = q;
          get_token(ctx);
          if (ctx->cur_tok == ctx->par_token) {
            if (ctx->long_state != 112) {
              if (ctx->long_state == 111) {
                runaway(ctx);
                print_nl(ctx, 262);
                print(ctx, 645);
                sprint_cs(ctx, ctx->warning_index);
                print(ctx, 646);
                ctx->help_ptr = 3;
                ctx->help_line[2] = 647;
                ctx->help_line[1] = 648;
                ctx->help_line[0] = 649;
                back_error(ctx);
              }
              ctx->pstack[n] = ctx->mem[mem_max - mem_min - 3].hh.rh;
              ctx->align_state -= unbalance;
              for (m = 0; m <= n; ++m)
                flush_list(ctx, ctx->pstack[m]);
              goto _L10;
            }
          }
          if (ctx->cur_tok >= 768)
            continue;
          if (ctx->cur_tok < 512) {
            ++unbalance;
          } else {
            --unbalance;
            if (!unbalance)
              goto _L31;
          }
        }
      _L31:
        rbrace_ptr = p;
        q = get_avail(ctx);
        ctx->mem[p - mem_min].hh.rh = q;
        ctx->mem[q - mem_min].hh.lh = ctx->cur_tok;
        p = q;
      } else {
        if (ctx->cur_tok == 2592) {
          if (ctx->mem[r - mem_min].hh.lh <= 3584) {
            if (ctx->mem[r - mem_min].hh.lh >= 3328)
              goto _L22;
          }
        }
        q = get_avail(ctx);
        ctx->mem[p - mem_min].hh.rh = q;
        ctx->mem[q - mem_min].hh.lh = ctx->cur_tok;
        p = q;
      }
      ++m;
      if (ctx->mem[r - mem_min].hh.lh > 3584)
        goto _L22;
      if (ctx->mem[r - mem_min].hh.lh < 3328)
        goto _L22;
    _L40:
      if (s != (-1073741824)) {
        if ((m == 1) && (ctx->mem[p - mem_min].hh.lh < 768) &&
            (p != (mem_max - 3))) {
          ctx->mem[rbrace_ptr - mem_min].hh.rh = -1073741824;
          ctx->mem[p - mem_min].hh.rh = ctx->avail;
          ctx->avail = p;
          p = ctx->mem[mem_max - mem_min - 3].hh.rh;
          ctx->pstack[n] = ctx->mem[p - mem_min].hh.rh;
          ctx->mem[p - mem_min].hh.rh = ctx->avail;
          ctx->avail = p;
        } else {
          ctx->pstack[n] = ctx->mem[mem_max - mem_min - 3].hh.rh;
        }
        ++n;
        if (ctx->eqtb[12193].int_ > 0) {
          begin_diagnostic(ctx);
          print_nl(ctx, match_chr);
          print_int(ctx, n);
          print(ctx, 656);
          show_token_list(ctx, ctx->pstack[n - 1], -1073741824, 1000);
          end_diagnostic(ctx, false);
        }
      }
    } while (ctx->mem[r - mem_min].hh.lh != 3584);
  }
  while ((!ctx->cur_input.state_field) &&
         (ctx->cur_input.loc_field == (-1073741824)) &&
         (ctx->cur_input.index_field != 2))
    end_token_list(ctx);
  begin_token_list(ctx, ref_count, 5);
  ctx->cur_input.name_field = ctx->warning_index;
  ctx->cur_input.loc_field = ctx->mem[r - mem_min].hh.rh;
  if (n > 0) {
    if (ctx->param_ptr + n > ctx->max_param_stack) {
      ctx->max_param_stack = ctx->param_ptr + n;
      if (ctx->max_param_stack > param_size)
        overflow(ctx, 636, param_size);
    }
    for (m = 0; m <= (n - 1); ++m)
      ctx->param_stack[ctx->param_ptr + m] = ctx->pstack[m];
    ctx->param_ptr += n;
  }
_L10:
  ctx->scanner_status = save_scanner_status;
  ctx->warning_index = save_warning_index;
}

void insert_relax(ctex_t *ctx) {
  ctx->cur_tok = ctx->cur_cs + 4095;
  back_input(ctx);
  ctx->cur_tok = 13616;
  back_input(ctx);
  ctx->cur_input.index_field = 4;
}

void expand(ctex_t *ctx) {
  halfword t, p, q, r;
  int j;
  small_number save_scanner_status;
  integer cv_backup = ctx->cur_val;
  small_number cvl_backup = ctx->cur_val_level;
  small_number radix_backup = ctx->radix;
  small_number co_backup = ctx->cur_order;
  halfword backup_backup = ctx->mem[mem_max - mem_min - 13].hh.rh;
  if (ctx->cur_cmd < 111) {
    if (ctx->eqtb[12199].int_ > 1)
      show_cur_cmd_chr(ctx);
    switch (ctx->cur_cmd) {
    case 110:
      if (ctx->cur_mark[ctx->cur_chr] != (-1073741824))
        begin_token_list(ctx, ctx->cur_mark[ctx->cur_chr], 14);
      break;
    case 102:
      get_token(ctx);
      t = ctx->cur_tok;
      get_token(ctx);
      if (ctx->cur_cmd > 100)
        expand(ctx);
      else
        back_input(ctx);
      ctx->cur_tok = t;
      back_input(ctx);
      break;
    case 103:
      save_scanner_status = ctx->scanner_status;
      ctx->scanner_status = 0;
      get_token(ctx);
      ctx->scanner_status = save_scanner_status;
      t = ctx->cur_tok;
      back_input(ctx);
      if (t >= 4095) {
        p = get_avail(ctx);
        ctx->mem[p - mem_min].hh.lh = 13618;
        ctx->mem[p - mem_min].hh.rh = ctx->cur_input.loc_field;
        ctx->cur_input.start_field = p;
        ctx->cur_input.loc_field = p;
      }
      break;
    case 107:
      r = get_avail(ctx);
      p = r;
      do {
        get_x_token(ctx);
        if (!ctx->cur_cs) {
          q = get_avail(ctx);
          ctx->mem[p - mem_min].hh.rh = q;
          ctx->mem[q - mem_min].hh.lh = ctx->cur_tok;
          p = q;
        }
      } while (!ctx->cur_cs);
      if (ctx->cur_cmd != 67) {
        print_nl(ctx, 262);
        print(ctx, 625);
        print_esc(ctx, 505);
        print(ctx, 626);
        ctx->help_ptr = 2;
        ctx->help_line[1] = 627;
        ctx->help_line[0] = 628;
        back_error(ctx);
      }
      j = ctx->first;
      p = ctx->mem[r - mem_min].hh.rh;
      while (p != (-1073741824)) {
        if (j >= ctx->max_buf_stack) {
          ctx->max_buf_stack = j + 1;
          if (ctx->max_buf_stack == buf_size)
            overflow(ctx, 256, buf_size);
        }
        ctx->buffer[j] = ctx->mem[p - mem_min].hh.lh & 255;
        ++j;
        p = ctx->mem[p - mem_min].hh.rh;
      }
      if (j > (ctx->first + 1)) {
        ctx->no_new_control_sequence = false;
        ctx->cur_cs = id_lookup(ctx, ctx->first, j - ctx->first);
        ctx->no_new_control_sequence = true;
      } else if (j == ctx->first)
        ctx->cur_cs = 513;
      else
        ctx->cur_cs = ctx->buffer[ctx->first] + 257;
      flush_list(ctx, r);
      if (ctx->eqtb[ctx->cur_cs].hh.U2.b0 == 101)
        eq_define(ctx, ctx->cur_cs, 0, 256);
      ctx->cur_tok = ctx->cur_cs + 4095;
      back_input(ctx);
      break;
    case 108:
      conv_toks(ctx);
      break;
    case 109:
      ins_the_toks(ctx);
      break;
    case 105:
      conditional(ctx);
      break;
    case 106:
      if (ctx->cur_chr > ctx->if_limit) {
        if (ctx->if_limit == 1) {
          insert_relax(ctx);
        } else {
          print_nl(ctx, 262);
          print(ctx, 776);
          print_cmd_chr(ctx, 106, ctx->cur_chr);
          ctx->help_ptr = 1;
          ctx->help_line[0] = 777;
          error(ctx);
        }
      } else {
        while (ctx->cur_chr != 2)
          pass_text(ctx);
        p = ctx->cond_ptr;
        ctx->if_line = ctx->mem[p - mem_min + 1].int_;
        ctx->cur_if = ctx->mem[p - mem_min].hh.U2.b1;
        ctx->if_limit = ctx->mem[p - mem_min].hh.U2.b0;
        ctx->cond_ptr = ctx->mem[p - mem_min].hh.rh;
        free_node(ctx, p, 2);
      }
      break;
    case 104:
      if (ctx->cur_chr > 0) {
        ctx->force_eof = true;
      } else if (ctx->name_in_progress)
        insert_relax(ctx);
      else
        start_input(ctx);
      break;
    default:
      print_nl(ctx, 262);
      print(ctx, 619);
      ctx->help_ptr = 5;
      ctx->help_line[4] = 620;
      ctx->help_line[3] = 621;
      ctx->help_line[2] = 622;
      ctx->help_line[1] = 623;
      ctx->help_line[0] = 624;
      error(ctx);
      break;
    }
  } else if (ctx->cur_cmd < 115) {
    macro_call(ctx);
  } else {
    ctx->cur_tok = 13615;
    back_input(ctx);
  }
  ctx->cur_val = cv_backup;
  ctx->cur_val_level = cvl_backup;
  ctx->radix = radix_backup;
  ctx->cur_order = co_backup;
  ctx->mem[mem_max - mem_min - 13].hh.rh = backup_backup;
}

void get_x_token(ctex_t *ctx) {
_L20:
  get_next(ctx);
  if (ctx->cur_cmd <= 100)
    goto _L30;
  if (ctx->cur_cmd >= 111) {
    if (ctx->cur_cmd >= 115) {
      ctx->cur_cs = 9520;
      ctx->cur_cmd = 9;
      goto _L30;
    }
    macro_call(ctx);
  } else {
    expand(ctx);
  }
  goto _L20;
_L30:
  if (!ctx->cur_cs)
    ctx->cur_tok = (ctx->cur_cmd * 256) + ctx->cur_chr;
  else
    ctx->cur_tok = ctx->cur_cs + 4095;
}

void x_token(ctex_t *ctx) {
  while (ctx->cur_cmd > 100) {
    expand(ctx);
    get_next(ctx);
  }
  if (!ctx->cur_cs)
    ctx->cur_tok = (ctx->cur_cmd * 256) + ctx->cur_chr;
  else
    ctx->cur_tok = ctx->cur_cs + 4095;
}

void scan_left_brace(ctex_t *ctx) {
  do {
    get_x_token(ctx);
  } while ((ctx->cur_cmd == 10) || (!ctx->cur_cmd));
  if (ctx->cur_cmd == 1)
    return;
  print_nl(ctx, 262);
  print(ctx, 657);
  ctx->help_ptr = 4;
  ctx->help_line[3] = 658;
  ctx->help_line[2] = 659;
  ctx->help_line[1] = 660;
  ctx->help_line[0] = 661;
  back_error(ctx);
  ctx->cur_tok = 379;
  ctx->cur_cmd = 1;
  ctx->cur_chr = 123;
  ++ctx->align_state;
}

void scan_optional_equals(ctex_t *ctx) {
  do {
    get_x_token(ctx);
  } while (ctx->cur_cmd == 10);
  if (ctx->cur_tok != 3133)
    back_input(ctx);
}

bool_t scan_keyword(ctex_t *ctx, str_number s) {
  bool_t result;
  halfword p = mem_max - 13, q;
  pool_pointer k;
  ctx->mem[p - mem_min].hh.rh = -1073741824;
  k = ctx->str_start[s];
  while (k < ctx->str_start[s + 1]) {
    get_x_token(ctx);
    if ((!ctx->cur_cs) && ((ctx->cur_chr == ctx->str_pool[k]) ||
                           (ctx->cur_chr == (ctx->str_pool[k] - 32)))) {
      q = get_avail(ctx);
      ctx->mem[p - mem_min].hh.rh = q;
      ctx->mem[q - mem_min].hh.lh = ctx->cur_tok;
      p = q;
      ++k;
      continue;
    } else {
      if ((ctx->cur_cmd == 10) && (p == (mem_max - 13)))
        continue;
      back_input(ctx);
      if (p != (mem_max - 13))
        begin_token_list(ctx, ctx->mem[mem_max - mem_min - 13].hh.rh, 3);
      result = false;
      goto _L10;
    }
  }
  flush_list(ctx, ctx->mem[mem_max - mem_min - 13].hh.rh);
  result = true;
_L10:
  return result;
}

void mu_error(ctex_t *ctx) {
  print_nl(ctx, 262);
  print(ctx, 662);
  ctx->help_ptr = 1;
  ctx->help_line[0] = 663;
  error(ctx);
}

void scan_eight_bit_int(ctex_t *ctx) {
  scan_int(ctx);
  if (((unsigned)ctx->cur_val) <= 255)
    return;
  print_nl(ctx, 262);
  print(ctx, 687);
  ctx->help_ptr = 2;
  ctx->help_line[1] = 688;
  ctx->help_line[0] = 689;
  int_error(ctx, ctx->cur_val);
  ctx->cur_val = 0;
}

void scan_char_num(ctex_t *ctx) {
  scan_int(ctx);
  if (((unsigned)ctx->cur_val) <= 255)
    return;
  print_nl(ctx, 262);
  print(ctx, 690);
  ctx->help_ptr = 2;
  ctx->help_line[1] = 691;
  ctx->help_line[0] = 689;
  int_error(ctx, ctx->cur_val);
  ctx->cur_val = 0;
}

void scan_four_bit_int(ctex_t *ctx) {
  scan_int(ctx);
  if (((unsigned)ctx->cur_val) <= 15)
    return;
  print_nl(ctx, 262);
  print(ctx, 692);
  ctx->help_ptr = 2;
  ctx->help_line[1] = 693;
  ctx->help_line[0] = 689;
  int_error(ctx, ctx->cur_val);
  ctx->cur_val = 0;
}

void scan_fifteen_bit_int(ctex_t *ctx) {
  scan_int(ctx);
  if (((unsigned)ctx->cur_val) <= 32767)
    return;
  print_nl(ctx, 262);
  print(ctx, 694);
  ctx->help_ptr = 2;
  ctx->help_line[1] = 695;
  ctx->help_line[0] = 689;
  int_error(ctx, ctx->cur_val);
  ctx->cur_val = 0;
}

void scan_twenty_seven_bit_int(ctex_t *ctx) {
  scan_int(ctx);
  if (((unsigned)ctx->cur_val) <= 134217727)
    return;
  print_nl(ctx, 262);
  print(ctx, 696);
  ctx->help_ptr = 2;
  ctx->help_line[1] = 697;
  ctx->help_line[0] = 689;
  int_error(ctx, ctx->cur_val);
  ctx->cur_val = 0;
}

void scan_font_ident(ctex_t *ctx) {
  internal_font_number f;
  halfword m;
  do {
    get_x_token(ctx);
  } while (ctx->cur_cmd == 10);
  if (ctx->cur_cmd == 88) {
    f = ctx->eqtb[10834].hh.rh;
  } else if (ctx->cur_cmd == 87) {
    f = ctx->cur_chr;
  } else if (ctx->cur_cmd == 86) {
    m = ctx->cur_chr;
    scan_four_bit_int(ctx);
    f = ctx->eqtb[m + ctx->cur_val].hh.rh;
  } else {
    print_nl(ctx, 262);
    print(ctx, 816);
    ctx->help_ptr = 2;
    ctx->help_line[1] = 817;
    ctx->help_line[0] = 818;
    back_error(ctx);
    f = 0;
  }
  ctx->cur_val = f;
}

void find_font_dimen(ctex_t *ctx, bool_t writing) {
  internal_font_number f;
  integer n;
  scan_int(ctx);
  n = ctx->cur_val;
  scan_font_ident(ctx);
  f = ctx->cur_val;
  if (n <= 0) {
    ctx->cur_val = ctx->fmem_ptr;
  } else {
    if (writing && (n <= 4) && (n >= 2) &&
        (ctx->fnt_infos.font_glue[f] != (-1073741824))) {
      delete_glue_ref(ctx, ctx->fnt_infos.font_glue[f]);
      ctx->fnt_infos.font_glue[f] = -1073741824;
    }
    if (n > ctx->fnt_infos.font_params[f]) {
      if (f < ctx->font_ptr) {
        ctx->cur_val = ctx->fmem_ptr;
      } else {
        do {
          if (ctx->fmem_ptr == font_mem_size)
            overflow(ctx, 823, font_mem_size);
          ctx->font_info[ctx->fmem_ptr].int_ = 0;
          ++ctx->fmem_ptr;
          ++ctx->fnt_infos.font_params[f];
        } while (n != ctx->fnt_infos.font_params[f]);
        ctx->cur_val = ctx->fmem_ptr - 1;
      }
    } else {
      ctx->cur_val = n + ctx->fnt_infos.param_base[f];
    }
  }
  if (ctx->cur_val != ctx->fmem_ptr)
    return;
  print_nl(ctx, 262);
  print(ctx, 801);
  print_esc(ctx, ctx->hash[f + 9010].rh);
  print(ctx, 819);
  print_int(ctx, ctx->fnt_infos.font_params[f]);
  print(ctx, 820);
  ctx->help_ptr = 2;
  ctx->help_line[1] = 821;
  ctx->help_line[0] = 822;
  error(ctx);
}

void scan_something_internal(ctex_t *ctx, small_number level, bool_t negative) {
  int p;
  halfword m = ctx->cur_chr;
  switch (ctx->cur_cmd) {
  case 85:
    scan_char_num(ctx);
    if (m == 11907) {
      ctx->cur_val = ctx->eqtb[ctx->cur_val + 11907].hh.rh + 1073741824;
      ctx->cur_val_level = 0;
    } else if (m < 11907) {
      ctx->cur_val = ctx->eqtb[m + ctx->cur_val].hh.rh;
      ctx->cur_val_level = 0;
    } else {
      ctx->cur_val = ctx->eqtb[m + ctx->cur_val].int_;
      ctx->cur_val_level = 0;
    }
    break;
  case 71:
  case 72:
  case 86:
  case 87:
  case 88:
    if (level != 5) {
      print_nl(ctx, 262);
      print(ctx, 664);
      ctx->help_ptr = 3;
      ctx->help_line[2] = 665;
      ctx->help_line[1] = 666;
      ctx->help_line[0] = 667;
      back_error(ctx);
      ctx->cur_val = 0;
      ctx->cur_val_level = 1;
    } else if (ctx->cur_cmd <= 72) {
      if (ctx->cur_cmd < 72) {
        scan_eight_bit_int(ctx);
        m = ctx->cur_val + 10322;
      }
      ctx->cur_val = ctx->eqtb[m].hh.rh;
      ctx->cur_val_level = 5;
    } else {
      back_input(ctx);
      scan_font_ident(ctx);
      ctx->cur_val += 9524;
      ctx->cur_val_level = 4;
    }
    break;
  case 73:
    ctx->cur_val = ctx->eqtb[m].int_;
    ctx->cur_val_level = 0;
    break;
  case 74:
    ctx->cur_val = ctx->eqtb[m].int_;
    ctx->cur_val_level = 1;
    break;
  case 75:
    ctx->cur_val = ctx->eqtb[m].hh.rh;
    ctx->cur_val_level = 2;
    break;
  case 76:
    ctx->cur_val = ctx->eqtb[m].hh.rh;
    ctx->cur_val_level = 3;
    break;
  case 79:
    if (abs(ctx->cur_list.mode_field) != m) {
      print_nl(ctx, 262);
      print(ctx, 680);
      print_cmd_chr(ctx, 79, m);
      ctx->help_ptr = 4;
      ctx->help_line[3] = 681;
      ctx->help_line[2] = 682;
      ctx->help_line[1] = 683;
      ctx->help_line[0] = 684;
      error(ctx);
      if (level != 5) {
        ctx->cur_val = 0;
        ctx->cur_val_level = 1;
      } else {
        ctx->cur_val = 0;
        ctx->cur_val_level = 0;
      }
    } else if (m == 1) {
      ctx->cur_val = ctx->cur_list.aux_field.int_;
      ctx->cur_val_level = 1;
    } else {
      ctx->cur_val = ctx->cur_list.aux_field.hh.lh;
      ctx->cur_val_level = 0;
    }
    break;
  case 80:
    if (!ctx->cur_list.mode_field) {
      ctx->cur_val = 0;
      ctx->cur_val_level = 0;
    } else {
      ctx->nest[ctx->nest_ptr] = ctx->cur_list;
      p = ctx->nest_ptr;
      while (abs(ctx->nest[p].mode_field) != 1)
        --p;
      ctx->cur_val = ctx->nest[p].pg_field;
      ctx->cur_val_level = 0;
    }
    break;
  case 82:
    if (!m)
      ctx->cur_val = ctx->dead_cycles;
    else
      ctx->cur_val = ctx->insert_penalties;
    ctx->cur_val_level = 0;
    break;
  case 81:
    if ((!ctx->page_contents) && (!ctx->output_active)) {
      if (!m)
        ctx->cur_val = 1073741823;
      else
        ctx->cur_val = 0;
    } else {
      ctx->cur_val = ctx->page_so_far[m];
    }
    ctx->cur_val_level = 1;
    break;
  case 84:
    if (ctx->eqtb[10312].hh.rh == (-1073741824))
      ctx->cur_val = 0;
    else
      ctx->cur_val = ctx->mem[ctx->eqtb[10312].hh.rh - mem_min].hh.lh;
    ctx->cur_val_level = 0;
    break;
  case 83:
    scan_eight_bit_int(ctx);
    if (ctx->eqtb[ctx->cur_val + 10578].hh.rh == (-1073741824))
      ctx->cur_val = 0;
    else
      ctx->cur_val =
          ctx->mem[ctx->eqtb[ctx->cur_val + 10578].hh.rh + m - mem_min].int_;
    ctx->cur_val_level = 1;
    break;
  case 68:
  case 69:
    ctx->cur_val = ctx->cur_chr;
    ctx->cur_val_level = 0;
    break;
  case 77:
    find_font_dimen(ctx, false);
    ctx->font_info[ctx->fmem_ptr].int_ = 0;
    ctx->cur_val = ctx->font_info[ctx->cur_val].int_;
    ctx->cur_val_level = 1;
    break;
  case 78:
    scan_font_ident(ctx);
    if (!m) {
      ctx->cur_val = ctx->fnt_infos.hyphen_char[ctx->cur_val];
      ctx->cur_val_level = 0;
    } else {
      ctx->cur_val = ctx->fnt_infos.skew_char[ctx->cur_val];
      ctx->cur_val_level = 0;
    }
    break;
  case 89:
    scan_eight_bit_int(ctx);
    switch (m) {
    case 0:
      ctx->cur_val = ctx->eqtb[ctx->cur_val + 12218].int_;
      break;
    case 1:
      ctx->cur_val = ctx->eqtb[ctx->cur_val + 12751].int_;
      break;
    case 2:
      ctx->cur_val = ctx->eqtb[ctx->cur_val + 9800].hh.rh;
      break;
    case 3:
      ctx->cur_val = ctx->eqtb[ctx->cur_val + 10056].hh.rh;
      break;
    }
    ctx->cur_val_level = m;
    break;
  case 70:
    if (ctx->cur_chr > 2) {
      if (ctx->cur_chr == 3)
        ctx->cur_val = ctx->line;
      else
        ctx->cur_val = ctx->last_badness;
      ctx->cur_val_level = 0;
    } else {
      if (ctx->cur_chr == 2)
        ctx->cur_val = 0;
      else
        ctx->cur_val = 0;
      ctx->cur_val_level = ctx->cur_chr;
      if ((ctx->cur_list.tail_field < ctx->hi_mem_min) &&
          ctx->cur_list.mode_field) {
        switch (ctx->cur_chr) {
        case 0:
          if (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 == 12)
            ctx->cur_val =
                ctx->mem[ctx->cur_list.tail_field - mem_min + 1].int_;
          break;
        case 1:
          if (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 == 11)
            ctx->cur_val =
                ctx->mem[ctx->cur_list.tail_field - mem_min + 1].int_;
          break;
        case 2:
          if (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 == 10) {
            ctx->cur_val =
                ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.lh;
            if (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 == 99)
              ctx->cur_val_level = 3;
          }
          break;
        }
      } else if ((ctx->cur_list.mode_field == 1) &&
                 (ctx->cur_list.tail_field == ctx->cur_list.head_field)) {
        switch (ctx->cur_chr) {
        case 0:
          ctx->cur_val = ctx->last_penalty;
          break;
        case 1:
          ctx->cur_val = ctx->last_kern;
          break;
        case 2:
          if (ctx->last_glue != 1073741824)
            ctx->cur_val = ctx->last_glue;
          break;
        }
      }
    }
    break;
  default:
    print_nl(ctx, 262);
    print(ctx, 685);
    print_cmd_chr(ctx, ctx->cur_cmd, ctx->cur_chr);
    print(ctx, 686);
    print_esc(ctx, 537);
    ctx->help_ptr = 1;
    ctx->help_line[0] = 684;
    error(ctx);
    if (level != 5) {
      ctx->cur_val = 0;
      ctx->cur_val_level = 1;
    } else {
      ctx->cur_val = 0;
      ctx->cur_val_level = 0;
    }
    break;
  }
  while (ctx->cur_val_level > level) {
    if (ctx->cur_val_level == 2) {
      ctx->cur_val = ctx->mem[ctx->cur_val - mem_min + 1].int_;
    } else if (ctx->cur_val_level == 3)
      mu_error(ctx);
    --ctx->cur_val_level;
  }
  if (!negative) {
    if ((ctx->cur_val_level >= 2) && (ctx->cur_val_level <= 3))
      ++ctx->mem[ctx->cur_val - mem_min].hh.rh;
    return;
  }
  if (ctx->cur_val_level < 2) {
    ctx->cur_val = -ctx->cur_val;
    return;
  }
  ctx->cur_val = new_spec(ctx, ctx->cur_val);
  ctx->mem[ctx->cur_val - mem_min + 1].int_ =
      -ctx->mem[ctx->cur_val - mem_min + 1].int_;
  ctx->mem[ctx->cur_val - mem_min + 2].int_ =
      -ctx->mem[ctx->cur_val - mem_min + 2].int_;
  ctx->mem[ctx->cur_val - mem_min + 3].int_ =
      -ctx->mem[ctx->cur_val - mem_min + 3].int_;
}

void scan_int(ctex_t *ctx) {
  bool_t negative = false;
  integer m;
  small_number d;
  bool_t vacuous, OK_so_far = true;
  ctx->radix = 0;
  do {
    do {
      get_x_token(ctx);
    } while (ctx->cur_cmd == 10);
    if (ctx->cur_tok == 3117) {
      negative = !negative;
      ctx->cur_tok = 3115;
    }
  } while (ctx->cur_tok == 3115);
  if (ctx->cur_tok == 3168) {
    get_token(ctx);
    if (ctx->cur_tok < 4095) {
      ctx->cur_val = ctx->cur_chr;
      if (ctx->cur_cmd <= 2) {
        if (ctx->cur_cmd == 2)
          ++ctx->align_state;
        else
          --ctx->align_state;
      }
    } else if (ctx->cur_tok < 4352)
      ctx->cur_val = ctx->cur_tok - 4096;
    else
      ctx->cur_val = ctx->cur_tok - 4352;
    if (ctx->cur_val > 255) {
      print_nl(ctx, 262);
      print(ctx, 698);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 699;
      ctx->help_line[0] = 700;
      ctx->cur_val = 48;
      back_error(ctx);
    } else {
      get_x_token(ctx);
      if (ctx->cur_cmd != 10)
        back_input(ctx);
    }
  } else if ((ctx->cur_cmd >= 68) && (ctx->cur_cmd <= 89)) {
    scan_something_internal(ctx, 0, false);
  } else {
    ctx->radix = 10;
    m = 214748364;
    if (ctx->cur_tok == 3111) {
      ctx->radix = 8;
      m = 268435456;
      get_x_token(ctx);
    } else if (ctx->cur_tok == 3106) {
      ctx->radix = 16;
      m = 134217728;
      get_x_token(ctx);
    }
    vacuous = true;
    ctx->cur_val = 0;
    while (true) {
      if ((ctx->cur_tok < (ctx->radix + 3120)) && (ctx->cur_tok >= 3120) &&
          (ctx->cur_tok <= 3129)) {
        d = ctx->cur_tok - 3120;
      } else if (ctx->radix == 16) {
        if ((ctx->cur_tok <= 2886) && (ctx->cur_tok >= 2881)) {
          d = ctx->cur_tok - 2871;
        } else if ((ctx->cur_tok <= 3142) && (ctx->cur_tok >= 3137))
          d = ctx->cur_tok - 3127;
        else
          goto _L30;
      } else {
        goto _L30;
      }
      vacuous = false;
      if ((ctx->cur_val >= m) &&
          ((ctx->cur_val > m) || (d > 7) || (ctx->radix != 10))) {
        if (OK_so_far) {
          print_nl(ctx, 262);
          print(ctx, 701);
          ctx->help_ptr = 2;
          ctx->help_line[1] = 702;
          ctx->help_line[0] = 703;
          error(ctx);
          ctx->cur_val = 2147483647;
          OK_so_far = false;
        }
      } else {
        ctx->cur_val = (ctx->cur_val * ctx->radix) + d;
      }
      get_x_token(ctx);
    }
  _L30:
    if (vacuous) {
      print_nl(ctx, 262);
      print(ctx, 664);
      ctx->help_ptr = 3;
      ctx->help_line[2] = 665;
      ctx->help_line[1] = 666;
      ctx->help_line[0] = 667;
      back_error(ctx);
    } else if (ctx->cur_cmd != 10)
      back_input(ctx);
  }
  if (negative)
    ctx->cur_val = -ctx->cur_val;
}

void scan_dimen(ctex_t *ctx, bool_t mu, bool_t inf, bool_t shortcut) {
  bool_t negative = false;
  integer f = 0, save_cur_val;
  int num, denom;
  small_number k, kk;
  halfword p, q;
  scaled v;
  ctx->arith_error = false;
  ctx->cur_order = 0;
  if (!shortcut) {
    do {
      do {
        get_x_token(ctx);
      } while (ctx->cur_cmd == 10);
      if (ctx->cur_tok == 3117) {
        negative = !negative;
        ctx->cur_tok = 3115;
      }
    } while (ctx->cur_tok == 3115);
    if ((ctx->cur_cmd >= 68) && (ctx->cur_cmd <= 89)) {
      if (mu) {
        scan_something_internal(ctx, 3, false);
        if (ctx->cur_val_level >= 2) {
          v = ctx->mem[ctx->cur_val - mem_min + 1].int_;
          delete_glue_ref(ctx, ctx->cur_val);
          ctx->cur_val = v;
        }
        if (ctx->cur_val_level == 3)
          goto _L89;
        if (ctx->cur_val_level)
          mu_error(ctx);
      } else {
        scan_something_internal(ctx, 1, false);
        if (ctx->cur_val_level == 1)
          goto _L89;
      }
    } else {
      back_input(ctx);
      if (ctx->cur_tok == 3116)
        ctx->cur_tok = 3118;
      if (ctx->cur_tok != 3118) {
        scan_int(ctx);
      } else {
        ctx->radix = 10;
        ctx->cur_val = 0;
      }
      if (ctx->cur_tok == 3116)
        ctx->cur_tok = 3118;
      if ((ctx->radix == 10) && (ctx->cur_tok == 3118)) {
        k = 0;
        p = -1073741824;
        get_token(ctx);
        while (true) {
          get_x_token(ctx);
          if ((ctx->cur_tok > 3129) || (ctx->cur_tok < 3120))
            goto _L31;
          if (k >= 17)
            continue;
          q = get_avail(ctx);
          ctx->mem[q - mem_min].hh.rh = p;
          ctx->mem[q - mem_min].hh.lh = ctx->cur_tok - 3120;
          p = q;
          ++k;
        }
      _L31:
        for (kk = k; kk >= 1; --kk) {
          ctx->dig[kk - 1] = ctx->mem[p - mem_min].hh.lh;
          q = p;
          p = ctx->mem[p - mem_min].hh.rh;
          ctx->mem[q - mem_min].hh.rh = ctx->avail;
          ctx->avail = q;
        }
        f = round_decimals(ctx, k);
        if (ctx->cur_cmd != 10)
          back_input(ctx);
      }
    }
  }
  if (ctx->cur_val < 0) {
    negative = !negative;
    ctx->cur_val = -ctx->cur_val;
  }
  if (inf) {
    if (scan_keyword(ctx, 311)) {
      ctx->cur_order = 1;
      while (scan_keyword(ctx, 108)) {
        if (ctx->cur_order != 3) {
          ++ctx->cur_order;
          continue;
        }
        print_nl(ctx, 262);
        print(ctx, 705);
        print(ctx, 706);
        ctx->help_ptr = 1;
        ctx->help_line[0] = 707;
        error(ctx);
      }
      goto _L88;
    }
  }
  save_cur_val = ctx->cur_val;
  do {
    get_x_token(ctx);
  } while (ctx->cur_cmd == 10);
  if ((ctx->cur_cmd >= 68) && (ctx->cur_cmd <= 89)) {
    if (mu) {
      scan_something_internal(ctx, 3, false);
      if (ctx->cur_val_level >= 2) {
        v = ctx->mem[ctx->cur_val - mem_min + 1].int_;
        delete_glue_ref(ctx, ctx->cur_val);
        ctx->cur_val = v;
      }
      if (ctx->cur_val_level != 3)
        mu_error(ctx);
    } else {
      scan_something_internal(ctx, 1, false);
    }
    v = ctx->cur_val;
    goto _L40;
  }
  back_input(ctx);
  if (mu)
    goto _L45;
  if (scan_keyword(ctx, 708)) {
    v = ctx->font_info[ctx->fnt_infos.param_base[ctx->eqtb[10834].hh.rh] + 6]
            .int_;
  } else if (scan_keyword(ctx, 709))
    v = ctx->font_info[ctx->fnt_infos.param_base[ctx->eqtb[10834].hh.rh] + 5]
            .int_;
  else
    goto _L45;
  get_x_token(ctx);
  if (ctx->cur_cmd != 10)
    back_input(ctx);
_L40:
  ctx->cur_val = mult_and_add(ctx, save_cur_val, v, xn_over_d(ctx, v, f, 65536),
                              1073741823);
  goto _L89;
_L45:
  if (mu) {
    if (scan_keyword(ctx, 337)) {
      goto _L88;
    } else {
      print_nl(ctx, 262);
      print(ctx, 705);
      print(ctx, 710);
      ctx->help_ptr = 4;
      ctx->help_line[3] = 711;
      ctx->help_line[2] = 712;
      ctx->help_line[1] = 713;
      ctx->help_line[0] = 714;
      error(ctx);
      goto _L88;
    }
  }
  if (scan_keyword(ctx, 704)) {
    prepare_mag(ctx);
    if (ctx->eqtb[12180].int_ != 1000) {
      ctx->cur_val = xn_over_d(ctx, ctx->cur_val, 1000, ctx->eqtb[12180].int_);
      f = ((f * 1000) + (ctx->remainder_ * 65536)) / ctx->eqtb[12180].int_;
      ctx->cur_val += f / 65536;
      f &= 65535;
    }
  }
  if (scan_keyword(ctx, 397))
    goto _L88;
  if (scan_keyword(ctx, 715)) {
    num = 7227;
    denom = 100;
  } else if (scan_keyword(ctx, 716)) {
    num = 12;
    denom = 1;
  } else if (scan_keyword(ctx, 717)) {
    num = 7227;
    denom = 254;
  } else if (scan_keyword(ctx, 718)) {
    num = 7227;
    denom = 2540;
  } else if (scan_keyword(ctx, 719)) {
    num = 7227;
    denom = 7200;
  } else if (scan_keyword(ctx, 720)) {
    num = 1238;
    denom = 1157;
  } else if (scan_keyword(ctx, 721)) {
    num = 14856;
    denom = 1157;
  } else if (scan_keyword(ctx, 722)) {
    goto _L30;
  } else {
    print_nl(ctx, 262);
    print(ctx, 705);
    print(ctx, 723);
    ctx->help_ptr = 6;
    ctx->help_line[5] = 724;
    ctx->help_line[4] = 725;
    ctx->help_line[3] = 726;
    ctx->help_line[2] = 712;
    ctx->help_line[1] = 713;
    ctx->help_line[0] = 714;
    error(ctx);
    goto _L32;
  }
  ctx->cur_val = xn_over_d(ctx, ctx->cur_val, num, denom);
  f = ((num * f) + (ctx->remainder_ * 65536)) / denom;
  ctx->cur_val += f / 65536;
  f &= 65535;
_L32:
_L88:
  if (ctx->cur_val >= 16384)
    ctx->arith_error = true;
  else
    ctx->cur_val = (ctx->cur_val * 65536) + f;
_L30:
  get_x_token(ctx);
  if (ctx->cur_cmd != 10)
    back_input(ctx);
_L89:
  if (ctx->arith_error || (abs(ctx->cur_val) >= 1073741824)) {
    print_nl(ctx, 262);
    print(ctx, 727);
    ctx->help_ptr = 2;
    ctx->help_line[1] = 728;
    ctx->help_line[0] = 729;
    error(ctx);
    ctx->cur_val = 1073741823;
    ctx->arith_error = false;
  }
  if (negative)
    ctx->cur_val = -ctx->cur_val;
}

void scan_glue(ctex_t *ctx, small_number level) {
  bool_t negative = false;
  halfword q;
  bool_t mu = level == 3;
  do {
    do {
      get_x_token(ctx);
    } while (ctx->cur_cmd == 10);
    if (ctx->cur_tok == 3117) {
      negative = !negative;
      ctx->cur_tok = 3115;
    }
  } while (ctx->cur_tok == 3115);
  if ((ctx->cur_cmd >= 68) && (ctx->cur_cmd <= 89)) {
    scan_something_internal(ctx, level, negative);
    if (ctx->cur_val_level >= 2) {
      if (ctx->cur_val_level != level)
        mu_error(ctx);
      goto _L10;
    }
    if (!ctx->cur_val_level) {
      scan_dimen(ctx, mu, false, true);
    } else if (level == 3)
      mu_error(ctx);
  } else {
    back_input(ctx);
    scan_dimen(ctx, mu, false, false);
    if (negative)
      ctx->cur_val = -ctx->cur_val;
  }
  q = new_spec(ctx, 0);
  ctx->mem[q - mem_min + 1].int_ = ctx->cur_val;
  if (scan_keyword(ctx, 730)) {
    scan_dimen(ctx, mu, true, false);
    ctx->mem[q - mem_min + 2].int_ = ctx->cur_val;
    ctx->mem[q - mem_min].hh.U2.b0 = ctx->cur_order;
  }
  if (scan_keyword(ctx, 731)) {
    scan_dimen(ctx, mu, true, false);
    ctx->mem[q - mem_min + 3].int_ = ctx->cur_val;
    ctx->mem[q - mem_min].hh.U2.b1 = ctx->cur_order;
  }
  ctx->cur_val = q;
_L10:;
}

halfword scan_rule_spec(ctex_t *ctx) {
  halfword q = new_rule(ctx);
  if (ctx->cur_cmd == 35) {
    ctx->mem[q - mem_min + 1].int_ = 26214;
  } else {
    ctx->mem[q - mem_min + 3].int_ = 26214;
    ctx->mem[q - mem_min + 2].int_ = 0;
  }
_L21:
  if (scan_keyword(ctx, 732)) {
    scan_dimen(ctx, false, false, false);
    ctx->mem[q - mem_min + 1].int_ = ctx->cur_val;
    goto _L21;
  }
  if (scan_keyword(ctx, 733)) {
    scan_dimen(ctx, false, false, false);
    ctx->mem[q - mem_min + 3].int_ = ctx->cur_val;
    goto _L21;
  }
  if (!scan_keyword(ctx, 734))
    return q;
  scan_dimen(ctx, false, false, false);
  ctx->mem[q - mem_min + 2].int_ = ctx->cur_val;
  goto _L21;
}

halfword str_toks(ctex_t *ctx, pool_pointer b) {
  halfword p = mem_max - 3, q, t;
  pool_pointer k;
  if (ctx->pool_ptr + 1 > pool_size)
    overflow(ctx, 257, pool_size - ctx->init_pool_ptr);
  ctx->mem[p - mem_min].hh.rh = -1073741824;
  k = b;
  while (k < ctx->pool_ptr) {
    t = ctx->str_pool[k];
    if (t == 32)
      t = 2592;
    else
      t += 3072;
    q = ctx->avail;
    if (q == (-1073741824)) {
      q = get_avail(ctx);
    } else {
      ctx->avail = ctx->mem[q - mem_min].hh.rh;
      ctx->mem[q - mem_min].hh.rh = -1073741824;
    }
    ctx->mem[p - mem_min].hh.rh = q;
    ctx->mem[q - mem_min].hh.lh = t;
    p = q;
    ++k;
  }
  ctx->pool_ptr = b;
  return p;
}

halfword the_toks(ctex_t *ctx) {
  char old_setting;
  halfword p, q, r;
  pool_pointer b;
  get_x_token(ctx);
  scan_something_internal(ctx, 5, false);
  if (ctx->cur_val_level >= 4) {
    p = mem_max - 3;
    ctx->mem[p - mem_min].hh.rh = -1073741824;
    if (ctx->cur_val_level == 4) {
      q = get_avail(ctx);
      ctx->mem[p - mem_min].hh.rh = q;
      ctx->mem[q - mem_min].hh.lh = ctx->cur_val + 4095;
      p = q;
      return p;
    }
    if (ctx->cur_val == (-1073741824))
      return p;
    r = ctx->mem[ctx->cur_val - mem_min].hh.rh;
    while (r != (-1073741824)) {
      q = ctx->avail;
      if (q == (-1073741824)) {
        q = get_avail(ctx);
      } else {
        ctx->avail = ctx->mem[q - mem_min].hh.rh;
        ctx->mem[q - mem_min].hh.rh = -1073741824;
      }
      ctx->mem[p - mem_min].hh.rh = q;
      ctx->mem[q - mem_min].hh.lh = ctx->mem[r - mem_min].hh.lh;
      p = q;
      r = ctx->mem[r - mem_min].hh.rh;
    }
    return p;
  } else {
    old_setting = ctx->selector;
    ctx->selector = 21;
    b = ctx->pool_ptr;
    switch (ctx->cur_val_level) {
    case 0:
      print_int(ctx, ctx->cur_val);
      break;
    case 1:
      print_scaled(ctx, ctx->cur_val);
      print(ctx, 397);
      break;
    case 2:
      print_spec(ctx, ctx->cur_val, 397);
      delete_glue_ref(ctx, ctx->cur_val);
      break;
    case 3:
      print_spec(ctx, ctx->cur_val, 337);
      delete_glue_ref(ctx, ctx->cur_val);
      break;
    }
    ctx->selector = old_setting;
    return str_toks(ctx, b);
  }
}

void ins_the_toks(ctex_t *ctx) {
  ctx->mem[mem_max - mem_min - 12].hh.rh = the_toks(ctx);
  begin_token_list(ctx, ctx->mem[mem_max - mem_min - 3].hh.rh, 4);
}

void conv_toks(ctex_t *ctx) {
  char old_setting;
  small_number save_scanner_status;
  pool_pointer b;
  char c = ctx->cur_chr;
  switch (c) {
  case 0:
  case 1:
    scan_int(ctx);
    break;
  case 2:
  case 3:
    save_scanner_status = ctx->scanner_status;
    ctx->scanner_status = 0;
    get_token(ctx);
    ctx->scanner_status = save_scanner_status;
    break;
  case 4:
    scan_font_ident(ctx);
    break;
  case 5:
    if (!ctx->job_name)
      open_log_file(ctx);
    break;
  }
  old_setting = ctx->selector;
  ctx->selector = 21;
  b = ctx->pool_ptr;
  switch (c) {
  case 0:
    print_int(ctx, ctx->cur_val);
    break;
  case 1:
    print_roman_int(ctx, ctx->cur_val);
    break;
  case 2:
    if (ctx->cur_cs)
      sprint_cs(ctx, ctx->cur_cs);
    else
      print_char(ctx, ctx->cur_chr);
    break;
  case 3:
    print_meaning(ctx);
    break;
  case 4:
    print(ctx, ctx->fnt_infos.font_name[ctx->cur_val]);
    if (ctx->fnt_infos.font_size[ctx->cur_val] !=
        ctx->fnt_infos.font_dsize[ctx->cur_val]) {
      print(ctx, 741);
      print_scaled(ctx, ctx->fnt_infos.font_size[ctx->cur_val]);
      print(ctx, 397);
    }
    break;
  case 5:
    print(ctx, ctx->job_name);
    break;
  }
  ctx->selector = old_setting;
  ctx->mem[mem_max - mem_min - 12].hh.rh = str_toks(ctx, b);
  begin_token_list(ctx, ctx->mem[mem_max - mem_min - 3].hh.rh, 4);
}

halfword scan_toks(ctex_t *ctx, bool_t macro_def, bool_t xpand) {
  halfword t = 3120, s, p, q, unbalance = 1, hash_brace = 0;
  if (macro_def)
    ctx->scanner_status = 2;
  else
    ctx->scanner_status = 5;
  ctx->warning_index = ctx->cur_cs;
  ctx->def_ref = get_avail(ctx);
  ctx->mem[ctx->def_ref - mem_min].hh.lh = -1073741824;
  p = ctx->def_ref;
  if (macro_def) {
    while (true) {
      get_token(ctx);
      if (ctx->cur_tok < 768)
        goto _L31;
      if (ctx->cur_cmd == 6) {
        s = ctx->cur_chr + 3328;
        get_token(ctx);
        if (ctx->cur_cmd == 1) {
          hash_brace = ctx->cur_tok;
          q = get_avail(ctx);
          ctx->mem[p - mem_min].hh.rh = q;
          ctx->mem[q - mem_min].hh.lh = ctx->cur_tok;
          p = q;
          q = get_avail(ctx);
          ctx->mem[p - mem_min].hh.rh = q;
          ctx->mem[q - mem_min].hh.lh = 3584;
          p = q;
          goto _L30;
        }
        if (t == 3129) {
          print_nl(ctx, 262);
          print(ctx, 744);
          ctx->help_ptr = 1;
          ctx->help_line[0] = 745;
          error(ctx);
        } else {
          ++t;
          if (ctx->cur_tok != t) {
            print_nl(ctx, 262);
            print(ctx, 746);
            ctx->help_ptr = 2;
            ctx->help_line[1] = 747;
            ctx->help_line[0] = 748;
            back_error(ctx);
          }
          ctx->cur_tok = s;
        }
      }
      q = get_avail(ctx);
      ctx->mem[p - mem_min].hh.rh = q;
      ctx->mem[q - mem_min].hh.lh = ctx->cur_tok;
      p = q;
    }
  _L31:
    q = get_avail(ctx);
    ctx->mem[p - mem_min].hh.rh = q;
    ctx->mem[q - mem_min].hh.lh = 3584;
    p = q;
    if (ctx->cur_cmd == 2) {
      print_nl(ctx, 262);
      print(ctx, 657);
      ++ctx->align_state;
      ctx->help_ptr = 2;
      ctx->help_line[1] = 742;
      ctx->help_line[0] = 743;
      error(ctx);
      goto _L40;
    }
  _L30:;
  } else {
    scan_left_brace(ctx);
  }
  while (true) {
    if (xpand) {
      while (true) {
        get_next(ctx);
        if (ctx->cur_cmd <= 100)
          goto _L32;
        if (ctx->cur_cmd != 109) {
          expand(ctx);
        } else {
          q = the_toks(ctx);
          if (ctx->mem[mem_max - mem_min - 3].hh.rh != (-1073741824)) {
            ctx->mem[p - mem_min].hh.rh = ctx->mem[mem_max - mem_min - 3].hh.rh;
            p = q;
          }
        }
      }
    _L32:
      x_token(ctx);
    } else {
      get_token(ctx);
    }
    if (ctx->cur_tok < 768) {
      if (ctx->cur_cmd < 2) {
        ++unbalance;
      } else {
        --unbalance;
        if (!unbalance)
          goto _L40;
      }
    } else if (ctx->cur_cmd == 6) {
      if (macro_def) {
        s = ctx->cur_tok;
        if (xpand)
          get_x_token(ctx);
        else
          get_token(ctx);
        if (ctx->cur_cmd != 6) {
          if ((ctx->cur_tok <= 3120) || (ctx->cur_tok > t)) {
            print_nl(ctx, 262);
            print(ctx, 749);
            sprint_cs(ctx, ctx->warning_index);
            ctx->help_ptr = 3;
            ctx->help_line[2] = 750;
            ctx->help_line[1] = 751;
            ctx->help_line[0] = 752;
            back_error(ctx);
            ctx->cur_tok = s;
          } else {
            ctx->cur_tok = ctx->cur_chr + 1232;
          }
        }
      }
    }
    q = get_avail(ctx);
    ctx->mem[p - mem_min].hh.rh = q;
    ctx->mem[q - mem_min].hh.lh = ctx->cur_tok;
    p = q;
  }
_L40:
  ctx->scanner_status = 0;
  if (!hash_brace)
    return p;
  q = get_avail(ctx);
  ctx->mem[p - mem_min].hh.rh = q;
  ctx->mem[q - mem_min].hh.lh = hash_brace;
  p = q;
  return p;
}

void read_toks(ctex_t *ctx, integer n, halfword r) {
  halfword p, q;
  integer s;
  small_number m;
  ctx->scanner_status = 2;
  ctx->warning_index = r;
  ctx->def_ref = get_avail(ctx);
  ctx->mem[ctx->def_ref - mem_min].hh.lh = -1073741824;
  p = ctx->def_ref;
  q = get_avail(ctx);
  ctx->mem[p - mem_min].hh.rh = q;
  ctx->mem[q - mem_min].hh.lh = 3584;
  p = q;
  if (((unsigned)n) > 15)
    m = 16;
  else
    m = n;
  s = ctx->align_state;
  ctx->align_state = 1000000;
  do {
    begin_file_reading(ctx);
    ctx->cur_input.name_field = m + 1;
    if (ctx->read_open[m] == 2) {
      if (ctx->interaction > 1) {
        if (n < 0) {
          print(ctx, 338);
          term_input(ctx);
        } else {
          print_ln(ctx);
          sprint_cs(ctx, r);
          print(ctx, 61);
          term_input(ctx);
          n = -1;
        }
      } else {
        fatal_error(ctx, 753);
      }
    } else if (ctx->read_open[m] == 1) {
      if (input_ln(ctx, ctx->read_file[m], false)) {
        ctx->read_open[m] = 0;
      } else {
        a_close(ctx, &ctx->read_file[m]);
        ctx->read_open[m] = 2;
      }
    } else if (!input_ln(ctx, ctx->read_file[m], true)) {
      a_close(ctx, &ctx->read_file[m]);
      ctx->read_open[m] = 2;
      if (ctx->align_state != 1000000) {
        runaway(ctx);
        print_nl(ctx, 262);
        print(ctx, 754);
        print_esc(ctx, 534);
        ctx->help_ptr = 1;
        ctx->help_line[0] = 755;
        ctx->align_state = 1000000;
        error(ctx);
      }
    }
    ctx->cur_input.limit_field = ctx->last;
    if (((unsigned)ctx->eqtb[12211].int_) > 255)
      --ctx->cur_input.limit_field;
    else
      ctx->buffer[ctx->cur_input.limit_field] = ctx->eqtb[12211].int_;
    ctx->first = ctx->cur_input.limit_field + 1;
    ctx->cur_input.loc_field = ctx->cur_input.start_field;
    ctx->cur_input.state_field = 33;
    while (true) {
      get_token(ctx);
      if (!ctx->cur_tok)
        goto _L30;
      if (ctx->align_state < 1000000) {
        do {
          get_token(ctx);
        } while (ctx->cur_tok);
        ctx->align_state = 1000000;
        goto _L30;
      }
      q = get_avail(ctx);
      ctx->mem[p - mem_min].hh.rh = q;
      ctx->mem[q - mem_min].hh.lh = ctx->cur_tok;
      p = q;
    }
  _L30:
    end_file_reading(ctx);
  } while (ctx->align_state != 1000000);
  ctx->cur_val = ctx->def_ref;
  ctx->scanner_status = 0;
  ctx->align_state = s;
}

void pass_text(ctex_t *ctx) {
  integer l = 0;
  small_number save_scanner_status = ctx->scanner_status;
  ctx->scanner_status = 1;
  ctx->skip_line = ctx->line;
  while (true) {
    get_next(ctx);
    if (ctx->cur_cmd == 106) {
      if (!l)
        goto _L30;
      if (ctx->cur_chr == 2)
        --l;
    } else if (ctx->cur_cmd == 105)
      ++l;
  }
_L30:
  ctx->scanner_status = save_scanner_status;
}

void change_if_limit(ctex_t *ctx, small_number l, halfword p) {
  halfword q;
  if (p == ctx->cond_ptr) {
    ctx->if_limit = l;
  } else {
    q = ctx->cond_ptr;
    while (true) {
      if (q == (-1073741824))
        confusion(ctx, 756);
      if (ctx->mem[q - mem_min].hh.rh == p) {
        ctx->mem[q - mem_min].hh.U2.b0 = l;
        goto _L10;
      }
      q = ctx->mem[q - mem_min].hh.rh;
    }
  }
_L10:;
}

void conditional(ctex_t *ctx) {
  bool_t b;
  char r;
  integer m, n;
  halfword q;
  small_number save_scanner_status;
  halfword save_cond_ptr;
  small_number this_if;
  halfword p = get_node(ctx, 2);
  ctx->mem[p - mem_min].hh.rh = ctx->cond_ptr;
  ctx->mem[p - mem_min].hh.U2.b0 = ctx->if_limit;
  ctx->mem[p - mem_min].hh.U2.b1 = ctx->cur_if;
  ctx->mem[p - mem_min + 1].int_ = ctx->if_line;
  ctx->cond_ptr = p;
  ctx->cur_if = ctx->cur_chr;
  ctx->if_limit = 1;
  ctx->if_line = ctx->line;
  save_cond_ptr = ctx->cond_ptr;
  this_if = ctx->cur_chr;
  switch (this_if) {
  case 0:
  case 1:
    get_x_token(ctx);
    if (!ctx->cur_cmd) {
      if (ctx->cur_chr == 257) {
        ctx->cur_cmd = 13;
        ctx->cur_chr = ctx->cur_tok - 4096;
      }
    }
    if ((ctx->cur_cmd > 13) || (ctx->cur_chr > 255)) {
      m = 0;
      n = 256;
    } else {
      m = ctx->cur_cmd;
      n = ctx->cur_chr;
    }
    get_x_token(ctx);
    if (!ctx->cur_cmd) {
      if (ctx->cur_chr == 257) {
        ctx->cur_cmd = 13;
        ctx->cur_chr = ctx->cur_tok - 4096;
      }
    }
    if ((ctx->cur_cmd > 13) || (ctx->cur_chr > 255)) {
      ctx->cur_cmd = 0;
      ctx->cur_chr = 256;
    }
    if (!this_if)
      b = (n == ctx->cur_chr);
    else
      b = (m == ctx->cur_cmd);
    break;
  case 2:
  case 3:
    if (this_if == 2)
      scan_int(ctx);
    else
      scan_dimen(ctx, false, false, false);
    n = ctx->cur_val;
    do {
      get_x_token(ctx);
    } while (ctx->cur_cmd == 10);
    if ((ctx->cur_tok >= 3132) && (ctx->cur_tok <= 3134)) {
      r = ctx->cur_tok - 3072;
    } else {
      print_nl(ctx, 262);
      print(ctx, 780);
      print_cmd_chr(ctx, 105, this_if);
      ctx->help_ptr = 1;
      ctx->help_line[0] = 781;
      back_error(ctx);
      r = 61;
    }
    if (this_if == 2)
      scan_int(ctx);
    else
      scan_dimen(ctx, false, false, false);
    switch (r) {
    case 60:
      b = (n < ctx->cur_val);
      break;
    case 61:
      b = (n == ctx->cur_val);
      break;
    case 62:
      b = (n > ctx->cur_val);
      break;
    }
    break;
  case 4:
    scan_int(ctx);
    b = ctx->cur_val & 1;
    break;
  case 5:
    b = (abs(ctx->cur_list.mode_field) == 1);
    break;
  case 6:
    b = (abs(ctx->cur_list.mode_field) == 102);
    break;
  case 7:
    b = (abs(ctx->cur_list.mode_field) == 203);
    break;
  case 8:
    b = (ctx->cur_list.mode_field < 0);
    break;
  case 9:
  case 10:
  case 11:
    scan_eight_bit_int(ctx);
    p = ctx->eqtb[ctx->cur_val + 10578].hh.rh;
    if (this_if == 9) {
      b = (p == (-1073741824));
    } else if (p == (-1073741824)) {
      b = false;
    } else if (this_if == 10)
      b = (ctx->mem[p - mem_min].hh.U2.b0 == 0);
    else
      b = (ctx->mem[p - mem_min].hh.U2.b0 == 1);
    break;
  case 12:
    save_scanner_status = ctx->scanner_status;
    ctx->scanner_status = 0;
    get_next(ctx);
    n = ctx->cur_cs;
    p = ctx->cur_cmd;
    q = ctx->cur_chr;
    get_next(ctx);
    if (ctx->cur_cmd != p) {
      b = false;
    } else if (ctx->cur_cmd < 111) {
      b = (ctx->cur_chr == q);
    } else {
      p = ctx->mem[ctx->cur_chr - mem_min].hh.rh;
      q = ctx->mem[ctx->eqtb[n].hh.rh - mem_min].hh.rh;
      if (p == q) {
        b = true;
      } else {
        while ((p != (-1073741824)) && (q != (-1073741824))) {
          if (ctx->mem[p - mem_min].hh.lh != ctx->mem[q - mem_min].hh.lh) {
            p = -1073741824;
          } else {
            p = ctx->mem[p - mem_min].hh.rh;
            q = ctx->mem[q - mem_min].hh.rh;
          }
        }
        b = ((p == (-1073741824)) && (q == (-1073741824)));
      }
    }
    ctx->scanner_status = save_scanner_status;
    break;
  case 13:
    scan_four_bit_int(ctx);
    b = (ctx->read_open[ctx->cur_val] == 2);
    break;
  case 14:
    b = true;
    break;
  case 15:
    b = false;
    break;
  case 16:
    scan_int(ctx);
    n = ctx->cur_val;
    if (ctx->eqtb[12199].int_ > 1) {
      begin_diagnostic(ctx);
      print(ctx, 782);
      print_int(ctx, n);
      print_char(ctx, 125);
      end_diagnostic(ctx, false);
    }
    while (n) {
      pass_text(ctx);
      if (ctx->cond_ptr == save_cond_ptr) {
        if (ctx->cur_chr != 4)
          goto _L50;
        --n;
        continue;
      }
      if (ctx->cur_chr != 2)
        continue;
      p = ctx->cond_ptr;
      ctx->if_line = ctx->mem[p - mem_min + 1].int_;
      ctx->cur_if = ctx->mem[p - mem_min].hh.U2.b1;
      ctx->if_limit = ctx->mem[p - mem_min].hh.U2.b0;
      ctx->cond_ptr = ctx->mem[p - mem_min].hh.rh;
      free_node(ctx, p, 2);
    }
    change_if_limit(ctx, 4, save_cond_ptr);
    goto _L10;
    break;
  }
  if (ctx->eqtb[12199].int_ > 1) {
    begin_diagnostic(ctx);
    if (b)
      print(ctx, 778);
    else
      print(ctx, 779);
    end_diagnostic(ctx, false);
  }
  if (b) {
    change_if_limit(ctx, 3, save_cond_ptr);
    goto _L10;
  }
  while (true) {
    pass_text(ctx);
    if (ctx->cond_ptr == save_cond_ptr) {
      if (ctx->cur_chr != 4)
        goto _L50;
      print_nl(ctx, 262);
      print(ctx, 776);
      print_esc(ctx, 774);
      ctx->help_ptr = 1;
      ctx->help_line[0] = 777;
      error(ctx);
      continue;
    }
    if (ctx->cur_chr != 2)
      continue;
    p = ctx->cond_ptr;
    ctx->if_line = ctx->mem[p - mem_min + 1].int_;
    ctx->cur_if = ctx->mem[p - mem_min].hh.U2.b1;
    ctx->if_limit = ctx->mem[p - mem_min].hh.U2.b0;
    ctx->cond_ptr = ctx->mem[p - mem_min].hh.rh;
    free_node(ctx, p, 2);
  }
_L50:
  if (ctx->cur_chr == 2) {
    p = ctx->cond_ptr;
    ctx->if_line = ctx->mem[p - mem_min + 1].int_;
    ctx->cur_if = ctx->mem[p - mem_min].hh.U2.b1;
    ctx->if_limit = ctx->mem[p - mem_min].hh.U2.b0;
    ctx->cond_ptr = ctx->mem[p - mem_min].hh.rh;
    free_node(ctx, p, 2);
  } else {
    ctx->if_limit = 2;
  }
_L10:;
}

void begin_name(ctex_t *ctx) {
  ctx->area_delimiter = 0;
  ctx->ext_delimiter = 0;
}

bool_t more_name(ctex_t *ctx, ASCII_code c) {
  if (c == 32) {
    return false;
  } else {
    if (ctx->pool_ptr + 1 > pool_size)
      overflow(ctx, 257, pool_size - ctx->init_pool_ptr);
    ctx->str_pool[ctx->pool_ptr] = c;
    ++ctx->pool_ptr;
    if ((c == 62) || (c == 58)) {
      ctx->area_delimiter = ctx->pool_ptr - ctx->str_start[ctx->str_ptr];
      ctx->ext_delimiter = 0;
    } else if ((c == 46) && (!ctx->ext_delimiter))
      ctx->ext_delimiter = ctx->pool_ptr - ctx->str_start[ctx->str_ptr];
    return true;
  }
}

void end_name(ctex_t *ctx) {
  if (ctx->str_ptr + 3 > max_strings)
    overflow(ctx, 258, max_strings - ctx->init_str_ptr);
  if (!ctx->area_delimiter) {
    ctx->cur_area = 338;
  } else {
    ctx->cur_area = ctx->str_ptr;
    ctx->str_start[ctx->str_ptr + 1] =
        ctx->str_start[ctx->str_ptr] + ctx->area_delimiter;
    ++ctx->str_ptr;
  }
  if (!ctx->ext_delimiter) {
    ctx->cur_ext = 338;
    ctx->cur_name = make_string(ctx);
    return;
  }
  ctx->cur_name = ctx->str_ptr;
  ctx->str_start[ctx->str_ptr + 1] = ctx->str_start[ctx->str_ptr] +
                                     ctx->ext_delimiter - ctx->area_delimiter -
                                     1;
  ++ctx->str_ptr;
  ctx->cur_ext = make_string(ctx);
}

void pack_file_name(ctex_t *ctx, str_number n, str_number a, str_number e) {
  integer k = 0;
  ASCII_code c;
  pool_pointer j, N1;
  for (N1 = ctx->str_start[a + 1], j = ctx->str_start[a]; j <= (N1 - 1); ++j) {
    c = ctx->str_pool[j];
    ++k;
    if (k <= file_name_size)
      ctx->name_of_file[k - 1] = ctx->xchr[c];
  }
  for (N1 = ctx->str_start[n + 1], j = ctx->str_start[n]; j <= (N1 - 1); ++j) {
    c = ctx->str_pool[j];
    ++k;
    if (k <= file_name_size)
      ctx->name_of_file[k - 1] = ctx->xchr[c];
  }
  for (N1 = ctx->str_start[e + 1], j = ctx->str_start[e]; j <= (N1 - 1); ++j) {
    c = ctx->str_pool[j];
    ++k;
    if (k <= file_name_size)
      ctx->name_of_file[k - 1] = ctx->xchr[c];
  }
  if (k <= file_name_size)
    ctx->name_length = k;
  else
    ctx->name_length = file_name_size;
  for (k = ctx->name_length + 1; k <= file_name_size; ++k)
    ctx->name_of_file[k - 1] = ' ';
}

void pack_buffered_name(ctex_t *ctx, small_number n, integer a, integer b) {
  integer k = 0, j;
  ASCII_code c;
  if (n + b - a + 5 > file_name_size)
    b = a + file_name_size - n - 5;
  for (j = 1; j <= n; ++j) {
    c = ctx->xord[ctx->TEX_format_default[j - 1]];
    ++k;
    if (k <= file_name_size)
      ctx->name_of_file[k - 1] = ctx->xchr[c];
  }
  for (j = a; j <= b; ++j) {
    c = ctx->buffer[j];
    ++k;
    if (k <= file_name_size)
      ctx->name_of_file[k - 1] = ctx->xchr[c];
  }
  for (j = 17; j <= 20; ++j) {
    c = ctx->xord[ctx->TEX_format_default[j - 1]];
    ++k;
    if (k <= file_name_size)
      ctx->name_of_file[k - 1] = ctx->xchr[c];
  }
  if (k <= file_name_size)
    ctx->name_length = k;
  else
    ctx->name_length = file_name_size;
  for (k = ctx->name_length + 1; k <= file_name_size; ++k)
    ctx->name_of_file[k - 1] = ' ';
}

str_number make_name_string(ctex_t *ctx) {
  int k, N;
  if ((ctx->pool_ptr + ctx->name_length > pool_size) ||
      (ctx->str_ptr == max_strings) ||
      (ctx->pool_ptr - ctx->str_start[ctx->str_ptr] > 0)) {
    return 63;
  } else {
    for (N = ctx->name_length, k = 1; k <= N; ++k) {
      ctx->str_pool[ctx->pool_ptr] = ctx->xord[ctx->name_of_file[k - 1]];
      ++ctx->pool_ptr;
    }
    return make_string(ctx);
  }
}

str_number a_make_name_string(ctex_t *ctx, FILE *f) {
  return make_name_string(ctx);
}

str_number b_make_name_string(ctex_t *ctx, FILE *f) {
  return make_name_string(ctx);
}

str_number w_make_name_string(ctex_t *ctx, FILE *f) {
  return make_name_string(ctx);
}

void scan_file_name(ctex_t *ctx) {
  ctx->name_in_progress = true;
  begin_name(ctx);
  do {
    get_x_token(ctx);
  } while (ctx->cur_cmd == 10);
  while (true) {
    if ((ctx->cur_cmd > 12) || (ctx->cur_chr > 255)) {
      back_input(ctx);
      goto _L30;
    }
    if (!more_name(ctx, ctx->cur_chr))
      goto _L30;
    get_x_token(ctx);
  }
_L30:
  end_name(ctx);
  ctx->name_in_progress = false;
}

void pack_job_name(ctex_t *ctx, str_number s) {
  ctx->cur_area = 338;
  ctx->cur_ext = s;
  ctx->cur_name = ctx->job_name;
  pack_file_name(ctx, ctx->cur_name, ctx->cur_area, ctx->cur_ext);
}

void prompt_file_name(ctex_t *ctx, str_number s, str_number e) {
  int k;
  if (s == 786) {
    print_nl(ctx, 262);
    print(ctx, 787);
  } else {
    print_nl(ctx, 262);
    print(ctx, 788);
  }
  print_file_name(ctx, ctx->cur_name, ctx->cur_area, ctx->cur_ext);
  print(ctx, 789);
  if (e == 790)
    show_context(ctx);
  print_nl(ctx, 791);
  print(ctx, s);
  if (ctx->interaction < 2)
    fatal_error(ctx, 792);
  break_in(ctx->term_in, true);
  print(ctx, 568);
  term_input(ctx);
  begin_name(ctx);
  k = ctx->first;
  while ((ctx->buffer[k] == 32) && (k < ctx->last))
    ++k;
  while (true) {
    if (k == ctx->last)
      goto _L30;
    if (!more_name(ctx, ctx->buffer[k]))
      goto _L30;
    ++k;
  }
_L30:
  end_name(ctx);
  if (ctx->cur_ext == 338)
    ctx->cur_ext = e;
  pack_file_name(ctx, ctx->cur_name, ctx->cur_area, ctx->cur_ext);
}

void open_log_file(ctex_t *ctx) {
  int k, l;
  char months[36];
  int N;
  char old_setting = ctx->selector;
  if (!ctx->job_name)
    ctx->job_name = 795;
  pack_job_name(ctx, 796);
  while (!a_open_out(ctx, &ctx->log_file)) {
    ctx->selector = 17;
    prompt_file_name(ctx, 798, 796);
  }
  ctx->log_name = a_make_name_string(ctx, ctx->log_file);
  ctx->selector = 18;
  ctx->log_opened = true;
  fprintf(ctx->log_file, "This is TeX, Version 3.14159265");
  slow_print(ctx, ctx->format_ident);
  print(ctx, 799);
  print_int(ctx, ctx->eqtb[12184].int_);
  print_char(ctx, 32);
  memcpy(months, "JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC", 36);
  for (N = ctx->eqtb[12185].int_ * 3, k = (ctx->eqtb[12185].int_ * 3) - 2;
       k <= N; ++k)
    fprintf(ctx->log_file, "%c", months[k - 1]);
  print_char(ctx, 32);
  print_int(ctx, ctx->eqtb[12186].int_);
  print_char(ctx, 32);
  print_two(ctx, ctx->eqtb[12183].int_ / 60);
  print_char(ctx, 58);
  print_two(ctx, ctx->eqtb[12183].int_ % 60);
  ctx->input_stack[ctx->input_ptr] = ctx->cur_input;
  print_nl(ctx, 797);
  l = ctx->input_stack[0].limit_field;
  if (ctx->buffer[l] == ctx->eqtb[12211].int_)
    --l;
  for (k = 1; k <= l; ++k)
    print(ctx, ctx->buffer[k]);
  print_ln(ctx);
  ctx->selector = old_setting + 2;
}

void start_input(ctex_t *ctx) {
  scan_file_name(ctx);
  if (ctx->cur_ext == 338)
    ctx->cur_ext = 790;
  pack_file_name(ctx, ctx->cur_name, ctx->cur_area, ctx->cur_ext);
  while (true) {
    begin_file_reading(ctx);
    if (a_open_in(ctx, &ctx->input_file[ctx->cur_input.index_field]))
      goto _L30;
    if (ctx->cur_area == 338) {
      pack_file_name(ctx, ctx->cur_name, 783, ctx->cur_ext);
      if (a_open_in(ctx, &ctx->input_file[ctx->cur_input.index_field]))
        goto _L30;
    }
    end_file_reading(ctx);
    prompt_file_name(ctx, 786, 790);
  }
_L30:
  ctx->cur_input.name_field =
      a_make_name_string(ctx, ctx->input_file[ctx->cur_input.index_field]);
  if (!ctx->job_name) {
    ctx->job_name = ctx->cur_name;
    open_log_file(ctx);
  }
  if (ctx->term_offset + ctx->str_start[ctx->cur_input.name_field + 1] -
          ctx->str_start[ctx->cur_input.name_field] >
      max_print_line - 2) {
    print_ln(ctx);
  } else if ((ctx->term_offset > 0) || (ctx->file_offset > 0))
    print_char(ctx, 32);
  print_char(ctx, 40);
  ++ctx->open_parens;
  slow_print(ctx, ctx->cur_input.name_field);
  fflush(ctx->term_out);
  errno = 0;
  ctx->cur_input.state_field = 33;
  if (ctx->cur_input.name_field == (ctx->str_ptr - 1)) {
    --ctx->str_ptr;
    ctx->pool_ptr = ctx->str_start[ctx->str_ptr];
    ctx->cur_input.name_field = ctx->cur_name;
  }
  ctx->line = 1;
  input_ln(ctx, ctx->input_file[ctx->cur_input.index_field], false);
  firm_up_the_line(ctx);
  if (((unsigned)ctx->eqtb[12211].int_) > 255)
    --ctx->cur_input.limit_field;
  else
    ctx->buffer[ctx->cur_input.limit_field] = ctx->eqtb[12211].int_;
  ctx->first = ctx->cur_input.limit_field + 1;
  ctx->cur_input.loc_field = ctx->cur_input.start_field;
}

internal_font_number read_font_info(ctex_t *ctx, halfword u, str_number nom,
                                    str_number aire, scaled s) {
  font_index k;
  bool_t file_opened = false;
  halfword lf, lh, bc, ec, nw, nh, nd, ni, nl, nk, ne, np;
  internal_font_number f, g = 0;
  uint8_t a, b, c, d;
  four_quarters qw;
  scaled sw, z;
  integer bch_label = 32767, alpha = 16;
  short bchar = 256;
  char beta;
  font_index N;
  if (aire == 338)
    pack_file_name(ctx, nom, 784, 810);
  else
    pack_file_name(ctx, nom, aire, 810);
  if (!b_open_in(ctx, &ctx->tfm_file))
    goto _L11;
  file_opened = true;
  ctx->tfm_file_mode = 1;
  lf = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (lf > 127)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  lf = (lf * 256) +
       *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  lh = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (lh > 127)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  lh = (lh * 256) +
       *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  bc = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (bc > 127)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  bc = (bc * 256) +
       *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  ec = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (ec > 127)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  ec = (ec * 256) +
       *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if ((bc > (ec + 1)) || (ec > 255))
    goto _L11;
  if (bc > 255) {
    bc = 1;
    ec = 0;
  }
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  nw = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (nw > 127)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  nw = (nw * 256) +
       *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  nh = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (nh > 127)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  nh = (nh * 256) +
       *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  nd = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (nd > 127)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  nd = (nd * 256) +
       *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  ni = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (ni > 127)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  ni = (ni * 256) +
       *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  nl = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (nl > 127)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  nl = (nl * 256) +
       *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  nk = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (nk > 127)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  nk = (nk * 256) +
       *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  ne = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (ne > 127)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  ne = (ne * 256) +
       *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  np = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (np > 127)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  np = (np * 256) +
       *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (lf != (lh + ec - bc + nw + nh + nd + ni + nl + nk + ne + np + 7))
    goto _L11;
  if ((!nw) || (!nh) || (!nd) || (!ni))
    goto _L11;
  lf += (-lh) - 6;
  if (np < 7)
    lf += 7 - np;
  if ((ctx->font_ptr == font_max) || (ctx->fmem_ptr + lf > font_mem_size)) {
    print_nl(ctx, 262);
    print(ctx, 801);
    sprint_cs(ctx, u);
    print_char(ctx, 61);
    print_file_name(ctx, nom, aire, 338);
    if (s >= 0) {
      print(ctx, 741);
      print_scaled(ctx, s);
      print(ctx, 397);
    } else if (s != (-1000)) {
      print(ctx, 802);
      print_int(ctx, -s);
    }
    print(ctx, 811);
    ctx->help_ptr = 4;
    ctx->help_line[3] = 812;
    ctx->help_line[2] = 813;
    ctx->help_line[1] = 814;
    ctx->help_line[0] = 815;
    error(ctx);
    goto _L30;
  }
  f = ctx->font_ptr + 1;
  ctx->fnt_infos.char_base[f] = ctx->fmem_ptr - bc;
  ctx->fnt_infos.width_base[f] = ctx->fnt_infos.char_base[f] + ec + 1;
  ctx->fnt_infos.height_base[f] = ctx->fnt_infos.width_base[f] + nw;
  ctx->fnt_infos.depth_base[f] = ctx->fnt_infos.height_base[f] + nh;
  ctx->fnt_infos.italic_base[f] = ctx->fnt_infos.depth_base[f] + nd;
  ctx->fnt_infos.lig_kern_base[f] = ctx->fnt_infos.italic_base[f] + ni;
  ctx->fnt_infos.kern_base[f] = ctx->fnt_infos.lig_kern_base[f] + nl - 32768;
  ctx->fnt_infos.exten_base[f] = ctx->fnt_infos.kern_base[f] + nk + 32768;
  ctx->fnt_infos.param_base[f] = ctx->fnt_infos.exten_base[f] + ne;
  if (lh < 2)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  a = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  qw.b0 = a;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  b = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  qw.b1 = b;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  c = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  qw.b2 = c;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  d = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  qw.b3 = d;
  ctx->fnt_infos.font_check[f] = qw;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  z = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  if (z > 127)
    goto _L11;
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  z = (z * 256) +
      *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  z = (z * 256) +
      *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
  z = (z * 16) +
      (*readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value) / 16);
  if (z < 65536)
    goto _L11;
  while (lh > 2) {
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    --lh;
  }
  ctx->fnt_infos.font_dsize[f] = z;
  if (s != (-1000)) {
    if (s >= 0)
      z = s;
    else
      z = xn_over_d(ctx, z, -s, 1000);
  }
  ctx->fnt_infos.font_size[f] = z;
  for (N = ctx->fnt_infos.width_base[f], k = ctx->fmem_ptr; k <= (N - 1); ++k) {
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    a = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    qw.b0 = a;
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    b = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    qw.b1 = b;
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    c = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    qw.b2 = c;
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    d = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    qw.b3 = d;
    ctx->font_info[k].qqqq = qw;
    if ((a >= nw) || (b / 16 >= nh) || ((b & 15) >= nd) || (c / 4 >= ni))
      goto _L11;
    switch (c & 3) {
    case 1:
      if (d >= nl)
        goto _L11;
      break;
    case 3:
      if (d >= ne)
        goto _L11;
      break;
    case 2:
      if ((d < bc) || (d > ec))
        goto _L11;
      while (d < (k + bc - ctx->fmem_ptr)) {
        qw = ctx->font_info[ctx->fnt_infos.char_base[f] + d].qqqq;
        if ((qw.b2 & 3) != 2)
          goto _L45;
        d = qw.b3;
      }
      if (d == (k + bc - ctx->fmem_ptr))
        goto _L11;
    _L45:;
      break;
    default:
      break;
    }
  }
  while (z >= 8388608) {
    z /= 2;
    alpha += alpha;
  }
  beta = 256 / alpha;
  alpha *= z;
  for (N = ctx->fnt_infos.lig_kern_base[f], k = ctx->fnt_infos.width_base[f];
       k <= (N - 1); ++k) {
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    fread(&a, sizeof(uint8_t), 1, ctx->tfm_file);
    fread(&b, sizeof(uint8_t), 1, ctx->tfm_file);
    fread(&c, sizeof(uint8_t), 1, ctx->tfm_file);
    d = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    sw = ((((d * z / 256) + (c * z)) / 256) + (b * z)) / beta;
    if (!a) {
      ctx->font_info[k].int_ = sw;
    } else if (a == 255)
      ctx->font_info[k].int_ = sw - alpha;
    else
      goto _L11;
  }
  if (ctx->font_info[ctx->fnt_infos.width_base[f]].int_)
    goto _L11;
  if (ctx->font_info[ctx->fnt_infos.height_base[f]].int_)
    goto _L11;
  if (ctx->font_info[ctx->fnt_infos.depth_base[f]].int_)
    goto _L11;
  if (ctx->font_info[ctx->fnt_infos.italic_base[f]].int_)
    goto _L11;
  if (nl > 0) {
    for (N = ctx->fnt_infos.kern_base[f] + 32767,
        k = ctx->fnt_infos.lig_kern_base[f];
         k <= N; ++k) {
      loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      a = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      qw.b0 = a;
      loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      b = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      qw.b1 = b;
      loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      c = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      qw.b2 = c;
      loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      d = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      qw.b3 = d;
      ctx->font_info[k].qqqq = qw;
      if (a > 128) {
        if ((c * 256) + d >= nl)
          goto _L11;
        if (a == 255) {
          if (k == ctx->fnt_infos.lig_kern_base[f])
            bchar = b;
        }
      } else {
        if (b != bchar) {
          if ((b < bc) || (b > ec))
            goto _L11;
          qw = ctx->font_info[ctx->fnt_infos.char_base[f] + b].qqqq;
          if (qw.b0 <= 0)
            goto _L11;
        }
        if (c < 128) {
          if ((d < bc) || (d > ec))
            goto _L11;
          qw = ctx->font_info[ctx->fnt_infos.char_base[f] + d].qqqq;
          if (qw.b0 <= 0)
            goto _L11;
        } else if (((c - 128) * 256) + d >= nk)
          goto _L11;
        if (a < 128) {
          if (k - ctx->fnt_infos.lig_kern_base[f] + a + 1 >= nl)
            goto _L11;
        }
      }
    }
    if (a == 255)
      bch_label = (c * 256) + d;
  }
  for (N = ctx->fnt_infos.exten_base[f],
      k = ctx->fnt_infos.kern_base[f] + 32768;
       k <= (N - 1); ++k) {
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    fread(&a, sizeof(uint8_t), 1, ctx->tfm_file);
    fread(&b, sizeof(uint8_t), 1, ctx->tfm_file);
    fread(&c, sizeof(uint8_t), 1, ctx->tfm_file);
    d = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    sw = ((((d * z / 256) + (c * z)) / 256) + (b * z)) / beta;
    if (!a) {
      ctx->font_info[k].int_ = sw;
    } else if (a == 255)
      ctx->font_info[k].int_ = sw - alpha;
    else
      goto _L11;
  }
  for (N = ctx->fnt_infos.param_base[f], k = ctx->fnt_infos.exten_base[f];
       k <= (N - 1); ++k) {
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    a = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    qw.b0 = a;
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    b = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    qw.b1 = b;
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    c = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    qw.b2 = c;
    loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    d = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
    qw.b3 = d;
    ctx->font_info[k].qqqq = qw;
    if (a) {
      if ((a < bc) || (a > ec))
        goto _L11;
      qw = ctx->font_info[ctx->fnt_infos.char_base[f] + a].qqqq;
      if (qw.b0 <= 0)
        goto _L11;
    }
    if (b) {
      if ((b < bc) || (b > ec))
        goto _L11;
      qw = ctx->font_info[ctx->fnt_infos.char_base[f] + b].qqqq;
      if (qw.b0 <= 0)
        goto _L11;
    }
    if (c) {
      if ((c < bc) || (c > ec))
        goto _L11;
      qw = ctx->font_info[ctx->fnt_infos.char_base[f] + c].qqqq;
      if (qw.b0 <= 0)
        goto _L11;
    }
    if ((d < bc) || (d > ec))
      goto _L11;
    qw = ctx->font_info[ctx->fnt_infos.char_base[f] + d].qqqq;
    if (qw.b0 <= 0)
      goto _L11;
  }
  for (k = 1; k <= np; ++k) {
    if (k == 1) {
      loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      sw = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      if (sw > 127)
        sw -= 256;
      loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      sw = (sw * 256) +
           *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      sw = (sw * 256) +
           *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      ctx->font_info[ctx->fnt_infos.param_base[f]].int_ =
          (sw * 16) +
          (*readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value) /
           16);
    } else {
      loadU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      fread(&a, sizeof(uint8_t), 1, ctx->tfm_file);
      fread(&b, sizeof(uint8_t), 1, ctx->tfm_file);
      fread(&c, sizeof(uint8_t), 1, ctx->tfm_file);
      d = *readU8(ctx->tfm_file, &ctx->tfm_file_mode, &ctx->tfm_file_value);
      sw = ((((d * z / 256) + (c * z)) / 256) + (b * z)) / beta;
      if (!a) {
        ctx->font_info[ctx->fnt_infos.param_base[f] + k - 1].int_ = sw;
      } else if (a == 255)
        ctx->font_info[ctx->fnt_infos.param_base[f] + k - 1].int_ = sw - alpha;
      else
        goto _L11;
    }
  }
  if (feof(ctx->tfm_file))
    goto _L11;
  for (k = np + 1; k <= 7; ++k)
    ctx->font_info[ctx->fnt_infos.param_base[f] + k - 1].int_ = 0;
  if (np >= 7)
    ctx->fnt_infos.font_params[f] = np;
  else
    ctx->fnt_infos.font_params[f] = 7;
  ctx->fnt_infos.hyphen_char[f] = ctx->eqtb[12209].int_;
  ctx->fnt_infos.skew_char[f] = ctx->eqtb[12210].int_;
  if (bch_label < nl)
    ctx->fnt_infos.bchar_label[f] = bch_label + ctx->fnt_infos.lig_kern_base[f];
  else
    ctx->fnt_infos.bchar_label[f] = 0;
  ctx->fnt_infos.font_bchar[f] = bchar;
  ctx->fnt_infos.font_false_bchar[f] = bchar;
  if (bchar <= ec) {
    if (bchar >= bc) {
      qw = ctx->font_info[ctx->fnt_infos.char_base[f] + bchar].qqqq;
      if (qw.b0 > 0)
        ctx->fnt_infos.font_false_bchar[f] = 256;
    }
  }
  ctx->fnt_infos.font_name[f] = nom;
  ctx->fnt_infos.font_area[f] = aire;
  ctx->fnt_infos.font_bc[f] = bc;
  ctx->fnt_infos.font_ec[f] = ec;
  ctx->fnt_infos.font_glue[f] = -1073741824;
  --ctx->fnt_infos.param_base[f];
  ctx->fmem_ptr += lf;
  ctx->font_ptr = f;
  g = f;
  goto _L30;
_L11:
  print_nl(ctx, 262);
  print(ctx, 801);
  sprint_cs(ctx, u);
  print_char(ctx, 61);
  print_file_name(ctx, nom, aire, 338);
  if (s >= 0) {
    print(ctx, 741);
    print_scaled(ctx, s);
    print(ctx, 397);
  } else if (s != (-1000)) {
    print(ctx, 802);
    print_int(ctx, -s);
  }
  if (file_opened)
    print(ctx, 803);
  else
    print(ctx, 804);
  ctx->help_ptr = 5;
  ctx->help_line[4] = 805;
  ctx->help_line[3] = 806;
  ctx->help_line[2] = 807;
  ctx->help_line[1] = 808;
  ctx->help_line[0] = 809;
  error(ctx);
_L30:
  if (file_opened)
    b_close(ctx, &ctx->tfm_file);
  {
    const char *tfm_fname = trim_name(ctx->name_of_file, file_name_size);
    int nnn = cgo_load_tfm_file(tfm_fname);
    if (nnn < 0) {
      fprintf(stderr, "could not load TFM file [%s]!\n", tfm_fname);
      fprintf(stderr, ">>> n-glyphs: %d\n", nnn);
      fprintf(stderr, ">>> font-id:  %d\n", g);
    }
  }
  return g;
}

void char_warning(ctex_t *ctx, internal_font_number f, uint8_t c) {
  if (ctx->eqtb[12198].int_ <= 0)
    return;
  begin_diagnostic(ctx);
  print_nl(ctx, 824);
  print(ctx, c);
  print(ctx, 825);
  slow_print(ctx, ctx->fnt_infos.font_name[f]);
  print_char(ctx, 33);
  end_diagnostic(ctx, false);
}

halfword new_character(ctex_t *ctx, internal_font_number f, uint8_t c) {
  halfword result, p;
  if (ctx->fnt_infos.font_bc[f] <= c) {
    if (ctx->fnt_infos.font_ec[f] >= c) {
      if (ctx->font_info[ctx->fnt_infos.char_base[f] + c].qqqq.b0 > 0) {
        p = get_avail(ctx);
        ctx->mem[p - mem_min].hh.U2.b0 = f;
        ctx->mem[p - mem_min].hh.U2.b1 = c;
        result = p;
        goto _L10;
      }
    }
  }
  char_warning(ctx, f, c);
  result = -1073741824;
_L10:
  return result;
}

void dvi_font_def(ctex_t *ctx, internal_font_number f) {
  pool_pointer k, N;
  uint8_t font_area;
  uint8_t font_name;
  integer font_area_id = ctx->fnt_infos.font_area[f];
  integer font_name_id = ctx->fnt_infos.font_name[f];

  font_area = ctx->str_start[font_area_id + 1] - ctx->str_start[font_area_id];
  font_name = ctx->str_start[font_name_id + 1] - ctx->str_start[font_name_id];

  ctex_dvi_wU8(&ctx->dvi_mgr, 243);
  ctex_dvi_wU8(&ctx->dvi_mgr, f - 1);
  ctex_dvi_wU8(&ctx->dvi_mgr, ctx->fnt_infos.font_check[f].b0);
  ctex_dvi_wU8(&ctx->dvi_mgr, ctx->fnt_infos.font_check[f].b1);
  ctex_dvi_wU8(&ctx->dvi_mgr, ctx->fnt_infos.font_check[f].b2);
  ctex_dvi_wU8(&ctx->dvi_mgr, ctx->fnt_infos.font_check[f].b3);
  ctex_dvi_four(&ctx->dvi_mgr, ctx->fnt_infos.font_size[f]);
  ctex_dvi_four(&ctx->dvi_mgr, ctx->fnt_infos.font_dsize[f]);
  ctex_dvi_wU8(&ctx->dvi_mgr, font_area);
  ctex_dvi_wU8(&ctx->dvi_mgr, font_name);
  for (N = ctx->str_start[ctx->fnt_infos.font_area[f] + 1],
      k = ctx->str_start[ctx->fnt_infos.font_area[f]];
       k <= (N - 1); ++k) {
    ctex_dvi_wU8(&ctx->dvi_mgr, ctx->str_pool[k]);
  }
  for (N = ctx->str_start[ctx->fnt_infos.font_name[f] + 1],
      k = ctx->str_start[ctx->fnt_infos.font_name[f]];
       k <= (N - 1); ++k) {
    ctex_dvi_wU8(&ctx->dvi_mgr, ctx->str_pool[k]);
  }
}

void movement(ctex_t *ctx, scaled w, uint8_t o) {
  small_number mstate = 0;
  halfword p;
  integer k;
  halfword q = get_node(ctx, 3);
  ctx->mem[q - mem_min + 1].int_ = w;
  ctx->mem[q - mem_min + 2].int_ = ctex_dvi_pos(&ctx->dvi_mgr);
  if (o == 157) {
    ctx->mem[q - mem_min].hh.rh = ctx->down_ptr;
    ctx->down_ptr = q;
  } else {
    ctx->mem[q - mem_min].hh.rh = ctx->right_ptr;
    ctx->right_ptr = q;
  }
  p = ctx->mem[q - mem_min].hh.rh;
  while (p != (-1073741824)) {
    if (ctx->mem[p - mem_min + 1].int_ == w) {
      switch (mstate + ctx->mem[p - mem_min].hh.lh) {
      case 3:
      case 4:
      case 15:
      case 16:
        if (ctx->mem[p - mem_min + 2].int_ < ctex_dvi_gone(&ctx->dvi_mgr)) {
          goto _L45;
        } else {
          k = ctx->mem[p - mem_min + 2].int_ - ctex_dvi_offset(&ctx->dvi_mgr);
          if (k < 0)
            k += dvi_buf_size;
          ctx->dvi_mgr.dvi_buf[k] += 5;
          ctx->mem[p - mem_min].hh.lh = 1;
          goto _L40;
        }
        break;
      case 5:
      case 9:
      case 11:
        if (ctx->mem[p - mem_min + 2].int_ < ctex_dvi_gone(&ctx->dvi_mgr)) {
          goto _L45;
        } else {
          k = ctx->mem[p - mem_min + 2].int_ - ctex_dvi_offset(&ctx->dvi_mgr);
          if (k < 0)
            k += dvi_buf_size;
          ctx->dvi_mgr.dvi_buf[k] += 10;
          ctx->mem[p - mem_min].hh.lh = 2;
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
      switch (mstate + ctx->mem[p - mem_min].hh.lh) {
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
    p = ctx->mem[p - mem_min].hh.rh;
  }
_L45:
  ctx->mem[q - mem_min].hh.lh = 3;
  if (abs(w) >= 8388608) {
    ctex_dvi_wU8(&ctx->dvi_mgr, o + 3);
    ctex_dvi_four(&ctx->dvi_mgr, w);
    goto _L10;
  }
  if (abs(w) >= 32768) {
    ctex_dvi_wU8(&ctx->dvi_mgr, o + 2);
    if (w < 0) {
      w += 16777216;
    }
    ctex_dvi_wU8(&ctx->dvi_mgr, w / 65536);
    w &= 65535;
    goto _L2;
  }
  if (abs(w) >= 128) {
    ctex_dvi_wU8(&ctx->dvi_mgr, o + 1);
    if (w < 0)
      w += 65536;
    goto _L2;
  }
  ctex_dvi_wU8(&ctx->dvi_mgr, o);
  if (w < 0)
    w += 256;
  goto _L1;
_L2:
  ctex_dvi_wU8(&ctx->dvi_mgr, w / 256);
_L1:
  ctex_dvi_wU8(&ctx->dvi_mgr, w & 255);
  goto _L10;
_L40:
  ctx->mem[q - mem_min].hh.lh = ctx->mem[p - mem_min].hh.lh;
  if (ctx->mem[q - mem_min].hh.lh == 1) {
    ctex_dvi_wU8(&ctx->dvi_mgr, o + 4);
    while (ctx->mem[q - mem_min].hh.rh != p) {
      q = ctx->mem[q - mem_min].hh.rh;
      switch (ctx->mem[q - mem_min].hh.lh) {
      case 3:
        ctx->mem[q - mem_min].hh.lh = 5;
        break;
      case 4:
        ctx->mem[q - mem_min].hh.lh = 6;
        break;
      default:
        break;
      }
    }
  } else {
    ctex_dvi_wU8(&ctx->dvi_mgr, o + 9);
    while (ctx->mem[q - mem_min].hh.rh != p) {
      q = ctx->mem[q - mem_min].hh.rh;
      switch (ctx->mem[q - mem_min].hh.lh) {
      case 3:
        ctx->mem[q - mem_min].hh.lh = 4;
        break;
      case 5:
        ctx->mem[q - mem_min].hh.lh = 6;
        break;
      default:
        break;
      }
    }
  }
_L10:;
}

void prune_movements(ctex_t *ctx, integer l) {
  halfword p;
  while (ctx->down_ptr != (-1073741824)) {
    if (ctx->mem[ctx->down_ptr - mem_min + 2].int_ < l)
      goto _L30;
    p = ctx->down_ptr;
    ctx->down_ptr = ctx->mem[p - mem_min].hh.rh;
    free_node(ctx, p, 3);
  }
_L30:
  while (ctx->right_ptr != (-1073741824)) {
    if (ctx->mem[ctx->right_ptr - mem_min + 2].int_ < l)
      goto _L10;
    p = ctx->right_ptr;
    ctx->right_ptr = ctx->mem[p - mem_min].hh.rh;
    free_node(ctx, p, 3);
  }
_L10:;
}

void special_out(ctex_t *ctx, halfword p) {
  char old_setting;
  pool_pointer k, N;
  if (ctx->cur_h != ctex_dvi_get_h(&ctx->dvi_mgr)) {
    movement(ctx, ctx->cur_h - ctex_dvi_get_h(&ctx->dvi_mgr), 143);
    ctex_dvi_set_h(&ctx->dvi_mgr, ctx->cur_h);
  }
  if (ctx->cur_v != ctex_dvi_get_v(&ctx->dvi_mgr)) {
    movement(ctx, ctx->cur_v - ctex_dvi_get_v(&ctx->dvi_mgr), 157);
    ctex_dvi_set_v(&ctx->dvi_mgr, ctx->cur_v);
  }
  old_setting = ctx->selector;
  ctx->selector = 21;
  show_token_list(ctx,
                  ctx->mem[ctx->mem[p - mem_min + 1].hh.rh - mem_min].hh.rh,
                  -1073741824, pool_size - ctx->pool_ptr);
  ctx->selector = old_setting;
  if (ctx->pool_ptr + 1 > pool_size)
    overflow(ctx, 257, pool_size - ctx->init_pool_ptr);
  if (ctx->pool_ptr - ctx->str_start[ctx->str_ptr] < 256) {
    ctex_dvi_wU8(&ctx->dvi_mgr, 239);
    ctex_dvi_wU8(&ctx->dvi_mgr, ctx->pool_ptr - ctx->str_start[ctx->str_ptr]);
  } else {
    ctex_dvi_wU8(&ctx->dvi_mgr, 242);
    ctex_dvi_four(&ctx->dvi_mgr, ctx->pool_ptr - ctx->str_start[ctx->str_ptr]);
  }
  for (N = ctx->pool_ptr, k = ctx->str_start[ctx->str_ptr]; k <= (N - 1); ++k) {
    ctex_dvi_wU8(&ctx->dvi_mgr, ctx->str_pool[k]);
  }
  ctx->pool_ptr = ctx->str_start[ctx->str_ptr];
}

void write_out(ctex_t *ctx, halfword p) {
  char old_setting;
  integer old_mode;
  small_number j;
  halfword r;
  halfword q = get_avail(ctx);
  ctx->mem[q - mem_min].hh.lh = 637;
  r = get_avail(ctx);
  ctx->mem[q - mem_min].hh.rh = r;
  ctx->mem[r - mem_min].hh.lh = 13617;
  begin_token_list(ctx, q, 4);
  begin_token_list(ctx, ctx->mem[p - mem_min + 1].hh.rh, 15);
  q = get_avail(ctx);
  ctx->mem[q - mem_min].hh.lh = 379;
  begin_token_list(ctx, q, 4);
  old_mode = ctx->cur_list.mode_field;
  ctx->cur_list.mode_field = 0;
  ctx->cur_cs = ctx->write_loc;
  q = scan_toks(ctx, false, true);
  get_token(ctx);
  if (ctx->cur_tok != 13617) {
    print_nl(ctx, 262);
    print(ctx, 1296);
    ctx->help_ptr = 2;
    ctx->help_line[1] = 1297;
    ctx->help_line[0] = 1011;
    error(ctx);
    do {
      get_token(ctx);
    } while (ctx->cur_tok != 13617);
  }
  ctx->cur_list.mode_field = old_mode;
  end_token_list(ctx);
  old_setting = ctx->selector;
  j = ctx->mem[p - mem_min + 1].hh.lh;
  if (ctx->write_open[j]) {
    ctx->selector = j;
  } else {
    if ((j == 17) && (ctx->selector == 19))
      ctx->selector = 18;
    print_nl(ctx, 338);
  }
  token_show(ctx, ctx->def_ref);
  print_ln(ctx);
  flush_list(ctx, ctx->def_ref);
  ctx->selector = old_setting;
}

void out_what(ctex_t *ctx, halfword p) {
  small_number j;
  switch (ctx->mem[p - mem_min].hh.U2.b1) {
  case 0:
  case 1:
  case 2:
    if (!ctx->doing_leaders) {
      j = ctx->mem[p - mem_min + 1].hh.lh;
      if (ctx->mem[p - mem_min].hh.U2.b1 == 1) {
        write_out(ctx, p);
      } else {
        if (ctx->write_open[j])
          a_close(ctx, &ctx->write_file[j]);
        if (ctx->mem[p - mem_min].hh.U2.b1 == 2) {
          ctx->write_open[j] = false;
        } else if (j < 16) {
          ctx->cur_name = ctx->mem[p - mem_min + 1].hh.rh;
          ctx->cur_area = ctx->mem[p - mem_min + 2].hh.lh;
          ctx->cur_ext = ctx->mem[p - mem_min + 2].hh.rh;
          if (ctx->cur_ext == 338)
            ctx->cur_ext = 790;
          pack_file_name(ctx, ctx->cur_name, ctx->cur_area, ctx->cur_ext);
          while (!a_open_out(ctx, &ctx->write_file[j]))
            prompt_file_name(ctx, 1299, 790);
          ctx->write_open[j] = true;
        }
      }
    }
    break;
  case 3:
    special_out(ctx, p);
    break;
  case 4:
    // blank case
    break;
  default:
    confusion(ctx, 1298);
    break;
  }
}

void hlist_out(ctex_t *ctx) {
  scaled base_line, left_edge, save_h, save_v, leader_wd, lx, edge, cur_g = 0;
  integer save_loc;
  halfword leader_box;
  bool_t outer_doing_leaders;
  double glue_temp, cur_glue = 0.0;
  halfword this_box = ctx->temp_ptr;
  glue_ord g_order = ctx->mem[this_box - mem_min + 5].hh.U2.b1;
  char g_sign = ctx->mem[this_box - mem_min + 5].hh.U2.b0;
  halfword p = ctx->mem[this_box - mem_min + 5].hh.rh;
  ++ctx->cur_s;
  if (ctx->cur_s > 0) {
    ctex_dvi_wU8(&ctx->dvi_mgr, 141);
  }
  if (ctx->cur_s > ctx->max_push)
    ctx->max_push = ctx->cur_s;
  save_loc = ctex_dvi_pos(&ctx->dvi_mgr);
  base_line = ctx->cur_v;
  left_edge = ctx->cur_h;
  while (p != (-1073741824)) {
  _L21:
    if (p >= ctx->hi_mem_min) {
      if (ctx->cur_h != ctex_dvi_get_h(&ctx->dvi_mgr)) {
        movement(ctx, ctx->cur_h - ctex_dvi_get_h(&ctx->dvi_mgr), 143);
        ctex_dvi_set_h(&ctx->dvi_mgr, ctx->cur_h);
      }
      if (ctx->cur_v != ctex_dvi_get_v(&ctx->dvi_mgr)) {
        movement(ctx, ctx->cur_v - ctex_dvi_get_v(&ctx->dvi_mgr), 157);
        ctex_dvi_set_v(&ctx->dvi_mgr, ctx->cur_v);
      }
      do {
        ctx->f = ctx->mem[p - mem_min].hh.U2.b0;
        ctx->c = ctx->mem[p - mem_min].hh.U2.b1;
        if (ctx->f != ctex_dvi_get_font(&ctx->dvi_mgr)) {
          if (!ctx->fnt_infos.font_used[ctx->f]) {
            dvi_font_def(ctx, ctx->f);
            ctx->fnt_infos.font_used[ctx->f] = true;
          }
          if (ctx->f <= 64) {
            ctex_dvi_wU8(&ctx->dvi_mgr, ctx->f + 170);
          } else {
            ctex_dvi_wU8(&ctx->dvi_mgr, 235);
            ctex_dvi_wU8(&ctx->dvi_mgr, ctx->f - 1);
          }
          ctex_dvi_set_font(&ctx->dvi_mgr, ctx->f);
        }
        if (ctx->c >= 128) {
          ctex_dvi_wU8(&ctx->dvi_mgr, 128);
        }
        ctex_dvi_wU8(&ctx->dvi_mgr, ctx->c);
        ctx->cur_h +=
            ctx->font_info[ctx->fnt_infos.width_base[ctx->f] +
                           ctx->font_info[ctx->fnt_infos.char_base[ctx->f] +
                                          ctx->c]
                               .qqqq.b0]
                .int_;
        p = ctx->mem[p - mem_min].hh.rh;
      } while (p >= ctx->hi_mem_min);
      ctex_dvi_set_h(&ctx->dvi_mgr, ctx->cur_h);
      continue;
    }
    switch (ctx->mem[p - mem_min].hh.U2.b0) {
    case 0:
    case 1:
      if (ctx->mem[p - mem_min + 5].hh.rh == (-1073741824)) {
        ctx->cur_h += ctx->mem[p - mem_min + 1].int_;
      } else {
        save_h = ctex_dvi_get_h(&ctx->dvi_mgr);
        save_v = ctex_dvi_get_v(&ctx->dvi_mgr);
        ctx->cur_v = base_line + ctx->mem[p - mem_min + 4].int_;
        ctx->temp_ptr = p;
        edge = ctx->cur_h;
        if (ctx->mem[p - mem_min].hh.U2.b0 == 1)
          vlist_out(ctx);
        else
          hlist_out(ctx);
        ctex_dvi_set_h(&ctx->dvi_mgr, save_h);
        ctex_dvi_set_v(&ctx->dvi_mgr, save_v);
        ctx->cur_h = edge + ctx->mem[p - mem_min + 1].int_;
        ctx->cur_v = base_line;
      }
      break;
    case 2:
      ctx->rule_ht = ctx->mem[p - mem_min + 3].int_;
      ctx->rule_dp = ctx->mem[p - mem_min + 2].int_;
      ctx->rule_wd = ctx->mem[p - mem_min + 1].int_;
      goto _L14;
      break;
    case 8:
      out_what(ctx, p);
      break;
    case 10:
      ctx->g = ctx->mem[p - mem_min + 1].hh.lh;
      ctx->rule_wd = ctx->mem[ctx->g - mem_min + 1].int_ - cur_g;
      if (g_sign) {
        if (g_sign == 1) {
          if (ctx->mem[ctx->g - mem_min].hh.U2.b0 == g_order) {
            cur_glue += ctx->mem[ctx->g - mem_min + 2].int_;
            glue_temp = ctx->mem[this_box - mem_min + 6].gr * cur_glue;
            if (glue_temp > 1000000000.0) {
              glue_temp = 1000000000.0;
            } else if (glue_temp < (-1000000000.0))
              glue_temp = -1000000000.0;
            cur_g = round(glue_temp);
          }
        } else if (ctx->mem[ctx->g - mem_min].hh.U2.b1 == g_order) {
          cur_glue -= ctx->mem[ctx->g - mem_min + 3].int_;
          glue_temp = ctx->mem[this_box - mem_min + 6].gr * cur_glue;
          if (glue_temp > 1000000000.0) {
            glue_temp = 1000000000.0;
          } else if (glue_temp < (-1000000000.0))
            glue_temp = -1000000000.0;
          cur_g = round(glue_temp);
        }
      }
      ctx->rule_wd += cur_g;
      if (ctx->mem[p - mem_min].hh.U2.b1 >= 100) {
        leader_box = ctx->mem[p - mem_min + 1].hh.rh;
        if (ctx->mem[leader_box - mem_min].hh.U2.b0 == 2) {
          ctx->rule_ht = ctx->mem[leader_box - mem_min + 3].int_;
          ctx->rule_dp = ctx->mem[leader_box - mem_min + 2].int_;
          goto _L14;
        }
        leader_wd = ctx->mem[leader_box - mem_min + 1].int_;
        if ((leader_wd > 0) && (ctx->rule_wd > 0)) {
          ctx->rule_wd += 10;
          edge = ctx->cur_h + ctx->rule_wd;
          lx = 0;
          if (ctx->mem[p - mem_min].hh.U2.b1 == 100) {
            save_h = ctx->cur_h;
            ctx->cur_h = left_edge +
                         (leader_wd * ((ctx->cur_h - left_edge) / leader_wd));
            if (ctx->cur_h < save_h)
              ctx->cur_h += leader_wd;
          } else {
            ctx->lq = ctx->rule_wd / leader_wd;
            ctx->lr = ctx->rule_wd % leader_wd;
            if (ctx->mem[p - mem_min].hh.U2.b1 == 101) {
              ctx->cur_h += ctx->lr / 2;
            } else {
              lx = ctx->lr / (ctx->lq + 1);
              ctx->cur_h += (ctx->lr - ((ctx->lq - 1) * lx)) / 2;
            }
          }
          while (ctx->cur_h + leader_wd <= edge) {
            ctx->cur_v = base_line + ctx->mem[leader_box - mem_min + 4].int_;
            if (ctx->cur_v != ctex_dvi_get_v(&ctx->dvi_mgr)) {
              movement(ctx, ctx->cur_v - ctex_dvi_get_v(&ctx->dvi_mgr), 157);
              ctex_dvi_set_v(&ctx->dvi_mgr, ctx->cur_v);
            }
            save_v = ctex_dvi_get_v(&ctx->dvi_mgr);
            if (ctx->cur_h != ctex_dvi_get_h(&ctx->dvi_mgr)) {
              movement(ctx, ctx->cur_h - ctex_dvi_get_h(&ctx->dvi_mgr), 143);
              ctex_dvi_set_h(&ctx->dvi_mgr, ctx->cur_h);
            }
            save_h = ctex_dvi_get_h(&ctx->dvi_mgr);
            ctx->temp_ptr = leader_box;
            outer_doing_leaders = ctx->doing_leaders;
            ctx->doing_leaders = true;
            if (ctx->mem[leader_box - mem_min].hh.U2.b0 == 1)
              vlist_out(ctx);
            else
              hlist_out(ctx);
            ctx->doing_leaders = outer_doing_leaders;
            ctex_dvi_set_v(&ctx->dvi_mgr, save_v);
            ctex_dvi_set_h(&ctx->dvi_mgr, save_h);
            ctx->cur_v = base_line;
            ctx->cur_h = save_h + leader_wd + lx;
          }
          ctx->cur_h = edge - 10;
          goto _L15;
        }
      }
      goto _L13;
      break;
    case 11:
    case 9:
      ctx->cur_h += ctx->mem[p - mem_min + 1].int_;
      break;
    case 6:
      ctx->mem[mem_max - mem_min - 12] = ctx->mem[p - mem_min + 1];
      ctx->mem[mem_max - mem_min - 12].hh.rh = ctx->mem[p - mem_min].hh.rh;
      p = mem_max - 12;
      goto _L21;
      break;
    default:
      break;
    }
    goto _L15;
  _L14:
    if (ctx->rule_ht == (-1073741824))
      ctx->rule_ht = ctx->mem[this_box - mem_min + 3].int_;
    if (ctx->rule_dp == (-1073741824))
      ctx->rule_dp = ctx->mem[this_box - mem_min + 2].int_;
    ctx->rule_ht += ctx->rule_dp;
    if ((ctx->rule_ht > 0) && (ctx->rule_wd > 0)) {
      if (ctx->cur_h != ctex_dvi_get_h(&ctx->dvi_mgr)) {
        movement(ctx, ctx->cur_h - ctex_dvi_get_h(&ctx->dvi_mgr), 143);
        ctex_dvi_set_h(&ctx->dvi_mgr, ctx->cur_h);
      }
      ctx->cur_v = base_line + ctx->rule_dp;
      if (ctx->cur_v != ctex_dvi_get_v(&ctx->dvi_mgr)) {
        movement(ctx, ctx->cur_v - ctex_dvi_get_v(&ctx->dvi_mgr), 157);
        ctex_dvi_set_v(&ctx->dvi_mgr, ctx->cur_v);
      }
      ctex_dvi_wU8(&ctx->dvi_mgr, 132);
      ctex_dvi_four(&ctx->dvi_mgr, ctx->rule_ht);
      ctex_dvi_four(&ctx->dvi_mgr, ctx->rule_wd);
      ctx->cur_v = base_line;
      ctex_dvi_set_h(&ctx->dvi_mgr,
                     ctex_dvi_get_h(&ctx->dvi_mgr) + ctx->rule_wd);
    }
  _L13:
    ctx->cur_h += ctx->rule_wd;
  _L15:
    p = ctx->mem[p - mem_min].hh.rh;
  }
  prune_movements(ctx, save_loc);
  if (ctx->cur_s > 0)
    ctex_dvi_pop(&ctx->dvi_mgr, save_loc);
  --ctx->cur_s;
}

void vlist_out(ctex_t *ctx) {
  scaled left_edge, top_edge, save_h, save_v, leader_ht, lx, edge, cur_g = 0;
  integer save_loc;
  halfword leader_box;
  bool_t outer_doing_leaders;
  double glue_temp, cur_glue = 0.0;
  halfword this_box = ctx->temp_ptr;
  glue_ord g_order = ctx->mem[this_box - mem_min + 5].hh.U2.b1;
  char g_sign = ctx->mem[this_box - mem_min + 5].hh.U2.b0;
  halfword p = ctx->mem[this_box - mem_min + 5].hh.rh;
  ++ctx->cur_s;
  if (ctx->cur_s > 0) {
    ctex_dvi_wU8(&ctx->dvi_mgr, 141);
  }
  if (ctx->cur_s > ctx->max_push)
    ctx->max_push = ctx->cur_s;
  save_loc = ctex_dvi_pos(&ctx->dvi_mgr);
  left_edge = ctx->cur_h;
  ctx->cur_v -= ctx->mem[this_box - mem_min + 3].int_;
  top_edge = ctx->cur_v;
  while (p != (-1073741824)) {
    if (p >= ctx->hi_mem_min) {
      confusion(ctx, 827);
    } else {
      switch (ctx->mem[p - mem_min].hh.U2.b0) {
      case 0:
      case 1:
        if (ctx->mem[p - mem_min + 5].hh.rh == (-1073741824)) {
          ctx->cur_v +=
              ctx->mem[p - mem_min + 3].int_ + ctx->mem[p - mem_min + 2].int_;
        } else {
          ctx->cur_v += ctx->mem[p - mem_min + 3].int_;
          if (ctx->cur_v != ctex_dvi_get_v(&ctx->dvi_mgr)) {
            movement(ctx, ctx->cur_v - ctex_dvi_get_v(&ctx->dvi_mgr), 157);
            ctex_dvi_set_v(&ctx->dvi_mgr, ctx->cur_v);
          }
          save_h = ctex_dvi_get_h(&ctx->dvi_mgr);
          save_v = ctex_dvi_get_v(&ctx->dvi_mgr);
          ctx->cur_h = left_edge + ctx->mem[p - mem_min + 4].int_;
          ctx->temp_ptr = p;
          if (ctx->mem[p - mem_min].hh.U2.b0 == 1)
            vlist_out(ctx);
          else
            hlist_out(ctx);
          ctex_dvi_set_h(&ctx->dvi_mgr, save_h);
          ctex_dvi_set_v(&ctx->dvi_mgr, save_v);
          ctx->cur_v = save_v + ctx->mem[p - mem_min + 2].int_;
          ctx->cur_h = left_edge;
        }
        break;
      case 2:
        ctx->rule_ht = ctx->mem[p - mem_min + 3].int_;
        ctx->rule_dp = ctx->mem[p - mem_min + 2].int_;
        ctx->rule_wd = ctx->mem[p - mem_min + 1].int_;
        goto _L14;
        break;
      case 8:
        out_what(ctx, p);
        break;
      case 10:
        ctx->g = ctx->mem[p - mem_min + 1].hh.lh;
        ctx->rule_ht = ctx->mem[ctx->g - mem_min + 1].int_ - cur_g;
        if (g_sign) {
          if (g_sign == 1) {
            if (ctx->mem[ctx->g - mem_min].hh.U2.b0 == g_order) {
              cur_glue += ctx->mem[ctx->g - mem_min + 2].int_;
              glue_temp = ctx->mem[this_box - mem_min + 6].gr * cur_glue;
              if (glue_temp > 1000000000.0) {
                glue_temp = 1000000000.0;
              } else if (glue_temp < (-1000000000.0))
                glue_temp = -1000000000.0;
              cur_g = round(glue_temp);
            }
          } else if (ctx->mem[ctx->g - mem_min].hh.U2.b1 == g_order) {
            cur_glue -= ctx->mem[ctx->g - mem_min + 3].int_;
            glue_temp = ctx->mem[this_box - mem_min + 6].gr * cur_glue;
            if (glue_temp > 1000000000.0) {
              glue_temp = 1000000000.0;
            } else if (glue_temp < (-1000000000.0))
              glue_temp = -1000000000.0;
            cur_g = round(glue_temp);
          }
        }
        ctx->rule_ht += cur_g;
        if (ctx->mem[p - mem_min].hh.U2.b1 >= 100) {
          leader_box = ctx->mem[p - mem_min + 1].hh.rh;
          if (ctx->mem[leader_box - mem_min].hh.U2.b0 == 2) {
            ctx->rule_wd = ctx->mem[leader_box - mem_min + 1].int_;
            ctx->rule_dp = 0;
            goto _L14;
          }
          leader_ht = ctx->mem[leader_box - mem_min + 3].int_ +
                      ctx->mem[leader_box - mem_min + 2].int_;
          if ((leader_ht > 0) && (ctx->rule_ht > 0)) {
            ctx->rule_ht += 10;
            edge = ctx->cur_v + ctx->rule_ht;
            lx = 0;
            if (ctx->mem[p - mem_min].hh.U2.b1 == 100) {
              save_v = ctx->cur_v;
              ctx->cur_v = top_edge +
                           (leader_ht * ((ctx->cur_v - top_edge) / leader_ht));
              if (ctx->cur_v < save_v)
                ctx->cur_v += leader_ht;
            } else {
              ctx->lq = ctx->rule_ht / leader_ht;
              ctx->lr = ctx->rule_ht % leader_ht;
              if (ctx->mem[p - mem_min].hh.U2.b1 == 101) {
                ctx->cur_v += ctx->lr / 2;
              } else {
                lx = ctx->lr / (ctx->lq + 1);
                ctx->cur_v += (ctx->lr - ((ctx->lq - 1) * lx)) / 2;
              }
            }
            while (ctx->cur_v + leader_ht <= edge) {
              ctx->cur_h = left_edge + ctx->mem[leader_box - mem_min + 4].int_;
              if (ctx->cur_h != ctex_dvi_get_h(&ctx->dvi_mgr)) {
                movement(ctx, ctx->cur_h - ctex_dvi_get_h(&ctx->dvi_mgr), 143);
                ctex_dvi_set_h(&ctx->dvi_mgr, ctx->cur_h);
              }
              save_h = ctex_dvi_get_h(&ctx->dvi_mgr);
              ctx->cur_v += ctx->mem[leader_box - mem_min + 3].int_;
              if (ctx->cur_v != ctex_dvi_get_v(&ctx->dvi_mgr)) {
                movement(ctx, ctx->cur_v - ctex_dvi_get_v(&ctx->dvi_mgr), 157);
                ctex_dvi_set_v(&ctx->dvi_mgr, ctx->cur_v);
              }
              save_v = ctex_dvi_get_v(&ctx->dvi_mgr);
              ctx->temp_ptr = leader_box;
              outer_doing_leaders = ctx->doing_leaders;
              ctx->doing_leaders = true;
              if (ctx->mem[leader_box - mem_min].hh.U2.b0 == 1)
                vlist_out(ctx);
              else
                hlist_out(ctx);
              ctx->doing_leaders = outer_doing_leaders;
              ctex_dvi_set_v(&ctx->dvi_mgr, save_v);
              ctex_dvi_set_h(&ctx->dvi_mgr, save_h);
              ctx->cur_h = left_edge;
              ctx->cur_v = save_v - ctx->mem[leader_box - mem_min + 3].int_ +
                           leader_ht + lx;
            }
            ctx->cur_v = edge - 10;
            goto _L15;
          }
        }
        goto _L13;
        break;
      case 11:
        ctx->cur_v += ctx->mem[p - mem_min + 1].int_;
        break;
      default:
        break;
      }
      goto _L15;
    _L14:
      if (ctx->rule_wd == (-1073741824))
        ctx->rule_wd = ctx->mem[this_box - mem_min + 1].int_;
      ctx->rule_ht += ctx->rule_dp;
      ctx->cur_v += ctx->rule_ht;
      if ((ctx->rule_ht > 0) && (ctx->rule_wd > 0)) {
        if (ctx->cur_h != ctex_dvi_get_h(&ctx->dvi_mgr)) {
          movement(ctx, ctx->cur_h - ctex_dvi_get_h(&ctx->dvi_mgr), 143);
          ctex_dvi_set_h(&ctx->dvi_mgr, ctx->cur_h);
        }
        if (ctx->cur_v != ctex_dvi_get_v(&ctx->dvi_mgr)) {
          movement(ctx, ctx->cur_v - ctex_dvi_get_v(&ctx->dvi_mgr), 157);
          ctex_dvi_set_v(&ctx->dvi_mgr, ctx->cur_v);
        }
        ctex_dvi_wU8(&ctx->dvi_mgr, 137);
        ctex_dvi_four(&ctx->dvi_mgr, ctx->rule_ht);
        ctex_dvi_four(&ctx->dvi_mgr, ctx->rule_wd);
      }
      goto _L15;
    _L13:
      ctx->cur_v += ctx->rule_ht;
    }
  _L15:
    p = ctx->mem[p - mem_min].hh.rh;
  }
  prune_movements(ctx, save_loc);
  if (ctx->cur_s > 0)
    ctex_dvi_pop(&ctx->dvi_mgr, save_loc);
  --ctx->cur_s;
}

void ship_out(ctex_t *ctx, halfword p) {
  integer page_loc;
  char j = 9, k;
  pool_pointer s;
  char old_setting;
  pool_pointer N;
  if (ctx->eqtb[12197].int_ > 0) {
    print_nl(ctx, 338);
    print_ln(ctx);
    print(ctx, 828);
  }
  if (ctx->term_offset > (max_print_line - 9)) {
    print_ln(ctx);
  } else if ((ctx->term_offset > 0) || (ctx->file_offset > 0))
    print_char(ctx, 32);
  print_char(ctx, 91);
  while ((!ctx->eqtb[j + 12218].int_) && (j > 0))
    --j;
  for (k = 0; k <= j; ++k) {
    print_int(ctx, ctx->eqtb[k + 12218].int_);
    if (k < j)
      print_char(ctx, 46);
  }
  fflush(ctx->term_out);
  errno = 0;
  if (ctx->eqtb[12197].int_ > 0) {
    print_char(ctx, 93);
    begin_diagnostic(ctx);
    show_box(ctx, p);
    end_diagnostic(ctx, true);
  }
  if ((ctx->mem[p - mem_min + 3].int_ > 1073741823) ||
      (ctx->mem[p - mem_min + 2].int_ > 1073741823) ||
      (ctx->mem[p - mem_min + 3].int_ + ctx->mem[p - mem_min + 2].int_ +
           ctx->eqtb[12749].int_ >
       1073741823) ||
      (ctx->mem[p - mem_min + 1].int_ + ctx->eqtb[12748].int_ > 1073741823)) {
    print_nl(ctx, 262);
    print(ctx, 832);
    ctx->help_ptr = 2;
    ctx->help_line[1] = 833;
    ctx->help_line[0] = 834;
    error(ctx);
    if (ctx->eqtb[12197].int_ <= 0) {
      begin_diagnostic(ctx);
      print_nl(ctx, 835);
      show_box(ctx, p);
      end_diagnostic(ctx, true);
    }
    goto _L30;
  }
  if (ctx->mem[p - mem_min + 3].int_ + ctx->mem[p - mem_min + 2].int_ +
          ctx->eqtb[12749].int_ >
      ctx->max_v)
    ctx->max_v = ctx->mem[p - mem_min + 3].int_ +
                 ctx->mem[p - mem_min + 2].int_ + ctx->eqtb[12749].int_;
  if (ctx->mem[p - mem_min + 1].int_ + ctx->eqtb[12748].int_ > ctx->max_h)
    ctx->max_h = ctx->mem[p - mem_min + 1].int_ + ctx->eqtb[12748].int_;
  ctex_dvi_set_h(&ctx->dvi_mgr, 0);
  ctex_dvi_set_v(&ctx->dvi_mgr, 0);
  ctx->cur_h = ctx->eqtb[12748].int_;
  ctex_dvi_set_font(&ctx->dvi_mgr, 0);
  if (!ctx->output_file_name) {
    if (!ctx->job_name)
      open_log_file(ctx);
    pack_job_name(ctx, 793);
    while (!ctx->dvi_mgr.dvi_file && !b_open_out(ctx, &ctx->dvi_mgr.dvi_file))
      prompt_file_name(ctx, 794, 793);
    ctx->output_file_name = b_make_name_string(ctx, ctx->dvi_mgr.dvi_file);
  }
  if (!ctex_dvi_pages(&ctx->dvi_mgr)) {
    ctex_dvi_wU8(&ctx->dvi_mgr, 247);
    ctex_dvi_wU8(&ctx->dvi_mgr, 2);
    ctex_dvi_four(&ctx->dvi_mgr, 25400000);
    ctex_dvi_four(&ctx->dvi_mgr, 473628672);
    prepare_mag(ctx);
    ctex_dvi_four(&ctx->dvi_mgr, ctx->eqtb[12180].int_);
    old_setting = ctx->selector;
    ctx->selector = 21;
    print(ctx, 826);
    print_int(ctx, ctx->eqtb[12186].int_);
    print_char(ctx, 46);
    print_two(ctx, ctx->eqtb[12185].int_);
    print_char(ctx, 46);
    print_two(ctx, ctx->eqtb[12184].int_);
    print_char(ctx, 58);
    print_two(ctx, ctx->eqtb[12183].int_ / 60);
    print_two(ctx, ctx->eqtb[12183].int_ % 60);
    ctx->selector = old_setting;
    ctex_dvi_wU8(&ctx->dvi_mgr, ctx->pool_ptr - ctx->str_start[ctx->str_ptr]);
    for (N = ctx->pool_ptr, s = ctx->str_start[ctx->str_ptr]; s <= (N - 1);
         ++s) {
      ctex_dvi_wU8(&ctx->dvi_mgr, ctx->str_pool[s]);
    }
    ctx->pool_ptr = ctx->str_start[ctx->str_ptr];
  }
  page_loc = ctex_dvi_pos(&ctx->dvi_mgr);
  ctex_dvi_wU8(&ctx->dvi_mgr, 139);
  for (k = 0; k <= 9; ++k) {
    ctex_dvi_four(&ctx->dvi_mgr, ctx->eqtb[k + 12218].int_);
  }
  ctex_dvi_four(&ctx->dvi_mgr, ctx->last_bop);
  ctx->last_bop = page_loc;
  ctx->cur_v = ctx->mem[p - mem_min + 3].int_ + ctx->eqtb[12749].int_;
  ctx->temp_ptr = p;
  if (ctx->mem[p - mem_min].hh.U2.b0 == 1)
    vlist_out(ctx);
  else
    hlist_out(ctx);
  ctex_dvi_wU8(&ctx->dvi_mgr, 140);
  ctex_dvi_add_page(&ctx->dvi_mgr);
  ctx->cur_s = -1;
_L30:
  if (ctx->eqtb[12197].int_ <= 0)
    print_char(ctx, 93);
  ctx->dead_cycles = 0;
  fflush(ctx->term_out);
  errno = 0;
  flush_node_list(ctx, p);
}

void scan_spec(ctex_t *ctx, group_code c, bool_t three_codes) {
  integer s;
  char spec_code;
  if (three_codes)
    s = ctx->save_stack[ctx->save_ptr].int_;
  if (scan_keyword(ctx, 841)) {
    spec_code = 0;
  } else if (scan_keyword(ctx, 842)) {
    spec_code = 1;
  } else {
    spec_code = 1;
    ctx->cur_val = 0;
    goto _L40;
  }
  scan_dimen(ctx, false, false, false);
_L40:
  if (three_codes) {
    ctx->save_stack[ctx->save_ptr].int_ = s;
    ++ctx->save_ptr;
  }
  ctx->save_stack[ctx->save_ptr].int_ = spec_code;
  ctx->save_stack[ctx->save_ptr + 1].int_ = ctx->cur_val;
  ctx->save_ptr += 2;
  new_save_level(ctx, c);
  scan_left_brace(ctx);
}

halfword hpack(ctex_t *ctx, halfword p, scaled w, small_number m) {
  halfword r, q, g;
  scaled h = 0, d = 0, x = 0, s;
  glue_ord o;
  internal_font_number f;
  four_quarters i;
  uint8_t hd;
  ctx->last_badness = 0;
  r = get_node(ctx, 7);
  ctx->mem[r - mem_min].hh.U2.b0 = 0;
  ctx->mem[r - mem_min].hh.U2.b1 = 0;
  ctx->mem[r - mem_min + 4].int_ = 0;
  q = r + 5;
  ctx->mem[q - mem_min].hh.rh = p;
  ctx->total_stretch[0] = 0;
  ctx->total_shrink[0] = 0;
  ctx->total_stretch[1] = 0;
  ctx->total_shrink[1] = 0;
  ctx->total_stretch[2] = 0;
  ctx->total_shrink[2] = 0;
  ctx->total_stretch[3] = 0;
  ctx->total_shrink[3] = 0;
  while (p != (-1073741824)) {
  _L21:
    while (p >= ctx->hi_mem_min) {
      f = ctx->mem[p - mem_min].hh.U2.b0;
      i = ctx->font_info[ctx->fnt_infos.char_base[f] +
                         ctx->mem[p - mem_min].hh.U2.b1]
              .qqqq;
      hd = i.b1;
      x += ctx->font_info[ctx->fnt_infos.width_base[f] + i.b0].int_;
      s = ctx->font_info[ctx->fnt_infos.height_base[f] + (hd / 16)].int_;
      if (s > h)
        h = s;
      s = ctx->font_info[ctx->fnt_infos.depth_base[f] + (hd & 15)].int_;
      if (s > d)
        d = s;
      p = ctx->mem[p - mem_min].hh.rh;
    }
    if (p == (-1073741824))
      break;
    switch (ctx->mem[p - mem_min].hh.U2.b0) {
    case 0:
    case 1:
    case 2:
    case 13:
      x += ctx->mem[p - mem_min + 1].int_;
      if (ctx->mem[p - mem_min].hh.U2.b0 >= 2)
        s = 0;
      else
        s = ctx->mem[p - mem_min + 4].int_;
      if (ctx->mem[p - mem_min + 3].int_ - s > h)
        h = ctx->mem[p - mem_min + 3].int_ - s;
      if (ctx->mem[p - mem_min + 2].int_ + s > d)
        d = ctx->mem[p - mem_min + 2].int_ + s;
      break;
    case 3:
    case 4:
    case 5:
      if (ctx->adjust_tail != (-1073741824)) {
        while (ctx->mem[q - mem_min].hh.rh != p)
          q = ctx->mem[q - mem_min].hh.rh;
        if (ctx->mem[p - mem_min].hh.U2.b0 == 5) {
          ctx->mem[ctx->adjust_tail - mem_min].hh.rh =
              ctx->mem[p - mem_min + 1].int_;
          while (ctx->mem[ctx->adjust_tail - mem_min].hh.rh != (-1073741824))
            ctx->adjust_tail = ctx->mem[ctx->adjust_tail - mem_min].hh.rh;
          p = ctx->mem[p - mem_min].hh.rh;
          free_node(ctx, ctx->mem[q - mem_min].hh.rh, 2);
        } else {
          ctx->mem[ctx->adjust_tail - mem_min].hh.rh = p;
          ctx->adjust_tail = p;
          p = ctx->mem[p - mem_min].hh.rh;
        }
        ctx->mem[q - mem_min].hh.rh = p;
        p = q;
      }
      break;
    case 8:
      // blank case
      break;
    case 10:
      g = ctx->mem[p - mem_min + 1].hh.lh;
      x += ctx->mem[g - mem_min + 1].int_;
      o = ctx->mem[g - mem_min].hh.U2.b0;
      ctx->total_stretch[o] += ctx->mem[g - mem_min + 2].int_;
      o = ctx->mem[g - mem_min].hh.U2.b1;
      ctx->total_shrink[o] += ctx->mem[g - mem_min + 3].int_;
      if (ctx->mem[p - mem_min].hh.U2.b1 >= 100) {
        g = ctx->mem[p - mem_min + 1].hh.rh;
        if (ctx->mem[g - mem_min + 3].int_ > h)
          h = ctx->mem[g - mem_min + 3].int_;
        if (ctx->mem[g - mem_min + 2].int_ > d)
          d = ctx->mem[g - mem_min + 2].int_;
      }
      break;
    case 11:
    case 9:
      x += ctx->mem[p - mem_min + 1].int_;
      break;
    case 6:
      ctx->mem[mem_max - mem_min - 12] = ctx->mem[p - mem_min + 1];
      ctx->mem[mem_max - mem_min - 12].hh.rh = ctx->mem[p - mem_min].hh.rh;
      p = mem_max - 12;
      goto _L21;
      break;
    default:
      break;
    }
    p = ctx->mem[p - mem_min].hh.rh;
  }
  if (ctx->adjust_tail != (-1073741824))
    ctx->mem[ctx->adjust_tail - mem_min].hh.rh = -1073741824;
  ctx->mem[r - mem_min + 3].int_ = h;
  ctx->mem[r - mem_min + 2].int_ = d;
  if (m == 1)
    w += x;
  ctx->mem[r - mem_min + 1].int_ = w;
  x = w - x;
  if (!x) {
    ctx->mem[r - mem_min + 5].hh.U2.b0 = 0;
    ctx->mem[r - mem_min + 5].hh.U2.b1 = 0;
    ctx->mem[r - mem_min + 6].gr = 0.0;
    goto _L10;
  } else if (x > 0) {
    if (ctx->total_stretch[3]) {
      o = 3;
    } else if (ctx->total_stretch[2]) {
      o = 2;
    } else if (ctx->total_stretch[1])
      o = 1;
    else
      o = 0;
    ctx->mem[r - mem_min + 5].hh.U2.b1 = o;
    ctx->mem[r - mem_min + 5].hh.U2.b0 = 1;
    if (ctx->total_stretch[o]) {
      ctx->mem[r - mem_min + 6].gr = ((double)x) / ctx->total_stretch[o];
    } else {
      ctx->mem[r - mem_min + 5].hh.U2.b0 = 0;
      ctx->mem[r - mem_min + 6].gr = 0.0;
    }
    if (!o) {
      if (ctx->mem[r - mem_min + 5].hh.rh != (-1073741824)) {
        ctx->last_badness = badness(ctx, x, ctx->total_stretch[0]);
        if (ctx->last_badness > ctx->eqtb[12189].int_) {
          print_ln(ctx);
          if (ctx->last_badness > 100)
            print_nl(ctx, 843);
          else
            print_nl(ctx, 844);
          print(ctx, 845);
          print_int(ctx, ctx->last_badness);
          goto _L50;
        }
      }
    }
    goto _L10;
  } else {
    if (ctx->total_shrink[3]) {
      o = 3;
    } else if (ctx->total_shrink[2]) {
      o = 2;
    } else if (ctx->total_shrink[1])
      o = 1;
    else
      o = 0;
    ctx->mem[r - mem_min + 5].hh.U2.b1 = o;
    ctx->mem[r - mem_min + 5].hh.U2.b0 = 2;
    if (ctx->total_shrink[o]) {
      ctx->mem[r - mem_min + 6].gr = ((double)(-x)) / ctx->total_shrink[o];
    } else {
      ctx->mem[r - mem_min + 5].hh.U2.b0 = 0;
      ctx->mem[r - mem_min + 6].gr = 0.0;
    }
    if ((ctx->total_shrink[o] < (-x)) && (!o) &&
        (ctx->mem[r - mem_min + 5].hh.rh != (-1073741824))) {
      ctx->last_badness = 1000000;
      ctx->mem[r - mem_min + 6].gr = 1.0;
      if (((-x) - ctx->total_shrink[0] > ctx->eqtb[12738].int_) ||
          (ctx->eqtb[12189].int_ < 100)) {
        if ((ctx->eqtb[12746].int_ > 0) &&
            ((-x) - ctx->total_shrink[0] > ctx->eqtb[12738].int_)) {
          while (ctx->mem[q - mem_min].hh.rh != (-1073741824))
            q = ctx->mem[q - mem_min].hh.rh;
          ctx->mem[q - mem_min].hh.rh = new_rule(ctx);
          ctx->mem[ctx->mem[q - mem_min].hh.rh - mem_min + 1].int_ =
              ctx->eqtb[12746].int_;
        }
        print_ln(ctx);
        print_nl(ctx, 851);
        print_scaled(ctx, (-x) - ctx->total_shrink[0]);
        print(ctx, 852);
        goto _L50;
      }
    } else if (!o) {
      if (ctx->mem[r - mem_min + 5].hh.rh != (-1073741824)) {
        ctx->last_badness = badness(ctx, -x, ctx->total_shrink[0]);
        if (ctx->last_badness > ctx->eqtb[12189].int_) {
          print_ln(ctx);
          print_nl(ctx, 853);
          print_int(ctx, ctx->last_badness);
          goto _L50;
        }
      }
    }
    goto _L10;
  }
_L50:
  if (ctx->output_active) {
    print(ctx, 846);
  } else {
    if (ctx->pack_begin_line) {
      if (ctx->pack_begin_line > 0)
        print(ctx, 847);
      else
        print(ctx, 848);
      print_int(ctx, abs(ctx->pack_begin_line));
      print(ctx, 849);
    } else {
      print(ctx, 850);
    }
    print_int(ctx, ctx->line);
  }
  print_ln(ctx);
  ctx->font_in_short_display = 0;
  short_display(ctx, ctx->mem[r - mem_min + 5].hh.rh);
  print_ln(ctx);
  begin_diagnostic(ctx);
  show_box(ctx, r);
  end_diagnostic(ctx, true);
_L10:
  return r;
}

halfword vpackage(ctex_t *ctx, halfword p, scaled h, small_number m, scaled l) {
  halfword r, g;
  scaled w = 0, d = 0, x = 0, s;
  glue_ord o;
  ctx->last_badness = 0;
  r = get_node(ctx, 7);
  ctx->mem[r - mem_min].hh.U2.b0 = 1;
  ctx->mem[r - mem_min].hh.U2.b1 = 0;
  ctx->mem[r - mem_min + 4].int_ = 0;
  ctx->mem[r - mem_min + 5].hh.rh = p;
  ctx->total_stretch[0] = 0;
  ctx->total_shrink[0] = 0;
  ctx->total_stretch[1] = 0;
  ctx->total_shrink[1] = 0;
  ctx->total_stretch[2] = 0;
  ctx->total_shrink[2] = 0;
  ctx->total_stretch[3] = 0;
  ctx->total_shrink[3] = 0;
  while (p != (-1073741824)) {
    if (p >= ctx->hi_mem_min) {
      confusion(ctx, 854);
    } else {
      switch (ctx->mem[p - mem_min].hh.U2.b0) {
      case 0:
      case 1:
      case 2:
      case 13:
        x += d + ctx->mem[p - mem_min + 3].int_;
        d = ctx->mem[p - mem_min + 2].int_;
        if (ctx->mem[p - mem_min].hh.U2.b0 >= 2)
          s = 0;
        else
          s = ctx->mem[p - mem_min + 4].int_;
        if (ctx->mem[p - mem_min + 1].int_ + s > w)
          w = ctx->mem[p - mem_min + 1].int_ + s;
        break;
      case 8:
        // blank case
        break;
      case 10:
        x += d;
        d = 0;
        g = ctx->mem[p - mem_min + 1].hh.lh;
        x += ctx->mem[g - mem_min + 1].int_;
        o = ctx->mem[g - mem_min].hh.U2.b0;
        ctx->total_stretch[o] += ctx->mem[g - mem_min + 2].int_;
        o = ctx->mem[g - mem_min].hh.U2.b1;
        ctx->total_shrink[o] += ctx->mem[g - mem_min + 3].int_;
        if (ctx->mem[p - mem_min].hh.U2.b1 >= 100) {
          g = ctx->mem[p - mem_min + 1].hh.rh;
          if (ctx->mem[g - mem_min + 1].int_ > w)
            w = ctx->mem[g - mem_min + 1].int_;
        }
        break;
      case 11:
        x += d + ctx->mem[p - mem_min + 1].int_;
        d = 0;
        break;
      default:
        break;
      }
    }
    p = ctx->mem[p - mem_min].hh.rh;
  }
  ctx->mem[r - mem_min + 1].int_ = w;
  if (d > l) {
    x += d - l;
    ctx->mem[r - mem_min + 2].int_ = l;
  } else {
    ctx->mem[r - mem_min + 2].int_ = d;
  }
  if (m == 1)
    h += x;
  ctx->mem[r - mem_min + 3].int_ = h;
  x = h - x;
  if (!x) {
    ctx->mem[r - mem_min + 5].hh.U2.b0 = 0;
    ctx->mem[r - mem_min + 5].hh.U2.b1 = 0;
    ctx->mem[r - mem_min + 6].gr = 0.0;
    goto _L10;
  } else if (x > 0) {
    if (ctx->total_stretch[3]) {
      o = 3;
    } else if (ctx->total_stretch[2]) {
      o = 2;
    } else if (ctx->total_stretch[1])
      o = 1;
    else
      o = 0;
    ctx->mem[r - mem_min + 5].hh.U2.b1 = o;
    ctx->mem[r - mem_min + 5].hh.U2.b0 = 1;
    if (ctx->total_stretch[o]) {
      ctx->mem[r - mem_min + 6].gr = ((double)x) / ctx->total_stretch[o];
    } else {
      ctx->mem[r - mem_min + 5].hh.U2.b0 = 0;
      ctx->mem[r - mem_min + 6].gr = 0.0;
    }
    if (!o) {
      if (ctx->mem[r - mem_min + 5].hh.rh != (-1073741824)) {
        ctx->last_badness = badness(ctx, x, ctx->total_stretch[0]);
        if (ctx->last_badness > ctx->eqtb[12190].int_) {
          print_ln(ctx);
          if (ctx->last_badness > 100)
            print_nl(ctx, 843);
          else
            print_nl(ctx, 844);
          print(ctx, 855);
          print_int(ctx, ctx->last_badness);
          goto _L50;
        }
      }
    }
    goto _L10;
  } else {
    if (ctx->total_shrink[3]) {
      o = 3;
    } else if (ctx->total_shrink[2]) {
      o = 2;
    } else if (ctx->total_shrink[1])
      o = 1;
    else
      o = 0;
    ctx->mem[r - mem_min + 5].hh.U2.b1 = o;
    ctx->mem[r - mem_min + 5].hh.U2.b0 = 2;
    if (ctx->total_shrink[o]) {
      ctx->mem[r - mem_min + 6].gr = ((double)(-x)) / ctx->total_shrink[o];
    } else {
      ctx->mem[r - mem_min + 5].hh.U2.b0 = 0;
      ctx->mem[r - mem_min + 6].gr = 0.0;
    }
    if ((ctx->total_shrink[o] < (-x)) && (!o) &&
        (ctx->mem[r - mem_min + 5].hh.rh != (-1073741824))) {
      ctx->last_badness = 1000000;
      ctx->mem[r - mem_min + 6].gr = 1.0;
      if (((-x) - ctx->total_shrink[0] > ctx->eqtb[12739].int_) ||
          (ctx->eqtb[12190].int_ < 100)) {
        print_ln(ctx);
        print_nl(ctx, 856);
        print_scaled(ctx, (-x) - ctx->total_shrink[0]);
        print(ctx, 857);
        goto _L50;
      }
    } else if (!o) {
      if (ctx->mem[r - mem_min + 5].hh.rh != (-1073741824)) {
        ctx->last_badness = badness(ctx, -x, ctx->total_shrink[0]);
        if (ctx->last_badness > ctx->eqtb[12190].int_) {
          print_ln(ctx);
          print_nl(ctx, 858);
          print_int(ctx, ctx->last_badness);
          goto _L50;
        }
      }
    }
    goto _L10;
  }
_L50:
  if (ctx->output_active) {
    print(ctx, 846);
  } else {
    if (ctx->pack_begin_line) {
      print(ctx, 848);
      print_int(ctx, abs(ctx->pack_begin_line));
      print(ctx, 849);
    } else {
      print(ctx, 850);
    }
    print_int(ctx, ctx->line);
    print_ln(ctx);
  }
  begin_diagnostic(ctx);
  show_box(ctx, r);
  end_diagnostic(ctx, true);
_L10:
  return r;
}

void append_to_vlist(ctex_t *ctx, halfword b) {
  scaled d;
  halfword p;
  if (ctx->cur_list.aux_field.int_ > (-65536000)) {
    d = ctx->mem[ctx->eqtb[9783].hh.rh - mem_min + 1].int_ -
        ctx->cur_list.aux_field.int_ - ctx->mem[b - mem_min + 3].int_;
    if (d < ctx->eqtb[12732].int_) {
      p = new_param_glue(ctx, 0);
    } else {
      p = new_skip_param(ctx, 1);
      ctx->mem[ctx->temp_ptr - mem_min + 1].int_ = d;
    }
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = p;
    ctx->cur_list.tail_field = p;
  }
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = b;
  ctx->cur_list.tail_field = b;
  ctx->cur_list.aux_field.int_ = ctx->mem[b - mem_min + 2].int_;
}

halfword new_noad(ctex_t *ctx) {
  halfword p = get_node(ctx, 4);
  ctx->mem[p - mem_min].hh.U2.b0 = 16;
  ctx->mem[p - mem_min].hh.U2.b1 = 0;
  ctx->mem[p - mem_min + 1].hh = ctx->empty_field;
  ctx->mem[p - mem_min + 3].hh = ctx->empty_field;
  ctx->mem[p - mem_min + 2].hh = ctx->empty_field;
  return p;
}

halfword new_style(ctex_t *ctx, small_number s) {
  halfword p = get_node(ctx, 3);
  ctx->mem[p - mem_min].hh.U2.b0 = 14;
  ctx->mem[p - mem_min].hh.U2.b1 = s;
  ctx->mem[p - mem_min + 1].int_ = 0;
  ctx->mem[p - mem_min + 2].int_ = 0;
  return p;
}

halfword new_choice(ctex_t *ctx) {
  halfword p = get_node(ctx, 3);
  ctx->mem[p - mem_min].hh.U2.b0 = 15;
  ctx->mem[p - mem_min].hh.U2.b1 = 0;
  ctx->mem[p - mem_min + 1].hh.lh = -1073741824;
  ctx->mem[p - mem_min + 1].hh.rh = -1073741824;
  ctx->mem[p - mem_min + 2].hh.lh = -1073741824;
  ctx->mem[p - mem_min + 2].hh.rh = -1073741824;
  return p;
}

void show_info(ctex_t *ctx) {
  show_node_list(ctx, ctx->mem[ctx->temp_ptr - mem_min].hh.lh);
}

halfword fraction_rule(ctex_t *ctx, scaled t) {
  halfword p = new_rule(ctx);
  ctx->mem[p - mem_min + 3].int_ = t;
  ctx->mem[p - mem_min + 2].int_ = 0;
  return p;
}

halfword overbar(ctex_t *ctx, halfword b, scaled k, scaled t) {
  halfword q;
  halfword p = new_kern(ctx, k);
  ctx->mem[p - mem_min].hh.rh = b;
  q = fraction_rule(ctx, t);
  ctx->mem[q - mem_min].hh.rh = p;
  p = new_kern(ctx, t);
  ctx->mem[p - mem_min].hh.rh = q;
  return vpackage(ctx, p, 0, 1, 1073741823);
}

halfword char_box(ctex_t *ctx, internal_font_number f, quarterword c) {
  halfword p;
  four_quarters q = ctx->font_info[ctx->fnt_infos.char_base[f] + c].qqqq;
  uint8_t hd = q.b1;
  halfword b = new_null_box(ctx);
  ctx->mem[b - mem_min + 1].int_ =
      ctx->font_info[ctx->fnt_infos.width_base[f] + q.b0].int_ +
      ctx->font_info[ctx->fnt_infos.italic_base[f] + (q.b2 / 4)].int_;
  ctx->mem[b - mem_min + 3].int_ =
      ctx->font_info[ctx->fnt_infos.height_base[f] + (hd / 16)].int_;
  ctx->mem[b - mem_min + 2].int_ =
      ctx->font_info[ctx->fnt_infos.depth_base[f] + (hd & 15)].int_;
  p = get_avail(ctx);
  ctx->mem[p - mem_min].hh.U2.b1 = c;
  ctx->mem[p - mem_min].hh.U2.b0 = f;
  ctx->mem[b - mem_min + 5].hh.rh = p;
  return b;
}

void stack_into_box(ctex_t *ctx, halfword b, internal_font_number f,
                    quarterword c) {
  halfword p = char_box(ctx, f, c);
  ctx->mem[p - mem_min].hh.rh = ctx->mem[b - mem_min + 5].hh.rh;
  ctx->mem[b - mem_min + 5].hh.rh = p;
  ctx->mem[b - mem_min + 3].int_ = ctx->mem[p - mem_min + 3].int_;
}

scaled height_plus_depth(ctex_t *ctx, internal_font_number f, quarterword c) {
  four_quarters q = ctx->font_info[ctx->fnt_infos.char_base[f] + c].qqqq;
  uint8_t hd = q.b1;
  return ctx->font_info[ctx->fnt_infos.height_base[f] + (hd / 16)].int_ +
         ctx->font_info[ctx->fnt_infos.depth_base[f] + (hd & 15)].int_;
}

halfword var_delimiter(ctex_t *ctx, halfword d, small_number s, scaled v) {
  halfword b;
  internal_font_number f = 0, g;
  quarterword c, y;
  integer m, n;
  scaled u, w = 0;
  four_quarters q;
  uint8_t hd;
  four_quarters r;
  bool_t large_attempt = false;
  small_number z = ctx->mem[d - mem_min].qqqq.b0;
  quarterword x = ctx->mem[d - mem_min].qqqq.b1;
  while (true) {
    if (z || x) {
      z += s + 16;
      do {
        z -= 16;
        g = ctx->eqtb[z + 10835].hh.rh;
        if (g) {
          y = x;
          if ((y >= ctx->fnt_infos.font_bc[g]) &&
              (y <= ctx->fnt_infos.font_ec[g])) {
          _L22:
            q = ctx->font_info[ctx->fnt_infos.char_base[g] + y].qqqq;
            if (q.b0 > 0) {
              if ((q.b2 & 3) == 3) {
                f = g;
                c = y;
                goto _L40;
              }
              hd = q.b1;
              u = ctx->font_info[ctx->fnt_infos.height_base[g] + (hd / 16)]
                      .int_ +
                  ctx->font_info[ctx->fnt_infos.depth_base[g] + (hd & 15)].int_;
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
    z = ctx->mem[d - mem_min].qqqq.b2;
    x = ctx->mem[d - mem_min].qqqq.b3;
  }
_L40:
  if (f) {
    if ((q.b2 & 3) == 3) {
      b = new_null_box(ctx);
      ctx->mem[b - mem_min].hh.U2.b0 = 1;
      r = ctx->font_info[ctx->fnt_infos.exten_base[f] + q.b3].qqqq;
      c = r.b3;
      u = height_plus_depth(ctx, f, c);
      w = 0;
      q = ctx->font_info[ctx->fnt_infos.char_base[f] + c].qqqq;
      ctx->mem[b - mem_min + 1].int_ =
          ctx->font_info[ctx->fnt_infos.width_base[f] + q.b0].int_ +
          ctx->font_info[ctx->fnt_infos.italic_base[f] + (q.b2 / 4)].int_;
      c = r.b2;
      if (c)
        w += height_plus_depth(ctx, f, c);
      c = r.b1;
      if (c)
        w += height_plus_depth(ctx, f, c);
      c = r.b0;
      if (c)
        w += height_plus_depth(ctx, f, c);
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
        stack_into_box(ctx, b, f, c);
      c = r.b3;
      for (m = 1; m <= n; ++m)
        stack_into_box(ctx, b, f, c);
      c = r.b1;
      if (c) {
        stack_into_box(ctx, b, f, c);
        c = r.b3;
        for (m = 1; m <= n; ++m)
          stack_into_box(ctx, b, f, c);
      }
      c = r.b0;
      if (c)
        stack_into_box(ctx, b, f, c);
      ctx->mem[b - mem_min + 2].int_ = w - ctx->mem[b - mem_min + 3].int_;
    } else {
      b = char_box(ctx, f, c);
    }
  } else {
    b = new_null_box(ctx);
    ctx->mem[b - mem_min + 1].int_ = ctx->eqtb[12741].int_;
  }
  (ctx->mem[b - mem_min + 4].int_ =
       (half(ctx,
             ctx->mem[b - mem_min + 3].int_ - ctx->mem[b - mem_min + 2].int_) -
        (ctx->font_info
             [(ctx->fnt_infos.param_base[((ctx->eqtb[s + 10837].hh).rh)] + 22)]
                 .int_)));
  return b;
}

halfword rebox(ctex_t *ctx, halfword b, scaled w) {
  halfword p;
  internal_font_number f;
  scaled v;
  if ((ctx->mem[b - mem_min + 1].int_ != w) &&
      (ctx->mem[b - mem_min + 5].hh.rh != (-1073741824))) {
    if (ctx->mem[b - mem_min].hh.U2.b0 == 1)
      b = hpack(ctx, b, 0, 1);
    p = ctx->mem[b - mem_min + 5].hh.rh;
    if ((p >= ctx->hi_mem_min) &&
        (ctx->mem[p - mem_min].hh.rh == (-1073741824))) {
      f = ctx->mem[p - mem_min].hh.U2.b0;
      v = ctx->font_info[ctx->fnt_infos.width_base[f] +
                         ctx->font_info[ctx->fnt_infos.char_base[f] +
                                        ctx->mem[p - mem_min].hh.U2.b1]
                             .qqqq.b0]
              .int_;
      if (v != ctx->mem[b - mem_min + 1].int_)
        ctx->mem[p - mem_min].hh.rh =
            new_kern(ctx, ctx->mem[b - mem_min + 1].int_ - v);
    }
    free_node(ctx, b, 7);
    b = new_glue(ctx, 12);
    ctx->mem[b - mem_min].hh.rh = p;
    while (ctx->mem[p - mem_min].hh.rh != (-1073741824))
      p = ctx->mem[p - mem_min].hh.rh;
    ctx->mem[p - mem_min].hh.rh = new_glue(ctx, 12);
    return hpack(ctx, b, w, 0);
  } else {
    ctx->mem[b - mem_min + 1].int_ = w;
    return b;
  }
}

halfword math_glue(ctex_t *ctx, halfword g, scaled m) {
  halfword p;
  integer n = x_over_n(ctx, m, 65536);
  scaled f = ctx->remainder_;
  if (f < 0) {
    --n;
    f += 65536;
  }
  p = get_node(ctx, 4);
  (ctx->mem[p - mem_min + 1].int_ = mult_and_add(
       ctx, n, ctx->mem[g - mem_min + 1].int_,
       xn_over_d(ctx, ctx->mem[g - mem_min + 1].int_, f, 65536), 1073741823));
  ctx->mem[p - mem_min].hh.U2.b0 = ctx->mem[g - mem_min].hh.U2.b0;
  if (!ctx->mem[p - mem_min].hh.U2.b0)
    (ctx->mem[p - mem_min + 2].int_ = mult_and_add(
         ctx, n, ctx->mem[g - mem_min + 2].int_,
         xn_over_d(ctx, ctx->mem[g - mem_min + 2].int_, f, 65536), 1073741823));
  else
    ctx->mem[p - mem_min + 2].int_ = ctx->mem[g - mem_min + 2].int_;
  ctx->mem[p - mem_min].hh.U2.b1 = ctx->mem[g - mem_min].hh.U2.b1;
  if (!ctx->mem[p - mem_min].hh.U2.b1)
    (ctx->mem[p - mem_min + 3].int_ = mult_and_add(
         ctx, n, ctx->mem[g - mem_min + 3].int_,
         xn_over_d(ctx, ctx->mem[g - mem_min + 3].int_, f, 65536), 1073741823));
  else
    ctx->mem[p - mem_min + 3].int_ = ctx->mem[g - mem_min + 3].int_;
  return p;
}

void math_kern(ctex_t *ctx, halfword p, scaled m) {
  integer n;
  scaled f;
  if (ctx->mem[p - mem_min].hh.U2.b1 != 99)
    return;
  n = x_over_n(ctx, m, 65536);
  f = ctx->remainder_;
  if (f < 0) {
    --n;
    f += 65536;
  }
  (ctx->mem[p - mem_min + 1].int_ = mult_and_add(
       ctx, n, ctx->mem[p - mem_min + 1].int_,
       xn_over_d(ctx, ctx->mem[p - mem_min + 1].int_, f, 65536), 1073741823));
  ctx->mem[p - mem_min].hh.U2.b1 = 1;
}

void flush_math(ctex_t *ctx) {
  flush_node_list(ctx, ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh);
  flush_node_list(ctx, ctx->cur_list.aux_field.int_);
  ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh = -1073741824;
  ctx->cur_list.tail_field = ctx->cur_list.head_field;
  ctx->cur_list.aux_field.int_ = -1073741824;
}

halfword clean_box(ctex_t *ctx, halfword p, small_number s) {
  halfword q;
  small_number save_style;
  halfword x, r;
  switch (ctx->mem[p - mem_min].hh.rh) {
  case 1:
    ctx->cur_mlist = new_noad(ctx);
    ctx->mem[ctx->cur_mlist - mem_min + 1] = ctx->mem[p - mem_min];
    break;
  case 2:
    q = ctx->mem[p - mem_min].hh.lh;
    goto _L40;
    break;
  case 3:
    ctx->cur_mlist = ctx->mem[p - mem_min].hh.lh;
    break;
  default:
    q = new_null_box(ctx);
    goto _L40;
    break;
  }
  save_style = ctx->cur_style;
  ctx->cur_style = s;
  ctx->mlist_penalties = false;
  mlist_to_hlist(ctx);
  q = ctx->mem[mem_max - mem_min - 3].hh.rh;
  ctx->cur_style = save_style;
  if (ctx->cur_style < 4)
    ctx->cur_size = 0;
  else
    ctx->cur_size = ((ctx->cur_style - 2) / 2) * 16;
  ctx->cur_mu = x_over_n(
      ctx,
      ctx->font_info[ctx->fnt_infos
                         .param_base[ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                     6]
          .int_,
      18);
_L40:
  if ((q >= ctx->hi_mem_min) || (q == (-1073741824))) {
    x = hpack(ctx, q, 0, 1);
  } else if ((ctx->mem[q - mem_min].hh.rh == (-1073741824)) &&
             (ctx->mem[q - mem_min].hh.U2.b0 <= 1) &&
             (!ctx->mem[q - mem_min + 4].int_))
    x = q;
  else
    x = hpack(ctx, q, 0, 1);
  q = ctx->mem[x - mem_min + 5].hh.rh;
  if (q < ctx->hi_mem_min)
    return x;
  r = ctx->mem[q - mem_min].hh.rh;
  if (r == (-1073741824))
    return x;
  if (ctx->mem[r - mem_min].hh.rh != (-1073741824))
    return x;
  if (r >= ctx->hi_mem_min)
    return x;
  if (ctx->mem[r - mem_min].hh.U2.b0 == 11) {
    free_node(ctx, r, 2);
    ctx->mem[q - mem_min].hh.rh = -1073741824;
  }
  return x;
}

void fetch(ctex_t *ctx, halfword a) {
  ctx->cur_c = ctx->mem[a - mem_min].hh.U2.b1;
  ctx->cur_f =
      ctx->eqtb[ctx->mem[a - mem_min].hh.U2.b0 + ctx->cur_size + 10835].hh.rh;
  if (!ctx->cur_f) {
    print_nl(ctx, 262);
    print(ctx, 338);
    print_size(ctx, ctx->cur_size);
    print_char(ctx, 32);
    print_int(ctx, ctx->mem[a - mem_min].hh.U2.b0);
    print(ctx, 883);
    print(ctx, ctx->cur_c);
    print_char(ctx, 41);
    ctx->help_ptr = 4;
    ctx->help_line[3] = 884;
    ctx->help_line[2] = 885;
    ctx->help_line[1] = 886;
    ctx->help_line[0] = 887;
    error(ctx);
    ctx->cur_i = ctx->null_character;
    ctx->mem[a - mem_min].hh.rh = 0;
    return;
  }
  if ((ctx->cur_c >= ctx->fnt_infos.font_bc[ctx->cur_f]) &&
      (ctx->cur_c <= ctx->fnt_infos.font_ec[ctx->cur_f]))
    ctx->cur_i =
        ctx->font_info[ctx->fnt_infos.char_base[ctx->cur_f] + ctx->cur_c].qqqq;
  else
    ctx->cur_i = ctx->null_character;
  if (ctx->cur_i.b0 <= 0) {
    char_warning(ctx, ctx->cur_f, ctx->cur_c);
    ctx->mem[a - mem_min].hh.rh = 0;
  }
}

void make_over(ctex_t *ctx, halfword q) {
  (ctx->mem[q - mem_min + 1].hh.lh = overbar(
       ctx, clean_box(ctx, q + 1, ((ctx->cur_style / 2) * 2) + 1),
       ctx->font_info[ctx->fnt_infos
                          .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                      8]
               .int_ *
           3,
       ctx->font_info[ctx->fnt_infos
                          .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                      8]
           .int_));
  ctx->mem[q - mem_min + 1].hh.rh = 2;
}

void make_under(ctex_t *ctx, halfword q) {
  halfword y;
  scaled delta;
  halfword x = clean_box(ctx, q + 1, ctx->cur_style);
  halfword p = new_kern(
      ctx,
      ctx->font_info[ctx->fnt_infos
                         .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                     8]
              .int_ *
          3);
  ctx->mem[x - mem_min].hh.rh = p;
  ctx->mem[p - mem_min].hh.rh = fraction_rule(
      ctx,
      ctx->font_info[ctx->fnt_infos
                         .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                     8]
          .int_);
  y = vpackage(ctx, x, 0, 1, 1073741823);
  delta =
      ctx->mem[y - mem_min + 3].int_ + ctx->mem[y - mem_min + 2].int_ +
      ctx->font_info[ctx->fnt_infos
                         .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                     8]
          .int_;
  ctx->mem[y - mem_min + 3].int_ = ctx->mem[x - mem_min + 3].int_;
  ctx->mem[y - mem_min + 2].int_ = delta - ctx->mem[y - mem_min + 3].int_;
  ctx->mem[q - mem_min + 1].hh.lh = y;
  ctx->mem[q - mem_min + 1].hh.rh = 2;
}

void make_vcenter(ctex_t *ctx, halfword q) {
  scaled delta;
  halfword v = ctx->mem[q - mem_min + 1].hh.lh;
  if (ctx->mem[v - mem_min].hh.U2.b0 != 1)
    confusion(ctx, 539);
  delta = ctx->mem[v - mem_min + 3].int_ + ctx->mem[v - mem_min + 2].int_;
  ctx->mem[v - mem_min + 3].int_ =
      ctx->font_info[ctx->fnt_infos
                         .param_base[ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                     22]
          .int_ +
      half(ctx, delta);
  ctx->mem[v - mem_min + 2].int_ = delta - ctx->mem[v - mem_min + 3].int_;
}

void make_radical(ctex_t *ctx, halfword q) {
  halfword y;
  scaled delta, clr;
  halfword x = clean_box(ctx, q + 1, ((ctx->cur_style / 2) * 2) + 1);
  if (ctx->cur_style < 2) {
    (clr = (ctx->font_info[ctx->fnt_infos.param_base
                               [ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                           8]
                .int_ +
            (abs(ctx->font_info[ctx->fnt_infos.param_base
                                    [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                                5]
                     .int_) /
             4)));
  } else {
    clr =
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                       8]
            .int_;
    clr += abs(clr) / 4;
  }
  (y = var_delimiter(
       ctx, q + 4, ctx->cur_size,
       (ctx->mem[x - mem_min + 3].int_ + ctx->mem[x - mem_min + 2].int_ + clr +
        (ctx->font_info[(ctx->fnt_infos.param_base
                             [ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                         8)]
             .int_))));
  delta = ctx->mem[y - mem_min + 2].int_ - ctx->mem[x - mem_min + 3].int_ -
          ctx->mem[x - mem_min + 2].int_ - clr;
  if (delta > 0)
    clr += half(ctx, delta);
  ctx->mem[y - mem_min + 4].int_ = -(ctx->mem[x - mem_min + 3].int_ + clr);
  ctx->mem[y - mem_min].hh.rh =
      overbar(ctx, x, clr, ctx->mem[y - mem_min + 3].int_);
  ctx->mem[q - mem_min + 1].hh.lh = hpack(ctx, y, 0, 1);
  ctx->mem[q - mem_min + 1].hh.rh = 2;
}

void make_math_accent(ctex_t *ctx, halfword q) {
  halfword p, x, y;
  integer a;
  quarterword c;
  internal_font_number f;
  four_quarters i;
  scaled s = 0, h, delta, w;
  fetch(ctx, q + 4);
  if (ctx->cur_i.b0 <= 0)
    return;
  i = ctx->cur_i;
  c = ctx->cur_c;
  f = ctx->cur_f;
  if (ctx->mem[q - mem_min + 1].hh.rh == 1) {
    fetch(ctx, q + 1);
    if ((ctx->cur_i.b2 & 3) == 1) {
      a = ctx->fnt_infos.lig_kern_base[ctx->cur_f] + ctx->cur_i.b3;
      ctx->cur_i = ctx->font_info[a].qqqq;
      if (ctx->cur_i.b0 > 128) {
        a = ctx->fnt_infos.lig_kern_base[ctx->cur_f] + (ctx->cur_i.b2 * 256) +
            ctx->cur_i.b3;
        ctx->cur_i = ctx->font_info[a].qqqq;
      }
      while (true) {
        if (ctx->cur_i.b1 == ctx->fnt_infos.skew_char[ctx->cur_f]) {
          if (ctx->cur_i.b2 >= 128) {
            if (ctx->cur_i.b0 <= 128)
              s = ctx->font_info[ctx->fnt_infos.kern_base[ctx->cur_f] +
                                 (ctx->cur_i.b2 * 256) + ctx->cur_i.b3]
                      .int_;
          }
          goto _L31;
        }
        if (ctx->cur_i.b0 >= 128)
          goto _L31;
        a += ctx->cur_i.b0 + 1;
        ctx->cur_i = ctx->font_info[a].qqqq;
      }
    }
  }
_L31:
  x = clean_box(ctx, q + 1, ((ctx->cur_style / 2) * 2) + 1);
  w = ctx->mem[x - mem_min + 1].int_;
  h = ctx->mem[x - mem_min + 3].int_;
  while (true) {
    if ((i.b2 & 3) != 2)
      goto _L30;
    y = i.b3;
    i = ctx->font_info[ctx->fnt_infos.char_base[f] + y].qqqq;
    if (i.b0 <= 0)
      goto _L30;
    if (ctx->font_info[ctx->fnt_infos.width_base[f] + i.b0].int_ > w)
      goto _L30;
    c = y;
  }
_L30:
  if (h < ctx->font_info[ctx->fnt_infos.param_base[f] + 5].int_)
    delta = h;
  else
    delta = ctx->font_info[ctx->fnt_infos.param_base[f] + 5].int_;
  if (ctx->mem[q - mem_min + 2].hh.rh || ctx->mem[q - mem_min + 3].hh.rh) {
    if (ctx->mem[q - mem_min + 1].hh.rh == 1) {
      flush_node_list(ctx, x);
      x = new_noad(ctx);
      ctx->mem[x - mem_min + 1] = ctx->mem[q - mem_min + 1];
      ctx->mem[x - mem_min + 2] = ctx->mem[q - mem_min + 2];
      ctx->mem[x - mem_min + 3] = ctx->mem[q - mem_min + 3];
      ctx->mem[q - mem_min + 2].hh = ctx->empty_field;
      ctx->mem[q - mem_min + 3].hh = ctx->empty_field;
      ctx->mem[q - mem_min + 1].hh.rh = 3;
      ctx->mem[q - mem_min + 1].hh.lh = x;
      x = clean_box(ctx, q + 1, ctx->cur_style);
      delta += ctx->mem[x - mem_min + 3].int_ - h;
      h = ctx->mem[x - mem_min + 3].int_;
    }
  }
  y = char_box(ctx, f, c);
  ctx->mem[y - mem_min + 4].int_ =
      s + half(ctx, w - ctx->mem[y - mem_min + 1].int_);
  ctx->mem[y - mem_min + 1].int_ = 0;
  p = new_kern(ctx, -delta);
  ctx->mem[p - mem_min].hh.rh = x;
  ctx->mem[y - mem_min].hh.rh = p;
  y = vpackage(ctx, y, 0, 1, 1073741823);
  ctx->mem[y - mem_min + 1].int_ = ctx->mem[x - mem_min + 1].int_;
  if (ctx->mem[y - mem_min + 3].int_ < h) {
    p = new_kern(ctx, h - ctx->mem[y - mem_min + 3].int_);
    ctx->mem[p - mem_min].hh.rh = ctx->mem[y - mem_min + 5].hh.rh;
    ctx->mem[y - mem_min + 5].hh.rh = p;
    ctx->mem[y - mem_min + 3].int_ = h;
  }
  ctx->mem[q - mem_min + 1].hh.lh = y;
  ctx->mem[q - mem_min + 1].hh.rh = 2;
}

void make_fraction(ctex_t *ctx, halfword q) {
  halfword p, v, x, y, z;
  scaled delta, delta1, delta2, shift_up, shift_down, clr;
  if (ctx->mem[q - mem_min + 1].int_ == 1073741824)
    ctx->mem[q - mem_min + 1].int_ =
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                       8]
            .int_;
  x = clean_box(ctx, q + 2, ctx->cur_style - ((ctx->cur_style / 6) * 2) + 2);
  z = clean_box(ctx, q + 3,
                ((ctx->cur_style / 2) * 2) - ((ctx->cur_style / 6) * 2) + 3);
  if (ctx->mem[x - mem_min + 1].int_ < ctx->mem[z - mem_min + 1].int_)
    x = rebox(ctx, x, ctx->mem[z - mem_min + 1].int_);
  else
    z = rebox(ctx, z, ctx->mem[x - mem_min + 1].int_);
  if (ctx->cur_style < 2) {
    shift_up =
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                       8]
            .int_;
    shift_down =
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                       11]
            .int_;
  } else {
    shift_down =
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                       12]
            .int_;
    if (ctx->mem[q - mem_min + 1].int_)
      shift_up = ctx->font_info[ctx->fnt_infos.param_base
                                    [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                                9]
                     .int_;
    else
      shift_up = ctx->font_info[ctx->fnt_infos.param_base
                                    [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                                10]
                     .int_;
  }
  if (!ctx->mem[q - mem_min + 1].int_) {
    if (ctx->cur_style < 2)
      clr = ctx->font_info[ctx->fnt_infos.param_base
                               [ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                           8]
                .int_ *
            7;
    else
      clr = ctx->font_info[ctx->fnt_infos.param_base
                               [ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                           8]
                .int_ *
            3;
    delta = half(ctx, clr - shift_up + ctx->mem[x - mem_min + 2].int_ +
                          ctx->mem[z - mem_min + 3].int_ - shift_down);
    if (delta > 0) {
      shift_up += delta;
      shift_down += delta;
    }
  } else {
    if (ctx->cur_style < 2)
      clr = ctx->mem[q - mem_min + 1].int_ * 3;
    else
      clr = ctx->mem[q - mem_min + 1].int_;
    delta = half(ctx, ctx->mem[q - mem_min + 1].int_);
    (delta1 = (clr - shift_up + ctx->mem[x - mem_min + 2].int_ +
               ctx->font_info[ctx->fnt_infos.param_base
                                  [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                              22]
                   .int_ +
               delta));
    (delta2 = (clr -
               ctx->font_info[ctx->fnt_infos.param_base
                                  [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                              22]
                   .int_ +
               delta + ctx->mem[z - mem_min + 3].int_ - shift_down));
    if (delta1 > 0)
      shift_up += delta1;
    if (delta2 > 0)
      shift_down += delta2;
  }
  v = new_null_box(ctx);
  ctx->mem[v - mem_min].hh.U2.b0 = 1;
  ctx->mem[v - mem_min + 3].int_ = shift_up + ctx->mem[x - mem_min + 3].int_;
  ctx->mem[v - mem_min + 2].int_ = ctx->mem[z - mem_min + 2].int_ + shift_down;
  ctx->mem[v - mem_min + 1].int_ = ctx->mem[x - mem_min + 1].int_;
  if (!ctx->mem[q - mem_min + 1].int_) {
    p = new_kern(ctx, shift_up - ctx->mem[x - mem_min + 2].int_ -
                          ctx->mem[z - mem_min + 3].int_ + shift_down);
    ctx->mem[p - mem_min].hh.rh = z;
  } else {
    y = fraction_rule(ctx, ctx->mem[q - mem_min + 1].int_);
    (p = new_kern(ctx,
                  ctx->font_info[ctx->fnt_infos.param_base
                                     [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                                 22]
                          .int_ -
                      delta - ctx->mem[z - mem_min + 3].int_ + shift_down));
    ctx->mem[y - mem_min].hh.rh = p;
    ctx->mem[p - mem_min].hh.rh = z;
    p = new_kern(
        ctx, shift_up - ctx->mem[x - mem_min + 2].int_ -
                 ctx->font_info[ctx->fnt_infos.param_base
                                    [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                                22]
                     .int_ -
                 delta);
    ctx->mem[p - mem_min].hh.rh = y;
  }
  ctx->mem[x - mem_min].hh.rh = p;
  ctx->mem[v - mem_min + 5].hh.rh = x;
  if (ctx->cur_style < 2)
    delta =
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                       20]
            .int_;
  else
    delta =
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                       21]
            .int_;
  x = var_delimiter(ctx, q + 4, ctx->cur_size, delta);
  ctx->mem[x - mem_min].hh.rh = v;
  z = var_delimiter(ctx, q + 5, ctx->cur_size, delta);
  ctx->mem[v - mem_min].hh.rh = z;
  ctx->mem[q - mem_min + 1].int_ = hpack(ctx, x, 0, 1);
}

scaled make_op(ctex_t *ctx, halfword q) {
  scaled delta, shift_up, shift_down;
  halfword p, v, x, y, z;
  quarterword c;
  four_quarters i;
  if ((!ctx->mem[q - mem_min].hh.U2.b1) && (ctx->cur_style < 2))
    ctx->mem[q - mem_min].hh.U2.b1 = 1;
  if (ctx->mem[q - mem_min + 1].hh.rh == 1) {
    fetch(ctx, q + 1);
    if ((ctx->cur_style < 2) && ((ctx->cur_i.b2 & 3) == 2)) {
      c = ctx->cur_i.b3;
      i = ctx->font_info[ctx->fnt_infos.char_base[ctx->cur_f] + c].qqqq;
      if (i.b0 > 0) {
        ctx->cur_c = c;
        ctx->cur_i = i;
        ctx->mem[q - mem_min + 1].hh.U2.b1 = c;
      }
    }
    delta = ctx->font_info[ctx->fnt_infos.italic_base[ctx->cur_f] +
                           (ctx->cur_i.b2 / 4)]
                .int_;
    x = clean_box(ctx, q + 1, ctx->cur_style);
    if (ctx->mem[q - mem_min + 3].hh.rh &&
        (ctx->mem[q - mem_min].hh.U2.b1 != 1))
      ctx->mem[x - mem_min + 1].int_ -= delta;
    (ctx->mem[x - mem_min + 4].int_ =
         (half(ctx, ctx->mem[x - mem_min + 3].int_ -
                        ctx->mem[x - mem_min + 2].int_) -
          (ctx->font_info[(ctx->fnt_infos.param_base[(
                               (ctx->eqtb[ctx->cur_size + 10837].hh).rh)] +
                           22)]
               .int_)));
    ctx->mem[q - mem_min + 1].hh.rh = 2;
    ctx->mem[q - mem_min + 1].hh.lh = x;
  } else {
    delta = 0;
  }
  if (ctx->mem[q - mem_min].hh.U2.b1 != 1)
    return delta;
  x = clean_box(ctx, q + 2,
                ((ctx->cur_style / 4) * 2) + (ctx->cur_style & 1) + 4);
  y = clean_box(ctx, q + 1, ctx->cur_style);
  z = clean_box(ctx, q + 3, ((ctx->cur_style / 4) * 2) + 5);
  v = new_null_box(ctx);
  ctx->mem[v - mem_min].hh.U2.b0 = 1;
  ctx->mem[v - mem_min + 1].int_ = ctx->mem[y - mem_min + 1].int_;
  if (ctx->mem[x - mem_min + 1].int_ > ctx->mem[v - mem_min + 1].int_)
    ctx->mem[v - mem_min + 1].int_ = ctx->mem[x - mem_min + 1].int_;
  if (ctx->mem[z - mem_min + 1].int_ > ctx->mem[v - mem_min + 1].int_)
    ctx->mem[v - mem_min + 1].int_ = ctx->mem[z - mem_min + 1].int_;
  x = rebox(ctx, x, ctx->mem[v - mem_min + 1].int_);
  y = rebox(ctx, y, ctx->mem[v - mem_min + 1].int_);
  z = rebox(ctx, z, ctx->mem[v - mem_min + 1].int_);
  ctx->mem[x - mem_min + 4].int_ = half(ctx, delta);
  ctx->mem[z - mem_min + 4].int_ = -ctx->mem[x - mem_min + 4].int_;
  ctx->mem[v - mem_min + 3].int_ = ctx->mem[y - mem_min + 3].int_;
  ctx->mem[v - mem_min + 2].int_ = ctx->mem[y - mem_min + 2].int_;
  if (!ctx->mem[q - mem_min + 2].hh.rh) {
    free_node(ctx, x, 7);
    ctx->mem[v - mem_min + 5].hh.rh = y;
  } else {
    shift_up =
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                       11]
            .int_ -
        ctx->mem[x - mem_min + 2].int_;
    if (shift_up <
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                       9]
            .int_)
      shift_up = ctx->font_info[ctx->fnt_infos.param_base
                                    [ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                                9]
                     .int_;
    p = new_kern(ctx, shift_up);
    ctx->mem[p - mem_min].hh.rh = y;
    ctx->mem[x - mem_min].hh.rh = p;
    p = new_kern(
        ctx,
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                       13]
            .int_);
    ctx->mem[p - mem_min].hh.rh = x;
    ctx->mem[v - mem_min + 5].hh.rh = p;
    (ctx->mem[v - mem_min + 3].int_ +=
     (ctx->font_info[ctx->fnt_infos
                         .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                     13]
          .int_ +
      ctx->mem[x - mem_min + 3].int_ + (ctx->mem[(x - mem_min + 2)].int_) +
      shift_up));
  }
  if (!ctx->mem[q - mem_min + 3].hh.rh) {
    free_node(ctx, z, 7);
  } else {
    shift_down =
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                       12]
            .int_ -
        ctx->mem[z - mem_min + 3].int_;
    if (shift_down <
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                       10]
            .int_)
      shift_down = ctx->font_info[ctx->fnt_infos.param_base
                                      [ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                                  10]
                       .int_;
    p = new_kern(ctx, shift_down);
    ctx->mem[y - mem_min].hh.rh = p;
    ctx->mem[p - mem_min].hh.rh = z;
    p = new_kern(
        ctx,
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                       13]
            .int_);
    ctx->mem[z - mem_min].hh.rh = p;
    (ctx->mem[v - mem_min + 2].int_ +=
     (ctx->font_info[ctx->fnt_infos
                         .param_base[ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                     13]
          .int_ +
      ctx->mem[z - mem_min + 3].int_ + (ctx->mem[(z - mem_min + 2)].int_) +
      shift_down));
  }
  ctx->mem[q - mem_min + 1].int_ = v;
  return delta;
}

void make_ord(ctex_t *ctx, halfword q) {
  integer a;
  halfword p, r;
_L20:
  if (!ctx->mem[q - mem_min + 3].hh.rh) {
    if (!ctx->mem[q - mem_min + 2].hh.rh) {
      if (ctx->mem[q - mem_min + 1].hh.rh == 1) {
        p = ctx->mem[q - mem_min].hh.rh;
        if (p != (-1073741824)) {
          if ((ctx->mem[p - mem_min].hh.U2.b0 >= 16) &&
              (ctx->mem[p - mem_min].hh.U2.b0 <= 22)) {
            if (ctx->mem[p - mem_min + 1].hh.rh == 1) {
              if (ctx->mem[p - mem_min + 1].hh.U2.b0 ==
                  ctx->mem[q - mem_min + 1].hh.U2.b0) {
                ctx->mem[q - mem_min + 1].hh.rh = 4;
                fetch(ctx, q + 1);
                if ((ctx->cur_i.b2 & 3) == 1) {
                  a = ctx->fnt_infos.lig_kern_base[ctx->cur_f] + ctx->cur_i.b3;
                  ctx->cur_c = ctx->mem[p - mem_min + 1].hh.U2.b1;
                  ctx->cur_i = ctx->font_info[a].qqqq;
                  if (ctx->cur_i.b0 > 128) {
                    a = ctx->fnt_infos.lig_kern_base[ctx->cur_f] +
                        (ctx->cur_i.b2 * 256) + ctx->cur_i.b3;
                    ctx->cur_i = ctx->font_info[a].qqqq;
                  }
                  while (true) {
                    if (ctx->cur_i.b1 == ctx->cur_c) {
                      if (ctx->cur_i.b0 <= 128) {
                        if (ctx->cur_i.b2 >= 128) {
                          p = new_kern(
                              ctx, ctx->font_info
                                       [ctx->fnt_infos.kern_base[ctx->cur_f] +
                                        (ctx->cur_i.b2 * 256) + ctx->cur_i.b3]
                                           .int_);
                          ctx->mem[p - mem_min].hh.rh =
                              ctx->mem[q - mem_min].hh.rh;
                          ctx->mem[q - mem_min].hh.rh = p;
                          goto _L10;
                        } else {
                          if (ctx->interrupt)
                            pause_for_instructions(ctx);
                          switch (ctx->cur_i.b2) {
                          case 1:
                          case 5:
                            ctx->mem[q - mem_min + 1].hh.U2.b1 = ctx->cur_i.b3;
                            break;
                          case 2:
                          case 6:
                            ctx->mem[p - mem_min + 1].hh.U2.b1 = ctx->cur_i.b3;
                            break;
                          case 3:
                          case 7:
                          case 11:
                            r = new_noad(ctx);
                            ctx->mem[r - mem_min + 1].hh.U2.b1 = ctx->cur_i.b3;
                            ctx->mem[r - mem_min + 1].hh.U2.b0 =
                                ctx->mem[q - mem_min + 1].hh.U2.b0;
                            ctx->mem[q - mem_min].hh.rh = r;
                            ctx->mem[r - mem_min].hh.rh = p;
                            if (ctx->cur_i.b2 < 11)
                              ctx->mem[r - mem_min + 1].hh.rh = 1;
                            else
                              ctx->mem[r - mem_min + 1].hh.rh = 4;
                            break;
                          default:
                            ctx->mem[q - mem_min].hh.rh =
                                ctx->mem[p - mem_min].hh.rh;
                            ctx->mem[q - mem_min + 1].hh.U2.b1 = ctx->cur_i.b3;
                            ctx->mem[q - mem_min + 3] =
                                ctx->mem[p - mem_min + 3];
                            ctx->mem[q - mem_min + 2] =
                                ctx->mem[p - mem_min + 2];
                            free_node(ctx, p, 4);
                            break;
                          }
                          if (ctx->cur_i.b2 > 3)
                            goto _L10;
                          ctx->mem[q - mem_min + 1].hh.rh = 1;
                          goto _L20;
                        }
                      }
                    }
                    if (ctx->cur_i.b0 >= 128)
                      goto _L10;
                    a += ctx->cur_i.b0 + 1;
                    ctx->cur_i = ctx->font_info[a].qqqq;
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

void make_scripts(ctex_t *ctx, halfword q, scaled delta) {
  halfword x, y, z;
  scaled shift_up, shift_down, clr;
  small_number t;
  halfword p = ctx->mem[q - mem_min + 1].int_;
  if (p >= ctx->hi_mem_min) {
    shift_up = 0;
    shift_down = 0;
  } else {
    z = hpack(ctx, p, 0, 1);
    if (ctx->cur_style < 4)
      t = 16;
    else
      t = 32;
    shift_up =
        ctx->mem[z - mem_min + 3].int_ -
        ctx->font_info[ctx->fnt_infos.param_base[ctx->eqtb[t + 10837].hh.rh] +
                       18]
            .int_;
    shift_down =
        ctx->mem[z - mem_min + 2].int_ +
        ctx->font_info[ctx->fnt_infos.param_base[ctx->eqtb[t + 10837].hh.rh] +
                       19]
            .int_;
    free_node(ctx, z, 7);
  }
  if (!ctx->mem[q - mem_min + 2].hh.rh) {
    x = clean_box(ctx, q + 3, ((ctx->cur_style / 4) * 2) + 5);
    ctx->mem[x - mem_min + 1].int_ += ctx->eqtb[12742].int_;
    if (shift_down <
        ctx->font_info[ctx->fnt_infos
                           .param_base[ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                       16]
            .int_)
      shift_down = ctx->font_info[ctx->fnt_infos.param_base
                                      [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                                  16]
                       .int_;
    clr = ctx->mem[x - mem_min + 3].int_ -
          (abs(ctx->font_info[ctx->fnt_infos.param_base
                                  [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                              5]
                   .int_ *
               4) /
           5);
    if (shift_down < clr)
      shift_down = clr;
    ctx->mem[x - mem_min + 4].int_ = shift_down;
  } else {
    x = clean_box(ctx, q + 2,
                  ((ctx->cur_style / 4) * 2) + (ctx->cur_style & 1) + 4);
    ctx->mem[x - mem_min + 1].int_ += ctx->eqtb[12742].int_;
    if (ctx->cur_style & 1) {
      clr = ctx->font_info[ctx->fnt_infos.param_base
                               [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                           15]
                .int_;
    } else if (ctx->cur_style < 2)
      clr = ctx->font_info[ctx->fnt_infos.param_base
                               [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                           13]
                .int_;
    else
      clr = ctx->font_info[ctx->fnt_infos.param_base
                               [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                           14]
                .int_;
    if (shift_up < clr)
      shift_up = clr;
    clr = ctx->mem[x - mem_min + 2].int_ +
          (abs(ctx->font_info[ctx->fnt_infos.param_base
                                  [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                              5]
                   .int_) /
           4);
    if (shift_up < clr)
      shift_up = clr;
    if (!ctx->mem[q - mem_min + 3].hh.rh) {
      ctx->mem[x - mem_min + 4].int_ = -shift_up;
    } else {
      y = clean_box(ctx, q + 3, ((ctx->cur_style / 4) * 2) + 5);
      ctx->mem[y - mem_min + 1].int_ += ctx->eqtb[12742].int_;
      if (shift_down <
          ctx->font_info[ctx->fnt_infos.param_base
                             [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                         17]
              .int_)
        shift_down =
            ctx->font_info[ctx->fnt_infos.param_base
                               [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                           17]
                .int_;
      (clr = ((ctx->font_info[ctx->fnt_infos.param_base
                                  [ctx->eqtb[ctx->cur_size + 10838].hh.rh] +
                              8]
                   .int_ *
               4) -
              shift_up + ctx->mem[x - mem_min + 2].int_ +
              (ctx->mem[(y - mem_min + 3)].int_) - shift_down));
      if (clr > 0) {
        shift_down += clr;
        (clr =
             ((abs(ctx->font_info[ctx->fnt_infos.param_base
                                      [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                                  5]
                       .int_ *
                   4) /
               5) -
              shift_up + (ctx->mem[(x - mem_min + 2)].int_)));
        if (clr > 0) {
          shift_up += clr;
          shift_down -= clr;
        }
      }
      ctx->mem[x - mem_min + 4].int_ = delta;
      p = new_kern(ctx, shift_up - ctx->mem[x - mem_min + 2].int_ -
                            ctx->mem[y - mem_min + 3].int_ + shift_down);
      ctx->mem[x - mem_min].hh.rh = p;
      ctx->mem[p - mem_min].hh.rh = y;
      x = vpackage(ctx, x, 0, 1, 1073741823);
      ctx->mem[x - mem_min + 4].int_ = shift_down;
    }
  }
  if (ctx->mem[q - mem_min + 1].int_ == (-1073741824)) {
    ctx->mem[q - mem_min + 1].int_ = x;
    return;
  }
  p = ctx->mem[q - mem_min + 1].int_;
  while (ctx->mem[p - mem_min].hh.rh != (-1073741824))
    p = ctx->mem[p - mem_min].hh.rh;
  ctx->mem[p - mem_min].hh.rh = x;
}

small_number make_left_right(ctex_t *ctx, halfword q, small_number style,
                             scaled max_d, scaled max_h) {
  scaled delta, delta1, delta2;
  if (style < 4)
    ctx->cur_size = 0;
  else
    ctx->cur_size = ((style - 2) / 2) * 16;
  delta2 =
      max_d +
      ctx->font_info[ctx->fnt_infos
                         .param_base[ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                     22]
          .int_;
  delta1 = max_h + max_d - delta2;
  if (delta2 > delta1)
    delta1 = delta2;
  delta = (delta1 / 500) * ctx->eqtb[12181].int_;
  delta2 = delta1 + delta1 - ctx->eqtb[12740].int_;
  if (delta < delta2)
    delta = delta2;
  ctx->mem[q - mem_min + 1].int_ =
      var_delimiter(ctx, q + 1, ctx->cur_size, delta);
  return ctx->mem[q - mem_min].hh.U2.b0 - 10;
}

void mlist_to_hlist(ctex_t *ctx) {
  small_number save_style;
  halfword r = -1073741824;
  small_number r_type = 17, t;
  halfword p, x, y, z;
  integer pen;
  small_number s;
  scaled max_h = 0, max_d = 0, delta;
  halfword mlist = ctx->cur_mlist;
  bool_t penalties = ctx->mlist_penalties;
  small_number style = ctx->cur_style;
  halfword q = mlist;
  if (ctx->cur_style < 4)
    ctx->cur_size = 0;
  else
    ctx->cur_size = ((ctx->cur_style - 2) / 2) * 16;
  ctx->cur_mu = x_over_n(
      ctx,
      ctx->font_info[ctx->fnt_infos
                         .param_base[ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                     6]
          .int_,
      18);
  while (q != (-1073741824)) {
  _L21:
    delta = 0;
    switch (ctx->mem[q - mem_min].hh.U2.b0) {
    case 18:
      switch (r_type) {
      case 18:
      case 17:
      case 19:
      case 20:
      case 22:
      case 30:
        ctx->mem[q - mem_min].hh.U2.b0 = 16;
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
        ctx->mem[r - mem_min].hh.U2.b0 = 16;
      if (ctx->mem[q - mem_min].hh.U2.b0 == 31)
        goto _L80;
      break;
    case 30:
      goto _L80;
      break;
    case 25:
      make_fraction(ctx, q);
      goto _L82;
      break;
    case 17:
      delta = make_op(ctx, q);
      if (ctx->mem[q - mem_min].hh.U2.b1 == 1)
        goto _L82;
      break;
    case 16:
      make_ord(ctx, q);
      break;
    case 20:
    case 23:
      // blank case
      break;
    case 24:
      make_radical(ctx, q);
      break;
    case 27:
      make_over(ctx, q);
      break;
    case 26:
      make_under(ctx, q);
      break;
    case 28:
      make_math_accent(ctx, q);
      break;
    case 29:
      make_vcenter(ctx, q);
      break;
    case 14:
      ctx->cur_style = ctx->mem[q - mem_min].hh.U2.b1;
      if (ctx->cur_style < 4)
        ctx->cur_size = 0;
      else
        ctx->cur_size = ((ctx->cur_style - 2) / 2) * 16;
      ctx->cur_mu =
          x_over_n(ctx,
                   ctx->font_info[ctx->fnt_infos.param_base
                                      [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                                  6]
                       .int_,
                   18);
      goto _L81;
      break;
    case 15:
      switch (ctx->cur_style / 2) {
      case 0:
        p = ctx->mem[q - mem_min + 1].hh.lh;
        ctx->mem[q - mem_min + 1].hh.lh = -1073741824;
        break;
      case 1:
        p = ctx->mem[q - mem_min + 1].hh.rh;
        ctx->mem[q - mem_min + 1].hh.rh = -1073741824;
        break;
      case 2:
        p = ctx->mem[q - mem_min + 2].hh.lh;
        ctx->mem[q - mem_min + 2].hh.lh = -1073741824;
        break;
      case 3:
        p = ctx->mem[q - mem_min + 2].hh.rh;
        ctx->mem[q - mem_min + 2].hh.rh = -1073741824;
        break;
      }
      flush_node_list(ctx, ctx->mem[q - mem_min + 1].hh.lh);
      flush_node_list(ctx, ctx->mem[q - mem_min + 1].hh.rh);
      flush_node_list(ctx, ctx->mem[q - mem_min + 2].hh.lh);
      flush_node_list(ctx, ctx->mem[q - mem_min + 2].hh.rh);
      ctx->mem[q - mem_min].hh.U2.b0 = 14;
      ctx->mem[q - mem_min].hh.U2.b1 = ctx->cur_style;
      ctx->mem[q - mem_min + 1].int_ = 0;
      ctx->mem[q - mem_min + 2].int_ = 0;
      if (p != (-1073741824)) {
        z = ctx->mem[q - mem_min].hh.rh;
        ctx->mem[q - mem_min].hh.rh = p;
        while (ctx->mem[p - mem_min].hh.rh != (-1073741824))
          p = ctx->mem[p - mem_min].hh.rh;
        ctx->mem[p - mem_min].hh.rh = z;
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
      if (ctx->mem[q - mem_min + 3].int_ > max_h)
        max_h = ctx->mem[q - mem_min + 3].int_;
      if (ctx->mem[q - mem_min + 2].int_ > max_d)
        max_d = ctx->mem[q - mem_min + 2].int_;
      goto _L81;
      break;
    case 10:
      if (ctx->mem[q - mem_min].hh.U2.b1 == 99) {
        x = ctx->mem[q - mem_min + 1].hh.lh;
        y = math_glue(ctx, x, ctx->cur_mu);
        delete_glue_ref(ctx, x);
        ctx->mem[q - mem_min + 1].hh.lh = y;
        ctx->mem[q - mem_min].hh.U2.b1 = 0;
      } else if (ctx->cur_size && (ctx->mem[q - mem_min].hh.U2.b1 == 98)) {
        p = ctx->mem[q - mem_min].hh.rh;
        if (p != (-1073741824)) {
          if ((ctx->mem[p - mem_min].hh.U2.b0 == 10) ||
              (ctx->mem[p - mem_min].hh.U2.b0 == 11)) {
            ctx->mem[q - mem_min].hh.rh = ctx->mem[p - mem_min].hh.rh;
            ctx->mem[p - mem_min].hh.rh = -1073741824;
            flush_node_list(ctx, p);
          }
        }
      }
      goto _L81;
      break;
    case 11:
      math_kern(ctx, q, ctx->cur_mu);
      goto _L81;
      break;
    default:
      confusion(ctx, 888);
      break;
    }
    switch (ctx->mem[q - mem_min + 1].hh.rh) {
    case 1:
    case 4:
      fetch(ctx, q + 1);
      if (ctx->cur_i.b0 > 0) {
        delta = ctx->font_info[ctx->fnt_infos.italic_base[ctx->cur_f] +
                               (ctx->cur_i.b2 / 4)]
                    .int_;
        p = new_character(ctx, ctx->cur_f, ctx->cur_c);
        if ((ctx->mem[q - mem_min + 1].hh.rh == 4) &&
            ctx->font_info[ctx->fnt_infos.param_base[ctx->cur_f] + 2].int_)
          delta = 0;
        if ((!ctx->mem[q - mem_min + 3].hh.rh) && delta) {
          ctx->mem[p - mem_min].hh.rh = new_kern(ctx, delta);
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
      p = ctx->mem[q - mem_min + 1].hh.lh;
      break;
    case 3:
      ctx->cur_mlist = ctx->mem[q - mem_min + 1].hh.lh;
      save_style = ctx->cur_style;
      ctx->mlist_penalties = false;
      mlist_to_hlist(ctx);
      ctx->cur_style = save_style;
      if (ctx->cur_style < 4)
        ctx->cur_size = 0;
      else
        ctx->cur_size = ((ctx->cur_style - 2) / 2) * 16;
      ctx->cur_mu =
          x_over_n(ctx,
                   ctx->font_info[ctx->fnt_infos.param_base
                                      [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                                  6]
                       .int_,
                   18);
      p = hpack(ctx, ctx->mem[mem_max - mem_min - 3].hh.rh, 0, 1);
      break;
    default:
      confusion(ctx, 889);
      break;
    }
    ctx->mem[q - mem_min + 1].int_ = p;
    if ((!ctx->mem[q - mem_min + 3].hh.rh) &&
        (!ctx->mem[q - mem_min + 2].hh.rh))
      goto _L82;
    make_scripts(ctx, q, delta);
  _L82:
    z = hpack(ctx, ctx->mem[q - mem_min + 1].int_, 0, 1);
    if (ctx->mem[z - mem_min + 3].int_ > max_h)
      max_h = ctx->mem[z - mem_min + 3].int_;
    if (ctx->mem[z - mem_min + 2].int_ > max_d)
      max_d = ctx->mem[z - mem_min + 2].int_;
    free_node(ctx, z, 7);
  _L80:
    r = q;
    r_type = ctx->mem[r - mem_min].hh.U2.b0;
  _L81:
    q = ctx->mem[q - mem_min].hh.rh;
  }
  if (r_type == 18)
    ctx->mem[r - mem_min].hh.U2.b0 = 16;
  p = mem_max - 3;
  ctx->mem[p - mem_min].hh.rh = -1073741824;
  q = mlist;
  r_type = 0;
  ctx->cur_style = style;
  if (ctx->cur_style < 4)
    ctx->cur_size = 0;
  else
    ctx->cur_size = ((ctx->cur_style - 2) / 2) * 16;
  ctx->cur_mu = x_over_n(
      ctx,
      ctx->font_info[ctx->fnt_infos
                         .param_base[ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                     6]
          .int_,
      18);
  while (q != (-1073741824)) {
    t = 16;
    s = 4;
    pen = 10000;
    switch (ctx->mem[q - mem_min].hh.U2.b0) {
    case 17:
    case 20:
    case 21:
    case 22:
    case 23:
      t = ctx->mem[q - mem_min].hh.U2.b0;
      break;
    case 18:
      t = 18;
      pen = ctx->eqtb[12172].int_;
      break;
    case 19:
      t = 19;
      pen = ctx->eqtb[12173].int_;
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
      t = make_left_right(ctx, q, style, max_d, max_h);
      break;
    case 14:
      ctx->cur_style = ctx->mem[q - mem_min].hh.U2.b1;
      s = 3;
      if (ctx->cur_style < 4)
        ctx->cur_size = 0;
      else
        ctx->cur_size = ((ctx->cur_style - 2) / 2) * 16;
      ctx->cur_mu =
          x_over_n(ctx,
                   ctx->font_info[ctx->fnt_infos.param_base
                                      [ctx->eqtb[ctx->cur_size + 10837].hh.rh] +
                                  6]
                       .int_,
                   18);
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
      ctx->mem[p - mem_min].hh.rh = q;
      p = q;
      q = ctx->mem[q - mem_min].hh.rh;
      ctx->mem[p - mem_min].hh.rh = -1073741824;
      goto _L30;
      break;
    default:
      confusion(ctx, 890);
      break;
    }
    if (r_type > 0) {
      switch (ctx->str_pool[(r_type * 8) + t + ctx->magic_offset]) {
      case 48:
        x = 0;
        break;
      case 49:
        if (ctx->cur_style < 4)
          x = 15;
        else
          x = 0;
        break;
      case 50:
        x = 15;
        break;
      case 51:
        if (ctx->cur_style < 4)
          x = 16;
        else
          x = 0;
        break;
      case 52:
        if (ctx->cur_style < 4)
          x = 17;
        else
          x = 0;
        break;
      default:
        confusion(ctx, 892);
        break;
      }
      if (x) {
        y = math_glue(ctx, ctx->eqtb[x + 9782].hh.rh, ctx->cur_mu);
        z = new_glue(ctx, y);
        ctx->mem[y - mem_min].hh.rh = -1073741824;
        ctx->mem[p - mem_min].hh.rh = z;
        p = z;
        ctx->mem[z - mem_min].hh.U2.b1 = x + 1;
      }
    }
    if (ctx->mem[q - mem_min + 1].int_ != (-1073741824)) {
      ctx->mem[p - mem_min].hh.rh = ctx->mem[q - mem_min + 1].int_;
      do {
        p = ctx->mem[p - mem_min].hh.rh;
      } while (ctx->mem[p - mem_min].hh.rh != (-1073741824));
    }
    if (penalties) {
      if (ctx->mem[q - mem_min].hh.rh != (-1073741824)) {
        if (pen < 10000) {
          r_type = ctx->mem[ctx->mem[q - mem_min].hh.rh - mem_min].hh.U2.b0;
          if (r_type != 12) {
            if (r_type != 19) {
              z = new_penalty(ctx, pen);
              ctx->mem[p - mem_min].hh.rh = z;
              p = z;
            }
          }
        }
      }
    }
    r_type = t;
  _L83:
    r = q;
    q = ctx->mem[q - mem_min].hh.rh;
    free_node(ctx, r, s);
  _L30:;
  }
}

void push_alignment(ctex_t *ctx) {
  halfword p = get_node(ctx, 5);
  ctx->mem[p - mem_min].hh.rh = ctx->align_ptr;
  ctx->mem[p - mem_min].hh.lh = ctx->cur_align;
  ctx->mem[p - mem_min + 1].hh.lh = ctx->mem[mem_max - mem_min - 8].hh.rh;
  ctx->mem[p - mem_min + 1].hh.rh = ctx->cur_span;
  ctx->mem[p - mem_min + 2].int_ = ctx->cur_loop;
  ctx->mem[p - mem_min + 3].int_ = ctx->align_state;
  ctx->mem[p - mem_min + 4].hh.lh = ctx->cur_head;
  ctx->mem[p - mem_min + 4].hh.rh = ctx->cur_tail;
  ctx->align_ptr = p;
  ctx->cur_head = get_avail(ctx);
}

void pop_alignment(ctex_t *ctx) {
  halfword p;
  ctx->mem[ctx->cur_head - mem_min].hh.rh = ctx->avail;
  ctx->avail = ctx->cur_head;
  p = ctx->align_ptr;
  ctx->cur_tail = ctx->mem[p - mem_min + 4].hh.rh;
  ctx->cur_head = ctx->mem[p - mem_min + 4].hh.lh;
  ctx->align_state = ctx->mem[p - mem_min + 3].int_;
  ctx->cur_loop = ctx->mem[p - mem_min + 2].int_;
  ctx->cur_span = ctx->mem[p - mem_min + 1].hh.rh;
  ctx->mem[mem_max - mem_min - 8].hh.rh = ctx->mem[p - mem_min + 1].hh.lh;
  ctx->cur_align = ctx->mem[p - mem_min].hh.lh;
  ctx->align_ptr = ctx->mem[p - mem_min].hh.rh;
  free_node(ctx, p, 5);
}

void get_preamble_token(ctex_t *ctx) {
_L20:
  get_token(ctx);
  while ((ctx->cur_chr == 256) && (ctx->cur_cmd == 4)) {
    get_token(ctx);
    if (ctx->cur_cmd > 100) {
      expand(ctx);
      get_token(ctx);
    }
  }
  if (ctx->cur_cmd == 9)
    fatal_error(ctx, 595);
  if ((ctx->cur_cmd != 75) || (ctx->cur_chr != 9793))
    return;
  scan_optional_equals(ctx);
  scan_glue(ctx, 2);
  if (ctx->eqtb[12206].int_ > 0)
    geq_define(ctx, 9793, 117, ctx->cur_val);
  else
    eq_define(ctx, 9793, 117, ctx->cur_val);
  goto _L20;
}

void init_align(ctex_t *ctx) {
  halfword p;
  halfword save_cs_ptr = ctx->cur_cs;
  push_alignment(ctx);
  ctx->align_state = -1000000;
  if ((ctx->cur_list.mode_field == 203) &&
      ((ctx->cur_list.tail_field != ctx->cur_list.head_field) ||
       (ctx->cur_list.aux_field.int_ != (-1073741824)))) {
    print_nl(ctx, 262);
    print(ctx, 680);
    print_esc(ctx, 520);
    print(ctx, 893);
    ctx->help_ptr = 3;
    ctx->help_line[2] = 894;
    ctx->help_line[1] = 895;
    ctx->help_line[0] = 896;
    error(ctx);
    flush_math(ctx);
  }
  push_nest(ctx);
  if (ctx->cur_list.mode_field == 203) {
    ctx->cur_list.mode_field = -1;
    ctx->cur_list.aux_field.int_ = ctx->nest[ctx->nest_ptr - 2].aux_field.int_;
  } else if (ctx->cur_list.mode_field > 0)
    ctx->cur_list.mode_field = -ctx->cur_list.mode_field;
  scan_spec(ctx, 6, false);
  ctx->mem[mem_max - mem_min - 8].hh.rh = -1073741824;
  ctx->cur_align = mem_max - 8;
  ctx->cur_loop = -1073741824;
  ctx->scanner_status = 4;
  ctx->warning_index = save_cs_ptr;
  ctx->align_state = -1000000;
  while (true) {
    ctx->mem[ctx->cur_align - mem_min].hh.rh = new_param_glue(ctx, 11);
    ctx->cur_align = ctx->mem[ctx->cur_align - mem_min].hh.rh;
    if (ctx->cur_cmd == 5)
      goto _L30;
    p = mem_max - 4;
    ctx->mem[p - mem_min].hh.rh = -1073741824;
    while (true) {
      get_preamble_token(ctx);
      if (ctx->cur_cmd == 6)
        goto _L31;
      if ((ctx->cur_cmd <= 5) && (ctx->cur_cmd >= 4) &&
          (ctx->align_state == (-1000000))) {
        if ((p == (mem_max - 4)) && (ctx->cur_loop == (-1073741824)) &&
            (ctx->cur_cmd == 4)) {
          ctx->cur_loop = ctx->cur_align;
          continue;
        } else {
          print_nl(ctx, 262);
          print(ctx, 902);
          ctx->help_ptr = 3;
          ctx->help_line[2] = 903;
          ctx->help_line[1] = 904;
          ctx->help_line[0] = 905;
          back_error(ctx);
          goto _L31;
        }
      } else {
        if ((ctx->cur_cmd != 10) || (p != (mem_max - 4))) {
          ctx->mem[p - mem_min].hh.rh = get_avail(ctx);
          p = ctx->mem[p - mem_min].hh.rh;
          ctx->mem[p - mem_min].hh.lh = ctx->cur_tok;
        }
        continue;
      }
    }
  _L31:
    ctx->mem[ctx->cur_align - mem_min].hh.rh = new_null_box(ctx);
    ctx->cur_align = ctx->mem[ctx->cur_align - mem_min].hh.rh;
    ctx->mem[ctx->cur_align - mem_min].hh.lh = mem_max - 9;
    ctx->mem[ctx->cur_align - mem_min + 1].int_ = -1073741824;
    ctx->mem[ctx->cur_align - mem_min + 3].int_ =
        ctx->mem[mem_max - mem_min - 4].hh.rh;
    p = mem_max - 4;
    ctx->mem[p - mem_min].hh.rh = -1073741824;
    while (true) {
    _L22:
      get_preamble_token(ctx);
      if ((ctx->cur_cmd <= 5) && (ctx->cur_cmd >= 4) &&
          (ctx->align_state == (-1000000)))
        goto _L32;
      if (ctx->cur_cmd == 6) {
        print_nl(ctx, 262);
        print(ctx, 906);
        ctx->help_ptr = 3;
        ctx->help_line[2] = 903;
        ctx->help_line[1] = 904;
        ctx->help_line[0] = 907;
        error(ctx);
        goto _L22;
      }
      ctx->mem[p - mem_min].hh.rh = get_avail(ctx);
      p = ctx->mem[p - mem_min].hh.rh;
      ctx->mem[p - mem_min].hh.lh = ctx->cur_tok;
    }
  _L32:
    ctx->mem[p - mem_min].hh.rh = get_avail(ctx);
    p = ctx->mem[p - mem_min].hh.rh;
    ctx->mem[p - mem_min].hh.lh = 13614;
    ctx->mem[ctx->cur_align - mem_min + 2].int_ =
        ctx->mem[mem_max - mem_min - 4].hh.rh;
  }
_L30:
  ctx->scanner_status = 0;
  new_save_level(ctx, 6);
  if (ctx->eqtb[10320].hh.rh != (-1073741824))
    begin_token_list(ctx, ctx->eqtb[10320].hh.rh, 13);
  align_peek(ctx);
}

void init_span(ctex_t *ctx, halfword p) {
  push_nest(ctx);
  if (ctx->cur_list.mode_field == (-102)) {
    ctx->cur_list.aux_field.hh.lh = 1000;
  } else {
    ctx->cur_list.aux_field.int_ = -65536000;
    normal_paragraph(ctx);
  }
  ctx->cur_span = p;
}

void init_row(ctex_t *ctx) {
  push_nest(ctx);
  ctx->cur_list.mode_field = (-ctx->cur_list.mode_field) - 103;
  if (ctx->cur_list.mode_field == (-102))
    ctx->cur_list.aux_field.hh.lh = 0;
  else
    ctx->cur_list.aux_field.int_ = 0;
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_glue(
      ctx, ctx->mem[ctx->mem[mem_max - mem_min - 8].hh.rh - mem_min + 1].hh.lh);
  ctx->cur_list.tail_field = ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 = 12;
  ctx->cur_align =
      ctx->mem[ctx->mem[mem_max - mem_min - 8].hh.rh - mem_min].hh.rh;
  ctx->cur_tail = ctx->cur_head;
  init_span(ctx, ctx->cur_align);
}

void init_col(ctex_t *ctx) {
  ctx->mem[ctx->cur_align - mem_min + 5].hh.lh = ctx->cur_cmd;
  if (ctx->cur_cmd == 63) {
    ctx->align_state = 0;
  } else {
    back_input(ctx);
    begin_token_list(ctx, ctx->mem[ctx->cur_align - mem_min + 3].int_, 1);
  }
}

bool_t fin_col(ctex_t *ctx) {
  bool_t result;
  halfword p, q, r, s, u;
  scaled w;
  glue_ord o;
  halfword n;
  if (ctx->cur_align == (-1073741824))
    confusion(ctx, 908);
  q = ctx->mem[ctx->cur_align - mem_min].hh.rh;
  if (q == (-1073741824))
    confusion(ctx, 908);
  if (ctx->align_state < 500000)
    fatal_error(ctx, 595);
  p = ctx->mem[q - mem_min].hh.rh;
  if ((p == (-1073741824)) &&
      (ctx->mem[ctx->cur_align - mem_min + 5].hh.lh < 257)) {
    if (ctx->cur_loop != (-1073741824)) {
      ctx->mem[q - mem_min].hh.rh = new_null_box(ctx);
      p = ctx->mem[q - mem_min].hh.rh;
      ctx->mem[p - mem_min].hh.lh = mem_max - 9;
      ctx->mem[p - mem_min + 1].int_ = -1073741824;
      ctx->cur_loop = ctx->mem[ctx->cur_loop - mem_min].hh.rh;
      q = mem_max - 4;
      r = ctx->mem[ctx->cur_loop - mem_min + 3].int_;
      while (r != (-1073741824)) {
        ctx->mem[q - mem_min].hh.rh = get_avail(ctx);
        q = ctx->mem[q - mem_min].hh.rh;
        ctx->mem[q - mem_min].hh.lh = ctx->mem[r - mem_min].hh.lh;
        r = ctx->mem[r - mem_min].hh.rh;
      }
      ctx->mem[q - mem_min].hh.rh = -1073741824;
      ctx->mem[p - mem_min + 3].int_ = ctx->mem[mem_max - mem_min - 4].hh.rh;
      q = mem_max - 4;
      r = ctx->mem[ctx->cur_loop - mem_min + 2].int_;
      while (r != (-1073741824)) {
        ctx->mem[q - mem_min].hh.rh = get_avail(ctx);
        q = ctx->mem[q - mem_min].hh.rh;
        ctx->mem[q - mem_min].hh.lh = ctx->mem[r - mem_min].hh.lh;
        r = ctx->mem[r - mem_min].hh.rh;
      }
      ctx->mem[q - mem_min].hh.rh = -1073741824;
      ctx->mem[p - mem_min + 2].int_ = ctx->mem[mem_max - mem_min - 4].hh.rh;
      ctx->cur_loop = ctx->mem[ctx->cur_loop - mem_min].hh.rh;
      ctx->mem[p - mem_min].hh.rh =
          new_glue(ctx, ctx->mem[ctx->cur_loop - mem_min + 1].hh.lh);
    } else {
      print_nl(ctx, 262);
      print(ctx, 909);
      print_esc(ctx, 898);
      ctx->help_ptr = 3;
      ctx->help_line[2] = 910;
      ctx->help_line[1] = 911;
      ctx->help_line[0] = 912;
      ctx->mem[ctx->cur_align - mem_min + 5].hh.lh = 257;
      error(ctx);
    }
  }
  if (ctx->mem[ctx->cur_align - mem_min + 5].hh.lh != 256) {
    unsave(ctx);
    new_save_level(ctx, 6);
    if (ctx->cur_list.mode_field == (-102)) {
      ctx->adjust_tail = ctx->cur_tail;
      u = hpack(ctx, ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh, 0, 1);
      w = ctx->mem[u - mem_min + 1].int_;
      ctx->cur_tail = ctx->adjust_tail;
      ctx->adjust_tail = -1073741824;
    } else {
      u = vpackage(ctx, ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh, 0,
                   1, 0);
      w = ctx->mem[u - mem_min + 3].int_;
    }
    n = 0;
    if (ctx->cur_span != ctx->cur_align) {
      q = ctx->cur_span;
      do {
        ++n;
        q = ctx->mem[ctx->mem[q - mem_min].hh.rh - mem_min].hh.rh;
      } while (q != ctx->cur_align);
      if (n > 65535)
        confusion(ctx, 913);
      q = ctx->cur_span;
      while (ctx->mem[ctx->mem[q - mem_min].hh.lh - mem_min].hh.rh < n)
        q = ctx->mem[q - mem_min].hh.lh;
      if (ctx->mem[ctx->mem[q - mem_min].hh.lh - mem_min].hh.rh > n) {
        s = get_node(ctx, 2);
        ctx->mem[s - mem_min].hh.lh = ctx->mem[q - mem_min].hh.lh;
        ctx->mem[s - mem_min].hh.rh = n;
        ctx->mem[q - mem_min].hh.lh = s;
        ctx->mem[s - mem_min + 1].int_ = w;
      } else if (ctx->mem[ctx->mem[q - mem_min].hh.lh - mem_min + 1].int_ < w)
        ctx->mem[ctx->mem[q - mem_min].hh.lh - mem_min + 1].int_ = w;
    } else if (w > ctx->mem[ctx->cur_align - mem_min + 1].int_)
      ctx->mem[ctx->cur_align - mem_min + 1].int_ = w;
    ctx->mem[u - mem_min].hh.U2.b0 = 13;
    ctx->mem[u - mem_min].hh.U2.b1 = n;
    if (ctx->total_stretch[3]) {
      o = 3;
    } else if (ctx->total_stretch[2]) {
      o = 2;
    } else if (ctx->total_stretch[1])
      o = 1;
    else
      o = 0;
    ctx->mem[u - mem_min + 5].hh.U2.b1 = o;
    ctx->mem[u - mem_min + 6].int_ = ctx->total_stretch[o];
    if (ctx->total_shrink[3]) {
      o = 3;
    } else if (ctx->total_shrink[2]) {
      o = 2;
    } else if (ctx->total_shrink[1])
      o = 1;
    else
      o = 0;
    ctx->mem[u - mem_min + 5].hh.U2.b0 = o;
    ctx->mem[u - mem_min + 4].int_ = ctx->total_shrink[o];
    pop_nest(ctx);
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = u;
    ctx->cur_list.tail_field = u;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_glue(
        ctx,
        ctx->mem[ctx->mem[ctx->cur_align - mem_min].hh.rh - mem_min + 1].hh.lh);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 = 12;
    if (ctx->mem[ctx->cur_align - mem_min + 5].hh.lh >= 257) {
      result = true;
      goto _L10;
    }
    init_span(ctx, p);
  }
  ctx->align_state = 1000000;
  do {
    get_x_token(ctx);
  } while (ctx->cur_cmd == 10);
  ctx->cur_align = p;
  init_col(ctx);
  result = false;
_L10:
  return result;
}

void fin_row(ctex_t *ctx) {
  halfword p;
  if (ctx->cur_list.mode_field == (-102)) {
    p = hpack(ctx, ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh, 0, 1);
    pop_nest(ctx);
    append_to_vlist(ctx, p);
    if (ctx->cur_head != ctx->cur_tail) {
      ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
          ctx->mem[ctx->cur_head - mem_min].hh.rh;
      ctx->cur_list.tail_field = ctx->cur_tail;
    }
  } else {
    p = vpackage(ctx, ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh, 0, 1,
                 1073741823);
    pop_nest(ctx);
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = p;
    ctx->cur_list.tail_field = p;
    ctx->cur_list.aux_field.hh.lh = 1000;
  }
  ctx->mem[p - mem_min].hh.U2.b0 = 13;
  ctx->mem[p - mem_min + 6].int_ = 0;
  if (ctx->eqtb[10320].hh.rh != (-1073741824))
    begin_token_list(ctx, ctx->eqtb[10320].hh.rh, 13);
  align_peek(ctx);
}

void fin_align(ctex_t *ctx) {
  halfword p, q, r, s, u, v, n;
  scaled t, w, o, rule_save;
  memory_word aux_save;
  if (ctx->cur_group != 6)
    confusion(ctx, 914);
  unsave(ctx);
  if (ctx->cur_group != 6)
    confusion(ctx, 915);
  unsave(ctx);
  if (ctx->nest[ctx->nest_ptr - 1].mode_field == 203)
    o = ctx->eqtb[12745].int_;
  else
    o = 0;
  q = ctx->mem[ctx->mem[mem_max - mem_min - 8].hh.rh - mem_min].hh.rh;
  do {
    flush_list(ctx, ctx->mem[q - mem_min + 3].int_);
    flush_list(ctx, ctx->mem[q - mem_min + 2].int_);
    p = ctx->mem[ctx->mem[q - mem_min].hh.rh - mem_min].hh.rh;
    if (ctx->mem[q - mem_min + 1].int_ == (-1073741824)) {
      ctx->mem[q - mem_min + 1].int_ = 0;
      r = ctx->mem[q - mem_min].hh.rh;
      s = ctx->mem[r - mem_min + 1].hh.lh;
      if (s) {
        ++ctx->mem[-mem_min].hh.rh;
        delete_glue_ref(ctx, s);
        ctx->mem[r - mem_min + 1].hh.lh = 0;
      }
    }
    if (ctx->mem[q - mem_min].hh.lh != (mem_max - 9)) {
      t = ctx->mem[q - mem_min + 1].int_ +
          ctx->mem[ctx->mem[ctx->mem[q - mem_min].hh.rh - mem_min + 1].hh.lh -
                   mem_min + 1]
              .int_;
      r = ctx->mem[q - mem_min].hh.lh;
      s = mem_max - 9;
      ctx->mem[s - mem_min].hh.lh = p;
      n = 1;
      do {
        ctx->mem[r - mem_min + 1].int_ -= t;
        u = ctx->mem[r - mem_min].hh.lh;
        while (ctx->mem[r - mem_min].hh.rh > n) {
          s = ctx->mem[s - mem_min].hh.lh;
          n = ctx->mem[ctx->mem[s - mem_min].hh.lh - mem_min].hh.rh + 1;
        }
        if (ctx->mem[r - mem_min].hh.rh < n) {
          ctx->mem[r - mem_min].hh.lh = ctx->mem[s - mem_min].hh.lh;
          ctx->mem[s - mem_min].hh.lh = r;
          --ctx->mem[r - mem_min].hh.rh;
          s = r;
        } else {
          if (ctx->mem[r - mem_min + 1].int_ >
              ctx->mem[ctx->mem[s - mem_min].hh.lh - mem_min + 1].int_)
            ctx->mem[ctx->mem[s - mem_min].hh.lh - mem_min + 1].int_ =
                ctx->mem[r - mem_min + 1].int_;
          free_node(ctx, r, 2);
        }
        r = u;
      } while (r != (mem_max - 9));
    }
    ctx->mem[q - mem_min].hh.U2.b0 = 13;
    ctx->mem[q - mem_min].hh.U2.b1 = 0;
    ctx->mem[q - mem_min + 3].int_ = 0;
    ctx->mem[q - mem_min + 2].int_ = 0;
    ctx->mem[q - mem_min + 5].hh.U2.b1 = 0;
    ctx->mem[q - mem_min + 5].hh.U2.b0 = 0;
    ctx->mem[q - mem_min + 6].int_ = 0;
    ctx->mem[q - mem_min + 4].int_ = 0;
    q = p;
  } while (q != (-1073741824));
  ctx->save_ptr -= 2;
  ctx->pack_begin_line = -ctx->cur_list.ml_field;
  if (ctx->cur_list.mode_field == (-1)) {
    rule_save = ctx->eqtb[12746].int_;
    ctx->eqtb[12746].int_ = 0;
    p = hpack(ctx, ctx->mem[mem_max - mem_min - 8].hh.rh,
              ctx->save_stack[ctx->save_ptr + 1].int_,
              ctx->save_stack[ctx->save_ptr].int_);
    ctx->eqtb[12746].int_ = rule_save;
  } else {
    q = ctx->mem[ctx->mem[mem_max - mem_min - 8].hh.rh - mem_min].hh.rh;
    do {
      ctx->mem[q - mem_min + 3].int_ = ctx->mem[q - mem_min + 1].int_;
      ctx->mem[q - mem_min + 1].int_ = 0;
      q = ctx->mem[ctx->mem[q - mem_min].hh.rh - mem_min].hh.rh;
    } while (q != (-1073741824));
    p = vpackage(ctx, ctx->mem[mem_max - mem_min - 8].hh.rh,
                 ctx->save_stack[ctx->save_ptr + 1].int_,
                 ctx->save_stack[ctx->save_ptr].int_, 1073741823);
    q = ctx->mem[ctx->mem[mem_max - mem_min - 8].hh.rh - mem_min].hh.rh;
    do {
      ctx->mem[q - mem_min + 1].int_ = ctx->mem[q - mem_min + 3].int_;
      ctx->mem[q - mem_min + 3].int_ = 0;
      q = ctx->mem[ctx->mem[q - mem_min].hh.rh - mem_min].hh.rh;
    } while (q != (-1073741824));
  }
  ctx->pack_begin_line = 0;
  q = ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh;
  s = ctx->cur_list.head_field;
  while (q != (-1073741824)) {
    if (q < ctx->hi_mem_min) {
      if (ctx->mem[q - mem_min].hh.U2.b0 == 13) {
        if (ctx->cur_list.mode_field == (-1)) {
          ctx->mem[q - mem_min].hh.U2.b0 = 0;
          ctx->mem[q - mem_min + 1].int_ = ctx->mem[p - mem_min + 1].int_;
        } else {
          ctx->mem[q - mem_min].hh.U2.b0 = 1;
          ctx->mem[q - mem_min + 3].int_ = ctx->mem[p - mem_min + 3].int_;
        }
        ctx->mem[q - mem_min + 5].hh.U2.b1 = ctx->mem[p - mem_min + 5].hh.U2.b1;
        ctx->mem[q - mem_min + 5].hh.U2.b0 = ctx->mem[p - mem_min + 5].hh.U2.b0;
        ctx->mem[q - mem_min + 6].gr = ctx->mem[p - mem_min + 6].gr;
        ctx->mem[q - mem_min + 4].int_ = o;
        r = ctx->mem[ctx->mem[q - mem_min + 5].hh.rh - mem_min].hh.rh;
        s = ctx->mem[ctx->mem[p - mem_min + 5].hh.rh - mem_min].hh.rh;
        do {
          n = ctx->mem[r - mem_min].hh.U2.b1;
          t = ctx->mem[s - mem_min + 1].int_;
          w = t;
          u = mem_max - 4;
          while (n > 0) {
            --n;
            s = ctx->mem[s - mem_min].hh.rh;
            v = ctx->mem[s - mem_min + 1].hh.lh;
            ctx->mem[u - mem_min].hh.rh = new_glue(ctx, v);
            u = ctx->mem[u - mem_min].hh.rh;
            ctx->mem[u - mem_min].hh.U2.b1 = 12;
            t += ctx->mem[v - mem_min + 1].int_;
            if (ctx->mem[p - mem_min + 5].hh.U2.b0 == 1) {
              if (ctx->mem[v - mem_min].hh.U2.b0 ==
                  ctx->mem[p - mem_min + 5].hh.U2.b1)
                t += round(ctx->mem[p - mem_min + 6].gr *
                           ctx->mem[v - mem_min + 2].int_);
            } else if (ctx->mem[p - mem_min + 5].hh.U2.b0 == 2) {
              if (ctx->mem[v - mem_min].hh.U2.b1 ==
                  ctx->mem[p - mem_min + 5].hh.U2.b1)
                t -= round(ctx->mem[p - mem_min + 6].gr *
                           ctx->mem[v - mem_min + 3].int_);
            }
            s = ctx->mem[s - mem_min].hh.rh;
            ctx->mem[u - mem_min].hh.rh = new_null_box(ctx);
            u = ctx->mem[u - mem_min].hh.rh;
            t += ctx->mem[s - mem_min + 1].int_;
            if (ctx->cur_list.mode_field == (-1)) {
              ctx->mem[u - mem_min + 1].int_ = ctx->mem[s - mem_min + 1].int_;
            } else {
              ctx->mem[u - mem_min].hh.U2.b0 = 1;
              ctx->mem[u - mem_min + 3].int_ = ctx->mem[s - mem_min + 1].int_;
            }
          }
          if (ctx->cur_list.mode_field == (-1)) {
            ctx->mem[r - mem_min + 3].int_ = ctx->mem[q - mem_min + 3].int_;
            ctx->mem[r - mem_min + 2].int_ = ctx->mem[q - mem_min + 2].int_;
            if (t == ctx->mem[r - mem_min + 1].int_) {
              ctx->mem[r - mem_min + 5].hh.U2.b0 = 0;
              ctx->mem[r - mem_min + 5].hh.U2.b1 = 0;
              ctx->mem[r - mem_min + 6].gr = 0.0;
            } else if (t > ctx->mem[r - mem_min + 1].int_) {
              ctx->mem[r - mem_min + 5].hh.U2.b0 = 1;
              if (!ctx->mem[r - mem_min + 6].int_)
                ctx->mem[r - mem_min + 6].gr = 0.0;
              else
                ctx->mem[r - mem_min + 6].gr =
                    ((double)(t - ctx->mem[r - mem_min + 1].int_)) /
                    ctx->mem[r - mem_min + 6].int_;
            } else {
              ctx->mem[r - mem_min + 5].hh.U2.b1 =
                  ctx->mem[r - mem_min + 5].hh.U2.b0;
              ctx->mem[r - mem_min + 5].hh.U2.b0 = 2;
              if (!ctx->mem[r - mem_min + 4].int_) {
                ctx->mem[r - mem_min + 6].gr = 0.0;
              } else if ((!ctx->mem[r - mem_min + 5].hh.U2.b1) &&
                         (ctx->mem[r - mem_min + 1].int_ - t >
                          ctx->mem[r - mem_min + 4].int_))
                ctx->mem[r - mem_min + 6].gr = 1.0;
              else
                ctx->mem[r - mem_min + 6].gr =
                    ((double)(ctx->mem[r - mem_min + 1].int_ - t)) /
                    ctx->mem[r - mem_min + 4].int_;
            }
            ctx->mem[r - mem_min + 1].int_ = w;
            ctx->mem[r - mem_min].hh.U2.b0 = 0;
          } else {
            ctx->mem[r - mem_min + 1].int_ = ctx->mem[q - mem_min + 1].int_;
            if (t == ctx->mem[r - mem_min + 3].int_) {
              ctx->mem[r - mem_min + 5].hh.U2.b0 = 0;
              ctx->mem[r - mem_min + 5].hh.U2.b1 = 0;
              ctx->mem[r - mem_min + 6].gr = 0.0;
            } else if (t > ctx->mem[r - mem_min + 3].int_) {
              ctx->mem[r - mem_min + 5].hh.U2.b0 = 1;
              if (!ctx->mem[r - mem_min + 6].int_)
                ctx->mem[r - mem_min + 6].gr = 0.0;
              else
                ctx->mem[r - mem_min + 6].gr =
                    ((double)(t - ctx->mem[r - mem_min + 3].int_)) /
                    ctx->mem[r - mem_min + 6].int_;
            } else {
              ctx->mem[r - mem_min + 5].hh.U2.b1 =
                  ctx->mem[r - mem_min + 5].hh.U2.b0;
              ctx->mem[r - mem_min + 5].hh.U2.b0 = 2;
              if (!ctx->mem[r - mem_min + 4].int_) {
                ctx->mem[r - mem_min + 6].gr = 0.0;
              } else if ((!ctx->mem[r - mem_min + 5].hh.U2.b1) &&
                         (ctx->mem[r - mem_min + 3].int_ - t >
                          ctx->mem[r - mem_min + 4].int_))
                ctx->mem[r - mem_min + 6].gr = 1.0;
              else
                ctx->mem[r - mem_min + 6].gr =
                    ((double)(ctx->mem[r - mem_min + 3].int_ - t)) /
                    ctx->mem[r - mem_min + 4].int_;
            }
            ctx->mem[r - mem_min + 3].int_ = w;
            ctx->mem[r - mem_min].hh.U2.b0 = 1;
          }
          ctx->mem[r - mem_min + 4].int_ = 0;
          if (u != (mem_max - 4)) {
            ctx->mem[u - mem_min].hh.rh = ctx->mem[r - mem_min].hh.rh;
            ctx->mem[r - mem_min].hh.rh = ctx->mem[mem_max - mem_min - 4].hh.rh;
            r = u;
          }
          r = ctx->mem[ctx->mem[r - mem_min].hh.rh - mem_min].hh.rh;
          s = ctx->mem[ctx->mem[s - mem_min].hh.rh - mem_min].hh.rh;
        } while (r != (-1073741824));
      } else if (ctx->mem[q - mem_min].hh.U2.b0 == 2) {
        if (ctx->mem[q - mem_min + 1].int_ == (-1073741824))
          ctx->mem[q - mem_min + 1].int_ = ctx->mem[p - mem_min + 1].int_;
        if (ctx->mem[q - mem_min + 3].int_ == (-1073741824))
          ctx->mem[q - mem_min + 3].int_ = ctx->mem[p - mem_min + 3].int_;
        if (ctx->mem[q - mem_min + 2].int_ == (-1073741824))
          ctx->mem[q - mem_min + 2].int_ = ctx->mem[p - mem_min + 2].int_;
        if (o) {
          r = ctx->mem[q - mem_min].hh.rh;
          ctx->mem[q - mem_min].hh.rh = -1073741824;
          q = hpack(ctx, q, 0, 1);
          ctx->mem[q - mem_min + 4].int_ = o;
          ctx->mem[q - mem_min].hh.rh = r;
          ctx->mem[s - mem_min].hh.rh = q;
        }
      }
    }
    s = q;
    q = ctx->mem[q - mem_min].hh.rh;
  }
  flush_node_list(ctx, p);
  pop_alignment(ctx);
  aux_save = ctx->cur_list.aux_field;
  p = ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh;
  q = ctx->cur_list.tail_field;
  pop_nest(ctx);
  if (ctx->cur_list.mode_field == 203) {
    do_assignments(ctx);
    if (ctx->cur_cmd != 3) {
      print_nl(ctx, 262);
      print(ctx, 1169);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 894;
      ctx->help_line[0] = 895;
      back_error(ctx);
    } else {
      get_x_token(ctx);
      if (ctx->cur_cmd != 3) {
        print_nl(ctx, 262);
        print(ctx, 1165);
        ctx->help_ptr = 2;
        ctx->help_line[1] = 1166;
        ctx->help_line[0] = 1167;
        back_error(ctx);
      }
    }
    pop_nest(ctx);
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        new_penalty(ctx, ctx->eqtb[12174].int_);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_param_glue(ctx, 3);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = p;
    if (p != (-1073741824))
      ctx->cur_list.tail_field = q;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        new_penalty(ctx, ctx->eqtb[12175].int_);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_param_glue(ctx, 4);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->cur_list.aux_field.int_ = aux_save.int_;
    resume_after_display(ctx);
    return;
  }
  ctx->cur_list.aux_field = aux_save;
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = p;
  if (p != (-1073741824))
    ctx->cur_list.tail_field = q;
  if (ctx->cur_list.mode_field == 1)
    build_page(ctx);
}

void align_peek(ctex_t *ctx) {
_L20:
  ctx->align_state = 1000000;
  do {
    get_x_token(ctx);
  } while (ctx->cur_cmd == 10);
  if (ctx->cur_cmd == 34) {
    scan_left_brace(ctx);
    new_save_level(ctx, 7);
    if (ctx->cur_list.mode_field == (-1))
      normal_paragraph(ctx);
    return;
  }
  if (ctx->cur_cmd == 2) {
    fin_align(ctx);
    return;
  }
  if ((ctx->cur_cmd == 5) && (ctx->cur_chr == 258))
    goto _L20;
  init_row(ctx);
  init_col(ctx);
}

halfword finite_shrink(ctex_t *ctx, halfword p) {
  halfword q;
  if (ctx->no_shrink_error_yet) {
    ctx->no_shrink_error_yet = false;
    print_nl(ctx, 262);
    print(ctx, 916);
    ctx->help_ptr = 5;
    ctx->help_line[4] = 917;
    ctx->help_line[3] = 918;
    ctx->help_line[2] = 919;
    ctx->help_line[1] = 920;
    ctx->help_line[0] = 921;
    error(ctx);
  }
  q = new_spec(ctx, p);
  ctx->mem[q - mem_min].hh.U2.b1 = 0;
  delete_glue_ref(ctx, p);
  return q;
}

void try_break(ctex_t *ctx, integer pi, small_number break_type) {
  halfword r, prev_r = mem_max - 7, old_l = 0;
  bool_t no_break_yet = true;
  halfword prev_prev_r, s, q, v;
  integer t, d;
  internal_font_number f;
  halfword l;
  bool_t node_r_stays_active;
  scaled line_width, shortfall;
  char fit_class;
  halfword b;
  bool_t artificial_demerits;
  if (abs(pi) >= 10000) {
    if (pi > 0)
      goto _L10;
    pi = -10000;
  }
  ctx->cur_active_width[1] = ctx->active_width[1];
  ctx->cur_active_width[2] = ctx->active_width[2];
  ctx->cur_active_width[3] = ctx->active_width[3];
  ctx->cur_active_width[4] = ctx->active_width[4];
  ctx->cur_active_width[5] = ctx->active_width[5];
  ctx->cur_active_width[6] = ctx->active_width[6];
  while (true) {
  _L22:
    r = ctx->mem[prev_r - mem_min].hh.rh;
    if (ctx->mem[r - mem_min].hh.U2.b0 == 2) {
      ctx->cur_active_width[1] += ctx->mem[r - mem_min + 1].int_;
      ctx->cur_active_width[2] += ctx->mem[r - mem_min + 2].int_;
      ctx->cur_active_width[3] += ctx->mem[r - mem_min + 3].int_;
      ctx->cur_active_width[4] += ctx->mem[r - mem_min + 4].int_;
      ctx->cur_active_width[5] += ctx->mem[r - mem_min + 5].int_;
      ctx->cur_active_width[6] += ctx->mem[r - mem_min + 6].int_;
      prev_prev_r = prev_r;
      prev_r = r;
      goto _L22;
    }
    l = ctx->mem[r - mem_min + 1].hh.lh;
    if (l > old_l) {
      if ((ctx->minimum_demerits < 1073741823) &&
          ((old_l != ctx->easy_line) || (r == (mem_max - 7)))) {
        if (no_break_yet) {
          no_break_yet = false;
          ctx->break_width[1] = ctx->background[1];
          ctx->break_width[2] = ctx->background[2];
          ctx->break_width[3] = ctx->background[3];
          ctx->break_width[4] = ctx->background[4];
          ctx->break_width[5] = ctx->background[5];
          ctx->break_width[6] = ctx->background[6];
          s = ctx->cur_p;
          if (break_type > 0) {
            if (ctx->cur_p != (-1073741824)) {
              t = ctx->mem[ctx->cur_p - mem_min].hh.U2.b1;
              v = ctx->cur_p;
              s = ctx->mem[ctx->cur_p - mem_min + 1].hh.rh;
              while (t > 0) {
                --t;
                v = ctx->mem[v - mem_min].hh.rh;
                if (v >= ctx->hi_mem_min) {
                  f = ctx->mem[v - mem_min].hh.U2.b0;
                  (ctx->break_width[1] -=
                   (ctx->font_info
                        [(ctx->fnt_infos.width_base[f] +
                          ((ctx->font_info[(ctx->fnt_infos.char_base[f] +
                                            ((ctx->mem[v - mem_min].hh).U2.b1))]
                                .qqqq)
                               .b0))]
                            .int_));
                  continue;
                }
                switch (ctx->mem[v - mem_min].hh.U2.b0) {
                case 6:
                  f = ctx->mem[v - mem_min + 1].hh.U2.b0;
                  (ctx->break_width[1] -=
                   (ctx
                        ->font_info[(
                            ctx->fnt_infos.width_base[f] +
                            ((ctx->font_info[(ctx->fnt_infos.char_base[f] +
                                              ((ctx->mem[(v - mem_min + 1)].hh)
                                                   .U2.b1))]
                                  .qqqq)
                                 .b0))]
                        .int_));
                  break;
                case 0:
                case 1:
                case 2:
                case 11:
                  ctx->break_width[1] -= ctx->mem[v - mem_min + 1].int_;
                  break;
                default:
                  confusion(ctx, 922);
                  break;
                }
              }
              while (s != (-1073741824)) {
                if (s >= ctx->hi_mem_min) {
                  f = ctx->mem[s - mem_min].hh.U2.b0;
                  (ctx->break_width[1] +=
                   (ctx->font_info
                        [(ctx->fnt_infos.width_base[f] +
                          ((ctx->font_info[(ctx->fnt_infos.char_base[f] +
                                            ((ctx->mem[s - mem_min].hh).U2.b1))]
                                .qqqq)
                               .b0))]
                            .int_));
                } else {
                  switch (ctx->mem[s - mem_min].hh.U2.b0) {
                  case 6:
                    f = ctx->mem[s - mem_min + 1].hh.U2.b0;
                    (ctx->break_width[1] +=
                     (ctx
                          ->font_info[(
                              ctx->fnt_infos.width_base[f] +
                              ((ctx->font_info
                                    [(ctx->fnt_infos.char_base[f] +
                                      ((ctx->mem[(s - mem_min + 1)].hh).U2.b1))]
                                        .qqqq)
                                   .b0))]
                          .int_));
                    break;
                  case 0:
                  case 1:
                  case 2:
                  case 11:
                    ctx->break_width[1] += ctx->mem[s - mem_min + 1].int_;
                    break;
                  default:
                    confusion(ctx, 923);
                    break;
                  }
                }
                s = ctx->mem[s - mem_min].hh.rh;
              }
              ctx->break_width[1] += ctx->disc_width;
              if (ctx->mem[ctx->cur_p - mem_min + 1].hh.rh == (-1073741824))
                s = ctx->mem[v - mem_min].hh.rh;
            }
          }
          while (s != (-1073741824)) {
            if (s >= ctx->hi_mem_min)
              goto _L30;
            switch (ctx->mem[s - mem_min].hh.U2.b0) {
            case 10:
              v = ctx->mem[s - mem_min + 1].hh.lh;
              ctx->break_width[1] -= ctx->mem[v - mem_min + 1].int_;
              ctx->break_width[ctx->mem[v - mem_min].hh.U2.b0 + 2] -=
                  ctx->mem[v - mem_min + 2].int_;
              ctx->break_width[6] -= ctx->mem[v - mem_min + 3].int_;
              break;
            case 12:
              // blank case
              break;
            case 9:
              ctx->break_width[1] -= ctx->mem[s - mem_min + 1].int_;
              break;
            case 11:
              if (ctx->mem[s - mem_min].hh.U2.b1 != 1)
                goto _L30;
              ctx->break_width[1] -= ctx->mem[s - mem_min + 1].int_;
              break;
            default:
              goto _L30;
              break;
            }
            s = ctx->mem[s - mem_min].hh.rh;
          }
        _L30:;
        }
        if (ctx->mem[prev_r - mem_min].hh.U2.b0 == 2) {
          ctx->mem[prev_r - mem_min + 1].int_ +=
              ctx->break_width[1] - ctx->cur_active_width[1];
          ctx->mem[prev_r - mem_min + 2].int_ +=
              ctx->break_width[2] - ctx->cur_active_width[2];
          ctx->mem[prev_r - mem_min + 3].int_ +=
              ctx->break_width[3] - ctx->cur_active_width[3];
          ctx->mem[prev_r - mem_min + 4].int_ +=
              ctx->break_width[4] - ctx->cur_active_width[4];
          ctx->mem[prev_r - mem_min + 5].int_ +=
              ctx->break_width[5] - ctx->cur_active_width[5];
          ctx->mem[prev_r - mem_min + 6].int_ +=
              ctx->break_width[6] - ctx->cur_active_width[6];
        } else if (prev_r == (mem_max - 7)) {
          ctx->active_width[1] = ctx->break_width[1];
          ctx->active_width[2] = ctx->break_width[2];
          ctx->active_width[3] = ctx->break_width[3];
          ctx->active_width[4] = ctx->break_width[4];
          ctx->active_width[5] = ctx->break_width[5];
          ctx->active_width[6] = ctx->break_width[6];
        } else {
          q = get_node(ctx, 7);
          ctx->mem[q - mem_min].hh.rh = r;
          ctx->mem[q - mem_min].hh.U2.b0 = 2;
          ctx->mem[q - mem_min].hh.U2.b1 = 0;
          ctx->mem[q - mem_min + 1].int_ =
              ctx->break_width[1] - ctx->cur_active_width[1];
          ctx->mem[q - mem_min + 2].int_ =
              ctx->break_width[2] - ctx->cur_active_width[2];
          ctx->mem[q - mem_min + 3].int_ =
              ctx->break_width[3] - ctx->cur_active_width[3];
          ctx->mem[q - mem_min + 4].int_ =
              ctx->break_width[4] - ctx->cur_active_width[4];
          ctx->mem[q - mem_min + 5].int_ =
              ctx->break_width[5] - ctx->cur_active_width[5];
          ctx->mem[q - mem_min + 6].int_ =
              ctx->break_width[6] - ctx->cur_active_width[6];
          ctx->mem[prev_r - mem_min].hh.rh = q;
          prev_prev_r = prev_r;
          prev_r = q;
        }
        if (abs(ctx->eqtb[12179].int_) >= (1073741823 - ctx->minimum_demerits))
          ctx->minimum_demerits = 1073741822;
        else
          ctx->minimum_demerits += abs(ctx->eqtb[12179].int_);
        for (fit_class = 0; fit_class <= 3; ++fit_class) {
          if (ctx->minimal_demerits[fit_class] <= ctx->minimum_demerits) {
            q = get_node(ctx, 2);
            ctx->mem[q - mem_min].hh.rh = ctx->passive;
            ctx->passive = q;
            ctx->mem[q - mem_min + 1].hh.rh = ctx->cur_p;
            ctx->mem[q - mem_min + 1].hh.lh = ctx->best_place[fit_class];
            q = get_node(ctx, 3);
            ctx->mem[q - mem_min + 1].hh.rh = ctx->passive;
            ctx->mem[q - mem_min + 1].hh.lh = ctx->best_pl_line[fit_class] + 1;
            ctx->mem[q - mem_min].hh.U2.b1 = fit_class;
            ctx->mem[q - mem_min].hh.U2.b0 = break_type;
            ctx->mem[q - mem_min + 2].int_ = ctx->minimal_demerits[fit_class];
            ctx->mem[q - mem_min].hh.rh = r;
            ctx->mem[prev_r - mem_min].hh.rh = q;
            prev_r = q;
          }
          ctx->minimal_demerits[fit_class] = 1073741823;
        }
        ctx->minimum_demerits = 1073741823;
        if (r != (mem_max - 7)) {
          q = get_node(ctx, 7);
          ctx->mem[q - mem_min].hh.rh = r;
          ctx->mem[q - mem_min].hh.U2.b0 = 2;
          ctx->mem[q - mem_min].hh.U2.b1 = 0;
          ctx->mem[q - mem_min + 1].int_ =
              ctx->cur_active_width[1] - ctx->break_width[1];
          ctx->mem[q - mem_min + 2].int_ =
              ctx->cur_active_width[2] - ctx->break_width[2];
          ctx->mem[q - mem_min + 3].int_ =
              ctx->cur_active_width[3] - ctx->break_width[3];
          ctx->mem[q - mem_min + 4].int_ =
              ctx->cur_active_width[4] - ctx->break_width[4];
          ctx->mem[q - mem_min + 5].int_ =
              ctx->cur_active_width[5] - ctx->break_width[5];
          ctx->mem[q - mem_min + 6].int_ =
              ctx->cur_active_width[6] - ctx->break_width[6];
          ctx->mem[prev_r - mem_min].hh.rh = q;
          prev_prev_r = prev_r;
          prev_r = q;
        }
      }
      if (r == (mem_max - 7))
        goto _L10;
      if (l > ctx->easy_line) {
        line_width = ctx->second_width;
        old_l = 1073741823;
      } else {
        old_l = l;
        if (l > ctx->last_special_line) {
          line_width = ctx->second_width;
        } else if (ctx->eqtb[10312].hh.rh == (-1073741824))
          line_width = ctx->first_width;
        else
          line_width =
              ctx->mem[ctx->eqtb[10312].hh.rh + (l * 2) - mem_min].int_;
      }
    }
    artificial_demerits = false;
    shortfall = line_width - ctx->cur_active_width[1];
    if (shortfall > 0) {
      if (ctx->cur_active_width[3] || ctx->cur_active_width[4] ||
          ctx->cur_active_width[5]) {
        b = 0;
        fit_class = 2;
      } else {
        if (shortfall > 7230584) {
          if (ctx->cur_active_width[2] < 1663497) {
            b = 10000;
            fit_class = 0;
            goto _L31;
          }
        }
        b = badness(ctx, shortfall, ctx->cur_active_width[2]);
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
      if (-shortfall > ctx->cur_active_width[6])
        b = 10001;
      else
        b = badness(ctx, -shortfall, ctx->cur_active_width[6]);
      if (b > 12)
        fit_class = 3;
      else
        fit_class = 2;
    }
    if ((b > 10000) || (pi == (-10000))) {
      if (ctx->final_pass && (ctx->minimum_demerits == 1073741823) &&
          (ctx->mem[r - mem_min].hh.rh == (mem_max - 7)) &&
          (prev_r == (mem_max - 7))) {
        artificial_demerits = true;
      } else if (b > ctx->threshold)
        goto _L60;
      node_r_stays_active = false;
    } else {
      prev_r = r;
      if (b > ctx->threshold)
        goto _L22;
      node_r_stays_active = true;
    }
    if (artificial_demerits) {
      d = 0;
    } else {
      d = ctx->eqtb[12165].int_ + b;
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
      if ((break_type == 1) && (ctx->mem[r - mem_min].hh.U2.b0 == 1)) {
        if (ctx->cur_p != (-1073741824))
          d += ctx->eqtb[12177].int_;
        else
          d += ctx->eqtb[12178].int_;
      }
      if (abs(fit_class - ctx->mem[r - mem_min].hh.U2.b1) > 1)
        d += ctx->eqtb[12179].int_;
    }
    d += ctx->mem[r - mem_min + 2].int_;
    if (d <= ctx->minimal_demerits[fit_class]) {
      ctx->minimal_demerits[fit_class] = d;
      ctx->best_place[fit_class] = ctx->mem[r - mem_min + 1].hh.rh;
      ctx->best_pl_line[fit_class] = l;
      if (d < ctx->minimum_demerits)
        ctx->minimum_demerits = d;
    }
    if (node_r_stays_active)
      goto _L22;
  _L60:
    ctx->mem[prev_r - mem_min].hh.rh = ctx->mem[r - mem_min].hh.rh;
    free_node(ctx, r, 3);
    if (prev_r == (mem_max - 7)) {
      r = ctx->mem[mem_max - mem_min - 7].hh.rh;
      if (ctx->mem[r - mem_min].hh.U2.b0 != 2)
        continue;
      ctx->active_width[1] += ctx->mem[r - mem_min + 1].int_;
      ctx->active_width[2] += ctx->mem[r - mem_min + 2].int_;
      ctx->active_width[3] += ctx->mem[r - mem_min + 3].int_;
      ctx->active_width[4] += ctx->mem[r - mem_min + 4].int_;
      ctx->active_width[5] += ctx->mem[r - mem_min + 5].int_;
      ctx->active_width[6] += ctx->mem[r - mem_min + 6].int_;
      ctx->cur_active_width[1] = ctx->active_width[1];
      ctx->cur_active_width[2] = ctx->active_width[2];
      ctx->cur_active_width[3] = ctx->active_width[3];
      ctx->cur_active_width[4] = ctx->active_width[4];
      ctx->cur_active_width[5] = ctx->active_width[5];
      ctx->cur_active_width[6] = ctx->active_width[6];
      ctx->mem[mem_max - mem_min - 7].hh.rh = ctx->mem[r - mem_min].hh.rh;
      free_node(ctx, r, 7);
      continue;
    }
    if (ctx->mem[prev_r - mem_min].hh.U2.b0 != 2)
      continue;
    r = ctx->mem[prev_r - mem_min].hh.rh;
    if (r == (mem_max - 7)) {
      ctx->cur_active_width[1] -= ctx->mem[prev_r - mem_min + 1].int_;
      ctx->cur_active_width[2] -= ctx->mem[prev_r - mem_min + 2].int_;
      ctx->cur_active_width[3] -= ctx->mem[prev_r - mem_min + 3].int_;
      ctx->cur_active_width[4] -= ctx->mem[prev_r - mem_min + 4].int_;
      ctx->cur_active_width[5] -= ctx->mem[prev_r - mem_min + 5].int_;
      ctx->cur_active_width[6] -= ctx->mem[prev_r - mem_min + 6].int_;
      ctx->mem[prev_prev_r - mem_min].hh.rh = mem_max - 7;
      free_node(ctx, prev_r, 7);
      prev_r = prev_prev_r;
      continue;
    }
    if (ctx->mem[r - mem_min].hh.U2.b0 != 2)
      continue;
    ctx->cur_active_width[1] += ctx->mem[r - mem_min + 1].int_;
    ctx->cur_active_width[2] += ctx->mem[r - mem_min + 2].int_;
    ctx->cur_active_width[3] += ctx->mem[r - mem_min + 3].int_;
    ctx->cur_active_width[4] += ctx->mem[r - mem_min + 4].int_;
    ctx->cur_active_width[5] += ctx->mem[r - mem_min + 5].int_;
    ctx->cur_active_width[6] += ctx->mem[r - mem_min + 6].int_;
    ctx->mem[prev_r - mem_min + 1].int_ += ctx->mem[r - mem_min + 1].int_;
    ctx->mem[prev_r - mem_min + 2].int_ += ctx->mem[r - mem_min + 2].int_;
    ctx->mem[prev_r - mem_min + 3].int_ += ctx->mem[r - mem_min + 3].int_;
    ctx->mem[prev_r - mem_min + 4].int_ += ctx->mem[r - mem_min + 4].int_;
    ctx->mem[prev_r - mem_min + 5].int_ += ctx->mem[r - mem_min + 5].int_;
    ctx->mem[prev_r - mem_min + 6].int_ += ctx->mem[r - mem_min + 6].int_;
    ctx->mem[prev_r - mem_min].hh.rh = ctx->mem[r - mem_min].hh.rh;
    free_node(ctx, r, 7);
  }
_L10:;
}

void post_line_break(ctex_t *ctx, integer final_widow_penalty) {
  halfword r, s;
  bool_t disc_break, post_disc_break;
  scaled cur_width, cur_indent;
  quarterword t;
  integer pen;
  halfword cur_line;
  halfword q = ctx->mem[ctx->best_bet - mem_min + 1].hh.rh;
  ctx->cur_p = -1073741824;
  do {
    r = q;
    q = ctx->mem[q - mem_min + 1].hh.lh;
    ctx->mem[r - mem_min + 1].hh.lh = ctx->cur_p;
    ctx->cur_p = r;
  } while (q != (-1073741824));
  cur_line = ctx->cur_list.pg_field + 1;
  do {
    q = ctx->mem[ctx->cur_p - mem_min + 1].hh.rh;
    disc_break = false;
    post_disc_break = false;
    if (q != (-1073741824)) {
      if (ctx->mem[q - mem_min].hh.U2.b0 == 10) {
        delete_glue_ref(ctx, ctx->mem[q - mem_min + 1].hh.lh);
        ctx->mem[q - mem_min + 1].hh.lh = ctx->eqtb[9790].hh.rh;
        ctx->mem[q - mem_min].hh.U2.b1 = 9;
        ++ctx->mem[ctx->eqtb[9790].hh.rh - mem_min].hh.rh;
        goto _L30;
      }
      if (ctx->mem[q - mem_min].hh.U2.b0 == 7) {
        t = ctx->mem[q - mem_min].hh.U2.b1;
        if (!t) {
          r = ctx->mem[q - mem_min].hh.rh;
        } else {
          r = q;
          while (t > 1) {
            r = ctx->mem[r - mem_min].hh.rh;
            --t;
          }
          s = ctx->mem[r - mem_min].hh.rh;
          r = ctx->mem[s - mem_min].hh.rh;
          ctx->mem[s - mem_min].hh.rh = -1073741824;
          flush_node_list(ctx, ctx->mem[q - mem_min].hh.rh);
          ctx->mem[q - mem_min].hh.U2.b1 = 0;
        }
        if (ctx->mem[q - mem_min + 1].hh.rh != (-1073741824)) {
          s = ctx->mem[q - mem_min + 1].hh.rh;
          while (ctx->mem[s - mem_min].hh.rh != (-1073741824))
            s = ctx->mem[s - mem_min].hh.rh;
          ctx->mem[s - mem_min].hh.rh = r;
          r = ctx->mem[q - mem_min + 1].hh.rh;
          ctx->mem[q - mem_min + 1].hh.rh = -1073741824;
          post_disc_break = true;
        }
        if (ctx->mem[q - mem_min + 1].hh.lh != (-1073741824)) {
          s = ctx->mem[q - mem_min + 1].hh.lh;
          ctx->mem[q - mem_min].hh.rh = s;
          while (ctx->mem[s - mem_min].hh.rh != (-1073741824))
            s = ctx->mem[s - mem_min].hh.rh;
          ctx->mem[q - mem_min + 1].hh.lh = -1073741824;
          q = s;
        }
        ctx->mem[q - mem_min].hh.rh = r;
        disc_break = true;
      } else if ((ctx->mem[q - mem_min].hh.U2.b0 == 9) ||
                 (ctx->mem[q - mem_min].hh.U2.b0 == 11))
        ctx->mem[q - mem_min + 1].int_ = 0;
    } else {
      q = mem_max - 3;
      while (ctx->mem[q - mem_min].hh.rh != (-1073741824))
        q = ctx->mem[q - mem_min].hh.rh;
    }
    r = new_param_glue(ctx, 8);
    ctx->mem[r - mem_min].hh.rh = ctx->mem[q - mem_min].hh.rh;
    ctx->mem[q - mem_min].hh.rh = r;
    q = r;
  _L30:
    r = ctx->mem[q - mem_min].hh.rh;
    ctx->mem[q - mem_min].hh.rh = -1073741824;
    q = ctx->mem[mem_max - mem_min - 3].hh.rh;
    ctx->mem[mem_max - mem_min - 3].hh.rh = r;
    if (ctx->eqtb[9789].hh.rh) {
      r = new_param_glue(ctx, 7);
      ctx->mem[r - mem_min].hh.rh = q;
      q = r;
    }
    if (cur_line > ctx->last_special_line) {
      cur_width = ctx->second_width;
      cur_indent = ctx->second_indent;
    } else if (ctx->eqtb[10312].hh.rh == (-1073741824)) {
      cur_width = ctx->first_width;
      cur_indent = ctx->first_indent;
    } else {
      cur_width =
          ctx->mem[ctx->eqtb[10312].hh.rh + (cur_line * 2) - mem_min].int_;
      cur_indent =
          ctx->mem[ctx->eqtb[10312].hh.rh + (cur_line * 2) - mem_min - 1].int_;
    }
    ctx->adjust_tail = mem_max - 5;
    ctx->just_box = hpack(ctx, q, cur_width, 0);
    ctx->mem[ctx->just_box - mem_min + 4].int_ = cur_indent;
    append_to_vlist(ctx, ctx->just_box);
    if (mem_max - 5 != ctx->adjust_tail) {
      ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
          ctx->mem[mem_max - mem_min - 5].hh.rh;
      ctx->cur_list.tail_field = ctx->adjust_tail;
    }
    ctx->adjust_tail = -1073741824;
    if (cur_line + 1 != ctx->best_line) {
      pen = ctx->eqtb[12176].int_;
      if (cur_line == (ctx->cur_list.pg_field + 1))
        pen += ctx->eqtb[12168].int_;
      if (cur_line + 2 == ctx->best_line)
        pen += final_widow_penalty;
      if (disc_break)
        pen += ctx->eqtb[12171].int_;
      if (pen) {
        r = new_penalty(ctx, pen);
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = r;
        ctx->cur_list.tail_field = r;
      }
    }
    ++cur_line;
    ctx->cur_p = ctx->mem[ctx->cur_p - mem_min + 1].hh.lh;
    if (ctx->cur_p != (-1073741824)) {
      if (!post_disc_break) {
        r = mem_max - 3;
        while (true) {
          q = ctx->mem[r - mem_min].hh.rh;
          if (q == ctx->mem[ctx->cur_p - mem_min + 1].hh.rh)
            goto _L31;
          if (q >= ctx->hi_mem_min)
            goto _L31;
          if (ctx->mem[q - mem_min].hh.U2.b0 < 9)
            goto _L31;
          if (ctx->mem[q - mem_min].hh.U2.b0 == 11) {
            if (ctx->mem[q - mem_min].hh.U2.b1 != 1)
              goto _L31;
          }
          r = q;
        }
      _L31:
        if (r != (mem_max - 3)) {
          ctx->mem[r - mem_min].hh.rh = -1073741824;
          flush_node_list(ctx, ctx->mem[mem_max - mem_min - 3].hh.rh);
          ctx->mem[mem_max - mem_min - 3].hh.rh = q;
        }
      }
    }
  } while (ctx->cur_p != (-1073741824));
  if ((cur_line != ctx->best_line) ||
      (ctx->mem[mem_max - mem_min - 3].hh.rh != (-1073741824)))
    confusion(ctx, 938);
  ctx->cur_list.pg_field = ctx->best_line - 1;
}

small_number reconstitute(ctex_t *ctx, small_number j, small_number n,
                          halfword bchar, halfword hchar) {
  halfword p, t = mem_max - 4;
  four_quarters q;
  halfword cur_rh, test_char;
  scaled w = 0;
  font_index k;
  ctx->hyphen_passed = 0;
  ctx->mem[mem_max - mem_min - 4].hh.rh = -1073741824;
  ctx->cur_l = ctx->hu[j];
  ctx->cur_q = t;
  if (!j) {
    ctx->ligature_present = ctx->init_lig;
    p = ctx->init_list;
    if (ctx->ligature_present)
      ctx->lft_hit = ctx->init_lft;
    while (p > (-1073741824)) {
      ctx->mem[t - mem_min].hh.rh = get_avail(ctx);
      t = ctx->mem[t - mem_min].hh.rh;
      ctx->mem[t - mem_min].hh.U2.b0 = ctx->hf;
      ctx->mem[t - mem_min].hh.U2.b1 = ctx->mem[p - mem_min].hh.U2.b1;
      p = ctx->mem[p - mem_min].hh.rh;
    }
  } else if (ctx->cur_l < 256) {
    ctx->mem[t - mem_min].hh.rh = get_avail(ctx);
    t = ctx->mem[t - mem_min].hh.rh;
    ctx->mem[t - mem_min].hh.U2.b0 = ctx->hf;
    ctx->mem[t - mem_min].hh.U2.b1 = ctx->cur_l;
  }
  ctx->lig_stack = -1073741824;
  if (j < n)
    ctx->cur_r = ctx->hu[j + 1];
  else
    ctx->cur_r = bchar;
  if (ctx->hyf[j] & 1)
    cur_rh = hchar;
  else
    cur_rh = 256;
_L22:
  if (ctx->cur_l == 256) {
    k = ctx->fnt_infos.bchar_label[ctx->hf];
    if (!k)
      goto _L30;
    q = ctx->font_info[k].qqqq;
  } else {
    q = ctx->font_info[ctx->fnt_infos.char_base[ctx->hf] + ctx->cur_l].qqqq;
    if ((q.b2 & 3) != 1)
      goto _L30;
    k = ctx->fnt_infos.lig_kern_base[ctx->hf] + q.b3;
    q = ctx->font_info[k].qqqq;
    if (q.b0 > 128) {
      k = ctx->fnt_infos.lig_kern_base[ctx->hf] + (q.b2 * 256) + q.b3;
      q = ctx->font_info[k].qqqq;
    }
  }
  if (cur_rh < 256)
    test_char = cur_rh;
  else
    test_char = ctx->cur_r;
  while (true) {
    if (q.b1 == test_char) {
      if (q.b0 <= 128) {
        if (cur_rh < 256) {
          ctx->hyphen_passed = j;
          hchar = 256;
          cur_rh = 256;
          goto _L22;
        } else {
          if (hchar < 256) {
            if (ctx->hyf[j] & 1) {
              ctx->hyphen_passed = j;
              hchar = 256;
            }
          }
          if (q.b2 < 128) {
            if (ctx->cur_l == 256)
              ctx->lft_hit = true;
            if (j == n) {
              if (ctx->lig_stack == (-1073741824))
                ctx->rt_hit = true;
            }
            if (ctx->interrupt)
              pause_for_instructions(ctx);
            switch (q.b2) {
            case 1:
            case 5:
              ctx->cur_l = q.b3;
              ctx->ligature_present = true;
              break;
            case 2:
            case 6:
              ctx->cur_r = q.b3;
              if (ctx->lig_stack > (-1073741824)) {
                ctx->mem[ctx->lig_stack - mem_min].hh.U2.b1 = ctx->cur_r;
              } else {
                ctx->lig_stack = new_lig_item(ctx, ctx->cur_r);
                if (j == n) {
                  bchar = 256;
                } else {
                  p = get_avail(ctx);
                  ctx->mem[ctx->lig_stack - mem_min + 1].hh.rh = p;
                  ctx->mem[p - mem_min].hh.U2.b1 = ctx->hu[j + 1];
                  ctx->mem[p - mem_min].hh.U2.b0 = ctx->hf;
                }
              }
              break;
            case 3:
              ctx->cur_r = q.b3;
              p = ctx->lig_stack;
              ctx->lig_stack = new_lig_item(ctx, ctx->cur_r);
              ctx->mem[ctx->lig_stack - mem_min].hh.rh = p;
              break;
            case 7:
            case 11:
              if (ctx->ligature_present) {
                p = new_ligature(ctx, ctx->hf, ctx->cur_l,
                                 ctx->mem[ctx->cur_q - mem_min].hh.rh);
                if (ctx->lft_hit) {
                  ctx->mem[p - mem_min].hh.U2.b1 = 2;
                  ctx->lft_hit = false;
                }
                ctx->mem[ctx->cur_q - mem_min].hh.rh = p;
                t = p;
                ctx->ligature_present = false;
              }
              ctx->cur_q = t;
              ctx->cur_l = q.b3;
              ctx->ligature_present = true;
              break;
            default:
              ctx->cur_l = q.b3;
              ctx->ligature_present = true;
              if (ctx->lig_stack > (-1073741824)) {
                if (ctx->mem[ctx->lig_stack - mem_min + 1].hh.rh >
                    (-1073741824)) {
                  ctx->mem[t - mem_min].hh.rh =
                      ctx->mem[ctx->lig_stack - mem_min + 1].hh.rh;
                  t = ctx->mem[t - mem_min].hh.rh;
                  ++j;
                }
                p = ctx->lig_stack;
                ctx->lig_stack = ctx->mem[p - mem_min].hh.rh;
                free_node(ctx, p, 2);
                if (ctx->lig_stack == (-1073741824)) {
                  if (j < n)
                    ctx->cur_r = ctx->hu[j + 1];
                  else
                    ctx->cur_r = bchar;
                  if (ctx->hyf[j] & 1)
                    cur_rh = hchar;
                  else
                    cur_rh = 256;
                } else {
                  ctx->cur_r = ctx->mem[ctx->lig_stack - mem_min].hh.U2.b1;
                }
              } else if (j == n) {
                goto _L30;
              } else {
                ctx->mem[t - mem_min].hh.rh = get_avail(ctx);
                t = ctx->mem[t - mem_min].hh.rh;
                ctx->mem[t - mem_min].hh.U2.b0 = ctx->hf;
                ctx->mem[t - mem_min].hh.U2.b1 = ctx->cur_r;
                ++j;
                if (j < n)
                  ctx->cur_r = ctx->hu[j + 1];
                else
                  ctx->cur_r = bchar;
                if (ctx->hyf[j] & 1)
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
          w = ctx->font_info[ctx->fnt_infos.kern_base[ctx->hf] + (q.b2 * 256) +
                             q.b3]
                  .int_;
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
    q = ctx->font_info[k].qqqq;
  }
_L30:
  if (ctx->ligature_present) {
    p = new_ligature(ctx, ctx->hf, ctx->cur_l,
                     ctx->mem[ctx->cur_q - mem_min].hh.rh);
    if (ctx->lft_hit) {
      ctx->mem[p - mem_min].hh.U2.b1 = 2;
      ctx->lft_hit = false;
    }
    if (ctx->rt_hit) {
      if (ctx->lig_stack == (-1073741824)) {
        ++ctx->mem[p - mem_min].hh.U2.b1;
        ctx->rt_hit = false;
      }
    }
    ctx->mem[ctx->cur_q - mem_min].hh.rh = p;
    t = p;
    ctx->ligature_present = false;
  }
  if (w) {
    ctx->mem[t - mem_min].hh.rh = new_kern(ctx, w);
    t = ctx->mem[t - mem_min].hh.rh;
    w = 0;
  }
  if (ctx->lig_stack <= (-1073741824))
    return j;
  ctx->cur_q = t;
  ctx->cur_l = ctx->mem[ctx->lig_stack - mem_min].hh.U2.b1;
  ctx->ligature_present = true;
  if (ctx->mem[ctx->lig_stack - mem_min + 1].hh.rh > (-1073741824)) {
    ctx->mem[t - mem_min].hh.rh = ctx->mem[ctx->lig_stack - mem_min + 1].hh.rh;
    t = ctx->mem[t - mem_min].hh.rh;
    ++j;
  }
  p = ctx->lig_stack;
  ctx->lig_stack = ctx->mem[p - mem_min].hh.rh;
  free_node(ctx, p, 2);
  if (ctx->lig_stack == (-1073741824)) {
    if (j < n)
      ctx->cur_r = ctx->hu[j + 1];
    else
      ctx->cur_r = bchar;
    if (ctx->hyf[j] & 1)
      cur_rh = hchar;
    else
      cur_rh = 256;
  } else {
    ctx->cur_r = ctx->mem[ctx->lig_stack - mem_min].hh.U2.b1;
  }
  goto _L22;
}

void hyphenate(ctex_t *ctx) {
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
  for (N = ctx->hn, j = 0; j <= N; ++j)
    ctx->hyf[j] = 0;
  h = ctx->hc[1];
  ++ctx->hn;
  ctx->hc[ctx->hn] = ctx->cur_lang;
  for (N = ctx->hn, j = 2; j <= N; ++j)
    h = (h + h + ctx->hc[j]) % 307;
  while (true) {
    k = ctx->hyph_word[h];
    if (!k)
      goto _L45;
    if (ctx->str_start[k + 1] - ctx->str_start[k] < ctx->hn)
      goto _L45;
    if (ctx->str_start[k + 1] - ctx->str_start[k] == ctx->hn) {
      j = 1;
      u = ctx->str_start[k];
      do {
        if (ctx->str_pool[u] < ctx->hc[j])
          goto _L45;
        if (ctx->str_pool[u] > ctx->hc[j])
          goto _L30;
        ++j;
        ++u;
      } while (j <= ctx->hn);
      s = ctx->hyph_list[h];
      while (s != (-1073741824)) {
        ctx->hyf[ctx->mem[s - mem_min].hh.lh] = 1;
        s = ctx->mem[s - mem_min].hh.rh;
      }
      --ctx->hn;
      goto _L40;
    }
  _L30:
    if (h > 0)
      --h;
    else
      h = 307;
  }
_L45:
  --ctx->hn;
  if (ctx->trie[ctx->cur_lang + 1].U2.b1 != ctx->cur_lang)
    goto _L10;
  ctx->hc[0] = 0;
  ctx->hc[ctx->hn + 1] = 0;
  ctx->hc[ctx->hn + 2] = 256;
  for (N = ctx->hn - ctx->r_hyf + 1, j = 0; j <= N; ++j) {
    z = ctx->trie[ctx->cur_lang + 1].rh + ctx->hc[j];
    l = j;
    while (ctx->hc[l] == ctx->trie[z].U2.b1) {
      if (ctx->trie[z].U2.b0) {
        v = ctx->trie[z].U2.b0;
        do {
          v += ctx->op_start[ctx->cur_lang];
          i = l - ctx->hyf_distance[v];
          if (ctx->hyf_num[v] > ctx->hyf[i])
            ctx->hyf[i] = ctx->hyf_num[v];
          v = ctx->hyf_next[v];
        } while (v);
      }
      ++l;
      z = ctx->trie[z].rh + ctx->hc[l];
    }
  }
_L40:
  for (N = ctx->l_hyf, j = 0; j <= (N - 1); ++j)
    ctx->hyf[j] = 0;
  for (N = ctx->r_hyf, j = 0; j <= (N - 1); ++j)
    ctx->hyf[ctx->hn - j] = 0;
  for (N = ctx->hn - ctx->r_hyf, j = ctx->l_hyf; j <= N; ++j) {
    if (ctx->hyf[j] & 1)
      goto _L41;
  }
  goto _L10;
_L41:
  q = ctx->mem[ctx->hb - mem_min].hh.rh;
  ctx->mem[ctx->hb - mem_min].hh.rh = -1073741824;
  r = ctx->mem[ctx->ha - mem_min].hh.rh;
  ctx->mem[ctx->ha - mem_min].hh.rh = -1073741824;
  bchar = ctx->hyf_bchar;
  if (ctx->ha >= ctx->hi_mem_min) {
    if (ctx->mem[ctx->ha - mem_min].hh.U2.b0 != ctx->hf)
      goto _L42;
    ctx->init_list = ctx->ha;
    ctx->init_lig = false;
    ctx->hu[0] = ctx->mem[ctx->ha - mem_min].hh.U2.b1;
  } else if (ctx->mem[ctx->ha - mem_min].hh.U2.b0 == 6) {
    if (ctx->mem[ctx->ha - mem_min + 1].hh.U2.b0 != ctx->hf)
      goto _L42;
    ctx->init_list = ctx->mem[ctx->ha - mem_min + 1].hh.rh;
    ctx->init_lig = true;
    ctx->init_lft = (ctx->mem[ctx->ha - mem_min].hh.U2.b1 > 1);
    ctx->hu[0] = ctx->mem[ctx->ha - mem_min + 1].hh.U2.b1;
    if (ctx->init_list == (-1073741824)) {
      if (ctx->init_lft) {
        ctx->hu[0] = 256;
        ctx->init_lig = false;
      }
    }
    free_node(ctx, ctx->ha, 2);
  } else {
    if (r < ctx->hi_mem_min) {
      if (ctx->mem[r - mem_min].hh.U2.b0 == 6) {
        if (ctx->mem[r - mem_min].hh.U2.b1 > 1)
          goto _L42;
      }
    }
    j = 1;
    s = ctx->ha;
    ctx->init_list = -1073741824;
    goto _L50;
  }
  s = ctx->cur_p;
  while (ctx->mem[s - mem_min].hh.rh != ctx->ha)
    s = ctx->mem[s - mem_min].hh.rh;
  j = 0;
  goto _L50;
_L42:
  s = ctx->ha;
  j = 0;
  ctx->hu[0] = 256;
  ctx->init_lig = false;
  ctx->init_list = -1073741824;
_L50:
  flush_node_list(ctx, r);
  do {
    l = j;
    j = reconstitute(ctx, j, ctx->hn, bchar, ctx->hyf_char) + 1;
    if (!ctx->hyphen_passed) {
      ctx->mem[s - mem_min].hh.rh = ctx->mem[mem_max - mem_min - 4].hh.rh;
      while (ctx->mem[s - mem_min].hh.rh > (-1073741824))
        s = ctx->mem[s - mem_min].hh.rh;
      if (ctx->hyf[j - 1] & 1) {
        l = j;
        ctx->hyphen_passed = j - 1;
        ctx->mem[mem_max - mem_min - 4].hh.rh = -1073741824;
      }
    }
    if (ctx->hyphen_passed > 0) {
      do {
        r = get_node(ctx, 2);
        ctx->mem[r - mem_min].hh.rh = ctx->mem[mem_max - mem_min - 4].hh.rh;
        ctx->mem[r - mem_min].hh.U2.b0 = 7;
        major_tail = r;
        r_count = 0;
        while (ctx->mem[major_tail - mem_min].hh.rh > (-1073741824)) {
          major_tail = ctx->mem[major_tail - mem_min].hh.rh;
          ++r_count;
        }
        i = ctx->hyphen_passed;
        ctx->hyf[i] = 0;
        minor_tail = -1073741824;
        ctx->mem[r - mem_min + 1].hh.lh = -1073741824;
        hyf_node = new_character(ctx, ctx->hf, ctx->hyf_char);
        if (hyf_node != (-1073741824)) {
          ++i;
          c = ctx->hu[i];
          ctx->hu[i] = ctx->hyf_char;
          ctx->mem[hyf_node - mem_min].hh.rh = ctx->avail;
          ctx->avail = hyf_node;
        }
        while (l <= i) {
          l = reconstitute(ctx, l, i, ctx->fnt_infos.font_bchar[ctx->hf], 256) +
              1;
          if (ctx->mem[mem_max - mem_min - 4].hh.rh <= (-1073741824))
            continue;
          if (minor_tail == (-1073741824))
            ctx->mem[r - mem_min + 1].hh.lh =
                ctx->mem[mem_max - mem_min - 4].hh.rh;
          else
            ctx->mem[minor_tail - mem_min].hh.rh =
                ctx->mem[mem_max - mem_min - 4].hh.rh;
          minor_tail = ctx->mem[mem_max - mem_min - 4].hh.rh;
          while (ctx->mem[minor_tail - mem_min].hh.rh > (-1073741824))
            minor_tail = ctx->mem[minor_tail - mem_min].hh.rh;
        }
        if (hyf_node != (-1073741824)) {
          ctx->hu[i] = c;
          l = i;
          --i;
        }
        minor_tail = -1073741824;
        ctx->mem[r - mem_min + 1].hh.rh = -1073741824;
        c_loc = 0;
        if (ctx->fnt_infos.bchar_label[ctx->hf]) {
          --l;
          c = ctx->hu[l];
          c_loc = l;
          ctx->hu[l] = 256;
        }
        while (l < j) {
          do {
            l = reconstitute(ctx, l, ctx->hn, bchar, 256) + 1;
            if (c_loc > 0) {
              ctx->hu[c_loc] = c;
              c_loc = 0;
            }
            if (ctx->mem[mem_max - mem_min - 4].hh.rh > (-1073741824)) {
              if (minor_tail == (-1073741824))
                ctx->mem[r - mem_min + 1].hh.rh =
                    ctx->mem[mem_max - mem_min - 4].hh.rh;
              else
                ctx->mem[minor_tail - mem_min].hh.rh =
                    ctx->mem[mem_max - mem_min - 4].hh.rh;
              minor_tail = ctx->mem[mem_max - mem_min - 4].hh.rh;
              while (ctx->mem[minor_tail - mem_min].hh.rh > (-1073741824))
                minor_tail = ctx->mem[minor_tail - mem_min].hh.rh;
            }
          } while (l < j);
          while (l > j) {
            j = reconstitute(ctx, j, ctx->hn, bchar, 256) + 1;
            ctx->mem[major_tail - mem_min].hh.rh =
                ctx->mem[mem_max - mem_min - 4].hh.rh;
            while (ctx->mem[major_tail - mem_min].hh.rh > (-1073741824)) {
              major_tail = ctx->mem[major_tail - mem_min].hh.rh;
              ++r_count;
            }
          }
        }
        if (r_count > 127) {
          ctx->mem[s - mem_min].hh.rh = ctx->mem[r - mem_min].hh.rh;
          ctx->mem[r - mem_min].hh.rh = -1073741824;
          flush_node_list(ctx, r);
        } else {
          ctx->mem[s - mem_min].hh.rh = r;
          ctx->mem[r - mem_min].hh.U2.b1 = r_count;
        }
        s = major_tail;
        ctx->hyphen_passed = j - 1;
        ctx->mem[mem_max - mem_min - 4].hh.rh = -1073741824;
      } while (ctx->hyf[j - 1] & 1);
    }
  } while (j <= ctx->hn);
  ctx->mem[s - mem_min].hh.rh = q;
  flush_list(ctx, ctx->init_list);
_L10:;
}

quarterword new_trie_op(ctex_t *ctx, small_number d, small_number n,
                        quarterword v) {
  quarterword result, u;
  int l;
  int h = (abs(n + (d * 313) + (v * 361) + (ctx->cur_lang * 1009)) %
           (trie_op_size + trie_op_size)) -
          trie_op_size;
  while (true) {
    l = ctx->trie_op_hash[h + trie_op_size];
    if (!l) {
      if (ctx->trie_op_ptr == trie_op_size)
        overflow(ctx, 948, trie_op_size);
      u = ctx->trie_used[ctx->cur_lang];
      if (u == 65535)
        overflow(ctx, 949, 65535);
      ++ctx->trie_op_ptr;
      ++u;
      ctx->trie_used[ctx->cur_lang] = u;
      ctx->hyf_distance[ctx->trie_op_ptr] = d;
      ctx->hyf_num[ctx->trie_op_ptr] = n;
      ctx->hyf_next[ctx->trie_op_ptr] = v;
      ctx->trie_op_lang[ctx->trie_op_ptr] = ctx->cur_lang;
      ctx->trie_op_hash[h + trie_op_size] = ctx->trie_op_ptr;
      ctx->trie_op_val[ctx->trie_op_ptr] = u;
      result = u;
      goto _L10;
    }
    if ((ctx->hyf_distance[l] == d) && (ctx->hyf_num[l] == n) &&
        (ctx->hyf_next[l] == v) && (ctx->trie_op_lang[l] == ctx->cur_lang)) {
      result = ctx->trie_op_val[l];
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

trie_pointer trie_node(ctex_t *ctx, trie_pointer p) {
  trie_pointer result, q;
  trie_pointer h = abs(ctx->trie_c[p] + (ctx->trie_o[p] * 1009) +
                       (ctx->trie_l[p] * 2718) + (ctx->trie_r[p] * 3142)) %
                   trie_size;
  while (true) {
    q = ctx->trie_hash[h];
    if (!q) {
      ctx->trie_hash[h] = p;
      result = p;
      goto _L10;
    }
    if ((ctx->trie_c[q] == ctx->trie_c[p]) &&
        (ctx->trie_o[q] == ctx->trie_o[p]) &&
        (ctx->trie_l[q] == ctx->trie_l[p]) &&
        (ctx->trie_r[q] == ctx->trie_r[p])) {
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

trie_pointer compress_trie(ctex_t *ctx, trie_pointer p) {
  if (!p) {
    return 0;
  } else {
    ctx->trie_l[p] = compress_trie(ctx, ctx->trie_l[p]);
    ctx->trie_r[p] = compress_trie(ctx, ctx->trie_r[p]);
    return trie_node(ctx, p);
  }
}

void first_fit(ctex_t *ctx, trie_pointer p) {
  trie_pointer h, q, l, r;
  short ll;
  ASCII_code c = ctx->trie_c[p];
  trie_pointer z = ctx->trie_min[c];
  while (true) {
    h = z - c;
    if (ctx->trie_max < (h + 256)) {
      if (trie_size <= (h + 256))
        overflow(ctx, 950, trie_size);
      do {
        ++ctx->trie_max;
        CTEX_BITCLEAR(ctx->trie_taken, ctx->trie_max - 1);
        ctx->trie[ctx->trie_max].rh = ctx->trie_max + 1;
        ctx->trie[ctx->trie_max].lh = ctx->trie_max - 1;
      } while (ctx->trie_max != (h + 256));
    }
    if (CTEX_BITTEST(ctx->trie_taken, h - 1))
      goto _L45;
    q = ctx->trie_r[p];
    while (q > 0) {
      if (!ctx->trie[h + ctx->trie_c[q]].rh)
        goto _L45;
      q = ctx->trie_r[q];
    }
    goto _L40;
  _L45:
    z = ctx->trie[z].rh;
  }
_L40:
  CTEX_BITSET(ctx->trie_taken, h - 1);
  ctx->trie_hash[p] = h;
  q = p;
  do {
    z = h + ctx->trie_c[q];
    l = ctx->trie[z].lh;
    r = ctx->trie[z].rh;
    ctx->trie[r].lh = l;
    ctx->trie[l].rh = r;
    ctx->trie[z].rh = 0;
    if (l < 256) {
      if (z < 256)
        ll = z;
      else
        ll = 256;
      do {
        ctx->trie_min[l] = r;
        ++l;
      } while (l != ll);
    }
    q = ctx->trie_r[q];
  } while (q);
}

void trie_pack(ctex_t *ctx, trie_pointer p) {
  trie_pointer q;
  do {
    q = ctx->trie_l[p];
    if ((q > 0) && (!ctx->trie_hash[q])) {
      first_fit(ctx, q);
      trie_pack(ctx, q);
    }
    p = ctx->trie_r[p];
  } while (p);
}

void trie_fix(ctex_t *ctx, trie_pointer p) {
  trie_pointer q;
  ASCII_code c;
  trie_pointer z = ctx->trie_hash[p];
  do {
    q = ctx->trie_l[p];
    c = ctx->trie_c[p];
    ctx->trie[z + c].rh = ctx->trie_hash[q];
    ctx->trie[z + c].U2.b1 = c;
    ctx->trie[z + c].U2.b0 = ctx->trie_o[p];
    if (q > 0)
      trie_fix(ctx, q);
    p = ctx->trie_r[p];
  } while (p);
}

void new_patterns(ctex_t *ctx) {
  char k, l;
  bool_t digit_sensed;
  quarterword v;
  trie_pointer p, q;
  bool_t first_child;
  ASCII_code c;
  if (ctx->trie_not_ready) {
    if (ctx->eqtb[12213].int_ <= 0) {
      ctx->cur_lang = 0;
    } else if (ctx->eqtb[12213].int_ > 255)
      ctx->cur_lang = 0;
    else
      ctx->cur_lang = ctx->eqtb[12213].int_;
    scan_left_brace(ctx);
    k = 0;
    ctx->hyf[0] = 0;
    digit_sensed = false;
    while (true) {
      get_x_token(ctx);
      switch (ctx->cur_cmd) {
      case 11:
      case 12:
        if (digit_sensed || (ctx->cur_chr < 48) || (ctx->cur_chr > 57)) {
          if (ctx->cur_chr == 46) {
            ctx->cur_chr = 0;
          } else {
            ctx->cur_chr = ctx->eqtb[ctx->cur_chr + 11139].hh.rh;
            if (!ctx->cur_chr) {
              print_nl(ctx, 262);
              print(ctx, 956);
              ctx->help_ptr = 1;
              ctx->help_line[0] = 955;
              error(ctx);
            }
          }
          if (k < 63) {
            ++k;
            ctx->hc[k] = ctx->cur_chr;
            ctx->hyf[k] = 0;
            digit_sensed = false;
          }
        } else if (k < 63) {
          ctx->hyf[k] = ctx->cur_chr - 48;
          digit_sensed = true;
        }
        break;
      case 10:
      case 2:
        if (k > 0) {
          if (!ctx->hc[1])
            ctx->hyf[0] = 0;
          if (!ctx->hc[k])
            ctx->hyf[k] = 0;
          l = k;
          v = 0;
          while (true) {
            if (ctx->hyf[l])
              v = new_trie_op(ctx, k - l, ctx->hyf[l], v);
            if (l <= 0)
              goto _L31;
            --l;
          }
        _L31:
          q = 0;
          ctx->hc[0] = ctx->cur_lang;
          while (l <= k) {
            c = ctx->hc[l];
            ++l;
            p = ctx->trie_l[q];
            first_child = true;
            while ((p > 0) && (c > ctx->trie_c[p])) {
              q = p;
              p = ctx->trie_r[q];
              first_child = false;
            }
            if ((!p) || (c < ctx->trie_c[p])) {
              if (ctx->trie_ptr == trie_size)
                overflow(ctx, 950, trie_size);
              ++ctx->trie_ptr;
              ctx->trie_r[ctx->trie_ptr] = p;
              p = ctx->trie_ptr;
              ctx->trie_l[p] = 0;
              if (first_child)
                ctx->trie_l[q] = p;
              else
                ctx->trie_r[q] = p;
              ctx->trie_c[p] = c;
              ctx->trie_o[p] = 0;
            }
            q = p;
          }
          if (ctx->trie_o[q]) {
            print_nl(ctx, 262);
            print(ctx, 957);
            ctx->help_ptr = 1;
            ctx->help_line[0] = 955;
            error(ctx);
          }
          ctx->trie_o[q] = v;
        }
        if (ctx->cur_cmd == 2)
          goto _L30;
        k = 0;
        ctx->hyf[0] = 0;
        digit_sensed = false;
        break;
      default:
        print_nl(ctx, 262);
        print(ctx, 954);
        print_esc(ctx, 952);
        ctx->help_ptr = 1;
        ctx->help_line[0] = 955;
        error(ctx);
        break;
      }
    }
  _L30:
    return;
  }
  print_nl(ctx, 262);
  print(ctx, 951);
  print_esc(ctx, 952);
  ctx->help_ptr = 1;
  ctx->help_line[0] = 953;
  error(ctx);
  ctx->mem[mem_max - mem_min - 12].hh.rh = scan_toks(ctx, false, false);
  flush_list(ctx, ctx->def_ref);
}

void init_trie(ctex_t *ctx) {
  trie_pointer p, r, s;
  integer j, k, t;
  two_halves h;
  int N;
  trie_pointer N1;
  ctx->op_start[0] = 0;
  for (j = 1; j <= 255; ++j)
    ctx->op_start[j] = ctx->op_start[j - 1] + ctx->trie_used[j - 1];
  for (N = ctx->trie_op_ptr, j = 1; j <= N; ++j)
    ctx->trie_op_hash[j + trie_op_size] =
        ctx->op_start[ctx->trie_op_lang[j]] + ctx->trie_op_val[j];
  for (N = ctx->trie_op_ptr, j = 1; j <= N; ++j) {
    while (ctx->trie_op_hash[j + trie_op_size] > j) {
      k = ctx->trie_op_hash[j + trie_op_size];
      t = ctx->hyf_distance[k];
      ctx->hyf_distance[k] = ctx->hyf_distance[j];
      ctx->hyf_distance[j] = t;
      t = ctx->hyf_num[k];
      ctx->hyf_num[k] = ctx->hyf_num[j];
      ctx->hyf_num[j] = t;
      t = ctx->hyf_next[k];
      ctx->hyf_next[k] = ctx->hyf_next[j];
      ctx->hyf_next[j] = t;
      ctx->trie_op_hash[j + trie_op_size] = ctx->trie_op_hash[k + trie_op_size];
      ctx->trie_op_hash[k + trie_op_size] = k;
    }
  }
  for (p = 0; p <= trie_size; ++p)
    ctx->trie_hash[p] = 0;
  ctx->trie_l[0] = compress_trie(ctx, ctx->trie_l[0]);
  for (N1 = ctx->trie_ptr, p = 0; p <= N1; ++p)
    ctx->trie_hash[p] = 0;
  for (p = 0; p <= 255; ++p)
    ctx->trie_min[p] = p + 1;
  ctx->trie[0].rh = 1;
  ctx->trie_max = 0;
  if (ctx->trie_l[0]) {
    first_fit(ctx, ctx->trie_l[0]);
    trie_pack(ctx, ctx->trie_l[0]);
  }
  h.rh = 0;
  h.U2.b0 = 0;
  h.U2.b1 = 0;
  if (!ctx->trie_l[0]) {
    for (r = 0; r <= 256; ++r)
      ctx->trie[r] = h;
    ctx->trie_max = 256;
  } else {
    trie_fix(ctx, ctx->trie_l[0]);
    r = 0;
    do {
      s = ctx->trie[r].rh;
      ctx->trie[r] = h;
      r = s;
    } while (r <= ctx->trie_max);
  }
  ctx->trie[0].U2.b1 = 63;
  ctx->trie_not_ready = false;
}

void line_break(ctex_t *ctx, integer final_widow_penalty) {
  bool_t auto_breaking;
  halfword prev_p, q, r, s, prev_s;
  internal_font_number f;
  small_number j;
  uint8_t c;
  ctx->pack_begin_line = ctx->cur_list.ml_field;
  ctx->mem[mem_max - mem_min - 3].hh.rh =
      ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh;
  if (ctx->cur_list.tail_field >= ctx->hi_mem_min) {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        new_penalty(ctx, 10000);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  } else if (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 != 10) {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        new_penalty(ctx, 10000);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  } else {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 = 12;
    delete_glue_ref(ctx,
                    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.lh);
    flush_node_list(ctx,
                    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.rh);
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].int_ = 10000;
  }
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_param_glue(ctx, 14);
  ctx->init_cur_lang = ctx->cur_list.pg_field & 65535;
  ctx->init_l_hyf = ctx->cur_list.pg_field / 4194304;
  ctx->init_r_hyf = (ctx->cur_list.pg_field / 65536) & 63;
  pop_nest(ctx);
  ctx->no_shrink_error_yet = true;
  if (ctx->mem[ctx->eqtb[9789].hh.rh - mem_min].hh.U2.b1 &&
      ctx->mem[ctx->eqtb[9789].hh.rh - mem_min + 3].int_)
    ctx->eqtb[9789].hh.rh = finite_shrink(ctx, ctx->eqtb[9789].hh.rh);
  if (ctx->mem[ctx->eqtb[9790].hh.rh - mem_min].hh.U2.b1 &&
      ctx->mem[ctx->eqtb[9790].hh.rh - mem_min + 3].int_)
    ctx->eqtb[9790].hh.rh = finite_shrink(ctx, ctx->eqtb[9790].hh.rh);
  q = ctx->eqtb[9789].hh.rh;
  r = ctx->eqtb[9790].hh.rh;
  ctx->background[1] =
      ctx->mem[q - mem_min + 1].int_ + ctx->mem[r - mem_min + 1].int_;
  ctx->background[2] = 0;
  ctx->background[3] = 0;
  ctx->background[4] = 0;
  ctx->background[5] = 0;
  ctx->background[ctx->mem[q - mem_min].hh.U2.b0 + 2] =
      ctx->mem[q - mem_min + 2].int_;
  ctx->background[ctx->mem[r - mem_min].hh.U2.b0 + 2] +=
      ctx->mem[r - mem_min + 2].int_;
  ctx->background[6] =
      ctx->mem[q - mem_min + 3].int_ + ctx->mem[r - mem_min + 3].int_;
  ctx->minimum_demerits = 1073741823;
  ctx->minimal_demerits[3] = 1073741823;
  ctx->minimal_demerits[2] = 1073741823;
  ctx->minimal_demerits[1] = 1073741823;
  ctx->minimal_demerits[0] = 1073741823;
  if (ctx->eqtb[10312].hh.rh == (-1073741824)) {
    if (!ctx->eqtb[12747].int_) {
      ctx->last_special_line = 0;
      ctx->second_width = ctx->eqtb[12733].int_;
      ctx->second_indent = 0;
    } else {
      ctx->last_special_line = abs(ctx->eqtb[12204].int_);
      if (ctx->eqtb[12204].int_ < 0) {
        ctx->first_width = ctx->eqtb[12733].int_ - abs(ctx->eqtb[12747].int_);
        if (ctx->eqtb[12747].int_ >= 0)
          ctx->first_indent = ctx->eqtb[12747].int_;
        else
          ctx->first_indent = 0;
        ctx->second_width = ctx->eqtb[12733].int_;
        ctx->second_indent = 0;
      } else {
        ctx->first_width = ctx->eqtb[12733].int_;
        ctx->first_indent = 0;
        ctx->second_width = ctx->eqtb[12733].int_ - abs(ctx->eqtb[12747].int_);
        if (ctx->eqtb[12747].int_ >= 0)
          ctx->second_indent = ctx->eqtb[12747].int_;
        else
          ctx->second_indent = 0;
      }
    }
  } else {
    ctx->last_special_line =
        ctx->mem[ctx->eqtb[10312].hh.rh - mem_min].hh.lh - 1;
    ctx->second_width = ctx->mem[ctx->eqtb[10312].hh.rh +
                                 ((ctx->last_special_line + 1) * 2) - mem_min]
                            .int_;
    ctx->second_indent = ctx->mem[ctx->eqtb[10312].hh.rh +
                                  (ctx->last_special_line * 2) - mem_min + 1]
                             .int_;
  }
  if (!ctx->eqtb[12182].int_)
    ctx->easy_line = ctx->last_special_line;
  else
    ctx->easy_line = 1073741824;
  ctx->threshold = ctx->eqtb[12163].int_;
  if (ctx->threshold >= 0) {
    ctx->second_pass = false;
    ctx->final_pass = false;
  } else {
    ctx->threshold = ctx->eqtb[12164].int_;
    ctx->second_pass = true;
    ctx->final_pass = (ctx->eqtb[12750].int_ <= 0);
  }
  while (true) {
    if (ctx->threshold > 10000)
      ctx->threshold = 10000;
    if (ctx->second_pass) {
      if (ctx->trie_not_ready)
        init_trie(ctx);
      ctx->cur_lang = ctx->init_cur_lang;
      ctx->l_hyf = ctx->init_l_hyf;
      ctx->r_hyf = ctx->init_r_hyf;
    }
    q = get_node(ctx, 3);
    ctx->mem[q - mem_min].hh.U2.b0 = 0;
    ctx->mem[q - mem_min].hh.U2.b1 = 2;
    ctx->mem[q - mem_min].hh.rh = mem_max - 7;
    ctx->mem[q - mem_min + 1].hh.rh = -1073741824;
    ctx->mem[q - mem_min + 1].hh.lh = ctx->cur_list.pg_field + 1;
    ctx->mem[q - mem_min + 2].int_ = 0;
    ctx->mem[mem_max - mem_min - 7].hh.rh = q;
    ctx->active_width[1] = ctx->background[1];
    ctx->active_width[2] = ctx->background[2];
    ctx->active_width[3] = ctx->background[3];
    ctx->active_width[4] = ctx->background[4];
    ctx->active_width[5] = ctx->background[5];
    ctx->active_width[6] = ctx->background[6];
    ctx->passive = -1073741824;
    ctx->printed_node = mem_max - 3;
    ctx->pass_number = 0;
    ctx->font_in_short_display = 0;
    ctx->cur_p = ctx->mem[mem_max - mem_min - 3].hh.rh;
    auto_breaking = true;
    prev_p = ctx->cur_p;
    while ((ctx->cur_p != (-1073741824)) &&
           (ctx->mem[mem_max - mem_min - 7].hh.rh != (mem_max - 7))) {
      if (ctx->cur_p >= ctx->hi_mem_min) {
        prev_p = ctx->cur_p;
        do {
          f = ctx->mem[ctx->cur_p - mem_min].hh.U2.b0;
          (ctx->active_width[1] +=
           (ctx
                ->font_info[(
                    ctx->fnt_infos.width_base[f] +
                    ((ctx->font_info[ctx->fnt_infos.char_base[f] +
                                     ctx->mem[ctx->cur_p - mem_min].hh.U2.b1]
                          .qqqq)
                         .b0))]
                .int_));
          ctx->cur_p = ctx->mem[ctx->cur_p - mem_min].hh.rh;
        } while (ctx->cur_p >= ctx->hi_mem_min);
      }
      switch (ctx->mem[ctx->cur_p - mem_min].hh.U2.b0) {
      case 0:
      case 1:
      case 2:
        ctx->active_width[1] += ctx->mem[ctx->cur_p - mem_min + 1].int_;
        break;
      case 8:
        if (ctx->mem[ctx->cur_p - mem_min].hh.U2.b1 == 4) {
          ctx->cur_lang = ctx->mem[ctx->cur_p - mem_min + 1].hh.rh;
          ctx->l_hyf = ctx->mem[ctx->cur_p - mem_min + 1].hh.U2.b0;
          ctx->r_hyf = ctx->mem[ctx->cur_p - mem_min + 1].hh.U2.b1;
        }
        break;
      case 10:
        if (auto_breaking) {
          if (prev_p >= ctx->hi_mem_min) {
            try_break(ctx, 0, 0);
          } else if (ctx->mem[prev_p - mem_min].hh.U2.b0 < 9) {
            try_break(ctx, 0, 0);
          } else if ((ctx->mem[prev_p - mem_min].hh.U2.b0 == 11) &&
                     (ctx->mem[prev_p - mem_min].hh.U2.b1 != 1))
            try_break(ctx, 0, 0);
        }
        if (ctx->mem[ctx->mem[ctx->cur_p - mem_min + 1].hh.lh - mem_min]
                .hh.U2.b1 &&
            ctx->mem[ctx->mem[ctx->cur_p - mem_min + 1].hh.lh - mem_min + 3]
                .int_)
          ctx->mem[ctx->cur_p - mem_min + 1].hh.lh =
              finite_shrink(ctx, ctx->mem[ctx->cur_p - mem_min + 1].hh.lh);
        q = ctx->mem[ctx->cur_p - mem_min + 1].hh.lh;
        ctx->active_width[1] += ctx->mem[q - mem_min + 1].int_;
        ctx->active_width[ctx->mem[q - mem_min].hh.U2.b0 + 2] +=
            ctx->mem[q - mem_min + 2].int_;
        ctx->active_width[6] += ctx->mem[q - mem_min + 3].int_;
        if (ctx->second_pass && auto_breaking) {
          prev_s = ctx->cur_p;
          s = ctx->mem[prev_s - mem_min].hh.rh;
          if (s != (-1073741824)) {
            while (true) {
              if (s >= ctx->hi_mem_min) {
                c = ctx->mem[s - mem_min].hh.U2.b1;
                ctx->hf = ctx->mem[s - mem_min].hh.U2.b0;
              } else if (ctx->mem[s - mem_min].hh.U2.b0 == 6) {
                if (ctx->mem[s - mem_min + 1].hh.rh == (-1073741824))
                  goto _L22;
                q = ctx->mem[s - mem_min + 1].hh.rh;
                c = ctx->mem[q - mem_min].hh.U2.b1;
                ctx->hf = ctx->mem[q - mem_min].hh.U2.b0;
              } else if ((ctx->mem[s - mem_min].hh.U2.b0 == 11) &&
                         (!ctx->mem[s - mem_min].hh.U2.b1)) {
                goto _L22;
              } else if (ctx->mem[s - mem_min].hh.U2.b0 == 8) {
                if (ctx->mem[s - mem_min].hh.U2.b1 == 4) {
                  ctx->cur_lang = ctx->mem[s - mem_min + 1].hh.rh;
                  ctx->l_hyf = ctx->mem[s - mem_min + 1].hh.U2.b0;
                  ctx->r_hyf = ctx->mem[s - mem_min + 1].hh.U2.b1;
                }
                goto _L22;
              } else {
                goto _L31;
              }
              if (ctx->eqtb[c + 11139].hh.rh) {
                if ((ctx->eqtb[c + 11139].hh.rh == c) ||
                    (ctx->eqtb[12201].int_ > 0))
                  goto _L32;
                else
                  goto _L31;
              }
            _L22:
              prev_s = s;
              s = ctx->mem[prev_s - mem_min].hh.rh;
            }
          _L32:
            ctx->hyf_char = ctx->fnt_infos.hyphen_char[ctx->hf];
            if (ctx->hyf_char < 0)
              goto _L31;
            if (ctx->hyf_char > 255)
              goto _L31;
            ctx->ha = prev_s;
            if (ctx->l_hyf + ctx->r_hyf > 63)
              goto _L31;
            ctx->hn = 0;
            while (true) {
              if (s >= ctx->hi_mem_min) {
                if (ctx->mem[s - mem_min].hh.U2.b0 != ctx->hf)
                  goto _L33;
                ctx->hyf_bchar = ctx->mem[s - mem_min].hh.U2.b1;
                c = ctx->hyf_bchar;
                if (!ctx->eqtb[c + 11139].hh.rh)
                  goto _L33;
                if (ctx->hn == 63)
                  goto _L33;
                ctx->hb = s;
                ++ctx->hn;
                ctx->hu[ctx->hn] = c;
                ctx->hc[ctx->hn] = ctx->eqtb[c + 11139].hh.rh;
                ctx->hyf_bchar = 256;
              } else if (ctx->mem[s - mem_min].hh.U2.b0 == 6) {
                if (ctx->mem[s - mem_min + 1].hh.U2.b0 != ctx->hf)
                  goto _L33;
                j = ctx->hn;
                q = ctx->mem[s - mem_min + 1].hh.rh;
                if (q > (-1073741824))
                  ctx->hyf_bchar = ctx->mem[q - mem_min].hh.U2.b1;
                while (q > (-1073741824)) {
                  c = ctx->mem[q - mem_min].hh.U2.b1;
                  if (!ctx->eqtb[c + 11139].hh.rh)
                    goto _L33;
                  if (j == 63)
                    goto _L33;
                  ++j;
                  ctx->hu[j] = c;
                  ctx->hc[j] = ctx->eqtb[c + 11139].hh.rh;
                  q = ctx->mem[q - mem_min].hh.rh;
                }
                ctx->hb = s;
                ctx->hn = j;
                if (ctx->mem[s - mem_min].hh.U2.b1 & 1)
                  ctx->hyf_bchar = ctx->fnt_infos.font_bchar[ctx->hf];
                else
                  ctx->hyf_bchar = 256;
              } else if ((ctx->mem[s - mem_min].hh.U2.b0 == 11) &&
                         (!ctx->mem[s - mem_min].hh.U2.b1)) {
                ctx->hb = s;
                ctx->hyf_bchar = ctx->fnt_infos.font_bchar[ctx->hf];
              } else {
                goto _L33;
              }
              s = ctx->mem[s - mem_min].hh.rh;
            }
          _L33:
            if (ctx->hn < (ctx->l_hyf + ctx->r_hyf))
              goto _L31;
            while (true) {
              if (s < ctx->hi_mem_min) {
                switch (ctx->mem[s - mem_min].hh.U2.b0) {
                case 6:
                  // blank case
                  break;
                case 11:
                  if (ctx->mem[s - mem_min].hh.U2.b1)
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
              s = ctx->mem[s - mem_min].hh.rh;
            }
          _L34:
            hyphenate(ctx);
          }
        _L31:;
        }
        break;
      case 11:
        if (ctx->mem[ctx->cur_p - mem_min].hh.U2.b1 == 1) {
          if ((ctx->mem[ctx->cur_p - mem_min].hh.rh < ctx->hi_mem_min) &&
              auto_breaking) {
            if (ctx->mem[ctx->mem[ctx->cur_p - mem_min].hh.rh - mem_min]
                    .hh.U2.b0 == 10)
              try_break(ctx, 0, 0);
          }
          ctx->active_width[1] += ctx->mem[ctx->cur_p - mem_min + 1].int_;
        } else {
          ctx->active_width[1] += ctx->mem[ctx->cur_p - mem_min + 1].int_;
        }
        break;
      case 6:
        f = ctx->mem[ctx->cur_p - mem_min + 1].hh.U2.b0;
        (ctx->active_width[1] +=
         (ctx
              ->font_info[(
                  ctx->fnt_infos.width_base[f] +
                  ((ctx->font_info[ctx->fnt_infos.char_base[f] +
                                   ctx->mem[ctx->cur_p - mem_min + 1].hh.U2.b1]
                        .qqqq)
                       .b0))]
              .int_));
        break;
      case 7:
        s = ctx->mem[ctx->cur_p - mem_min + 1].hh.lh;
        ctx->disc_width = 0;
        if (s == (-1073741824)) {
          try_break(ctx, ctx->eqtb[12167].int_, 1);
        } else {
          do {
            if (s >= ctx->hi_mem_min) {
              f = ctx->mem[s - mem_min].hh.U2.b0;
              (ctx->disc_width +=
               (ctx->font_info[(ctx->fnt_infos.width_base[f] +
                                (ctx->font_info[ctx->fnt_infos.char_base[f] +
                                                ctx->mem[s - mem_min].hh.U2.b1]
                                     .qqqq.b0))]
                    .int_));
            } else {
              switch (ctx->mem[s - mem_min].hh.U2.b0) {
              case 6:
                f = ctx->mem[s - mem_min + 1].hh.U2.b0;
                (ctx->disc_width +=
                 (ctx->font_info
                      [(ctx->fnt_infos.width_base[f] +
                        ((ctx->font_info[(ctx->fnt_infos.char_base[f] +
                                          (ctx->mem[s - mem_min + 1].hh.U2.b1))]
                              .qqqq)
                             .b0))]
                          .int_));
                break;
              case 0:
              case 1:
              case 2:
              case 11:
                ctx->disc_width += ctx->mem[s - mem_min + 1].int_;
                break;
              default:
                confusion(ctx, 936);
                break;
              }
            }
            s = ctx->mem[s - mem_min].hh.rh;
          } while (s != (-1073741824));
          ctx->active_width[1] += ctx->disc_width;
          try_break(ctx, ctx->eqtb[12166].int_, 1);
          ctx->active_width[1] -= ctx->disc_width;
        }
        r = ctx->mem[ctx->cur_p - mem_min].hh.U2.b1;
        s = ctx->mem[ctx->cur_p - mem_min].hh.rh;
        while (r > 0) {
          if (s >= ctx->hi_mem_min) {
            f = ctx->mem[s - mem_min].hh.U2.b0;
            (ctx->active_width[1] +=
             (ctx->font_info[(ctx->fnt_infos.width_base[f] +
                              ((ctx->font_info[ctx->fnt_infos.char_base[f] +
                                               ctx->mem[s - mem_min].hh.U2.b1]
                                    .qqqq)
                                   .b0))]
                  .int_));
          } else {
            switch (ctx->mem[s - mem_min].hh.U2.b0) {
            case 6:
              f = ctx->mem[s - mem_min + 1].hh.U2.b0;
              (ctx->active_width[1] +=
               (ctx
                    ->font_info[(
                        ctx->fnt_infos.width_base[f] +
                        ((ctx->font_info[(ctx->fnt_infos.char_base[f] +
                                          (ctx->mem[s - mem_min + 1].hh.U2.b1))]
                              .qqqq)
                             .b0))]
                    .int_));
              break;
            case 0:
            case 1:
            case 2:
            case 11:
              ctx->active_width[1] += ctx->mem[s - mem_min + 1].int_;
              break;
            default:
              confusion(ctx, 937);
              break;
            }
          }
          --r;
          s = ctx->mem[s - mem_min].hh.rh;
        }
        prev_p = ctx->cur_p;
        ctx->cur_p = s;
        goto _L35;
        break;
      case 9:
        auto_breaking = (ctx->mem[ctx->cur_p - mem_min].hh.U2.b1 == 1);
        if ((ctx->mem[ctx->cur_p - mem_min].hh.rh < ctx->hi_mem_min) &&
            auto_breaking) {
          if (ctx->mem[ctx->mem[ctx->cur_p - mem_min].hh.rh - mem_min]
                  .hh.U2.b0 == 10)
            try_break(ctx, 0, 0);
        }
        ctx->active_width[1] += ctx->mem[ctx->cur_p - mem_min + 1].int_;
        break;
      case 12:
        try_break(ctx, ctx->mem[ctx->cur_p - mem_min + 1].int_, 0);
        break;
      case 4:
      case 3:
      case 5:
        // blank case
        break;
      default:
        confusion(ctx, 935);
        break;
      }
      prev_p = ctx->cur_p;
      ctx->cur_p = ctx->mem[ctx->cur_p - mem_min].hh.rh;
    _L35:;
    }
    if (ctx->cur_p == (-1073741824)) {
      try_break(ctx, -10000, 1);
      if (ctx->mem[mem_max - mem_min - 7].hh.rh != (mem_max - 7)) {
        r = ctx->mem[mem_max - mem_min - 7].hh.rh;
        ctx->fewest_demerits = 1073741823;
        do {
          if (ctx->mem[r - mem_min].hh.U2.b0 != 2) {
            if (ctx->mem[r - mem_min + 2].int_ < ctx->fewest_demerits) {
              ctx->fewest_demerits = ctx->mem[r - mem_min + 2].int_;
              ctx->best_bet = r;
            }
          }
          r = ctx->mem[r - mem_min].hh.rh;
        } while (r != (mem_max - 7));
        ctx->best_line = ctx->mem[ctx->best_bet - mem_min + 1].hh.lh;
        if (!ctx->eqtb[12182].int_)
          goto _L30;
        r = ctx->mem[mem_max - mem_min - 7].hh.rh;
        ctx->actual_looseness = 0;
        do {
          if (ctx->mem[r - mem_min].hh.U2.b0 != 2) {
            ctx->line_diff = ctx->mem[r - mem_min + 1].hh.lh - ctx->best_line;
            if (((ctx->line_diff < ctx->actual_looseness) &&
                 (ctx->eqtb[12182].int_ <= ctx->line_diff)) ||
                ((ctx->line_diff > ctx->actual_looseness) &&
                 (ctx->eqtb[12182].int_ >= ctx->line_diff))) {
              ctx->best_bet = r;
              ctx->actual_looseness = ctx->line_diff;
              ctx->fewest_demerits = ctx->mem[r - mem_min + 2].int_;
            } else if ((ctx->line_diff == ctx->actual_looseness) &&
                       (ctx->mem[r - mem_min + 2].int_ <
                        ctx->fewest_demerits)) {
              ctx->best_bet = r;
              ctx->fewest_demerits = ctx->mem[r - mem_min + 2].int_;
            }
          }
          r = ctx->mem[r - mem_min].hh.rh;
        } while (r != (mem_max - 7));
        ctx->best_line = ctx->mem[ctx->best_bet - mem_min + 1].hh.lh;
        if ((ctx->actual_looseness == ctx->eqtb[12182].int_) || ctx->final_pass)
          goto _L30;
      }
    }
    q = ctx->mem[mem_max - mem_min - 7].hh.rh;
    while (q != (mem_max - 7)) {
      ctx->cur_p = ctx->mem[q - mem_min].hh.rh;
      if (ctx->mem[q - mem_min].hh.U2.b0 == 2)
        free_node(ctx, q, 7);
      else
        free_node(ctx, q, 3);
      q = ctx->cur_p;
    }
    q = ctx->passive;
    while (q != (-1073741824)) {
      ctx->cur_p = ctx->mem[q - mem_min].hh.rh;
      free_node(ctx, q, 2);
      q = ctx->cur_p;
    }
    if (!ctx->second_pass) {
      ctx->threshold = ctx->eqtb[12164].int_;
      ctx->second_pass = true;
      ctx->final_pass = (ctx->eqtb[12750].int_ <= 0);
    } else {
      ctx->background[2] += ctx->eqtb[12750].int_;
      ctx->final_pass = true;
    }
  }
_L30:
  post_line_break(ctx, final_widow_penalty);
  q = ctx->mem[mem_max - mem_min - 7].hh.rh;
  while (q != (mem_max - 7)) {
    ctx->cur_p = ctx->mem[q - mem_min].hh.rh;
    if (ctx->mem[q - mem_min].hh.U2.b0 == 2)
      free_node(ctx, q, 7);
    else
      free_node(ctx, q, 3);
    q = ctx->cur_p;
  }
  q = ctx->passive;
  while (q != (-1073741824)) {
    ctx->cur_p = ctx->mem[q - mem_min].hh.rh;
    free_node(ctx, q, 2);
    q = ctx->cur_p;
  }
  ctx->pack_begin_line = 0;
}

void new_hyph_exceptions(ctex_t *ctx) {
  char n = 0, j;
  hyph_pointer h;
  str_number k;
  halfword p = -1073741824, q;
  str_number s, t;
  pool_pointer u, v;
  scan_left_brace(ctx);
  if (ctx->eqtb[12213].int_ <= 0) {
    ctx->cur_lang = 0;
  } else if (ctx->eqtb[12213].int_ > 255)
    ctx->cur_lang = 0;
  else
    ctx->cur_lang = ctx->eqtb[12213].int_;
  while (true) {
    get_x_token(ctx);
  _L21:
    switch (ctx->cur_cmd) {
    case 11:
    case 12:
    case 68:
      if (ctx->cur_chr == 45) {
        if (n < 63) {
          q = get_avail(ctx);
          ctx->mem[q - mem_min].hh.rh = p;
          ctx->mem[q - mem_min].hh.lh = n;
          p = q;
        }
      } else if (!ctx->eqtb[ctx->cur_chr + 11139].hh.rh) {
        print_nl(ctx, 262);
        print(ctx, 944);
        ctx->help_ptr = 2;
        ctx->help_line[1] = 945;
        ctx->help_line[0] = 946;
        error(ctx);
      } else if (n < 63) {
        ++n;
        ctx->hc[n] = ctx->eqtb[ctx->cur_chr + 11139].hh.rh;
      }
      break;
    case 16:
      scan_char_num(ctx);
      ctx->cur_chr = ctx->cur_val;
      ctx->cur_cmd = 68;
      goto _L21;
      break;
    case 10:
    case 2:
      if (n > 1) {
        ++n;
        ctx->hc[n] = ctx->cur_lang;
        if (ctx->pool_ptr + n > pool_size)
          overflow(ctx, 257, pool_size - ctx->init_pool_ptr);
        h = 0;
        for (j = 1; j <= n; ++j) {
          h = (h + h + ctx->hc[j]) % 307;
          ctx->str_pool[ctx->pool_ptr] = ctx->hc[j];
          ++ctx->pool_ptr;
        }
        s = make_string(ctx);
        if (ctx->hyph_count == 307)
          overflow(ctx, 947, 307);
        ++ctx->hyph_count;
        while (ctx->hyph_word[h]) {
          k = ctx->hyph_word[h];
          if (ctx->str_start[k + 1] - ctx->str_start[k] <
              ctx->str_start[s + 1] - ctx->str_start[s])
            goto _L40;
          if (ctx->str_start[k + 1] - ctx->str_start[k] >
              ctx->str_start[s + 1] - ctx->str_start[s])
            goto _L45;
          u = ctx->str_start[k];
          v = ctx->str_start[s];
          do {
            if (ctx->str_pool[u] < ctx->str_pool[v])
              goto _L40;
            if (ctx->str_pool[u] > ctx->str_pool[v])
              goto _L45;
            ++u;
            ++v;
          } while (u != ctx->str_start[k + 1]);
        _L40:
          q = ctx->hyph_list[h];
          ctx->hyph_list[h] = p;
          p = q;
          t = ctx->hyph_word[h];
          ctx->hyph_word[h] = s;
          s = t;
        _L45:
          if (h > 0)
            --h;
          else
            h = 307;
        }
        ctx->hyph_word[h] = s;
        ctx->hyph_list[h] = p;
      }
      if (ctx->cur_cmd == 2)
        goto _L10;
      n = 0;
      p = -1073741824;
      break;
    default:
      print_nl(ctx, 262);
      print(ctx, 680);
      print_esc(ctx, 940);
      print(ctx, 941);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 942;
      ctx->help_line[0] = 943;
      error(ctx);
      break;
    }
  }
_L10:;
}

halfword prune_page_top(ctex_t *ctx, halfword p) {
  halfword prev_p = mem_max - 3, q;
  ctx->mem[mem_max - mem_min - 3].hh.rh = p;
  while (p != (-1073741824)) {
    switch (ctx->mem[p - mem_min].hh.U2.b0) {
    case 0:
    case 1:
    case 2:
      q = new_skip_param(ctx, 10);
      ctx->mem[prev_p - mem_min].hh.rh = q;
      ctx->mem[q - mem_min].hh.rh = p;
      if (ctx->mem[ctx->temp_ptr - mem_min + 1].int_ >
          ctx->mem[p - mem_min + 3].int_)
        ctx->mem[ctx->temp_ptr - mem_min + 1].int_ -=
            ctx->mem[p - mem_min + 3].int_;
      else
        ctx->mem[ctx->temp_ptr - mem_min + 1].int_ = 0;
      p = -1073741824;
      break;
    case 8:
    case 4:
    case 3:
      prev_p = p;
      p = ctx->mem[prev_p - mem_min].hh.rh;
      break;
    case 10:
    case 11:
    case 12:
      q = p;
      p = ctx->mem[q - mem_min].hh.rh;
      ctx->mem[q - mem_min].hh.rh = -1073741824;
      ctx->mem[prev_p - mem_min].hh.rh = p;
      flush_node_list(ctx, q);
      break;
    default:
      confusion(ctx, 958);
      break;
    }
  }
  return ctx->mem[mem_max - mem_min - 3].hh.rh;
}

halfword vert_break(ctex_t *ctx, halfword p, scaled h, scaled d) {
  halfword prev_p = p, q, r, best_place;
  integer pi, b, least_cost = 1073741823;
  scaled prev_dp = 0;
  small_number t;
  ctx->active_width[1] = 0;
  ctx->active_width[2] = 0;
  ctx->active_width[3] = 0;
  ctx->active_width[4] = 0;
  ctx->active_width[5] = 0;
  ctx->active_width[6] = 0;
  while (true) {
    if (p == (-1073741824)) {
      pi = -10000;
    } else {
      switch (ctx->mem[p - mem_min].hh.U2.b0) {
      case 0:
      case 1:
      case 2:
        ctx->active_width[1] += prev_dp + ctx->mem[p - mem_min + 3].int_;
        prev_dp = ctx->mem[p - mem_min + 2].int_;
        goto _L45;
        break;
      case 8:
        goto _L45;
        break;
      case 10:
        if (ctx->mem[prev_p - mem_min].hh.U2.b0 >= 9)
          goto _L90;
        pi = 0;
        break;
      case 11:
        if (ctx->mem[p - mem_min].hh.rh == (-1073741824))
          t = 12;
        else
          t = ctx->mem[ctx->mem[p - mem_min].hh.rh - mem_min].hh.U2.b0;
        if (t != 10)
          goto _L90;
        pi = 0;
        break;
      case 12:
        pi = ctx->mem[p - mem_min + 1].int_;
        break;
      case 4:
      case 3:
        goto _L45;
        break;
      default:
        confusion(ctx, 959);
        break;
      }
    }
    if (pi < 10000) {
      if (ctx->active_width[1] < h) {
        if (ctx->active_width[3] || ctx->active_width[4] ||
            ctx->active_width[5])
          b = 0;
        else
          b = badness(ctx, h - ctx->active_width[1], ctx->active_width[2]);
      } else if (ctx->active_width[1] - h > ctx->active_width[6])
        b = 1073741823;
      else
        b = badness(ctx, ctx->active_width[1] - h, ctx->active_width[6]);
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
        ctx->best_height_plus_depth = ctx->active_width[1] + prev_dp;
      }
      if ((b == 1073741823) || (pi <= (-10000)))
        goto _L30;
    }
    if ((ctx->mem[p - mem_min].hh.U2.b0 < 10) ||
        (ctx->mem[p - mem_min].hh.U2.b0 > 11))
      goto _L45;
  _L90:
    if (ctx->mem[p - mem_min].hh.U2.b0 == 11) {
      q = p;
    } else {
      q = ctx->mem[p - mem_min + 1].hh.lh;
      ctx->active_width[ctx->mem[q - mem_min].hh.U2.b0 + 2] +=
          ctx->mem[q - mem_min + 2].int_;
      ctx->active_width[6] += ctx->mem[q - mem_min + 3].int_;
      if (ctx->mem[q - mem_min].hh.U2.b1 && ctx->mem[q - mem_min + 3].int_) {
        print_nl(ctx, 262);
        print(ctx, 960);
        ctx->help_ptr = 4;
        ctx->help_line[3] = 961;
        ctx->help_line[2] = 962;
        ctx->help_line[1] = 963;
        ctx->help_line[0] = 921;
        error(ctx);
        r = new_spec(ctx, q);
        ctx->mem[r - mem_min].hh.U2.b1 = 0;
        delete_glue_ref(ctx, q);
        ctx->mem[p - mem_min + 1].hh.lh = r;
        q = r;
      }
    }
    ctx->active_width[1] += prev_dp + ctx->mem[q - mem_min + 1].int_;
    prev_dp = 0;
  _L45:
    if (prev_dp > d) {
      ctx->active_width[1] += prev_dp - d;
      prev_dp = d;
    }
    prev_p = p;
    p = ctx->mem[prev_p - mem_min].hh.rh;
  }
_L30:
  return best_place;
}

halfword vsplit(ctex_t *ctx, uint8_t n, scaled h) {
  halfword result, p, q;
  halfword v = ctx->eqtb[n + 10578].hh.rh;
  if (ctx->cur_mark[3] != (-1073741824)) {
    delete_token_ref(ctx, ctx->cur_mark[3]);
    ctx->cur_mark[3] = -1073741824;
    delete_token_ref(ctx, ctx->cur_mark[4]);
    ctx->cur_mark[4] = -1073741824;
  }
  if (v == (-1073741824)) {
    result = -1073741824;
    goto _L10;
  }
  if (ctx->mem[v - mem_min].hh.U2.b0 != 1) {
    print_nl(ctx, 262);
    print(ctx, 338);
    print_esc(ctx, 964);
    print(ctx, 965);
    print_esc(ctx, 966);
    ctx->help_ptr = 2;
    ctx->help_line[1] = 967;
    ctx->help_line[0] = 968;
    error(ctx);
    result = -1073741824;
    goto _L10;
  }
  q = vert_break(ctx, ctx->mem[v - mem_min + 5].hh.rh, h,
                 ctx->eqtb[12736].int_);
  p = ctx->mem[v - mem_min + 5].hh.rh;
  if (p == q) {
    ctx->mem[v - mem_min + 5].hh.rh = -1073741824;
  } else {
    while (true) {
      if (ctx->mem[p - mem_min].hh.U2.b0 == 4) {
        if (ctx->cur_mark[3] == (-1073741824)) {
          ctx->cur_mark[3] = ctx->mem[p - mem_min + 1].int_;
          ctx->cur_mark[4] = ctx->cur_mark[3];
          ctx->mem[ctx->cur_mark[3] - mem_min].hh.lh += 2;
        } else {
          delete_token_ref(ctx, ctx->cur_mark[4]);
          ctx->cur_mark[4] = ctx->mem[p - mem_min + 1].int_;
          ++ctx->mem[ctx->cur_mark[4] - mem_min].hh.lh;
        }
      }
      if (ctx->mem[p - mem_min].hh.rh == q) {
        ctx->mem[p - mem_min].hh.rh = -1073741824;
        goto _L30;
      }
      p = ctx->mem[p - mem_min].hh.rh;
    }
  }
_L30:
  q = prune_page_top(ctx, q);
  p = ctx->mem[v - mem_min + 5].hh.rh;
  free_node(ctx, v, 7);
  if (q == (-1073741824))
    ctx->eqtb[n + 10578].hh.rh = -1073741824;
  else
    ctx->eqtb[n + 10578].hh.rh = vpackage(ctx, q, 0, 1, 1073741823);
  result = vpackage(ctx, p, h, 0, ctx->eqtb[12736].int_);
_L10:
  return result;
}

void print_totals(ctex_t *ctx) {
  print_scaled(ctx, ctx->page_so_far[1]);
  if (ctx->page_so_far[2]) {
    print(ctx, 312);
    print_scaled(ctx, ctx->page_so_far[2]);
    print(ctx, 338);
  }
  if (ctx->page_so_far[3]) {
    print(ctx, 312);
    print_scaled(ctx, ctx->page_so_far[3]);
    print(ctx, 311);
  }
  if (ctx->page_so_far[4]) {
    print(ctx, 312);
    print_scaled(ctx, ctx->page_so_far[4]);
    print(ctx, 977);
  }
  if (ctx->page_so_far[5]) {
    print(ctx, 312);
    print_scaled(ctx, ctx->page_so_far[5]);
    print(ctx, 978);
  }
  if (ctx->page_so_far[6]) {
    print(ctx, 313);
    print_scaled(ctx, ctx->page_so_far[6]);
  }
}

void freeze_page_specs(ctex_t *ctx, small_number s) {
  ctx->page_contents = s;
  ctx->page_so_far[0] = ctx->eqtb[12734].int_;
  ctx->page_max_depth = ctx->eqtb[12735].int_;
  ctx->page_so_far[7] = 0;
  ctx->page_so_far[1] = 0;
  ctx->page_so_far[2] = 0;
  ctx->page_so_far[3] = 0;
  ctx->page_so_far[4] = 0;
  ctx->page_so_far[5] = 0;
  ctx->page_so_far[6] = 0;
  ctx->least_page_cost = 1073741823;
}

void box_error(ctex_t *ctx, uint8_t n) {
  error(ctx);
  begin_diagnostic(ctx);
  print_nl(ctx, 835);
  show_box(ctx, ctx->eqtb[n + 10578].hh.rh);
  end_diagnostic(ctx, true);
  flush_node_list(ctx, ctx->eqtb[n + 10578].hh.rh);
  ctx->eqtb[n + 10578].hh.rh = -1073741824;
}

void ensure_vbox(ctex_t *ctx, uint8_t n) {
  halfword p = ctx->eqtb[n + 10578].hh.rh;
  if (p == (-1073741824))
    return;
  if (ctx->mem[p - mem_min].hh.U2.b0)
    return;
  print_nl(ctx, 262);
  print(ctx, 988);
  ctx->help_ptr = 3;
  ctx->help_line[2] = 989;
  ctx->help_line[1] = 990;
  ctx->help_line[0] = 991;
  box_error(ctx, n);
}

void fire_up(ctex_t *ctx, halfword c) {
  halfword p, q = mem_max - 4, r, s, prev_p = mem_max - 2;
  uint8_t n;
  bool_t wait;
  integer save_vbadness;
  scaled save_vfuzz;
  halfword save_split_top_skip;
  if (ctx->mem[ctx->best_page_break - mem_min].hh.U2.b0 == 12) {
    geq_word_define(ctx, 12202,
                    ctx->mem[ctx->best_page_break - mem_min + 1].int_);
    ctx->mem[ctx->best_page_break - mem_min + 1].int_ = 10000;
  } else {
    geq_word_define(ctx, 12202, 10000);
  }
  if (ctx->cur_mark[2] != (-1073741824)) {
    if (ctx->cur_mark[0] != (-1073741824))
      delete_token_ref(ctx, ctx->cur_mark[0]);
    ctx->cur_mark[0] = ctx->cur_mark[2];
    ++ctx->mem[ctx->cur_mark[0] - mem_min].hh.lh;
    delete_token_ref(ctx, ctx->cur_mark[1]);
    ctx->cur_mark[1] = -1073741824;
  }
  if (c == ctx->best_page_break)
    ctx->best_page_break = -1073741824;
  if (ctx->eqtb[10833].hh.rh != (-1073741824)) {
    print_nl(ctx, 262);
    print(ctx, 338);
    print_esc(ctx, 409);
    print(ctx, 1002);
    ctx->help_ptr = 2;
    ctx->help_line[1] = 1003;
    ctx->help_line[0] = 991;
    box_error(ctx, 255);
  }
  ctx->insert_penalties = 0;
  save_split_top_skip = ctx->eqtb[9792].hh.rh;
  if (ctx->eqtb[12216].int_ <= 0) {
    r = ctx->mem[mem_max - mem_min].hh.rh;
    while (r != mem_max) {
      if (ctx->mem[r - mem_min + 2].hh.lh != (-1073741824)) {
        n = ctx->mem[r - mem_min].hh.U2.b1;
        ensure_vbox(ctx, n);
        if (ctx->eqtb[n + 10578].hh.rh == (-1073741824))
          ctx->eqtb[n + 10578].hh.rh = new_null_box(ctx);
        p = ctx->eqtb[n + 10578].hh.rh + 5;
        while (ctx->mem[p - mem_min].hh.rh != (-1073741824))
          p = ctx->mem[p - mem_min].hh.rh;
        ctx->mem[r - mem_min + 2].hh.rh = p;
      }
      r = ctx->mem[r - mem_min].hh.rh;
    }
  }
  ctx->mem[q - mem_min].hh.rh = -1073741824;
  p = ctx->mem[prev_p - mem_min].hh.rh;
  while (p != ctx->best_page_break) {
    if (ctx->mem[p - mem_min].hh.U2.b0 == 3) {
      if (ctx->eqtb[12216].int_ <= 0) {
        r = ctx->mem[mem_max - mem_min].hh.rh;
        while (ctx->mem[r - mem_min].hh.U2.b1 != ctx->mem[p - mem_min].hh.U2.b1)
          r = ctx->mem[r - mem_min].hh.rh;
        if (ctx->mem[r - mem_min + 2].hh.lh == (-1073741824)) {
          wait = true;
        } else {
          wait = false;
          s = ctx->mem[r - mem_min + 2].hh.rh;
          ctx->mem[s - mem_min].hh.rh = ctx->mem[p - mem_min + 4].hh.lh;
          if (ctx->mem[r - mem_min + 2].hh.lh == p) {
            if (ctx->mem[r - mem_min].hh.U2.b0 == 1) {
              if ((ctx->mem[r - mem_min + 1].hh.lh == p) &&
                  (ctx->mem[r - mem_min + 1].hh.rh != (-1073741824))) {
                while (ctx->mem[s - mem_min].hh.rh !=
                       ctx->mem[r - mem_min + 1].hh.rh)
                  s = ctx->mem[s - mem_min].hh.rh;
                ctx->mem[s - mem_min].hh.rh = -1073741824;
                ctx->eqtb[9792].hh.rh = ctx->mem[p - mem_min + 4].hh.rh;
                ctx->mem[p - mem_min + 4].hh.lh =
                    prune_page_top(ctx, ctx->mem[r - mem_min + 1].hh.rh);
                if (ctx->mem[p - mem_min + 4].hh.lh != (-1073741824)) {
                  ctx->temp_ptr = vpackage(ctx, ctx->mem[p - mem_min + 4].hh.lh,
                                           0, 1, 1073741823);
                  (ctx->mem[p - mem_min + 3].int_ =
                       (ctx->mem[ctx->temp_ptr - mem_min + 3].int_ +
                        (ctx->mem[ctx->temp_ptr - mem_min + 2].int_)));
                  free_node(ctx, ctx->temp_ptr, 7);
                  wait = true;
                }
              }
            }
            ctx->mem[r - mem_min + 2].hh.lh = -1073741824;
            n = ctx->mem[r - mem_min].hh.U2.b1;
            ctx->temp_ptr =
                ctx->mem[ctx->eqtb[n + 10578].hh.rh - mem_min + 5].hh.rh;
            free_node(ctx, ctx->eqtb[n + 10578].hh.rh, 7);
            ctx->eqtb[n + 10578].hh.rh =
                vpackage(ctx, ctx->temp_ptr, 0, 1, 1073741823);
          } else {
            while (ctx->mem[s - mem_min].hh.rh != (-1073741824))
              s = ctx->mem[s - mem_min].hh.rh;
            ctx->mem[r - mem_min + 2].hh.rh = s;
          }
        }
        ctx->mem[prev_p - mem_min].hh.rh = ctx->mem[p - mem_min].hh.rh;
        ctx->mem[p - mem_min].hh.rh = -1073741824;
        if (wait) {
          ctx->mem[q - mem_min].hh.rh = p;
          q = p;
          ++ctx->insert_penalties;
        } else {
          delete_glue_ref(ctx, ctx->mem[p - mem_min + 4].hh.rh);
          free_node(ctx, p, 5);
        }
        p = prev_p;
      }
    } else if (ctx->mem[p - mem_min].hh.U2.b0 == 4) {
      if (ctx->cur_mark[1] == (-1073741824)) {
        ctx->cur_mark[1] = ctx->mem[p - mem_min + 1].int_;
        ++ctx->mem[ctx->cur_mark[1] - mem_min].hh.lh;
      }
      if (ctx->cur_mark[2] != (-1073741824))
        delete_token_ref(ctx, ctx->cur_mark[2]);
      ctx->cur_mark[2] = ctx->mem[p - mem_min + 1].int_;
      ++ctx->mem[ctx->cur_mark[2] - mem_min].hh.lh;
    }
    prev_p = p;
    p = ctx->mem[prev_p - mem_min].hh.rh;
  }
  ctx->eqtb[9792].hh.rh = save_split_top_skip;
  if (p != (-1073741824)) {
    if (ctx->mem[mem_max - mem_min - 1].hh.rh == (-1073741824)) {
      if (!ctx->nest_ptr)
        ctx->cur_list.tail_field = ctx->page_tail;
      else
        ctx->nest[0].tail_field = ctx->page_tail;
    }
    ctx->mem[ctx->page_tail - mem_min].hh.rh =
        ctx->mem[mem_max - mem_min - 1].hh.rh;
    ctx->mem[mem_max - mem_min - 1].hh.rh = p;
    ctx->mem[prev_p - mem_min].hh.rh = -1073741824;
  }
  save_vbadness = ctx->eqtb[12190].int_;
  ctx->eqtb[12190].int_ = 10000;
  save_vfuzz = ctx->eqtb[12739].int_;
  ctx->eqtb[12739].int_ = 1073741823;
  ctx->eqtb[10833].hh.rh = vpackage(ctx, ctx->mem[mem_max - mem_min - 2].hh.rh,
                                    ctx->best_size, 0, ctx->page_max_depth);
  ctx->eqtb[12190].int_ = save_vbadness;
  ctx->eqtb[12739].int_ = save_vfuzz;
  if (ctx->last_glue != 1073741824)
    delete_glue_ref(ctx, ctx->last_glue);
  ctx->page_contents = 0;
  ctx->page_tail = mem_max - 2;
  ctx->mem[mem_max - mem_min - 2].hh.rh = -1073741824;
  ctx->last_glue = 1073741824;
  ctx->last_penalty = 0;
  ctx->last_kern = 0;
  ctx->page_so_far[7] = 0;
  ctx->page_max_depth = 0;
  if (q != (mem_max - 4)) {
    ctx->mem[mem_max - mem_min - 2].hh.rh =
        ctx->mem[mem_max - mem_min - 4].hh.rh;
    ctx->page_tail = q;
  }
  r = ctx->mem[mem_max - mem_min].hh.rh;
  while (r != mem_max) {
    q = ctx->mem[r - mem_min].hh.rh;
    free_node(ctx, r, 4);
    r = q;
  }
  ctx->mem[mem_max - mem_min].hh.rh = mem_max;
  if ((ctx->cur_mark[0] != (-1073741824)) &&
      (ctx->cur_mark[1] == (-1073741824))) {
    ctx->cur_mark[1] = ctx->cur_mark[0];
    ++ctx->mem[ctx->cur_mark[0] - mem_min].hh.lh;
  }
  if (ctx->eqtb[10313].hh.rh != (-1073741824)) {
    if (ctx->dead_cycles < ctx->eqtb[12203].int_) {
      ctx->output_active = true;
      ++ctx->dead_cycles;
      push_nest(ctx);
      ctx->cur_list.mode_field = -1;
      ctx->cur_list.aux_field.int_ = -65536000;
      ctx->cur_list.ml_field = -ctx->line;
      begin_token_list(ctx, ctx->eqtb[10313].hh.rh, 6);
      new_save_level(ctx, 8);
      normal_paragraph(ctx);
      scan_left_brace(ctx);
      goto _L10;
    }
    print_nl(ctx, 262);
    print(ctx, 1004);
    print_int(ctx, ctx->dead_cycles);
    print(ctx, 1005);
    ctx->help_ptr = 3;
    ctx->help_line[2] = 1006;
    ctx->help_line[1] = 1007;
    ctx->help_line[0] = 1008;
    error(ctx);
  }
  if (ctx->mem[mem_max - mem_min - 2].hh.rh != (-1073741824)) {
    if (ctx->mem[mem_max - mem_min - 1].hh.rh == (-1073741824)) {
      if (!ctx->nest_ptr)
        ctx->cur_list.tail_field = ctx->page_tail;
      else
        ctx->nest[0].tail_field = ctx->page_tail;
    } else {
      ctx->mem[ctx->page_tail - mem_min].hh.rh =
          ctx->mem[mem_max - mem_min - 1].hh.rh;
    }
    ctx->mem[mem_max - mem_min - 1].hh.rh =
        ctx->mem[mem_max - mem_min - 2].hh.rh;
    ctx->mem[mem_max - mem_min - 2].hh.rh = -1073741824;
    ctx->page_tail = mem_max - 2;
  }
  ship_out(ctx, ctx->eqtb[10833].hh.rh);
  ctx->eqtb[10833].hh.rh = -1073741824;
_L10:;
}

void build_page(ctex_t *ctx) {
  halfword p, q, r;
  integer b, c, pi;
  uint8_t n;
  scaled delta, h, w;
  if ((ctx->mem[mem_max - mem_min - 1].hh.rh == (-1073741824)) ||
      ctx->output_active)
    goto _L10;
  do {
  _L22:
    p = ctx->mem[mem_max - mem_min - 1].hh.rh;
    if (ctx->last_glue != 1073741824)
      delete_glue_ref(ctx, ctx->last_glue);
    ctx->last_penalty = 0;
    ctx->last_kern = 0;
    if (ctx->mem[p - mem_min].hh.U2.b0 == 10) {
      ctx->last_glue = ctx->mem[p - mem_min + 1].hh.lh;
      ++ctx->mem[ctx->last_glue - mem_min].hh.rh;
    } else {
      ctx->last_glue = 1073741824;
      if (ctx->mem[p - mem_min].hh.U2.b0 == 12) {
        ctx->last_penalty = ctx->mem[p - mem_min + 1].int_;
      } else if (ctx->mem[p - mem_min].hh.U2.b0 == 11)
        ctx->last_kern = ctx->mem[p - mem_min + 1].int_;
    }
    switch (ctx->mem[p - mem_min].hh.U2.b0) {
    case 0:
    case 1:
    case 2:
      if (ctx->page_contents < 2) {
        if (!ctx->page_contents)
          freeze_page_specs(ctx, 2);
        else
          ctx->page_contents = 2;
        q = new_skip_param(ctx, 9);
        if (ctx->mem[ctx->temp_ptr - mem_min + 1].int_ >
            ctx->mem[p - mem_min + 3].int_)
          ctx->mem[ctx->temp_ptr - mem_min + 1].int_ -=
              ctx->mem[p - mem_min + 3].int_;
        else
          ctx->mem[ctx->temp_ptr - mem_min + 1].int_ = 0;
        ctx->mem[q - mem_min].hh.rh = p;
        ctx->mem[mem_max - mem_min - 1].hh.rh = q;
        goto _L22;
      } else {
        ctx->page_so_far[1] +=
            ctx->page_so_far[7] + ctx->mem[p - mem_min + 3].int_;
        ctx->page_so_far[7] = ctx->mem[p - mem_min + 2].int_;
        goto _L80;
      }
      break;
    case 8:
      goto _L80;
      break;
    case 10:
      if (ctx->page_contents < 2)
        goto _L31;
      if (ctx->mem[ctx->page_tail - mem_min].hh.U2.b0 >= 9)
        goto _L90;
      pi = 0;
      break;
    case 11:
      if (ctx->page_contents < 2)
        goto _L31;
      if (ctx->mem[p - mem_min].hh.rh == (-1073741824))
        goto _L10;
      if (ctx->mem[ctx->mem[p - mem_min].hh.rh - mem_min].hh.U2.b0 != 10)
        goto _L90;
      pi = 0;
      break;
    case 12:
      if (ctx->page_contents < 2)
        goto _L31;
      pi = ctx->mem[p - mem_min + 1].int_;
      break;
    case 4:
      goto _L80;
      break;
    case 3:
      if (!ctx->page_contents)
        freeze_page_specs(ctx, 1);
      n = ctx->mem[p - mem_min].hh.U2.b1;
      r = mem_max;
      while (n >= ctx->mem[ctx->mem[r - mem_min].hh.rh - mem_min].hh.U2.b1)
        r = ctx->mem[r - mem_min].hh.rh;
      if (ctx->mem[r - mem_min].hh.U2.b1 != n) {
        q = get_node(ctx, 4);
        ctx->mem[q - mem_min].hh.rh = ctx->mem[r - mem_min].hh.rh;
        ctx->mem[r - mem_min].hh.rh = q;
        r = q;
        ctx->mem[r - mem_min].hh.U2.b1 = n;
        ctx->mem[r - mem_min].hh.U2.b0 = 0;
        ensure_vbox(ctx, n);
        if (ctx->eqtb[n + 10578].hh.rh == (-1073741824))
          ctx->mem[r - mem_min + 3].int_ = 0;
        else
          (ctx->mem[r - mem_min + 3].int_ =
               (ctx->mem[ctx->eqtb[n + 10578].hh.rh - mem_min + 3].int_ +
                (ctx->mem[(ctx->eqtb[n + 10578].hh.rh - mem_min + 2)].int_)));
        ctx->mem[r - mem_min + 2].hh.lh = -1073741824;
        q = ctx->eqtb[n + 9800].hh.rh;
        if (ctx->eqtb[n + 12218].int_ == 1000)
          h = ctx->mem[r - mem_min + 3].int_;
        else
          h = x_over_n(ctx, ctx->mem[r - mem_min + 3].int_, 1000) *
              ctx->eqtb[n + 12218].int_;
        ctx->page_so_far[0] += (-h) - ctx->mem[q - mem_min + 1].int_;
        ctx->page_so_far[ctx->mem[q - mem_min].hh.U2.b0 + 2] +=
            ctx->mem[q - mem_min + 2].int_;
        ctx->page_so_far[6] += ctx->mem[q - mem_min + 3].int_;
        if (ctx->mem[q - mem_min].hh.U2.b1 && ctx->mem[q - mem_min + 3].int_) {
          print_nl(ctx, 262);
          print(ctx, 997);
          print_esc(ctx, 395);
          print_int(ctx, n);
          ctx->help_ptr = 3;
          ctx->help_line[2] = 998;
          ctx->help_line[1] = 999;
          ctx->help_line[0] = 921;
          error(ctx);
        }
      }
      if (ctx->mem[r - mem_min].hh.U2.b0 == 1) {
        ctx->insert_penalties += ctx->mem[p - mem_min + 1].int_;
      } else {
        ctx->mem[r - mem_min + 2].hh.rh = p;
        delta = ctx->page_so_far[0] - ctx->page_so_far[1] -
                ctx->page_so_far[7] + ctx->page_so_far[6];
        if (ctx->eqtb[n + 12218].int_ == 1000)
          h = ctx->mem[p - mem_min + 3].int_;
        else
          h = x_over_n(ctx, ctx->mem[p - mem_min + 3].int_, 1000) *
              ctx->eqtb[n + 12218].int_;
        if (((h <= 0) || (h <= delta)) &&
            (ctx->mem[p - mem_min + 3].int_ + ctx->mem[r - mem_min + 3].int_ <=
             ctx->eqtb[n + 12751].int_)) {
          ctx->page_so_far[0] -= h;
          ctx->mem[r - mem_min + 3].int_ += ctx->mem[p - mem_min + 3].int_;
        } else {
          if (ctx->eqtb[n + 12218].int_ <= 0) {
            w = 1073741823;
          } else {
            w = ctx->page_so_far[0] - ctx->page_so_far[1] - ctx->page_so_far[7];
            if (ctx->eqtb[n + 12218].int_ != 1000)
              w = x_over_n(ctx, w, ctx->eqtb[n + 12218].int_) * 1000;
          }
          if (w > (ctx->eqtb[n + 12751].int_ - ctx->mem[r - mem_min + 3].int_))
            w = ctx->eqtb[n + 12751].int_ - ctx->mem[r - mem_min + 3].int_;
          q = vert_break(ctx, ctx->mem[p - mem_min + 4].hh.lh, w,
                         ctx->mem[p - mem_min + 2].int_);
          ctx->mem[r - mem_min + 3].int_ += ctx->best_height_plus_depth;
          if (ctx->eqtb[n + 12218].int_ != 1000)
            ctx->best_height_plus_depth =
                x_over_n(ctx, ctx->best_height_plus_depth, 1000) *
                ctx->eqtb[n + 12218].int_;
          ctx->page_so_far[0] -= ctx->best_height_plus_depth;
          ctx->mem[r - mem_min].hh.U2.b0 = 1;
          ctx->mem[r - mem_min + 1].hh.rh = q;
          ctx->mem[r - mem_min + 1].hh.lh = p;
          if (q == (-1073741824)) {
            ctx->insert_penalties -= 10000;
          } else if (ctx->mem[q - mem_min].hh.U2.b0 == 12)
            ctx->insert_penalties += ctx->mem[q - mem_min + 1].int_;
        }
      }
      goto _L80;
      break;
    default:
      confusion(ctx, 992);
      break;
    }
    if (pi < 10000) {
      if (ctx->page_so_far[1] < ctx->page_so_far[0]) {
        if (ctx->page_so_far[3] || ctx->page_so_far[4] || ctx->page_so_far[5])
          b = 0;
        else
          b = badness(ctx, ctx->page_so_far[0] - ctx->page_so_far[1],
                      ctx->page_so_far[2]);
      } else if (ctx->page_so_far[1] - ctx->page_so_far[0] >
                 ctx->page_so_far[6])
        b = 1073741823;
      else
        b = badness(ctx, ctx->page_so_far[1] - ctx->page_so_far[0],
                    ctx->page_so_far[6]);
      if (b < 1073741823) {
        if (pi <= (-10000)) {
          c = pi;
        } else if (b < 10000)
          c = b + pi + ctx->insert_penalties;
        else
          c = 100000;
      } else {
        c = b;
      }
      if (ctx->insert_penalties >= 10000)
        c = 1073741823;
      if (c <= ctx->least_page_cost) {
        ctx->best_page_break = p;
        ctx->best_size = ctx->page_so_far[0];
        ctx->least_page_cost = c;
        r = ctx->mem[mem_max - mem_min].hh.rh;
        while (r != mem_max) {
          ctx->mem[r - mem_min + 2].hh.lh = ctx->mem[r - mem_min + 2].hh.rh;
          r = ctx->mem[r - mem_min].hh.rh;
        }
      }
      if ((c == 1073741823) || (pi <= (-10000))) {
        fire_up(ctx, p);
        if (ctx->output_active)
          goto _L10;
        goto _L30;
      }
    }
    if ((ctx->mem[p - mem_min].hh.U2.b0 < 10) ||
        (ctx->mem[p - mem_min].hh.U2.b0 > 11))
      goto _L80;
  _L90:
    if (ctx->mem[p - mem_min].hh.U2.b0 == 11) {
      q = p;
    } else {
      q = ctx->mem[p - mem_min + 1].hh.lh;
      ctx->page_so_far[ctx->mem[q - mem_min].hh.U2.b0 + 2] +=
          ctx->mem[q - mem_min + 2].int_;
      ctx->page_so_far[6] += ctx->mem[q - mem_min + 3].int_;
      if (ctx->mem[q - mem_min].hh.U2.b1 && ctx->mem[q - mem_min + 3].int_) {
        print_nl(ctx, 262);
        print(ctx, 993);
        ctx->help_ptr = 4;
        ctx->help_line[3] = 994;
        ctx->help_line[2] = 962;
        ctx->help_line[1] = 963;
        ctx->help_line[0] = 921;
        error(ctx);
        r = new_spec(ctx, q);
        ctx->mem[r - mem_min].hh.U2.b1 = 0;
        delete_glue_ref(ctx, q);
        ctx->mem[p - mem_min + 1].hh.lh = r;
        q = r;
      }
    }
    ctx->page_so_far[1] += ctx->page_so_far[7] + ctx->mem[q - mem_min + 1].int_;
    ctx->page_so_far[7] = 0;
  _L80:
    if (ctx->page_so_far[7] > ctx->page_max_depth) {
      ctx->page_so_far[1] += ctx->page_so_far[7] - ctx->page_max_depth;
      ctx->page_so_far[7] = ctx->page_max_depth;
    }
    ctx->mem[ctx->page_tail - mem_min].hh.rh = p;
    ctx->page_tail = p;
    ctx->mem[mem_max - mem_min - 1].hh.rh = ctx->mem[p - mem_min].hh.rh;
    ctx->mem[p - mem_min].hh.rh = -1073741824;
    goto _L30;
  _L31:
    ctx->mem[mem_max - mem_min - 1].hh.rh = ctx->mem[p - mem_min].hh.rh;
    ctx->mem[p - mem_min].hh.rh = -1073741824;
    flush_node_list(ctx, p);
  _L30:;
  } while (ctx->mem[mem_max - mem_min - 1].hh.rh != (-1073741824));
  if (!ctx->nest_ptr)
    ctx->cur_list.tail_field = mem_max - 1;
  else
    ctx->nest[0].tail_field = mem_max - 1;
_L10:;
}

void app_space(ctex_t *ctx) {
  halfword q;
  if ((ctx->cur_list.aux_field.hh.lh >= 2000) && ctx->eqtb[9795].hh.rh) {
    q = new_param_glue(ctx, 13);
  } else {
    if (ctx->eqtb[9794].hh.rh) {
      ctx->main_p = ctx->eqtb[9794].hh.rh;
    } else {
      ctx->main_p = ctx->fnt_infos.font_glue[ctx->eqtb[10834].hh.rh];
      if (ctx->main_p == (-1073741824)) {
        ctx->main_p = new_spec(ctx, 0);
        ctx->main_k = ctx->fnt_infos.param_base[ctx->eqtb[10834].hh.rh] + 2;
        ctx->mem[ctx->main_p - mem_min + 1].int_ =
            ctx->font_info[ctx->main_k].int_;
        ctx->mem[ctx->main_p - mem_min + 2].int_ =
            ctx->font_info[ctx->main_k + 1].int_;
        ctx->mem[ctx->main_p - mem_min + 3].int_ =
            ctx->font_info[ctx->main_k + 2].int_;
        ctx->fnt_infos.font_glue[ctx->eqtb[10834].hh.rh] = ctx->main_p;
      }
    }
    ctx->main_p = new_spec(ctx, ctx->main_p);
    if (ctx->cur_list.aux_field.hh.lh >= 2000)
      ctx->mem[ctx->main_p - mem_min + 1].int_ +=
          ctx->font_info[ctx->fnt_infos.param_base[ctx->eqtb[10834].hh.rh] + 7]
              .int_;
    ctx->mem[ctx->main_p - mem_min + 2].int_ =
        xn_over_d(ctx, ctx->mem[ctx->main_p - mem_min + 2].int_,
                  ctx->cur_list.aux_field.hh.lh, 1000);
    ctx->mem[ctx->main_p - mem_min + 3].int_ =
        xn_over_d(ctx, ctx->mem[ctx->main_p - mem_min + 3].int_, 1000,
                  ctx->cur_list.aux_field.hh.lh);
    q = new_glue(ctx, ctx->main_p);
    ctx->mem[ctx->main_p - mem_min].hh.rh = -1073741824;
  }
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = q;
  ctx->cur_list.tail_field = q;
}

void insert_dollar_sign(ctex_t *ctx) {
  back_input(ctx);
  ctx->cur_tok = 804;
  print_nl(ctx, 262);
  print(ctx, 1016);
  ctx->help_ptr = 2;
  ctx->help_line[1] = 1017;
  ctx->help_line[0] = 1018;
  ins_error(ctx);
}

void you_cant(ctex_t *ctx) {
  print_nl(ctx, 262);
  print(ctx, 685);
  print_cmd_chr(ctx, ctx->cur_cmd, ctx->cur_chr);
  print(ctx, 1019);
  print_mode(ctx, ctx->cur_list.mode_field);
}

void report_illegal_case(ctex_t *ctx) {
  you_cant(ctx);
  ctx->help_ptr = 4;
  ctx->help_line[3] = 1020;
  ctx->help_line[2] = 1021;
  ctx->help_line[1] = 1022;
  ctx->help_line[0] = 1023;
  error(ctx);
}

bool_t privileged(ctex_t *ctx) {
  if (ctx->cur_list.mode_field > 0) {
    return true;
  } else {
    report_illegal_case(ctx);
    return false;
  }
}

bool_t its_all_over(ctex_t *ctx) {
  bool_t result;
  if (privileged(ctx)) {
    if ((mem_max - 2 == ctx->page_tail) &&
        (ctx->cur_list.head_field == ctx->cur_list.tail_field) &&
        (!ctx->dead_cycles)) {
      result = true;
      goto _L10;
    }
    back_input(ctx);
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_null_box(ctx);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].int_ =
        ctx->eqtb[12733].int_;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_glue(ctx, 8);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        new_penalty(ctx, -1073741824);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    build_page(ctx);
  }
  result = false;
_L10:
  return result;
}

void append_glue(ctex_t *ctx) {
  small_number s = ctx->cur_chr;
  switch (s) {
  case 0:
    ctx->cur_val = 4;
    break;
  case 1:
    ctx->cur_val = 8;
    break;
  case 2:
    ctx->cur_val = 12;
    break;
  case 3:
    ctx->cur_val = 16;
    break;
  case 4:
    scan_glue(ctx, 2);
    break;
  case 5:
    scan_glue(ctx, 3);
    break;
  }
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
      new_glue(ctx, ctx->cur_val);
  ctx->cur_list.tail_field = ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  if (s < 4)
    return;
  --ctx->mem[ctx->cur_val - mem_min].hh.rh;
  if (s > 4)
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 = 99;
}

void append_kern(ctex_t *ctx) {
  quarterword s = ctx->cur_chr;
  scan_dimen(ctx, s == 99, false, false);
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
      new_kern(ctx, ctx->cur_val);
  ctx->cur_list.tail_field = ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 = s;
}

void off_save(ctex_t *ctx) {
  halfword p;
  if (!ctx->cur_group) {
    print_nl(ctx, 262);
    print(ctx, 776);
    print_cmd_chr(ctx, ctx->cur_cmd, ctx->cur_chr);
    ctx->help_ptr = 1;
    ctx->help_line[0] = 1042;
    error(ctx);
    return;
  }
  back_input(ctx);
  p = get_avail(ctx);
  ctx->mem[mem_max - mem_min - 3].hh.rh = p;
  print_nl(ctx, 262);
  print(ctx, 625);
  switch (ctx->cur_group) {
  case 14:
    ctx->mem[p - mem_min].hh.lh = 13611;
    print_esc(ctx, 516);
    break;
  case 15:
    ctx->mem[p - mem_min].hh.lh = 804;
    print_char(ctx, 36);
    break;
  case 16:
    ctx->mem[p - mem_min].hh.lh = 13612;
    ctx->mem[p - mem_min].hh.rh = get_avail(ctx);
    p = ctx->mem[p - mem_min].hh.rh;
    ctx->mem[p - mem_min].hh.lh = 3118;
    print_esc(ctx, 1041);
    break;
  default:
    ctx->mem[p - mem_min].hh.lh = 637;
    print_char(ctx, 125);
    break;
  }
  print(ctx, 626);
  begin_token_list(ctx, ctx->mem[mem_max - mem_min - 3].hh.rh, 4);
  ctx->help_ptr = 5;
  ctx->help_line[4] = 1036;
  ctx->help_line[3] = 1037;
  ctx->help_line[2] = 1038;
  ctx->help_line[1] = 1039;
  ctx->help_line[0] = 1040;
  error(ctx);
}

void extra_right_brace(ctex_t *ctx) {
  print_nl(ctx, 262);
  print(ctx, 1047);
  switch (ctx->cur_group) {
  case 14:
    print_esc(ctx, 516);
    break;
  case 15:
    print_char(ctx, 36);
    break;
  case 16:
    print_esc(ctx, 876);
    break;
  }
  ctx->help_ptr = 5;
  ctx->help_line[4] = 1048;
  ctx->help_line[3] = 1049;
  ctx->help_line[2] = 1050;
  ctx->help_line[1] = 1051;
  ctx->help_line[0] = 1052;
  error(ctx);
  ++ctx->align_state;
}

void normal_paragraph(ctex_t *ctx) {
  if (ctx->eqtb[12182].int_)
    eq_word_define(ctx, 12182, 0);
  if (ctx->eqtb[12747].int_)
    eq_word_define(ctx, 12747, 0);
  if (ctx->eqtb[12204].int_ != 1)
    eq_word_define(ctx, 12204, 1);
  if (ctx->eqtb[10312].hh.rh != (-1073741824))
    eq_define(ctx, 10312, 118, -1073741824);
}

void box_end(ctex_t *ctx, integer box_context) {
  halfword p;
  if (box_context < 1073741824) {
    if (ctx->cur_box == (-1073741824))
      return;
    ctx->mem[ctx->cur_box - mem_min + 4].int_ = box_context;
    if (abs(ctx->cur_list.mode_field) == 1) {
      append_to_vlist(ctx, ctx->cur_box);
      if (ctx->adjust_tail != (-1073741824)) {
        if (mem_max - 5 != ctx->adjust_tail) {
          ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
              ctx->mem[mem_max - mem_min - 5].hh.rh;
          ctx->cur_list.tail_field = ctx->adjust_tail;
        }
        ctx->adjust_tail = -1073741824;
      }
      if (ctx->cur_list.mode_field > 0)
        build_page(ctx);
      return;
    }
    if (abs(ctx->cur_list.mode_field) == 102) {
      ctx->cur_list.aux_field.hh.lh = 1000;
    } else {
      p = new_noad(ctx);
      ctx->mem[p - mem_min + 1].hh.rh = 2;
      ctx->mem[p - mem_min + 1].hh.lh = ctx->cur_box;
      ctx->cur_box = p;
    }
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = ctx->cur_box;
    ctx->cur_list.tail_field = ctx->cur_box;
    return;
  }
  if (box_context < 1073742336) {
    if (box_context < 1073742080)
      eq_define(ctx, box_context - 1073731246, 119, ctx->cur_box);
    else
      geq_define(ctx, box_context - 1073731502, 119, ctx->cur_box);
    return;
  }
  if (ctx->cur_box == (-1073741824))
    return;
  if (box_context <= 1073742336) {
    ship_out(ctx, ctx->cur_box);
    return;
  }
  do {
    get_x_token(ctx);
  } while ((ctx->cur_cmd == 10) || (!ctx->cur_cmd));
  if (((ctx->cur_cmd == 26) && (abs(ctx->cur_list.mode_field) != 1)) ||
      ((ctx->cur_cmd == 27) && (abs(ctx->cur_list.mode_field) == 1))) {
    append_glue(ctx);
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 =
        box_context - 1073742237;
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.rh = ctx->cur_box;
    return;
  }
  print_nl(ctx, 262);
  print(ctx, 1065);
  ctx->help_ptr = 3;
  ctx->help_line[2] = 1066;
  ctx->help_line[1] = 1067;
  ctx->help_line[0] = 1068;
  back_error(ctx);
  flush_node_list(ctx, ctx->cur_box);
}

void begin_box(ctex_t *ctx, integer box_context) {
  halfword p, q;
  quarterword m;
  halfword k;
  uint8_t n;
  quarterword N1;
  switch (ctx->cur_chr) {
  case 0:
    scan_eight_bit_int(ctx);
    ctx->cur_box = ctx->eqtb[ctx->cur_val + 10578].hh.rh;
    ctx->eqtb[ctx->cur_val + 10578].hh.rh = -1073741824;
    break;
  case 1:
    scan_eight_bit_int(ctx);
    ctx->cur_box = copy_node_list(ctx, ctx->eqtb[ctx->cur_val + 10578].hh.rh);
    break;
  case 2:
    ctx->cur_box = -1073741824;
    if (abs(ctx->cur_list.mode_field) == 203) {
      you_cant(ctx);
      ctx->help_ptr = 1;
      ctx->help_line[0] = 1069;
      error(ctx);
    } else if ((ctx->cur_list.mode_field == 1) &&
               (ctx->cur_list.head_field == ctx->cur_list.tail_field)) {
      you_cant(ctx);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 1070;
      ctx->help_line[0] = 1071;
      error(ctx);
    } else if (ctx->cur_list.tail_field < ctx->hi_mem_min) {
      if ((!ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0) ||
          (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 == 1)) {
        q = ctx->cur_list.head_field;
        do {
          p = q;
          if (q < ctx->hi_mem_min) {
            if (ctx->mem[q - mem_min].hh.U2.b0 == 7) {
              for (N1 = ctx->mem[q - mem_min].hh.U2.b1, m = 1; m <= N1; ++m)
                p = ctx->mem[p - mem_min].hh.rh;
              if (p == ctx->cur_list.tail_field)
                goto _L30;
            }
          }
          q = ctx->mem[p - mem_min].hh.rh;
        } while (q != ctx->cur_list.tail_field);
        ctx->cur_box = ctx->cur_list.tail_field;
        ctx->mem[ctx->cur_box - mem_min + 4].int_ = 0;
        ctx->cur_list.tail_field = p;
        ctx->mem[p - mem_min].hh.rh = -1073741824;
      _L30:;
      }
    }
    break;
  case 3:
    scan_eight_bit_int(ctx);
    n = ctx->cur_val;
    if (!scan_keyword(ctx, 841)) {
      print_nl(ctx, 262);
      print(ctx, 1072);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 1073;
      ctx->help_line[0] = 1074;
      error(ctx);
    }
    scan_dimen(ctx, false, false, false);
    ctx->cur_box = vsplit(ctx, n, ctx->cur_val);
    break;
  default:
    k = ctx->cur_chr - 4;
    ctx->save_stack[ctx->save_ptr].int_ = box_context;
    if (k == 102) {
      if ((box_context < 1073741824) && (abs(ctx->cur_list.mode_field) == 1))
        scan_spec(ctx, 3, true);
      else
        scan_spec(ctx, 2, true);
    } else {
      if (k == 1) {
        scan_spec(ctx, 4, true);
      } else {
        scan_spec(ctx, 5, true);
        k = 1;
      }
      normal_paragraph(ctx);
    }
    push_nest(ctx);
    ctx->cur_list.mode_field = -k;
    if (k == 1) {
      ctx->cur_list.aux_field.int_ = -65536000;
      if (ctx->eqtb[10318].hh.rh != (-1073741824))
        begin_token_list(ctx, ctx->eqtb[10318].hh.rh, 11);
    } else {
      ctx->cur_list.aux_field.hh.lh = 1000;
      if (ctx->eqtb[10317].hh.rh != (-1073741824))
        begin_token_list(ctx, ctx->eqtb[10317].hh.rh, 10);
    }
    goto _L10;
    break;
  }
  box_end(ctx, box_context);
_L10:;
}

void scan_box(ctex_t *ctx, integer box_context) {
  do {
    get_x_token(ctx);
  } while ((ctx->cur_cmd == 10) || (!ctx->cur_cmd));
  if (ctx->cur_cmd == 20) {
    begin_box(ctx, box_context);
    return;
  }
  if ((box_context >= 1073742337) &&
      ((ctx->cur_cmd == 36) || (ctx->cur_cmd == 35))) {
    ctx->cur_box = scan_rule_spec(ctx);
    box_end(ctx, box_context);
    return;
  }
  print_nl(ctx, 262);
  print(ctx, 1075);
  ctx->help_ptr = 3;
  ctx->help_line[2] = 1076;
  ctx->help_line[1] = 1077;
  ctx->help_line[0] = 1078;
  back_error(ctx);
}

void package(ctex_t *ctx, small_number c) {
  scaled h;
  halfword p;
  scaled d = ctx->eqtb[12737].int_;
  unsave(ctx);
  ctx->save_ptr -= 3;
  if (ctx->cur_list.mode_field == (-102)) {
    ctx->cur_box =
        hpack(ctx, ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh,
              ctx->save_stack[ctx->save_ptr + 2].int_,
              ctx->save_stack[ctx->save_ptr + 1].int_);
  } else {
    (ctx->cur_box =
         vpackage(ctx, ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh,
                  ctx->save_stack[ctx->save_ptr + 2].int_,
                  ctx->save_stack[ctx->save_ptr + 1].int_, d));
    if (c == 4) {
      h = 0;
      p = ctx->mem[ctx->cur_box - mem_min + 5].hh.rh;
      if (p != (-1073741824)) {
        if (ctx->mem[p - mem_min].hh.U2.b0 <= 2)
          h = ctx->mem[p - mem_min + 3].int_;
      }
      ctx->mem[ctx->cur_box - mem_min + 2].int_ +=
          ctx->mem[ctx->cur_box - mem_min + 3].int_ - h;
      ctx->mem[ctx->cur_box - mem_min + 3].int_ = h;
    }
  }
  pop_nest(ctx);
  box_end(ctx, ctx->save_stack[ctx->save_ptr].int_);
}

small_number norm_min(ctex_t *ctx, integer h) {
  if (h <= 0) {
    return 1;
  } else if (h >= 63)
    return 63;
  else
    return h;
}

void new_graf(ctex_t *ctx, bool_t indented) {
  ctx->cur_list.pg_field = 0;
  if ((ctx->cur_list.mode_field == 1) ||
      (ctx->cur_list.head_field != ctx->cur_list.tail_field)) {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_param_glue(ctx, 2);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  }
  push_nest(ctx);
  ctx->cur_list.mode_field = 102;
  ctx->cur_list.aux_field.hh.lh = 1000;
  if (ctx->eqtb[12213].int_ <= 0) {
    ctx->cur_lang = 0;
  } else if (ctx->eqtb[12213].int_ > 255)
    ctx->cur_lang = 0;
  else
    ctx->cur_lang = ctx->eqtb[12213].int_;
  ctx->cur_list.aux_field.hh.rh = ctx->cur_lang;
  ctx->cur_list.pg_field = (((norm_min(ctx, ctx->eqtb[12214].int_) * 64) +
                             norm_min(ctx, ctx->eqtb[12215].int_)) *
                            65536) +
                           ctx->cur_lang;
  if (indented) {
    ctx->cur_list.tail_field = new_null_box(ctx);
    ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh =
        ctx->cur_list.tail_field;
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].int_ =
        ctx->eqtb[12730].int_;
  }
  if (ctx->eqtb[10314].hh.rh != (-1073741824))
    begin_token_list(ctx, ctx->eqtb[10314].hh.rh, 7);
  if (ctx->nest_ptr == 1)
    build_page(ctx);
}

void indent_in_hmode(ctex_t *ctx) {
  halfword p, q;
  if (ctx->cur_chr <= 0)
    return;
  p = new_null_box(ctx);
  ctx->mem[p - mem_min + 1].int_ = ctx->eqtb[12730].int_;
  if (abs(ctx->cur_list.mode_field) == 102) {
    ctx->cur_list.aux_field.hh.lh = 1000;
  } else {
    q = new_noad(ctx);
    ctx->mem[q - mem_min + 1].hh.rh = 2;
    ctx->mem[q - mem_min + 1].hh.lh = p;
    p = q;
  }
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = p;
  ctx->cur_list.tail_field = ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
}

void head_for_vmode(ctex_t *ctx) {
  if (ctx->cur_list.mode_field < 0) {
    if (ctx->cur_cmd != 36) {
      off_save(ctx);
      return;
    }
    print_nl(ctx, 262);
    print(ctx, 685);
    print_esc(ctx, 521);
    print(ctx, 1081);
    ctx->help_ptr = 2;
    ctx->help_line[1] = 1082;
    ctx->help_line[0] = 1083;
    error(ctx);
    return;
  }
  back_input(ctx);
  ctx->cur_tok = ctx->par_token;
  back_input(ctx);
  ctx->cur_input.index_field = 4;
}

void end_graf(ctex_t *ctx) {
  if (ctx->cur_list.mode_field != 102)
    return;
  if (ctx->cur_list.head_field == ctx->cur_list.tail_field)
    pop_nest(ctx);
  else
    line_break(ctx, ctx->eqtb[12169].int_);
  normal_paragraph(ctx);
  ctx->error_count = 0;
}

void begin_insert_or_adjust(ctex_t *ctx) {
  if (ctx->cur_cmd == 38) {
    ctx->cur_val = 255;
  } else {
    scan_eight_bit_int(ctx);
    if (ctx->cur_val == 255) {
      print_nl(ctx, 262);
      print(ctx, 1084);
      print_esc(ctx, 330);
      print_int(ctx, 255);
      ctx->help_ptr = 1;
      ctx->help_line[0] = 1085;
      error(ctx);
      ctx->cur_val = 0;
    }
  }
  ctx->save_stack[ctx->save_ptr].int_ = ctx->cur_val;
  ++ctx->save_ptr;
  new_save_level(ctx, 11);
  scan_left_brace(ctx);
  normal_paragraph(ctx);
  push_nest(ctx);
  ctx->cur_list.mode_field = -1;
  ctx->cur_list.aux_field.int_ = -65536000;
}

void make_mark(ctex_t *ctx) {
  halfword p = scan_toks(ctx, false, true);
  p = get_node(ctx, 2);
  ctx->mem[p - mem_min].hh.U2.b0 = 4;
  ctx->mem[p - mem_min].hh.U2.b1 = 0;
  ctx->mem[p - mem_min + 1].int_ = ctx->def_ref;
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = p;
  ctx->cur_list.tail_field = p;
}

void append_penalty(ctex_t *ctx) {
  scan_int(ctx);
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
      new_penalty(ctx, ctx->cur_val);
  ctx->cur_list.tail_field = ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  if (ctx->cur_list.mode_field == 1)
    build_page(ctx);
}

void delete_last(ctex_t *ctx) {
  halfword p, q;
  quarterword m, N;
  if ((ctx->cur_list.mode_field == 1) &&
      (ctx->cur_list.tail_field == ctx->cur_list.head_field)) {
    if ((ctx->cur_chr != 10) || (ctx->last_glue != 1073741824)) {
      you_cant(ctx);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 1070;
      ctx->help_line[0] = 1086;
      if (ctx->cur_chr == 11) {
        ctx->help_line[0] = 1087;
      } else if (ctx->cur_chr != 10)
        ctx->help_line[0] = 1088;
      error(ctx);
    }
  } else if (ctx->cur_list.tail_field < ctx->hi_mem_min) {
    if (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 == ctx->cur_chr) {
      q = ctx->cur_list.head_field;
      do {
        p = q;
        if (q < ctx->hi_mem_min) {
          if (ctx->mem[q - mem_min].hh.U2.b0 == 7) {
            for (N = ctx->mem[q - mem_min].hh.U2.b1, m = 1; m <= N; ++m)
              p = ctx->mem[p - mem_min].hh.rh;
            if (p == ctx->cur_list.tail_field)
              goto _L10;
          }
        }
        q = ctx->mem[p - mem_min].hh.rh;
      } while (q != ctx->cur_list.tail_field);
      ctx->mem[p - mem_min].hh.rh = -1073741824;
      flush_node_list(ctx, ctx->cur_list.tail_field);
      ctx->cur_list.tail_field = p;
    }
  }
_L10:;
}

void unpackage(ctex_t *ctx) {
  halfword p;
  char c = ctx->cur_chr;
  scan_eight_bit_int(ctx);
  p = ctx->eqtb[ctx->cur_val + 10578].hh.rh;
  if (p == (-1073741824))
    goto _L10;
  if ((abs(ctx->cur_list.mode_field) == 203) ||
      ((abs(ctx->cur_list.mode_field) == 1) &&
       (ctx->mem[p - mem_min].hh.U2.b0 != 1)) ||
      ((abs(ctx->cur_list.mode_field) == 102) &&
       ctx->mem[p - mem_min].hh.U2.b0)) {
    print_nl(ctx, 262);
    print(ctx, 1096);
    ctx->help_ptr = 3;
    ctx->help_line[2] = 1097;
    ctx->help_line[1] = 1098;
    ctx->help_line[0] = 1099;
    error(ctx);
    goto _L10;
  }
  if (c == 1) {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        copy_node_list(ctx, ctx->mem[p - mem_min + 5].hh.rh);
  } else {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        ctx->mem[p - mem_min + 5].hh.rh;
    ctx->eqtb[ctx->cur_val + 10578].hh.rh = -1073741824;
    free_node(ctx, p, 7);
  }
  while (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh != (-1073741824))
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
_L10:;
}

void append_italic_correction(ctex_t *ctx) {
  halfword p;
  internal_font_number f;
  if (ctx->cur_list.tail_field != ctx->cur_list.head_field) {
    if (ctx->cur_list.tail_field >= ctx->hi_mem_min) {
      p = ctx->cur_list.tail_field;
    } else if (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 == 6)
      p = ctx->cur_list.tail_field + 1;
    else
      goto _L10;
    f = ctx->mem[p - mem_min].hh.U2.b0;
    (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_kern(
         ctx, ctx->font_info[ctx->fnt_infos.italic_base[f] +
                             (ctx->font_info[ctx->fnt_infos.char_base[f] +
                                             ctx->mem[p - mem_min].hh.U2.b1]
                                  .qqqq.b2 /
                              4)]
                  .int_));
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 = 1;
  }
_L10:;
}

void append_discretionary(ctex_t *ctx) {
  integer c;
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_disc(ctx);
  ctx->cur_list.tail_field = ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  if (ctx->cur_chr == 1) {
    c = ctx->fnt_infos.hyphen_char[ctx->eqtb[10834].hh.rh];
    if (c >= 0) {
      if (c < 256)
        ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.lh =
            new_character(ctx, ctx->eqtb[10834].hh.rh, c);
    }
    return;
  }
  ++ctx->save_ptr;
  ctx->save_stack[ctx->save_ptr - 1].int_ = 0;
  new_save_level(ctx, 10);
  scan_left_brace(ctx);
  push_nest(ctx);
  ctx->cur_list.mode_field = -102;
  ctx->cur_list.aux_field.hh.lh = 1000;
}

void build_discretionary(ctex_t *ctx) {
  halfword p, q;
  integer n = 0;
  unsave(ctx);
  q = ctx->cur_list.head_field;
  p = ctx->mem[q - mem_min].hh.rh;
  while (p != (-1073741824)) {
    if (p < ctx->hi_mem_min) {
      if (ctx->mem[p - mem_min].hh.U2.b0 > 2) {
        if (ctx->mem[p - mem_min].hh.U2.b0 != 11) {
          if (ctx->mem[p - mem_min].hh.U2.b0 != 6) {
            print_nl(ctx, 262);
            print(ctx, 1106);
            ctx->help_ptr = 1;
            ctx->help_line[0] = 1107;
            error(ctx);
            begin_diagnostic(ctx);
            print_nl(ctx, 1108);
            show_box(ctx, p);
            end_diagnostic(ctx, true);
            flush_node_list(ctx, p);
            ctx->mem[q - mem_min].hh.rh = -1073741824;
            goto _L30;
          }
        }
      }
    }
    q = p;
    p = ctx->mem[q - mem_min].hh.rh;
    ++n;
  }
_L30:
  p = ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh;
  pop_nest(ctx);
  switch (ctx->save_stack[ctx->save_ptr - 1].int_) {
  case 0:
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.lh = p;
    break;
  case 1:
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.rh = p;
    break;
  case 2:
    if ((n > 0) && (abs(ctx->cur_list.mode_field) == 203)) {
      print_nl(ctx, 262);
      print(ctx, 1100);
      print_esc(ctx, 349);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 1101;
      ctx->help_line[0] = 1102;
      flush_node_list(ctx, p);
      n = 0;
      error(ctx);
    } else {
      ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = p;
    }
    if (n <= 65535) {
      ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 = n;
    } else {
      print_nl(ctx, 262);
      print(ctx, 1103);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 1104;
      ctx->help_line[0] = 1105;
      error(ctx);
    }
    if (n > 0)
      ctx->cur_list.tail_field = q;
    --ctx->save_ptr;
    goto _L10;
    break;
  }
  ++ctx->save_stack[ctx->save_ptr - 1].int_;
  new_save_level(ctx, 10);
  scan_left_brace(ctx);
  push_nest(ctx);
  ctx->cur_list.mode_field = -102;
  ctx->cur_list.aux_field.hh.lh = 1000;
_L10:;
}

void make_accent(ctex_t *ctx) {
  double s, t;
  halfword p, q = -1073741824, r;
  internal_font_number f;
  scaled a, h, x, w, delta;
  four_quarters i;
  scan_char_num(ctx);
  f = ctx->eqtb[10834].hh.rh;
  p = new_character(ctx, f, ctx->cur_val);
  if (p == (-1073741824))
    return;
  x = ctx->font_info[ctx->fnt_infos.param_base[f] + 5].int_;
  s = ctx->font_info[ctx->fnt_infos.param_base[f] + 1].int_ / 65536.0;
  a = ctx->font_info[ctx->fnt_infos.width_base[f] +
                     ctx->font_info[ctx->fnt_infos.char_base[f] +
                                    ctx->mem[p - mem_min].hh.U2.b1]
                         .qqqq.b0]
          .int_;
  do_assignments(ctx);
  f = ctx->eqtb[10834].hh.rh;
  if ((ctx->cur_cmd == 11) || (ctx->cur_cmd == 12) || (ctx->cur_cmd == 68)) {
    q = new_character(ctx, f, ctx->cur_chr);
  } else if (ctx->cur_cmd == 16) {
    scan_char_num(ctx);
    q = new_character(ctx, f, ctx->cur_val);
  } else {
    back_input(ctx);
  }
  if (q != (-1073741824)) {
    t = ctx->font_info[ctx->fnt_infos.param_base[f] + 1].int_ / 65536.0;
    i = ctx->font_info[ctx->fnt_infos.char_base[f] +
                       ctx->mem[q - mem_min].hh.U2.b1]
            .qqqq;
    w = ctx->font_info[ctx->fnt_infos.width_base[f] + i.b0].int_;
    h = ctx->font_info[ctx->fnt_infos.height_base[f] + (i.b1 / 16)].int_;
    if (h != x) {
      p = hpack(ctx, p, 0, 1);
      ctx->mem[p - mem_min + 4].int_ = x - h;
    }
    delta = round(((w - a) / 2.0) + (h * t) - (x * s));
    r = new_kern(ctx, delta);
    ctx->mem[r - mem_min].hh.U2.b1 = 2;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = r;
    ctx->mem[r - mem_min].hh.rh = p;
    ctx->cur_list.tail_field = new_kern(ctx, (-a) - delta);
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 = 2;
    ctx->mem[p - mem_min].hh.rh = ctx->cur_list.tail_field;
    p = q;
  }
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = p;
  ctx->cur_list.tail_field = p;
  ctx->cur_list.aux_field.hh.lh = 1000;
}

void align_error(ctex_t *ctx) {
  if (abs(ctx->align_state) > 2) {
    print_nl(ctx, 262);
    print(ctx, 1113);
    print_cmd_chr(ctx, ctx->cur_cmd, ctx->cur_chr);
    if (ctx->cur_tok == 1062) {
      ctx->help_ptr = 6;
      ctx->help_line[5] = 1114;
      ctx->help_line[4] = 1115;
      ctx->help_line[3] = 1116;
      ctx->help_line[2] = 1117;
      ctx->help_line[1] = 1118;
      ctx->help_line[0] = 1119;
    } else {
      ctx->help_ptr = 5;
      ctx->help_line[4] = 1114;
      ctx->help_line[3] = 1120;
      ctx->help_line[2] = 1117;
      ctx->help_line[1] = 1118;
      ctx->help_line[0] = 1119;
    }
    error(ctx);
    return;
  }
  back_input(ctx);
  if (ctx->align_state < 0) {
    print_nl(ctx, 262);
    print(ctx, 657);
    ++ctx->align_state;
    ctx->cur_tok = 379;
  } else {
    print_nl(ctx, 262);
    print(ctx, 1109);
    --ctx->align_state;
    ctx->cur_tok = 637;
  }
  ctx->help_ptr = 3;
  ctx->help_line[2] = 1110;
  ctx->help_line[1] = 1111;
  ctx->help_line[0] = 1112;
  ins_error(ctx);
}

void no_align_error(ctex_t *ctx) {
  print_nl(ctx, 262);
  print(ctx, 1113);
  print_esc(ctx, 527);
  ctx->help_ptr = 2;
  ctx->help_line[1] = 1121;
  ctx->help_line[0] = 1122;
  error(ctx);
}

void omit_error(ctex_t *ctx) {
  print_nl(ctx, 262);
  print(ctx, 1113);
  print_esc(ctx, 530);
  ctx->help_ptr = 2;
  ctx->help_line[1] = 1123;
  ctx->help_line[0] = 1122;
  error(ctx);
}

void do_endv(ctex_t *ctx) {
  ctx->base_ptr = ctx->input_ptr;
  ctx->input_stack[ctx->base_ptr] = ctx->cur_input;
  while ((ctx->input_stack[ctx->base_ptr].index_field != 2) &&
         (ctx->input_stack[ctx->base_ptr].loc_field == (-1073741824)) &&
         (!ctx->input_stack[ctx->base_ptr].state_field))
    --ctx->base_ptr;
  if ((ctx->input_stack[ctx->base_ptr].index_field != 2) ||
      (ctx->input_stack[ctx->base_ptr].loc_field != (-1073741824)) ||
      ctx->input_stack[ctx->base_ptr].state_field)
    fatal_error(ctx, 595);
  if (ctx->cur_group != 6) {
    off_save(ctx);
    return;
  }
  end_graf(ctx);
  if (fin_col(ctx))
    fin_row(ctx);
}

void cs_error(ctex_t *ctx) {
  print_nl(ctx, 262);
  print(ctx, 776);
  print_esc(ctx, 505);
  ctx->help_ptr = 1;
  ctx->help_line[0] = 1125;
  error(ctx);
}

void push_math(ctex_t *ctx, group_code c) {
  push_nest(ctx);
  ctx->cur_list.mode_field = -203;
  ctx->cur_list.aux_field.int_ = -1073741824;
  new_save_level(ctx, c);
}

void init_math(ctex_t *ctx) {
  scaled w, l, s, v, d;
  halfword p, q;
  internal_font_number f;
  integer n;
  get_token(ctx);
  if ((ctx->cur_cmd == 3) && (ctx->cur_list.mode_field > 0)) {
    if (ctx->cur_list.head_field == ctx->cur_list.tail_field) {
      pop_nest(ctx);
      w = -1073741823;
    } else {
      line_break(ctx, ctx->eqtb[12170].int_);
      v = ctx->mem[ctx->just_box - mem_min + 4].int_ +
          (ctx->font_info[ctx->fnt_infos.param_base[ctx->eqtb[10834].hh.rh] + 6]
               .int_ *
           2);
      w = -1073741823;
      p = ctx->mem[ctx->just_box - mem_min + 5].hh.rh;
      while (p != (-1073741824)) {
      _L21:
        if (p >= ctx->hi_mem_min) {
          f = ctx->mem[p - mem_min].hh.U2.b0;
          d = ctx->font_info[ctx->fnt_infos.width_base[f] +
                             ctx->font_info[ctx->fnt_infos.char_base[f] +
                                            ctx->mem[p - mem_min].hh.U2.b1]
                                 .qqqq.b0]
                  .int_;
          goto _L40;
        }
        switch (ctx->mem[p - mem_min].hh.U2.b0) {
        case 0:
        case 1:
        case 2:
          d = ctx->mem[p - mem_min + 1].int_;
          goto _L40;
          break;
        case 6:
          ctx->mem[mem_max - mem_min - 12] = ctx->mem[p - mem_min + 1];
          ctx->mem[mem_max - mem_min - 12].hh.rh = ctx->mem[p - mem_min].hh.rh;
          p = mem_max - 12;
          goto _L21;
          break;
        case 11:
        case 9:
          d = ctx->mem[p - mem_min + 1].int_;
          break;
        case 10:
          q = ctx->mem[p - mem_min + 1].hh.lh;
          d = ctx->mem[q - mem_min + 1].int_;
          if (ctx->mem[ctx->just_box - mem_min + 5].hh.U2.b0 == 1) {
            if ((ctx->mem[ctx->just_box - mem_min + 5].hh.U2.b1 ==
                 ctx->mem[q - mem_min].hh.U2.b0) &&
                ctx->mem[q - mem_min + 2].int_)
              v = 1073741823;
          } else if (ctx->mem[ctx->just_box - mem_min + 5].hh.U2.b0 == 2) {
            if ((ctx->mem[ctx->just_box - mem_min + 5].hh.U2.b1 ==
                 ctx->mem[q - mem_min].hh.U2.b1) &&
                ctx->mem[q - mem_min + 3].int_)
              v = 1073741823;
          }
          if (ctx->mem[p - mem_min].hh.U2.b1 >= 100)
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
        p = ctx->mem[p - mem_min].hh.rh;
      }
    _L30:;
    }
    if (ctx->eqtb[10312].hh.rh == (-1073741824)) {
      if (ctx->eqtb[12747].int_ &&
          (((ctx->eqtb[12204].int_ >= 0) &&
            (ctx->cur_list.pg_field + 2 > ctx->eqtb[12204].int_)) ||
           (ctx->cur_list.pg_field + 1 < -ctx->eqtb[12204].int_))) {
        l = ctx->eqtb[12733].int_ - abs(ctx->eqtb[12747].int_);
        if (ctx->eqtb[12747].int_ > 0)
          s = ctx->eqtb[12747].int_;
        else
          s = 0;
      } else {
        l = ctx->eqtb[12733].int_;
        s = 0;
      }
    } else {
      n = ctx->mem[ctx->eqtb[10312].hh.rh - mem_min].hh.lh;
      if (ctx->cur_list.pg_field + 2 >= n)
        p = ctx->eqtb[10312].hh.rh + (n * 2);
      else
        p = ctx->eqtb[10312].hh.rh + ((ctx->cur_list.pg_field + 2) * 2);
      s = ctx->mem[p - mem_min - 1].int_;
      l = ctx->mem[p - mem_min].int_;
    }
    push_math(ctx, 15);
    ctx->cur_list.mode_field = 203;
    eq_word_define(ctx, 12207, -1);
    eq_word_define(ctx, 12743, w);
    eq_word_define(ctx, 12744, l);
    eq_word_define(ctx, 12745, s);
    if (ctx->eqtb[10316].hh.rh != (-1073741824))
      begin_token_list(ctx, ctx->eqtb[10316].hh.rh, 9);
    if (ctx->nest_ptr == 1)
      build_page(ctx);
    return;
  }
  back_input(ctx);
  push_math(ctx, 15);
  eq_word_define(ctx, 12207, -1);
  if (ctx->eqtb[10315].hh.rh != (-1073741824))
    begin_token_list(ctx, ctx->eqtb[10315].hh.rh, 8);
}

void start_eq_no(ctex_t *ctx) {
  ctx->save_stack[ctx->save_ptr].int_ = ctx->cur_chr;
  ++ctx->save_ptr;
  push_math(ctx, 15);
  eq_word_define(ctx, 12207, -1);
  if (ctx->eqtb[10315].hh.rh != (-1073741824))
    begin_token_list(ctx, ctx->eqtb[10315].hh.rh, 8);
}

void scan_math(ctex_t *ctx, halfword p) {
  integer c;
_L20:
  do {
    get_x_token(ctx);
  } while ((ctx->cur_cmd == 10) || (!ctx->cur_cmd));
_L21:
  switch (ctx->cur_cmd) {
  case 11:
  case 12:
  case 68:
    c = ctx->eqtb[ctx->cur_chr + 11907].hh.rh + 1073741824;
    if (c == 32768) {
      ctx->cur_cs = ctx->cur_chr + 1;
      ctx->cur_cmd = ctx->eqtb[ctx->cur_cs].hh.U2.b0;
      ctx->cur_chr = ctx->eqtb[ctx->cur_cs].hh.rh;
      x_token(ctx);
      back_input(ctx);
      goto _L20;
    }
    break;
  case 16:
    scan_char_num(ctx);
    ctx->cur_chr = ctx->cur_val;
    ctx->cur_cmd = 68;
    goto _L21;
    break;
  case 17:
    scan_fifteen_bit_int(ctx);
    c = ctx->cur_val;
    break;
  case 69:
    c = ctx->cur_chr;
    break;
  case 15:
    scan_twenty_seven_bit_int(ctx);
    c = ctx->cur_val / 4096;
    break;
  default:
    back_input(ctx);
    scan_left_brace(ctx);
    ctx->save_stack[ctx->save_ptr].int_ = p;
    ++ctx->save_ptr;
    push_math(ctx, 9);
    goto _L10;
    break;
  }
  ctx->mem[p - mem_min].hh.rh = 1;
  ctx->mem[p - mem_min].hh.U2.b1 = c & 255;
  if ((c >= 28672) && (((unsigned)ctx->eqtb[12207].int_) < 16))
    ctx->mem[p - mem_min].hh.U2.b0 = ctx->eqtb[12207].int_;
  else
    ctx->mem[p - mem_min].hh.U2.b0 = (c / 256) & 15;
_L10:;
}

void set_math_char(ctex_t *ctx, integer c) {
  halfword p;
  if (c >= 32768) {
    ctx->cur_cs = ctx->cur_chr + 1;
    ctx->cur_cmd = ctx->eqtb[ctx->cur_cs].hh.U2.b0;
    ctx->cur_chr = ctx->eqtb[ctx->cur_cs].hh.rh;
    x_token(ctx);
    back_input(ctx);
    return;
  }
  p = new_noad(ctx);
  ctx->mem[p - mem_min + 1].hh.rh = 1;
  ctx->mem[p - mem_min + 1].hh.U2.b1 = c & 255;
  ctx->mem[p - mem_min + 1].hh.U2.b0 = (c / 256) & 15;
  if (c >= 28672) {
    if (((unsigned)ctx->eqtb[12207].int_) < 16)
      ctx->mem[p - mem_min + 1].hh.U2.b0 = ctx->eqtb[12207].int_;
    ctx->mem[p - mem_min].hh.U2.b0 = 16;
  } else {
    ctx->mem[p - mem_min].hh.U2.b0 = (c / 4096) + 16;
  }
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = p;
  ctx->cur_list.tail_field = p;
}

void math_limit_switch(ctex_t *ctx) {
  if (ctx->cur_list.head_field != ctx->cur_list.tail_field) {
    if (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 == 17) {
      ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 = ctx->cur_chr;
      goto _L10;
    }
  }
  print_nl(ctx, 262);
  print(ctx, 1129);
  ctx->help_ptr = 1;
  ctx->help_line[0] = 1130;
  error(ctx);
_L10:;
}

void scan_delimiter(ctex_t *ctx, halfword p, bool_t r) {
  if (r) {
    scan_twenty_seven_bit_int(ctx);
  } else {
    do {
      get_x_token(ctx);
    } while ((ctx->cur_cmd == 10) || (!ctx->cur_cmd));
    switch (ctx->cur_cmd) {
    case 11:
    case 12:
      ctx->cur_val = ctx->eqtb[ctx->cur_chr + 12474].int_;
      break;
    case 15:
      scan_twenty_seven_bit_int(ctx);
      break;
    default:
      ctx->cur_val = -1;
      break;
    }
  }
  if (ctx->cur_val < 0) {
    print_nl(ctx, 262);
    print(ctx, 1131);
    ctx->help_ptr = 6;
    ctx->help_line[5] = 1132;
    ctx->help_line[4] = 1133;
    ctx->help_line[3] = 1134;
    ctx->help_line[2] = 1135;
    ctx->help_line[1] = 1136;
    ctx->help_line[0] = 1137;
    back_error(ctx);
    ctx->cur_val = 0;
  }
  ctx->mem[p - mem_min].qqqq.b0 = (ctx->cur_val / 1048576) & 15;
  ctx->mem[p - mem_min].qqqq.b1 = (ctx->cur_val / 4096) & 255;
  ctx->mem[p - mem_min].qqqq.b2 = (ctx->cur_val / 256) & 15;
  ctx->mem[p - mem_min].qqqq.b3 = ctx->cur_val & 255;
}

void math_radical(ctex_t *ctx) {
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = get_node(ctx, 5);
  ctx->cur_list.tail_field = ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 = 24;
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 = 0;
  ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh = ctx->empty_field;
  ctx->mem[ctx->cur_list.tail_field - mem_min + 3].hh = ctx->empty_field;
  ctx->mem[ctx->cur_list.tail_field - mem_min + 2].hh = ctx->empty_field;
  scan_delimiter(ctx, ctx->cur_list.tail_field + 4, true);
  scan_math(ctx, ctx->cur_list.tail_field + 1);
}

void math_ac(ctex_t *ctx) {
  if (ctx->cur_cmd == 45) {
    print_nl(ctx, 262);
    print(ctx, 1138);
    print_esc(ctx, 523);
    print(ctx, 1139);
    ctx->help_ptr = 2;
    ctx->help_line[1] = 1140;
    ctx->help_line[0] = 1141;
    error(ctx);
  }
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = get_node(ctx, 5);
  ctx->cur_list.tail_field = ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 = 28;
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 = 0;
  ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh = ctx->empty_field;
  ctx->mem[ctx->cur_list.tail_field - mem_min + 3].hh = ctx->empty_field;
  ctx->mem[ctx->cur_list.tail_field - mem_min + 2].hh = ctx->empty_field;
  ctx->mem[ctx->cur_list.tail_field - mem_min + 4].hh.rh = 1;
  scan_fifteen_bit_int(ctx);
  ctx->mem[ctx->cur_list.tail_field - mem_min + 4].hh.U2.b1 =
      ctx->cur_val & 255;
  if ((ctx->cur_val >= 28672) && (((unsigned)ctx->eqtb[12207].int_) < 16))
    ctx->mem[ctx->cur_list.tail_field - mem_min + 4].hh.U2.b0 =
        ctx->eqtb[12207].int_;
  else
    ctx->mem[ctx->cur_list.tail_field - mem_min + 4].hh.U2.b0 =
        (ctx->cur_val / 256) & 15;
  scan_math(ctx, ctx->cur_list.tail_field + 1);
}

void append_choices(ctex_t *ctx) {
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_choice(ctx);
  ctx->cur_list.tail_field = ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  ++ctx->save_ptr;
  ctx->save_stack[ctx->save_ptr - 1].int_ = 0;
  push_math(ctx, 13);
  scan_left_brace(ctx);
}

halfword fin_mlist(ctex_t *ctx, halfword p) {
  halfword q;
  if (ctx->cur_list.aux_field.int_ != (-1073741824)) {
    ctx->mem[ctx->cur_list.aux_field.int_ - mem_min + 3].hh.rh = 3;
    ctx->mem[ctx->cur_list.aux_field.int_ - mem_min + 3].hh.lh =
        ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh;
    if (p == (-1073741824)) {
      q = ctx->cur_list.aux_field.int_;
    } else {
      q = ctx->mem[ctx->cur_list.aux_field.int_ - mem_min + 2].hh.lh;
      if (ctx->mem[q - mem_min].hh.U2.b0 != 30)
        confusion(ctx, 876);
      ctx->mem[ctx->cur_list.aux_field.int_ - mem_min + 2].hh.lh =
          ctx->mem[q - mem_min].hh.rh;
      ctx->mem[q - mem_min].hh.rh = ctx->cur_list.aux_field.int_;
      ctx->mem[ctx->cur_list.aux_field.int_ - mem_min].hh.rh = p;
    }
  } else {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = p;
    q = ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh;
  }
  pop_nest(ctx);
  return q;
}

void build_choices(ctex_t *ctx) {
  halfword p;
  unsave(ctx);
  p = fin_mlist(ctx, -1073741824);
  switch (ctx->save_stack[ctx->save_ptr - 1].int_) {
  case 0:
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.lh = p;
    break;
  case 1:
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.rh = p;
    break;
  case 2:
    ctx->mem[ctx->cur_list.tail_field - mem_min + 2].hh.lh = p;
    break;
  case 3:
    ctx->mem[ctx->cur_list.tail_field - mem_min + 2].hh.rh = p;
    --ctx->save_ptr;
    goto _L10;
    break;
  }
  ++ctx->save_stack[ctx->save_ptr - 1].int_;
  push_math(ctx, 13);
  scan_left_brace(ctx);
_L10:;
}

void sub_sup(ctex_t *ctx) {
  small_number t = 0;
  halfword p = -1073741824;
  if (ctx->cur_list.tail_field != ctx->cur_list.head_field) {
    if ((ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 >= 16) &&
        (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 < 30)) {
      p = ctx->cur_list.tail_field + ctx->cur_cmd - 5;
      t = ctx->mem[p - mem_min].hh.rh;
    }
  }
  if ((p == (-1073741824)) || t) {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_noad(ctx);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    p = ctx->cur_list.tail_field + ctx->cur_cmd - 5;
    if (t) {
      if (ctx->cur_cmd == 7) {
        print_nl(ctx, 262);
        print(ctx, 1142);
        ctx->help_ptr = 1;
        ctx->help_line[0] = 1143;
      } else {
        print_nl(ctx, 262);
        print(ctx, 1144);
        ctx->help_ptr = 1;
        ctx->help_line[0] = 1145;
      }
      error(ctx);
    }
  }
  scan_math(ctx, p);
}

void math_fraction(ctex_t *ctx) {
  small_number c = ctx->cur_chr;
  if (ctx->cur_list.aux_field.int_ != (-1073741824)) {
    if (c >= 3) {
      scan_delimiter(ctx, mem_max - 12, false);
      scan_delimiter(ctx, mem_max - 12, false);
    }
    if (!(c % 3))
      scan_dimen(ctx, false, false, false);
    print_nl(ctx, 262);
    print(ctx, 1152);
    ctx->help_ptr = 3;
    ctx->help_line[2] = 1153;
    ctx->help_line[1] = 1154;
    ctx->help_line[0] = 1155;
    error(ctx);
    return;
  }
  ctx->cur_list.aux_field.int_ = get_node(ctx, 6);
  ctx->mem[ctx->cur_list.aux_field.int_ - mem_min].hh.U2.b0 = 25;
  ctx->mem[ctx->cur_list.aux_field.int_ - mem_min].hh.U2.b1 = 0;
  ctx->mem[ctx->cur_list.aux_field.int_ - mem_min + 2].hh.rh = 3;
  ctx->mem[ctx->cur_list.aux_field.int_ - mem_min + 2].hh.lh =
      ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh;
  ctx->mem[ctx->cur_list.aux_field.int_ - mem_min + 3].hh = ctx->empty_field;
  ctx->mem[ctx->cur_list.aux_field.int_ - mem_min + 4].qqqq =
      ctx->null_delimiter;
  ctx->mem[ctx->cur_list.aux_field.int_ - mem_min + 5].qqqq =
      ctx->null_delimiter;
  ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh = -1073741824;
  ctx->cur_list.tail_field = ctx->cur_list.head_field;
  if (c >= 3) {
    scan_delimiter(ctx, ctx->cur_list.aux_field.int_ + 4, false);
    scan_delimiter(ctx, ctx->cur_list.aux_field.int_ + 5, false);
  }
  switch (c % 3) {
  case 0:
    scan_dimen(ctx, false, false, false);
    ctx->mem[ctx->cur_list.aux_field.int_ - mem_min + 1].int_ = ctx->cur_val;
    break;
  case 1:
    ctx->mem[ctx->cur_list.aux_field.int_ - mem_min + 1].int_ = 1073741824;
    break;
  case 2:
    ctx->mem[ctx->cur_list.aux_field.int_ - mem_min + 1].int_ = 0;
    break;
  }
}

void math_left_right(ctex_t *ctx) {
  halfword p;
  small_number t = ctx->cur_chr;
  if ((t == 31) && (ctx->cur_group != 16)) {
    if (ctx->cur_group != 15) {
      off_save(ctx);
      return;
    }
    scan_delimiter(ctx, mem_max - 12, false);
    print_nl(ctx, 262);
    print(ctx, 776);
    print_esc(ctx, 876);
    ctx->help_ptr = 1;
    ctx->help_line[0] = 1156;
    error(ctx);
    return;
  }
  p = new_noad(ctx);
  ctx->mem[p - mem_min].hh.U2.b0 = t;
  scan_delimiter(ctx, p + 1, false);
  if (t == 30) {
    push_math(ctx, 16);
    ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh = p;
    ctx->cur_list.tail_field = p;
    return;
  }
  p = fin_mlist(ctx, p);
  unsave(ctx);
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_noad(ctx);
  ctx->cur_list.tail_field = ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 = 23;
  ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.rh = 3;
  ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.lh = p;
}

void after_math(ctex_t *ctx) {
  bool_t l = false, danger = false;
  integer m;
  halfword p, a, b;
  scaled w, z, e, q, d, s;
  small_number g1, g2;
  halfword r, t;
  if ((ctx->fnt_infos.font_params[ctx->eqtb[10837].hh.rh] < 22) ||
      (ctx->fnt_infos.font_params[ctx->eqtb[10853].hh.rh] < 22) ||
      (ctx->fnt_infos.font_params[ctx->eqtb[10869].hh.rh] < 22)) {
    print_nl(ctx, 262);
    print(ctx, 1157);
    ctx->help_ptr = 3;
    ctx->help_line[2] = 1158;
    ctx->help_line[1] = 1159;
    ctx->help_line[0] = 1160;
    error(ctx);
    flush_math(ctx);
    danger = true;
  } else if ((ctx->fnt_infos.font_params[ctx->eqtb[10838].hh.rh] < 13) ||
             (ctx->fnt_infos.font_params[ctx->eqtb[10854].hh.rh] < 13) ||
             (ctx->fnt_infos.font_params[ctx->eqtb[10870].hh.rh] < 13)) {
    print_nl(ctx, 262);
    print(ctx, 1161);
    ctx->help_ptr = 3;
    ctx->help_line[2] = 1162;
    ctx->help_line[1] = 1163;
    ctx->help_line[0] = 1164;
    error(ctx);
    flush_math(ctx);
    danger = true;
  }
  m = ctx->cur_list.mode_field;
  p = fin_mlist(ctx, -1073741824);
  if (ctx->cur_list.mode_field == (-m)) {
    get_x_token(ctx);
    if (ctx->cur_cmd != 3) {
      print_nl(ctx, 262);
      print(ctx, 1165);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 1166;
      ctx->help_line[0] = 1167;
      back_error(ctx);
    }
    ctx->cur_mlist = p;
    ctx->cur_style = 2;
    ctx->mlist_penalties = false;
    mlist_to_hlist(ctx);
    a = hpack(ctx, ctx->mem[mem_max - mem_min - 3].hh.rh, 0, 1);
    unsave(ctx);
    --ctx->save_ptr;
    if (ctx->save_stack[ctx->save_ptr].int_ == 1)
      l = true;
    danger = false;
    if ((ctx->fnt_infos.font_params[ctx->eqtb[10837].hh.rh] < 22) ||
        (ctx->fnt_infos.font_params[ctx->eqtb[10853].hh.rh] < 22) ||
        (ctx->fnt_infos.font_params[ctx->eqtb[10869].hh.rh] < 22)) {
      print_nl(ctx, 262);
      print(ctx, 1157);
      ctx->help_ptr = 3;
      ctx->help_line[2] = 1158;
      ctx->help_line[1] = 1159;
      ctx->help_line[0] = 1160;
      error(ctx);
      flush_math(ctx);
      danger = true;
    } else if ((ctx->fnt_infos.font_params[ctx->eqtb[10838].hh.rh] < 13) ||
               (ctx->fnt_infos.font_params[ctx->eqtb[10854].hh.rh] < 13) ||
               (ctx->fnt_infos.font_params[ctx->eqtb[10870].hh.rh] < 13)) {
      print_nl(ctx, 262);
      print(ctx, 1161);
      ctx->help_ptr = 3;
      ctx->help_line[2] = 1162;
      ctx->help_line[1] = 1163;
      ctx->help_line[0] = 1164;
      error(ctx);
      flush_math(ctx);
      danger = true;
    }
    m = ctx->cur_list.mode_field;
    p = fin_mlist(ctx, -1073741824);
  } else {
    a = -1073741824;
  }
  if (m < 0) {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        new_math(ctx, ctx->eqtb[12731].int_, 0);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->cur_mlist = p;
    ctx->cur_style = 2;
    ctx->mlist_penalties = (ctx->cur_list.mode_field > 0);
    mlist_to_hlist(ctx);
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        ctx->mem[mem_max - mem_min - 3].hh.rh;
    while (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh != (-1073741824))
      ctx->cur_list.tail_field =
          ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        new_math(ctx, ctx->eqtb[12731].int_, 1);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->cur_list.aux_field.hh.lh = 1000;
    unsave(ctx);
    return;
  }
  if (a == (-1073741824)) {
    get_x_token(ctx);
    if (ctx->cur_cmd != 3) {
      print_nl(ctx, 262);
      print(ctx, 1165);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 1166;
      ctx->help_line[0] = 1167;
      back_error(ctx);
    }
  }
  ctx->cur_mlist = p;
  ctx->cur_style = 0;
  ctx->mlist_penalties = false;
  mlist_to_hlist(ctx);
  p = ctx->mem[mem_max - mem_min - 3].hh.rh;
  ctx->adjust_tail = mem_max - 5;
  b = hpack(ctx, p, 0, 1);
  p = ctx->mem[b - mem_min + 5].hh.rh;
  t = ctx->adjust_tail;
  ctx->adjust_tail = -1073741824;
  w = ctx->mem[b - mem_min + 1].int_;
  z = ctx->eqtb[12744].int_;
  s = ctx->eqtb[12745].int_;
  if ((a == (-1073741824)) || danger) {
    e = 0;
    q = 0;
  } else {
    e = ctx->mem[a - mem_min + 1].int_;
    q = e +
        ctx->font_info[ctx->fnt_infos.param_base[ctx->eqtb[10837].hh.rh] + 6]
            .int_;
  }
  if (w + q > z) {
    if (e && ((w - ctx->total_shrink[0] + q <= z) || ctx->total_shrink[1] ||
              ctx->total_shrink[2] || ctx->total_shrink[3])) {
      free_node(ctx, b, 7);
      b = hpack(ctx, p, z - q, 0);
    } else {
      e = 0;
      if (w > z) {
        free_node(ctx, b, 7);
        b = hpack(ctx, p, z, 0);
      }
    }
    w = ctx->mem[b - mem_min + 1].int_;
  }
  d = half(ctx, z - w);
  if ((e > 0) && (d < (e * 2))) {
    d = half(ctx, z - w - e);
    if (p != (-1073741824)) {
      if (p < ctx->hi_mem_min) {
        if (ctx->mem[p - mem_min].hh.U2.b0 == 10)
          d = 0;
      }
    }
  }
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
      new_penalty(ctx, ctx->eqtb[12174].int_);
  ctx->cur_list.tail_field = ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  if ((d + s <= ctx->eqtb[12743].int_) || l) {
    g1 = 3;
    g2 = 4;
  } else {
    g1 = 5;
    g2 = 6;
  }
  if (l && (!e)) {
    ctx->mem[a - mem_min + 4].int_ = s;
    append_to_vlist(ctx, a);
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        new_penalty(ctx, 10000);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  } else {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        new_param_glue(ctx, g1);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  }
  if (e) {
    r = new_kern(ctx, z - w - e - d);
    if (l) {
      ctx->mem[a - mem_min].hh.rh = r;
      ctx->mem[r - mem_min].hh.rh = b;
      b = a;
      d = 0;
    } else {
      ctx->mem[b - mem_min].hh.rh = r;
      ctx->mem[r - mem_min].hh.rh = a;
    }
    b = hpack(ctx, b, 0, 1);
  }
  ctx->mem[b - mem_min + 4].int_ = s + d;
  append_to_vlist(ctx, b);
  if ((a != (-1073741824)) && (!e) && (!l)) {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        new_penalty(ctx, 10000);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->mem[a - mem_min + 4].int_ = s + z - ctx->mem[a - mem_min + 1].int_;
    append_to_vlist(ctx, a);
    g2 = 0;
  }
  if (t != (mem_max - 5)) {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        ctx->mem[mem_max - mem_min - 5].hh.rh;
    ctx->cur_list.tail_field = t;
  }
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
      new_penalty(ctx, ctx->eqtb[12175].int_);
  ctx->cur_list.tail_field = ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  if (g2 > 0) {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        new_param_glue(ctx, g2);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  }
  resume_after_display(ctx);
}

void resume_after_display(ctex_t *ctx) {
  if (ctx->cur_group != 15)
    confusion(ctx, 1168);
  unsave(ctx);
  ctx->cur_list.pg_field += 3;
  push_nest(ctx);
  ctx->cur_list.mode_field = 102;
  ctx->cur_list.aux_field.hh.lh = 1000;
  if (ctx->eqtb[12213].int_ <= 0) {
    ctx->cur_lang = 0;
  } else if (ctx->eqtb[12213].int_ > 255)
    ctx->cur_lang = 0;
  else
    ctx->cur_lang = ctx->eqtb[12213].int_;
  ctx->cur_list.aux_field.hh.rh = ctx->cur_lang;
  ctx->cur_list.pg_field = (((norm_min(ctx, ctx->eqtb[12214].int_) * 64) +
                             norm_min(ctx, ctx->eqtb[12215].int_)) *
                            65536) +
                           ctx->cur_lang;
  get_x_token(ctx);
  if (ctx->cur_cmd != 10)
    back_input(ctx);
  if (ctx->nest_ptr == 1)
    build_page(ctx);
}

void get_r_token(ctex_t *ctx) {
_L20:
  do {
    get_token(ctx);
  } while (ctx->cur_tok == 2592);
  if (ctx->cur_cs && (ctx->cur_cs <= 9514))
    return;
  print_nl(ctx, 262);
  print(ctx, 1183);
  ctx->help_ptr = 5;
  ctx->help_line[4] = 1184;
  ctx->help_line[3] = 1185;
  ctx->help_line[2] = 1186;
  ctx->help_line[1] = 1187;
  ctx->help_line[0] = 1188;
  if (!ctx->cur_cs)
    back_input(ctx);
  ctx->cur_tok = 13609;
  ins_error(ctx);
  goto _L20;
}

void trap_zero_glue(ctex_t *ctx) {
  if (ctx->mem[ctx->cur_val - mem_min + 1].int_ ||
      ctx->mem[ctx->cur_val - mem_min + 2].int_ ||
      ctx->mem[ctx->cur_val - mem_min + 3].int_)
    return;
  ++ctx->mem[-mem_min].hh.rh;
  delete_glue_ref(ctx, ctx->cur_val);
  ctx->cur_val = 0;
}

void do_register_command(ctex_t *ctx, small_number a) {
  halfword l, r, s;
  char p;
  halfword q = ctx->cur_cmd;
  if (q != 89) {
    get_x_token(ctx);
    if ((ctx->cur_cmd >= 73) && (ctx->cur_cmd <= 76)) {
      l = ctx->cur_chr;
      p = ctx->cur_cmd - 73;
      goto _L40;
    }
    if (ctx->cur_cmd != 89) {
      print_nl(ctx, 262);
      print(ctx, 685);
      print_cmd_chr(ctx, ctx->cur_cmd, ctx->cur_chr);
      print(ctx, 686);
      print_cmd_chr(ctx, q, 0);
      ctx->help_ptr = 1;
      ctx->help_line[0] = 1209;
      error(ctx);
      goto _L10;
    }
  }
  p = ctx->cur_chr;
  scan_eight_bit_int(ctx);
  switch (p) {
  case 0:
    l = ctx->cur_val + 12218;
    break;
  case 1:
    l = ctx->cur_val + 12751;
    break;
  case 2:
    l = ctx->cur_val + 9800;
    break;
  case 3:
    l = ctx->cur_val + 10056;
    break;
  }
_L40:
  if (q == 89)
    scan_optional_equals(ctx);
  else
    scan_keyword(ctx, 1205);
  ctx->arith_error = false;
  if (q < 91) {
    if (p < 2) {
      if (!p)
        scan_int(ctx);
      else
        scan_dimen(ctx, false, false, false);
      if (q == 90)
        ctx->cur_val += ctx->eqtb[l].int_;
    } else {
      scan_glue(ctx, p);
      if (q == 90) {
        q = new_spec(ctx, ctx->cur_val);
        r = ctx->eqtb[l].hh.rh;
        delete_glue_ref(ctx, ctx->cur_val);
        ctx->mem[q - mem_min + 1].int_ += ctx->mem[r - mem_min + 1].int_;
        if (!ctx->mem[q - mem_min + 2].int_)
          ctx->mem[q - mem_min].hh.U2.b0 = 0;
        if (ctx->mem[q - mem_min].hh.U2.b0 == ctx->mem[r - mem_min].hh.U2.b0) {
          ctx->mem[q - mem_min + 2].int_ += ctx->mem[r - mem_min + 2].int_;
        } else if ((ctx->mem[q - mem_min].hh.U2.b0 <
                    ctx->mem[r - mem_min].hh.U2.b0) &&
                   ctx->mem[r - mem_min + 2].int_) {
          ctx->mem[q - mem_min + 2].int_ = ctx->mem[r - mem_min + 2].int_;
          ctx->mem[q - mem_min].hh.U2.b0 = ctx->mem[r - mem_min].hh.U2.b0;
        }
        if (!ctx->mem[q - mem_min + 3].int_)
          ctx->mem[q - mem_min].hh.U2.b1 = 0;
        if (ctx->mem[q - mem_min].hh.U2.b1 == ctx->mem[r - mem_min].hh.U2.b1) {
          ctx->mem[q - mem_min + 3].int_ += ctx->mem[r - mem_min + 3].int_;
        } else if ((ctx->mem[q - mem_min].hh.U2.b1 <
                    ctx->mem[r - mem_min].hh.U2.b1) &&
                   ctx->mem[r - mem_min + 3].int_) {
          ctx->mem[q - mem_min + 3].int_ = ctx->mem[r - mem_min + 3].int_;
          ctx->mem[q - mem_min].hh.U2.b1 = ctx->mem[r - mem_min].hh.U2.b1;
        }
        ctx->cur_val = q;
      }
    }
  } else {
    scan_int(ctx);
    if (p < 2) {
      if (q == 91) {
        if (!p)
          ctx->cur_val =
              mult_and_add(ctx, ctx->eqtb[l].int_, ctx->cur_val, 0, 2147483647);
        else
          ctx->cur_val =
              mult_and_add(ctx, ctx->eqtb[l].int_, ctx->cur_val, 0, 1073741823);
      } else {
        ctx->cur_val = x_over_n(ctx, ctx->eqtb[l].int_, ctx->cur_val);
      }
    } else {
      s = ctx->eqtb[l].hh.rh;
      r = new_spec(ctx, s);
      if (q == 91) {
        ctx->mem[r - mem_min + 1].int_ = mult_and_add(
            ctx, ctx->mem[s - mem_min + 1].int_, ctx->cur_val, 0, 1073741823);
        ctx->mem[r - mem_min + 2].int_ = mult_and_add(
            ctx, ctx->mem[s - mem_min + 2].int_, ctx->cur_val, 0, 1073741823);
        ctx->mem[r - mem_min + 3].int_ = mult_and_add(
            ctx, ctx->mem[s - mem_min + 3].int_, ctx->cur_val, 0, 1073741823);
      } else {
        ctx->mem[r - mem_min + 1].int_ =
            x_over_n(ctx, ctx->mem[s - mem_min + 1].int_, ctx->cur_val);
        ctx->mem[r - mem_min + 2].int_ =
            x_over_n(ctx, ctx->mem[s - mem_min + 2].int_, ctx->cur_val);
        ctx->mem[r - mem_min + 3].int_ =
            x_over_n(ctx, ctx->mem[s - mem_min + 3].int_, ctx->cur_val);
      }
      ctx->cur_val = r;
    }
  }
  if (ctx->arith_error) {
    print_nl(ctx, 262);
    print(ctx, 1206);
    ctx->help_ptr = 2;
    ctx->help_line[1] = 1207;
    ctx->help_line[0] = 1208;
    if (p >= 2)
      delete_glue_ref(ctx, ctx->cur_val);
    error(ctx);
    goto _L10;
  }
  if (p < 2) {
    if (a >= 4)
      geq_word_define(ctx, l, ctx->cur_val);
    else
      eq_word_define(ctx, l, ctx->cur_val);
  } else {
    trap_zero_glue(ctx);
    if (a >= 4)
      geq_define(ctx, l, 117, ctx->cur_val);
    else
      eq_define(ctx, l, 117, ctx->cur_val);
  }
_L10:;
}

void alter_aux(ctex_t *ctx) {
  halfword c;
  if (ctx->cur_chr != abs(ctx->cur_list.mode_field)) {
    report_illegal_case(ctx);
    return;
  }
  c = ctx->cur_chr;
  scan_optional_equals(ctx);
  if (c == 1) {
    scan_dimen(ctx, false, false, false);
    ctx->cur_list.aux_field.int_ = ctx->cur_val;
    return;
  }
  scan_int(ctx);
  if ((ctx->cur_val > 0) && (ctx->cur_val <= 32767)) {
    ctx->cur_list.aux_field.hh.lh = ctx->cur_val;
    return;
  }
  print_nl(ctx, 262);
  print(ctx, 1212);
  ctx->help_ptr = 1;
  ctx->help_line[0] = 1213;
  int_error(ctx, ctx->cur_val);
}

void alter_prev_graf(ctex_t *ctx) {
  int p;
  ctx->nest[ctx->nest_ptr] = ctx->cur_list;
  p = ctx->nest_ptr;
  while (abs(ctx->nest[p].mode_field) != 1)
    --p;
  scan_optional_equals(ctx);
  scan_int(ctx);
  if (ctx->cur_val >= 0) {
    ctx->nest[p].pg_field = ctx->cur_val;
    ctx->cur_list = ctx->nest[ctx->nest_ptr];
    return;
  }
  print_nl(ctx, 262);
  print(ctx, 954);
  print_esc(ctx, 532);
  ctx->help_ptr = 1;
  ctx->help_line[0] = 1214;
  int_error(ctx, ctx->cur_val);
}

void alter_page_so_far(ctex_t *ctx) {
  char c = ctx->cur_chr;
  scan_optional_equals(ctx);
  scan_dimen(ctx, false, false, false);
  ctx->page_so_far[c] = ctx->cur_val;
}

void alter_integer(ctex_t *ctx) {
  char c = ctx->cur_chr;
  scan_optional_equals(ctx);
  scan_int(ctx);
  if (!c)
    ctx->dead_cycles = ctx->cur_val;
  else
    ctx->insert_penalties = ctx->cur_val;
}

void alter_box_dimen(ctex_t *ctx) {
  uint8_t b;
  small_number c = ctx->cur_chr;
  scan_eight_bit_int(ctx);
  b = ctx->cur_val;
  scan_optional_equals(ctx);
  scan_dimen(ctx, false, false, false);
  if (ctx->eqtb[b + 10578].hh.rh != (-1073741824))
    ctx->mem[ctx->eqtb[b + 10578].hh.rh + c - mem_min].int_ = ctx->cur_val;
}

void new_font(ctex_t *ctx, small_number a) {
  halfword u;
  scaled s;
  internal_font_number f;
  str_number t;
  char old_setting;
  str_number flushable_string;
  internal_font_number N;
  if (!ctx->job_name)
    open_log_file(ctx);
  get_r_token(ctx);
  u = ctx->cur_cs;
  if (u >= 514) {
    t = ctx->hash[u - 514].rh;
  } else if (u >= 257) {
    if (u == 513)
      t = 1218;
    else
      t = u - 257;
  } else {
    old_setting = ctx->selector;
    ctx->selector = 21;
    print(ctx, 1218);
    print(ctx, u - 1);
    ctx->selector = old_setting;
    if (ctx->pool_ptr + 1 > pool_size)
      overflow(ctx, 257, pool_size - ctx->init_pool_ptr);
    t = make_string(ctx);
  }
  if (a >= 4)
    geq_define(ctx, u, 87, 0);
  else
    eq_define(ctx, u, 87, 0);
  scan_optional_equals(ctx);
  scan_file_name(ctx);
  ctx->name_in_progress = true;
  if (scan_keyword(ctx, 1219)) {
    scan_dimen(ctx, false, false, false);
    s = ctx->cur_val;
    if ((s <= 0) || (s >= 134217728)) {
      print_nl(ctx, 262);
      print(ctx, 1221);
      print_scaled(ctx, s);
      print(ctx, 1222);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 1223;
      ctx->help_line[0] = 1224;
      error(ctx);
      s = 655360;
    }
  } else if (scan_keyword(ctx, 1220)) {
    scan_int(ctx);
    s = -ctx->cur_val;
    if ((ctx->cur_val <= 0) || (ctx->cur_val > 32768)) {
      print_nl(ctx, 262);
      print(ctx, 552);
      ctx->help_ptr = 1;
      ctx->help_line[0] = 553;
      int_error(ctx, ctx->cur_val);
      s = -1000;
    }
  } else {
    s = -1000;
  }
  ctx->name_in_progress = false;
  flushable_string = ctx->str_ptr - 1;
  for (N = ctx->font_ptr, f = 1; f <= N; ++f) {
    if (str_eq_str(ctx, ctx->fnt_infos.font_name[f], ctx->cur_name) &
        str_eq_str(ctx, ctx->fnt_infos.font_area[f], ctx->cur_area)) {
      if (ctx->cur_name == flushable_string) {
        --ctx->str_ptr;
        ctx->pool_ptr = ctx->str_start[ctx->str_ptr];
        ctx->cur_name = ctx->fnt_infos.font_name[f];
      }
      if (s > 0) {
        if (s == ctx->fnt_infos.font_size[f])
          goto _L50;
      } else if (ctx->fnt_infos.font_size[f] ==
                 xn_over_d(ctx, ctx->fnt_infos.font_dsize[f], -s, 1000))
        goto _L50;
    }
  }
  f = read_font_info(ctx, u, ctx->cur_name, ctx->cur_area, s);
_L50:
  ctx->eqtb[u].hh.rh = f;
  ctx->eqtb[f + 9524] = ctx->eqtb[u];
  ctx->hash[f + 9010].rh = t;
}

void new_interaction(ctex_t *ctx) {
  print_ln(ctx);
  ctx->interaction = ctx->cur_chr;
  if (!ctx->interaction)
    ctx->selector = 16;
  else
    ctx->selector = 17;
  if (ctx->log_opened)
    ctx->selector += 2;
}

void prefixed_command(ctex_t *ctx) {
  small_number a = 0;
  internal_font_number f;
  halfword j;
  font_index k;
  halfword p, q;
  integer n;
  bool_t e;
  while (ctx->cur_cmd == 93) {
    if (!((a / ctx->cur_chr) & 1))
      a += ctx->cur_chr;
    do {
      get_x_token(ctx);
    } while ((ctx->cur_cmd == 10) || (!ctx->cur_cmd));
    if (ctx->cur_cmd > 70)
      continue;
    print_nl(ctx, 262);
    print(ctx, 1178);
    print_cmd_chr(ctx, ctx->cur_cmd, ctx->cur_chr);
    print_char(ctx, 39);
    ctx->help_ptr = 1;
    ctx->help_line[0] = 1179;
    back_error(ctx);
    goto _L10;
  }
  if ((ctx->cur_cmd != 97) && (a & 3)) {
    print_nl(ctx, 262);
    print(ctx, 685);
    print_esc(ctx, 1170);
    print(ctx, 1180);
    print_esc(ctx, 1171);
    print(ctx, 1181);
    print_cmd_chr(ctx, ctx->cur_cmd, ctx->cur_chr);
    print_char(ctx, 39);
    ctx->help_ptr = 1;
    ctx->help_line[0] = 1182;
    error(ctx);
  }
  if (ctx->eqtb[12206].int_) {
    if (ctx->eqtb[12206].int_ < 0) {
      if (a >= 4)
        a -= 4;
    } else if (a < 4)
      a += 4;
  }
  switch (ctx->cur_cmd) {
  case 87:
    if (a >= 4)
      geq_define(ctx, 10834, 120, ctx->cur_chr);
    else
      eq_define(ctx, 10834, 120, ctx->cur_chr);
    break;
  case 97:
    if ((ctx->cur_chr & 1) && (a < 4) && (ctx->eqtb[12206].int_ >= 0))
      a += 4;
    e = (ctx->cur_chr >= 2);
    get_r_token(ctx);
    p = ctx->cur_cs;
    q = scan_toks(ctx, true, e);
    if (a >= 4)
      geq_define(ctx, p, (a & 3) + 111, ctx->def_ref);
    else
      eq_define(ctx, p, (a & 3) + 111, ctx->def_ref);
    break;
  case 94:
    n = ctx->cur_chr;
    get_r_token(ctx);
    p = ctx->cur_cs;
    if (!n) {
      do {
        get_token(ctx);
      } while (ctx->cur_cmd == 10);
      if (ctx->cur_tok == 3133) {
        get_token(ctx);
        if (ctx->cur_cmd == 10)
          get_token(ctx);
      }
    } else {
      get_token(ctx);
      q = ctx->cur_tok;
      get_token(ctx);
      back_input(ctx);
      ctx->cur_tok = q;
      back_input(ctx);
    }
    if (ctx->cur_cmd >= 111)
      ++ctx->mem[ctx->cur_chr - mem_min].hh.lh;
    if (a >= 4)
      geq_define(ctx, p, ctx->cur_cmd, ctx->cur_chr);
    else
      eq_define(ctx, p, ctx->cur_cmd, ctx->cur_chr);
    break;
  case 95:
    n = ctx->cur_chr;
    get_r_token(ctx);
    p = ctx->cur_cs;
    if (a >= 4)
      geq_define(ctx, p, 0, 256);
    else
      eq_define(ctx, p, 0, 256);
    scan_optional_equals(ctx);
    switch (n) {
    case 0:
      scan_char_num(ctx);
      if (a >= 4)
        geq_define(ctx, p, 68, ctx->cur_val);
      else
        eq_define(ctx, p, 68, ctx->cur_val);
      break;
    case 1:
      scan_fifteen_bit_int(ctx);
      if (a >= 4)
        geq_define(ctx, p, 69, ctx->cur_val);
      else
        eq_define(ctx, p, 69, ctx->cur_val);
      break;
    default:
      scan_eight_bit_int(ctx);
      switch (n) {
      case 2:
        if (a >= 4)
          geq_define(ctx, p, 73, ctx->cur_val + 12218);
        else
          eq_define(ctx, p, 73, ctx->cur_val + 12218);
        break;
      case 3:
        if (a >= 4)
          geq_define(ctx, p, 74, ctx->cur_val + 12751);
        else
          eq_define(ctx, p, 74, ctx->cur_val + 12751);
        break;
      case 4:
        if (a >= 4)
          geq_define(ctx, p, 75, ctx->cur_val + 9800);
        else
          eq_define(ctx, p, 75, ctx->cur_val + 9800);
        break;
      case 5:
        if (a >= 4)
          geq_define(ctx, p, 76, ctx->cur_val + 10056);
        else
          eq_define(ctx, p, 76, ctx->cur_val + 10056);
        break;
      case 6:
        if (a >= 4)
          geq_define(ctx, p, 72, ctx->cur_val + 10322);
        else
          eq_define(ctx, p, 72, ctx->cur_val + 10322);
        break;
      }
      break;
    }
    break;
  case 96:
    scan_int(ctx);
    n = ctx->cur_val;
    if (!scan_keyword(ctx, 841)) {
      print_nl(ctx, 262);
      print(ctx, 1072);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 1199;
      ctx->help_line[0] = 1200;
      error(ctx);
    }
    get_r_token(ctx);
    p = ctx->cur_cs;
    read_toks(ctx, n, p);
    if (a >= 4)
      geq_define(ctx, p, 111, ctx->cur_val);
    else
      eq_define(ctx, p, 111, ctx->cur_val);
    break;
  case 71:
  case 72:
    q = ctx->cur_cs;
    if (ctx->cur_cmd == 71) {
      scan_eight_bit_int(ctx);
      p = ctx->cur_val + 10322;
    } else {
      p = ctx->cur_chr;
    }
    scan_optional_equals(ctx);
    do {
      get_x_token(ctx);
    } while ((ctx->cur_cmd == 10) || (!ctx->cur_cmd));
    if (ctx->cur_cmd != 1) {
      if (ctx->cur_cmd == 71) {
        scan_eight_bit_int(ctx);
        ctx->cur_cmd = 72;
        ctx->cur_chr = ctx->cur_val + 10322;
      }
      if (ctx->cur_cmd == 72) {
        q = ctx->eqtb[ctx->cur_chr].hh.rh;
        if (q == (-1073741824)) {
          if (a >= 4)
            geq_define(ctx, p, 101, -1073741824);
          else
            eq_define(ctx, p, 101, -1073741824);
        } else {
          ++ctx->mem[q - mem_min].hh.lh;
          if (a >= 4)
            geq_define(ctx, p, 111, q);
          else
            eq_define(ctx, p, 111, q);
        }
        goto _L30;
      }
    }
    back_input(ctx);
    ctx->cur_cs = q;
    q = scan_toks(ctx, false, false);
    if (ctx->mem[ctx->def_ref - mem_min].hh.rh == (-1073741824)) {
      if (a >= 4)
        geq_define(ctx, p, 101, -1073741824);
      else
        eq_define(ctx, p, 101, -1073741824);
      ctx->mem[ctx->def_ref - mem_min].hh.rh = ctx->avail;
      ctx->avail = ctx->def_ref;
    } else {
      if (p == 10313) {
        ctx->mem[q - mem_min].hh.rh = get_avail(ctx);
        q = ctx->mem[q - mem_min].hh.rh;
        ctx->mem[q - mem_min].hh.lh = 637;
        q = get_avail(ctx);
        ctx->mem[q - mem_min].hh.lh = 379;
        ctx->mem[q - mem_min].hh.rh = ctx->mem[ctx->def_ref - mem_min].hh.rh;
        ctx->mem[ctx->def_ref - mem_min].hh.rh = q;
      }
      if (a >= 4)
        geq_define(ctx, p, 111, ctx->def_ref);
      else
        eq_define(ctx, p, 111, ctx->def_ref);
    }
    break;
  case 73:
    p = ctx->cur_chr;
    scan_optional_equals(ctx);
    scan_int(ctx);
    if (a >= 4)
      geq_word_define(ctx, p, ctx->cur_val);
    else
      eq_word_define(ctx, p, ctx->cur_val);
    break;
  case 74:
    p = ctx->cur_chr;
    scan_optional_equals(ctx);
    scan_dimen(ctx, false, false, false);
    if (a >= 4)
      geq_word_define(ctx, p, ctx->cur_val);
    else
      eq_word_define(ctx, p, ctx->cur_val);
    break;
  case 75:
  case 76:
    p = ctx->cur_chr;
    n = ctx->cur_cmd;
    scan_optional_equals(ctx);
    if (n == 76)
      scan_glue(ctx, 3);
    else
      scan_glue(ctx, 2);
    trap_zero_glue(ctx);
    if (a >= 4)
      geq_define(ctx, p, 117, ctx->cur_val);
    else
      eq_define(ctx, p, 117, ctx->cur_val);
    break;
  case 85:
    if (ctx->cur_chr == 10883) {
      n = 15;
    } else if (ctx->cur_chr == 11907) {
      n = 32768;
    } else if (ctx->cur_chr == 11651) {
      n = 32767;
    } else if (ctx->cur_chr == 12474)
      n = 16777215;
    else
      n = 255;
    p = ctx->cur_chr;
    scan_char_num(ctx);
    p += ctx->cur_val;
    scan_optional_equals(ctx);
    scan_int(ctx);
    if (((ctx->cur_val < 0) && (p < 12474)) || (ctx->cur_val > n)) {
      print_nl(ctx, 262);
      print(ctx, 1201);
      print_int(ctx, ctx->cur_val);
      if (p < 12474)
        print(ctx, 1202);
      else
        print(ctx, 1203);
      print_int(ctx, n);
      ctx->help_ptr = 1;
      ctx->help_line[0] = 1204;
      error(ctx);
      ctx->cur_val = 0;
    }
    if (p < 11907) {
      if (a >= 4)
        geq_define(ctx, p, 120, ctx->cur_val);
      else
        eq_define(ctx, p, 120, ctx->cur_val);
    } else if (p < 12474) {
      if (a >= 4)
        geq_define(ctx, p, 120, ctx->cur_val - 1073741824);
      else
        eq_define(ctx, p, 120, ctx->cur_val - 1073741824);
    } else if (a >= 4)
      geq_word_define(ctx, p, ctx->cur_val);
    else
      eq_word_define(ctx, p, ctx->cur_val);
    break;
  case 86:
    p = ctx->cur_chr;
    scan_four_bit_int(ctx);
    p += ctx->cur_val;
    scan_optional_equals(ctx);
    scan_font_ident(ctx);
    if (a >= 4)
      geq_define(ctx, p, 120, ctx->cur_val);
    else
      eq_define(ctx, p, 120, ctx->cur_val);
    break;
  case 89:
  case 90:
  case 91:
  case 92:
    do_register_command(ctx, a);
    break;
  case 98:
    scan_eight_bit_int(ctx);
    if (a >= 4)
      n = ctx->cur_val + 256;
    else
      n = ctx->cur_val;
    scan_optional_equals(ctx);
    if (ctx->set_box_allowed) {
      scan_box(ctx, n + 1073741824);
    } else {
      print_nl(ctx, 262);
      print(ctx, 680);
      print_esc(ctx, 536);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 1210;
      ctx->help_line[0] = 1211;
      error(ctx);
    }
    break;
  case 79:
    alter_aux(ctx);
    break;
  case 80:
    alter_prev_graf(ctx);
    break;
  case 81:
    alter_page_so_far(ctx);
    break;
  case 82:
    alter_integer(ctx);
    break;
  case 83:
    alter_box_dimen(ctx);
    break;
  case 84:
    scan_optional_equals(ctx);
    scan_int(ctx);
    n = ctx->cur_val;
    if (n <= 0) {
      p = -1073741824;
    } else {
      p = get_node(ctx, (n * 2) + 1);
      ctx->mem[p - mem_min].hh.lh = n;
      for (j = 1; j <= n; ++j) {
        scan_dimen(ctx, false, false, false);
        ctx->mem[p + (j * 2) - mem_min - 1].int_ = ctx->cur_val;
        scan_dimen(ctx, false, false, false);
        ctx->mem[p + (j * 2) - mem_min].int_ = ctx->cur_val;
      }
    }
    if (a >= 4)
      geq_define(ctx, 10312, 118, p);
    else
      eq_define(ctx, 10312, 118, p);
    break;
  case 99:
    if (ctx->cur_chr == 1) {
      new_patterns(ctx);
      goto _L30;
    } else {
      new_hyph_exceptions(ctx);
      goto _L30;
    }
    break;
  case 77:
    find_font_dimen(ctx, true);
    k = ctx->cur_val;
    scan_optional_equals(ctx);
    scan_dimen(ctx, false, false, false);
    ctx->font_info[k].int_ = ctx->cur_val;
    break;
  case 78:
    n = ctx->cur_chr;
    scan_font_ident(ctx);
    f = ctx->cur_val;
    scan_optional_equals(ctx);
    scan_int(ctx);
    if (!n)
      ctx->fnt_infos.hyphen_char[f] = ctx->cur_val;
    else
      ctx->fnt_infos.skew_char[f] = ctx->cur_val;
    break;
  case 88:
    new_font(ctx, a);
    break;
  case 100:
    new_interaction(ctx);
    break;
  default:
    confusion(ctx, 1177);
    break;
  }
_L30:
  if (ctx->after_token) {
    ctx->cur_tok = ctx->after_token;
    back_input(ctx);
    ctx->after_token = 0;
  }
_L10:;
}

void do_assignments(ctex_t *ctx) {
  while (true) {
    do {
      get_x_token(ctx);
    } while ((ctx->cur_cmd == 10) || (!ctx->cur_cmd));
    if (ctx->cur_cmd <= 70)
      goto _L10;
    ctx->set_box_allowed = false;
    prefixed_command(ctx);
    ctx->set_box_allowed = true;
  }
_L10:;
}

void open_or_close_in(ctex_t *ctx) {
  char n;
  char c = ctx->cur_chr;
  scan_four_bit_int(ctx);
  n = ctx->cur_val;
  if (ctx->read_open[n] != 2) {
    a_close(ctx, &ctx->read_file[n]);
    ctx->read_open[n] = 2;
  }
  if (!c)
    return;
  scan_optional_equals(ctx);
  scan_file_name(ctx);
  if (ctx->cur_ext == 338)
    ctx->cur_ext = 790;
  pack_file_name(ctx, ctx->cur_name, ctx->cur_area, ctx->cur_ext);
  if (a_open_in(ctx, &ctx->read_file[n]))
    ctx->read_open[n] = 1;
}

void issue_message(ctex_t *ctx) {
  char old_setting;
  str_number s;
  char c = ctx->cur_chr;
  ctx->mem[mem_max - mem_min - 12].hh.rh = scan_toks(ctx, false, true);
  old_setting = ctx->selector;
  ctx->selector = 21;
  token_show(ctx, ctx->def_ref);
  ctx->selector = old_setting;
  flush_list(ctx, ctx->def_ref);
  if (ctx->pool_ptr + 1 > pool_size)
    overflow(ctx, 257, pool_size - ctx->init_pool_ptr);
  s = make_string(ctx);
  if (!c) {
    if (ctx->term_offset + ctx->str_start[s + 1] - ctx->str_start[s] >
        max_print_line - 2) {
      print_ln(ctx);
    } else if ((ctx->term_offset > 0) || (ctx->file_offset > 0))
      print_char(ctx, 32);
    slow_print(ctx, s);
    fflush(ctx->term_out);
    errno = 0;
  } else {
    print_nl(ctx, 262);
    print(ctx, 338);
    slow_print(ctx, s);
    if (ctx->eqtb[10321].hh.rh != (-1073741824)) {
      ctx->use_err_help = true;
    } else if (ctx->long_help_seen) {
      ctx->help_ptr = 1;
      ctx->help_line[0] = 1231;
    } else {
      if (ctx->interaction < 3)
        ctx->long_help_seen = true;
      ctx->help_ptr = 4;
      ctx->help_line[3] = 1232;
      ctx->help_line[2] = 1233;
      ctx->help_line[1] = 1234;
      ctx->help_line[0] = 1235;
    }
    error(ctx);
    ctx->use_err_help = false;
  }
  --ctx->str_ptr;
  ctx->pool_ptr = ctx->str_start[ctx->str_ptr];
}

void shift_case(ctex_t *ctx) {
  halfword t;
  uint8_t c;
  halfword b = ctx->cur_chr;
  halfword p = scan_toks(ctx, false, false);
  p = ctx->mem[ctx->def_ref - mem_min].hh.rh;
  while (p != (-1073741824)) {
    t = ctx->mem[p - mem_min].hh.lh;
    if (t < 4352) {
      c = t & 255;
      if (ctx->eqtb[b + c].hh.rh)
        ctx->mem[p - mem_min].hh.lh = t - c + ctx->eqtb[b + c].hh.rh;
    }
    p = ctx->mem[p - mem_min].hh.rh;
  }
  begin_token_list(ctx, ctx->mem[ctx->def_ref - mem_min].hh.rh, 3);
  ctx->mem[ctx->def_ref - mem_min].hh.rh = ctx->avail;
  ctx->avail = ctx->def_ref;
}

void show_whatever(ctex_t *ctx) {
  halfword p;
  switch (ctx->cur_chr) {
  case 3:
    begin_diagnostic(ctx);
    show_activities(ctx);
    break;
  case 1:
    scan_eight_bit_int(ctx);
    begin_diagnostic(ctx);
    print_nl(ctx, 1253);
    print_int(ctx, ctx->cur_val);
    print_char(ctx, 61);
    if (ctx->eqtb[ctx->cur_val + 10578].hh.rh == (-1073741824))
      print(ctx, 410);
    else
      show_box(ctx, ctx->eqtb[ctx->cur_val + 10578].hh.rh);
    break;
  case 0:
    get_token(ctx);
    print_nl(ctx, 1247);
    if (ctx->cur_cs) {
      sprint_cs(ctx, ctx->cur_cs);
      print_char(ctx, 61);
    }
    print_meaning(ctx);
    goto _L50;
    break;
  default:
    p = the_toks(ctx);
    print_nl(ctx, 1247);
    token_show(ctx, mem_max - 3);
    flush_list(ctx, ctx->mem[mem_max - mem_min - 3].hh.rh);
    goto _L50;
    break;
  }
  end_diagnostic(ctx, true);
  print_nl(ctx, 262);
  print(ctx, 1254);
  if (ctx->selector == 19) {
    if (ctx->eqtb[12192].int_ <= 0) {
      ctx->selector = 17;
      print(ctx, 1255);
      ctx->selector = 19;
    }
  }
_L50:
  if (ctx->interaction < 3) {
    ctx->help_ptr = 0;
    --ctx->error_count;
  } else if (ctx->eqtb[12192].int_ > 0) {
    ctx->help_ptr = 3;
    ctx->help_line[2] = 1242;
    ctx->help_line[1] = 1243;
    ctx->help_line[0] = 1244;
  } else {
    ctx->help_ptr = 5;
    ctx->help_line[4] = 1242;
    ctx->help_line[3] = 1243;
    ctx->help_line[2] = 1244;
    ctx->help_line[1] = 1245;
    ctx->help_line[0] = 1246;
  }
  error(ctx);
}

void store_fmt_file(ctex_t *ctx) {
  integer j, k, l, x = 0;
  halfword p = 0, q;
  four_quarters w;
  int N;
  halfword N1;
  if (ctx->save_ptr) {
    print_nl(ctx, 262);
    print(ctx, 1257);
    ctx->help_ptr = 1;
    ctx->help_line[0] = 1258;
    if (ctx->interaction == 3)
      ctx->interaction = 2;
    if (ctx->log_opened)
      error(ctx);
    ctx->history = 3;
    jump_out(ctx);
  }
  ctx->selector = 21;
  print(ctx, 1271);
  print(ctx, ctx->job_name);
  print_char(ctx, 32);
  print_int(ctx, ctx->eqtb[12186].int_);
  print_char(ctx, 46);
  print_int(ctx, ctx->eqtb[12185].int_);
  print_char(ctx, 46);
  print_int(ctx, ctx->eqtb[12184].int_);
  print_char(ctx, 41);
  if (!ctx->interaction)
    ctx->selector = 18;
  else
    ctx->selector = 19;
  if (ctx->pool_ptr + 1 > pool_size)
    overflow(ctx, 257, pool_size - ctx->init_pool_ptr);
  ctx->format_ident = make_string(ctx);
  pack_job_name(ctx, 785);
  while (!w_open_out(ctx, &ctx->fmt_file))
    prompt_file_name(ctx, 1272, 785);
  print_nl(ctx, 1273);
  slow_print(ctx, w_make_name_string(ctx, ctx->fmt_file));
  --ctx->str_ptr;
  ctx->pool_ptr = ctx->str_start[ctx->str_ptr];
  print_nl(ctx, 338);
  slow_print(ctx, ctx->format_ident);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      117275187;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ = 0;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      mem_max;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      13006;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      7649;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ = 307;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->pool_ptr;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->str_ptr;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  for (N = ctx->str_ptr, k = 0; k <= N; ++k) {
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->str_start[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  }
  k = 0;
  while (k + 4 < ctx->pool_ptr) {
    w.b0 = ctx->str_pool[k];
    w.b1 = ctx->str_pool[k + 1];
    w.b2 = ctx->str_pool[k + 2];
    w.b3 = ctx->str_pool[k + 3];
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->qqqq = w;
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    k += 4;
  }
  k = ctx->pool_ptr - 4;
  w.b0 = ctx->str_pool[k];
  w.b1 = ctx->str_pool[k + 1];
  w.b2 = ctx->str_pool[k + 2];
  w.b3 = ctx->str_pool[k + 3];
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->qqqq = w;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  print_ln(ctx);
  print_int(ctx, ctx->str_ptr);
  print(ctx, 1259);
  print_int(ctx, ctx->pool_ptr);
  sort_avail(ctx);
  ctx->var_used = 0;
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->lo_mem_max;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->rover;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  q = ctx->rover;
  do {
    for (k = p; k <= (q + 1); ++k)
      fwrite((&ctx->mem[k - mem_min]), sizeof(memory_word), 1, ctx->fmt_file);

    x += q - p + 2;
    ctx->var_used += q - p;
    p = q + ctx->mem[q - mem_min].hh.lh;
    q = ctx->mem[q - mem_min + 1].hh.rh;
  } while (q != ctx->rover);
  ctx->var_used += ctx->lo_mem_max - p;
  ctx->dyn_used = ctx->mem_end - ctx->hi_mem_min + 1;
  for (N = ctx->lo_mem_max, k = p; k <= N; ++k)
    fwrite((&ctx->mem[k - mem_min]), sizeof(memory_word), 1, ctx->fmt_file);
  x += ctx->lo_mem_max - p + 1;
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->hi_mem_min;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->avail;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  for (N = ctx->mem_end, k = ctx->hi_mem_min; k <= N; ++k)
    fwrite((&ctx->mem[k - mem_min]), sizeof(memory_word), 1, ctx->fmt_file);
  x += ctx->mem_end - ctx->hi_mem_min + 1;
  p = ctx->avail;
  while (p != (-1073741824)) {
    --ctx->dyn_used;
    p = ctx->mem[p - mem_min].hh.rh;
  }
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->var_used;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->dyn_used;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  print_ln(ctx);
  print_int(ctx, x);
  print(ctx, 1260);
  print_int(ctx, ctx->var_used);
  print_char(ctx, 38);
  print_int(ctx, ctx->dyn_used);
  k = 1;
  do {
    j = k;
    while (j < 12162) {
      if ((ctx->eqtb[j].hh.rh == ctx->eqtb[j + 1].hh.rh) &&
          (ctx->eqtb[j].hh.U2.b0 == ctx->eqtb[j + 1].hh.U2.b0) &&
          (ctx->eqtb[j].hh.U2.b1 == ctx->eqtb[j + 1].hh.U2.b1))
        goto _L41;
      ++j;
    }
    l = 12163;
    goto _L31;
  _L41:
    ++j;
    l = j;
    while (j < 12162) {
      if ((ctx->eqtb[j].hh.rh != ctx->eqtb[j + 1].hh.rh) ||
          (ctx->eqtb[j].hh.U2.b0 != ctx->eqtb[j + 1].hh.U2.b0) ||
          (ctx->eqtb[j].hh.U2.b1 != ctx->eqtb[j + 1].hh.U2.b1))
        goto _L31;
      ++j;
    }
  _L31:
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        l - k;
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    while (k < l) {
      fwrite((&ctx->eqtb[k]), sizeof(memory_word), 1, ctx->fmt_file);
      ++k;
    }
    k = j + 1;
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        k - l;
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  } while (k != 12163);
  do {
    j = k;
    while (j < 13006) {
      if (ctx->eqtb[j].int_ == ctx->eqtb[j + 1].int_)
        goto _L42;
      ++j;
    }
    l = 13007;
    goto _L32;
  _L42:
    ++j;
    l = j;
    while (j < 13006) {
      if (ctx->eqtb[j].int_ != ctx->eqtb[j + 1].int_)
        goto _L32;
      ++j;
    }
  _L32:
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        l - k;
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    while (k < l) {
      fwrite((&ctx->eqtb[k]), sizeof(memory_word), 1, ctx->fmt_file);
      ++k;
    }
    k = j + 1;
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        k - l;
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  } while (k <= 13006);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->par_loc;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->write_loc;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->hash_used;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  ctx->cs_count = 9513 - ctx->hash_used;
  for (N1 = ctx->hash_used, p = 514; p <= N1; ++p) {
    if (ctx->hash[p - 514].rh) {
      readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
          p;
      writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
      readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->hh =
          ctx->hash[p - 514];
      writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
      ++ctx->cs_count;
    }
  }
  for (p = ctx->hash_used + 1; p <= 9780; ++p) {
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->hh =
        ctx->hash[p - 514];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  }
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->cs_count;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  print_ln(ctx);
  print_int(ctx, ctx->cs_count);
  print(ctx, 1261);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->fmem_ptr;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  for (N = ctx->fmem_ptr, k = 0; k < N; ++k)
    fwrite((&ctx->font_info[k]), sizeof(memory_word), 1, ctx->fmt_file);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->font_ptr;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  for (N = ctx->font_ptr, k = 0; k <= N; ++k) {
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->qqqq =
        ctx->fnt_infos.font_check[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.font_size[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.font_dsize[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.font_params[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.hyphen_char[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.skew_char[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.font_name[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.font_area[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.font_bc[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.font_ec[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.char_base[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.width_base[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.height_base[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.depth_base[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.italic_base[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.lig_kern_base[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.kern_base[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.exten_base[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.param_base[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.font_glue[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.bchar_label[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.font_bchar[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->fnt_infos.font_false_bchar[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    print_nl(ctx, 1264);
    print_esc(ctx, ctx->hash[k + 9010].rh);
    print_char(ctx, 61);
    print_file_name(ctx, ctx->fnt_infos.font_name[k],
                    ctx->fnt_infos.font_area[k], 338);
    if (ctx->fnt_infos.font_size[k] != ctx->fnt_infos.font_dsize[k]) {
      print(ctx, 741);
      print_scaled(ctx, ctx->fnt_infos.font_size[k]);
      print(ctx, 397);
    }
  }
  print_ln(ctx);
  print_int(ctx, ctx->fmem_ptr - 7);
  print(ctx, 1262);
  print_int(ctx, ctx->font_ptr);
  print(ctx, 1263);
  if (ctx->font_ptr != 1)
    print_char(ctx, 115);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->hyph_count;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  for (k = 0; k <= 307; ++k) {
    if (ctx->hyph_word[k]) {
      readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
          k;
      writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
      readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
          ctx->hyph_word[k];
      writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
      readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
          ctx->hyph_list[k];
      writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    }
  }
  print_ln(ctx);
  print_int(ctx, ctx->hyph_count);
  print(ctx, 1265);
  if (ctx->hyph_count != 1)
    print_char(ctx, 115);
  if (ctx->trie_not_ready)
    init_trie(ctx);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->trie_max;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  for (N = ctx->trie_max, k = 0; k <= N; ++k) {
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->hh =
        ctx->trie[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  }
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->trie_op_ptr;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  for (N = ctx->trie_op_ptr, k = 1; k <= N; ++k) {
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->hyf_distance[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->hyf_num[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
        ctx->hyf_next[k];
    writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  }
  print_nl(ctx, 1266);
  print_int(ctx, ctx->trie_max);
  print(ctx, 1267);
  print_int(ctx, ctx->trie_op_ptr);
  print(ctx, 1268);
  if (ctx->trie_op_ptr != 1)
    print_char(ctx, 115);
  print(ctx, 1269);
  print_int(ctx, trie_op_size);
  for (k = 255; k >= 0; --k) {
    if (ctx->trie_used[k] > 0) {
      print_nl(ctx, 799);
      print_int(ctx, ctx->trie_used[k]);
      print(ctx, 1270);
      print_int(ctx, k);
      readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
          k;
      writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
      readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
          ctx->trie_used[k];
      writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    }
  }
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->interaction;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      ctx->format_ident;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_ =
      69069;
  writeU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  ctx->eqtb[12194].int_ = 0;
  w_close(ctx, &ctx->fmt_file);
}

void new_whatsit(ctex_t *ctx, small_number s, small_number w) {
  halfword p = get_node(ctx, w);
  ctx->mem[p - mem_min].hh.U2.b0 = 8;
  ctx->mem[p - mem_min].hh.U2.b1 = s;
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = p;
  ctx->cur_list.tail_field = p;
}

void new_write_whatsit(ctex_t *ctx, small_number w) {
  new_whatsit(ctx, ctx->cur_chr, w);
  if (w != 2) {
    scan_four_bit_int(ctx);
  } else {
    scan_int(ctx);
    if (ctx->cur_val < 0) {
      ctx->cur_val = 17;
    } else if (ctx->cur_val > 15)
      ctx->cur_val = 16;
  }
  ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.lh = ctx->cur_val;
}

void do_extension(ctex_t *ctx) {
  integer k;
  halfword p;
  switch (ctx->cur_chr) {
  case 0:
    new_write_whatsit(ctx, 3);
    scan_optional_equals(ctx);
    scan_file_name(ctx);
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.rh = ctx->cur_name;
    ctx->mem[ctx->cur_list.tail_field - mem_min + 2].hh.lh = ctx->cur_area;
    ctx->mem[ctx->cur_list.tail_field - mem_min + 2].hh.rh = ctx->cur_ext;
    break;
  case 1:
    k = ctx->cur_cs;
    new_write_whatsit(ctx, 2);
    ctx->cur_cs = k;
    p = scan_toks(ctx, false, false);
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.rh = ctx->def_ref;
    break;
  case 2:
    new_write_whatsit(ctx, 2);
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.rh = -1073741824;
    break;
  case 3:
    new_whatsit(ctx, 3, 2);
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.lh = -1073741824;
    p = scan_toks(ctx, false, true);
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.rh = ctx->def_ref;
    break;
  case 4:
    get_x_token(ctx);
    if ((ctx->cur_cmd == 59) && (ctx->cur_chr <= 2)) {
      p = ctx->cur_list.tail_field;
      do_extension(ctx);
      out_what(ctx, ctx->cur_list.tail_field);
      flush_node_list(ctx, ctx->cur_list.tail_field);
      ctx->cur_list.tail_field = p;
      ctx->mem[p - mem_min].hh.rh = -1073741824;
    } else {
      back_input(ctx);
    }
    break;
  case 5:
    if (abs(ctx->cur_list.mode_field) != 102) {
      report_illegal_case(ctx);
    } else {
      new_whatsit(ctx, 4, 2);
      scan_int(ctx);
      if (ctx->cur_val <= 0) {
        ctx->cur_list.aux_field.hh.rh = 0;
      } else if (ctx->cur_val > 255)
        ctx->cur_list.aux_field.hh.rh = 0;
      else
        ctx->cur_list.aux_field.hh.rh = ctx->cur_val;
      ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.rh =
          ctx->cur_list.aux_field.hh.rh;
      ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.U2.b0 =
          norm_min(ctx, ctx->eqtb[12214].int_);
      ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.U2.b1 =
          norm_min(ctx, ctx->eqtb[12215].int_);
    }
    break;
  default:
    confusion(ctx, 1290);
    break;
  }
}

void fix_language(ctex_t *ctx) {
  ASCII_code l;
  if (ctx->eqtb[12213].int_ <= 0) {
    l = 0;
  } else if (ctx->eqtb[12213].int_ > 255)
    l = 0;
  else
    l = ctx->eqtb[12213].int_;
  if (l == ctx->cur_list.aux_field.hh.rh)
    return;
  new_whatsit(ctx, 4, 2);
  ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.rh = l;
  ctx->cur_list.aux_field.hh.rh = l;
  ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.U2.b0 =
      norm_min(ctx, ctx->eqtb[12214].int_);
  ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.U2.b1 =
      norm_min(ctx, ctx->eqtb[12215].int_);
}

void handle_right_brace(ctex_t *ctx) {
  halfword p, q;
  scaled d;
  integer f;
  switch (ctx->cur_group) {
  case 1:
    unsave(ctx);
    break;
  case 0:
    print_nl(ctx, 262);
    print(ctx, 1043);
    ctx->help_ptr = 2;
    ctx->help_line[1] = 1044;
    ctx->help_line[0] = 1045;
    error(ctx);
    break;
  case 14:
  case 15:
  case 16:
    extra_right_brace(ctx);
    break;
  case 2:
    package(ctx, 0);
    break;
  case 3:
    ctx->adjust_tail = mem_max - 5;
    package(ctx, 0);
    break;
  case 4:
    end_graf(ctx);
    package(ctx, 0);
    break;
  case 5:
    end_graf(ctx);
    package(ctx, 4);
    break;
  case 11:
    end_graf(ctx);
    q = ctx->eqtb[9792].hh.rh;
    ++ctx->mem[q - mem_min].hh.rh;
    d = ctx->eqtb[12736].int_;
    f = ctx->eqtb[12205].int_;
    unsave(ctx);
    --ctx->save_ptr;
    p = vpackage(ctx, ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh, 0, 1,
                 1073741823);
    pop_nest(ctx);
    if (ctx->save_stack[ctx->save_ptr].int_ < 255) {
      ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = get_node(ctx, 5);
      ctx->cur_list.tail_field =
          ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
      ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 = 3;
      ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 =
          ctx->save_stack[ctx->save_ptr].int_;
      ctx->mem[ctx->cur_list.tail_field - mem_min + 3].int_ =
          ctx->mem[p - mem_min + 3].int_ + ctx->mem[p - mem_min + 2].int_;
      ctx->mem[ctx->cur_list.tail_field - mem_min + 4].hh.lh =
          ctx->mem[p - mem_min + 5].hh.rh;
      ctx->mem[ctx->cur_list.tail_field - mem_min + 4].hh.rh = q;
      ctx->mem[ctx->cur_list.tail_field - mem_min + 2].int_ = d;
      ctx->mem[ctx->cur_list.tail_field - mem_min + 1].int_ = f;
    } else {
      ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = get_node(ctx, 2);
      ctx->cur_list.tail_field =
          ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
      ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 = 5;
      ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 = 0;
      ctx->mem[ctx->cur_list.tail_field - mem_min + 1].int_ =
          ctx->mem[p - mem_min + 5].hh.rh;
      delete_glue_ref(ctx, q);
    }
    free_node(ctx, p, 7);
    if (!ctx->nest_ptr)
      build_page(ctx);
    break;
  case 8:
    if ((ctx->cur_input.loc_field != (-1073741824)) ||
        ((ctx->cur_input.index_field != 6) &&
         (ctx->cur_input.index_field != 3))) {
      print_nl(ctx, 262);
      print(ctx, 1009);
      ctx->help_ptr = 2;
      ctx->help_line[1] = 1010;
      ctx->help_line[0] = 1011;
      error(ctx);
      do {
        get_token(ctx);
      } while (ctx->cur_input.loc_field != (-1073741824));
    }
    end_token_list(ctx);
    end_graf(ctx);
    unsave(ctx);
    ctx->output_active = false;
    ctx->insert_penalties = 0;
    if (ctx->eqtb[10833].hh.rh != (-1073741824)) {
      print_nl(ctx, 262);
      print(ctx, 1012);
      print_esc(ctx, 409);
      print_int(ctx, 255);
      ctx->help_ptr = 3;
      ctx->help_line[2] = 1013;
      ctx->help_line[1] = 1014;
      ctx->help_line[0] = 1015;
      box_error(ctx, 255);
    }
    if (ctx->cur_list.tail_field != ctx->cur_list.head_field) {
      ctx->mem[ctx->page_tail - mem_min].hh.rh =
          ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh;
      ctx->page_tail = ctx->cur_list.tail_field;
    }
    if (ctx->mem[mem_max - mem_min - 2].hh.rh != (-1073741824)) {
      if (ctx->mem[mem_max - mem_min - 1].hh.rh == (-1073741824))
        ctx->nest[0].tail_field = ctx->page_tail;
      ctx->mem[ctx->page_tail - mem_min].hh.rh =
          ctx->mem[mem_max - mem_min - 1].hh.rh;
      ctx->mem[mem_max - mem_min - 1].hh.rh =
          ctx->mem[mem_max - mem_min - 2].hh.rh;
      ctx->mem[mem_max - mem_min - 2].hh.rh = -1073741824;
      ctx->page_tail = mem_max - 2;
    }
    pop_nest(ctx);
    build_page(ctx);
    break;
  case 10:
    build_discretionary(ctx);
    break;
  case 6:
    back_input(ctx);
    ctx->cur_tok = 13610;
    print_nl(ctx, 262);
    print(ctx, 625);
    print_esc(ctx, 898);
    print(ctx, 626);
    ctx->help_ptr = 1;
    ctx->help_line[0] = 1124;
    ins_error(ctx);
    break;
  case 7:
    end_graf(ctx);
    unsave(ctx);
    align_peek(ctx);
    break;
  case 12:
    end_graf(ctx);
    unsave(ctx);
    ctx->save_ptr -= 2;
    (p = vpackage(ctx, ctx->mem[ctx->cur_list.head_field - mem_min].hh.rh,
                  ctx->save_stack[ctx->save_ptr + 1].int_,
                  ctx->save_stack[ctx->save_ptr].int_, 1073741823));
    pop_nest(ctx);
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_noad(ctx);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 = 29;
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.rh = 2;
    ctx->mem[ctx->cur_list.tail_field - mem_min + 1].hh.lh = p;
    break;
  case 13:
    build_choices(ctx);
    break;
  case 9:
    unsave(ctx);
    --ctx->save_ptr;
    ctx->mem[ctx->save_stack[ctx->save_ptr].int_ - mem_min].hh.rh = 3;
    p = fin_mlist(ctx, -1073741824);
    ctx->mem[ctx->save_stack[ctx->save_ptr].int_ - mem_min].hh.lh = p;
    if (p != (-1073741824)) {
      if (ctx->mem[p - mem_min].hh.rh == (-1073741824)) {
        if (ctx->mem[p - mem_min].hh.U2.b0 == 16) {
          if (!ctx->mem[p - mem_min + 3].hh.rh) {
            if (!ctx->mem[p - mem_min + 2].hh.rh) {
              ctx->mem[ctx->save_stack[ctx->save_ptr].int_ - mem_min].hh =
                  ctx->mem[p - mem_min + 1].hh;
              free_node(ctx, p, 4);
            }
          }
        } else if (ctx->mem[p - mem_min].hh.U2.b0 == 28) {
          if (ctx->save_stack[ctx->save_ptr].int_ ==
              (ctx->cur_list.tail_field + 1)) {
            if (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 == 16) {
              q = ctx->cur_list.head_field;
              while (ctx->mem[q - mem_min].hh.rh != ctx->cur_list.tail_field)
                q = ctx->mem[q - mem_min].hh.rh;
              ctx->mem[q - mem_min].hh.rh = p;
              free_node(ctx, ctx->cur_list.tail_field, 4);
              ctx->cur_list.tail_field = p;
            }
          }
        }
      }
    }
    break;
  default:
    confusion(ctx, 1046);
    break;
  }
}

void main_control(ctex_t *ctx) {
  integer t;
  if (ctx->eqtb[10319].hh.rh != (-1073741824))
    begin_token_list(ctx, ctx->eqtb[10319].hh.rh, 12);
_L60:
  get_x_token(ctx);
_L21:
  if (ctx->interrupt) {
    if (ctx->OK_to_interrupt) {
      back_input(ctx);
      if (ctx->interrupt)
        pause_for_instructions(ctx);
      goto _L60;
    }
  }
  if (ctx->eqtb[12199].int_ > 0)
    show_cur_cmd_chr(ctx);
  switch (abs(ctx->cur_list.mode_field) + ctx->cur_cmd) {
  case 113:
  case 114:
  case 170:
    goto _L70;
    break;
  case 118:
    scan_char_num(ctx);
    ctx->cur_chr = ctx->cur_val;
    goto _L70;
    break;
  case 167:
    get_x_token(ctx);
    if ((ctx->cur_cmd == 11) || (ctx->cur_cmd == 12) || (ctx->cur_cmd == 68) ||
        (ctx->cur_cmd == 16))
      ctx->cancel_boundary = true;
    goto _L21;
    break;
  case 112:
    if (ctx->cur_list.aux_field.hh.lh == 1000)
      goto _L120;
    app_space(ctx);
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
      get_x_token(ctx);
    } while (ctx->cur_cmd == 10);
    goto _L21;
    break;
  case 15:
    if (its_all_over(ctx))
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
    report_illegal_case(ctx);
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
    insert_dollar_sign(ctx);
    break;
  case 37:
  case 137:
  case 238:
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = scan_rule_spec(ctx);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    if (abs(ctx->cur_list.mode_field) == 1) {
      ctx->cur_list.aux_field.int_ = -65536000;
    } else if (abs(ctx->cur_list.mode_field) == 102)
      ctx->cur_list.aux_field.hh.lh = 1000;
    break;
  case 28:
  case 128:
  case 229:
  case 231:
    append_glue(ctx);
    break;
  case 30:
  case 131:
  case 232:
  case 233:
    append_kern(ctx);
    break;
  case 2:
  case 103:
    new_save_level(ctx, 1);
    break;
  case 62:
  case 163:
  case 264:
    new_save_level(ctx, 14);
    break;
  case 63:
  case 164:
  case 265:
    if (ctx->cur_group == 14)
      unsave(ctx);
    else
      off_save(ctx);
    break;
  case 3:
  case 104:
  case 205:
    handle_right_brace(ctx);
    break;
  case 22:
  case 124:
  case 225:
    t = ctx->cur_chr;
    scan_dimen(ctx, false, false, false);
    if (!t)
      scan_box(ctx, ctx->cur_val);
    else
      scan_box(ctx, -ctx->cur_val);
    break;
  case 32:
  case 133:
  case 234:
    scan_box(ctx, ctx->cur_chr + 1073742237);
    break;
  case 21:
  case 122:
  case 223:
    begin_box(ctx, 0);
    break;
  case 44:
    new_graf(ctx, ctx->cur_chr > 0);
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
    back_input(ctx);
    new_graf(ctx, true);
    break;
  case 145:
  case 246:
    indent_in_hmode(ctx);
    break;
  case 14:
    normal_paragraph(ctx);
    if (ctx->cur_list.mode_field > 0)
      build_page(ctx);
    break;
  case 115:
    if (ctx->align_state < 0)
      off_save(ctx);
    end_graf(ctx);
    if (ctx->cur_list.mode_field == 1)
      build_page(ctx);
    break;
  case 116:
  case 129:
  case 138:
  case 126:
  case 134:
    head_for_vmode(ctx);
    break;
  case 38:
  case 139:
  case 240:
  case 140:
  case 241:
    begin_insert_or_adjust(ctx);
    break;
  case 19:
  case 120:
  case 221:
    make_mark(ctx);
    break;
  case 43:
  case 144:
  case 245:
    append_penalty(ctx);
    break;
  case 26:
  case 127:
  case 228:
    delete_last(ctx);
    break;
  case 25:
  case 125:
  case 226:
    unpackage(ctx);
    break;
  case 146:
    append_italic_correction(ctx);
    break;
  case 247:
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_kern(ctx, 0);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    break;
  case 149:
  case 250:
    append_discretionary(ctx);
    break;
  case 147:
    make_accent(ctx);
    break;
  case 6:
  case 107:
  case 208:
  case 5:
  case 106:
  case 207:
    align_error(ctx);
    break;
  case 35:
  case 136:
  case 237:
    no_align_error(ctx);
    break;
  case 64:
  case 165:
  case 266:
    omit_error(ctx);
    break;
  case 33:
  case 135:
    init_align(ctx);
    break;
  case 235:
    if (privileged(ctx)) {
      if (ctx->cur_group == 15)
        init_align(ctx);
      else
        off_save(ctx);
    }
    break;
  case 10:
  case 111:
    do_endv(ctx);
    break;
  case 68:
  case 169:
  case 270:
    cs_error(ctx);
    break;
  case 105:
    init_math(ctx);
    break;
  case 251:
    if (privileged(ctx)) {
      if (ctx->cur_group == 15)
        start_eq_no(ctx);
      else
        off_save(ctx);
    }
    break;
  case 204:
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_noad(ctx);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    back_input(ctx);
    scan_math(ctx, ctx->cur_list.tail_field + 1);
    break;
  case 214:
  case 215:
  case 271:
    set_math_char(ctx, ctx->eqtb[ctx->cur_chr + 11907].hh.rh + 1073741824);
    break;
  case 219:
    scan_char_num(ctx);
    ctx->cur_chr = ctx->cur_val;
    set_math_char(ctx, ctx->eqtb[ctx->cur_chr + 11907].hh.rh + 1073741824);
    break;
  case 220:
    scan_fifteen_bit_int(ctx);
    set_math_char(ctx, ctx->cur_val);
    break;
  case 272:
    set_math_char(ctx, ctx->cur_chr);
    break;
  case 218:
    scan_twenty_seven_bit_int(ctx);
    set_math_char(ctx, ctx->cur_val / 4096);
    break;
  case 253:
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_noad(ctx);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b0 = ctx->cur_chr;
    scan_math(ctx, ctx->cur_list.tail_field + 1);
    break;
  case 254:
    math_limit_switch(ctx);
    break;
  case 269:
    math_radical(ctx);
    break;
  case 248:
  case 249:
    math_ac(ctx);
    break;
  case 259:
    scan_spec(ctx, 12, false);
    normal_paragraph(ctx);
    push_nest(ctx);
    ctx->cur_list.mode_field = -1;
    ctx->cur_list.aux_field.int_ = -65536000;
    if (ctx->eqtb[10318].hh.rh != (-1073741824))
      begin_token_list(ctx, ctx->eqtb[10318].hh.rh, 11);
    break;
  case 256:
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
        new_style(ctx, ctx->cur_chr);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    break;
  case 258:
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_glue(ctx, 0);
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 = 98;
    break;
  case 257:
    append_choices(ctx);
    break;
  case 211:
  case 210:
    sub_sup(ctx);
    break;
  case 255:
    math_fraction(ctx);
    break;
  case 252:
    math_left_right(ctx);
    break;
  case 206:
    if (ctx->cur_group == 15)
      after_math(ctx);
    else
      off_save(ctx);
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
    prefixed_command(ctx);
    break;
  case 41:
  case 142:
  case 243:
    get_token(ctx);
    ctx->after_token = ctx->cur_tok;
    break;
  case 42:
  case 143:
  case 244:
    get_token(ctx);
    save_for_after(ctx, ctx->cur_tok);
    break;
  case 61:
  case 162:
  case 263:
    open_or_close_in(ctx);
    break;
  case 59:
  case 160:
  case 261:
    issue_message(ctx);
    break;
  case 58:
  case 159:
  case 260:
    shift_case(ctx);
    break;
  case 20:
  case 121:
  case 222:
    show_whatever(ctx);
    break;
  case 60:
  case 161:
  case 262:
    do_extension(ctx);
    break;
  }
  goto _L60;
_L70:
  ctx->main_s = ctx->eqtb[ctx->cur_chr + 11651].hh.rh;
  if (ctx->main_s == 1000) {
    ctx->cur_list.aux_field.hh.lh = 1000;
  } else if (ctx->main_s < 1000) {
    if (ctx->main_s > 0)
      ctx->cur_list.aux_field.hh.lh = ctx->main_s;
  } else if (ctx->cur_list.aux_field.hh.lh < 1000)
    ctx->cur_list.aux_field.hh.lh = 1000;
  else
    ctx->cur_list.aux_field.hh.lh = ctx->main_s;
  ctx->main_f = ctx->eqtb[10834].hh.rh;
  ctx->bchar = ctx->fnt_infos.font_bchar[ctx->main_f];
  ctx->false_bchar = ctx->fnt_infos.font_false_bchar[ctx->main_f];
  if (ctx->cur_list.mode_field > 0) {
    if (ctx->eqtb[12213].int_ != ctx->cur_list.aux_field.hh.rh)
      fix_language(ctx);
  }
  ctx->lig_stack = ctx->avail;
  if (ctx->lig_stack == (-1073741824)) {
    ctx->lig_stack = get_avail(ctx);
  } else {
    ctx->avail = ctx->mem[ctx->lig_stack - mem_min].hh.rh;
    ctx->mem[ctx->lig_stack - mem_min].hh.rh = -1073741824;
  }
  ctx->mem[ctx->lig_stack - mem_min].hh.U2.b0 = ctx->main_f;
  ctx->cur_l = ctx->cur_chr;
  ctx->mem[ctx->lig_stack - mem_min].hh.U2.b1 = ctx->cur_l;
  ctx->cur_q = ctx->cur_list.tail_field;
  if (ctx->cancel_boundary) {
    ctx->cancel_boundary = false;
    ctx->main_k = 0;
  } else {
    ctx->main_k = ctx->fnt_infos.bchar_label[ctx->main_f];
  }
  if (!ctx->main_k)
    goto _L92;
  ctx->cur_r = ctx->cur_l;
  ctx->cur_l = 256;
  goto _L111;
_L80:
  if (ctx->cur_l < 256) {
    if (ctx->mem[ctx->cur_q - mem_min].hh.rh > (-1073741824)) {
      if (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 ==
          ctx->fnt_infos.hyphen_char[ctx->main_f])
        ctx->ins_disc = true;
    }
    if (ctx->ligature_present) {
      ctx->main_p = new_ligature(ctx, ctx->main_f, ctx->cur_l,
                                 ctx->mem[ctx->cur_q - mem_min].hh.rh);
      if (ctx->lft_hit) {
        ctx->mem[ctx->main_p - mem_min].hh.U2.b1 = 2;
        ctx->lft_hit = false;
      }
      if (ctx->rt_hit) {
        if (ctx->lig_stack == (-1073741824)) {
          ++ctx->mem[ctx->main_p - mem_min].hh.U2.b1;
          ctx->rt_hit = false;
        }
      }
      ctx->mem[ctx->cur_q - mem_min].hh.rh = ctx->main_p;
      ctx->cur_list.tail_field = ctx->main_p;
      ctx->ligature_present = false;
    }
    if (ctx->ins_disc) {
      ctx->ins_disc = false;
      if (ctx->cur_list.mode_field > 0) {
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_disc(ctx);
        ctx->cur_list.tail_field =
            ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
      }
    }
  }
_L90:
  if (ctx->lig_stack == (-1073741824))
    goto _L21;
  ctx->cur_q = ctx->cur_list.tail_field;
  ctx->cur_l = ctx->mem[ctx->lig_stack - mem_min].hh.U2.b1;
_L91:
  if (ctx->lig_stack < ctx->hi_mem_min)
    goto _L95;
_L92:
  if ((ctx->cur_chr < ctx->fnt_infos.font_bc[ctx->main_f]) ||
      (ctx->cur_chr > ctx->fnt_infos.font_ec[ctx->main_f])) {
    char_warning(ctx, ctx->main_f, ctx->cur_chr);
    ctx->mem[ctx->lig_stack - mem_min].hh.rh = ctx->avail;
    ctx->avail = ctx->lig_stack;
    goto _L60;
  }
  ctx->main_i =
      ctx->font_info[ctx->fnt_infos.char_base[ctx->main_f] + ctx->cur_l].qqqq;
  if (ctx->main_i.b0 <= 0) {
    char_warning(ctx, ctx->main_f, ctx->cur_chr);
    ctx->mem[ctx->lig_stack - mem_min].hh.rh = ctx->avail;
    ctx->avail = ctx->lig_stack;
    goto _L60;
  }
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = ctx->lig_stack;
  ctx->cur_list.tail_field = ctx->lig_stack;
_L100:
  get_next(ctx);
  if (ctx->cur_cmd == 11)
    goto _L101;
  if (ctx->cur_cmd == 12)
    goto _L101;
  if (ctx->cur_cmd == 68)
    goto _L101;
  x_token(ctx);
  if (ctx->cur_cmd == 11)
    goto _L101;
  if (ctx->cur_cmd == 12)
    goto _L101;
  if (ctx->cur_cmd == 68)
    goto _L101;
  if (ctx->cur_cmd == 16) {
    scan_char_num(ctx);
    ctx->cur_chr = ctx->cur_val;
    goto _L101;
  }
  if (ctx->cur_cmd == 65)
    ctx->bchar = 256;
  ctx->cur_r = ctx->bchar;
  ctx->lig_stack = -1073741824;
  goto _L110;
_L101:
  ctx->main_s = ctx->eqtb[ctx->cur_chr + 11651].hh.rh;
  if (ctx->main_s == 1000) {
    ctx->cur_list.aux_field.hh.lh = 1000;
  } else if (ctx->main_s < 1000) {
    if (ctx->main_s > 0)
      ctx->cur_list.aux_field.hh.lh = ctx->main_s;
  } else if (ctx->cur_list.aux_field.hh.lh < 1000)
    ctx->cur_list.aux_field.hh.lh = 1000;
  else
    ctx->cur_list.aux_field.hh.lh = ctx->main_s;
  ctx->lig_stack = ctx->avail;
  if (ctx->lig_stack == (-1073741824)) {
    ctx->lig_stack = get_avail(ctx);
  } else {
    ctx->avail = ctx->mem[ctx->lig_stack - mem_min].hh.rh;
    ctx->mem[ctx->lig_stack - mem_min].hh.rh = -1073741824;
  }
  ctx->mem[ctx->lig_stack - mem_min].hh.U2.b0 = ctx->main_f;
  ctx->cur_r = ctx->cur_chr;
  ctx->mem[ctx->lig_stack - mem_min].hh.U2.b1 = ctx->cur_r;
  if (ctx->cur_r == ctx->false_bchar)
    ctx->cur_r = 256;
_L110:
  if ((ctx->main_i.b2 & 3) != 1)
    goto _L80;
  if (ctx->cur_r == 256)
    goto _L80;
  ctx->main_k = ctx->fnt_infos.lig_kern_base[ctx->main_f] + ctx->main_i.b3;
  ctx->main_j = ctx->font_info[ctx->main_k].qqqq;
  if (ctx->main_j.b0 <= 128)
    goto _L112;
  ctx->main_k = ctx->fnt_infos.lig_kern_base[ctx->main_f] +
                (ctx->main_j.b2 * 256) + ctx->main_j.b3;
_L111:
  ctx->main_j = ctx->font_info[ctx->main_k].qqqq;
_L112:
  if (ctx->main_j.b1 == ctx->cur_r) {
    if (ctx->main_j.b0 <= 128) {
      if (ctx->main_j.b2 >= 128) {
        if (ctx->cur_l < 256) {
          if (ctx->mem[ctx->cur_q - mem_min].hh.rh > (-1073741824)) {
            if (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 ==
                ctx->fnt_infos.hyphen_char[ctx->main_f])
              ctx->ins_disc = true;
          }
          if (ctx->ligature_present) {
            ctx->main_p = new_ligature(ctx, ctx->main_f, ctx->cur_l,
                                       ctx->mem[ctx->cur_q - mem_min].hh.rh);
            if (ctx->lft_hit) {
              ctx->mem[ctx->main_p - mem_min].hh.U2.b1 = 2;
              ctx->lft_hit = false;
            }
            if (ctx->rt_hit) {
              if (ctx->lig_stack == (-1073741824)) {
                ++ctx->mem[ctx->main_p - mem_min].hh.U2.b1;
                ctx->rt_hit = false;
              }
            }
            ctx->mem[ctx->cur_q - mem_min].hh.rh = ctx->main_p;
            ctx->cur_list.tail_field = ctx->main_p;
            ctx->ligature_present = false;
          }
          if (ctx->ins_disc) {
            ctx->ins_disc = false;
            if (ctx->cur_list.mode_field > 0) {
              ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
                  new_disc(ctx);
              ctx->cur_list.tail_field =
                  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
            }
          }
        }
        (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = new_kern(
             ctx, ctx->font_info[ctx->fnt_infos.kern_base[ctx->main_f] +
                                 (ctx->main_j.b2 * 256) + ctx->main_j.b3]
                      .int_));
        ctx->cur_list.tail_field =
            ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
        goto _L90;
      }
      if (ctx->cur_l == 256) {
        ctx->lft_hit = true;
      } else if (ctx->lig_stack == (-1073741824))
        ctx->rt_hit = true;
      if (ctx->interrupt)
        pause_for_instructions(ctx);
      switch (ctx->main_j.b2) {
      case 1:
      case 5:
        ctx->cur_l = ctx->main_j.b3;
        ctx->main_i =
            ctx->font_info[ctx->fnt_infos.char_base[ctx->main_f] + ctx->cur_l]
                .qqqq;
        ctx->ligature_present = true;
        break;
      case 2:
      case 6:
        ctx->cur_r = ctx->main_j.b3;
        if (ctx->lig_stack == (-1073741824)) {
          ctx->lig_stack = new_lig_item(ctx, ctx->cur_r);
          ctx->bchar = 256;
        } else if (ctx->lig_stack >= ctx->hi_mem_min) {
          ctx->main_p = ctx->lig_stack;
          ctx->lig_stack = new_lig_item(ctx, ctx->cur_r);
          ctx->mem[ctx->lig_stack - mem_min + 1].hh.rh = ctx->main_p;
        } else {
          ctx->mem[ctx->lig_stack - mem_min].hh.U2.b1 = ctx->cur_r;
        }
        break;
      case 3:
        ctx->cur_r = ctx->main_j.b3;
        ctx->main_p = ctx->lig_stack;
        ctx->lig_stack = new_lig_item(ctx, ctx->cur_r);
        ctx->mem[ctx->lig_stack - mem_min].hh.rh = ctx->main_p;
        break;
      case 7:
      case 11:
        if (ctx->cur_l < 256) {
          if (ctx->mem[ctx->cur_q - mem_min].hh.rh > (-1073741824)) {
            if (ctx->mem[ctx->cur_list.tail_field - mem_min].hh.U2.b1 ==
                ctx->fnt_infos.hyphen_char[ctx->main_f])
              ctx->ins_disc = true;
          }
          if (ctx->ligature_present) {
            ctx->main_p = new_ligature(ctx, ctx->main_f, ctx->cur_l,
                                       ctx->mem[ctx->cur_q - mem_min].hh.rh);
            if (ctx->lft_hit) {
              ctx->mem[ctx->main_p - mem_min].hh.U2.b1 = 2;
              ctx->lft_hit = false;
            }
            ctx->mem[ctx->cur_q - mem_min].hh.rh = ctx->main_p;
            ctx->cur_list.tail_field = ctx->main_p;
            ctx->ligature_present = false;
          }
          if (ctx->ins_disc) {
            ctx->ins_disc = false;
            if (ctx->cur_list.mode_field > 0) {
              ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh =
                  new_disc(ctx);
              ctx->cur_list.tail_field =
                  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
            }
          }
        }
        ctx->cur_q = ctx->cur_list.tail_field;
        ctx->cur_l = ctx->main_j.b3;
        ctx->main_i =
            ctx->font_info[ctx->fnt_infos.char_base[ctx->main_f] + ctx->cur_l]
                .qqqq;
        ctx->ligature_present = true;
        break;
      default:
        ctx->cur_l = ctx->main_j.b3;
        ctx->ligature_present = true;
        if (ctx->lig_stack == (-1073741824))
          goto _L80;
        else
          goto _L91;
        break;
      }
      if (ctx->main_j.b2 > 4) {
        if (ctx->main_j.b2 != 7)
          goto _L80;
      }
      if (ctx->cur_l < 256)
        goto _L110;
      ctx->main_k = ctx->fnt_infos.bchar_label[ctx->main_f];
      goto _L111;
    }
  }
  if (!ctx->main_j.b0) {
    ++ctx->main_k;
  } else {
    if (ctx->main_j.b0 >= 128)
      goto _L80;
    ctx->main_k += ctx->main_j.b0 + 1;
  }
  goto _L111;
_L95:
  ctx->main_p = ctx->mem[ctx->lig_stack - mem_min + 1].hh.rh;
  if (ctx->main_p > (-1073741824)) {
    ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = ctx->main_p;
    ctx->cur_list.tail_field =
        ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh;
  }
  ctx->temp_ptr = ctx->lig_stack;
  ctx->lig_stack = ctx->mem[ctx->temp_ptr - mem_min].hh.rh;
  free_node(ctx, ctx->temp_ptr, 2);
  ctx->main_i =
      ctx->font_info[ctx->fnt_infos.char_base[ctx->main_f] + ctx->cur_l].qqqq;
  ctx->ligature_present = true;
  if (ctx->lig_stack == (-1073741824)) {
    if (ctx->main_p > (-1073741824))
      goto _L100;
    ctx->cur_r = ctx->bchar;
  } else {
    ctx->cur_r = ctx->mem[ctx->lig_stack - mem_min].hh.U2.b1;
  }
  goto _L110;
_L120:
  if (!ctx->eqtb[9794].hh.rh) {
    ctx->main_p = ctx->fnt_infos.font_glue[ctx->eqtb[10834].hh.rh];
    if (ctx->main_p == (-1073741824)) {
      ctx->main_p = new_spec(ctx, 0);
      ctx->main_k = ctx->fnt_infos.param_base[ctx->eqtb[10834].hh.rh] + 2;
      ctx->mem[ctx->main_p - mem_min + 1].int_ =
          ctx->font_info[ctx->main_k].int_;
      ctx->mem[ctx->main_p - mem_min + 2].int_ =
          ctx->font_info[ctx->main_k + 1].int_;
      ctx->mem[ctx->main_p - mem_min + 3].int_ =
          ctx->font_info[ctx->main_k + 2].int_;
      ctx->fnt_infos.font_glue[ctx->eqtb[10834].hh.rh] = ctx->main_p;
    }
    ctx->temp_ptr = new_glue(ctx, ctx->main_p);
  } else {
    ctx->temp_ptr = new_param_glue(ctx, 12);
  }
  ctx->mem[ctx->cur_list.tail_field - mem_min].hh.rh = ctx->temp_ptr;
  ctx->cur_list.tail_field = ctx->temp_ptr;
  goto _L60;
_L10:;
}

void give_err_help(ctex_t *ctx) { token_show(ctx, ctx->eqtb[10321].hh.rh); }

bool_t open_fmt_file(ctex_t *ctx) {
  bool_t result;
  int j = ctx->cur_input.loc_field;
  if (ctx->buffer[ctx->cur_input.loc_field] == 38) {
    ++ctx->cur_input.loc_field;
    j = ctx->cur_input.loc_field;
    ctx->buffer[ctx->last] = 32;
    while (ctx->buffer[j] != 32)
      ++j;
    pack_buffered_name(ctx, 0, ctx->cur_input.loc_field, j - 1);
    if (w_open_in(ctx, &ctx->fmt_file))
      goto _L40;
    pack_buffered_name(ctx, 11, ctx->cur_input.loc_field, j - 1);
    if (w_open_in(ctx, &ctx->fmt_file))
      goto _L40;
    fprintf(ctx->term_out,
            "Sorry, I can't find that format; will try PLAIN.\n");
    fflush(ctx->term_out);
    errno = 0;
  }
  pack_buffered_name(ctx, 16, 1, 0);
  if (!w_open_in(ctx, &ctx->fmt_file)) {
    fprintf(ctx->term_out, "I can't find the PLAIN format file!\n");
    result = false;
    goto _L10;
  }
_L40:
  ctx->cur_input.loc_field = j;
  result = true;
_L10:
  return result;
}

bool_t load_fmt_file(ctex_t *ctx) {
  bool_t result = true;
  integer j, k;
  halfword p = 0, q;
  four_quarters w;
  int N;
  integer x =
      readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (x != 117275187)
    goto _L6666;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (x)
    goto _L6666;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (x != mem_max)
    goto _L6666;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (x != 13006)
    goto _L6666;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (x != 7649)
    goto _L6666;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (x != 307)
    goto _L6666;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (x < 0)
    goto _L6666;
  if (x > pool_size) {
    fprintf(ctx->term_out, "---! Must increase the string pool size\n");
    goto _L6666;
  }
  ctx->pool_ptr = x;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (x < 0)
    goto _L6666;
  if (x > max_strings) {
    fprintf(ctx->term_out, "---! Must increase the max strings\n");
    goto _L6666;
  }
  ctx->str_ptr = x;
  for (N = ctx->str_ptr, k = 0; k <= N; ++k) {
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) > ctx->pool_ptr)
      goto _L6666;
    ctx->str_start[k] = x;
  }
  k = 0;
  while (k + 4 < ctx->pool_ptr) {
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    w = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->qqqq;
    ctx->str_pool[k] = w.b0;
    ctx->str_pool[k + 1] = w.b1;
    ctx->str_pool[k + 2] = w.b2;
    ctx->str_pool[k + 3] = w.b3;
    k += 4;
  }
  k = ctx->pool_ptr - 4;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  w = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->qqqq;
  ctx->str_pool[k] = w.b0;
  ctx->str_pool[k + 1] = w.b1;
  ctx->str_pool[k + 2] = w.b2;
  ctx->str_pool[k + 3] = w.b3;
  ctx->init_str_ptr = ctx->str_ptr;
  ctx->init_pool_ptr = ctx->pool_ptr;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if ((x < 1019) || (x > (mem_max - 14)))
    goto _L6666;
  ctx->lo_mem_max = x;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if ((x < 20) || (x > ctx->lo_mem_max))
    goto _L6666;
  ctx->rover = x;
  q = ctx->rover;
  do {
    for (k = p; k <= (q + 1); ++k) {
      loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
      ctx->mem[k - mem_min] =
          *readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    }
    p = q + ctx->mem[q - mem_min].hh.lh;
    if ((p > ctx->lo_mem_max) ||
        ((q >= ctx->mem[q - mem_min + 1].hh.rh) &&
         (ctx->mem[q - mem_min + 1].hh.rh != ctx->rover)))
      goto _L6666;
    q = ctx->mem[q - mem_min + 1].hh.rh;
  } while (q != ctx->rover);
  for (N = ctx->lo_mem_max, k = p; k <= N; ++k) {
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->mem[k - mem_min] =
        *readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  }
  if (mem_min < (-2)) {
    p = ctx->mem[ctx->rover - mem_min + 1].hh.lh;
    q = mem_min + 1;
    ctx->mem[0].hh.rh = -1073741824;
    ctx->mem[0].hh.lh = -1073741824;
    ctx->mem[p - mem_min + 1].hh.rh = q;
    ctx->mem[ctx->rover - mem_min + 1].hh.lh = q;
    ctx->mem[q - mem_min + 1].hh.rh = ctx->rover;
    ctx->mem[q - mem_min + 1].hh.lh = p;
    ctx->mem[q - mem_min].hh.rh = 1073741824;
    ctx->mem[q - mem_min].hh.lh = -q;
  }
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if ((x <= ctx->lo_mem_max) || (x > (mem_max - 13)))
    goto _L6666;
  ctx->hi_mem_min = x;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if ((x < (-1073741824)) || (x > mem_max))
    goto _L6666;
  ctx->avail = x;
  ctx->mem_end = mem_max;
  for (N = ctx->mem_end, k = ctx->hi_mem_min; k <= N; ++k) {
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->mem[k - mem_min] =
        *readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  }
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  ctx->var_used =
      readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  ctx->dyn_used =
      readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  k = 1;
  do {
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if ((x < 1) || (k + x > 13007))
      goto _L6666;
    for (j = k; j < (k + x); ++j) {
      loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
      ctx->eqtb[j] =
          *readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    }
    k += x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if ((x < 0) || (k + x > 13007))
      goto _L6666;
    for (j = k; j < (k + x); ++j)
      ctx->eqtb[j] = ctx->eqtb[k - 1];
    k += x;
  } while (k <= 13006);
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if ((x < 514) || (x > 9514))
    goto _L6666;
  ctx->par_loc = x;
  ctx->par_token = ctx->par_loc + 4095;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if ((x < 514) || (x > 9514))
    goto _L6666;
  ctx->write_loc = x;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if ((x < 514) || (x > 9514))
    goto _L6666;
  ctx->hash_used = x;
  p = 513;
  do {
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if ((x <= p) || (x > ctx->hash_used))
      goto _L6666;
    p = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->hash[p - 514] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->hh;
  } while (p != ctx->hash_used);
  for (p = ctx->hash_used + 1; p <= 9780; ++p) {
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->hash[p - 514] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->hh;
  }
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  ctx->cs_count =
      readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (x < 7)
    goto _L6666;
  if (x > font_mem_size) {
    fprintf(ctx->term_out, "---! Must increase the font mem size\n");
    goto _L6666;
  }
  ctx->fmem_ptr = x;
  for (N = ctx->fmem_ptr, k = 0; k < N; ++k) {
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->font_info[k] =
        *readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  }
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (x < 0)
    goto _L6666;
  if (x > font_max) {
    fprintf(ctx->term_out, "---! Must increase the font max\n");
    goto _L6666;
  }
  ctx->font_ptr = x;
  for (N = ctx->font_ptr, k = 0; k <= N; ++k) {
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.font_check[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->qqqq;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.font_size[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.font_dsize[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if ((x < (-1073741824)) || (x > 1073741824))
      goto _L6666;
    ctx->fnt_infos.font_params[k] = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.hyphen_char[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.skew_char[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) > ctx->str_ptr)
      goto _L6666;
    ctx->fnt_infos.font_name[k] = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) > ctx->str_ptr)
      goto _L6666;
    ctx->fnt_infos.font_area[k] = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) > 255)
      goto _L6666;
    ctx->fnt_infos.font_bc[k] = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) > 255)
      goto _L6666;
    ctx->fnt_infos.font_ec[k] = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.char_base[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.width_base[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.height_base[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.depth_base[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.italic_base[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.lig_kern_base[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.kern_base[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.exten_base[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->fnt_infos.param_base[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if ((x < (-1073741824)) || (x > ctx->lo_mem_max))
      goto _L6666;
    ctx->fnt_infos.font_glue[k] = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) >= ctx->fmem_ptr)
      goto _L6666;
    ctx->fnt_infos.bchar_label[k] = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) > 256)
      goto _L6666;
    ctx->fnt_infos.font_bchar[k] = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) > 256)
      goto _L6666;
    ctx->fnt_infos.font_false_bchar[k] = x;
  }
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (((unsigned)x) > 307)
    goto _L6666;
  ctx->hyph_count = x;
  for (N = ctx->hyph_count, k = 1; k <= N; ++k) {
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) > 307)
      goto _L6666;
    j = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) > ctx->str_ptr)
      goto _L6666;
    ctx->hyph_word[j] = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if ((x < (-1073741824)) || (x > 1073741824))
      goto _L6666;
    ctx->hyph_list[j] = x;
  }
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (x < 0)
    goto _L6666;
  if (x > trie_size) {
    fprintf(ctx->term_out, "---! Must increase the trie size\n");
    goto _L6666;
  }
  j = x;
  ctx->trie_max = j;
  for (k = 0; k <= j; ++k) {
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    ctx->trie[k] =
        readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->hh;
  }
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (x < 0)
    goto _L6666;
  if (x > trie_op_size) {
    fprintf(ctx->term_out, "---! Must increase the trie op size\n");
    goto _L6666;
  }
  j = x;
  ctx->trie_op_ptr = j;
  for (k = 1; k <= j; ++k) {
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) > 63)
      goto _L6666;
    ctx->hyf_distance[k] = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) > 63)
      goto _L6666;
    ctx->hyf_num[k] = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) > 65535)
      goto _L6666;
    ctx->hyf_next[k] = x;
  }
  for (k = 0; k <= 255; ++k)
    ctx->trie_used[k] = 0;
  k = 256;
  while (j > 0) {
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if (((unsigned)x) >= k)
      goto _L6666;
    k = x;
    loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
    x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
    if ((x < 1) || (x > j))
      goto _L6666;
    ctx->trie_used[k] = x;
    j -= x;
    ctx->op_start[k] = j;
  }
  ctx->trie_not_ready = false;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (((unsigned)x) > 3)
    goto _L6666;
  ctx->interaction = x;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if (((unsigned)x) > ctx->str_ptr)
    goto _L6666;
  ctx->format_ident = x;
  loadU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value);
  x = readU32(ctx->fmt_file, &ctx->fmt_file_mode, &ctx->fmt_file_value)->int_;
  if ((x != 69069) || feof(ctx->fmt_file))
    goto _L6666;
  goto _L10;
_L6666:
  fprintf(ctx->term_out, "(Fatal format file error; I'm stymied)\n");
  result = false;
_L10:
  return result;
}

void close_files_and_terminate(ctex_t *ctx) {
  integer k;
  for (k = 0; k <= 15; ++k) {
    if (ctx->write_open[k])
      a_close(ctx, &ctx->write_file[k]);
  }
  while (ctx->cur_s > (-1)) {
    if (ctx->cur_s > 0) {
      ctex_dvi_wU8(&ctx->dvi_mgr, 142);
    } else {
      ctex_dvi_wU8(&ctx->dvi_mgr, 140);
      ctex_dvi_add_page(&ctx->dvi_mgr);
    }
    --ctx->cur_s;
  }
  integer npages = ctex_dvi_pages(&ctx->dvi_mgr);
  if (!npages) {
    print_nl(ctx, 836);
  } else {
    ctex_dvi_wU8(&ctx->dvi_mgr, 248);
    ctex_dvi_four(&ctx->dvi_mgr, ctx->last_bop);
    ctx->last_bop = ctex_dvi_pos(&ctx->dvi_mgr) - 5;
    ctex_dvi_four(&ctx->dvi_mgr, 25400000);
    ctex_dvi_four(&ctx->dvi_mgr, 473628672);
    prepare_mag(ctx);
    ctex_dvi_four(&ctx->dvi_mgr, ctx->eqtb[12180].int_);
    ctex_dvi_four(&ctx->dvi_mgr, ctx->max_v);
    ctex_dvi_four(&ctx->dvi_mgr, ctx->max_h);
    ctex_dvi_wU8(&ctx->dvi_mgr, ctx->max_push / 256);
    ctex_dvi_wU8(&ctx->dvi_mgr, ctx->max_push & 255);
    ctex_dvi_wU8(&ctx->dvi_mgr, (npages / 256) & 255);
    ctex_dvi_wU8(&ctx->dvi_mgr, npages & 255);
    while (ctx->font_ptr > 0) {
      if (ctx->fnt_infos.font_used[ctx->font_ptr]) {
        dvi_font_def(ctx, ctx->font_ptr);
      }
      --ctx->font_ptr;
    }
    ctex_dvi_wU8(&ctx->dvi_mgr, 249);
    ctex_dvi_four(&ctx->dvi_mgr, ctx->last_bop);
    ctex_dvi_wU8(&ctx->dvi_mgr, 2);
    k = (ctex_dvi_cap(&ctx->dvi_mgr) & 3) + 4;
    while (k > 0) {
      ctex_dvi_wU8(&ctx->dvi_mgr, 223);
      --k;
    }
    ctex_dvi_flush(&ctx->dvi_mgr);
    print_nl(ctx, 837);
    slow_print(ctx, ctx->output_file_name);
    print(ctx, 286);
    npages = ctex_dvi_pages(&ctx->dvi_mgr);
    print_int(ctx, npages);
    print(ctx, 838);
    if (npages != 1)
      print_char(ctx, 115);
    print(ctx, 839);
    print_int(ctx, ctex_dvi_pos(&ctx->dvi_mgr));
    print(ctx, 840);
    b_close(ctx, &ctx->dvi_mgr.dvi_file);
  }
  if (!ctx->log_opened)
    return;
  fprintf(ctx->log_file, "\n");
  a_close(ctx, &ctx->log_file);
  ctx->selector -= 2;
  if (ctx->selector != 17)
    return;
  print_nl(ctx, 1274);
  slow_print(ctx, ctx->log_name);
  print_char(ctx, 46);
}

void final_cleanup(ctex_t *ctx) {
  small_number c = ctx->cur_chr;
  if (!ctx->job_name)
    open_log_file(ctx);
  while (ctx->input_ptr > 0) {
    if (!ctx->cur_input.state_field)
      end_token_list(ctx);
    else
      end_file_reading(ctx);
  }
  while (ctx->open_parens > 0) {
    print(ctx, 1275);
    --ctx->open_parens;
  }
  if (ctx->cur_level > 1) {
    print_nl(ctx, 40);
    print_esc(ctx, 1276);
    print(ctx, 1277);
    print_int(ctx, ctx->cur_level - 1);
    print_char(ctx, 41);
  }
  while (ctx->cond_ptr != (-1073741824)) {
    print_nl(ctx, 40);
    print_esc(ctx, 1276);
    print(ctx, 1278);
    print_cmd_chr(ctx, 105, ctx->cur_if);
    if (ctx->if_line) {
      print(ctx, 1279);
      print_int(ctx, ctx->if_line);
    }
    print(ctx, 1280);
    ctx->if_line = ctx->mem[ctx->cond_ptr - mem_min + 1].int_;
    ctx->cur_if = ctx->mem[ctx->cond_ptr - mem_min].hh.U2.b1;
    ctx->temp_ptr = ctx->cond_ptr;
    ctx->cond_ptr = ctx->mem[ctx->cond_ptr - mem_min].hh.rh;
    free_node(ctx, ctx->temp_ptr, 2);
  }
  if (ctx->history) {
    if ((ctx->history == 1) || (ctx->interaction < 3)) {
      if (ctx->selector == 19) {
        ctx->selector = 17;
        print_nl(ctx, 1281);
        ctx->selector = 19;
      }
    }
  }
  if (c == 1) {
    for (c = 0; c <= 4; ++c) {
      if (ctx->cur_mark[c] != (-1073741824))
        delete_token_ref(ctx, ctx->cur_mark[c]);
    }
    if (ctx->last_glue != 1073741824)
      delete_glue_ref(ctx, ctx->last_glue);
    store_fmt_file(ctx);
    goto _L10;
  }
_L10:;
}

void init_prim(ctex_t *ctx) {
  ctx->no_new_control_sequence = false;
  primitive(ctx, 376, 75, 9782);
  primitive(ctx, 377, 75, 9783);
  primitive(ctx, 378, 75, 9784);
  primitive(ctx, 379, 75, 9785);
  primitive(ctx, 380, 75, 9786);
  primitive(ctx, 381, 75, 9787);
  primitive(ctx, 382, 75, 9788);
  primitive(ctx, 383, 75, 9789);
  primitive(ctx, 384, 75, 9790);
  primitive(ctx, 385, 75, 9791);
  primitive(ctx, 386, 75, 9792);
  primitive(ctx, 387, 75, 9793);
  primitive(ctx, 388, 75, 9794);
  primitive(ctx, 389, 75, 9795);
  primitive(ctx, 390, 75, 9796);
  primitive(ctx, 391, 76, 9797);
  primitive(ctx, 392, 76, 9798);
  primitive(ctx, 393, 76, 9799);
  primitive(ctx, 398, 72, 10313);
  primitive(ctx, 399, 72, 10314);
  primitive(ctx, 400, 72, 10315);
  primitive(ctx, 401, 72, 10316);
  primitive(ctx, 402, 72, 10317);
  primitive(ctx, 403, 72, 10318);
  primitive(ctx, 404, 72, 10319);
  primitive(ctx, 405, 72, 10320);
  primitive(ctx, 406, 72, 10321);
  primitive(ctx, 420, 73, 12163);
  primitive(ctx, 421, 73, 12164);
  primitive(ctx, 422, 73, 12165);
  primitive(ctx, 423, 73, 12166);
  primitive(ctx, 424, 73, 12167);
  primitive(ctx, 425, 73, 12168);
  primitive(ctx, 426, 73, 12169);
  primitive(ctx, 427, 73, 12170);
  primitive(ctx, 428, 73, 12171);
  primitive(ctx, 429, 73, 12172);
  primitive(ctx, 430, 73, 12173);
  primitive(ctx, 431, 73, 12174);
  primitive(ctx, 432, 73, 12175);
  primitive(ctx, 433, 73, 12176);
  primitive(ctx, 434, 73, 12177);
  primitive(ctx, 435, 73, 12178);
  primitive(ctx, 436, 73, 12179);
  primitive(ctx, 437, 73, 12180);
  primitive(ctx, 438, 73, 12181);
  primitive(ctx, 439, 73, 12182);
  primitive(ctx, 440, 73, 12183);
  primitive(ctx, 441, 73, 12184);
  primitive(ctx, 442, 73, 12185);
  primitive(ctx, 443, 73, 12186);
  primitive(ctx, 444, 73, 12187);
  primitive(ctx, 445, 73, 12188);
  primitive(ctx, 446, 73, 12189);
  primitive(ctx, 447, 73, 12190);
  primitive(ctx, 448, 73, 12191);
  primitive(ctx, 449, 73, 12192);
  primitive(ctx, 450, 73, 12193);
  primitive(ctx, 451, 73, 12194);
  primitive(ctx, 452, 73, 12195);
  primitive(ctx, 453, 73, 12196);
  primitive(ctx, 454, 73, 12197);
  primitive(ctx, 455, 73, 12198);
  primitive(ctx, 456, 73, 12199);
  primitive(ctx, 457, 73, 12200);
  primitive(ctx, 458, 73, 12201);
  primitive(ctx, 459, 73, 12202);
  primitive(ctx, 460, 73, 12203);
  primitive(ctx, 461, 73, 12204);
  primitive(ctx, 462, 73, 12205);
  primitive(ctx, 463, 73, 12206);
  primitive(ctx, 464, 73, 12207);
  primitive(ctx, 465, 73, 12208);
  primitive(ctx, 466, 73, 12209);
  primitive(ctx, 467, 73, 12210);
  primitive(ctx, 468, 73, 12211);
  primitive(ctx, 469, 73, 12212);
  primitive(ctx, 470, 73, 12213);
  primitive(ctx, 471, 73, 12214);
  primitive(ctx, 472, 73, 12215);
  primitive(ctx, 473, 73, 12216);
  primitive(ctx, 474, 73, 12217);
  primitive(ctx, 478, 74, 12730);
  primitive(ctx, 479, 74, 12731);
  primitive(ctx, 480, 74, 12732);
  primitive(ctx, 481, 74, 12733);
  primitive(ctx, 482, 74, 12734);
  primitive(ctx, 483, 74, 12735);
  primitive(ctx, 484, 74, 12736);
  primitive(ctx, 485, 74, 12737);
  primitive(ctx, 486, 74, 12738);
  primitive(ctx, 487, 74, 12739);
  primitive(ctx, 488, 74, 12740);
  primitive(ctx, 489, 74, 12741);
  primitive(ctx, 490, 74, 12742);
  primitive(ctx, 491, 74, 12743);
  primitive(ctx, 492, 74, 12744);
  primitive(ctx, 493, 74, 12745);
  primitive(ctx, 494, 74, 12746);
  primitive(ctx, 495, 74, 12747);
  primitive(ctx, 496, 74, 12748);
  primitive(ctx, 497, 74, 12749);
  primitive(ctx, 498, 74, 12750);
  primitive(ctx, 32, 64, 0);
  primitive(ctx, 47, 44, 0);
  primitive(ctx, 508, 45, 0);
  primitive(ctx, 509, 90, 0);
  primitive(ctx, 510, 40, 0);
  primitive(ctx, 511, 41, 0);
  primitive(ctx, 512, 61, 0);
  primitive(ctx, 513, 16, 0);
  primitive(ctx, 504, 107, 0);
  primitive(ctx, 514, 15, 0);
  primitive(ctx, 515, 92, 0);
  primitive(ctx, 505, 67, 0);
  primitive(ctx, 516, 62, 0);
  ctx->hash[9002].rh = 516;
  ctx->eqtb[9516] = ctx->eqtb[ctx->cur_val];
  primitive(ctx, 517, 102, 0);
  primitive(ctx, 518, 88, 0);
  primitive(ctx, 519, 77, 0);
  primitive(ctx, 520, 32, 0);
  primitive(ctx, 521, 36, 0);
  primitive(ctx, 522, 39, 0);
  primitive(ctx, 330, 37, 0);
  primitive(ctx, 351, 18, 0);
  primitive(ctx, 523, 46, 0);
  primitive(ctx, 524, 17, 0);
  primitive(ctx, 525, 54, 0);
  primitive(ctx, 526, 91, 0);
  primitive(ctx, 527, 34, 0);
  primitive(ctx, 528, 65, 0);
  primitive(ctx, 529, 103, 0);
  primitive(ctx, 335, 55, 0);
  primitive(ctx, 530, 63, 0);
  primitive(ctx, 408, 84, 0);
  primitive(ctx, 531, 42, 0);
  primitive(ctx, 532, 80, 0);
  primitive(ctx, 533, 66, 0);
  primitive(ctx, 534, 96, 0);
  primitive(ctx, 535, 0, 256);
  ctx->hash[9007].rh = 535;
  ctx->eqtb[9521] = ctx->eqtb[ctx->cur_val];
  primitive(ctx, 536, 98, 0);
  primitive(ctx, 537, 109, 0);
  primitive(ctx, 407, 71, 0);
  primitive(ctx, 352, 38, 0);
  primitive(ctx, 538, 33, 0);
  primitive(ctx, 539, 56, 0);
  primitive(ctx, 540, 35, 0);
  primitive(ctx, 597, 13, 256);
  ctx->par_loc = ctx->cur_val;
  ctx->par_token = ctx->par_loc + 4095;
  primitive(ctx, 629, 104, 0);
  primitive(ctx, 630, 104, 1);
  primitive(ctx, 631, 110, 0);
  primitive(ctx, 632, 110, 1);
  primitive(ctx, 633, 110, 2);
  primitive(ctx, 634, 110, 3);
  primitive(ctx, 635, 110, 4);
  primitive(ctx, 476, 89, 0);
  primitive(ctx, 500, 89, 1);
  primitive(ctx, 395, 89, 2);
  primitive(ctx, 396, 89, 3);
  primitive(ctx, 668, 79, 102);
  primitive(ctx, 669, 79, 1);
  primitive(ctx, 670, 82, 0);
  primitive(ctx, 671, 82, 1);
  primitive(ctx, 672, 83, 1);
  primitive(ctx, 673, 83, 3);
  primitive(ctx, 674, 83, 2);
  primitive(ctx, 675, 70, 0);
  primitive(ctx, 676, 70, 1);
  primitive(ctx, 677, 70, 2);
  primitive(ctx, 678, 70, 3);
  primitive(ctx, 679, 70, 4);
  primitive(ctx, 735, 108, 0);
  primitive(ctx, 736, 108, 1);
  primitive(ctx, 737, 108, 2);
  primitive(ctx, 738, 108, 3);
  primitive(ctx, 739, 108, 4);
  primitive(ctx, 740, 108, 5);
  primitive(ctx, 756, 105, 0);
  primitive(ctx, 757, 105, 1);
  primitive(ctx, 758, 105, 2);
  primitive(ctx, 759, 105, 3);
  primitive(ctx, 760, 105, 4);
  primitive(ctx, 761, 105, 5);
  primitive(ctx, 762, 105, 6);
  primitive(ctx, 763, 105, 7);
  primitive(ctx, 764, 105, 8);
  primitive(ctx, 765, 105, 9);
  primitive(ctx, 766, 105, 10);
  primitive(ctx, 767, 105, 11);
  primitive(ctx, 768, 105, 12);
  primitive(ctx, 769, 105, 13);
  primitive(ctx, 770, 105, 14);
  primitive(ctx, 771, 105, 15);
  primitive(ctx, 772, 105, 16);
  primitive(ctx, 773, 106, 2);
  ctx->hash[9004].rh = 773;
  ctx->eqtb[9518] = ctx->eqtb[ctx->cur_val];
  primitive(ctx, 774, 106, 4);
  primitive(ctx, 775, 106, 3);
  primitive(ctx, 800, 87, 0);
  ctx->hash[9010].rh = 800;
  ctx->eqtb[9524] = ctx->eqtb[ctx->cur_val];
  primitive(ctx, 897, 4, 256);
  primitive(ctx, 898, 5, 257);
  ctx->hash[9001].rh = 898;
  ctx->eqtb[9515] = ctx->eqtb[ctx->cur_val];
  primitive(ctx, 899, 5, 258);
  ctx->hash[9005].rh = 900;
  ctx->hash[9006].rh = 900;
  ctx->eqtb[9520].hh.U2.b0 = 9;
  ctx->eqtb[9520].hh.rh = mem_max - 11;
  ctx->eqtb[9520].hh.U2.b1 = 1;
  ctx->eqtb[9519] = ctx->eqtb[9520];
  ctx->eqtb[9519].hh.U2.b0 = 115;
  primitive(ctx, 969, 81, 0);
  primitive(ctx, 970, 81, 1);
  primitive(ctx, 971, 81, 2);
  primitive(ctx, 972, 81, 3);
  primitive(ctx, 973, 81, 4);
  primitive(ctx, 974, 81, 5);
  primitive(ctx, 975, 81, 6);
  primitive(ctx, 976, 81, 7);
  primitive(ctx, 1024, 14, 0);
  primitive(ctx, 1025, 14, 1);
  primitive(ctx, 1026, 26, 4);
  primitive(ctx, 1027, 26, 0);
  primitive(ctx, 1028, 26, 1);
  primitive(ctx, 1029, 26, 2);
  primitive(ctx, 1030, 26, 3);
  primitive(ctx, 1031, 27, 4);
  primitive(ctx, 1032, 27, 0);
  primitive(ctx, 1033, 27, 1);
  primitive(ctx, 1034, 27, 2);
  primitive(ctx, 1035, 27, 3);
  primitive(ctx, 336, 28, 5);
  primitive(ctx, 340, 29, 1);
  primitive(ctx, 342, 30, 99);
  primitive(ctx, 1053, 21, 1);
  primitive(ctx, 1054, 21, 0);
  primitive(ctx, 1055, 22, 1);
  primitive(ctx, 1056, 22, 0);
  primitive(ctx, 409, 20, 0);
  primitive(ctx, 1057, 20, 1);
  primitive(ctx, 1058, 20, 2);
  primitive(ctx, 964, 20, 3);
  primitive(ctx, 1059, 20, 4);
  primitive(ctx, 966, 20, 5);
  primitive(ctx, 1060, 20, 106);
  primitive(ctx, 1061, 31, 99);
  primitive(ctx, 1062, 31, 100);
  primitive(ctx, 1063, 31, 101);
  primitive(ctx, 1064, 31, 102);
  primitive(ctx, 1079, 43, 1);
  primitive(ctx, 1080, 43, 0);
  primitive(ctx, 1089, 25, 12);
  primitive(ctx, 1090, 25, 11);
  primitive(ctx, 1091, 25, 10);
  primitive(ctx, 1092, 23, 0);
  primitive(ctx, 1093, 23, 1);
  primitive(ctx, 1094, 24, 0);
  primitive(ctx, 1095, 24, 1);
  primitive(ctx, 45, 47, 1);
  primitive(ctx, 349, 47, 0);
  primitive(ctx, 1126, 48, 0);
  primitive(ctx, 1127, 48, 1);
  primitive(ctx, 865, 50, 16);
  primitive(ctx, 866, 50, 17);
  primitive(ctx, 867, 50, 18);
  primitive(ctx, 868, 50, 19);
  primitive(ctx, 869, 50, 20);
  primitive(ctx, 870, 50, 21);
  primitive(ctx, 871, 50, 22);
  primitive(ctx, 872, 50, 23);
  primitive(ctx, 874, 50, 26);
  primitive(ctx, 873, 50, 27);
  primitive(ctx, 1128, 51, 0);
  primitive(ctx, 877, 51, 1);
  primitive(ctx, 878, 51, 2);
  primitive(ctx, 860, 53, 0);
  primitive(ctx, 861, 53, 2);
  primitive(ctx, 862, 53, 4);
  primitive(ctx, 863, 53, 6);
  primitive(ctx, 1146, 52, 0);
  primitive(ctx, 1147, 52, 1);
  primitive(ctx, 1148, 52, 2);
  primitive(ctx, 1149, 52, 3);
  primitive(ctx, 1150, 52, 4);
  primitive(ctx, 1151, 52, 5);
  primitive(ctx, 875, 49, 30);
  primitive(ctx, 876, 49, 31);
  ctx->hash[9003].rh = 876;
  ctx->eqtb[9517] = ctx->eqtb[ctx->cur_val];
  primitive(ctx, 1170, 93, 1);
  primitive(ctx, 1171, 93, 2);
  primitive(ctx, 1172, 93, 4);
  primitive(ctx, 1173, 97, 0);
  primitive(ctx, 1174, 97, 1);
  primitive(ctx, 1175, 97, 2);
  primitive(ctx, 1176, 97, 3);
  primitive(ctx, 1190, 94, 0);
  primitive(ctx, 1191, 94, 1);
  primitive(ctx, 1192, 95, 0);
  primitive(ctx, 1193, 95, 1);
  primitive(ctx, 1194, 95, 2);
  primitive(ctx, 1195, 95, 3);
  primitive(ctx, 1196, 95, 4);
  primitive(ctx, 1197, 95, 5);
  primitive(ctx, 1198, 95, 6);
  primitive(ctx, 415, 85, 10883);
  primitive(ctx, 419, 85, 11907);
  primitive(ctx, 416, 85, 11139);
  primitive(ctx, 417, 85, 11395);
  primitive(ctx, 418, 85, 11651);
  primitive(ctx, 477, 85, 12474);
  primitive(ctx, 412, 86, 10835);
  primitive(ctx, 413, 86, 10851);
  primitive(ctx, 414, 86, 10867);
  primitive(ctx, 940, 99, 0);
  primitive(ctx, 952, 99, 1);
  primitive(ctx, 1216, 78, 0);
  primitive(ctx, 1217, 78, 1);
  primitive(ctx, 274, 100, 0);
  primitive(ctx, 275, 100, 1);
  primitive(ctx, 276, 100, 2);
  primitive(ctx, 1226, 100, 3);
  primitive(ctx, 1227, 60, 1);
  primitive(ctx, 1228, 60, 0);
  primitive(ctx, 1229, 58, 0);
  primitive(ctx, 1230, 58, 1);
  primitive(ctx, 1236, 57, 11139);
  primitive(ctx, 1237, 57, 11395);
  primitive(ctx, 1238, 19, 0);
  primitive(ctx, 1239, 19, 1);
  primitive(ctx, 1240, 19, 2);
  primitive(ctx, 1241, 19, 3);
  primitive(ctx, 1284, 59, 0);
  primitive(ctx, 594, 59, 1);
  ctx->write_loc = ctx->cur_val;
  primitive(ctx, 1285, 59, 2);
  primitive(ctx, 1286, 59, 3);
  primitive(ctx, 1287, 59, 4);
  primitive(ctx, 1288, 59, 5);
  ctx->no_new_control_sequence = true;
}

void getopt(ctex_t *ctx, int argc, const char **args) {
  for (int i = 0; i < argc; i++) {
    // ' ' must come first, the first character is always skipped…
    fprintf(ctx->input_stream, " %s", args[i]);
  }
}

void typeset(ctex_t *ctx, int argc, const char **args) {
  getopt(ctx, argc, args);
  if (setjmp(ctx->_JL9998))
    goto _L9998;
  if (setjmp(ctx->_JL9999))
    goto _L9999;
  ctx->history = 3;
  ctx->term_out = ctx->output_stream;
  if (!ctx->term_out)
    io_error(errno, "TTY:");
  if (ctx->ready_already == 314159)
    goto _L1;
  initialize(ctx);
  if (!get_strings_started(ctx))
    goto _L9999;
  init_prim(ctx);
  ctx->init_str_ptr = ctx->str_ptr;
  ctx->init_pool_ptr = ctx->pool_ptr;
  fix_date_and_time(ctx);
  ctx->ready_already = 314159;
_L1:
  ctx->selector = 17;
  ctx->tally = 0;
  ctx->term_offset = 0;
  ctx->file_offset = 0;
  fprintf(ctx->term_out, "This is TeX, Version 3.14159265");
  if (!ctx->format_ident) {
    fprintf(ctx->term_out, " (no format preloaded)\n");
  } else {
    slow_print(ctx, ctx->format_ident);
    print_ln(ctx);
  }
  fflush(ctx->term_out);
  errno = 0;
  ctx->job_name = 0;
  ctx->name_in_progress = false;
  ctx->log_opened = false;
  ctx->output_file_name = 0;
  ctx->input_ptr = 0;
  ctx->max_in_stack = 0;
  ctx->in_open = 0;
  ctx->open_parens = 0;
  ctx->max_buf_stack = 0;
  ctx->param_ptr = 0;
  ctx->max_param_stack = 0;
  ctx->first = buf_size;
  do {
    ctx->buffer[ctx->first] = 0;
    --ctx->first;
  } while (ctx->first);
  ctx->scanner_status = 0;
  ctx->warning_index = -1073741824;
  ctx->first = 1;
  ctx->cur_input.state_field = 33;
  ctx->cur_input.start_field = 1;
  ctx->cur_input.index_field = 0;
  ctx->line = 0;
  ctx->cur_input.name_field = 0;
  ctx->force_eof = false;
  ctx->align_state = 1000000;
  if (!init_terminal(ctx))
    goto _L9999;
  ctx->cur_input.limit_field = ctx->last;
  ctx->first = ctx->last + 1;
  if ((!ctx->format_ident) || (ctx->buffer[ctx->cur_input.loc_field] == 38)) {
    if (ctx->format_ident)
      initialize(ctx);
    if (!open_fmt_file(ctx))
      goto _L9999;
    if (!load_fmt_file(ctx)) {
      w_close(ctx, &ctx->fmt_file);
      goto _L9999;
    }
    w_close(ctx, &ctx->fmt_file);
    while ((ctx->cur_input.loc_field < ctx->cur_input.limit_field) &&
           (ctx->buffer[ctx->cur_input.loc_field] == 32))
      ++ctx->cur_input.loc_field;
  }
  if (((unsigned)ctx->eqtb[12211].int_) > 255)
    --ctx->cur_input.limit_field;
  else
    ctx->buffer[ctx->cur_input.limit_field] = ctx->eqtb[12211].int_;
  fix_date_and_time(ctx);
  ctx->magic_offset = ctx->str_start[891] - 144;
  if (!ctx->interaction)
    ctx->selector = 16;
  else
    ctx->selector = 17;
  if ((ctx->cur_input.loc_field < ctx->cur_input.limit_field) &&
      ctx->eqtb[ctx->buffer[ctx->cur_input.loc_field] + 10883].hh.rh)
    start_input(ctx);
  ctx->history = 0;
  main_control(ctx);
  final_cleanup(ctx);
_L9998:
  close_files_and_terminate(ctx);
_L9999:
  ctx->ready_already = 0;
  if (ctx->term_in)
    fclose(ctx->term_in);
  if (ctx->term_out)
    fclose(ctx->term_out);
  if (ctx->pool_file)
    fclose(ctx->pool_file);
  if (ctx->log_file)
    fclose(ctx->log_file);
  if (ctx->dvi_mgr.dvi_file)
    fclose(ctx->dvi_mgr.dvi_file);
  if (ctx->tfm_file)
    fclose(ctx->tfm_file);
  if (ctx->fmt_file)
    fclose(ctx->fmt_file);
  return;
}

void process(ctex_t *ctx, const char *filename, const char *result,
             const char *search_dir, const char *working_dir,
             const char *output) {

  ctx->input_stream =
      open_memstream(&ctx->input_stream_buf,
                     &ctx->input_stream_len); // will be closed as term_in
  ctx->output_stream = fopen(output, "w");    // will be closed as term_out

  ctx->dvi_mgr.dvi_file = fopen(result, "w");

  const char *args[5] = {
      R"(\nonstopmode)", // omits all stops (\batchmode also omits terminal
                         // output)
      R"(\input plain)",
      R"(\input)",
      filename,
      R"(\end)",
  };
  typeset(ctx, 5, args);
}
