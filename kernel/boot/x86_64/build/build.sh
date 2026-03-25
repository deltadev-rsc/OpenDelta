#!/bin/bash

#---toolchain---#
CC = clang
CXX = clang++
LD = ld.ldd

$FLAGS = -m64 -nostdlib -ffreestanding -fno-pie  
$LD_FLAGS = -m elf_x86_64 -z noexecstack -T ~/open-delta/kernel/boot/x86_64/linker.ld -Ttext 0x10000 --oformat binary

#---source-code-and-binaries---#
bootPath = "~/open-delta/kernel/boot/x86_64/"
bootBinPath = "~/open-delta/kernel/img/boot_x86_64.bin"
kernEntryPath = "~/open-delta/kernel/kernel_entry.asm"
kernEntryI386Path = "~/open-delta/kernel/entry_i386.asm"
kernEntryBinPath = "~/open-delta/kernel/obj/kern_entry.o"
kernEntryI386BinPath = "~/open-delta/kernel/obj/entry_i386.o"

#---source-code-and-binaries-for-kernel---#
kernelSourcePath = "~/open-delta/kernel/kernel.c"
kernelObjPath = "~/open-delta/kernel/obj/kernel.o"
kernelBinPath = "~/open-delta/kernel/img/kernel.bin"
idtSourcePath = "~/open-delta/kernel/cpu/idt.c"
idtBinPath = "~/open-delta/kernel/obj/idt.o"

#---function-for-build---#
build() {
    while true; do
        nasm $bootPath -f bin -o $bootBinPath 
        nasm $kernEntryPath -f elf -o $kernEntryBinPath
        nasm $kernEntryI386Path -f elf -o $kernEntryI386BinPath
        $CC $FLAGS -c $kernelSourcePath -o $kernelObjPath
        $CC $FLAGS -c $idtSourcePath -o $idtBinPath
        $LD $LD_FLAGS -s $kernelObjPath $idtBinPath -o $kernelBinPath
    done
} 
