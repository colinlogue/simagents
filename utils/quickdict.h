#ifndef QUICKDICT_H
#define QUICKDICT_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// struct declarations
struct quickdict;
struct entry;

// type definitions
typedef struct entry {
  char *key;
  char *value;
  struct quickdict *qd;
} entry_t;

typedef struct quickdict {
  entry_t **entries;
  struct quickdict *warnings;
  uint8_t max_entries;
  uint8_t not_found;
  bool allow_add_overwrite;
} quickdict_t;

// function declarations
quickdict_t *qd_build();
void qd_destroy(quickdict_t *);
uint8_t qd_check_key(quickdict_t *, char *);
entry_t *qd_add_entry(quickdict_t *, char *, char *);
entry_t *qd_insert_key(quickdict_t *, char *, uint8_t);
void qd_update_entry(entry_t *, char *);
entry_t *qd_add_or_update_entry(quickdict_t *, char *, char *);
entry_t *qd_lookup(quickdict_t *, char *);
uint8_t qd_hash(char *);
void qd_wipe(quickdict_t *);

#endif