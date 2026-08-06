#ifndef MEMMAP_H
#define MEMMAP_H

#include <stdint.h>
#include <stdbool.h>

#include "multiboot.h"
#include "serial.h"

#include "sys/abort.h"
#include "kprintf.h"
#define MAX_MEM_ENTRIES 64

typedef uint32_t mem_loc_t;

uint64_t usable_mask = 0;
uint64_t base_addrs[MAX_MEM_ENTRIES];
uint64_t lengths[MAX_MEM_ENTRIES];
multiboot_memory_map_t* kmainmem = NULL;
int idx = 0;

void memset(uint32_t* p, uint16_t v, uint16_t l) {
    for(size_t i = 0; i < l; i++){
        p[i] = v;
    }
    return;
}

int dump_memory_map(multiboot_info_t* mb)
{
    kprintf("[MEMORY MAP DUMP]\n");

    if (!(mb->flags & MULTIBOOT_FLAG_MMAP)) {
        kprintf("No memory map available\n");
        return 1;
    }

    multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)(uint32_t)mb->mmap_addr;

    int index = 0;

    while ((uint32_t)mmap < (mb->mmap_addr + mb->mmap_length)) {

        kprintf(
            "Entry %d:\n"
            "  Base = 0x%x%x\n"
            "  Size = 0x%x%x\n"
            "  Type = %u\n",
            index,
            (uint32_t)(mmap->addr >> 32),
            (uint32_t)(mmap->addr & 0xFFFFFFFF),
            (uint32_t)(mmap->len >> 32),
            (uint32_t)(mmap->len & 0xFFFFFFFF),
            mmap->type
        );

        if (mmap->len > 4096 * 8) {
            kprintf("got a hit for memory size greater than 32KB at addr: %d\n", mmap);
            kmainmem = mmap;
        }

        if (mmap->type == 1 && index < MAX_MEM_ENTRIES) {
            usable_mask |= (1ULL << index);
            base_addrs[index] = mmap->addr;
            lengths[index]   = mmap->len;
        }

        mmap = (multiboot_memory_map_t*)
            ((uint32_t)mmap + mmap->size + sizeof(mmap->size));

        index++;
    }

    kprintf("Usable Mask: 0x%x%x\n",
        (uint32_t)(usable_mask >> 32),
        (uint32_t)(usable_mask & 0xFFFFFFFF));

    return 0;
}

#endif