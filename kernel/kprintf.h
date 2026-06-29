#ifndef KPRINTF_H
#define KPRINTF_H

#include "drivers/vga/vga.h"
#include "serial.h"

void kprintf(const char* fmt, ...);

#endif
