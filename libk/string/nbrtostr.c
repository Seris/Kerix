#include <libk/string.h>
#include <stddef.h>
#include <stdint.h>

size_t ulongtostr(uint32_t n, char* buf, short base,){
  char* digits = "0123456789abcdefghijklmnopqrstuvwxyz";
  char tmp_str[128];

  size_t i = 0, j = 0;

  do {
    tmp_str[j++] = digits[n % base];
    n /= base;
  } while(n > 0);

  do {
    buf[i++] = tmp_str[--j];
  } while(j > 0);

  buf[i+1] = '\0';

  return i;
}


size_t longtostr(int32_t n, char* buf, short base){
  size_t i = 0;

  if(n < 0){
    n = -n;
    buf[i++] = '-';
  }

  i += ulongtostr((uint32_t) n, buf + i, base);
  return i;
}


size_t uintostr(uint16_t n, char* buf, short base){
  return ulongtostr((uint32_t) n, buf, base);
}


size_t intostr(int16_t n, char* buf, short base){
  return longtostr((int32_t) n, buf, base);
}