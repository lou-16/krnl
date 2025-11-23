#ifndef TTY_H
#define TTY_H

#include <stdint.h>

typedef struct {
    char character;
    uint16_t color;
} tty_character_t;

struct tty {
    tty_character_t char_buffer;
    uint8_t rows;
    uint8_t columns;
};

void putchar()
{
    
}

#endif