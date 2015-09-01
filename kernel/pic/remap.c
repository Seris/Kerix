#include <libk/asm/ioport.h>
#include <kernel/pic.h>
#include <kernel/printk.h>

void pic_remap(uint32_t mas_offset, uint32_t sla_offset){
  // Saving pic data
  uint8_t mdat = inb(MPIC_DAT_ADDR),
          sdat = inb(SPIC_DAT_ADDR);

  // Initialization sequence
  outb(MPIC_CMD_ADDR, PIC_CMD_INIT);
  io_wait();
  outb(SPIC_CMD_ADDR, PIC_CMD_INIT);
  io_wait();

  // Configuring vector offset
  outl(MPIC_DAT_ADDR, mas_offset);
  io_wait();
  outl(SPIC_DAT_ADDR, sla_offset);
  io_wait();

  // Cascade mode
  outb(MPIC_DAT_ADDR, 4);
  io_wait();
  outb(SPIC_DAT_ADDR, 2);
  io_wait();

  outb(MPIC_DAT_ADDR, 1);
  io_wait();
  outb(SPIC_DAT_ADDR, 1);
  io_wait();

  // Restore pic data
  outb(MPIC_DAT_ADDR, mdat);
  io_wait();
  outb(SPIC_DAT_ADDR, sdat);
  io_wait();
}
