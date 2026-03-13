# clang tools
CC = clang
CXX = clang++
LD = ld.lld
OBJCOPY = llvm-objcopy

# source code
SRCS = kernel.c lib/source/types.c 
LIBS = lib/types.h 

# clang flags for build on i386
FLAGS = -m32 -march=i386 -fno-pie -ffreestanding -nostdlib

# image file 
img = open-delta.img

# qemu
QEMU = qemu-system-i386
QEMU_FLAGS = -boot c -m 1024 -smp 1 -vga vmware -s -d int

all: run 

boot.bin: boot/boot.asm 
	nasm $< -f bin -o $@

idt.o: cpu/idt.c
	$(CC) $(FLAGS) -c $< -o $@

# ints.o: cpu/ints.asm
# 	nasm $< -f elf -o $@

# isr.o: cpu/isr.c
# 	clang -m32 -nostdlib -ffreestanding -c $< -o $@ 

kernel.bin: kernel_entry.o kernel.o kernel_base.o idt.o entry_i386.o # ints.o isr.o  
	$(LD) -m elf_i386 -s -o $@ -z noexecstack -T link.ld -Ttext 0x10000 $^ --oformat binary 

entry_i386.o: entry_i386.asm
	nasm $< -f elf -o $@

kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@

kernel_base.o: lib/source/stdbase.c
	$(CC) $(FLAGS) -c $< -o $@
 
kernel.o: $(SRCS) 
	$(CC) $(FLAGS) -c $< -o $@

$(img): boot.bin kernel.bin
	dd if=/dev/zero of=$@ bs=2048 count=4096 status=none
	mkfs.fat -F12 open-delta.img
	dd if=boot.bin of=$@ conv=ascii bs=512 count=1
	dd if=kernel.bin of=$@ conv=ascii bs=2048 count=1
	cat boot.bin kernel.bin > open-delta.img
	
run: open-delta.img kernel.bin
	$(QEMU) -hdd $< $(QEMU_FLAGS)

clean:
	rm -f kernel_entry.o kernel.o ints.o isr.o idt.o kernel_base.o entry_i386.o
	rm -f boot.bin kernel.bin bootloader.img open-delta.img
