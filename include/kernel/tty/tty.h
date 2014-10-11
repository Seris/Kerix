#ifndef KERNEL_TTY_H
#define KERNEL_TTY_H

#include <stddef.h>

struct console {
  char[16] name;
  void (*write)(char* str);
  void (*read)(size_t size);
};

#endif