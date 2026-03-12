disk_load:
    pusha
    push dx

    mov ah, 0x02
    mov al, dh 
    mov ch, 0x00
    mov dl, 0x00
    mov dh, 0x00 
    mov cl, 0x02

    int 13h
    jc disk_error

    pop dx
    cmp al, dh
    jne sectors_error

    popa 
    ret

disk_error:
    mov bx, error_msg
    call print
    call print_nl
    mov dh, ah
    call print_hex
    jmp $

sectors_error:
    mov bx, error_msg
    call print

error_msg: 
    db "[err]: disk read error", 0x0D, 0x0A, 0x0
    db "[err]: floppy read error", 0x0D, 0x0A, 0x0
