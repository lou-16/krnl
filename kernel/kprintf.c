#include <stdarg.h>
#include <stdint.h>

#include "kprintf.h"

/* Provided by you */
void vga_putchar(char c);
void serial_write_char(char c);

/* Single choke point */
static inline void console_putchar(char c)
{
    vga_putchar(c);
    serial_write_char(c);
}

/* Write string safely */
static void console_write(const char* s)
{
    if (!s)
        s = "(null)";

    while (*s)
        console_putchar(*s++);
}

/* Unsigned integer printing (base 10 or 16) */
static void print_uint(uint32_t value, uint32_t base)
{
    char buf[32];
    int i = 0;

    if (value == 0) {
        console_putchar('0');
        return;
    }

    while (value > 0) {
        uint32_t digit = value % base;
        buf[i++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
        value /= base;
    }

    while (i--)
        console_putchar(buf[i]);
}

/* Signed decimal */
static void print_int(int32_t value)
{
    if (value < 0) {
        console_putchar('-');
        print_uint((uint32_t)(-value), 10);
    } else {
        print_uint((uint32_t)value, 10);
    }
}

void kprintf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt != '%') {
            console_putchar(*fmt++);
            continue;
        }

        fmt++; /* skip '%' */

        switch (*fmt) {
        case 'c': {
            char c = (char)va_arg(args, int);
            console_putchar(c);
            break;
        }
        case 's': {
            const char* s = va_arg(args, const char*);
            console_write(s);
            break;
        }
        case 'd': {
            uint32_t v = va_arg(args, uint32_t);
            print_int(v);
            break;
        }
        case 'u': {
            uint32_t v = va_arg(args, uint32_t);
            print_uint(v, 10);
            break;
        }
        case 'x': {
            uint32_t v = va_arg(args, uint32_t);
            print_uint(v, 16);
            break;
        }
        case '%':
            console_putchar('%');
            break;
        default:
            /* Unknown format: print literally */
            console_putchar('%');
            console_putchar(*fmt);
            break;
        }

        fmt++;
    }

    va_end(args);
}
