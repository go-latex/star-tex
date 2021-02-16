#ifndef CTEX_API_H
#define CTEX_API_H 1

#ifdef __cplusplus
extern "C" {
#endif

typedef void* context_t;

context_t ctex_new_context();
void ctex_del_context(context_t *ctx);

int
ctex_context_typeset(
		context_t ctx,
		const char* tex_fname,
		const char* dvi_oname,
		const char* search_dir, const char* working_dir,
		const char* err_oname);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CTEX_API_H */
