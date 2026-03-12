all: build

build: src/term.c src/commands.c src/files.c src/dltsh_base.c src/simple_comms.c
	clang src/term.c src/commands.c src/files.c src/dltsh_base.c src/simple_comms.c -o bin/dltsh
	rustc -O src/clocks.rs -o ./bin/clock

run:
	./bin/dltsh

clean:
	rm -f bin/dltsh
