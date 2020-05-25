#include "kernel.h"
#include "utils.h"
#include "char.c"
#include "time.h"


#define  CALC_SLEEP 1


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
  print_color_string("3. Time", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("4. About us", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("5. Exit", WHITE, BLACK);
  gotoxy(align, next_line_index++);
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

uint32 fib(uint8 n)
{
  uint32 a1 = 1, a2 = 1;
  if (n == 1 || n == 2)
  {
    return 1;
  }

  uint32 i = 3, a;
  while (i <= n)
  {
    a = a1 + a2;
    a1 = a2;
    a2 = a;
    i++;
  }
  return a;
}

uint32 fac(uint8 n)
{
  uint32 fact = 1;
  for (uint8 i = 1; i <= n; ++i)
  {
    fact *= i;
  }
  return fact;
}

void tool()
{

  init_vga(WHITE, BLACK);
  const char *title = "OS GROUP PROJECT";
  uint8 baseAlign = (VGA_MAX_WIDTH / 2) - strlen(title) / 2;

  uint8 num, choice;
  while (1)
  {
    next_line_index = 1;
    gotoxy(baseAlign, next_line_index);
    print_color_string(title, BRIGHT_GREEN, BLACK);
    draw_box(BOX_DOUBLELINE, 0, 0, BOX_MAX_WIDTH, BOX_MAX_HEIGHT, CYAN, BLACK);
    display_menu(baseAlign);
    gotoxy(baseAlign, next_line_index++);
    print_color_string("Enter your choice: ", WHITE, BLACK);
    choice = read_int();
    switch (choice)
    {
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
      gotoxy(baseAlign, ++next_line_index);
      print_color_string("Time:", RED, BLACK);
      //print_time_now_struct();
      print_time_locale();
      break;
    case 4:
      clear_screen();
      next_line_index = 1;
      gotoxy(baseAlign, next_line_index);
      print_color_string(title, BRIGHT_GREEN, BLACK);
      draw_box(BOX_DOUBLELINE, 0, 0, BOX_MAX_WIDTH, BOX_MAX_HEIGHT, CYAN, BLACK);
      about(baseAlign);
      break;
    case 5:
      gotoxy(baseAlign, ++next_line_index);
      print_color_string("Exiting from Calculator...", WHITE, BLACK);
      sleep(CALC_SLEEP * 3);
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
