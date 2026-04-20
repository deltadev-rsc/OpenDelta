[bits 32]

section .data
    nl db 'W', 0x0A

section .text 
    extern entry_point
    extern kmain

    align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 - 0x00)

global _start
global readp  ; read port 
global writep ; write port
global load_idt

readp:
    mov edx, [esp + 4]
    in al, dx
    ret

writep:
    mov edx, [esp + 4]
    mov al, [esp + 4 + 4]
    out dx, al
    ret

load_idt:
    mov edx, [esp + 4]
    lidt [edx]
    sti
    ret

_start:
    cli
    mov esp, stack_space
    call entry_point

    mov ecx, nl
    mov edx, 0x41
    cmp edx, ecx
    je _exit

    call kmain 
    hlt

    jmp $ 

_exit:
    mov ebx, 0
    mov eax, 1
    int 0x80

stack_space:
    resb 2048

[bits 64]
long_mode_entry:
    mov ax, 0x10000
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov gs, ax
    mov ss, ax

    cli 

    xor rax, rax 
    xor rbx, rbx
    xor rcx, rcx
    xor rdx, rdx
    xor rdi, rdi

    lea rsp, [rel stack64_top]
    and rsp, -16

    mov rdi, rbx
    call kmain

.hang64:
    hlt
    jmp .hang64

section .bss
align 32
stack64_bottom:
    resb 65536
stack64_top:
