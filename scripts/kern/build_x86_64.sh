#!/usr/bin/bash

cd ~/OpenDelta/kernel/

mkdir -p img/
mkdir -p obj/

function build_x86_64 {
    nasm boot/x86_64/boot.asm -f bin -o img/boot64.bin
    nasm kernel_entry.asm -f elf -o obj/entry.o
    nasm arch/gdt/gdt.asm -f elf -o obj/gdta.o

    clang -m64 -fno-pie -ffreestanding -nostdlib -c kernel.c -o obj/kernel.o
    clang -m64 -fno-pie -ffreestanding -nostdlib -c cpu/idt.c -o obj/idt.o
    clang -m64 -fno-pie -ffreestanding -nostdlib -c lib/source/stdbase.c -o obj/stdbase.o
    clang -m64 -fno-pie -ffreestanding -nostdlib -c lib/source/string.c -o obj/string.o
    clang -m64 -fno-pie -ffreestanding -nostdlib -c lib/source/types.c -o obj/types.o
    clang -m64 -fno-pie -ffreestanding -nostdlib -c lib/source/ctype.c -o obj/ctype.o
    clang -m64 -fno-pie -ffreestanding -nostdlib -c mem/memory.c -o obj/mem.o
    clang -m64 -fno-pie -ffreestanding -nostdlib -c ports/ports.c -o obj/ports.o
    clang -m64 -fno-pie -ffreestanding -nostdlib -c drvs/screen.c -o obj/screen.o
    clang -m64 -fno-pie -ffreestanding -nostdlib -c tty/tty.c -o obj/tty.o
    clang -m64 -fno-pie -ffreestanding -nostdlib -c arch/gdt/gdt.c -o obj/gdtc.o

    ld.lld -m elf_x64_64 -s obj/kernel.o obj/entry.o obj/idt.o obj/mem.o obj/stdbase.o obj/tty.o obj/ctype.o obj/gdtc.o obj/gdta.os obj/string.o obj/types.o obj/ports.o obj/screen.o -o img/kernel.bin -z noexecstack -T link.ld -Ttext 0x10000 --oformat binary

    dd if=/dev/zero/ of=img/open-delta.img bs=512 count=32516 status=none
    mkfas.fat -F32 img/open-delta.img
    dd if=img/boot.bin of=img/open-delta.img conv=ascii bs=1024 count=1
    dd if=img/kernel.bin of=img/open-delta.img conv=ascii bs=2048 count=1
}

build_x86_64
