#include "serial.h"
#include <stdint.h>
#include "video.h"
void exception_handler(uint32_t code) 
{
    serial_write_string("[Exception] interrupt recieved:");
    serial_write_dec(code);
    serial_write_char('\n');
    printf("[Exception Hit] Code : %d", code);
    while(1){asm volatile ("hlt");}
    return;
}

