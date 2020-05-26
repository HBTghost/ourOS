#include "kernel.h"
#include "utils.h"
#include "char.c"
#include "time.h"
#include "tools.h"

void display_menu(uint8 align)
{
  next_line_index += 2;
  gotoxy(align+3, next_line_index++);
  print_color_string(" MENU ", YELLOW, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("1. Time now", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("2. Fibonacci", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("3. Factorial", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("4. About us", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("5. Edit pass", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("6. History", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("7. Log out", WHITE, BLACK);
  gotoxy(align, next_line_index++);
  print_color_string("8. Exit", WHITE, BLACK);
}
void about(uint8 align)
{
  align -= 4;
  next_line_index += 2;
  draw_box(BOX_DOUBLELINE, align - 10, ++next_line_index, 39, 5, MAGENTA, BLACK);
  gotoxy(align + 6, next_line_index);
  print_color_string(" OS GROUP ", YELLOW, BLACK);
  next_line_index += 2;
  gotoxy(align - 7, next_line_index++);
  print_color_string("1. 18127027 - TRAN MINH DUC", WHITE, BLACK);
  gotoxy(align - 7, next_line_index++);
  print_color_string("2. 18127004 - NGUYEN VU THU HIEN", WHITE, BLACK);
  gotoxy(align - 7, next_line_index);
  print_color_string("3. 18127208 - NGO THANH PHUONG THAI", WHITE, BLACK);
  next_line_index += 2;
}

void read_number(uint8 *num)
{
  sleep(CALC_SLEEP);
  *num = read_int();
}

uint8 tool() {

  init_vga(WHITE, BLACK);
  const char* title = " OS GROUP PROJECT ";
  uint8 baseAlign = (VGA_MAX_WIDTH/2)-strlen(title)/2;

  uint8 num;
  int choice;
  while(1) {
    next_line_index = 1;
    draw_generic_box(0, 1, BOX_MAX_WIDTH, BOX_MAX_HEIGHT-1, BROWN, BLACK, 4, 4, 4, 4, 4, 4);
    gotoxy(baseAlign, 1);
    print_color_string(title, BRIGHT_MAGENTA, BLACK);
    draw_generic_box(baseAlign-1, 0, strlen(title), 1, BRIGHT_GREEN, BLACK, 3, 3, 3, 3, 3, 3);

    ++next_line_index;

    draw_box(BOX_DOUBLELINE, baseAlign, next_line_index+2, 16, 8, MAGENTA, BLACK);
    display_menu(baseAlign+3);
    next_line_index += 2;
    gotoxy(baseAlign-1, next_line_index++);
    print_color_string("Enter your choice: ", WHITE, BLACK);
    choice = read_int();
    switch(choice){
      case 1:
        gotoxy(baseAlign-10, ++next_line_index);
        print_color_string("Time now: ", BRIGHT_BLUE, BLACK);
        print_color_string("Result: ", BRIGHT_BLUE, BLACK);
        char timeString[24] = {0};
        time_t_clone t;
        read_time(&t);
        convert_asc(timeString, &t);
        print_string(timeString);
        
        //next_line_index += 2;
        //gotoxy(baseAlign-7, next_line_index);
        //print_color_string("Press any key to reload screen...", WHITE, BLACK);
        //getchar();
        //clear_screen();
        break;
      case 2:
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Fibonacci of n = ", BRIGHT_BLUE, BLACK);
        read_number(&num);
        if (!num) {
          ++next_line_index;
          goto DEF;
        }
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Result: ", BRIGHT_BLUE, BLACK);
        print_int(fib(num));
        break;
      case 3:
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Factorial of n = ", BRIGHT_BLUE, BLACK);
        read_number(&num);
        if (!num) {
          ++next_line_index;
          goto DEF;
        }
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Result: ", BRIGHT_BLUE, BLACK);
        print_int(fac(num));
        break;
      case 4:
        clear_screen();
        next_line_index = 1;
        draw_generic_box(0, 1, BOX_MAX_WIDTH, BOX_MAX_HEIGHT-1, BROWN, BLACK, 4, 4, 4, 4, 4, 4);
        gotoxy(baseAlign, 1);
        print_color_string(title, BRIGHT_MAGENTA, BLACK);
        draw_generic_box(baseAlign-1, 0, strlen(title), 1, BRIGHT_GREEN, BLACK, 3, 3, 3, 3, 3, 3);
        about(baseAlign+2);
        ++next_line_index;
        break;
      case 5:
        if (!validateUser(baseAlign, next_line_index)) {
          next_line_index += 2;
          break;
        } else {
          changePass(baseAlign, next_line_index);
          next_line_index += 3;
        }
        break;
      case 6:
        showHistory(baseAlign, next_line_index);
        next_line_index += 10;
        break;
      case 7:
        return 1;
      case 8:
        gotoxy(baseAlign-4, ++next_line_index);
        print_color_string("Exiting from Calculator...", BRIGHT_BLUE, BLACK);
        sleep(CALC_SLEEP*3);
        clear_screen();
        for (int i = 0; i < 12; ++i) {
          draw_box(BOX_DOUBLELINE, baseAlign-1-2*i, 11-i, 18+4*i, 1+2*i, i, BLACK);
        }
        gotoxy(baseAlign, 12);
        print_char(' ');
        print_char(3);
        print_char(3);
        print_char(3);
        print_color_string(" GOOD BYE ", YELLOW, BLACK);
        print_char(3);
        print_char(3);
        print_char(3);
        print_char(' ');
        return 0;
      DEF:
      default:
        gotoxy(baseAlign, ++next_line_index);
        print_color_string("Invalid choice...!", BRIGHT_RED, BLACK);
        break;
    }
    next_line_index += 2;
    gotoxy(baseAlign-7, next_line_index);
    print_color_string("Press any key to reload screen...", WHITE, BLACK);
    getchar();
    clear_screen();
  }
}

uint8 validation() {
  init_vga(WHITE, BLACK);
  const char* title = " OS GROUP PROJECT ";
  uint8 baseAlign = (VGA_MAX_WIDTH/2)-strlen(title)/2;

  while(1) {
    next_line_index = 1;
    draw_generic_box(0, 1, BOX_MAX_WIDTH, BOX_MAX_HEIGHT-1, BROWN, BLACK, 4, 4, 4, 4, 4, 4);
    gotoxy(baseAlign, 1);
    print_color_string(title, BRIGHT_MAGENTA, BLACK);
    draw_generic_box(baseAlign-1, 0, strlen(title), 1, GREY, BLACK, 3, 3, 3, 3, 3, 3);


    next_line_index += 6;
    // draw_generic_box(baseAlign-2, next_line_index, 18, 4, MAGENTA, BLACK, 3, 3, 3, 3, 3, 3);
    draw_box(BOX_DOUBLELINE, baseAlign - 1, next_line_index, 18, 4, MAGENTA, BLACK);
    gotoxy(baseAlign+5, next_line_index++);
    print_color_string(" LOG IN ", YELLOW, BLACK);
    if (signIn(baseAlign+1, next_line_index)) {
      if (!tool()) {
        return;
      }
      next_line_index += 4;
      sleep(CALC_SLEEP);
    } else {
      next_line_index += 7;
      gotoxy(baseAlign-7, next_line_index);
      print_color_string("Press any key to reload screen...", WHITE, BLACK);
      getchar();
    }
    clear_screen();
  }
}

void kernel_entry()
{
  sleep(CALC_SLEEP);
  validation();
}
