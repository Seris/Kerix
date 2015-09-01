.macro gen_noerr_isr id
  .global isr_\id
  .type isr_\id, @function

  isr_\id:
    cli
    push $0
    push $\id
    jmp isr_wrapper
.endm

.macro gen_errisr id
  .global isr_\id
  .type isr_\id, @function

  isr_\id:
    cli
    push $\id
    jmp isr_wrapper
.endm

.section .text
  isr_wrapper:
    pusha
    call isr_handler
    popa
    addl $8, %esp
    sti
    iret

  isr_base_pointer:
    // Intel
    GEN_NOERR_ISR 0
    GEN_NOERR_ISR 1
    GEN_NOERR_ISR 2
    GEN_NOERR_ISR 3
    GEN_NOERR_ISR 4
    GEN_NOERR_ISR 5
    GEN_NOERR_ISR 6
    GEN_NOERR_ISR 7
    GEN_NOERR_ISR 9
    GEN_NOERR_ISR 16
    GEN_NOERR_ISR 18
    GEN_NOERR_ISR 19
    GEN_NOERR_ISR 20
    GEN_ERRISR    8
    GEN_ERRISR    10
    GEN_ERRISR    11
    GEN_ERRISR    12
    GEN_ERRISR    13
    GEN_ERRISR    14
    GEN_ERRISR    17

    // IRQs
    GEN_NOERR_ISR 32
    GEN_NOERR_ISR 33

    // Kerix
    GEN_NOERR_ISR 70
    
