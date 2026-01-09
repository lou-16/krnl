#ifndef GPU_H
#define GPU_H

#include <stdint.h>

// pardon the terrible naming.

// a Graphics device must first implement these functions.

struct framebuffer_info {
    void* base;
    uint64_t physical_base;
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    uint32_t bpp;
    struct {
        uint8_t red_pos, red_size;
        uint8_t green_pos, green_size;
        uint8_t blue_pos, blue_size;
    } color;
};

bool init_from_firmware(struct framebuffer_info* info);

void put_pixel(uint32_t x, uint32_t y, uint32_t color);

bool framebuffer_available();

void framebuffer_bind(struct framebuffer_info* info);


#endif
