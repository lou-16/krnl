#include "serial.h"
#include "gdt.h"
#include "video.h"
#include "multiboot.h"
#include "memmap.h"
#include "interrupts.h"


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
    
    load_idt();
    //install_irq_handlers();

    //test output
    serial_write_string("Hello from serial output!\n");
    serial_write_dec(10);
    
    setup_exceptions();

    while(1);
}