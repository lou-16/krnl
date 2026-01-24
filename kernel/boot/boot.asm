BITS 64
DEFAULT REL

global _start
section .text
_start:
    cli
halt: 
    hlt
    jmp halt