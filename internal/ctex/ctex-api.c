#include "ctex-api.h"

ctex_t *ctex_new_context() {
  ctex_t *ctx = (ctex_t *)(malloc(sizeof(ctex_t)));
  ctex_init_ctx(ctx);
  return ctx;
}

void ctex_del_context(ctex_t **ctx) {
  free(*ctx);
  *ctx = NULL;
}

int ctex_context_typeset(ctex_t *ctx, const char *oname, const char *istream,
                         const char *ostream) {
  typeset(ctx, oname, istream, ostream);
  return 0;
}
