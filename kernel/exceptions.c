#include "serial.h"
#include <stdint.h>
#include "../drivers/pit/pit.h"

void exception_handler(uint32_t code) 
{
    serial_write_string("[Exception] interrupt recieved:");
    serial_write_dec(code);
    serial_write_char('\n');
    while(1){asm volatile ("hlt");}
    return;
}
