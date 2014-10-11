#include <libk/string.h>

void* memmove (void* dstptr, const void* srcptr, size_t size) {
  unsigned char* dst = (unsigned char*) dstptr;
  const unsigned char* src = (const unsigned char*) srcptr;
  if ( dst < src ){
    size_t i;
    for (i = 0; i < size; i++) {
      dst[i] = src[i];
    }
  } else {
    size_t i;
    for (i = size; i != 0; i--) {
      dst[i-1] = src[i-1];
    }
  }
  return dstptr;
}
