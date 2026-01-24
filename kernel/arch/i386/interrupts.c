#include "interrupts.h"
#include "drivers/pic/pic.h"

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
    PIC_remap(0x20, 0x28);
    for(int i = 0; i < 32; i++) {
        set_idt_gate(i, isr_stub_table[i], 0x08, 0x8e);
    }
    
    //set_idt_gate(32, irq_stub_table[0],0x08, 0x8e);
    //set_idt_gate(33, irq_stub_table[1], 0x08, 0x8e);
}

static inline void read_idtr(idt_ptr_t *idtr) {
    asm volatile ("sidt %0" : "=m"(*idtr));
}

void load_idt() {
    //cli();
    idt_ptr_t ptr;
    ptr.limit = sizeof(idt) - 1; // 255
    ptr.base = (uint32_t)&idt;

    //load that into idtr (idt register )
    asm volatile ("lidt %0" : : "m"(ptr));
    serial_write_string("\nload_idt\n");
    idt_ptr_t idtr_debug;
    read_idtr(&idtr_debug);
    serial_write_string("idtr values\n");
    serial_write_hex32(idtr_debug.base);
    serial_write_string("\n");
    serial_write_hex32(idtr_debug.limit);
    //init PIC from 0x20 and second at 0x28
    
    uint32_t freq = 100;
    pit_init(freq);
    PIC_unmask_master((uint8_t)32); // enable PIT
    //set_idt_gate(32, (void*)isr_stub_table[32],0x08, 0x8e);
    serial_write_string("pit enabled\n");
    //PIC_unmask_master((uint8_t)33); // enable keyboard
    //serial_write_string("keyboard enabled\n");
    
    serial_write_string("pit initiated with freq: ");
    serial_write_dec(freq);
    serial_write_string("\n");
    asm volatile ("sti");
    //sti();
}