#pragma once

#include "gpu.h"

void gpu_fill(struct framebuffer_info* f, uint8_t color) {
    uint32_t* base_addr = (uint32_t*)f->base;
    uint32_t fb_h = f->height;
    uint32_t fb_w = f->width;
    uint32_t fb_pitch = f->pitch;
    uint32_t fb_bpp = f->bpp;
    for(int i = 0; i < fb_w; i++)
    {
        for(int j = 0; j < fb_w; j++)
        {
            *(base_addr + ((fb_pitch * i) + j)) = color;
        }
    }
}