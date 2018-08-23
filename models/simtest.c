#include <stdio.h>
#include "../simulation.h"
#include "../utils/shuffle.h"

typedef struct simtest_agent {
  int id;
} simtest_agent_t;

void simtest_print(sim_info_t *simu_ptr) {
  sim_info_t simu = *simu_ptr;
  simtest_agent_t *agents = simu.agents;
  int n_agents = simu.n_agents;
  for (int i = 0; i < n_agents; i++) {
    printf("%i ", agents[i].id);
  }
  printf("\n");
};

void simtest_init(sim_info_t *simu_ptr) {
  sim_info_t simu = *simu_ptr;
  simtest_agent_t *agents = simu.agents;
  int n_agents = simu.n_agents;
  // initialize agent ids
  for (int i = 0; i < n_agents; i++) {
    agents[i].id = i;
  }
  simtest_print(&simu);
};

void simtest_step(sim_info_t *simu_ptr) {
  sim_info_t simu = *simu_ptr;
  simtest_agent_t *agents = simu.agents;
  int n_agents = simu.n_agents;
  
  // shuffle agents
  shuffleArray(agents, n_agents, sizeof(simtest_agent_t));
  simtest_print(&simu);
};

sim_t simtest_declare() {
  sim_t simtest;
  simtest.init_f = simtest_init;
  simtest.step_f = simtest_step;
  simtest.agent_size = sizeof(simtest_agent_t);
  return simtest;
};

sim_t simtest = {simtest_init, simtest_step, sizeof(simtest_agent_t)};
