#include "boot.h"
#include <boot/early_console.h>
#include <boot/multiboot.h>
#include <kernel/printk.h>
#include <kernel/panic.h>

void check_multiboot(int magic){
  printk(KERN_INFO "checking machine state...\n");

  if(magic != MULTIBOOT_BOOTLOADER_MAGIC)
    panic("Not a multiboot system (invalid magic)");

  if(check_protected_mode() == 0)
    panic("Not a multiboot system (not in protected mode)");
}


void kernel_main (int magic, multiboot_info_t* multiboot_info) {
  early_console_init();
  printk("early_console in kernel_main\n");

  printk("magic: (%p)\n", &magic);

  check_multiboot(magic);

  panic("lol");
}
