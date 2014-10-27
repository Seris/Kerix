#include <boot/main.h>
#include <boot/early_console.h>

void kernel_main (void) {
  early_console_init();
  current_tty->write("Kerix - Early console ready\n");
}