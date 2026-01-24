[bits 16]
;check paging
;disable paging

global check_paging
check_paging:
    mov eax, cr0
    bt eax, 31
    setc al
    ret
