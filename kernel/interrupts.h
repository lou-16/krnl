#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>
#define IDT_MAX_DESCRIPTORS 256

#include "serial.h"

#include "../drivers/pic/pic.h"
#include "../drivers/pit/pit.h"
/**
 * :: offset : 32 bit valiue, address of the entry point of the ISR;
 * :: segment selector that must point to a valid code segment in the GDT (update with what segment selector is, the gdt
 * 's loc + offset, or just a numeric value for the gdt's entry for code segments)
 * :: gate type :: lowkey dont care just set it to the default values and ask GPT to pregenerate or sm
 * :: privilege level (2bits ) safeguard ur interrupts with a mall cop :skull:
 * :; present bit set to 1 for descriptor to be valid & called;
 */
typedef struct {
    uint16_t offset_low;
    uint16_t seg_selector;
    uint8_t zero;
    uint8_t type_attribs;
    uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

void setas_interrupt_gate(idt_entry_t* idt_entry);

void setas_trap_gate(idt_entry_t* idt_entry);

extern idt_entry_t idt[256];
extern void (*isr_stub_table[256])();

void set_idt_gate(int idx, void* offset, uint16_t selector, uint8_t type_attr);

#define PIC1 0x20
#define PIC2 0xA0


void setup_exceptions();

typedef struct {
    uint16_t limit; 
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

void load_idt();

#endif