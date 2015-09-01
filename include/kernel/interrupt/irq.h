#ifndef KERNEL_INTERRUPT_IRQ_H
#define KERNEL_INTERRUPT_IRQ_H

#define MPIC_IRQ_OFFSET 0x20
#define SPIC_IRQ_OFFSET 0x28

void irq_configure(void);
void irq_set_mask(uint8_t irq);
void irq_clear_mask(uint8_t irq);

#endif