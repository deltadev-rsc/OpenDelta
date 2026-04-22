switch_longmode:
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
    
pages_loop:
	mov [di], eax
	add eax, 0x100
	add di, 8
	cmp di, PAGE_TABLE_BUFFER + 0x4000
	jl pages_loop

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
