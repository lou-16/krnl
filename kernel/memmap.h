#ifndef MEMMAP_H
#define MEMMAP_H

#include <stdint.h>
#include <stdbool.h>

#include "multiboot.h"
#include "serial.h"

#define MAX_MEM_ENTRIES 64

typedef uint32_t mem_loc_t;

uint64_t usable_mask = 0;
uint64_t base_addrs[MAX_MEM_ENTRIES];
uint64_t lengths[MAX_MEM_ENTRIES];
multiboot_memory_map_t* kmainmem = NULL;
int idx = 0;

void memset(uint8_t* p, uint32_t l, uint16_t v) {
    for(size_t i = 0; i < l; i++){
        p[i] = v;
    }
    return;
}

int dump_memory_map(multiboot_info_t* mb) {
    serial_write_string("\n[MEMORY MAP DUMP]\n");

    if (!((mb->flags) & (MULTIBOOT_FLAG_MMAP))) {
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

#define BITMAP_SIZE 512   // 512 bytes = 4096 bits

typedef struct {
    mem_loc_t* p;
    uint8_t len; // should be 4 KB or 4096 Bytes
    uint8_t proc_id; 
    uint8_t use; //1 if true and vice versa
    uint8_t used_bytes[BITMAP_SIZE]; // bitmap for bytes used.
} mem_block_t;


// Get the bit at index x (0..4095)
static inline bool get_bit(const uint8_t bitmap[BITMAP_SIZE], int x) {
    return (bitmap[x / 8] >> (x % 8)) & 1U;
}

// Set the bit at index x (0..4095)
static inline void set_bit(uint8_t bitmap[BITMAP_SIZE], int x) {
    bitmap[x / 8] |= (1U << (x % 8));
}

// Clear the bit at index x (0..4095)
static inline void clear_bit(uint8_t bitmap[BITMAP_SIZE], int x) {
    bitmap[x / 8] &= ~(1U << (x % 8));
}

struct m_map {
    mem_block_t* mem_block_array;
    int len;
    int idx;
    uint32_t mem_in_use_size;
    uint32_t max_mem_size;
    uint32_t max_usable_mem_size;
};
struct m_map mmap;
struct m_map* m = &mmap;

// cast to mem_block_t to use pls
void* kcreate_memmap(){
    //we clear the memblockarray;
    memset((char*)m->mem_block_array, MAX_MEM_ENTRIES * sizeof(mem_block_t), 0);
    
    //set index and length of mmap
    m->idx = 0;
    m->len = MAX_MEM_ENTRIES;

    // size based variables
    m->mem_in_use_size = 0;
    m->max_mem_size = kgetmemsize();
    m->max_usable_mem_size = m->max_mem_size - 1024 * sizeof(INTMAX_MAX);

    serial_write_string("\nthe memory size is\n");
    serial_write_dec((int)((m->max_mem_size) / (1000.0 * 1000.0))); // returns MBs
    serial_write_string(" MB\nmemmap location is\n");
    serial_write_hex32(m);
    serial_write_string("\n");

    //return the location of the mem_block_array
    return (void*)m->mem_block_array;
}

// only allocates a page

#define MEM_START 0x01000000


// cast to mem_loc_t, will only be called by kmalloc, so we set the in use flag here [TODO] fix
void* find_first_page_free()
{
    for(size_t i = MEM_START; i < m->max_usable_mem_size; i++)
    {
        // if first bit is set to 0 (not in use)
        if(get_bit((m->mem_block_array[i]).used_bytes, 0) == 0){
            m->mem_block_array[i].use = true;
            return (void*)m->mem_block_array[i].p;
        }
    }
    // else this means we ran of out memory, highly unlikely since we have 4kb pages and a bunch of memory. but if it does happen
    serial_write_string("[CRITICAL] memory ran out. triple faulting");
    abort();
}



void* kmalloc(size_t size)
{
   if(size < 4096)
   {
        return (void*) find_first_page_free();
        
   }
   else {
    // TODO, implement a malloc for larger size
    return NULL;
   }
}



int kfree(void* p)
{
    mem_loc_t page = (mem_loc_t) p;
    for (size_t i = 0; i < m->max_usable_mem_size; i++)
    {
        mem_block_t* block = &(m->mem_block_array[i]);
        if(block->p == page){
            block->use = false;
            return 0;
        }
    }
}

#endif