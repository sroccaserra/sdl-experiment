SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=build/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS := -Wall -std=c18 $(shell sdl2-config --cflags)
LDLIBS := $(shell sdl2-config --libs) -lc -llua5.4

.PHONY: run
run: build/a | build
	build/a

build/a: $(OBJ)
	cc $(LDFLAGS) $^ $(LDLIBS) -o $@

build/%.o: src/%.c | build
	cc $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

build:
	mkdir -p $@

.PHONY: clean
clean:
	@rm -rvf build/*

-include $(OBJ:.o=.d)
