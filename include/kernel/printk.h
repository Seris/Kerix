#ifndef KERNEL_PRINTK_H
#define KERNEL_PRINTK_H

#include <stdarg.h>
#include <stddef.h>

#define KERN_SOH        "\001"

#define KERN_PANIC      KERN_SOH "0"
#define KERN_ALERT      KERN_SOH "1"
#define KERN_CRIT       KERN_SOH "2"
#define KERN_ERR        KERN_SOH "3"
#define KERN_WARNING    KERN_SOH "4"
#define KERN_NOTICE     KERN_SOH "5"
#define KERN_INFO       KERN_SOH "6"
#define KERN_DEBUG      KERN_SOH "7"

// Default log level
#define KERN_DEFAULT    KERN_SOH "d"

size_t printk(const char *fmt, ...);
size_t sprintk(char* buf, const char* fmt, ...);

size_t vprintk(const char *fmt, va_list args);
size_t vsprintk(char *buf, const char *fmt, va_list args);

size_t parse_kernel_soh(const char* fmt, char buf[], size_t* n);

#endif