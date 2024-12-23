#include "screen.h"
#include "string.h"
#include <stddef.h>
#include <stdarg.h>

uint16_t* vga_buffer = (uint16_t*)0xb8000;

uint16_t terminal_buffer[VGA_TEXT_BUFFER_SIZE] = {0};

size_t terminal_row;
size_t terminal_column;

uint8_t type;

int special_char = 0;

size_t strlen(const char* str){
    char c = str[0];
    int i = 0; 
    while (c != '\0')
    {
        i++;
        c = str[i];
    }
    return i;
}


void clear_screen(){
    for(int i = 0; i < VGA_TEXT_BUFFER_SIZE; i++){
        vga_buffer[i] = 0;
    }
    terminal_row = 0;
    terminal_column = 0;
}

void print_char_to_vga(char c, uint16_t x_loc, uint16_t y_loc){

        size_t offset = 80 * y_loc + x_loc;

        uint16_t vga_char = (uint16_t)c | (uint16_t)((uint8_t)(VGA_COLOR_WHITE | VGA_COLOR_BLACK << 4) << 8);

        vga_buffer[offset] = vga_char;
        terminal_buffer[offset] = vga_char;
        terminal_row = y_loc;
        terminal_column = x_loc;

}

void write_char(char c){    
    if(c == '\n'){
        terminal_row++;
        terminal_column = 0;
    }
    else{
    print_char_to_vga(c, terminal_column, terminal_row);

    if(++terminal_column == VGA_WIDTH){
        terminal_column = 0;
        if(++terminal_row == VGA_HEIGHT){
            terminal_column = 0;
        }
    }
    }
}

void print_string(char* str, ...){
    va_list varlist;
    int index = 0;
    size_t size = strlen(str);
    va_start(varlist, index);
    int special_char = 0;

    for(size_t i = 0; i < size; i++){
        if(str[i] == '%'){
            if(str[i+1] == 'd'){
                int x = va_arg(varlist, int);
                index++;
                char* string; 
                itoa(x,string);
                print_string(string);
                i++;
                continue;
            }
        }
        
        write_char(str[i]);
        
        
    }
    va_end(varlist);
}


void itoa(int num, char* str){
    int i = 0, isNegative = 0;

    // Handle negative numbers
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Process each digit
    do {
        str[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    // Add '-' if the number is negative
    if (isNegative) {
        str[i++] = '-';
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}
