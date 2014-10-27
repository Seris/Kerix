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
uint32_t line_size    = 80;
uint32_t lines_number = 25;

uint32_t current_line;
uint32_t current_offset;

uint16_t console_font_color = EARLY_CONSOLE_COLOR_WHITE;
uint16_t console_background = EARLY_CONSOLE_COLOR_BLACK;

void early_console_init (void){
  early_console_tty.write = &early_console_write;
  current_tty = &early_console_tty;
  early_console_clean();
}

size_t early_console_write(char* str){
  size_t i;
  for(i = 0; str[i] != 0; i++){
    switch (str[i]){
      case '\n':
        early_console_new_line();
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

void early_console_mv_line(uint32_t src, uint32_t dest){
  uint32_t src_pos = src * line_size * 2;

  uint32_t j = 0;
  for(uint32_t i = 0; i < line_size * 2; i += 2){
    early_console_put_chat_at(vga_buffer[src_pos + i], dest, j);
    early_console_put_chat_at(' ', src, j++);
  }
}

void early_console_new_line(void){
  current_offset = 0;
  if(++current_line == lines_number){
    current_line--;
    for(uint32_t l = 1; l < lines_number; l++){
      early_console_mv_line(l, l - 1);
    }
  }
}

void early_console_clean(void){
  current_line = 0;
  current_offset  = 0;
  for(size_t i = 0; i < line_size * lines_number; i++){
    early_console_push_char(' ');
  }
  current_line = 0;
  current_offset  = 0;
}

void early_console_push_char(char c){
  early_console_put_chat_at(c, current_line, current_offset);
  if(++current_offset == line_size)
    early_console_new_line();
}

void early_console_put_chat_at(char c, uint32_t row, uint32_t column){
  uint32_t cursor = (row * line_size + column) * 2;
  vga_buffer[cursor] = c;
  vga_buffer[++cursor] = console_font_color | console_background << 4;
}