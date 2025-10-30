#ifndef SLEEP_H
#define SLEEP_H

#define TICKS_PER_SECOND 1000
#define MS_PER_TICK (1000 / TICKS_PER_SECOND)

#include <stdint.h>

int sys_sleep(uint32_t ms);

#endif
