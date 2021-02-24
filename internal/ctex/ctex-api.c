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

int ctex_context_typeset(ctex_t *ctx, const char *tex_fname,
                         const char *dvi_oname, const char *search_dir,
                         const char *working_dir, const char *err_oname) {
  process(ctx, tex_fname, dvi_oname, search_dir, working_dir, err_oname);
  return 0;
}
