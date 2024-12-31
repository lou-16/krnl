#include "gdt.h"

void encodeGDTEntry(char* target, GDTEntry source)
{
    if(source.limit > 0xFFFFFFFF){
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

void setupMemory(GDT* myGDT)

    {
    GDTEntry firstPointer = {0, 0, 0, 0}, 
    CodeSegmentK = {
        0x40000000, 0x00400000, 0x9A, 0x8
    }, 
    DataSegmentK = {
        0x40000000, 0x00800000, 0x92, 0x8
    } 
    //,CodeSegmentU, 
    //DataSegmentU,
    //TaskStateSegment
    ;
    char* origin = myGDT->firstEntry;

    
    encodeGDTEntry(origin, firstPointer);
    encodeGDTEntry((origin + 8), CodeSegmentK);
    encodeGDTEntry((origin + 16), DataSegmentK);
}


