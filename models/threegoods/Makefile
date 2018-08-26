# this file generated automatically

CC = gcc -std=gnu11
UTILS = shuffle intmath
OBJECTS = $(foreach util, $(UTILS), ../../bin/utils/$(util).o)
CFLAGS = -Wall -ggdb -c

all: update threegoods

threegoods:
	$(CC) $(CFLAGS) $(OBJECTS) -o ../../bin/models/threegoods.o model.c

update:
	cd ../../utils && make $(UTILS)