/** /brief Model for simulating market with three goods. 
  *
  * This model simulates interactions between a group of agents who have a preference for
  * one of three goods. Each agent only wants one of the goods, and will trade for it using
  * whatever of the other goods they have. The market has a totaly utility that is determined
  * by the sum of the goods that each agent has of their preference.
  *
**/


#include "headers.h"


#include "params.c"




static void tradeWith(agent_t *ptr_a, agent_t *ptr_b) {
  agent_t a = *ptr_a;
  agent_t b = *ptr_b;
  
  // if a and b have same prefs, do nothing
  if (a.pref == b.pref) {
    return;
  }

  bool a_has_bs_pref = (a.amts[b.pref] > 0);
  bool b_has_as_pref = (b.amts[a.pref] > 0);

  int goods[3][3] = { {3, 2, 1}, {2, 3, 0}, {1, 0, 3} };
  int third_good = goods[a.pref][b.pref];
  assert(third_good < 3);

  bool a_has_third_good = (a.amts[third_good] > 0);
  bool b_has_third_good = (b.amts[third_good] > 0);
  
  // if both have each other's pref, exchange
  if (a_has_bs_pref && b_has_as_pref) {
    a.amts[b.pref]--;
    b.amts[b.pref]++;
    b.amts[a.pref]--;
    a.amts[a.pref]++;
  }

  // if only one has pref, try to exchange for third good
  else if (a_has_bs_pref && b_has_third_good) {
    a.amts[b.pref]--;
    b.amts[b.pref]++;
    b.amts[third_good]--;
    a.amts[third_good]++;
  } else if (b_has_as_pref && a_has_third_good) {
    a.amts[third_good]--;
    b.amts[third_good]++;
    b.amts[a.pref]--;
    a.amts[a.pref]++;
  }

  *ptr_a = a;
  *ptr_b = b;
};

static int getTotalUtility(agent_t *agents, int n_agents) {
  int total_utility = 0;
  for (int i = 0; i < n_agents; i++) {
    total_utility += agents[i].amts[agents[i].pref];
  }
  return total_utility;
};

static void sim_init(sim_t *simu) {
  // init agents
  agent_t *agents = simu->agents;
  for (int i = 0; i < simu->n_agents; i++) {
    agents[i].id = i;
    agents[i].amts[0] = randRange(MIN_AMT, MAX_AMT + 1); // 1 is added because randRange is in range
    agents[i].amts[1] = randRange(MIN_AMT, MAX_AMT + 1); // (min, max] rather than (min, max)
    agents[i].amts[2] = randRange(MIN_AMT, MAX_AMT + 1);
    agents[i].pref = randRange(0,3);
    agent_t a = agents[i];
    printf("agent %i: %i %i %i, prefers %i\n", a.id, a.amts[0], a.amts[1], a.amts[2], a.pref);
  } // each gets a unique id, a random pref, and a random amt of each item
};

static void sim_step(sim_t *simu) {
  agent_t *agents = simu->agents;
  
  // shuffle agents
  shuffleArray(agents, simu->n_agents, sizeof(agent_t));
  
  // pair up agents and trade
  int n_trades = simu->n_agents/2;
  for (int i = 0; i < n_trades; i++) {
    tradeWith(&agents[i], &agents[i+n_trades]);
  }

  // save results
  printf("totaly utility after step %i: %i\n", simu->current_step, getTotalUtility(agents, simu->n_agents));
};


extern model_t threegoods_model = {sim_init, sim_step, sizeof(agent_t)};