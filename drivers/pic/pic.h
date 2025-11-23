#ifndef PIC_H
#define PIC_H

#include "../../kernel/io.h"

#define PIC_MASTER 0x0020 
#define PIC_SLAVE 0x00A0

#define PIC1_COMMAND 0x0020
#define PIC1_DATA 0x0021
#define PIC2_COMMAND 0x00A0
#define PIC2_DATA 0x00A1

// should i enable going back to real mode? it seems funny, but no.
// hence i will not store the current config of the PIC

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

#define CASCADE_IRQ 2

struct regs {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

/*
arguments:
	offset1 - vector offset for master PIC
		vectors on the master become offset1..offset1+7
	offset2 - same for slave PIC: offset2..offset2+7
*/
void PIC_remap(uint16_t	 offset1, uint16_t offset2);

void PIC_unmask_master(uint8_t irq);

#define PIC_EOI 0x20
//end of interrupt 
void eoi(uint8_t irq);

#endif