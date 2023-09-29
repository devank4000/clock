default: build test

build:
	cc ./clock.c -lncurses -o clock

test:
	./clock
