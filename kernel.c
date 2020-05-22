#include "kernel.h"
#include "utils.h"
#include "char.c"

uint32 vga_index;
static uint32 next_line_index = 1;
uint8 g_fore_color = WHITE, g_back_color = BLUE;
int digit_ascii_codes[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
uint16 cursor_pos = 0, cursor_next_line_index = 1;
#define CALC_SLEEP 8

uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color) 
{
  uint16 ax = 0;
  uint8 ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{
  uint32 i;
  for(i = 0; i < BUFSIZE; i++){
    (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
  }
  next_line_index = 1;
  vga_index = 0;
}

void init_vga(uint8 fore_color, uint8 back_color)
{  
  vga_buffer = (uint16*)VGA_ADDRESS;
  clear_vga_buffer(&vga_buffer, fore_color, back_color);
  g_fore_color = fore_color;
  g_back_color = back_color;
}

void print_new_line()
{
  if(next_line_index >= 55){
    next_line_index = 0;
    clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
  }
  vga_index = 80*next_line_index;
  next_line_index++;
}

void print_char(char ch)
{
  vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
  vga_index++;
}

void print_string(char *str)
{
  uint32 index = 0;
  while(str[index]){
    print_char(str[index]);
    index++;
  }
}

void print_color_string(char *str, uint8 fore_color, uint8 back_color)
{
  uint32 index = 0;
  uint8 fc, bc;
  fc = g_fore_color;
  bc = g_back_color;
  g_fore_color = fore_color;
  g_back_color = back_color;
  while(str[index]){
    print_char(str[index]);
    index++;
  }
  g_fore_color = fc;
  g_back_color = bc;
}

void print_int(int num)
{
  char str_num[digit_count(num)+1];
  itoa(num, str_num);
  print_string(str_num);
}

uint16 get_box_draw_char(uint8 chn, uint8 fore_color, uint8 back_color)
{
  uint16 ax = 0;
  uint8 ah = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  ax |= chn;

  return ax;
}

void gotoxy(uint16 x, uint16 y)
{
  vga_index = 80*y;
  vga_index += x;
}

void draw_generic_box(uint16 x, uint16 y, 
                      uint16 width, uint16 height,
                      uint8 fore_color, uint8 back_color,
                      uint8 topleft_ch,
                      uint8 topbottom_ch,
                      uint8 topright_ch,
                      uint8 leftrightside_ch,
                      uint8 bottomleft_ch,
                      uint8 bottomright_ch)
{
  uint32 i;

  //increase vga_index to x & y location
  vga_index = 80*y;
  vga_index += x;

  //draw top-left box character
  vga_buffer[vga_index] = get_box_draw_char(topleft_ch, fore_color, back_color);

  vga_index++;
  //draw box top characters, -
  for(i = 0; i < width; i++){
    vga_buffer[vga_index] = get_box_draw_char(topbottom_ch, fore_color, back_color);
    vga_index++;
  }

  //draw top-right box character
  vga_buffer[vga_index] = get_box_draw_char(topright_ch, fore_color, back_color);

  // increase y, for drawing next line
  y++;
  // goto next line
  vga_index = 80*y;
  vga_index += x;

  //draw left and right sides of box
  for(i = 0; i < height; i++){
    //draw left side character
    vga_buffer[vga_index] = get_box_draw_char(leftrightside_ch, fore_color, back_color);
    vga_index++;
    //increase vga_index to the width of box
    vga_index += width;
    //draw right side character
    vga_buffer[vga_index] = get_box_draw_char(leftrightside_ch, fore_color, back_color);
    //goto next line
    y++;
    vga_index = 80*y;
    vga_index += x;
  }
  //draw bottom-left box character
  vga_buffer[vga_index] = get_box_draw_char(bottomleft_ch, fore_color, back_color);
  vga_index++;
  //draw box bottom characters, -
  for(i = 0; i < width; i++){
    vga_buffer[vga_index] = get_box_draw_char(topbottom_ch, fore_color, back_color);
    vga_index++;
  }
  //draw bottom-right box character
  vga_buffer[vga_index] = get_box_draw_char(bottomright_ch, fore_color, back_color);

  vga_index = 0;
}

void draw_box(uint8 boxtype, 
              uint16 x, uint16 y, 
              uint16 width, uint16 height,
              uint8 fore_color, uint8 back_color)
{
  switch(boxtype){
    case BOX_SINGLELINE : 
      draw_generic_box(x, y, width, height, 
                      fore_color, back_color, 
                      218, 196, 191, 179, 192, 217);
      break;

    case BOX_DOUBLELINE : 
      draw_generic_box(x, y, width, height, 
                      fore_color, back_color, 
                      201, 205, 187, 186, 200, 188);
      break;
  }
}

void fill_box(uint8 ch, uint16 x, uint16 y, uint16 width, uint16 height, uint8 color)
{
  uint32 i,j;

  for(i = 0; i < height; i++){
    //increase vga_index to x & y location
    vga_index = 80*y;
    vga_index += x;

    for(j = 0; j < width; j++){
      vga_buffer[vga_index] = get_box_draw_char(ch, 0, color);
      vga_index++;
    }
    y++;
  }
}

void clear_screen()
{
  clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
  cursor_pos = 0;
  cursor_next_line_index = 1;
}

uint8 inb(uint16 port)
{
  uint8 data;
  asm volatile("inb %1, %0" : "=a"(data) : "Nd"(port));
  return data;
}

void outb(uint16 port, uint8 data)
{
  asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

void move_cursor(uint16 pos)
{
  outb(0x3D4, 14);
  outb(0x3D5, ((pos >> 8) & 0x00FF));
  outb(0x3D4, 15);
  outb(0x3D5, pos & 0x00FF);
}

void move_cursor_next_line()
{
  cursor_pos = 80 * cursor_next_line_index;
  cursor_next_line_index++;
  move_cursor(cursor_pos);
}

char get_input_keycode()
{
  char ch = 0;
  while((ch = inb(KEYBOARD_PORT)) != 0){
    if(ch > 0)
      return ch;
  }
  return ch;
}

/*
keep the cpu busy for doing nothing(nop)
so that io port will not be processed by cpu
here timer can also be used, but lets do this in looping counter
*/
void wait_for_io(uint32 timer_count)
{
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}

void sleep(uint32 timer_count)
{
  wait_for_io(timer_count*0x02FFFFFF);
}

int read_int()
{
  char ch = 0;
  char keycode = 0;
  char data[32];
  int index = 0;
  do{
    keycode = get_input_keycode();
    if(keycode == KEY_ENTER){
      data[index] = '\0';
      print_new_line();
      break;
    }else{
      ch = get_ascii_char(keycode);
      print_char(ch);
      data[index] = ch;
      index++;
    }
    sleep(CALC_SLEEP);
  }while(ch > 0);

  return atoi(data);
}

char getchar()
{
  char keycode = 0;
  sleep(CALC_SLEEP);
  keycode = get_input_keycode();
  sleep(CALC_SLEEP);
  return get_ascii_char(keycode);
}

void display_menu(uint8 align)
{
  next_line_index += 2;
  gotoxy(align, next_line_index++);
  print_color_string("--- Menu ---", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("1. Fibonacci", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("2. Factorial", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("3. About us", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("4. Exit", WHITE, BLACK);
}
void about(uint8 align) {
  align -= 4;
  next_line_index += 2;
  draw_box(BOX_DOUBLELINE, align - 10, next_line_index, 40, 4, GREY, BLACK);
  gotoxy(align + 6, next_line_index);
  print_color_string(" OS GROUP ", BRIGHT_MAGENTA, BLACK);
  next_line_index += 2;
  gotoxy(align - 8, next_line_index++);
  print_color_string("1. 18127xxx - TRAN MINH DUC", WHITE, BLACK);
  gotoxy(align - 8, next_line_index++);
  print_color_string("2. 18127xxx - NGUYEN VU THU HIEN", WHITE, BLACK);
  gotoxy(align - 8, next_line_index++);
  print_color_string("3. 18127208 - NGO THANH PHUONG THAI", WHITE, BLACK);
}

void read_two_numbers(int* num1, int *num2)
{
  print_string("Enter first number : ");
  sleep(CALC_SLEEP);
  *num1 = read_int();
  print_string("Enter second number : ");
  sleep(CALC_SLEEP);
  *num2 = read_int();
}

void read_number(uint8* num) {
  sleep(CALC_SLEEP);
  *num = read_int();
}

uint32 fib(uint8 n) {
  uint32 a1 = 1, a2 = 1;
  if (n == 1 || n == 2) {
    return 1;
  }

  uint32 i = 3, a;
  while (i <= n) {
    a = a1 + a2;
    a1 = a2;
    a2 = a;
    i++;
  }
  return a;
}

uint32 fac(uint8 n) {
  uint32 fact = 1;
  for (uint8 i = 1; i <= n; ++i) {
    fact *= i;
  }
  return fact;
}

void tool() {

  init_vga(WHITE, BLACK);
  const char* title = "OS GROUP PROJECT";
  uint8 baseAlign = (VGA_MAX_WIDTH/2)-strlen(title)/2;

  uint8 num, choice;
  while(1) {
    next_line_index = 1;
    gotoxy(baseAlign, next_line_index);
    print_color_string(title, BRIGHT_GREEN, BLACK);
    draw_box(BOX_DOUBLELINE, 0, 0, BOX_MAX_WIDTH, BOX_MAX_HEIGHT, CYAN, BLACK);
    display_menu(baseAlign);
    gotoxy(baseAlign, next_line_index++);
    print_color_string("Enter your choice: ", WHITE, BLACK);
    choice = read_int();
    switch(choice){
      case 1:
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Fibonacci of n = ", WHITE, BLACK);
        read_number(&num);
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Result: ", WHITE, BLACK);
        print_int(fib(num));
        break;
      case 2:
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Factorial of n = ", WHITE, BLACK);
        read_number(&num);
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Result: ", WHITE, BLACK);
        print_int(fac(num));
        break;
      case 3:
        clear_screen();
        next_line_index = 1;
        gotoxy(baseAlign, next_line_index);
        print_color_string(title, BRIGHT_GREEN, BLACK);
        draw_box(BOX_DOUBLELINE, 0, 0, BOX_MAX_WIDTH, BOX_MAX_HEIGHT, CYAN, BLACK);
        about(baseAlign);
        break;
      case 4:
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Exiting from Calculator...", WHITE, BLACK);
        sleep(CALC_SLEEP*3);
        clear_screen();
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Exited...", WHITE, BLACK);
        return;
      default:
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Invalid choice...!", WHITE, BLACK);
        break;
    }
    gotoxy(baseAlign, ++next_line_index);
    print_color_string("Press any key to reload screen...", WHITE, BLACK);
    getchar();
    clear_screen();
  }
}

void kernel_entry()
{
  getchar();
  tool();
}
