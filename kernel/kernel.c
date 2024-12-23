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
    unsigned int i = 1;
    char *c = (char*)&i;
    
    clear_screen();
    print_string("[+] loading the kernel\n");
    print_string("[+] kernel loaded\n");

    print_string("%d", 5);

    struct GDT my_gdt;

    while (1);
    
}
