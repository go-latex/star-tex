// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "ctex-io.h"

void loadU8(FILE *r, int *mode, uint8_t *v) {
  if (*mode == 1) {
    fread(v, sizeof(uint8_t), 1, r);
  } else {
    *mode = 1;
  }
}

uint8_t *readU8(FILE *r, int *mode, uint8_t *v) {
  if (*mode == 1) {
    *mode = 2;
    fread(v, sizeof(uint8_t), 1, r);
  }
  return v;
}

void loadU32(FILE *r, int *mode, memory_word *v) {
  if (*mode == 1) {
    fread(&v, sizeof(memory_word), 1, r);
  } else {
    *mode = 1;
  }
}

memory_word *readU32(FILE *r, int *mode, memory_word *v) {
  if (*mode == 1) {
    *mode = 2;
    fread(&v, sizeof(memory_word), 1, r);
  }
  return v;
}

void writeU32(FILE *w, int *mode, memory_word *v) {
  fwrite(v, sizeof(memory_word), 1, w);
  *mode = 0;
}

int erstat(FILE *f) { return (f == NULL) || (ferror(f) != 0); }

int fpeek(FILE *f) {
  int c = fgetc(f);
  ungetc(c, f);
  return c;
}

void break_in(FILE *ios, bool_t v) {}

bool_t eoln(FILE *f) {
  int c = fpeek(f);
  return (c == EOF) || (c == '\n');
}

const char *trim_name(char *filename,
                      size_t length) // never called on a string literal;
                                     // note the lack of a const
{
  for (char *p = filename + length - 1; *p == ' '; --p)
    *p = '\0';

  return filename;
}

void io_error(int error, const char *name) {}
