#include "video.h"
#include <stdarg.h>

int terminal_row = 0;
int terminal_column = 0;
uint8_t terminal_color = 0x07; // Light gray on black
uint16_t* terminal_buffer = (uint16_t*) 0xB8000;

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = 0x07;
    terminal_buffer = (uint16_t*) 0xB8000;

    for (size_t y = 0; y < 25; y++) {
        for (size_t x = 0; x < 80; x++) {
            terminal_putentryat(' ', terminal_color, x, y);
        }
    }
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * 80 + x;
    terminal_buffer[index] = ((uint16_t)color << 8) | c;
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        terminal_row++;
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == 80) {
            terminal_column = 0;
            terminal_row++;
        }
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

void* memcpy(void* dest, const void* src, size_t count) {
    char* dst8 = (char*)dest;
    const char* src8 = (const char*)src;
    while (count--) {
        *dst8++ = *src8++;
    }
    return dest;
}

char* itoa(int value, char* str, int base) {
    char* ptr = str, *ptr1 = str, tmp_char;
    int tmp_value;
    int is_negative = 0;

    if (value < 0 && base == 10) {
        is_negative = 1;
        value = -value;
    }

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "0123456789ABCDEF"[tmp_value % base];
    } while (value);

    if (is_negative)
        *ptr++ = '-';

    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }

    return str;
}

int printf(const char* format, ...) {
    char buffer[256];
    char* str = buffer;
    const char* traverse;
    int i;
    char* s;

    va_list arg;
    va_start(arg, format);

    for (traverse = format; *traverse != '\0'; traverse++) {
        if (*traverse != '%') {
            *str++ = *traverse;
            continue;
        }

        traverse++;
        switch (*traverse) {
            case 'c':
                *str++ = (char)va_arg(arg, int);
                break;

            case 'd': {
                i = va_arg(arg, int);
                char num_buf[16];
                itoa(i, num_buf, 10);
                char* p = num_buf;
                while (*p)
                    *str++ = *p++;
                break;
            }

            case 'x': {
                i = va_arg(arg, int);
                char num_buf[16];
                itoa(i, num_buf, 16);
                char* p = num_buf;
                while (*p)
                    *str++ = *p++;
                break;
            }

            case 's':
                s = va_arg(arg, char*);
                while (*s)
                    *str++ = *s++;
                break;

            default:
                *str++ = '%';
                *str++ = *traverse;
                break;
        }
    }

    *str = '\0';
    terminal_writestring(buffer);
    va_end(arg);
    return 0;
}
