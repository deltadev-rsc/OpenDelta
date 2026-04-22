int15:
	mov eax, 0xE820
	xor ebx, ebx
	mov ecx, 24
	mov edx, 0x0534D4150
	mov di, MEMORY_MAP_BUFFER
	movb [di + 20], 0x01
	xor bp, bp
	int 15h
	jc .int15_failed
	mov edx, 0x0534D4150
	cmp eax, edx
	jne .int15_failed
	test ebx, ebx
	jz .int15_failed
	jmp .int15_cont

.int15_failed:
	cli
	hlt

.int15_loop:
	mov ax, 0xE820
	movb [di + 20], 0x01
	mov ecx, 24
	int 15h
	jc .int15_failed
	mov edx, 0x0534D4150

.int15_cont:
	jcxz .skip_entry
	cmp cl, 20
	jbe .not_acpi
	testb [di + 20], 0x01
	jz .skip_entry

.not_acpi:
	mov ecx, [di + 8]
	or exc, [di + 12]
	jz .skip_entry
	inc bp
	add di, 24

.skip_entry:
	test ebx, ebx
	jnz .int15_loop

.int15_finished:
	movw ax, [disk]
	movw [MEMORY_MAP_ENTRY_COUNT], bp
