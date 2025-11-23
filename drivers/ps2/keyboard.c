#include "keyboard.h"

void enable_keyboard()
{
    serial_write_string("[keyboard.h] Setting scan code set 1...\n");

    // Tell keyboard to set scan code set 1
    wait_input_empty();
    outb(PS2_DATA_PORT, CMD_SET_SCANCODE);
    wait_input_empty();
    outb(PS2_DATA_PORT, SCANCODE_SET_1);

    wait_output_full();
    uint8_t resp = inb(PS2_DATA_PORT);
    if (resp == RESP_RESEND) {
        serial_write_string("[keyboard.h] Resend requested, retrying set scancode.\n");
        outb(PS2_DATA_PORT, CMD_SET_SCANCODE);
        wait_input_empty();
        outb(PS2_DATA_PORT, SCANCODE_SET_1);
    }

    wait_output_full();
    resp = inb(PS2_DATA_PORT);
    if (resp != RESP_ACK)
        serial_write_string("[keyboard.h] Warning: no ACK for scancode set.\n");

    // Enable scanning
    serial_write_string("[keyboard.h] Enabling keyboard scanning...\n");
    wait_input_empty();
    outb(PS2_DATA_PORT, CMD_ENABLE_SCAN);

    wait_output_full();
    resp = inb(PS2_DATA_PORT);
    if (resp == RESP_RESEND) {
        outb(PS2_DATA_PORT, CMD_ENABLE_SCAN);
        wait_output_full();
        resp = inb(PS2_DATA_PORT);
    }

    if (resp == RESP_ACK)
        serial_write_string("[keyboard.h] Scanning enabled successfully.\n");
    else
        serial_write_string("[keyboard.h] Failed to enable scanning.\n");
}
void kbd_isr()
{
    uint8_t code = inb(KBD_DATA_PORT);
    bool released = code & 0x80; // mask the last 7 bits 0x80 = 1000 0000
    code &= 0x7F; // mask the first bit 0x7F = 0111 1111
    kbd_event_t ev = {code, !released};
    uint8_t next  = (kbd_buf.head + 1) % (KBD_BUF_SIZE);

    // if next is not equal to tail, as what may happen if tail = 128, then we set the head. to rotate queue
    if(next != kbd_buf.tail)
    {
        kbd_buf.kbuf[kbd_buf.head] = ev;
        kbd_buf.head  = next;
    }
}

kbd_event_t kbd_read_event() {
    kbd_event_t ev = {0};
    if (kbd_buf.head == kbd_buf.tail)
        return ev; // empty event (no data)

    cli(); // disable interrupts to prevent race
    ev = kbd_buf.kbuf[kbd_buf.tail];
    kbd_buf.tail = (kbd_buf.tail + 1) % KBD_BUF_SIZE;
    sti();

    return ev;
}