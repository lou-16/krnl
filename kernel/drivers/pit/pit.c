#include "pit.h"
#include "kprintf.h"
void pit_init(uint32_t frequency)
{
    uint32_t divisor = PIT_DIVISOR(frequency);
    outb(PIT_CMD, 0x36); // Channel 0, LSB/MSB, Mode 3 (square wave)
    outb(PIT_CH0, divisor & 0xFF); // Low byte
    outb(PIT_CH0, divisor >> 8);
    set_idt_gate(32, pit_handler, 0x8, 0x8E); // set IRQ32 to this
}

volatile uint32_t CountDown = 0;
volatile uint8_t redraw = 0;
void pit_handler()
{
    CountDown++;
    kprintf("%d", CountDown);
}
