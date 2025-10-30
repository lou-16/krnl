#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>
#include <stddef.h>

// VGA terminal globals
extern int terminal_row;
extern int terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;

// Terminal functions
void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);

// Utility functions
char* itoa(int value, char* str, int base);
size_t strlen(const char* str);
void* memcpy(void* dest, const void* src, size_t count);
int printf(const char* format, ...);

#endif // VIDEO_H
