; SETTING THE VARIABLE MAGIC NUMBER
MODULEALIGN equ 1 << 0                   ; Space before and after 'equ'
MEMINFO     equ 1 << 1                   ; Space before and after 'equ'
FLAGS       equ MODULEALIGN | MEMINFO    ; Space before and after 'equ'
MAGIC       equ 0x1BADB002               ; Space before and after 'equ'
CHECKSUM    equ -(MAGIC + FLAGS)          ; Space before and after 'equ:

; aligning the memory for the 4-byte (32 bit) memories so the bootloader know or read the correct magic number 
; preapering to load for the kernel using protected x86-kernels mode 
section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM


; setting up the stack 
; allocating 16384 bytes for the stack (Its for basic kernel), which its mark from the bottm to the top 
; if the stack failed to align at 16-bytes it can lead to undefined behavior or even crash 
section .bss 
align 16 
    stack_bottom:
    resb 16384
    stack_top:


; calling the kernel 
; which mean we already the bootloader already boot us into 32-bit protected mode on x86
; its literal bare-metal theres no printf, stdio.h, no safeguards, no debugging only us and the machine 
section .text
global start
extern kernel_main

start: 
    cli 
    mov esp,stack_top  ; move the stack pointer to the top 
    call kernel_main


.hang:
    cli
    hlt
    jmp .hang

