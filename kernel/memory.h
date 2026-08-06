#ifndef MEMORY_H
#define MEMORY_H

#include "kprintf.h"
#include "multiboot.h"
#include "memmap.h"
#include <stddef.h>

#define KILOBYTE 1024
#define PAGE_SIZE 4096

#define MAX_MEMORY (512 * 1024 * 1024)
#define MAX_PAGES (MAX_MEMORY/PAGE_SIZE)
#define BITMAP_SIZE (MAX_PAGES / 32)
// pmm = physical memory management

/* we need to get the memory address of the __kernel_end*/
extern uint32_t __kernel_end;

#endif