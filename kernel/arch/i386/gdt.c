#include "gdt.h"
#include "serial.h"
#include "kprintf.h"
//3 entries, null, code & data

static struct gdt_entry gdt[4];

static struct gdt_ptr gp;

extern void gdt_flush(uint32_t);

extern void gdt_load_tr(uint16_t);

static struct tss32 tss;

void tss_init() 
{
    for(uint32_t i = 0;i < sizeof(tss); i++)
    {
        *((uint32_t*)(&tss) + i) = 0;
    }
    tss.iomap_base = sizeof(struct tss32);
}

static void gdt_set_entry (int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
    gdt[idx].base_low = base & 0xFFFF;
    gdt[idx].base_middle = (base >> 16) & 0xff;
    gdt[idx].base_high = (base >> 24) & 0xff;

    gdt[idx].limit_low = limit & 0xffff;
    gdt[idx].granularity = ((limit >> 16) & 0xff) | (gran & 0xF0);
    gdt[idx].access = access;
}

#define TSS_SELECTOR (3 << 3)

void gdt_install() {
    gp.limit = sizeof(gdt) - 1;
    gp.base = (uint32_t)&gdt;

    tss_init();

    gdt_set_entry(0,0,0,0,0);
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9a, 0xcf); //code seg
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xcf); // data seg
    gdt_set_entry(3, (uint32_t)  &tss, sizeof(tss) - 1, 0x89, 0x00); // TSS
    gdt_flush((uint32_t) &gp);

    gdt_load_tr((uint16_t) TSS_SELECTOR);
    kprintf("[+] GDT set up\n");
}

int check_protected_mode() {
    uint32_t mode;
    asm volatile("mov %%cr0, %0" : "=r"(mode));
    if (mode & 0x1) {
        return 0;
    }
    return 1;
}


