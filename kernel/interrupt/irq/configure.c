#include <kernel/interrupt/interrupt.h>
#include <kernel/interrupt/irq.h>
#include <libk/asm/ioport.h>
#include <kernel/pic.h>

extern int_desc_t interrupt_list[256];

void irq_configure(void){
  // Remap IRQ to avoid conflict with Intel Interrupts (thx IBM)
  pic_remap(MPIC_IRQ_OFFSET, SPIC_IRQ_OFFSET);
  irq_clear_mask(1);
}

void irq_set_mask(uint8_t irq){
  uint16_t port;
  if(irq < 8){
    port = MPIC_DAT_ADDR;
  } else {
    port = SPIC_DAT_ADDR;
    irq -= 8;
  }

  uint8_t value = inb(port) | (1 << irq);
  outb(port, value);
  io_wait();
}

void irq_clear_mask(uint8_t irq){
  uint16_t port;
  if(irq < 8){
    port = MPIC_DAT_ADDR;
  } else {
    port = SPIC_DAT_ADDR;
    irq -= 8;
  }

  uint8_t value = inb(port) & ~(1 << irq);
  outb(port, value);
  io_wait();
}