#!/usr/bin/bash

cd ~/OpenDelta/kernel/
mkdir ./img
mkdir ./obj

function buildKernel() {
    #---compile-asm-code---# 
    nasm boot/i386/boot.asm -f bin -o img/boot.bin    
    nasm kernel_entry.asm -f elf -o obj/entry.o
    
    #---compile-kernel---#
    clang -m32 -march=i386 -fno-pie -ffreestanding -nostdlib -c kernel.c -o obj/kernel.o
    clang -m32 -march=i386 -fno-pie -ffreestanding -nostdlib -c cpu/idt.c -o obj/idt.o
    clang -m32 -march=i386 -fno-pie -ffreestanding -nostdlib -c lib/source/stdbase.c -o obj/stdbase.o
    clang -m32 -march=i386 -fno-pie -ffreestanding -nostdlib -c lib/source/string.c -o obj/string.o
    clang -m32 -march=i386 -fno-pie -ffreestanding -nostdlib -c mem/memory.c -o obj/mem.o
    clang -m32 -march=i386 -fno-pie -ffreestanding -nostdlib -c ports/ports.c -o obj/ports.o
    clang -m32 -march=i386 -fno-pie -ffreestanding -nostdlib -c drvs/screen.c -o obj/screen.o
    clang -m32 -march=i386 -fno-pie -ffreestanding -nostdlib -c lib/source/types.c -o obj/types.o
        
    #---create-kernel-bin-file---#
    ld.lld -m elf_i386 -s obj/kernel.o obj/stdbase.o obj/idt.o obj/mem.o obj/string.o obj/types.o obj/screen.o obj/ports.o obj/entry.o -o img/kernel.bin -z noexecstack -T link.ld -Ttext 0x10000 --oformat binary

    #---create-os-image---#
    dd if=/dev/zero of=img/open-delta.img bs=512 count=32516 status=none
    mkfs.fat -F12 img/open-delta.img
    dd if=img/boot.bin of=img/open-delta.img conv=ascii bs=1024 count=1 
    dd if=img/kernel.bin of=img/open-delta.img conv=ascii bs=2048 count=1
}

buildKernel
