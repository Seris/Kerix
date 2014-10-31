#ifndef BOOT_H
#define BOOT_H

#include <boot/multiboot.h>

void kernel_main (int, multiboot_info_t*);

void check_multiboot(int);
short check_protected_mode(void);

#endif