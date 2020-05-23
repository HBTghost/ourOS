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
    } else{
      ch = get_ascii_char(keycode);
      print_char(ch);
      res[index] = ch;
      index++;
    }
    sleep(2);
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
    } else{
      ch = get_ascii_char(keycode);
      print_char('*');
      res[index] = ch;
      index++;
    }
    sleep(2);
  } while(ch > 0);
}

uint8 match(char* a, char* b) {
  uint8 i = 0;
  for (; i < 32 && a[i] != '\0'; ++i) {
    if (a[i] != b[i]) {
      return 0;
    }
  }
  return a[i] == b[i]; 
}

uint8 signIn(uint32 align, uint32 line) {
  gotoxy(align, line++);
  print_color_string("Username: ", BLUE, BLACK);
  uint8 isMatch;
  char* input;
  read_string(input);
  isMatch = match(input, "ADMIN\0");

  sleep(2);
  gotoxy(align, line++);
  print_color_string("Password: ", BLUE, BLACK);
  read_pass(input);
  isMatch = isMatch && match(input, "12345678\0");

  gotoxy(align, line++);
  if (isMatch) {
    print_color_string("MATCH", BLUE, BLACK);
    sleep(2);
    return 1;
  } else {
    print_color_string("NOT MATCH", RED, BLACK);
  }

  return 0;
}