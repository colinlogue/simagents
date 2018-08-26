P=simulation
OBJECTS= $(wildcard bin/*.o)
CFLAGS= -ggdb -Wall
LDLIBS=
CC=gcc -std=gnu11


$(P): $(OBJECTS)

bin/%.o: utils/%.c

bin/%.o: models/%/model.c
