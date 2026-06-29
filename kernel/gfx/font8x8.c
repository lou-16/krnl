#include "fonts.h"
#include "font8x8.h"

const struct font font_8x8 = {
    .width  = 8,
    .height = 8,
    .data   = (const uint8_t *) font8x8_basic
};

const struct font_map font_8x8_ascii = {
    .font       = &font_8x8,
    .first_char = 0,
    .last_char  = 127
};




