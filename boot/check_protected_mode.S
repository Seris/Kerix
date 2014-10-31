.section .text
  .global check_protected_mode
  .type   check_protected_mode, @function

  check_protected_mode:
    pushl %ebp
    movl %esp, %ebp

    pushl %eax
    movl %cr0, %eax
    andl $1, %eax # ax=1 (protected mode), ax=0 (not in protected mode)

    movl %ebp, %esp
    popl %ebp
    ret
    