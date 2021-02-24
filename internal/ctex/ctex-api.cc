#include "ctex-api.h"

#include "tex.hpp"

tex::tex *to_tex(context_t ctx) { return reinterpret_cast<tex::tex *>(ctx); }

context_t ctex_new_context() {
  auto ctx = new tex::tex();
  return reinterpret_cast<context_t>(ctx);
}

void ctex_del_context(context_t *ctx) {
  tex::tex *tex = reinterpret_cast<tex::tex *>(*ctx);
  delete tex;
  tex = nullptr;
}

int ctex_context_typeset(context_t ctx, const char *tex_fname,
                         const char *dvi_oname, const char *search_dir,
                         const char *working_dir, const char *err_oname) {
  auto ctex = to_tex(ctx);

  ctex->process(tex_fname, dvi_oname, search_dir, working_dir, err_oname);

  return 0;
}
