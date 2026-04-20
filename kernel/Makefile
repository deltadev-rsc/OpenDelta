# clang tools
CC = clang
CXX = clang++
LD = ld.lld
OBJCOPY = llvm-objcopy

# source code
SRCS = kernel.c
KERNEL_OBJ = obj/kernel.o
KERNEL_BIN = img/kernel.bin
ENTRY = obj/entry.o
ENTRY_SRC = kernel_entry.asm
BOOT = img/boot.bin
BOOT_SRC = boot/i386/boot.asm
STDBASE = obj/kernel_base.o
STDBASE_SRS = lib/source/stdbase.c 
TYPES = obj/types.o
TYPES_SRC = lib/source/types.c
STRING = obj/string.o
STRING_SRC = lib/source/string.c
IDT = obj/idt.o
IDT_SRC = cpu/idt.c
MEM = obj/mem.o
MEM_SRC = mem/memory.c
SCREEN = obj/screen.o 
SCREEN_SRC = drvs/screen.c 
PORTS = obj/ports.o
PORTS_SRC = ports/ports.c
 
# clang flags for build on i386
FLAGS = -m32 -march=i386 -std=c17 -fno-pie -ffreestanding -nostdlib -Wall -Wextra -Wstrict-prototypes

# image file 
img = img/open-delta.img

# qemu
QEMU = qemu-system-x86_64
QEMU_FLAGS = -boot c -m 1024 -smp 1 -vga vmware -s -d int

all: run 

$(BOOT): $(BOOT_SRC) 
	nasm $< -f bin -o $@

$(IDT): $(IDT_SRC)
	$(CC) $(FLAGS) -c $< -o $@

$(KERNEL_BIN): $(ENTRY) $(KERNEL_OBJ) $(STDBASE) $(SCREEN) $(PORTS) $(IDT) $(STRING) $(MEM) $(TYPES)
	$(LD) -m elf_i386 -s -o $@ -z noexecstack -T link.ld -Ttext 0x10000 $^ --oformat binary 

$(ENTRY): $(ENTRY_SRC)
	nasm $< -f elf -o $@

$(MEM): $(MEM_SRC)
	$(CC) $(FLAGS) -c $< -o $@

$(STRING): $(STRING_SRC)
	$(CC) $(FLAGS) -c $< -o $@

$(STDBASE): $(STDBASE_SRS)
	$(CC) $(FLAGS) -c $< -o $@

$(TYPES): $(TYPES_SRC)
	$(CC) $(FLAGS) -c $< -o $@

$(SCREEN): $(SCREEN_SRC)
	$(CC) $(FLAGS) -c $< -o $@

$(PORTS): $(PORTS_SRC)
	$(CC) $(FLAGS) -c $< -o $@

$(KERNEL_OBJ): $(SRCS) 
	$(CC) $(FLAGS) -c $< -o $@

$(img): $(BOOT) $(KERNEL_BIN)
	dd if=/dev/zero of=$@ bs=512 count=32516 status=none
	mkfs.fat -F32 img/open-delta.img
	dd if=$(BOOT) of=$@ conv=ascii bs=1024 count=1
	dd if=$(KERNEL_BIN) of=$@ conv=ascii bs=2048 count=1
	cat $(BOOT) $(KERNEL_BIN) > img/open-delta.img
	
run: img/open-delta.img img/kernel.bin
	$(QEMU) -hdd $<  $(QEMU_FLAGS)

clean:
	rm -f $(ENTRY) $(KERNEL_OBJ) $(SCREEN) $(PORTS) $(STDBASE) $(TYPES) $(MEM) $(STRING) $(IDT) 
	rm -f $(BOOT) $(KERNEL_BIN) $(img)

.PHONY: $(BOOT) $(KERNEL_BIN) $(img) run clean 
