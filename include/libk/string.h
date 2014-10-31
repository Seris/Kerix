#ifndef LIBK_STRING_H
#define LIBK_STRING_H

#include <stddef.h>
#include <stdint.h>

int   memcmp (const void*, const void*, size_t);
void* memcpy (void*, const void*, size_t);
void* memmove (void*, const void*, size_t);
void* memset (void*, int, size_t);

size_t ulongtostr(uint32_t, char*, short);
size_t longtostr(int32_t, char*, short);
size_t uintostr(uint16_t, char*, short);
size_t intostr(int16_t, char*, short);

#endif
