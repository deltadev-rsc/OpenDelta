# clang tools
CC = clang
CXX = clang++
LD = ld.lld
OBJCOPY = llvm-objcopy

# source code
SRCS = kernel.c lib/source/types.c 
LIBS = lib/types.h 

STDBASE = obj/kernel_base.o
STDBASE_SRS = lib/source/stdbase.c 
MEM = obj/mem.o
MEM_SRC = mem/memory.c

# clang flags for build on i386
FLAGS = -m32 -march=i386 -std=c17 -fno-pie -ffreestanding -nostdlib -Wall -Wextra -Wstrict-prototypes

# image file 
img = img/open-delta.img

# qemu
QEMU = qemu-system-x86_64
QEMU_FLAGS = -boot c -m 1024 -smp 1 -vga vmware -s -d int

all: run 

img/boot.bin: boot/i386/boot.asm 
	nasm $< -f bin -o $@

obj/ints.o: cpu/asm/ints.asm
	nasm $< -f elf -o $@

obj/idt.o: cpu/idt.c
	$(CC) $(FLAGS) -c $< -o $@

img/kernel.bin: obj/kernel_entry.o obj/kernel.o obj/kernel_base.o obj/idt.o 
	$(LD) -m elf_i386 -s -o $@ -z noexecstack -T link.ld -Ttext 0x10000 $^ --oformat binary 

obj/kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@

$(MEM): $(MEM_SRC)
	$(CC) $(FLAGS) -c $< -o $@

$(STDBASE): $(STDBASE_SRS)
	$(CC) $(FLAGS) -c $< -o $@
 
obj/kernel.o: $(SRCS) 
	$(CC) $(FLAGS) -c $< -o $@

$(img): img/boot.bin img/kernel.bin
	dd if=/dev/zero of=$@ bs=512 count=32516 status=none
	mkfs.fat -F12 img/open-delta.img
	dd if=img/boot.bin of=$@ conv=ascii bs=1024 count=1
	dd if=img/kernel.bin of=$@ conv=ascii bs=2048 count=1
	cat img/boot.bin img/kernel.bin > img/open-delta.img
	
run: img/open-delta.img img/kernel.bin
	$(QEMU) -hdd $<  $(QEMU_FLAGS)

clean:
	rm -f obj/kernel_entry.o obj/kernel.o obj/idt.o obj/kernel_base.o 
	rm -f img/boot.bin img/kernel.bin img/open-delta.img

.PHONY: img/boot.bin img/kernel.bin img/open-delta.img run clean 
