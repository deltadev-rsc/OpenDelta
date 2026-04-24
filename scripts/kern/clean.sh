#!/usr/bin/bash

cd ~/OpenDelta/kernel/

function clean {
    echo "clean .obj binaries"
    rm -f obj/kernel.o obj/stdbase.o obj/idt.o obj/mem.o obj/string.o obj/types.o obj/screen.o  obj/gdt.o obj/gdtasm.o  \ 
        \ obj/ints.o obj/isr.o obj/tty.o obj/ctype.o obj/ports.o obj/entry.o

    echo "clean .bin and .img binaries"
    rm -f img/kernel.bin img/boot.bin img/open-delta.img
}

clean
