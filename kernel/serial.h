#ifndef SERIAL_H
#define SERIAL_H

#include <stddef.h>
#include <stdint.h>

#define COM1 0x3F8

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void serial_init() {
    outb(COM1 + 1, 0x00); // Disable interrupts
    outb(COM1 + 3, 0x80); // Enable DLAB
    outb(COM1 + 0, 0x03); // Baud rate divisor low byte
    outb(COM1 + 1, 0x00); // Baud rate divisor high byte
    outb(COM1 + 3, 0x03); // 8 bits, no parity, one stop
    outb(COM1 + 2, 0xC7); // Enable FIFO, clear, 14-byte threshold
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

// These are declared here but defined in serial.c
void serial_write_hex32(uint32_t val);
void serial_write_hex64(uint64_t val);
void serial_write_dec(uint64_t val);

#endif // SERIAL_H
