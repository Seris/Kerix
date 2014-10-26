#ifndef BOOT_EARLY_CONSOLE_H
#define BOOT_EARLY_CONSOLE_H

#include <tty/tty.h>

void early_console_init (void);
size_t early_console_write(char*);
void early_console_clean(void);
void next_line(void);
void early_console_push_char(char);

#endif
