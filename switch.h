#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
#ifndef CO_CPP_BEGIN
#define CO_CPP_BEGIN extern "C" {
#endif
#ifndef CO_CPP_END
#define CO_CPP_END   }
#endif
#else
#ifndef CO_CPP_BEGIN
#define CO_CPP_BEGIN
#endif
#ifndef CO_CPP_END
#define CO_CPP_END
#endif
#endif

#ifdef __linux__
  
#ifdef __x86_64__

CO_CPP_BEGIN

/* Type for general register */
typedef long long int greg_t;

/* Number of general registers */
#define NGREG 14

#endif

/* Userlevel context.  */
typedef struct co_ctx_t
{
  greg_t gregs[NGREG];
  struct co_ctx_t *uc_link;
  void*  ss_sp;
  size_t ss_size;
  int    finish;
} co_ctx_t;

typedef void (*co_ctx_func_t)(void* argv);

void co_ctx_init(co_ctx_t* ctx);
co_ctx_t* co_ctx_create();
void co_ctx_make(co_ctx_t* ctx, co_ctx_func_t fn, void* argv);
extern void co_switch(co_ctx_t* old_ctx, co_ctx_t* new_ctx);

CO_CPP_END

#endif


