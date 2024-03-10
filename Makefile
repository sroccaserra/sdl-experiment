CFLAGS=-Wall -std=c99 $(shell sdl2-config --cflags)
LDLIBS=$(shell sdl2-config --libs) -llua5.4

run: src/a
	src/a

src/a: src/a.o src/b.o src/ba.o

clean:
	rm -rf src/a src/*.o
