#include <kernel/io/kprint.h>
#include <stdarg.h>
#include <stdint.h>
#include <tty/tty.h>
#include <libk/string.h>

int vskprint(char *buf, const char *fmt, va_list args){
  unsigned int i;
  int d;

  char* str;
  char tmp[256];

  short base;

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
        d = va_arg(args, int);
        intostr(d, tmp, base);
        str = (char*) tmp;
        break;

      case 'x':
        base = 16;
      case 'u':
        d = va_arg(args, unsigned int);
        uintostr(d, tmp, base);
        str = (char*) tmp;
        break;

      case 'p':
        d = (long) va_arg(args, void*);
        ulongtostr(d, tmp, 16);
        str = (char*) tmp;
        break;

      case 's':
        str = va_arg(args, char*);
        break;

      default:
        continue;
    }

    for(; *str != '\0'; str++)
      buf[i++] = *str;
  }

  return i;
}

int kprint(const char *fmt, ...){
  char printf_buf[1024];
  va_list args;
  int printed;

  va_start(args, fmt);
  printed = vskprint(printf_buf, fmt, args);
  va_end(args);

  current_tty->write(printf_buf);

  return printed;
}
