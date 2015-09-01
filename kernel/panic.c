#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/halt.h>
#include <register.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void display_stack_trace(int maxFrames){
  register uint32_t* ebp asm("ebp");
  uint32_t* frame = ebp;
  for(int i = 0; i < maxFrames; i++){
    printk("\t#%d: [%p]\n", i, frame);
    frame = (uint32_t*) *frame;

    if(frame == 0)
      break;
  }
}

void panic(const char* str, ...){
  va_list args;

  printk("\nKernel Panic : ");
  va_start(args, str);
  vprintk(str, args);
  va_end(args);
  printk("\n");

  printk("Stack trace: \n");
  display_stack_trace(STACK_TRACE_FRAMES);

  printk(KERN_INFO "halting system");
  halt_system();
}