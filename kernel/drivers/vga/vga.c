#include "vga.h"

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

#define VGA_MEMORY ((volatile uint16_t*)0xB8000)

static volatile uint16_t* const vga_buffer = VGA_MEMORY;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

//typedef struct TimeStamp {
//    uint8_t t_Hour;
//    uint8_t t_Min;
//    void (*modifyTimeStamp)(struct TimeStamp_t*);
//}TimeStamp_t;
//
//void modifyTimeStamp()
//{
//
//}

/* Light grey on black */
static uint8_t vga_color = 0x07;

static inline uint16_t vga_entry(char c, uint8_t color)
{
    return (uint16_t)c | ((uint16_t)color << 8);
}

static void vga_scroll(void)
{
    for (int y = 1; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[(y - 1) * VGA_WIDTH + x] =
                vga_buffer[y * VGA_WIDTH + x];
        }
    }

    /* Clear last line */
    for (int x = 0; x < VGA_WIDTH; x++) {
        vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] =
            vga_entry(' ', vga_color);
    }

    cursor_y = VGA_HEIGHT - 1;
}

void vga_putchar(char c)
{
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\r') {
        cursor_x = 0;
    } else {
        const uint16_t index = cursor_y * VGA_WIDTH + cursor_x;
        vga_buffer[index] = vga_entry(c, vga_color);
        cursor_x++;
    }

    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= VGA_HEIGHT) {
        vga_scroll();
    }
}

void vga_clear(void)
{
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[y * VGA_WIDTH + x] =
                vga_entry(' ', vga_color);
        }
    }

    cursor_x = 0;
    cursor_y = 0;
}

void vgaInit() { vga_clear(); }