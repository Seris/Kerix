#ifndef KERNEL_PIC_H
#define KERNEL_PIC_H

#include <stdint.h>

#define MPIC_CMD_ADDR 0x20
#define MPIC_DAT_ADDR 0x21

#define SPIC_CMD_ADDR 0xA0
#define SPIC_DAT_ADDR 0xA1

#define PIC_CMD_INIT 0x11
#define PIC_CMD_EOI  0x20

void pic_remap(uint32_t, uint32_t);
void pic_sendEOI(uint32_t);

#endif
