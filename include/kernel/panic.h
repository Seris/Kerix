#ifndef KERNEL_PANIC_H
#define KERNEL_PANIC_H

#include <stddef.h>

#define STACK_TRACE_FRAMES 10

void panic(const char* str, ...);
void display_stack_trace(unsigned int maxFrames);

#endif