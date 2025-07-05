#include <stdint.h>
#include "multiboot.h"
#include "serial.h"
#include "utils.h"

#define MAX_MEM_ENTRIES 64

uint64_t usable_mask = 0;
uint64_t base_addrs[MAX_MEM_ENTRIES];
uint64_t lengths[MAX_MEM_ENTRIES];

void dump_memory_map(multiboot_info_t* mb) {
    serial_write_string("\n[MEMORY MAP DUMP]\n");

    if (!(mb->flags & (MULTIBOOT_FLAG_MMAP))) {
        serial_write_string("No memory map available \n");
        return;
    }

    multiboot_memory_map_t* mmap = (void*)mb->mmap_addr;
    int index = 0;

    while ((uint32_t)mmap < mb->mmap_addr + mb->mmap_length) {
        serial_write_string("Entry : ");
        serial_write_dec(index);
        serial_write_string(":\nBase=");
        serial_write_hex64(mmap->addr);
        serial_write_string(" | Size=");
        serial_write_hex64(mmap->len);
        serial_write_string(" | Type=");
        serial_write_dec(mmap->type);
        serial_write_string("\n");

        if (mmap->type == 1 && index < MAX_MEM_ENTRIES) {
            usable_mask |= (1ULL << index);
            base_addrs[index] = mmap->addr;
            lengths[index] = mmap->len;
        }
        mmap = (multiboot_memory_map_t*)((uint32_t)mmap + mmap->size + 4);
        index++;
    }
   
    serial_write_string("\nUsable Mask: ");
    serial_write_hex64(usable_mask);
    serial_write_string("\n");
    
}