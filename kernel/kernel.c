#include "serial.h"
#include "gdt.h"
#include "multiboot.h"
#include "memmap.h"
#include "interrupts.h"
#include "../drivers/vga/BGA.h"
#include "../drivers/pit/pit.h"
// drivers

void kernel_main(uint32_t magic, multiboot_info_t* mbi){

    serial_init();
    if( magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        serial_write_string("Invalid multiboot magic");
        return;
    }

    dump_memory_map(mbi);

    gdt_install();
    if(check_protected_mode() == 0){
        serial_write_string("protected mode active");
    };
    kcreate_memmap();
    
    setup_exceptions();
    load_idt();
    //install_irq_handlers();
    //test output
    serial_write_string("Hello from serial output!\n");

    bga_enable();
    bga_test();
    while(1);
}