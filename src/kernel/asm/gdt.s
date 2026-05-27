global setGdt
section .text

setGdt:
    mov ax, [esp + 4]          ; limit 
    mov [gdtr_spool], ax
    
    mov eax, [esp + 8]         ; Base addr 
    mov [gdtr_spool + 2], eax

    lgdt [gdtr_spool]          ; Load GDT 

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Long jump 
    jmp 0x08:.reload_cs

.reload_cs:
    ret                       

section .data
align 4
gdtr_spool:
    dw 0                       
    dd 0                       ; 32-bit base address slot :with
