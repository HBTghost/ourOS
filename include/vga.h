#ifndef VGA_H
#define VGA_H
#include "kernel.h"

static uint32 vga_index;
static uint8 g_fore_color = WHITE;
static uint8 g_back_color = BLUE;
static uint32 next_line_index= 1;

static uint16 cursor_pos =0;
static uint16 cursor_next_line_index =1 ;
uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color);
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color);
void init_vga(uint8 fore_color, uint8 back_color);
void gotoxy(uint16 x, uint16 y);
void draw_generic_box(uint16 x, uint16 y,
                      uint16 width, uint16 height,
                      uint8 fore_color, uint8 back_color,
                      uint8 topleft_ch,
                      uint8 topbottom_ch,
                      uint8 topright_ch,
                      uint8 leftrightside_ch,
                      uint8 bottomleft_ch,
                      uint8 bottomright_ch);
void draw_box(uint8 boxtype,
              uint16 x, uint16 y,
              uint16 width, uint16 height,
              uint8 fore_color, uint8 back_color);
void fill_box(uint8 ch, uint16 x, uint16 y, uint16 width, uint16 height, uint8 color);
void clear_screen();
uint16 get_box_draw_char(uint8 chn, uint8 fore_color, uint8 back_color);
void print_new_line();

void print_char(char ch);
void print_string(char *str);
void print_color_string(char *str, uint8 fore_color, uint8 back_color);
void print_int(int num); 
void move_cursor(uint16 pos);
void move_cursor_next_line();

#endif