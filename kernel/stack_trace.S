.section .rodata
  stack_line: .string "\t#%d: %p\n\0"

.section .text
  .global display_stack_tracef
  .type   display_stack_tracef, @function

  display_stack_tracef:
    push %ebp
    mov %esp, %ebp

    # %ecx = maxFrames
    mov 8(%ebp), %ecx
    mov %ebp, %eax

print_next_frame:  
    push %eax
    push %ecx
    push $stack_line
    call printk
    add  $4, %esp

    xor %ecx, %ecx
    pop %ecx
    pop %eax

    mov (%eax), %eax
    cmp $0, %eax
    loopne print_next_frame
    
    mov %ebp, %esp
    pop %ebp
    ret