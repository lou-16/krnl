[bits 32]
[extern kernel_main]

section .multiboot
align 32
    dd 0x1BADB002
    dd 0x0
    dd -(0X1BADB002)

section .bss
    
align 16    
stack_bottom:    
    resb 4096
stack_top:

section .text
global _start

_start: 

    mov esp, stack_top
    
    push ebx
    push eax
    
    call kernel_main
    cli 

.hang:
    hlt
    jmp .hang