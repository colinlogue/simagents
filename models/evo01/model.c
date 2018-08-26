#include "./headers.h"

// split into other files for clarity
#include "params.c"

static int get_n_states() {
  return STOCKPILE_LEVELS * power(TREE_LEVELS, N_TREES) * WALLET_LEVELS;
};

static int get_n_market_states() {
  return BUYSELL_LEVELS * STOCKPILE_LEVELS * WALLET_LEVELS;
}

static size_t get_actiontable_size() {
  return sizeof(uint8_t) * get_n_states() * N_ACTIONS;
};

static size_t get_buyselltable_size() {
  return sizeof(uint8_t) * get_n_market_states() * N_MARKET_ACTIONS;
}

static void init_agents(info_t *info) {
  printf("Initializing agents to random state action values...\n");
  for (int i = 0; i < N_AGENTS; i++) {
    info->agents[i].explore = rand();
    info->agents[i].id = i;
    info->agents[i].actiontable = malloc(get_actiontable_size());
    info->agents[i].selltable = malloc(get_buyselltable_size());
    info->agents[i].buytable = malloc(get_buyselltable_size());
    for (int j = 0; j < info->n_states; j++) {
      info->agents[i].actiontable[j] = malloc(N_ACTIONS * sizeof(uint8_t));
      for (int k = 0; k < N_ACTIONS; k++) {
        info->agents[i].actiontable[j][k] = rand();
      }
    }
  }
  printf("Agents initialized.\n");
};

static void sim_init(info_t *info) {
  for (int i = 0; i < N_AGENTS; i++) {
    info->agents[i].stats.is_dead = false;
    info->agents[i].stats.stockpile = (rand() % 10) + 1;
    info->agents[i].stats.wallet = (rand() % 10) + 1;
    info->agents[i].stats.trees = malloc(sizeof(uint8_t) * N_TREES);
    for (int j = 0; j < N_TREES; j++) {
      info->agents[i].stats.trees[j] = 0;
    }
  }
};

static int get_stockpile_state(uint8_t stockpile) {
  // converts agent's stockpile value to an internal state
  return min(stockpile, STOCKPILE_LEVELS) - 1;
};

static int get_wallet_state(uint8_t wallet) {
  return min(wallet, WALLET_LEVELS) - 1;
};

static int get_tree_state(uint8_t tree_age) {
  // converts age of tree to state
  return min(tree_age, TREE_LEVELS - 1);
};

static int get_buysell_state(int n_sellers, int n_buyers) {
  assert(n_sellers > 0 || n_buyers > 0); // don't call if no one in market
  float ratio = (float)n_sellers / (float)n_buyers;
  float range1 = 0.1;
  float range2 = 0.33;
  if (ratio < 1. - range2) return 0;
  else if (ratio < 1. - range1) return 1;
  else if (ratio <= 1. + range1) return 2;
  else if (ratio <= 1. + range2) return 3;
  else return 4;
};

static int food_from_tree(uint8_t tree_age) {
  // returns the amount of food harvested from a tree of a given age
  if (tree_age < 3) return 0;
  else if (tree_age == 3) return 1;
  else if (tree_age == 4) return 3;
  else return 5;
};

static void harvest_action(agent_t *agent_ptr) {
  int oldest_tree_age = 0;
  int oldest_tree_idx = -1;
  int tree_age;
  for (int i = 0; i < N_TREES; i++) {
    tree_age = agent_ptr->stats.trees[i];
    if (tree_age > oldest_tree_age) {
      oldest_tree_age = tree_age;
      oldest_tree_idx = i;
    }
  }
  if (oldest_tree_idx > -1) {
    agent_ptr->stats.trees[oldest_tree_idx] = 0;
    agent_ptr->stats.stockpile += food_from_tree(oldest_tree_age);
  }
};

static void plant_action(agent_t *agent_ptr) {
  for (int i = 0; i < N_TREES; i++) {
    if (agent_ptr->stats.trees[i] == 0) {
      agent_ptr->stats.trees[i] = 1;
      return;
    }
  }
};

static void sell_action(agent_t *agent_ptr, info_t *info) {
  info->sellers[info->n_sellers] = agent_ptr->id;
  info->n_sellers++;
};

static void buy_action(agent_t *agent_ptr, info_t *info) {
  info->buyers[info->n_buyers] = agent_ptr->id;
  info->n_buyers++;
};


static int get_agent_state(agent_t *agent_ptr, info_t *info) {
  int state = 0;
  int z = info->n_states; // what should i call this?
  int s = get_stockpile_state(agent_ptr->stats.stockpile);
  state += (z /= STOCKPILE_LEVELS) * s;
  int w = get_wallet_state(agent_ptr->stats.wallet);
  state += (z /= WALLET_LEVELS)  * w;
  for (int i = 0; i < N_TREES; i++) {
    int t = get_tree_state(agent_ptr->stats.trees[i]);
    state += (z /= TREE_LEVELS) * t;
  }
  return state;
};

static int get_action_from_table(agent_t *agent_ptr, info_t *info, uint8_t **table,
      int (*state_f)(agent_t*, info_t*), int n_actions) {
  int max_action = 0;
  uint8_t max_action_val = 0;
  uint8_t action_val;
  for (int i = 0; i < n_actions; i++) {
    action_val = table[(*state_f)(agent_ptr, info)][i];
    if (action_val > max_action_val) {
      max_action_val = action_val;
      max_action = i;
    }
  }
  return max_action;
};

