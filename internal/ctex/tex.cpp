// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "tex.hpp"

namespace tex {

	internal_font_number
	  tex::read_font_info(halfword u, str_number nom,
                                      str_number aire, scaled s) {
    font_index k;
    bool file_opened = false;
    halfword lf, lh, bc, ec, nw, nh, nd, ni, nl, nk, ne, np;
    internal_font_number f, g = 0;
    eight_bits a, b, c, d;
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
	  fread(&a, sizeof(eight_bits), 1, tfm_file);
	  fread(&b, sizeof(eight_bits), 1, tfm_file);
	  fread(&c, sizeof(eight_bits), 1, tfm_file);
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
	  fread(&a, sizeof(eight_bits), 1, tfm_file);
	  fread(&b, sizeof(eight_bits), 1, tfm_file);
	  fread(&c, sizeof(eight_bits), 1, tfm_file);
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
		fread(&a, sizeof(eight_bits), 1, tfm_file);
		fread(&b, sizeof(eight_bits), 1, tfm_file);
		fread(&c, sizeof(eight_bits), 1, tfm_file);
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
