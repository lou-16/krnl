#include "gdt.h"
#define MAX_GDT_SIZE 128
#define GDT_ENTRY_SIZE 8


typedef struct {
    uint32_t limit;
    uint32_t base;
    uint8_t flags;
    uint8_t access;
} GDT_struct;



void encodeGDTEntry(char* target, GDT_struct source){
    if(source.limit > 0xFFFFF){
        print_string("this shit wont slide lil bro");
    }
    //encode limit (20 bit address)
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8 ) & 0xFF;
    target[6] = (source.limit >> 16) & 0x0F;
    
    //encode base (32 bit address)
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;

    //encode the access byte (8 bits)
    target[5] = source.access;

    //encode the flags (4 bits (MSB))
    target[6] |= source.flags << 4;
}

char* g_GDT[MAX_GDT_SIZE * GDT_ENTRY_SIZE];

struct GDTDescriptor {};

void setupMemory()
{
    GDT_struct data_seg_k = {
        .base = 0x00000,
        .limit = 0xFFFFF,
        .access = 0x92,
        .flags = 0xC
    };
    GDT_struct code_seg_k;
    
}


