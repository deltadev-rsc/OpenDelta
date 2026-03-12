[bits 32]
   
section .data
    nl db 'W', 0x0A

section .text 
    align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 - 0x00)

global _start
global readp  ; read port 
global writep ; write port
global load_idt

extern entry_point
extern kmain

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

section .bss
    resb 8192
stack_space:
