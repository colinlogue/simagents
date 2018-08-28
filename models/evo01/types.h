#ifndef EVO01_TYPES_H
#define EVO01_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include "../../utils/queue.h"

// data types
typedef struct {
  bool is_dead;
  int8_t stockpile; // amount of food agent has collected
  uint8_t wallet;    // amount of money agent has gained
  uint8_t *trees;  // age of the trees agent has planted
  uint8_t action;
  uint8_t buysell_price;
} agent_stats_t;

typedef struct {
  unsigned int id;
  agent_stats_t stats;
  uint8_t **actiontable;
  uint8_t **selltable;
  uint8_t **buytable;
  uint8_t explore;
} agent_t;

typedef struct {
  agent_t *agents;
  queue_t *sellers;
  queue_t *buyers;
  int gen;
  int step;
  int n_states;
  int n_market_states;
} info_t;

#endif