#include <boot/descriptor_table.h>
#include <kernel/interrupt/interrupt.h>
#include <kernel/printk.h>
#include <kernel/panic.h>

int_desc_t interrupt_list[256];

void isr_handler(int_reg_t reg){
  if(interrupt_list[reg.int_no].flags & 1){
    printk(KERN_DEBUG "isr_handler() - interrupt %u (%s)\n",
      reg.int_no, interrupt_list[reg.int_no].name);
  
    if(interrupt_list[reg.int_no].flags & 0b10){
      panic(interrupt_list[reg.int_no].name);
    }
  }
}
