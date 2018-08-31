#ifndef QUICKDICT_H
#define QUICKDICT_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
  char *key;
  char *value;
} entry_t;

typedef struct {
  entry_t **entries;
  uint8_t max_entries;
  uint8_t not_found;
  bool allow_add_overwrite;
} quickdict_t;

quickdict_t *qd_build();
entry_t *qd_add_entry(quickdict_t *, char *, void *, size_t);
uint8_t qd_lookup(quickdict_t *, char *);
uint8_t qd_hash(char *);
void qd_wipe(quickdict_t *);

#endif