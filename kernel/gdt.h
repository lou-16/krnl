#include <stdint-gcc.h>
#ifndef GDT_H
#define GDT_H
#include "screen.h"

//borrowed code from wiki.osdev.org/GDT_Tutorial
typedef struct GDTEntry {
    uint32_t limit;
    uint32_t base;
    uint8_t access_byte;
    uint8_t flags;
} GDTEntry;

struct GDT {
    GDTEntry* firstEntry;
    int totalEntries;
} GDT;

// limit is of 
void createGDTEntry(uint32_t _limit, uint32_t _base, uint8_t _accessbyte, uint8_t _flags) {
    GDTEntry newGDT;
    newGDT.limit = _limit;
    newGDT.base = _base;
    newGDT.access_byte = _accessbyte;
    newGDT.flags = _flags;
    return;
}

void bindGlobalDescriptorTable(uint32_t _address)
{
    GDT.firstEntry = _address;
    GDT.totalEntries += 1;
}




void encodeGDTEntry(char* target, GDTEntry source)
{
    if(source.limit > 0xFFFFF){
        print_string("GDT cannot have limits larger than 0xFFFFF");
    }

    //encode the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] = (source.limit >> 16) & 0x0F;

    //encode the base 
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 24) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;

    //encode the access byte
    target[5] = source.access_byte;

    //encode the flags
    target[6] |= (source.flags << 4);

}

#endif
