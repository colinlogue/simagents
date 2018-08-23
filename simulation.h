#include <stdio.h>

#ifndef SIMULATION_H
#define SIMULATION_H

typedef struct sim {
  void (*init_f)(void *simu); // these are actually pointers to sim_info_t but it hasn't been declared yet
  void (*step_f)(void *simu); // not sure what the best way to do this is?
  size_t agent_size;
} sim_t;

typedef struct sim_info {
  sim_t sim;
  void *agents;
  int n_agents;
  int n_steps;
  int current_step;
} sim_info_t;

#endif
