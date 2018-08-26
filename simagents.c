#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "models/models.h"
#include "simagents.h"


void runSimulation(sim_t *simu_ptr) {
  /** /brief Handles the looping of a simulation for a number of turns
    *        as specified in the sim_t.
    *
    * 
    *
  **/
  
  // first step is to call init function to set
  simu.sim.init_f(simu_ptr);
  while (simu_ptr->current_step < simu_ptr->n_steps) {
    simu_ptr->sim.step_f(simu_ptr);
    simu_ptr->current_step++;
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

  model_t model = get_sim_from_str(argv[1]);
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
