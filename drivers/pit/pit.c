#include "pit.h"

void pit_init(uint32_t frequency)
{
    uint32_t divisor = PIT_DIVISOR(frequency);
    outb(PIT_CMD, 0x36); // Channel 0, LSB/MSB, Mode 3 (square wave)
    outb(PIT_CH0, divisor & 0xFF); // Low byte
    outb(PIT_CH0, divisor >> 8);
    set_idt_gate(32, pit_handler, 0x0, 0x8E); // set IRQ32 to this
}

volatile uint32_t CountDown;

void pit_handler()
{
    CountDown++;
    if (CountDown % 100 == 0)
        serial_write_string("[pit] 100 ticks passed\n");
    eoi(0);
}
