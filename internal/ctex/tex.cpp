// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "tex.hpp"

namespace tex {

void 
tex::initialize() {

    integer k;
    hyph_pointer z;
    mem.resize(mem_max - mem_min + 1);
    font_info.resize(font_mem_size + 1);
    str_pool.resize(pool_size + 1);
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
    null_character.b0 = 0;
    null_character.b1 = 0;
    null_character.b2 = 0;
    null_character.b3 = 0;
    max_v = 0;
    max_h = 0;
    max_push = 0;
    last_bop = -1;
    doing_leaders = false;
    dead_cycles = 0;
    cur_s = -1;
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
	ctex_font_info_init(&fnt_infos);
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

internal_font_number
tex::read_font_info(halfword u, str_number nom, str_number aire, scaled s) {
    font_index k;
    bool file_opened = false;
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
      pack_file_name(nom, 784, 810);
    else
      pack_file_name(nom, aire, 810);
    if (!b_open_in(tfm_file))
      goto _L11;
    file_opened = true;
    tfm_file_mode = 1;
    lf = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (lf > 127)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    lf = (lf * 256) +
         readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    lh = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (lh > 127)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    lh = (lh * 256) +
         readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    bc = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (bc > 127)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    bc = (bc * 256) +
         readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    ec = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (ec > 127)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    ec = (ec * 256) +
         readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if ((bc > (ec + 1)) || (ec > 255))
      goto _L11;
    if (bc > 255) {
      bc = 1;
      ec = 0;
    }
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    nw = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (nw > 127)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    nw = (nw * 256) +
         readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    nh = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (nh > 127)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    nh = (nh * 256) +
         readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    nd = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (nd > 127)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    nd = (nd * 256) +
         readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    ni = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (ni > 127)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    ni = (ni * 256) +
         readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    nl = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (nl > 127)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    nl = (nl * 256) +
         readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    nk = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (nk > 127)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    nk = (nk * 256) +
         readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    ne = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (ne > 127)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    ne = (ne * 256) +
         readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    np = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (np > 127)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    np = (np * 256) +
         readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (lf != (lh + ec - bc + nw + nh + nd + ni + nl + nk + ne + np + 7))
      goto _L11;
    if ((!nw) || (!nh) || (!nd) || (!ni))
      goto _L11;
    lf += (-lh) - 6;
    if (np < 7)
      lf += 7 - np;
    if ((font_ptr == font_max) || (fmem_ptr + lf > font_mem_size)) {
      print_nl(262);
      print(801);
      sprint_cs(u);
      print_char(61);
      print_file_name(nom, aire, 338);
      if (s >= 0) {
        print(741);
        print_scaled(s);
        print(397);
      } else if (s != (-1000)) {
        print(802);
        print_int(-s);
      }
      print(811);
      help_ptr = 4;
      help_line[3] = 812;
      help_line[2] = 813;
      help_line[1] = 814;
      help_line[0] = 815;
      error();
      goto _L30;
    }
    f = font_ptr + 1;
    fnt_infos.char_base[f] = fmem_ptr - bc;
    fnt_infos.width_base[f] = fnt_infos.char_base[f] + ec + 1;
    fnt_infos.height_base[f] = fnt_infos.width_base[f] + nw;
    fnt_infos.depth_base[f] = fnt_infos.height_base[f] + nh;
    fnt_infos.italic_base[f] = fnt_infos.depth_base[f] + nd;
    fnt_infos.lig_kern_base[f] = fnt_infos.italic_base[f] + ni;
    fnt_infos.kern_base[f] = fnt_infos.lig_kern_base[f] + nl - 32768;
    fnt_infos.exten_base[f] = fnt_infos.kern_base[f] + nk + 32768;
    fnt_infos.param_base[f] = fnt_infos.exten_base[f] + ne;
    if (lh < 2)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    a = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    qw.b0 = a;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    b = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    qw.b1 = b;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    c = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    qw.b2 = c;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    d = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    qw.b3 = d;
    fnt_infos.font_check[f] = qw;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    z = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    if (z > 127)
      goto _L11;
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    z = (z * 256) +
        readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    z = (z * 256) +
        readU8(tfm_file, tfm_file_mode, &tfm_file_value);
    loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
    z = (z * 16) +
        (readU8(tfm_file, tfm_file_mode, &tfm_file_value) / 16);
    if (z < 65536)
      goto _L11;
    while (lh > 2) {
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
      --lh;
    }
    fnt_infos.font_dsize[f] = z;
    if (s != (-1000)) {
      if (s >= 0)
        z = s;
      else
        z = xn_over_d(z, -s, 1000);
    }
    fnt_infos.font_size[f] = z;
    for (N = fnt_infos.width_base[f], k = fmem_ptr; k <= (N - 1); ++k) {
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
      a = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
      qw.b0 = a;
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
      b = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
      qw.b1 = b;
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
      c = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
      qw.b2 = c;
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
      d = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
      qw.b3 = d;
      font_info[k].qqqq = qw;
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
        while (d < (k + bc - fmem_ptr)) {
          qw = font_info[fnt_infos.char_base[f] + d].qqqq;
          if ((qw.b2 & 3) != 2)
            goto _L45;
          d = qw.b3;
        }
        if (d == (k + bc - fmem_ptr))
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
    for (N = fnt_infos.lig_kern_base[f], k = fnt_infos.width_base[f]; k <= (N - 1); ++k) {
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
	  fread(&a, sizeof(uint8_t), 1, tfm_file);
	  fread(&b, sizeof(uint8_t), 1, tfm_file);
	  fread(&c, sizeof(uint8_t), 1, tfm_file);
      d = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
      sw = ((((d * z / 256) + (c * z)) / 256) + (b * z)) / beta;
      if (!a) {
        font_info[k].int_ = sw;
      } else if (a == 255)
        font_info[k].int_ = sw - alpha;
      else
        goto _L11;
    }
    if (font_info[fnt_infos.width_base[f]].int_)
      goto _L11;
    if (font_info[fnt_infos.height_base[f]].int_)
      goto _L11;
    if (font_info[fnt_infos.depth_base[f]].int_)
      goto _L11;
    if (font_info[fnt_infos.italic_base[f]].int_)
      goto _L11;
    if (nl > 0) {
      for (N = fnt_infos.kern_base[f] + 32767, k = fnt_infos.lig_kern_base[f]; k <= N; ++k) {
        loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
        a = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
        qw.b0 = a;
        loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
        b = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
        qw.b1 = b;
        loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
        c = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
        qw.b2 = c;
        loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
        d = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
        qw.b3 = d;
        font_info[k].qqqq = qw;
        if (a > 128) {
          if ((c * 256) + d >= nl)
            goto _L11;
          if (a == 255) {
            if (k == fnt_infos.lig_kern_base[f])
              bchar = b;
          }
        } else {
          if (b != bchar) {
            if ((b < bc) || (b > ec))
              goto _L11;
            qw = font_info[fnt_infos.char_base[f] + b].qqqq;
            if (qw.b0 <= 0)
              goto _L11;
          }
          if (c < 128) {
            if ((d < bc) || (d > ec))
              goto _L11;
            qw = font_info[fnt_infos.char_base[f] + d].qqqq;
            if (qw.b0 <= 0)
              goto _L11;
          } else if (((c - 128) * 256) + d >= nk)
            goto _L11;
          if (a < 128) {
            if (k - fnt_infos.lig_kern_base[f] + a + 1 >= nl)
              goto _L11;
          }
        }
      }
      if (a == 255)
        bch_label = (c * 256) + d;
    }
    for (N = fnt_infos.exten_base[f], k = fnt_infos.kern_base[f] + 32768; k <= (N - 1); ++k) {
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
	  fread(&a, sizeof(uint8_t), 1, tfm_file);
	  fread(&b, sizeof(uint8_t), 1, tfm_file);
	  fread(&c, sizeof(uint8_t), 1, tfm_file);
      d = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
      sw = ((((d * z / 256) + (c * z)) / 256) + (b * z)) / beta;
      if (!a) {
        font_info[k].int_ = sw;
      } else if (a == 255)
        font_info[k].int_ = sw - alpha;
      else
        goto _L11;
    }
    for (N = fnt_infos.param_base[f], k = fnt_infos.exten_base[f]; k <= (N - 1); ++k) {
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
      a = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
      qw.b0 = a;
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
      b = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
      qw.b1 = b;
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
      c = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
      qw.b2 = c;
      loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
      d = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
      qw.b3 = d;
      font_info[k].qqqq = qw;
      if (a) {
        if ((a < bc) || (a > ec))
          goto _L11;
        qw = font_info[fnt_infos.char_base[f] + a].qqqq;
        if (qw.b0 <= 0)
          goto _L11;
      }
      if (b) {
        if ((b < bc) || (b > ec))
          goto _L11;
        qw = font_info[fnt_infos.char_base[f] + b].qqqq;
        if (qw.b0 <= 0)
          goto _L11;
      }
      if (c) {
        if ((c < bc) || (c > ec))
          goto _L11;
        qw = font_info[fnt_infos.char_base[f] + c].qqqq;
        if (qw.b0 <= 0)
          goto _L11;
      }
      if ((d < bc) || (d > ec))
        goto _L11;
      qw = font_info[fnt_infos.char_base[f] + d].qqqq;
      if (qw.b0 <= 0)
        goto _L11;
    }
    for (k = 1; k <= np; ++k) {
      if (k == 1) {
        loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
        sw = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
        if (sw > 127)
          sw -= 256;
        loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
        sw = (sw * 256) +
             readU8(tfm_file, tfm_file_mode, &tfm_file_value);
        loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
        sw = (sw * 256) +
             readU8(tfm_file, tfm_file_mode, &tfm_file_value);
        loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
        font_info[fnt_infos.param_base[f]].int_ =
            (sw * 16) +
            (readU8(tfm_file, tfm_file_mode, &tfm_file_value) /
             16);
      } else {
        loadU8(tfm_file, tfm_file_mode, &tfm_file_value);
		fread(&a, sizeof(uint8_t), 1, tfm_file);
		fread(&b, sizeof(uint8_t), 1, tfm_file);
		fread(&c, sizeof(uint8_t), 1, tfm_file);
        d = readU8(tfm_file, tfm_file_mode, &tfm_file_value);
        sw = ((((d * z / 256) + (c * z)) / 256) + (b * z)) / beta;
        if (!a) {
          font_info[fnt_infos.param_base[f] + k - 1].int_ = sw;
        } else if (a == 255)
          font_info[fnt_infos.param_base[f] + k - 1].int_ = sw - alpha;
        else
          goto _L11;
      }
    }
    if (feof(tfm_file))
      goto _L11;
    for (k = np + 1; k <= 7; ++k)
      font_info[fnt_infos.param_base[f] + k - 1].int_ = 0;
    if (np >= 7)
      fnt_infos.font_params[f] = np;
    else
      fnt_infos.font_params[f] = 7;
    fnt_infos.hyphen_char[f] = eqtb[12209].int_;
    fnt_infos.skew_char[f] = eqtb[12210].int_;
    if (bch_label < nl)
      fnt_infos.bchar_label[f] = bch_label + fnt_infos.lig_kern_base[f];
    else
      fnt_infos.bchar_label[f] = 0;
    fnt_infos.font_bchar[f] = bchar;
    fnt_infos.font_false_bchar[f] = bchar;
    if (bchar <= ec) {
      if (bchar >= bc) {
        qw = font_info[fnt_infos.char_base[f] + bchar].qqqq;
        if (qw.b0 > 0)
          fnt_infos.font_false_bchar[f] = 256;
      }
    }
    fnt_infos.font_name[f] = nom;
    fnt_infos.font_area[f] = aire;
    fnt_infos.font_bc[f] = bc;
    fnt_infos.font_ec[f] = ec;
    fnt_infos.font_glue[f] = -1073741824;
    --fnt_infos.param_base[f];
    fmem_ptr += lf;
    font_ptr = f;
    g = f;
    goto _L30;
  _L11:
    print_nl(262);
    print(801);
    sprint_cs(u);
    print_char(61);
    print_file_name(nom, aire, 338);
    if (s >= 0) {
      print(741);
      print_scaled(s);
      print(397);
    } else if (s != (-1000)) {
      print(802);
      print_int(-s);
    }
    if (file_opened)
      print(803);
    else
      print(804);
    help_ptr = 5;
    help_line[4] = 805;
    help_line[3] = 806;
    help_line[2] = 807;
    help_line[1] = 808;
    help_line[0] = 809;
    error();
  _L30:
    if (file_opened)
      b_close(tfm_file);
	{
		const char *tfm_fname = trim_name(name_of_file, file_name_size);
		int nnn = cgo_load_tfm_file(tfm_fname);
		if (nnn < 0) {
			fprintf(stderr, "could not load TFM file [%s]!\n", tfm_fname);
			fprintf(stderr, ">>> n-glyphs: %d\n", nnn);
			fprintf(stderr, ">>> font-id:  %d\n", g);
		}
	}
    return g;
}

} // namespace tex
