#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "quickdict.h"

// Dictionary type that holds up to 256 items and uses a simple hash function
// to locate keys. Values are strings.

#define ADD_OVERWRITE_DEFAULT true
#define DICT_SIZE (uint8_t)255
#define NOT_FOUND_CODE (uint8_t)255

const char *QD_ENTRY_DELETED = "QD_ENTRY_DELETED";

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
  for (int i = 0; i < DICT_SIZE; i++) {
    qd->entries[i] = malloc(sizeof(entry_t));
    qd->entries[i]->key = NULL;
    qd->entries[i]->value = NULL;
    qd->entries[i]->qd = qd;
  }
  return qd;
}

void qd_destroy(quickdict_t *qd) {
/**
  * Frees memory for the quickdict, its entries, and each key and value for
  * each entry.
  *
  * Parameters
  * ----------
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
  * Parameters
  * ----------
  * qd : *quickdict_t
  *     Pointer to the quickdict in which to search for the key.
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

entry_t *qd_add_entry(quickdict_t *qd, char *key, char *value) {
/**
  * Adds a key into the quickdict. If the quickdict's allow_add_overwrite
  * member is set to ``true``, will overwrite key's data if it already exists.
  *
  * Parameters
  * ----------
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
  *     Pointer to the newly added or updated entry_t, or ``NULL`` if quickdict
  *     is full.
**/
  uint8_t key_idx = qd_check_key(qd, key);
  if (key_idx == NOT_FOUND_CODE) {
    // if key not found in dict, find next empty entry and copy key and value
    key_idx = qd_hash(key);
    uint8_t last_to_check = (key_idx - 1) % DICT_SIZE;
    // loop until key at entry index is NULL
    while (qd->entries[key_idx]->key) {
      if (key_idx == last_to_check) {
        // if qd full, return NULL
        return NULL;
      }
      key_idx++;
    }
    entry_t *en = qd_insert_key(qd, key, key_idx);
    qd_update_entry(en, value);
    return en;
  }
  else if (qd->allow_add_overwrite) {
    entry_t *en = qd->entries[key_idx];
    qd_update_entry(en, value);
    return en;
  }
  else {
    fprintf(stderr, "Unable to overwrite value for key %s in quickdict", key);
    exit(EXIT_FAILURE);
  }
}

entry_t *qd_insert_key(quickdict_t *qd, char *key, uint8_t key_idx) {
/**
  * Updates the key value of the entry found at given index of the given
  * qickdict to a copy of key.
  *
  * Parameters
  * ----------
  * qd : *quickdict_t
  *     Quickdict to insert the key into.
  * key : *char
  *     String to set the entry's key value to.
  * key_idx : uint8_t
  *     Index of entry to update in qd's entries member.
  *
  * Returns
  * -------
  * en : *entry_t
  *     Pointer to the entry for the key that was inserted.
**/
  entry_t *en = qd->entries[key_idx];
  size_t key_len = strlen(key);
  en->key = malloc((key_len + 1) * sizeof(char));
  strncpy(en->key, key, key_len);
  return en;
}

void qd_update_entry(entry_t *en, char *value) {
/**
  * Updates the entry at the given location to hold the given value.
  *
  * Parameters
  * ----------
  * en : *entry_t
  *     Pointer to the entry to be updated.
  * value : *char
  *     Pointer to the string to be set as the entry's value.
**/
  free(en->value);
  if (value) {
    size_t val_len = strlen(value);
    en->value = malloc((val_len + 1) * sizeof(char));
    strncpy(en->value, value, val_len);
  }
  else {
    en->value = NULL;
  }
}

void qd_delete_entry(entry_t *en) {
  en->key = QD_ENTRY_DELETED;
  free(en->value);
  en->value = NULL;
}

entry_t *qd_add_or_update_entry(quickdict_t *qd, char *key, char *value) {
/**
  * Adds a new entry with the given key and value, or updates the entry if the
  * Key is already found in the quickdict's ``entries``.
  *
  * Same as ``qd_add_entry`` with quickdict's ``allow_add_overwrite`` set to
  * ``true``.
  *
  * Parameters
  * ----------
  * qd : *quickdict_t
  *     Pointer to the quickdict to update.
  * key : *char
  *     Pointer to the string to search for in qd's entries, to be copied to
  *     entry's key member if key doesn't exist yet in the quickdict.
  * value : *char
  *     Pointer to string to be copied to entry's value member.
**/
  bool overwrite_setting = qd->allow_add_overwrite;
  qd->allow_add_overwrite = true;
  entry_t *en = qd_add_entry(qd, key, value);
  qd->allow_add_overwrite = overwrite_setting;
  return en;
}

entry_t *qd_lookup(quickdict_t *qd, char *key) {
/**
  * Searches for the key in the quickdict's entries and returns a pointer to
  * the entry if found, or NULL otherwise.
  *
  * Parameters
  * ----------
  * qd : *quickdict_t
  *     Pointer to the quickdict to search for the key in.
  * key : *char
  *     String to be searched for in quickdict's entry keys.
  *
  * Returns
  * -------
  * en : *entry_t
  *      Pointer to the entry matching the given key, or NULL if no match.
**/
  uint8_t key_idx = qd_check_key(qd, key);
  if (key_idx == NOT_FOUND_CODE) {
    return NULL;
  }
  else {
    return qd->entries[key_idx];
  }
}

uint8_t qd_hash(char *key) {
/**
  * Hashes a string for indexing in the quickdict.
  *
  * Parameters
  * ----------
  * key : *char
  *     Pointer to string to be hashed.
  *
  * Returns
  * -------
  * uint8_t
  *     Index of key, between 0 and DICT_SIZE.
  *
  * Notes
  * -----
  * This is a very simple hash function returns the modulus of the sum of all
  * the character values in the string by the max number of entries in the
  * dictionary.
**/
  unsigned int sum = 0;
  while (*key != '\0') {
  	sum += (unsigned int)(*key);
  	key++;
  }
  return (uint8_t)(sum % DICT_SIZE);
}

void qd_wipe(quickdict_t *qd) {
/**
  * Frees previously allocated memory for each entry's key and value members.
  *
  * Parameters
  * ----------
  * qd : *quickdict_t
  *     Pointer to quickdict to be wiped.
**/
  for (int i = 0; i < qd->max_entries; i++) {
    entry_t *en = qd->entries[i];
  	free(en->key);
    en->key = NULL;
    free(en->value);
  	en->value = NULL;
  }
}