#include "serial.h"
#include "args.h"
#include "multiboot.h"
#include "memmap.h"

//#include "drivers/bga/BGA.h"
#include "drivers/gpu/gpu.h"
#include "drivers/pit/pit.h"
#include "drivers/ps2/keyboard.h"

#include "arch/i386/interrupts.h"
#include "arch/i386/gdt.h"

//extern struct __boot_args__* boot_args;

void kernel_main(uint32_t magic, multiboot_info_t* mbi){

    //boot_args = parse_boot_args((uint32_t*)mbi->cmdline);

    serial_init();
    vgaInit();
    if( magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        kprintf("Invalid multiboot magic");
        return;
    }

    //dump_memory_map(mbi);

    gdt_install();
    if(check_protected_mode() == 0){
        kprintf("protected mode active\n");
    };
    setup_exceptions();
    load_idt();
    //enable_keyboard();
    //enable_interrupts();

    kcreate_memmap();
    //install_irq_handlers();
    //test output
    kprintf("Hello from Krnl\n");
    
    while(1)
    {
    };
}

/*
    PROPOSED FUNCTION:
    void kernel_main(struct kernel_info* kInfo)
    {
        ParseKInfo(kInfo);
        initIO();
        initRAMFS();
        initDisplay();
        initDrivers();
        initVFS() if needed;
        initProcesses();
        
        RunDefaultTasks() (something that simply sends the kernel on its merry way, like schedules a bunch of prepared tasks like a tty);
        while(1);
    }

    seems way more cooler imo. now its very obvious what i need to verify.

    what about kInfo?

    heres what i propose, we'll see what happens:
    kernel_info {
        CPU_ARCH,
        CPU_CORES,
        MAIN_MEM_LEN,
        PAGING_STATUS,
        FRAMEBUFFER_INFO {
            FB_ptr,
            FB_x,
            FB_y,
            FB_bpp,
            FB_pitch (and more shit)
        }
        and further architechture agnostic info, maybe where is the kernel located, and where does the userland begin, and where is the initRAMVFS.
        like multicore CPUs will have their own optimizations that i can study from the manual, who knows?

        anyways. i feel like i have a much higher chance of making it, because all i need to do is decide the interfaces, and move the existing codebase.
    }

*/