/**
 * interrupt handling
 * 
 */

#ifndef KERNEL_INTERRUPT_INTERRUPT_H
#define KERNEL_INTERRUPT_INTERRUPT_H

#include <stdint.h>

typedef struct {
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, useresp, ss;
} int_reg_t;


typedef struct {
  char* name;
  uint8_t flags;
  void* custom_handler;
} int_desc_t;
/**
 * flags
 * [ - | - | - | - | - | H | F | D ]
 * D : 1 if the entry is defined, 0 otherwise.
 * F : 1 if the interrupt is fatal. If CH is 1,
 *     the custom handler will be called nevertheless.
 * H : if 1, a custom handler will be called. (a)
 * - : unused
 *
 * (a) the custom handler will be called with 1 parameter:
 *     void isr_handler_x(int_reg_t *reg);
 */

void interrupt_init(void);
void isr_handler(int_reg_t);

// INTEL
extern void isr_0(void);
extern void isr_1(void);
extern void isr_2(void);
extern void isr_3(void);
extern void isr_4(void);
extern void isr_5(void);
extern void isr_6(void);
extern void isr_7(void);
extern void isr_8(void);
extern void isr_9(void);
extern void isr_10(void);
extern void isr_11(void);
extern void isr_12(void);
extern void isr_13(void);
extern void isr_14(void);
extern void isr_16(void);
extern void isr_17(void);
extern void isr_18(void);
extern void isr_19(void);
extern void isr_20(void);

// IRQs
extern void isr_32(void);
extern void isr_33(void);

// Kerix
extern void isr_70(void);


#endif
