extern exception_handler

%macro isr_err_stub 1
isr_stub_%+%1:
    push %1
    jmp common_handler
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
    push 0
    push %1
    jmp common_handler
%endmacro
%macro isr_common_stub 1

; EFLAGS, CS, EIP, errorCode.
common_handler:
    ;lets push all the regs that we need.
    ;EAX, ECX, EDX,EBX, ESP (the value prior to executing the PUSHA instruction), EBP, ESI, and EDI
    pushad
    push ds      ; ds
    push es      ; es
    push fs     ; fs
    push gs      ;gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax 

    push esp
    call exception_handler
    add esp, 4

    pop gs
    pop fs
    pop es 
    pop ds
    popa 
    ;pop ; pop the CPU shit  
    add esp, 8
    iretd

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

; 32

global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    32
    dd isr_stub_%+i ; use DQ instead if targeting 64-bit
%assign i i+1

%endrep

