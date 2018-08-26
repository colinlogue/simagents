#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "models/models.h"
#include "simagents.h"


void runSimulation(sim_t *sim_p) {
  /** /brief Handles the looping of a simulation for a number of turns
    *        as specified in the sim_t.
    *
    * 
    *
  **/
  
  // first step is to call init function to set
  sim_p->sim.init_f(sim_p);
  while (sim_p->current_step < sim_p->n_steps) {
    sim_p->sim.step_f(sim_p);
    sim_p->current_step++;
  };
};

int main(int argc, char **argv) {
  /* takes 3 args:
     - name of model to run simulation on
     - number of agents to run sim with
     - number of time steps to run sim for */
  
  if (argc != 4) return EXIT_FAILURE;

  // set random seed
  srand(time(0));

  model_t model = threegoods_model;
  int n_agents = atoi(argv[2]);
  int n_steps = atoi(argv[3]);

  // create sim_t
  sim_t simu;
  simu.sim = model;
  simu.n_agents = n_agents;
  simu.n_steps = n_steps;
  simu.current_step = 0;
  simu.agents = malloc(simu.sim.agent_size * simu.n_agents);
  
  
  runSimulation(&simu);
};
