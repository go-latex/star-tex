// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef CTEX_IO_H
#define CTEX_IO_H 1

#include <stdint.h>
#include <stdio.h>

#include "ctex-capi-types.h"

#ifdef __cplusplus
extern "C" {
#endif

void loadU8(FILE *r, int *mode, uint8_t *v);
uint8_t *readU8(FILE *r, int *mode, uint8_t *v);
void loadU32(FILE *r, int *mode, memory_word *v);
memory_word *readU32(FILE *r, int *mode, memory_word *v);
void writeU32(FILE *w, int *mode, memory_word *v);

int erstat(FILE *f);
int fpeek(FILE *f);
void break_in(FILE *ios, bool_t);
bool_t eoln(FILE *f);

const char *trim_name(char *filename,
                      size_t length); // never called on a string literal;
                                      // note the lack of a const
void io_error(int error, const char *name);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CTEX_IO_H */
