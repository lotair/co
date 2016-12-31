#include "switch.h"
#include <stdio.h>

co_ctx_t ctx[1000], ctx_main;

void func(void* argv) {
  int x = (uintptr_t)argv;
  printf("enter fuck -> %d\n", x);
  co_switch(ctx + x, &ctx_main);
  printf("leave fuck -> %d\n", x);
}

#include <stdlib.h>

void co_ctx_with_stack_init(co_ctx_t* ctx, size_t stack_size) {
  co_ctx_init(ctx);
  ctx->ss_sp    = malloc(stack_size);
  ctx->ss_size  = stack_size;
  ctx->uc_link  = NULL;
}

#define UTHREAD_MAX_NUM 1000

int main() {
  co_ctx_with_stack_init(&ctx_main, 4 * 1024);

  for (int i = 0; i < UTHREAD_MAX_NUM; i++) {
    co_ctx_with_stack_init(ctx + i, 4 * 1024);
    ctx[i].uc_link = &ctx_main;
    co_ctx_make(ctx + i, func, (void *)(uintptr_t)i);
  }

  while (1) {
    int done = 0;
    for (int i = 0; i < UTHREAD_MAX_NUM; i++) {
      if (ctx[i].finish == 0) {
        done = 1;
        co_switch(&ctx_main, ctx + i);
      }
    }
    if (done == 0) break;
  }

  for (int i = 0; i < UTHREAD_MAX_NUM; i++) {
    free(ctx[i].ss_sp);
  }
  free(ctx_main.ss_sp);

  printf("switch to over...\n");

  return 0;
}

