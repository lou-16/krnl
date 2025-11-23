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
    // move master and slave PICs so that my ints and cpu ints do not overlap

    for(int i = 0; i < 32; i++) {
        set_idt_gate(i, isr_stub_table[i], 0x08, 0x8e);
    }
    serial_write_string("\n[CPU IRQ] set up the stubs for CPU faults.\n[TODO] implement proper ISRs\n");
}

void load_idt() {
    cli();
    idt_ptr_t ptr;
    ptr.limit = sizeof(idt) - 1; // 255
    ptr.base = (uint32_t)&idt;

    //load that into idtr (idt register )
    asm volatile ("lidt %0" : : "m"(ptr));
    serial_write_string("\nload_idt\n");

    //init PIC from 0x20 and second at 0x28
    PIC_remap(0x20, 0x28);
    serial_write_string("pic remapped\n");
    
    
    
    PIC_unmask_master(0x32); // enable PIT
    setas_interrupt_gate(&idt[32]);
    serial_write_string("pit enabled\n");
    //PIC_unmask_master(0x33); // enable keyboard
    //serial_write_string("keyboard enabled\n");
    pit_init((uint32_t)100);
    serial_write_string("pit initiated with freq 100Hz");
    
    sti();
}