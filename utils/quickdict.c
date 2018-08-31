#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "quickdict.h"

// Dictionary type that holds up to 256 items and uses a simple hash function
// to locate keys. Keys CANNOT be deleted. Values are strings.

#define ADD_OVERWRITE_DEFAULT true;
#define DICT_SIZE = 255;
#define NOT_FOUND_CODE = 255;

quickdict_t *qd_build() {
/**
  * Allocates memory for a quickdict and initializes each member.
  *
  * Returns
  * -------
  * *quickdict_t
  *     Pointer to the initialized quickdict.
**/
  quickdict_t *qd = malloc(sizeof(quickdict_t));
  qd->max_entries = DICT_SIZE;
  qd->not_found = NOT_FOUND_CODE;
  qd->allow_add_overwrite = ADD_OVERWRITE_DEFAULT;
  qd->entries = malloc(DICT_SIZE * sizeof(entry_t *));
  qd_wipe(qd);
  return qd;
}

void qd_destroy(quickdict_t *qd) {
/**
  * Frees memory for the quickdict, its entries, and each key and value for
  * each entry.
  *
  * Arguments
  * ---------
  * qd : *quickdict_t
  *      Memory address of the quickdict to be destroyed.
**/
  for (int i = 0; i < qd->max_entries; i++) {
    entry_t *en = qd->entries[i];
    free(en->key);
    free(en->value);
  }
  free(qd->entries);
  free(qd);
}

uint8_t qd_check_key(quickdict_t *qd, char *key) {
/**
  * Checks a quickdict for a given key, returning the index or the value of
  * ``NOT_FOUND_CODE``.
  *
  * Arguments
  * ---------
  * qd : *quickdict_t
  *     Pointer to the quickdict_t in which to search for the key.
  * key : *char
  *     Pointer to the first char of a string to search for.
  *
  * Returns
  * -------
  * uint8_t
  *     Returns the index of the key if it is found in the quickdict's
  *     entries, or else ``NOT_FOUND_CODE`` (defined in quickdict.c).
**/
  uint8_t key_hash = qd_hash(key);
  uint8_t last_to_check = (key_hash - 1) % qd->max_entries;
  while(qd->entries[key_hash]->key) {
  	if (strcmp(qd->entries[key_hash]->key, key) == 0) {
  	  return key_hash;
  	}
  	if (key_hash == last_to_check) {
  	  break;
  	}
  	key_hash = (key_hash + 1) % qd->max_entries;
  }
  return NOT_FOUND_CODE;
}

entry_t *qd_add_entry(quickdict_t *qd, char *key, char *value,) {
/**
  * Adds a key into the quickdict. If the quickdict's allow_add_overwrite
  * member is set to ``true``, will overwrite key's data if it already exists.
  *
  * Arguments
  * ---------
  * qd : *quickdict_t
  *     The quickdict to add the entry to.
  * key : *char
  *     String to be copied to key member of new quickdict entry, if they key
  *     is not already found in the quickdict's entries.
  * value : *char
  *     String that will be copied to entry in quickdict. If key is already in
  *     quickdict's entries and ``allow_add_overwrite`` is set to `true`, will
  *     overwrite existing value in entry found by ``qd_check_key``.
  *
  * Returns
  * -------
  * en : *entry_t
  *     Pointer to the newly added or updated entry_t. NULL if quickdict full.
**/
  uint8_t key_idx = qd_check_key(qd, key);
  if (key_idx == NOT_FOUND_CODE) {
    // if key not found in dict, find next empty entry and copy key and value
    uint8_t key_hash = qd_hash(key);
    uint8_t last_to_check = (key_hash - 1) % DICT_SIZE;
    while (qd->entries[key_hash]) {
      if (key_hash == last_to_check) {
        // if qd full, return NULL
        return NULL;
      }
      key_hash++;
    }
    entry_t *en = qd->entries[key_hash];
    size_t key_len = strlen(key);
    en->key = malloc(key_len * sizeof(char));
    strncpy(en->key, key, key_len);
    size_t val_len = strlen(value);
    en->value = malloc(val_len * sizeof(char));
    strncpy(en->value, value, val_len);
    return en;
  }
  else if (qd->allow_add_overwrite) {
    entry *en = qd->entries[key_hash];
    free(en->value);
    size_t val_len = strlen(value);
    en->value = malloc(val_len * sizeof(char));
    strncpy(en->value, value, val_len);
  }  
}

void qd_update_entry(quickdict_t *qd, char *key, void *value) {
  
}

entry_t *qd_add_or_update_entry(quickdict_t *qd,
                                char *key,
                                void *value,
                                size_t val_size) {
  
}

uint8_t qd_lookup(quickdict_t *qd, char *key) {
  // returns the index of the key, or not ofund code if key not present
  uint8_t key_hash = qd_hash(key);
  uint8_t last_hash = (key_hash - 1) % qd->max_entries;
  while (key_hash != last_hash) {
  	if (strcmp(qd->entries[key_hash]->key, key) == 0) {
      return key_hash;
  	}
  }
  return NOT_FOUND_CODE;
}

uint8_t qd_hash(char *key) {
  // return the modulus of the sum of the char values in the string by the
  // max number of entries in the dictionary
  unsigned int sum = 0;
  while (*key != '\0') {
  	sum += (unsigned int)(*key);
  	key++;
  }
  return (uint8_t)(sum % DICT_SIZE);
}

void qd_wipe(quickdict_t *qd) {
  for (int i = 0; i < qd->max_entries; i++) {
  	// free previously allocated memory
  	free(qd->entries[i]);
  	// initialize new empty entry_t
  	entry_t *en = malloc(sizeof(entry_t));
  	en->key = NULL;
  	en->value = NULL;
  	en->val_size = 0;
  	qd->entries[i] = en;
  }
}