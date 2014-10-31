#ifndef TTY_TTY_H
#define TTY_TTY_H

#include <stddef.h>

typedef struct {
  size_t (*write)(char*);
  size_t (*read)(char*, size_t);
  size_t tabsize;
} tty_t;

tty_t* current_tty;

#endif