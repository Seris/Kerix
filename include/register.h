#ifndef REGISTER_H
#define REGISTER_H

#include <stdint.h>

typedef struct {
  uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp;
  uint32_t eip, cs, eflags, useresp, ss;
} register_t;

void get_register_content(register_t*);

#endif