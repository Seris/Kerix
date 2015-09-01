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
    cli
    
    # Setting up stack
    mov $stack_start, %esp
    xor %ebp, %ebp
    push %ebp

    push %ebx
    push %eax
    call kernel_main


  .global halt_system
  .type   halt_system, @function
  
  halt_system:
    hlt
  hang_up:
    jmp hang_up


.section .bootstrap_stack
  stack_end:
    .space 4096 * 4
  stack_start: