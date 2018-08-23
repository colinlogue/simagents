P=simulation
OBJECTS= $(patsubst %.c, %.o, $(wildcard models/*.c)) $(patsubst %.c, %.o, $(wildcard utils/*.c))
CFLAGS= -g -Wall
LDLIBS=
CC=gcc -std=gnu11


$(P): $(OBJECTS)

utils/%.o: utils/%.c

models/%.o: models/%.c

