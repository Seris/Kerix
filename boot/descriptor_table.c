/*
 * Initialize GDT / IDT 
 */

#include <boot/descriptor_table.h>
#include <kernel/interrupt/interrupt.h>
#include <kernel/printk.h>
#include <kernel/panic.h>
#include <libk/string.h>

/*===========================
=            GDT            =
===========================*/

gdt_ptr_t gdt_pointer;
gdt_entry_t gdt_entries[GDT_EARLY_ENTRY_NUMBER];

void gdt_install(void){
  gdt_pointer.base = (uint32_t) &gdt_entries;
  gdt_pointer.limit = sizeof(gdt_entry_t) * GDT_EARLY_ENTRY_NUMBER - 1;

  gdt_set_gate(0, 0, 0, 0, 0); // NULL Descriptor
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xC0); // Code Segment 
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xC0); // Data Segment

  load_gdt((uint32_t) &gdt_pointer);
}

void gdt_set_gate(uint32_t gate, uint32_t base, uint32_t limit, uint8_t access, uint8_t flag){
  gdt_entry_t *entry = &gdt_entries[gate];

  entry->base_low = base & 0xFFFF;
  entry->base_mid = (base >> 16) & 0xFF;
  entry->base_high = (base >> 24) & 0xFF;

  entry->limit_low = limit & 0xFFFF;
  entry->gran = (limit >> 16) & 0xF;

  entry->gran |= flag & 0xF0;
  entry->access = access;
}

/*-----  End of GDT  ------*/



/*===========================
=            IDT            =
===========================*/

idt_ptr_t idt_pointer;
idt_entry_t idt_entries[256];

void idt_install(void){
  idt_pointer.base = (uint32_t) &idt_entries;
  idt_pointer.limit = sizeof(idt_entry_t) * 256 - 1;
  memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

  interrupt_init();

  idt_set_gate(0,  (uint32_t) isr_0,  0x08, 0x8E);
  idt_set_gate(1,  (uint32_t) isr_1,  0x08, 0x8E);
  idt_set_gate(2,  (uint32_t) isr_2,  0x08, 0x8E);
  idt_set_gate(3,  (uint32_t) isr_3,  0x08, 0x8E);
  idt_set_gate(4,  (uint32_t) isr_4,  0x08, 0x8E);
  idt_set_gate(5,  (uint32_t) isr_5,  0x08, 0x8E);
  idt_set_gate(6,  (uint32_t) isr_6,  0x08, 0x8E);
  idt_set_gate(7,  (uint32_t) isr_7,  0x08, 0x8E);
  idt_set_gate(8,  (uint32_t) isr_8,  0x08, 0x8E);
  idt_set_gate(9,  (uint32_t) isr_9,  0x08, 0x8E); 
  idt_set_gate(10, (uint32_t) isr_10, 0x08, 0x8E);
  idt_set_gate(11, (uint32_t) isr_11, 0x08, 0x8E);
  idt_set_gate(12, (uint32_t) isr_12, 0x08, 0x8E);
  idt_set_gate(13, (uint32_t) isr_13, 0x08, 0x8E);
  idt_set_gate(14, (uint32_t) isr_14, 0x08, 0x8E);
  idt_set_gate(16, (uint32_t) isr_16, 0x08, 0x8E);
  idt_set_gate(17, (uint32_t) isr_17, 0x08, 0x8E);
  idt_set_gate(18, (uint32_t) isr_18, 0x08, 0x8E);
  idt_set_gate(19, (uint32_t) isr_19, 0x08, 0x8E);
  idt_set_gate(20, (uint32_t) isr_20, 0x08, 0x8E);


  idt_set_gate(32, (uint32_t) isr_32, 0x08, 0x8E);
  idt_set_gate(33, (uint32_t) isr_33, 0x08, 0x8E);

  idt_set_gate(70, (uint32_t) isr_70, 0x08, 0x8E);

  load_idt((uint32_t) &idt_pointer);
}

void idt_set_gate(uint32_t entry, uint32_t base, uint16_t sel, uint8_t flags){
  idt_entries[entry].base_low = base & 0xFFFF;
  idt_entries[entry].base_high = (base >> 16) & 0xFFFF;

  idt_entries[entry].selector = sel;
  idt_entries[entry].flags = flags;
  idt_entries[entry].zero = 0;
}

/*-----  End of IDT  ------*/

