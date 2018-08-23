P=simulation
OBJECTS= utils/shuffle.o $(patsubst %.c, %.o, $(wildcard models/*.c))
CFLAGS= -g -Wall
LDLIBS=
CC=gcc -std=gnu11


$(P): $(OBJECTS)

utils/%.o: utils/%.c

models/%.o: models/%.c

