/**
 * Send "End of Interrupt" signal to the PIC
 */

#include <kernel/pic.h>
#include <libk/asm/ioport.h>

void pic_sendEOI(uint32_t irq){
  if(irq >= 8){
    outl(SPIC_CMD_ADDR, PIC_CMD_EOI);
  }
  outl(MPIC_CMD_ADDR, PIC_CMD_EOI);
}