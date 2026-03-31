[bits 16]
[org 0x7c00]

; includes like .h in C
%include "boot/disk.asm"
%include "boot/print.asm"
%include "boot/print_pmode.asm"
%include "boot/gdt.asm"
%include "boot/switch.asm"
%include "boot/print_hex.asm"
%include "boot/mboot_tables.asm"
%include "boot/fat_header.asm"

; new line (\n)
%define ENDL 0x0D, 0x0A

; data, strings, messages...
section .data
    str_real: dw "Started in 16-bit real mode", 0
    str_pmode: dw "Landed in 32-bit prorected mode", 0
    str_load: dw "Loading dltkernel from the disk", 0
    
    boot_drive db 0x0

    ; errors
    str_returned_kernel: dw "Returned from kernel. Error?", 0
    str_read_fail: dw "[err]: [read failed!]", 0

; main and important variably for starting program
section .text
    kernel_offset equ 0x100000
    global _start

_start:
    mov [boot_drive], dl

    mov bp, 0x9000
    mov sp, bp
    
    mov ss, ax
    mov sp, 0x7c00 

    mov bx, 0x100000
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
    int 0x13
    ret

[bits 32]
begin_pm:
    mov ebx, str_pmode
    mov bx, 0x100000
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call print_pmode
    call kernel_offset
    call disk_load
	ret

    jmp $ 

times 510 - ($-$$) db 0x0
dw 0xAA55
