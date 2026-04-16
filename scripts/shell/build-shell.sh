#!/usr/bin/env bash

function build() {
    cd ~/OpenDelta/shell/
    clang src/term.c src/files.c src/dltsh.c src/commands.c src/simple_comms.c -o bin/dltsh
    clang++ src/help_table.cpp -o bin/table -lncursesw
	rustc src/dexide.rs -o bin/dexide
    rustc src/calc.rs -o bin/calc
    rustc src/clocks.rs -o bin/clock
}

function run() { ./bin/term }

build && run
