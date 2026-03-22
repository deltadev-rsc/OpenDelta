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

; new line (\n)
%define ENDL 0x0D, 0x0A

%define FILESYSTEM 0
%define fat12 1
%define fat16 2
%define fat32 3
%define ext2  4

section .fsjump

    jmp short _start
    nop

section .fsheaders

%if (FILESYSTEM == fat12) || (FILESYSTEM == fat16) || (FILESYSTEM == fat32)

    bdb_oem:                    db "abcdefgh"           ; 8 bytes
    bdb_bytes_per_sector:       dw 512
    bdb_sectors_per_cluster:    db 1
    bdb_reserved_sectors:       dw 1
    bdb_fat_count:              db 2
    bdb_dir_entries_count:      dw 0E0h
    bdb_total_sectors:          dw 2880                 ; 2880 * 512 = 1.44MB
    bdb_media_descriptor_type:  db 0F0h                 ; F0 = 3.5" floppy disk
    bdb_sectors_per_fat:        dw 9                    ; 9 sectors/fat
    bdb_sectors_per_track:      dw 18
    bdb_heads:                  dw 2
    bdb_hidden_sectors:         dd 0
    bdb_large_sector_count:     dd 0

    %if (FILESYSTEM == fat32)
        fat32_sectors_per_fat:      dd 0
        fat32_flags:                dw 0
        fat32_fat_version_number:   dw 0
        fat32_rootdir_cluster:      dd 0
        fat32_fsinfo_sector:        dw 0
        fat32_backup_boot_sector:   dw 0
        fat32_reserved:             times 12 db 0
    %endif

    ; extended boot record
    ebr_drive_number:           db 0                    ; 0x00 floppy, 0x80 hdd, useless
                                db 0                    ; reserved
    ebr_signature:              db 29h
    ebr_volume_id:              db 12h, 34h, 56h, 78h   ; serial number, value doesn't matter
    ebr_volume_label:           db 'NANOBYTE OS'        ; 11 bytes, padded with spaces
    ebr_system_id:              db 'FAT12   '           ; 8 bytes

%endif

; data, strings, messages...
section .data
    str_real: dw "Started in 16-bit real mode", ENDL, 0x0
    str_pmode: dw "Landed in 32-bit prorected mode", ENDL, 0x0
    str_load: dw "Loading dltkernel from the disk", ENDL, 0x0
    
    boot_drive db 0x0

    ; errors
    str_returned_kernel: dw "Returned from kernel. Error?", ENDL, 0x0
    str_read_fail: dw "[err]: [read failed!]", ENDL, 0x0

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
