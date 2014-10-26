#include <boot/early_console.h>
#include <tty/tty.h>
#include <stdint.h>

tty_t early_console_tty;

enum early_console_color {
  EARLY_CONSOLE_COLOR_BLACK         = 0,
  EARLY_CONSOLE_COLOR_BLUE          = 1,
  EARLY_CONSOLE_COLOR_GREEN         = 2,
  EARLY_CONSOLE_COLOR_CYAN          = 3,
  EARLY_CONSOLE_COLOR_RED           = 4,
  EARLY_CONSOLE_COLOR_MAGENTA       = 5,
  EARLY_CONSOLE_COLOR_BROWN         = 6,
  EARLY_CONSOLE_COLOR_LIGHT_GREY    = 7,
  EARLY_CONSOLE_COLOR_DARK_GREY     = 8,
  EARLY_CONSOLE_COLOR_LIGHT_BLUE    = 9,
  EARLY_CONSOLE_COLOR_LIGHT_GREEN   = 10,
  EARLY_CONSOLE_COLOR_LIGHT_CYAN    = 11,
  EARLY_CONSOLE_COLOR_LIGHT_RED     = 12,
  EARLY_CONSOLE_COLOR_LIGHT_MAGENTA = 13,
  EARLY_CONSOLE_COLOR_LIGHT_BROWN   = 14,
  EARLY_CONSOLE_COLOR_WHITE         = 15,
};


char* vga_buffer = (char*) 0xB8000;
unsigned int line_size    = 80;
unsigned int lines_number = 25;

unsigned int current_line;
unsigned int current_offset;

uint16_t console_font_color = EARLY_CONSOLE_COLOR_WHITE;
uint16_t console_background = EARLY_CONSOLE_COLOR_BLACK;

void early_console_init (void){
  early_console_tty.write = &early_console_write;
  current_tty = &early_console_tty;
  early_console_clean();
}

size_t early_console_write(char* str){
  unsigned int i;
  for(i = 0; str[i] != 0; i++){
    switch (str[i]){
      case '\n':
        next_line();
        break;

      case '\e':
        break;

      default:
        early_console_push_char(str[i]);
        break;
    }
  }

  return i;
}

void early_console_clean(void){
  size_t s = line_size * lines_number * 2;
  do {
    vga_buffer[--s] = 0;
  } while(s > 0);
  current_line = 0;
  current_offset  = 0;
}

/**
 * New line
 */
void next_line(void){
  current_offset = 0;
  if(++current_line == lines_number){
    current_line--;
  }
}

void early_console_push_char(char c){
  unsigned int cursor = (current_line * line_size + current_offset) * 2;
  vga_buffer[cursor] = c;
  vga_buffer[++cursor] = console_font_color | console_background << 4;
  if(++current_offset == line_size)
    next_line();
}