#include "gdt.h"
#include "serial.h"

//3 entries, null, code & data

static struct gdt_entry gdt[3];

static struct gdt_ptr gp;

extern void gdt_flush(uint32_t);

static void gdt_set_entry (int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
    gdt[idx].base_low = base & 0xFFFF;
    gdt[idx].base_middle = (base >> 16) & 0xff;
    gdt[idx].base_high = (base >> 24) & 0xff;

    gdt[idx].limit_low = limit && 0xffff;
    gdt[idx].granularity = ((limit >> 16) & 0xff) | (gran & 0xF0);
    gdt[idx].access = access;
}

void gdt_install() {
    gp.limit = sizeof(gdt) - 1;
    gp.base = (uint32_t)&gdt;

    gdt_set_entry(0,0,0,0,0);
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9a, 0xcf);
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xcf);

    gdt_flush((uint32_t) &gp);
    serial_write_string("[+] GDT set up\n");
}