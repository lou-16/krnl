#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

#include "serial.h"

static const char hex_chars[] = "0123456789ABCDEF";

void serial_write_hex32(uint32_t val) {
    serial_write_string("0x");
    for(int i = 7; i >= 0; i--){
        /*
        Logic for that nasty bit of code;
            what it does is shifts the character of val to the right
            eg : if a = 01100001. it shifts right and gets 00000110
                isolates the 4bit at the end, and then AND with 0xF
                which is 00001111, we get
                0001 & 1111 = 1; so it isolated the last 4 digits n conveted it to 1
                then we will get 0110 & 1111 = 0110, which will become 6.
        */

        serial_write_char(hex_chars[(val >> (i * 4) & 0xF)]);

    }
}

void serial_write_hex64(uint64_t val) {
    serial_write_string("0x");
    for (int i = 15; i >= 0; i--) {
        serial_write_char(hex_chars[(val >> (i * 4)) & 0xF]);
    }
}


// DONT ASK. PLEASE JUST DON'T
void serial_write_dec(uint64_t val) {
    if (val == 0) {
        serial_write_char('0');
        return;
    }

    // Buffer for up to 20 decimal digits + null terminator
    char buf[21];
    buf[20] = '\0';
    int i = 20;

    // Multiply-subtract method using 32-bit division
    const uint64_t powers_of_10[] = {
        10000000000000000000ULL, 1000000000000000000ULL,
        100000000000000000ULL,   10000000000000000ULL,
        1000000000000000ULL,     100000000000000ULL,
        10000000000000ULL,       1000000000000ULL,
        100000000000ULL,         10000000000ULL,
        1000000000ULL,           100000000ULL,
        10000000ULL,             1000000ULL,
        100000ULL,               10000ULL,
        1000ULL,                 100ULL,
        10ULL,                   1ULL
    };

    int started = 0;

    for (int j = 0; j < 20; j++) {
        int digit = 0;
        while (val >= powers_of_10[j]) {
            val -= powers_of_10[j];
            digit++;
        }
        if (digit || started) {
            serial_write_char('0' + digit);
            started = 1;
        }
    }
}

#endif