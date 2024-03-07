CFLAGS=-Wall -std=c99 $(shell sdl2-config --cflags)
LDLIBS=$(shell sdl2-config --libs) -llua5.4

run: aa
	./aa

aa: aa.o ab.o

clean:
	rm -rf aa *.o
