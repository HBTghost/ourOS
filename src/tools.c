#include "tools.h"

char pwd[10] = "\0";
uint8 times = 0;
char loginTimes[5][40];
char logoutTimes[5][40];

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

char* getPass(char* pass) {
  if (match(pwd, "\0")) {
    pass = "12345\0";
  } else {
    pass = pwd;
  }
  return pass;
}

void addLoginTimes() {
  times %= 5;
  get_cur_time(loginTimes[times]);
}
void addLogoutTimes() {
  get_cur_time(logoutTimes[times++]);
}

uint8 signIn(uint32 align, uint32 line) {
  gotoxy(align, line++);
  print_color_string("Username: ", BRIGHT_BLUE, BLACK);
  uint8 isMatch;
  char input[10];
  read_string(input);
  isMatch = match(input, "ADMIN\0");

  sleep(CALC_SLEEP);
  gotoxy(align, line++);
  print_color_string("Password: ", BRIGHT_BLUE, BLACK);
  
  read_pass(input);
  
  char* pass;
  isMatch = match(input, getPass(pass));

  if (isMatch == 1) {
    gotoxy(align+2, ++line);
    print_color_string("SUCCESSFULLY", BRIGHT_GREEN, BLACK);
    addLoginTimes();
    sleep(CALC_SLEEP + 2);
    clear_screen();
    return 1;
  } else {
    gotoxy(align+1, ++line);
    print_color_string("UNSUCCESSFULLY", BRIGHT_RED, BLACK);
  }

  return 0;
}

uint8 validateUser(uint32 align, uint32 line) {
  sleep(CALC_SLEEP);
  gotoxy(align-2, line+1);
  print_color_string("Enter current password: ", BRIGHT_BLUE, BLACK);
  char input[10], pass[10];
  read_pass(input);
  if (match(input, getPass(pass))) {
    gotoxy(align-2, line+2);
    print_color_string("Password is correct!", BRIGHT_GREEN, BLACK);
    sleep(CALC_SLEEP + 2);
    return 1;
  } else {
    gotoxy(align-10, line+2);
    print_color_string("Password is incorrect! Please try again!", BRIGHT_RED, BLACK);
    return 0;
  }
}

void changePass(uint32 align, uint32 line) {
  sleep(CALC_SLEEP);
  while (1) {
    for (int i = 0; i < 5; ++i) {
      gotoxy(2, line+1+i);
      for (int j = 0; j < 70; ++j) {
        print_char(' ');
      }
    }

    gotoxy(align-2, line+1);
    char pass1[10], pass2[10];
    print_color_string("Enter new password: ", BRIGHT_BLUE, BLACK);
    read_pass(pass1);
    sleep(CALC_SLEEP);

    gotoxy(align-2, line+2);
    print_color_string("ReEnter new password: ", BRIGHT_BLUE, BLACK);
    read_pass(pass2);
    sleep(CALC_SLEEP);

    if (match(pass1, pass2)) {
      int i = 0;
      for (; i < strlen(pass1); ++i) {
        pwd[i] = pass1[i];
      }
      pwd[i] = '\0';
      gotoxy(align-2, line+3);
      print_color_string("Successfully!!", BRIGHT_GREEN, BLACK);
      return;
    } else {
      gotoxy(align-2, line+3);
      print_color_string("Two password doesn't match", BRIGHT_RED, BLACK);
      gotoxy(align-2, line+5);
      print_color_string("Press any key to try again", WHITE, BLACK);
      getchar();
    }
  }
}

uint8 showHistory(uint32 align, uint32 line) {
  line += 2;
  draw_box(BOX_DOUBLELINE, align - 9, ++line, 34, (times+1)*3, CYAN, BLACK);
  gotoxy(align + 4, line++);
  print_color_string(" HISTORY ", YELLOW, BLACK);
  int i = 0;
  for (; i < times; ++i) {
    gotoxy(align-7, ++line);
    print_char(26);
    print_char(' ');
    print_color_string(loginTimes[i], BRIGHT_BLUE, BLACK);

    gotoxy(align-7, ++line);
    print_char(27);
    print_char(' ');
    print_color_string(logoutTimes[i], BRIGHT_RED, BLACK);
    ++line;
  }
  gotoxy(align-7, ++line);
  print_char(26);
  print_char(' ');
  print_color_string(loginTimes[i], BRIGHT_BLUE, BLACK);
  line += 2;
  return line;
}