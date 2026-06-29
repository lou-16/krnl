#include "interrupts.h"

idt_entry_t idt[256];

void setas_interrupt_gate(idt_entry_t* idt_entry) {
    idt_entry->type_attribs = 0x8e;
}

void setas_trap_gate(idt_entry_t* idt_entry) {
    idt_entry->type_attribs = 0x8F;
}

void set_idt_gate(int idx, void* offset, uint16_t selector, uint8_t type_attr) {
    uint32_t addr = (uint32_t)offset;

    idt[idx].offset_low = addr & 0xFFFF;
    idt[idx].offset_high = (addr >> 16) & 0xffff;
    idt[idx].zero = 0; //lol
    idt[idx].seg_selector = selector;
    idt[idx].type_attribs = type_attr;
}

void setup_exceptions() {
    for(int i = 0; i < 32; i++) {
        set_idt_gate(i, isr_stub_table[i], 0x08, 0x8e);
    }
    
}
idt_ptr_t ptr;
extern void irq0_stub(void);

void load_idt() {
    ptr.limit = sizeof(idt) - 1;
    ptr.base = (uint32_t)&idt;

    setup_exceptions();                          // fill exception gates
    set_idt_gate(32, &irq0_stub, 0x08, 0x8e); // fill IRQ0 gate

    asm volatile("lidt %0" :: "m"(ptr));         // load IDT FIRST

    PIC_remap(0x20, 0x28);                       // then remap PIC
    pit_init(100);                               // then init PIT
    PIC_unmask_master(0);                      // then unmask
    uint8_t val = inb(0x21);
    serial_write_hex32(val);

    asm volatile("sti");                         // then enable interrupts
}