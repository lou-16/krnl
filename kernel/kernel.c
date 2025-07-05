#include "serial.h"
#include "gdt.h"
#include "video.h"
#include "multiboot.h"
#include "memmap.h"


void kernel_main(uint32_t magic, multiboot_info_t* mbi){

    if( magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        serial_write_string("Invalid multiboot magic");
        return;
    }

    dump_memory_map(mbi);

   
    gdt_install();

    //test output
    terminal_initialize();
    terminal_writestring("Hello world\n");

    serial_init();
    serial_write_string("Hello from serial output!\n");

    while(1);
}