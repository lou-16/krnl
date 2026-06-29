#ifndef GPU_H
#define GPU_H

#include "multiboot.h"
#include <stdint.h>
#include <stdbool.h>
// pardon the terrible naming.

// a Graphics device must first implement these functions.


#define RGB565(r,g,b) ( ((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (b & 0x1F) )
struct framebuffer_info {
    void* base;
    uint64_t physical_base;
    uint16_t width;
    uint16_t height;
    uint16_t pitch;
    uint16_t bpp;
    struct {
        uint8_t red_pos, red_size;
        uint8_t green_pos, green_size;
        uint8_t blue_pos, blue_size;
    } color;
};

bool init_from_firmware(struct framebuffer_info* info, multiboot_info_t* mb);

void put_pixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);

bool framebuffer_available();

void framebuffer_bind(struct framebuffer_info* info);

uint32_t framebuffer_packcolor(uint8_t r, uint8_t g, uint8_t b); 

void fb_fill_color(uint16_t width, uint16_t height, uint16_t color);
#endif
