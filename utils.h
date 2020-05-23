#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include "keyboard.h"

extern uint32 strlen(const char*);
extern uint32 digit_count(int);
extern void itoa(int, char *);
extern int atoi(char*);
extern void print_int(int);
extern void print_string(char*);
extern uint8 inb(uint16);
extern void outb(uint16, uint8);
extern void move_cursor(uint16);
extern char get_input_keycode();
extern void wait_for_io(uint32);
extern void sleep(uint32);

#endif

