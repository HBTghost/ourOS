#include "../include/keyboard.h"


char get_input_keycode()
{
  char ch = 0;
  while ((ch = inb(KEYBOARD_PORT)) != 0)
  {
    if (ch > 0)
      return ch;
  }
  return ch;
}


void wait_for_io(uint32 timer_count)
{
  while (1)
  {
    asm volatile("nop");
    timer_count--;
    if (timer_count <= 0)
      break;
  }
}

void sleep(uint32 timer_count)
{
  wait_for_io(timer_count * 0x020FFFFF);
}

int read_int()
{
  char ch = 0;
  char keycode = 0;
  char data[32];
  int index = 0;
  do
  {
    keycode = get_input_keycode();
    if (keycode == KEY_ENTER)
    {
      data[index] = '\0';
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
      if (ch >= '0' && ch <= '9') {
        data[index] = ch;
        index++;
      } else {
        return 0;
      }
    }
    sleep(CALC_SLEEP);
  } while (ch > 0);

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
