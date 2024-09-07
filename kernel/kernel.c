#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "screen.h"

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
    print_string("[+] infinite looooooop!\n");
    while (1);
    
}
