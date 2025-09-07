#ifndef MEMMAP_H
#define MEMMAP_H

#include <stdint.h>
#include "multiboot.h"
#include "serial.h"

#define MAX_MEM_ENTRIES 64

uint64_t usable_mask = 0;
uint64_t base_addrs[MAX_MEM_ENTRIES];
uint64_t lengths[MAX_MEM_ENTRIES];
multiboot_memory_map_t* kmainmem = NULL;
int idx = 0;

void memset(uint8_t* p, uint16_t l, uint16_t v) {
    for(size_t i = 0; i < l; i++){
        p[i] = v;
    }
    return;
}

int dump_memory_map(multiboot_info_t* mb) {
    serial_write_string("\n[MEMORY MAP DUMP]\n");

    if (!(mb->flags & (MULTIBOOT_FLAG_MMAP))) {
        serial_write_string("No memory map available \n");
        return 1;
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

        if(mmap->len > 0x00400000){
            kmainmem = mmap;
        }

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
    return 0;
}

//only call if dump_memory_map succeeds / returns 1
int64_t kgetmemsize(){
    if(kmainmem == NULL) {
        return -1;
    }
    return kmainmem->len;
}

//so stupid i am. find out how big the memory is. create an array that tracks the size. bitmap and all
//and then simply based on the amount of memory asked, give and provide. but i should also make 
// some structure that tracks the allocation calls. 



typedef struct {
    uint8_t* p;
    uint8_t len; // should be 4 KB or 4096 Bytes
    uint8_t proc_id; 
    uint8_t flag; //1 if true and vice versa
    uint8_t used_bytes[512]; // bitmap for bytes used.
} mem_block_t;

struct m_map {
    mem_block_t* mem_block_array;
    int len;
    int idx;
    int mem_in_use_size;
    uint32_t max_mem_size;
};
struct m_map mmap;
struct m_map* m = &mmap;

// cast to mem_block_t to use pls
void* kcreate_memmap(){
    //we clear the memblockarray;
    memset(m->mem_block_array, MAX_MEM_ENTRIES, 0);
    
    //set index and length of mmap
    m->idx = 0;
    m->len = MAX_MEM_ENTRIES;

    // size based variables
    m->mem_in_use_size = 0;
    m->max_mem_size = kgetmemsize();
    
    /*let us set up a way to track where anything is stored
      i think a 2 layer block based method where one block stores 
      4 KB of blocks
      and each of those blocks store in a bitmap what all bytes r allocated.
      so now we do a first come first serve.  
    */

 
    //return the location of the mem_block_array
    return (void*)m->mem_block_array;
}

void* kmalloc(int size){
    // check if mem available
    if(m->mem_in_use_size > (m->max_mem_size + size)){
        return (void*)0;
    }
    
}


#endif