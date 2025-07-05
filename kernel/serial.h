#ifndef SERIAL_H
#define SERIAL_H

#include <stddef.h>

#define COM1 0x3F8

static inline void outb(unsigned short port, unsigned char val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void serial_init() {
    outb(COM1 + 1, 0x00); // Disable all interrupts
    outb(COM1 + 3, 0x80); // Enable DLAB
    outb(COM1 + 0, 0x03); // Set baud rate divisor to 3 (38400)
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03); // 8 bits, no parity, one stop bit
    outb(COM1 + 2, 0xC7); // Enable FIFO, clear them, 14-byte threshold
    outb(COM1 + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

static inline int serial_is_transmit_ready() {
    return inb(COM1 + 5) & 0x20;
}

static inline void serial_write_char(char a) {
    while (!serial_is_transmit_ready());
    outb(COM1, a);
}

static inline void serial_write_string(const char* str) {
    for (size_t i = 0; str[i] != '\0'; ++i)
        serial_write_char(str[i]);
}

#endif // SERIAL_H
