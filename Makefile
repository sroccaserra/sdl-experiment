CFLAGS=-Wall -std=c99 $(shell sdl2-config --cflags)
LDLIBS=$(shell sdl2-config --libs) -llua5.4

run: a
	./a

a: a.o b.o ba.o

clean:
	rm -rf a *.o
