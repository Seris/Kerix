#include <kernel/panic.h>
#include <kernel/printk.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void display_stack_trace(unsigned int maxFrames){
  register uint32_t* ebp asm("ebp");
  uint32_t* frame = ebp;
  for(unsigned int i = 0; i < maxFrames; i++){
    printk("\t#%u: [0x%p]\n", i, frame);
    frame = (uint32_t*) *frame;

    if(frame == 0)
      break;
  }
}

void panic(const char* str, ...){
  va_list args;

  printk(KERN_PANIC);
  va_start(args, str);
  vprintk(str, args);
  va_end(args);
  printk("\n");

  display_stack_trace(STACK_TRACE_FRAMES);
}