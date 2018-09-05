# this file generated automatically

CC = gcc -std=gnu11
UTILS = # add the file name (without path or extension) of any util here
OBJECTS = $(foreach util, $(UTILS), ../../bin/utils/$(util).o)
CFLAGS = -Wall -ggdb -c

all: update simtest

simtest:
	$(CC) $(CFLAGS) $(OBJECTS) -o ../../bin/models/simtest.o model.c

update:
	cd ../../utils && make $(UTILS)