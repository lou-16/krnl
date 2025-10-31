#ifndef BGA_H
#define BGA_H

#include <stdint.h>
#include <stdbool.h>
#include "../../kernel/io.h"
#include "../../kernel/serial.h"

#define VBE_DISPI_IOPORT_INDEX 0x01CE
#define VBE_DISPI_IOPORT_DATA 0x01CF

#define VBE_DISPI_INDEX_ID 0
#define VBE_DISPI_INDEX_XRES 1
#define VBE_DISPI_INDEX_YRES 2
#define VBE_DISPI_INDEX_BPP (3)
#define VBE_DISPI_INDEX_ENABLE (4)
#define VBE_DISPI_INDEX_BANK (5)
#define VBE_DISPI_INDEX_VIRT_WIDTH (6)
#define VBE_DISPI_INDEX_VIRT_HEIGHT (7)
#define VBE_DISPI_INDEX_X_OFFSET (8)
#define VBE_DISPI_INDEX_Y_OFFSET (9)

#define VBE_DISPI_DISABLED 0x00
#define VBE_DISPI_ENABLED 0x01

#define VBE_DISPI_ID5 0xB0C5
#define VBE_DISPI_ID0 0xB0C0

#define VBE_DISPI_LFB_ENABLED 0x40

#define VBE_DISPI_BPP_4 (0x04)
#define VBE_DISPI_BPP_8 (0x08)
#define VBE_DISPI_BPP_15 (0x0F)
#define VBE_DISPI_BPP_16 (0x10)
#define VBE_DISPI_BPP_24 (0x18)
#define VBE_DISPI_BPP_32 (0x20)


#define RGB565(r,g,b) ( ((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (b & 0x1F) )

typedef struct {
    uint32_t fb;
    uint32_t fb_size;
} framebuffer_t;

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t bpp;
} 
res_info_t ;

void bga_enable_extensions();
void bga_disable_extensions();

/* read a register */
uint16_t bga_read_register(uint16_t value_to_read);
bool bga_set_register(uint16_t value_to_set, uint16_t register_to_set);
bool bga_check_availability();
void bga_set_resolution(uint16_t height, uint16_t width);
uint32_t bga_get_lfb_loc();

uint32_t bga_get_fb_size();

// returns the framebuffer location
uint32_t bga_enable();

void bga_test_fill(uint32_t fb_addr, uint16_t width, uint16_t height);

void bga_test();

void bga_putpixel(uint16_t x, uint16_t y, uint16_t color);
#endif /* ENDIF BGA_H */