#define offset_rbx  0
#define offset_rbp  8
#define offset_r12  16
#define offset_r13  24
#define offset_r14  32
#define offset_r15  40
#define offset_rdi  48
#define offset_rsi  56
#define offset_rdx  64
#define offset_rcx  72
#define offset_r8   80
#define offset_r9   88
#define offset_rsp  96
#define offset_rip  104

.global co_set
.type co_set @function
co_set: /* co_set(co_ctx_t*) */
  /* load sp */
  movq offset_rsp(%rdi), %rsp

  /* callee preserved load */
  movq offset_rbx(%rdi), %rbx
  movq offset_rbp(%rdi), %rbp
  movq offset_r12(%rdi), %r12
  movq offset_r13(%rdi), %r13
  movq offset_r14(%rdi), %r14
  movq offset_r15(%rdi), %r15

  movq offset_rip(%rdi), %rcx
  pushq %rcx

  /* input arguments load */
  movq offset_rdi(%rdi), %rsi
  movq offset_rdx(%rdi), %rdx
  movq offset_rcx(%rdi), %rcx
  movq offset_r8(%rdi), %r8
  movq offset_r9(%rdi), %r9

  /* finally %rsi */
  movq offset_rsi(%rdi), %rdi

  xorl %eax, %eax
  ret

.global co_switch
.type co_switch, @function
co_switch: /* co_switch(co_ctx_t* co_ctx_t*) */
  /* callee preserved save */
  movq %rbx, offset_rbx(%rdi)
  movq %rbp, offset_rbp(%rdi) 
  movq %r12, offset_r12(%rdi) 
  movq %r13, offset_r13(%rdi) 
  movq %r14, offset_r14(%rdi) 
  movq %r15, offset_r15(%rdi) 

  /* input arguments save */
  movq %rdi, offset_rdi(%rdi) 
  movq %rsi, offset_rsi(%rdi) 
  movq %rdx, offset_rdx(%rdi) 
  movq %rcx, offset_rcx(%rdi) 
  movq %r8, offset_r8(%rdi) 
  movq %r9, offset_r9(%rdi) 

  /* ip save */
  movq (%rsp), %rcx
  movq %rcx, offset_rip(%rdi)

  /* return address save */
  leaq 8(%rsp), %rcx
  movq %rcx, offset_rsp(%rdi)

  /* load sp */
  movq offset_rsp(%rsi), %rsp

  /* callee preserved load */
  movq offset_rbx(%rsi), %rbx
  movq offset_rbp(%rsi), %rbp
  movq offset_r12(%rsi), %r12
  movq offset_r13(%rsi), %r13
  movq offset_r14(%rsi), %r14
  movq offset_r15(%rsi), %r15

  movq offset_rip(%rsi), %rcx
  pushq %rcx

  /* input arguments load */
  movq offset_rdi(%rsi), %rdi
  movq offset_rdx(%rsi), %rdx
  movq offset_rcx(%rsi), %rcx
  movq offset_r8(%rsi), %r8
  movq offset_r9(%rsi), %r9

  /* finally %rsi */
  movq offset_rsi(%rsi), %rsi

  xorl %eax, %eax
  ret

