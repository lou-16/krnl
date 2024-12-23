.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
    .align 4
    .long MAGIC 
    .long FLAGS
    .long CHECKSUM

.section .text
.extern __kernelMain

.section .bss
.align 16
stack_bottom:  
.skip 16384 # 16 KiB
stack_top:

.section .text
.global loader
.type loader, @function


loader: 
    mov $stack_top ,%esp
    push %eax
    push %ebx
    call __kernelMain
    call __stop
__stop: 
    cli
    hlt
    jmp __stop



    
