#ifndef IO_H
#define IO_H
#include "kernel.h"
uint8 inb(uint16 port);
void outb(uint16 port, uint8 data);

#endif