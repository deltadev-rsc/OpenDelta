[bits 32]

global start
global read_port
global write_port
global loadi ; load idt

extern entry_point
extern kmain

read_port:
    mov edx, [esp + 4]
    in al, dx
    ret

write_port:
    mov edx, [esp + 4]
    mov al, [esp + 4 + 4]
    out dx, al
    ret

loadi:
    mov edx, [esp + 4]
    lidt [edx]
    sti
    ret

start:
    call entry_point
    call kmain
    jmp $

section .bss
    buffer:
        resb 512
