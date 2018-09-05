#include "agents.h"



uint8_t look_offsets[N_VISIBLE_TILES][2] = {
  {-1, 1}, {0, 1}, {1, 1},
  {-1, 0},         {1, 0},
  {-1, -1},{0, -1},{1,-1}
};

uint8_t *agent_generate_genotype() {
/**
  * Randomly generates a new agent genotype.
  *
  * Returns
  * -------
  * genotype: *uint8_t
  *     Pointer to allocated memory of genotype.
**/
  int n_state_action_pairs = N_AGENT_STATES * N_AGENT_ACTIONS;
  uint8_t *genotype = malloc(n_state_action_pairs);
  for (int i = 0; i < n_state_action_pairs; i++) {
  	genotype[i] = (uint8_t)rand();
  }
  return genotype;
}

agent_t *agent_create() {
  agent_t *ag = malloc(sizeof(agent_t));
  ag->actiontable = (uint8_t **)agent_generate_genotype();
  return ag;
}

int agent_get_state(agent_t *ag) {
/**
  * Calculates a numeric state for the agent based on what it can see in the
  * environment and its internal memory state.
  *
  * Parameters
  * ----------
  * ag : *agent_t
  *     Pointer to agent for which to calculate state.
  *
  * Returns
  * -------
  * state : int
  *     Numeric representation of the state of the agent. Each value
  *     corresponds with a unique set of conditions.
**/
  uint8_t ag_x = ag->env->ag_x;
  uint8_t ag_y = ag->env->ag_y;
  uint8_t x, y;
  int z = 1;
  int state = 0;
  for (int i = 0; i < N_VISIBLE_TILES; i++) {
  	x = look_offsets[i][0] + ag_x;
  	y = look_offsets[i][1] + ag_y;
    state += (z * env_check_tile(ag->env, x, y));
    z *= N_TILE_TYPES;
  }
  for (size_t i = 0; i < N_MEMORY_INDICES; i++) {
  	state += (z * agent_check_memory(ag, i));
    z *= N_MEMORY_STATES;
  }
  return state;
}

uint8_t agent_check_memory(agent_t *ag, size_t memory_idx) {
/**
  * Checks the agent's memory state at the given index.
  *
  * Parameters
  * ----------
  * ag : *agent_t
  *     Point to the agent to check the memory of.
  * memory_idx : size_t
  *     Index of the agent's memory location to check.
  *
  * Returns
  * -------
  * uint8_t
  *     Internal state of the agent's memory at the given index.
**/
  return ag->memory[memory_idx] % N_MEMORY_STATES;
}

uint8_t env_check_tile(env_t *env, uint8_t x_tile, uint8_t y_tile) {
/**
  * Checks for the tile value at the given (x, y) coordinates in the
  * environment's tiles array.
  *
  * Parameters
  * ----------
  * env : *env_t
  *     Pointer to the environment to check.
  * x_tile : uint8_t
  *     x-value of the tile to check.
  * y_tile : uint8_t
  *     y-value of the tile to check.
  *
  * Returns
  * -------
  * uint8_t
  *     Value of the tile at the given (x, y) coordinates in the environment.
**/
  return env->tiles[x_tile][y_tile];
}

env_t *env_create() {
/**
  * Initializes a new environment.
  *
  * Returns
  * -------
  * env : *env_t
  *     Pointer to the newly reated environment.
**/
  env_t *env = malloc(sizeof(env_t));
  for (int x = 0; x < ENV_X_SIZE; x++) {
  	for (int y = 0; y < ENV_Y_SIZE; y++) {
  	  env->tiles[x][y] = 0;
  	}
  }
  return env;
}

void env_print(env_t *env) {
  for (int x = 0; x < ENV_X_SIZE; x++) {
    for (int y = 0; y < ENV_Y_SIZE; y++) {
      printf("%i ", env->tiles[x][y]);
    }
    printf("\n");
  }
}

int main() {
  srand((time(0)));
  env_t *env = env_create();
  uint8_t rand_x = (uint8_t)(rand() % ENV_X_SIZE);
  uint8_t rand_y = (uint8_t)(rand() % ENV_Y_SIZE);
  env->tiles[rand_x][rand_y] = 1;
  env_print(env);
}