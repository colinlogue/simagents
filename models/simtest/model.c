#include "headers.h"

typedef struct simtest_agent {
  int id;
} simtest_agent_t;

void simtest_print(sim_t *simu_ptr) {
  sim_t simu = *simu_ptr;
  simtest_agent_t *agents = simu.agents;
  int n_agents = simu.n_agents;
  for (int i = 0; i < n_agents; i++) {
    printf("%i ", agents[i].id);
  }
  printf("\n");
};

void simtest_init(sim_t *simu_ptr) {
  sim_t simu = *simu_ptr;
  simtest_agent_t *agents = simu.agents;
  int n_agents = simu.n_agents;
  // initialize agent ids
  for (int i = 0; i < n_agents; i++) {
    agents[i].id = i;
  }
  simtest_print(&simu);
};

void simtest_step(sim_t *simu_ptr) {
  sim_t simu = *simu_ptr;
  simtest_agent_t *agents = simu.agents;
  int n_agents = simu.n_agents;
  
  // shuffle agents
  shuffleArray(agents, n_agents, sizeof(simtest_agent_t));
  simtest_print(&simu);
};

model_t simtest = {simtest_init, simtest_step, sizeof(simtest_agent_t)};
