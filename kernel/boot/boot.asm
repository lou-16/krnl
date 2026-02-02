BITS 64
DEFAULT REL

extern __kernel_main
global _start
section .text
_start:
    cli
    call __kernel_main
halt: 
    hlt
    jmp halt