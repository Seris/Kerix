#include <register.h>

void get_register_content(register_t* reg){
  register uint32_t eax asm("eax"), ebx asm("ebx"),
                    ecx asm("ecx"), edx asm("edx");

  reg->eax = eax;
  reg->ebx = ebx;
  reg->ecx = ecx;
  reg->edx = edx;
}