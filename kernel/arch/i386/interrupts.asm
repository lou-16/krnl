extern isr_handler_c

irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push dword [esp + 48]          ; or push the IRQ number
    call isr_handler_c
    add esp, 4
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 4
    iret

global irq0_stub
irq0_stub:
    push 32           ; interrupt number
    jmp irq_common_stub