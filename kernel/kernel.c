#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "asmfunc.s"

#include "screen.h"
#include "gdt.h"


void memset(void* location, int len, char value){
    uint8_t* l = (uint8_t*)location;

    for(int i = 0; i < len; i++){
        l[i] = value;
    }
}



extern void  __kernelMain(){

    enable_protected_mode();
    clear_screen();
    print_string("[+] loading the kernel\n");
    print_string("[+] kernel loaded\n");

    print_string("%d\n", 5);

    struct GDT my_gdt = {(char*)0x500, 6};
    asm volatile ("cli");
    setupMemory(&my_gdt);
    asm volatile ("");

    while (1);
    
}
