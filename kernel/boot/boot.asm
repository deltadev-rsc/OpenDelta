[bits 16]
[org 0x7C00]

; includes like .h in C
%include "boot/i386/disk.asm"
%include "boot/i386/print.asm"
%include "boot/i386/print_pmode.asm"
%include "boot/i386/gdt.asm"
%include "boot/i386/switch.asm"
%include "boot/i386/print_hex.asm"
%include "boot/i386/mboot_tables.asm"
%include "boot/i386/fat_header.asm"

; new line (\n)
%define ENDL 0x0D, 0x0A

; data, strings, messages...
section .data
    str_real: dw "Started in 16-bit real mode", ENDL, 0
    str_pmode: dw "Landed in 32-bit prorected mode", ENDL, 0
    str_load: dw "Loading dltkernel from the disk", ENDL, 0
    
    boot_drive db 0x0
    boot_part_seg dw 0
    boot_part_off dw 0
    
    ; errors
    str_returned_kernel: dw "Returned from kernel. Error?", 0
    str_read_fail: dw "[err]: [read failed!]", 0

; main and important variably for starting program
section .text
    kernel_offset equ 0x100000
    global _start

_start:
    cli 

    mov ax, PARTITION_ENTRY_SEGMENT
    mov es, ax
    mov di, PARTITION_ENTRY_OFFSET
    mov cx, 16
    rep movsb

    mov ax, 0
    mov ds, ax
    mov es, ax

    mov ss, ax
    mov sp, 0x7C00 

    mov bx, 0x100000
    mov es, bx
    int 13h

    mov  bx, str_real 
    call print
    call print_nl

    call load_gdt
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
    mov ax, 0x10 
    mov bx, 0x100000
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov dx, [boot_part_seg]
    shl edx, 16
    mov dx, [boot_part_off]
    push edx 

    xor edx, edx
    mov dl, [boot_drive]
    push edx
    call _start 

    cld
    rep stosb

    call print_pmode
    call kernel_offset
    call disk_load
	ret

    jmp $ 

times 510 - ($-$$) db 0x0
dw 0xAA55
