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

typedef struct GDT {
    char* firstEntry;
    int totalEntries;
} GDT;

void encodeGDTEntry(char* target, GDTEntry source);


void setupMemory(GDT* myGDT);


#endif
