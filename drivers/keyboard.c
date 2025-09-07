#ifndef KEYBOARD_PS2
#define KEYBOARD_PS2
#include <stdint.h>
#include "../kernel/serial.h"
#include "../kernel/stdin.h"
#define EMPTY (int)0
//data port 
#define KEYBOARD_IN 0x60
//if read : Status register / io port 
// if write : Data register / io port
#define KEYBOARD_OUT 0x64
uint8_t get_bit(uint8_t byte, uint8_t pos) {
    return (byte >> pos) & 1;
}
uint8_t set_bit(uint8_t b, uint8_t p){
    return b | (1 << p);
}
uint8_t clear_bit(uint8_t b, uint8_t p){
    return b | ~(1 << p);
}

uint8_t key_buffer[1024];
int buff_top = 0;
/*
    there is a clear seperation between the interrupt handler's call to send a keypress and the actual communication with
    the keyboard. since every key press needs to wait for an ACK sig from the ps2 keyboard, we can't really use the 
    isr to send the sigs, as maybe the first one is being processed and imagine if the second one comes. thats UB.
    so the isr needs to simply call a function callback which all it does is add the key pressed to a queue.
    first ill implement a simple interface with the outer world.
    a function to send a key press, and that's it.
 */

uint8_t send_key_press(uint8_t c) {
    buff_top++;
    key_buffer[buff_top] = c;
    wait_for_res();
}

#define ACK_SIG 0xFA
void wait_for_res() {
    
}

void enable_keyboard() {
    
}

void poll_for_inputs() {
    if(buff_top != EMPTY) {

    }
}

#endif
