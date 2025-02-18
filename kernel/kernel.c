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

int is_protected_mode(){
    uint16_t cs;
    asm volatile ("mov %%cs, %0":"=r"(cs));
    return (cs != 0x08);
}


extern void  __kernelMain(){


    clear_screen();
    print_string("[+] loading the kernel\n");

    if(is_protected_mode()){
        print_string("protected mode is enabled!\n");
    } else {
        print_string("protected mode wasnt turned on\n");
    }
    
    //print_string("[+] kernel loaded\n");

    print_string("%d\n", 5);
 
    while (1);
    
}
