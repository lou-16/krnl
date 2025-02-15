#include <stdint-gcc.h>
#include <stddef.h>
#ifndef GDT_H
#define GDT_H
#include "screen.h"

typedef enum {
    GDT_ACCESS_CODE_READABLE    = 0x02,
    GDT_ACCESS_DATA_WRITABLE    = 0x02,
    GDT_ACCESS_CODE_CONFORMING  = 0x04,
    GDT_ACCESS_DIRECTION_NORMAL = 0x00,
    GDT_ACCESS_DIRECTION_DOWN   = 0x04,
    GDT_ACCESS_DATA_SEGMENT     = 0x10,
    GDT_ACCESS_CODE_SEGMENT     = 0x18,
    GDT_ACCESS_DESCRIPTOR_TSS   = 0x00,

    GDT_ACCESS_RING0            = 0x00,
    GDT_ACCESS_RING1            = 0x20,
    GDT_ACCESS_RING2            = 0x40,
    GDT_ACCESS_RING3            = 0x60,

    GDT_ACCESS_PRESENT          = 0x80

} GDT_ACCESS;

//borrowed code from wiki.osdev.org/GDT_Tutorial
struct GDTEntry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct GDTEntry GDT[16];

void encodeGDTEntry(char* target, struct GDTEntry source);
void enable_protected_mode(void);
void setupMemory(struct GDTEntry* GDT);



#endif
