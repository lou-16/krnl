#include "memory.h"

static void* pmm_mem_start = &__kernel_end;

char bitmap[BITMAP_SIZE];

void pmm_init(multiboot_info_t* mb)
{
    memset(bitmap, 0xff,sizeof(bitmap));
    size_t _end = 0;

    for(size_t i = 0; i < MAX_MEM_ENTRIES; i++)
    {
        if(!((usable_mask) & (1ULL << i))) continue;
        uint32_t base_addr = base_addrs[i];
        uint32_t length = lengths[i];
        uint32_t end = base_addr + length;

        if(end > MAX_MEMORY) {
            end = MAX_MEMORY;
            break;
        }
        memset((bitmap + _end) , 0, length / PAGE_SIZE);
        _end += (length / PAGE_SIZE);
    }
    memset(bitmap, 1, __kernel_end);
    return;
}