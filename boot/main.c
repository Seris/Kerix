#include "boot.h"
#include <boot/multiboot.h>
#include <boot/early_console.h>
#include <boot/descriptor_table.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/interrupt/irq.h>

multiboot_info_t *mb_info;

void check_multiboot(int magic){
  if(magic != MULTIBOOT_BOOTLOADER_MAGIC){
    panic("Not a multiboot system (invalid magic)");
  }

  if(check_protected_mode() == 0){
    panic("Not in protected mode");
  }
}

void kernel_main(int magic, multiboot_info_t* mbi) {
  early_console_init();
  printk("early_console in kernel_main()\n");

  mb_info = mbi;

  // Check if the bootloader is multiboot 0.6 compliant
  printk(KERN_DEBUG "checking machine state...\n");
  check_multiboot(magic);
  
  // Install GDT/IDT
  printk(KERN_DEBUG "loading GDT... ");
  gdt_install();
  printk("done\n");

  printk(KERN_DEBUG "loading IDT... ");
  idt_install();
  printk("done\n");

  printk(KERN_DEBUG "configuring IRQs... ");
  irq_configure();
  printk("done\n");

}

/*
  multiboot_mmap *ptr;
  uint32_t length = mb_info->mmap_length;
  size_t memsize = 0;

  printk("mmap length: %u, address: %p\n\n", length, mb_info->mmap_addr);

  for (ptr = (multiboot_mmap*) mb_info->mmap_addr;
      (uint32_t) ptr <= mb_info->mmap_addr + length;
      ptr = (multiboot_mmap*) ((uint32_t) ptr + ptr->size + sizeof(ptr->size)))
  {
    printk(
      "addr: %p, length: %X, size: %X, type: %X\n",
      ptr->base_addr_low, ptr->length_low, ptr->size, ptr->type
    );

    memsize += ptr->length_low;
  }
  */