#include "serial.h"
#include <stdint.h>
#include "../drivers/pit/pit.h"

/* Order of the items on the stack:
    EFLAGS
    CS
    EIP
    Optional (Error code)
    
    What is the procedure on an Interrupt:
    push relevant shit on the stack
    load the seg register for the new code seg and new IP into the CS and EIP
    -> if(TRAP) -> clear the IF flag in EFLAGS reg
    -> else keep it same, preventing more interrupt interrupting the current interrupt. LOL
    and then begin the execution of exception_handler();

*/
/*
    what will come in this func, inside the register:
    EAX ECX EDX EBX ESP EBP ESI EDI DS ES FS GS
    so registers will be flipped.
*/

struct regs { 
    uint32_t GS;
    uint32_t FS;
    uint32_t ES;
    uint32_t DS;

    uint32_t EDI;
    uint32_t ESI;
    uint32_t EBP;
    uint32_t ESP;
    uint32_t EBX;
    uint32_t EDX;
    uint32_t ECX;
    uint32_t EAX;
    uint32_t ERRCODE;
    uint32_t EXCEPTNUM;
    uint32_t EIP;
    uint32_t CS;
    uint32_t EFLAGS;
} __attribute__((packed));

void __attribute__((__cdecl__)) exception_handler(struct regs* registers) 
{

    serial_write_string("\n\n\n\n ::: CPU EXCEPTION :::\n\n\n\n");

    serial_write_string("Exception #: ");
    serial_write_dec(registers->EXCEPTNUM);
    serial_write_string("\n");

    serial_write_string("Error Code : ");
    serial_write_hex32(registers->ERRCODE);
    serial_write_string("\n\n");

    serial_write_string("EIP    : "); serial_write_hex32(registers->EIP);     serial_write_string("\n");
    serial_write_string("CS     : "); serial_write_hex32(registers->CS);      serial_write_string("\n");
    serial_write_string("EFLAGS : "); serial_write_hex32(registers->EFLAGS);  serial_write_string("\n\n");

    serial_write_string("General Registers:\n");

    serial_write_string("EAX: "); serial_write_hex32(registers->EAX);
    serial_write_string("  EBX: "); serial_write_hex32(registers->EBX);
    serial_write_string("\n");

    serial_write_string("ECX: "); serial_write_hex32(registers->ECX);
    serial_write_string("  EDX: "); serial_write_hex32(registers->EDX);
    serial_write_string("\n");

    serial_write_string("ESI: "); serial_write_hex32(registers->ESI);
    serial_write_string("  EDI: "); serial_write_hex32(registers->EDI);
    serial_write_string("\n");

    serial_write_string("EBP: "); serial_write_hex32(registers->EBP);
    serial_write_string("  ESP: "); serial_write_hex32(registers->ESP);
    serial_write_string("\n\n");

    serial_write_string("Segment Registers:\n");

    serial_write_string("DS: "); serial_write_hex32(registers->DS);
    serial_write_string("  ES: "); serial_write_hex32(registers->ES);
    serial_write_string("\n");

    serial_write_string("FS: "); serial_write_hex32(registers->FS);
    serial_write_string("  GS: "); serial_write_hex32(registers->GS);
    serial_write_string("\n");

//    serial_write_string("\nSystem halted.\n");

//    for (;;)
//      __asm__ volatile ("hlt");
}
