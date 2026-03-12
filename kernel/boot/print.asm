print:
    push si
    push ax
    push bx
loop:
    lodsb 
    or al, al
    jz done
  
    mov ah, 0x0E
    int 10h
    
    jmp loop
done:
    pop bx
    pop ax
    pop si
    ret

print_nl:
    pusha

    mov ah, 0x0E
    mov al, 0x0A
    int 10h
    mov al, 0x0D
    int 10h

    popa 
    ret
