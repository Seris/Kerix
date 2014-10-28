#ifndef KERNEL_IO_kprint_H
#define KERNEL_IO_kprint_H

#include <stdarg.h>

int kprint(const char*, ...);
int skprint(char*, const char*, ...);
int vsprintf(char *, const char*, va_list);

#endif