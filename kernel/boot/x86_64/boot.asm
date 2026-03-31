%include "boot/x86_64/constants.asm"
%include "boot/x86_64/int15.asm"
%include "boot/x86_64/switch64.asm"

[bits 16]
section .boot
    global 	startup
    global 	init

startup:
	ljmp 0x0000, .flush_segments

.flush_segments:
	cld
	mov sp, startup
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax

	movb [disk], dl
	mov ax, 0x0241
	mov bx, 0x7E00
	mov cx, 0x0002
	xor dh , dh
	int 0x13
.check_cpuid:
	pushfd
	pop eax
	mov ecx, eax
	xor eax, (1 << 21)
	push eax
	popfd
	pushfd
	pop eax
	push ecx
	popfd
	xor eax, ecx
	jz .no_cpuid

	mov eax, 0x80000000
	cpuid
	cmp eax, 0x80000001
	jz .no_longmode

	mov ax, 0x2401
	int 0x15

	mov ax, 0x03
	int 0x10

.switch_longmode:
	mov di, PAGE_TABLE_BUFFER
	push di

	mov cx, 0x1000
	xor eax, eax
	cld
	rep stosd
	pop di

	movw [di], PAGE_TABLE_BUFFER + 0x1003
	movw [di + 0x1000], PAGE_TABLE_BUFFER + 0x2003
	movw [di + 0x2000], PAGE_TABLE_BUFFER + 0x3003
	mov di, PAGE_TABLE_BUFFER, 0x3000
	mov ax, 0x03
.pages_loop:
	mov [di], eax
	add eax, 0x100
	add di, 8
	cmp di, PAGE_TABLE_BUFFER + 0x4000
	jl .pages_loop

	mov al, 0xFF
	out 0x21, al
	out 0xA1, al

	lidt [dummy_IDT]

	mov eax, 0xb10100000
	mov cr4, eax

	mov edi, PAGE_TABLE_BUFFER
	mov cr3, edi

	mov ecx, EFER
	rdmsr
	or eax, 0x00000101
	wrmsr

	mov ebx, cr0
	or ebx, 0x800000001
	mov cr0, ebx

	mov ecx, LSTAR
	mov eax, syscall_handler
	wrmsr

	mov ecx, SFMASK
	mov eax, 0xFFFFFFFF
	wrmsr

	lgdt [GDT_PTR]
	ljmp KERNEL_CODE_SEGMET, 0x7E00

.no_cpuid:
	mov si, no_cpuid_str
	call printstr_rmode
	cli
	hlt
.no_longmode:
	mov si, no_longmode_str
	call printstr_rmode
	cli
	hlt
.printstr_rmode:
	lodsb
	test a1, a1
	jz .done
	mov ah, 0x0E
	int 0x10
	jmp printstr_rmode
.done:
	ret
dummy_IDT:
	.word 0x00
	.long 0x00
disk: .byte 0x00
.space 510 - (. - startup), 0
dword 0xAA55

[bits 64]
long_mode:
	mov ax, KERNEL_DATA_SEGMENT
	mov, ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	cli

	xor rax, rax
	xor rbx, rbx
	xor rcx, rcx
	xor rdx, rdx
	xor rdi, rdi

	mov rsp, KERNEL_STACK
	mov rbp, rsp

	call kmain

	cli
	hlt

syscall_handler:
	systetq

GDT:
.null:
	.quad 0x00
.kcode:
	.quad 0x00209A0000000000
.kdata
	.quad 0x0000920000000000
.ucode:
	.quad 0x0000FA0000000000
.udata:
	.quad 0x0000F20000000000
GDT_END:
GDT_PTR:
	.word GDT_END - GDT - 1
	.long GDT

no_cpuid_str: dq "[ERR FATAL]: [CPU does not support CPUID.]"
no_longmode_str: dq "[ERR FATAL]: [CPU does not support long mode.]"
