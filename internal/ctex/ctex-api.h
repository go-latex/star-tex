#ifndef CTEX_API_H
#define CTEX_API_H 1

#include "ctex.h"

#ifdef __cplusplus
extern "C" {
#endif

ctex_t *ctex_new_context();
void ctex_del_context(ctex_t **ctx);

int ctex_context_typeset(ctex_t *ctx, const char *oname, const char *istream,
                         const char *ostream);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CTEX_API_H */
