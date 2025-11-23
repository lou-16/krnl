#ifndef SYS_ABORT
#define SYS_ABORT

#include <stdint.h>
void sys_abort()
{
    asm volatile ("cli");
    // triple fault on next int by having a null IDT
    struct {
        uint16_t limit;
        uint32_t base;
    } __attribute__((packed)) idtr = {0, 0};
    asm volatile ("lidt %0": : "m"(idtr));
    asm volatile ("int3");
    for(;;) asm volatile ("hlt");
}

#endif /* SYS_ABORT */