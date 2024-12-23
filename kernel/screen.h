#ifndef SCREEN_H
#define SCREEN_H
#include <stdint.h>
#define VGA_TEXT_BUFFER_SIZE 2000
#define VGA_HEIGHT 25
#define VGA_WIDTH 80

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

extern uint16_t* vga_buffer;

/**
 * the console works in this fashion:
 * > writes to VGA_TEXT_MEMORY defined here
 * > defines the variables:
 *      > terminal_buffer[80 * 25] character array
 *      > terminal_cursor int storing cursor loc
 * > defines the other functions lol
 * x goes along the row and y goes along the:w
 *  columns
 */    

extern uint16_t terminal_buffer[VGA_TEXT_BUFFER_SIZE];
extern uint16_t terminal_cursor;

void set_terminal_cursor(uint16_t x_loc, uint16_t y_loc);
void clear_screen();
void print_char_to_vga(char c, uint16_t x_loc, uint16_t y_loc);
void print_string(char* str, ...);
void print_int(int integer);
void itoa(int integer, char* string);

#endif /* SCREEN_H */  