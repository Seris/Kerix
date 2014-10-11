#include <libk/string.h>
 
void* memcpy (void* dstptr, const void* srcptr, size_t size) {
  unsigned char* dst = (unsigned char*) dstptr;
  const unsigned char* src = (const unsigned char*) srcptr;

  size_t i;
  for (i = 0; i < size; i++)
    dst[i] = src[i];
  return dstptr;
}