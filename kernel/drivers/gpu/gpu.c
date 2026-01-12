#include "gpu.h"

struct framebuffer_info *framebuffer;

bool init_from_firmware(struct framebuffer_info *info, multiboot_info_t *mb)
{
    if (!mb || !info)
        return false;

    if (!(mb->flags & MULTIBOOT_INFO_FRAMEBUFFER_INFO))
        return false;

    info->physical_base = mb->framebuffer_addr;
    info->height = mb->framebuffer_height;
    info->width = mb->framebuffer_width;
    info->pitch = mb->framebuffer_pitch;
    info->bpp = mb->framebuffer_bpp;

    if(mb->framebuffer_type == MULTIBOOT_FRAMEBUFFER_TYPE_RGB){    
        info->color.blue_pos = mb->blue_field_position;
        info->color.blue_size = mb->blue_mask_size;
        info->color.red_pos = mb->red_field_position;
        info->color.red_size = mb->red_mask_size;
        info->color.green_pos = mb->green_field_position;
        info->color.green_size = mb->green_mask_size;
    }  else return false;
    return true;
}

void put_pixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
{
    if (x >= framebuffer->width || y >= framebuffer->height)
        return;

    uint32_t* base = (uint32_t*)framebuffer->physical_base;
    uint32_t bytes_per_pixel = framebuffer->bpp / 8;

    uint32_t* pixel =
        base + y * framebuffer->pitch + x * bytes_per_pixel;

    uint32_t calculated_color = framebuffer_packcolor(r, g, b);
    switch (bytes_per_pixel) {
        case 2:
            *(uint16_t*)pixel = (uint16_t)calculated_color;
            break;
        case 4:
            *(uint32_t*)pixel = calculated_color;
            break;
    }
}

uint32_t framebuffer_packcolor(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t rv = (uint32_t)(r >> (8 - framebuffer->color.red_size)) << framebuffer->color.red_pos;
    uint32_t gv = (uint32_t)(g >> (8 - framebuffer->color.green_size)) << framebuffer->color.green_pos;
    uint32_t bv = (uint32_t)(b >> (8 - framebuffer->color.blue_size)) << framebuffer->color.blue_pos;
    return rv | gv | bv;
}

void fb_fill_color(uint16_t width, uint16_t height, uint16_t color){
    for(int y = 0; y < framebuffer->height; y++){
        for(int x = 0; x < framebuffer->width; x++)
        {
            put_pixel(x, y, 255, 0, 0);
        }
    }
}