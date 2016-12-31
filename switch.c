#include "switch.h"

#ifdef __x86_64__

CO_CPP_BEGIN
  extern void __co_start();
CO_CPP_END

/* Number of each register in the `gregset_t' array.  */
enum
{
  REG_RBX = 0,
# define REG_RBX  REG_RBX
  REG_RBP,
# define REG_RBP  REG_RBP
  REG_R12,
# define REG_R12  REG_R12
  REG_R13,
# define REG_R13  REG_R13
  REG_R14,
# define REG_R14  REG_R14
  REG_R15,
# define REG_R15  REG_R15

  REG_RDI,
# define REG_RDI  REG_RDI
  REG_RSI,
# define REG_RSI  REG_RSI
  REG_RDX,
# define REG_RDX  REG_RDX
  REG_RCX,
# define REG_RCX  REG_RCX
  REG_R8,
# define REG_R8   REG_R8
  REG_R9,
# define REG_R9   REG_R9

  REG_RSP,
# define REG_RSP  REG_RSP
  REG_RIP
# define REG_RIP  REG_RIP
};

#include <stdlib.h>
#include <unistd.h>

void co_ctx_init(co_ctx_t* ctx) {
  memset(ctx, 0, sizeof(co_ctx_t));
}

co_ctx_t* co_ctx_create() {
  co_ctx_t* ctx = (co_ctx_t *)malloc(sizeof(co_ctx_t));
  co_ctx_init(ctx);
  return ctx;
}

void co_ctx_make(co_ctx_t* ctx, co_ctx_func_t fn, void* argv) {
  greg_t *sp;
  
  sp = (greg_t *)((uintptr_t)ctx->ss_sp + ctx->ss_size);
  sp -= 2;
  sp = (greg_t *)((((uintptr_t)sp) & -16L) - 8);

  ctx->gregs[REG_RIP] = (uintptr_t)fn;
  ctx->gregs[REG_RBX] = (uintptr_t)&sp[1];
  ctx->gregs[REG_RSP] = (uintptr_t)sp;

  ctx->gregs[REG_RDI] = (uintptr_t)argv;

  sp[0] = (uintptr_t)&__co_start;
  sp[1] = (uintptr_t)ctx->uc_link;
  sp[2] = (uintptr_t)&ctx->finish;
}


#endif

