#include <stdio.h>

#ifndef SIMULATION_H
#define SIMULATION_H

typedef struct {
  void (*init_f)(void *sim_p); // these are actually pointers to sim_t but it hasn't been declared yet
  void (*step_f)(void *sim_p); // not sure what the best way to do this is?
  size_t agent_size;
} model_t;

typedef struct {
  model_t sim;
  void *agents;
  int n_agents;
  int n_steps;
  int current_step;
} sim_t;

#endif
