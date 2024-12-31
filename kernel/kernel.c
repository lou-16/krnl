#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "screen.h"
#include "gdt.h"


void memset(void* location, int len, char value){
    uint8_t* l = (uint8_t*)location;

    for(int i = 0; i < len; i++){
        l[i] = value;
    }
}



extern void  __kernelMain(){    
    clear_screen();
    print_string("[+] loading the kernel\n");
    print_string("[+] kernel loaded\n");

    print_string("%d", 5);

    struct GDT my_gdt = {(char*)0x500, 6};
    setupMemory(&my_gdt);

    int _i = (int)(my_gdt.firstEntry);

    print_string("[+]GDT loaded at memory %d", _i);

    for(int i = 0; i < 3; i++){
        print_string("%d", (int)(*(my_gdt.firstEntry)));
    }

    while (1);
    
}
