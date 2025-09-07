#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

typedef struct display_ops
{
    void (*init)(void);
    void (*clear)(uint32_t color);
    void (*putpixel)(int x, int y, uint32_t color);
    void (*draw_char)(int x, int y, char c, uint32_t fg, uint32_t bg);
    void (*update)(void);
} display_ops_t;



typedef struct display_device {
    int width;
    int height;
    int bpp;
    uint8_t* framebuffer;
    display_ops_t* ops;
} display_device_t;


typedef struct vga_port_t 
{

};


#endif