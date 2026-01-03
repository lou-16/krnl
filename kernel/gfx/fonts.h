#ifndef KERNEL_FONT_H
#define KERNEL_FONT_H

#include <stdint.h>

/*
 * Bitmap font description.
 *
 * Each glyph is stored as a bitmap, one row per byte.
 * Bit 0 (LSB) is the rightmost pixel.
 * Bit (width-1) is the leftmost pixel.
 */
struct font {
    uint8_t width;          // glyph width in pixels
    uint8_t height;         // glyph height in pixels
    const uint8_t *data;    // pointer to glyph bitmap data
};

/*
 * Font layout rules:
 *
 * - Glyphs are stored sequentially
 * - Each glyph occupies `height` bytes
 * - Glyph index = (character - first_char)
 */
struct font_map {
    const struct font *font;
    uint8_t first_char;     // ASCII code of first glyph
    uint8_t last_char;      // ASCII code of last glyph
};

/*
 * Public font instances
 *
 * These are defined in font.c
 */
extern const struct font font_5x7;
extern const struct font_map font_5x7_ascii;

#endif /* KERNEL_FONT_H */
