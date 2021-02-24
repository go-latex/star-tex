#ifndef CTEX_API_H
#define CTEX_API_H 1

#include "ctex.h"

#ifdef __cplusplus
extern "C" {
#endif

ctex_t *ctex_new_context();
void ctex_del_context(ctex_t **ctx);

int ctex_context_typeset(ctex_t *ctx, const char *tex_fname,
                         const char *dvi_oname, const char *search_dir,
                         const char *working_dir, const char *err_oname);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CTEX_API_H */