static int get_agent_action(agent_t *agent_ptr, info_t *info) {
  uint8_t **table = agent_ptr->actiontable;
  int n_actions = N_ACTIONS;
  return get_action_from_table(agent_ptr, info, table, get_agent_state,
      n_actions);
};

static int get_market_state(agent_t *agent_ptr, info_t *info) {
  int state = 0;
  int z = info->n_market_states;
  int s = get_stockpile_state(agent_ptr->stats.stockpile);
  state += (z /= STOCKPILE_LEVELS) * s;
  int w = get_wallet_state(agent_ptr->stats.wallet);
  state += (z /= WALLET_LEVELS)  * w;
  int bs = get_buysell_state(info->n_sellers, info->n_buyers);
  state += (z /= BUYSELL_LEVELS) * bs;
  return state;
};

static int get_sell_action(agent_t *agent_ptr, info_t *info) {
  uint8_t **table = agent_ptr->selltable;
  int n_actions = N_MARKET_ACTIONS;
  return get_action_from_table(agent_ptr, info, table, get_market_state,
    n_actions);
};

static int get_buy_action(agent_t *agent_ptr, info_t *info) {
  uint8_t **table = agent_ptr->buytable;
  int n_actions = N_MARKET_ACTIONS;
  return get_action_from_table(agent_ptr, info, table, get_market_state,
    n_actions);
};

static void take_action(agent_t *agent_ptr, info_t *info) {
  int action = get_agent_action(agent_ptr, info);
  if (action == 0) {
    harvest_action(agent_ptr);
  }
  else if (action == 1) {
    plant_action(agent_ptr);
  }
  else if (action == 2) {
    sell_action(agent_ptr, info);
  }
  else if (action == 3) {
    buy_action(agent_ptr, info);
  }
  else {
    fprintf(stderr, "action %i out of range", action);
    exit(EXIT_FAILURE);
  }
};

static void kill_agent(agent_t *agent_ptr) {
  agent_ptr->stats.is_dead = true;
  agent_ptr->stats.stockpile = 0;
}

static void buy_and_sell(info_t *info) {
  int agent_id;
  int price;
  int sell_levels[BUYSELL_LEVELS]; // initialize to 0
  int buy_levels[BUYSELL_LEVELS];
  // tdl: add action value to agent stats so that don't need separate list
  for (int i = 0; i < info->n_sellers; i++) {
    agent_id = info->sellers[i];
    price = get_sell_action(&(info->agents[agent_id]), info);
    info->agents[agent_id].stats.buysell_price = price;
    sell_levels[price]++;
  }
  for (int i = 0; i < info->n_buyers; i++) {
    agent_id = info->buyers[i];
    price = get_buy_action(&(info->agents[agent_id]), info);
    info->agents[agent_id].stats.buysell_price = price;
    buy_levels[price]++;
  }
};

static void end_of_step(info_t *info) {
  for (int idx = 0; idx < N_AGENTS; idx++) {
    for (int j = 0; j < N_TREES; j++) {
      if (info->agents[idx].stats.trees[j] > 0) {
        info->agents[idx].stats.trees[j] += 1;
      }
    }
    info->agents[idx].stats.stockpile--; // decrease food by 1
    if (info->agents[idx].stats.stockpile <= 0) { // check if anyone starved
    kill_agent(&(info->agents[idx]));
  }
  }
  info->n_sellers = 0;
  info->n_buyers = 0;
};

static int get_num_alive(info_t *info) {
  int alive_ct = 0;
  for (int idx = 0; idx < N_AGENTS; idx++) {
    if (info->agents[idx].stats.is_dead == false) {
      alive_ct++;
    }
  }
  return alive_ct;
};

static void agent_actions(info_t *info) {
  for (int idx = 0; idx < N_AGENTS; idx++) {
    if (info->agents[idx].stats.is_dead == false) {
      take_action(&(info->agents[idx]), info);
    }
  }
};

static void sim_step(info_t *info) {
  agent_actions(info);
  buy_and_sell(info);
  end_of_step(info);
  printf("%i left alive\n", get_num_alive(info));
};

static void sim_generation(info_t *info) {
  info->step = 0;
  while (info->step < GEN_STEPS) {
    sim_step(info);
    info->step++;
  }
}

static int do_the_thing() {
  srand(1);

  info_t info;
  info.agents = malloc(sizeof(agent_t)*N_AGENTS);
  info.sellers = malloc(sizeof(int)*N_AGENTS);
  info.n_sellers = 0;
  info.buyers = malloc(sizeof(int)*N_AGENTS);
  info.n_buyers = 0;
  info.gen = 0;
  info.step = 0;
  info.n_states = get_n_states();
  info.n_market_states = get_n_market_states();

  init_agents(&info);
  sim_init(&info);
  while (info.gen < N_GENERATIONS) {
    if (info.gen % 10 == 0) {
      printf("Beginning generation %i...\n", info.gen);
    }
    sim_generation(&info);
    info.gen++;
  }
  printf("Simulation complete.\n");
};

static void init_f(sim_t *sim_p) {
};

static void step_f(sim_t *sim_p) {
};

extern model_t evo01_model = {init_f, step_f, sizeof(agent_t)};