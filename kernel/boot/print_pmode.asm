[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0F

print_pmode:
	pusha
    mov edx, VIDEO_MEMORY

print_pmode_loop:
	mov al, [ebx]  
	mov ah, WHITE_ON_BLACK 
	cmp al, 0x0      
	jz  print_pmode_end

	mov [edx], ax   

	add ebx, 1       
	add edx, 2        

	jmp print_pmode_loop

print_pmode_end:
	popa
	ret
