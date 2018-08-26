P = simagents
OBJECTS = $(MODELS) models/model_list.c
CFLAGS = -ggdb -Wall
LDLIBS =
CC = gcc -std=gnu11
MODELS = $(patsubst models/%/model.c, bin/models/%.o, $(wildcard models/*/model.c))
UTILS = $(wildcard bin/utils/*.o)


all: update $(P)

$(P): $(OBJECTS) $(UTILS)

bin/models/%.o:
	cd models/$(notdir $(basename $@)) && make

update:
	python scripts/update_models.py