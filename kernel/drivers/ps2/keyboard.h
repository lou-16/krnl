#ifndef KEYBOARD_PS2
#define KEYBOARD_PS2
#include <stdint.h>
#include <stdbool.h>
#include "../../kernel/serial.h"
#include "sc.h"
#include "../../kernel/io.h"

#define EMPTY (int)0
//data port 
#define KBD_DATA_PORT 0x60
//if read : Status register / io port 
// if write : Data register / io port
#define KBD_STATUS_PORT 0x64

#define SIG_ACK 0xFA
#define SIG_RESEND 0xFE
#define PS2_BUF_OVERFLOW 0x0
#define PS2_KEY_ERR 0x0
#define SIG_TEST_FAILED 0xFC | 0xFD
#define SIG_TEST_PASSED 0xAA

/*
    there is a clear seperation between the interrupt handler's call to send a keypress and the actual communication with
    the keyboard. since every key press needs to wait for an ACK sig from the ps2 keyboard, we can't really use the 
    isr to send the sigs, as maybe the first one is being processed and imagine if the second one comes. thats UB.
    so the isr needs to simply call a function callback which all it does is add the key pressed to a queue.
    first ill implement a simple interface with the outer world.
    a function to send a key press, and that's it.
 */

/* types */
typedef struct {
    uint8_t scancode;
    bool pressed;
} kbd_event_t;

#define KBD_BUF_SIZE 64
typedef struct {
    kbd_event_t kbuf[KBD_BUF_SIZE];
    volatile uint8_t head; // where shit is put
    volatile uint8_t tail; // where shit is taken from
} kbd_buf_t;

/* bit-functions */
inline uint8_t get_bit(uint8_t byte, uint8_t pos) {
    return (byte >> pos) & 1;
}
inline uint8_t set_bit(uint8_t b, uint8_t p){
    return b | (1 << p);
}
inline uint8_t clear_bit(uint8_t b, uint8_t p){
    return b | ~(1 << p);
}

static kbd_buf_t kbd_buf;
 /* a PS/2 response for a key is
        0 1 2 3 4 5 6 7
        | |           |
        | V           V
        | [ key code  ]
        |
        V
        released bit, checks if the button is pressed or released. we only care about press rn
    */
void kbd_isr(void);

#define PS2_DATA_PORT    0x60
#define PS2_STATUS_PORT  0x64

#define CMD_SET_SCANCODE 0xF0
#define SCANCODE_SET_1   0x01
#define CMD_ENABLE_SCAN  0xF4

#define RESP_ACK         0xFA
#define RESP_RESEND      0xFE

static inline void wait_input_empty() {
    while (inb(PS2_STATUS_PORT) & 0x02); // wait for input buffer to clear
}

static inline void wait_output_full() {
    while (!(inb(PS2_STATUS_PORT) & 0x01)); // wait for output buffer
}

void enable_keyboard();

kbd_event_t kbd_read_event();

#endif
