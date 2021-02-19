// Copyright ©2021 The star-tex Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef CTEX_CAPI_IO_H
#define CTEX_CAPI_IO_H 1

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int ctex_io_file;

extern ctex_io_file ctex_io_open(const char *name);

extern ctex_io_file ctex_io_create(const char *name);

extern int ctex_io_fflush(ctex_io_file fd);

extern int ctex_io_fwrite(ctex_io_file fd, const uint8_t *data,
                          const uint_t size);

extern int ctex_io_fclose(ctex_io_file fd);

extern int ctex_io_fwriteln(ctex_io_file fd);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CTEX_CAPI_IO_H */
