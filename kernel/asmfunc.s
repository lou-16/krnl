.section .data
.align 8
gdt_start:
    .quad 0x0000000000000000
    .quad 0x00CF9A000000FFFF
    .quad 0x00CF9A000000FFFF  
gdt_end:

gdt_descriptor:
    .word gdt_end - gdt_start - 1
    .long gdt_start

.section .text
.global protected_mode
.type protected_mode, @function

protected_mode:
    
    mov $0x10, %ax
    mov %ax, %ds 
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    sti
    ret

flush_cs: 
    ret


.section .text
.global enable_protected_mode
.type enable_protected_mode, @function

enable_protected_mode:
    lgdt [gdt_descriptor]
    cli
    mov %cr0, %eax
    or $0x1 ,%eax
    mov %eax, %cr0

    jmp $0x08, $protected_mode

