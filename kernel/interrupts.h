#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>
#define IDT_MAX_DESCRIPTORS 256
#include "video.h"
#include "../drivers/pic/pic.h"

/**
 * :: offset : 32 bit valiue, address of the entry point of the ISR;
 * :: segment selector that must point to a valid code segment in the GDT (update with what segment selector is, the gdt
 * 's loc + offset, or just a numeric value for the gdt's entry for code segments)
 * :: gate type :: lowkey dont care just set it to the default values and ask GPT to pregenerate or sm
 * :: privilege level (2bits ) safeguard ur interrupts with a mall cop :skull:
 * :; present bit set to 1 for descriptor to be valid & called;
 */
struct idt_entry_t {
    uint16_t offset_low;
    uint16_t seg_selector;
    uint8_t zero;
    uint8_t type_attribs;
    uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

void setas_interrupt_gate(struct idt_entry_t* idt_entry) {
    idt_entry->type_attribs = 0x8e;
}

void setas_trap_gate(struct idt_entry_t* idt_entry) {
    idt_entry->type_attribs = 0x8F;
}

struct idt_entry_t idt[256];
extern void (*isr_stub_table[256])();

void set_idt_gate(int idx, void* offset, uint16_t selector, uint8_t type_attr) {
    uint32_t addr = (uint32_t)offset;

    idt[idx].offset_low = addr & 0xFFFF;
    idt[idx].offset_high = (addr >> 16) & 0xffff;
    idt[idx].zero = 0; //lol
    idt[idx].seg_selector = selector;
    idt[idx].type_attribs = type_attr;
}

#define PIC1 0x20
#define PIC2 0xA0


void setup_exceptions() {
    // move master and slave PICs so that my ints and cpu ints do not overlap

    for(int i = 0; i < 32; i++) {
        set_idt_gate(i, isr_stub_table[i], 0x08, 0x8e);
    }
    serial_write_string("\n[CPU IRQ] set up the stubs for CPU faults.\n[TODO] implement proper ISRs\n");
}

struct idt_ptr_t {
    uint16_t limit; 
    uint32_t base;
} __attribute__((packed));

void load_idt() {
    struct idt_ptr_t ptr;
    ptr.limit = sizeof(idt) - 1; // 255
    ptr.base = (uint32_t)&idt;

    //load that into idtr (idt register )
    asm volatile ("lidt %0" : : "m"(ptr));
    serial_write_string("\nload_idt\n");

    // init PIC from 0x20 and second at 0x28
    PIC_remap(0x20, 0x28);
}

void test_div_by_zero() {
    int x = 1;
    int y = 0;
    int z = x / y; //should trigger INT 0
    (void)z;       //avoid unused variable warning apparently;
}

#endif