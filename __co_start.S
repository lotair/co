.global __co_start
.type __co_start, @function
__co_start:
  pushq %rax
  movq 8(%rbx), %rax
  movl $1, (%rax)
  popq %rax

  movq %rbx, %rsp 
  popq %rdi
  testq %rdi, %rdi
  je 2f
  callq co_set
2:
  movq $0, %rdi
  callq exit
  hlt
