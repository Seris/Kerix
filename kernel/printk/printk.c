#include <kernel/printk.h>
#include <libk/string.h>
#include <tty/tty.h>
#include <stddef.h>
#include <stdarg.h>

size_t parse_kernel_soh(const char* fmt, char buf[], size_t* n){
  if(*fmt == *KERN_SOH){
    *n = 2;
    switch(*(++fmt)){
      case '0':
        memcpy((void*) buf, "<panic> : ", 10);
        return 10;

      case '1':
        memcpy((void*) buf, "<alert> : ", 10);
        return 10;

      case '2':
        memcpy((void*) buf, "<crit> : ", 9);
        return 9;

      case '3':
        memcpy((void*) buf, "<error> : ", 10);
        return 10;

      case '4':
        memcpy((void*) buf, "<warning> : ", 10);
        return 10;

      case '5':
        memcpy((void*) buf, "<notice> : ", 9);
        return 9;

      case 'd':
      case '6':
        memcpy((void*) buf, "<info> : ", 9);
        return 9;

      case '7':
        memcpy((void*) buf, "<debug> : ", 10);
        return 10;
    }
  }

  *n = 0;
  return 0;
}


size_t vsprintk(char *buf, const char *fmt, va_list args){
  unsigned int i;

  char* str;
  char tmp[256];

  short base;

  size_t n;
  size_t off = parse_kernel_soh(fmt, buf, &n);

  buf += off;
  fmt += n;

  for(i = 0; *fmt != '\0'; fmt++){
    if(*fmt != '%'){
      buf[i++] = *fmt;
      continue;
    }

    base = 10;

    fmt++;
    switch(*fmt){
      case 'i':
        base = 16;
      case 'd':
        intostr(va_arg(args, int), tmp, base);
        str = (char*) tmp;
        break;

      case 'x':
        base = 16;
      case 'u':
        uintostr(va_arg(args, unsigned int), tmp, base);
        str = (char*) tmp;
        break;

      case 'o':
        uintostr(va_arg(args, unsigned int), tmp, 8);
        str = (char*) tmp;
        break;

      case 'p':
        ulongtostr((long) va_arg(args, void*), tmp, 16);
        str = (char*) tmp;
        break;

      case 's':
        str = va_arg(args, char*);
        break;

      case 'L':
        base = 16;
      case 'l':
        ulongtostr(va_arg(args, long), tmp, base);
        str = tmp;
        break;

      case 'n':
        base = 16;
      case 'N':
        ulongtostr(va_arg(args, unsigned long), tmp, base);
        str = tmp;
        break;

      case '%':
        buf[i++] = '%';
        continue;

      case 'c':
        buf[i++] = (char) va_arg(args, int);
        continue;

      default:
        continue;
    }

    for(; *str != '\0'; str++)
      buf[i++] = *str;
  }

  buf[i++] = '\0';

  return i;
}


size_t sprintk(char* buf, const char* fmt, ...){
  va_list args;

  va_start(args, fmt);
  size_t printed = vsprintk(buf, fmt, args);
  va_end(args);

  return printed;
}


size_t vprintk(const char *fmt, va_list args){
  char parsed_str[1024];
  vsprintk((char*) parsed_str, fmt, args);
  return printk(fmt);
}


size_t printk(const char *fmt, ...){
  char parsed_str[1024];

  va_list args;

  va_start(args, fmt);
  size_t printed = vsprintk((char*) parsed_str, fmt, args);
  va_end(args);

  current_tty->write(parsed_str);

  return printed;
}
