#include <stdint.h>
#include <stddef.h>

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

/**
 * vga text mode height is set to 80 and width is 25 by default. use those values only
 */

volatile uint16_t* vga_buffer = (uint16_t*) 0xB8000;

void print_char_to_vga(char c, uint16_t x, uint16_t y){
    uint16_t offset = 80 * y + x;
    uint8_t color = (VGA_COLOR_WHITE | VGA_COLOR_BLACK << 4 );

    vga_buffer[offset] = ((uint16_t)c | (uint16_t)color << 8);

}

size_t strlen(char* str){
    char c = *str;
    int i = 0;
    while(c != '\0'){
        i++;
        c = str[i];
    }
    return i;
}

void print_string(char* str)
{
    int i = strlen(str);
    for(int j = 0; j < i; j++)
    {
        print_char_to_vga(str[j], (j % 80), (j / 80));
    }

}

void clear_screen(){
    for(int i = 0; i < 25; i++){
       for(int j = 0; j < 80; j++){
        print_char_to_vga(' ', j, i);
       } 
    }
}

extern void  __kernelMain(){
    clear_screen();
    print_string("hello world! lou was here");
    while (1);
    
}