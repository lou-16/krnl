#include "pit.h"
#include "../../serial.h"

void eoi(int);
void set_idt_gate(int, void*, int, char);

void pit_init(uint32_t frequency)
{
    uint32_t divisor = PIT_DIVISOR(frequency);
    outb(PIT_CMD, 0x36); // Channel 0, LSB/MSB, Mode 3 (square wave)
    outb(PIT_CH0, divisor & 0xFF); // Low byte
    outb(PIT_CH0, divisor >> 8);
}

void pit_handler()
{
    
}
