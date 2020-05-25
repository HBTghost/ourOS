#include "kernel.h"
#include "utils.h"
#include "char.c"
#include "time.h"
#include "tools.h"

uint8 validation() {
  init_vga(WHITE, BLACK);
  const char* title = "OS GROUP PROJECT";
  uint8 baseAlign = (VGA_MAX_WIDTH/2)-strlen(title)/2;

  while(1) {
    next_line_index = 1;
    gotoxy(baseAlign, ++next_line_index);
    ++next_line_index;
    print_color_string(title, BRIGHT_GREEN, BLACK);
    draw_generic_box(0, 0, BOX_MAX_WIDTH, BOX_MAX_HEIGHT, BROWN, BLACK, 14, 14, 14, 14, 14, 14);
    draw_generic_box(baseAlign-2, 1, strlen(title)+2, 1, DARK_GREY, BLACK, 3, 3, 3, 3, 3, 3);


    next_line_index += 6;
    draw_generic_box(baseAlign-2, next_line_index, 18, 4, MAGENTA, BLACK, 3, 3, 3, 3, 3, 3);
    gotoxy(baseAlign+4, next_line_index++);
    print_color_string(" LOG IN ", YELLOW, BLACK);
    if (signIn(baseAlign, next_line_index)) {
      break;
    }

    next_line_index += 4;
    gotoxy(baseAlign-8, next_line_index);
    print_color_string("Press any key to reload screen...", WHITE, BLACK);
    getchar();
    clear_screen();
  }
  tool();
}

void display_menu(uint8 align)
{
  next_line_index += 2;
  gotoxy(align+3, next_line_index++);
  print_color_string(" MENU ", YELLOW, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("1. CLOCK", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("2. Fibonacci", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("3. Factorial", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("4. About us", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("5. Exit", WHITE, BLACK);
}
void about(uint8 align)
{
  align -= 4;
  next_line_index += 2;
  draw_box(BOX_DOUBLELINE, align - 10, next_line_index, 40, 4, GREY, BLACK);
  gotoxy(align + 6, next_line_index);
  print_color_string(" OS GROUP ", BRIGHT_MAGENTA, BLACK);
  next_line_index += 2;
  gotoxy(align - 8, next_line_index++);
  print_color_string("1. 18127027 - TRAN MINH DUC", WHITE, BLACK);
  gotoxy(align - 8, next_line_index++);
  print_color_string("2. 18127004 - NGUYEN VU THU HIEN", WHITE, BLACK);
  gotoxy(align - 8, next_line_index++);
  print_color_string("3. 18127208 - NGO THANH PHUONG THAI", WHITE, BLACK);
}

void read_two_numbers(int *num1, int *num2)
{
  print_string("Enter first number : ");
  sleep(CALC_SLEEP);
  *num1 = read_int();
  print_string("Enter second number : ");
  sleep(CALC_SLEEP);
  *num2 = read_int();
}

void read_number(uint8 *num)
{
  sleep(CALC_SLEEP);
  *num = read_int();
}

void tool() {

  init_vga(WHITE, BLACK);
  const char* title = "OS GROUP PROJECT";
  uint8 baseAlign = (VGA_MAX_WIDTH/2)-strlen(title)/2;

  uint8 num;
  int choice;
  while(1) {
    next_line_index = 1;
    gotoxy(baseAlign, ++next_line_index);
    ++next_line_index;
    print_color_string(title, BRIGHT_GREEN, BLACK);
    draw_generic_box(0, 0, BOX_MAX_WIDTH, BOX_MAX_HEIGHT, CYAN, BLACK, 14, 14, 14, 14, 14, 14);
    draw_generic_box(baseAlign-2, 1, strlen(title)+2, 1, GREY, BLACK, 3, 3, 3, 3, 3, 3);


    ++next_line_index;

    draw_generic_box(baseAlign-1, next_line_index+2, 16, 5, MAGENTA, BLACK, 3, 3, 3, 3, 3, 3);
    display_menu(baseAlign+2);
    next_line_index += 2;
    gotoxy(baseAlign-1, next_line_index++);
    print_color_string("Enter your choice: ", WHITE, BLACK);
    choice = read_int();
    switch(choice){
      case 1:
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("TIME NOW: ", BRIGHT_RED, BLACK);
        print_time_locale();
        break;
      case 2:
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Fibonacci of n = ", BRIGHT_RED, BLACK);
        read_number(&num);
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Result: ", BRIGHT_RED, BLACK);
        print_int(fib(num));
        break;
      case 3:
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Factorial of n = ", BRIGHT_RED, BLACK);
        read_number(&num);
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Result: ", BRIGHT_RED, BLACK);
        print_int(fac(num));
        break;
      case 4:
        clear_screen();
        next_line_index = 1;
        gotoxy(baseAlign, ++next_line_index);
        ++next_line_index;
        print_color_string(title, BRIGHT_GREEN, BLACK);
        draw_generic_box(0, 0, BOX_MAX_WIDTH, BOX_MAX_HEIGHT, CYAN, BLACK, 14, 14, 14, 14, 14, 14);
        draw_generic_box(baseAlign-2, 1, strlen(title)+2, 1, GREY, BLACK, 3, 3, 3, 3, 3, 3);


        ++next_line_index;

        about(baseAlign+1);
        break;
      case 5:
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Exiting from Calculator...", WHITE, BLACK);
        sleep(CALC_SLEEP*3);
        clear_screen();
        for (int i = 0; i < 12; ++i) {
          draw_box(BOX_DOUBLELINE, baseAlign-1-2*i, next_line_index+10-i, 18+4*i, 1+2*i, i, BLACK);
        }
        gotoxy(baseAlign, next_line_index+11);
        print_char(' ');
        print_char(3);
        print_char(3);
        print_char(3);
        print_color_string(" GOOD BYE ", YELLOW, BLACK);
        print_char(3);
        print_char(3);
        print_char(3);
        print_char(' ');
        return;
      default:
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Invalid choice...!", WHITE, BLACK);
        break;
    }
    next_line_index += 2;
    gotoxy(baseAlign-8, next_line_index);
    print_color_string("Press any key to reload screen...", WHITE, BLACK);
    getchar();
    clear_screen();
  }
}

void kernel_entry()
{
  sleep(CALC_SLEEP);
  //getchar();
  validation();

}
