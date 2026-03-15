#!/usr/bin/env bash

function build() {
  cd ~/OpenDelta/shell/
  mkdir bin/
  clang src/term.c src/files.c src/dltsh_base.c src/commands.c src/simple_comms.c -o bin/dltsh
  rustc src/clocks.rs -o bin/clock
  bin/dltsh
}

build
