#ifndef CLK
#define CLK

#include <stdint.h>
#include "../../kernel/io.h"
#include "../../kernel/interrupts.h"

#define PIT_CMD 0x43
#define PIT_CH0 0x40
#define PIT_FREQ 1193182
#define PIT_DIVISOR(freq) (PIT_FREQ / (freq))

void pit_init(uint32_t frequency);

void pit_handler(void);

#endif