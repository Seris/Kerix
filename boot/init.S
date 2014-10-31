.section .data
  .set ALIGN,    1<<0
  .set MEMINFO,  1<<1
  .set FLAGS,    ALIGN | MEMINFO
  .set MAGIC,    0x1BADB002
  .set CHECKSUM, -(MAGIC + FLAGS)


.section .multiboot
  .align 4
  .long MAGIC
  .long FLAGS
  .long CHECKSUM


.section .text
  .global _start
  .type   _start, @function

  _start:
    # Setting up stack
    mov $stack_start, %esp
    xor %ebp, %ebp
    push %ebp
    cli

    push %ebx
    push %eax
    call kernel_main

    hlt
    .hang_up: jmp .hang_up


.section .bss
  stack_end:
    .zero 16384
  stack_start: