#!/usr/bin/bash

# !NO DEBIAN AND APT

clear

installDeps() {
    while true; do
        echo "choose your distro group"
        echo "1.arch, 2.void"
        read group

        if [ "$group" == "1" ]; then
            sudo pacman -S clang llvm nasm make
            sudo pacman -S qemu-system-i386
            sudo pacman -S ld.lld git
            break
        elif [ "$group" == "2" ]; then
            sudo xbps-install -S clang llvm nasm make
            sudo xbps-install -S git ld.lld
            sudo xbps-install -S qemu-system-i386
            break
        else
            echo "choose only 1 or 2"
        fi
    done
}

installDeps
