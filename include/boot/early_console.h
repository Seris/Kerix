#ifndef BOOT_EARLY_CONSOLE_H
#define BOOT_EARLY_CONSOLE_H

#include <tty/tty.h>
#include <stdint.h>

void early_console_init (void);
size_t early_console_write(char*);
void early_console_clean(void);
void early_console_new_line(void);
void early_console_push_char(char);
void early_console_mv_line(uint32_t src, uint32_t dest);
void early_console_put_chat_at(char c, uint32_t row, uint32_t column);

#endif
