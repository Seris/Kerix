#include <libk/string.h>
#include <kernel/interrupt/interrupt.h>
#include <boot/descriptor_table.h>

extern int_desc_t interrupt_list[256];

void interrupt_init(void){
  memset(&interrupt_list, 0, sizeof(int_desc_t) * 256);

  interrupt_list[0]  = (int_desc_t) { .name = "Divide Error", .flags = 0b001 };
  interrupt_list[1]  = (int_desc_t) { .name = "Debug Exception", .flags = 0b001 };
  interrupt_list[2]  = (int_desc_t) { .name = "NMI Interrupt", .flags = 0b001 };
  interrupt_list[3]  = (int_desc_t) { .name = "Breakpoint", .flags = 0b001 };
  interrupt_list[4]  = (int_desc_t) { .name = "Overflow", .flags = 0b001 };
  interrupt_list[5]  = (int_desc_t) { .name = "Bound Range Exceeded", .flags = 0b001 };
  interrupt_list[6]  = (int_desc_t) { .name = "Invalid Opcode", .flags = 0b001 };
  interrupt_list[7]  = (int_desc_t) { .name = "Device Not Available", .flags = 0b001 };
  interrupt_list[8]  = (int_desc_t) { .name = "Double Fault", .flags = 0b011 };
  interrupt_list[9]  = (int_desc_t) { .name = "Coprocessor Segment Overrun", .flags = 0b001 };
  interrupt_list[10] = (int_desc_t) { .name = "Invalid TSS", .flags = 0b001 };
  interrupt_list[11] = (int_desc_t) { .name = "Segment Not Present", .flags = 0b001 };
  interrupt_list[12] = (int_desc_t) { .name = "Stack Segment Fault", .flags = 0b001 };
  interrupt_list[13] = (int_desc_t) { .name = "General Protection Fault", .flags = 0b011 };
  interrupt_list[14] = (int_desc_t) { .name = "Page Fault", .flags = 0b001 };
  interrupt_list[16] = (int_desc_t) { .name = "x87 FPU Floating Point Error", .flags = 0b001 };
  interrupt_list[17] = (int_desc_t) { .name = "Alignmement Check", .flags = 0b001 };
  interrupt_list[18] = (int_desc_t) { .name = "Machine Check", .flags = 0b011 };
  interrupt_list[19] = (int_desc_t) { .name = "SMID Floating Point Exception", .flags = 0b001 };
  interrupt_list[20] = (int_desc_t) { .name = "Virtualization Exception Fault", .flags = 0b001 };

  interrupt_list[32] = (int_desc_t) { .name = "System Clock", .flags = 0b001 };
  interrupt_list[33] = (int_desc_t) { .name = "Keyboard Interrupt", .flags = 0b001 };
}
