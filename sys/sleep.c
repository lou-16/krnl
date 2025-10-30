#include "../kernel/sys/sleep.h"

int sys_sleep(uint32_t ms)
{
    uint64_t ticks = ms / MS_PER_TICK;
    if(ticks == 0) ticks = 1;
    timer_wait(ticks);
    return 0;
}