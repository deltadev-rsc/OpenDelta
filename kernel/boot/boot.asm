[bits 16]
[org 0x0000:0x7c00]

; includes like .h in C
%include "boot/disk.asm"
%include "boot/print.asm"
%include "boot/print_pmode.asm"
%include "boot/gdt.asm"
%include "boot/switch.asm"
%include "boot/print_hex.asm"
%include "boot/mboot_tables.asm"

; new line (\n)
%define ENDL 0x0D, 0x0A

; data, strings, messages...
section .data
    str_real dw "Started in 16-bit real mode", ENDL, 0x0
    str_pmode dw "Landed in 32-bit prorected mode", ENDL, 0x0
    str_load dw "Loading dltkernel from the disk", ENDL, 0x0
    str_returned_kernel dw "Returned from kernel. Error?", ENDL, 0x0
    boot_drive db 0x0

; main and important variably for starting program
section .text
    align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 - 0x00)

    kernel_offset equ 0x10000
    global _start

_start:
    mov [boot_drive], dl

    mov bp, 0x9000
    mov sp, bp
    
    mov ss, ax
    mov sp, 0x7c00 

    mov bx, 0x10000
    mov es, bx
    int 13h

    mov  bx, str_real
    call print
    call print_nl

    call load_kernel
    call switch

    jmp $

[bits 16]
load_kernel:
    mov	bx, str_load
    call print
    call print_nl

    mov	bx, kernel_offset
    mov	dh, 31
    mov	dl, [boot_drive]
    call	disk_load
    int 13h
    ret

[bits 32]
begin_pm:
    mov ebx, str_pmode
    mov bx, 0x10000
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call kernel_offset
    call print_pmode
    call disk_load
	ret

    jmp 0x10000

times 510 - ($-$$) db 0x0
dw 0xaa55
