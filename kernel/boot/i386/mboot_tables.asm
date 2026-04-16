[bits 32]

section .text
    align 8

    align 4
mb1_start:
    dd 0x1BADB002
    dd 0x00000000
    dd -(0x1BADB002 + 0x00000000)

    align 8
mb2_start:
    dd 0xE85250D6
    dd 0x00000000
    dd mb2_end - mb2_start

    dd 0x100000000 - (0xE85250D6 + 0x00000000 + (mb2_end - mb2_start))

    align 8
    dw 5
    dw 0
    dd 20
    dd 1920
    dd 1080
    dd 32

    align 8
    dw 0 
    dw 0 
    dd 8

mb2_end:
