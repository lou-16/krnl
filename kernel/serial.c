#include "serial.h"

static const char hex_chars[] = "0123456789ABCDEF";

void serial_write_hex32(uint32_t val) {
    serial_write_string("0x");
    for (int i = 7; i >= 0; i--) {
        serial_write_char(hex_chars[(val >> (i * 4)) & 0xF]);
    }
}

void serial_write_hex64(uint64_t val) {
    serial_write_string("0x");
    for (int i = 15; i >= 0; i--) {
        serial_write_char(hex_chars[(val >> (i * 4)) & 0xF]);
    }
}

void serial_write_dec(uint64_t val) {
    if (val == 0) {
        serial_write_char('0');
        return;
    }

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
