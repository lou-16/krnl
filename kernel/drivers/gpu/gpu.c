#include "gpu.h"

struct framebuffer_info* framebuffer;

bool init_from_firmware(struct framebuffer_info* info, multiboot_info_t* mb )
{
    if(mb == NULL || info == NULL)
    {
        return false;
    }
    if(mb->framebuffer_addr != NULL){
        info->physical_base = mb->framebuffer_addr;
    } else return false;
    if(mb->framebuffer_height != NULL)
    {
        info->height = mb->framebuffer_height;
    } else return false;
    if(mb->framebuffer_width != NULL)
    {
        info->width = mb->framebuffer_width;
    } else return false;
    if(mb->framebuffer_pitch != NULL)
    {
        info->pitch = mb->framebuffer_pitch;
    } else return false;
    if(mb->framebuffer_bpp != NULL)
    {
        info->bpp = mb->framebuffer_bpp;
    } else return false;

    return true;
}

void put_pixel(uint32_t x, uint32_t y, uint16_t color)
{
    if(x >= framebuffer->width || y >= framebuffer->height) return;
    uint16_t* pixel_loc = (uint16_t*)framebuffer->physical_base + (y * framebuffer->pitch)
}