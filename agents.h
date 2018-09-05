#ifndef AGENTS_H
#define AGENTS_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "utils/intmath.h"

#define N_VISIBLE_TILES 8
#define ENV_X_SIZE 10
#define ENV_Y_SIZE 10
#define N_TILE_TYPES 2
#define N_MEMORY_INDICES 3
#define N_MEMORY_STATES 2
#define N_AGENT_STATES (power(N_MEMORY_STATES, N_MEMORY_INDICES) * \
                        power(N_TILE_TYPES, N_VISIBLE_TILES))
#define N_AGENT_MOVES 4
#define N_AGENT_ACTIONS (N_AGENT_MOVES * (N_MEMORY_INDICES + 1))

#define NN_LAYER_0_SIZE (N_VISIBLE_TILES + N_MEMORY_STATES)
#define NN_LAYER_1_SIZE 10
#define NN_LAYER_2_SIZE 8
#define NN_LAYER_3_SIZE 8
#define NN_OUTPUT_SIZE 4

// 16 possible agent if 3 memory slots:
// moves (L,R,U,D) + update memory (none, 1, 2, 3)

typedef struct {
  uint8_t tiles[ENV_X_SIZE][ENV_Y_SIZE];
  uint8_t ag_x, ag_y, prize_x, prize_y;
} env_t;

struct agent_xy_pos {
  uint8_t x_pos, y_pos;
};

struct agent_memory {
  uint8_t memory[N_MEMORY_INDICES];
};

struct agent_actiontable {
  uint8_t **actiontable;
};

typedef struct {
  struct agent_memory;
  struct agent_actiontable;
  env_t *env;
} agent_t;

// function declarations
uint8_t *agent_generate_genotype();
agent_t *agent_create();
int agent_get_state(agent_t *);
uint8_t agent_check_memory(agent_t *, size_t);
uint8_t env_check_tile(env_t *, uint8_t, uint8_t);
env_t *env_create();
void env_print(env_t *);

#endif