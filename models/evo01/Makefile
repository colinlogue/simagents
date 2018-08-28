CC = gcc -std=gnu11
UTILS = intmath queue
OBJECTS = $(foreach util, $(UTILS), ../../bin/utils/$(util).o)
CFLAGS = -Wall -ggdb -c

all: update evo01

evo01:
	gcc -c -o $(OBJECTS) -o ../../bin/models/evo01.o model.c

update:
	cd ../../utils/ && make $(UTILS)