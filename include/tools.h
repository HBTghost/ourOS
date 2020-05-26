#ifndef TOOLS_H
#define TOOLS_H

#include "utils.h"
#include "kernel.h"
#include "time.h"

extern uint32 fib(uint8);
extern uint32 fac(uint8);
extern void read_string(char*);
extern uint8 signIn(uint32, uint32);
extern uint8 match(char*, char*);

#endif