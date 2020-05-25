#include "tools.h"





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
void read_string(char* res)
{
  char ch = 0;
  char keycode = 0;
  int index = 0;
  do{
    keycode = get_input_keycode();
    if (keycode == KEY_ENTER){
      res[index] = '\0';
      print_new_line();
      break;
    } else if (keycode == KEY_BACKSPACE) {
      if (index > 0) {
        --index;
        backspace();
      }
    } else {
      ch = get_ascii_char(keycode);
      print_char(ch);
      res[index] = ch;
      index++;
    }
    sleep(CALC_SLEEP);
  } while(ch > 0);
}
void read_pass(char* res)
{
  char ch = 0;
  char keycode = 0;
  int index = 0;
  do{
    keycode = get_input_keycode();
    if (keycode == KEY_ENTER){
      res[index] = '\0';
      print_new_line();
      break;
    } else if (keycode == KEY_BACKSPACE) {
      if (index > 0) {
        --index;
        backspace();
      }
    } else{
      ch = get_ascii_char(keycode);
      print_char('*');
      res[index] = ch;
      index++;
    }
    sleep(CALC_SLEEP);
  } while(ch > 0);
}

uint8 match(char* a, char* b) {
  uint8 i = 0;
  if (strlen(a) == strlen(b)) {
    for (int i = 0; i < strlen(a); ++i) {
      if (a[i] != b[i]) {
        return 0;
      }
    }
    return 1;
  }
  return 0;
}

uint8 signIn(uint32 align, uint32 line) {
  gotoxy(align, line++);
  print_color_string("Username: ", BLUE, BLACK);
  uint8 isMatch;
  char input[10];
  read_string(input);
  isMatch = match(input, "ADMIN");

  sleep(CALC_SLEEP);
  gotoxy(align, line++);
  print_color_string("Password: ", BLUE, BLACK);
  
  read_string(input);
  
  isMatch = match(input, "12345");

  if (isMatch == 1) {
    gotoxy(align+5, ++line);
    print_color_string("MATCH", CYAN, BLACK);
    sleep(CALC_SLEEP + 2);
    clear_screen();
    return 1;
  } else {
    gotoxy(align+4, ++line);
    print_color_string("NOT MATCH", BRIGHT_RED, BLACK);
  }

  return 0;
}