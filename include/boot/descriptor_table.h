#ifndef BOOT_DESCRIPTOR_TABLE_H
#define BOOT_DESCRIPTOR_TABLE_H

#include <stdint.h>

/*===========================
=            GDT            =
===========================*/

#define GDT_EARLY_ENTRY_NUMBER 3

struct gdt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr_t;

struct gdt_entry {
  uint16_t limit_low, base_low;
  uint8_t base_mid, access, gran, base_high;
} __attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

void gdt_install(void);
void gdt_set_gate(uint32_t, uint32_t, uint32_t, uint8_t, uint8_t);
extern void load_gdt(uint32_t);

/*-----  End of GDT  ------*/



/*===========================
=            IDT            =
===========================*/

struct idt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

struct idt_entry {
  uint16_t base_low, selector;
  uint8_t zero, flags;
  uint16_t base_high;
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;

void idt_install(void);
void idt_set_gate(uint32_t, uint32_t, uint16_t, uint8_t);
extern void load_idt(uint32_t);

/*-----  End of IDT  ------*/


#endif
