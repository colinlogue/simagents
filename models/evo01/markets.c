static int get_n_market_states() {
  return BUYSELL_LEVELS * STOCKPILE_LEVELS * WALLET_LEVELS;
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

static int get_market_state(agent_t *agent_ptr, info_t *info) {
  int state = 0;
  int z = info->n_market_states;
  int s = get_stockpile_state(agent_ptr->stats.stockpile);
  state += (z /= STOCKPILE_LEVELS) * s;
  int w = get_wallet_state(agent_ptr->stats.wallet);
  state += (z /= WALLET_LEVELS)  * w;
  int bs = get_buysell_state(info->sellers->len, info->buyers->len);
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

static void buy_and_sell(info_t *info) {
  int agent_id;
  int cur_action;
  agent_t *cur_agent;
  queue_node_t *cur_node;

  queue_t *sell_qs[BUYSELL_LEVELS];
  queue_t *buy_qs[BUYSELL_LEVELS];
  for (int i = 0; i < BUYSELL_LEVELS; i++) {
    sell_qs[i] = q_create();
    buy_qs[i] = q_create();
  }

  // get sell level of each seller
  cur_node = info->sellers->head;
  while (cur_node) {
  	cur_agent = (agent_t*)(cur_node->content);
  	cur_action = get_sell_action(cur_agent, info);
  	q_append(sell_qs[cur_action], cur_agent, sizeof(*cur_agent));
  	cur_node = cur_node->next;
  }
  // get buy level of each buyer
  cur_node = info->buyers->head;
  while (cur_node) {
  	cur_agent = (agent_t*)(cur_node->content);
  	cur_action = get_buy_action(cur_agent, info);
  	q_append(buy_qs[cur_action], cur_agent, sizeof(*cur_agent));
  	cur_node = cur_node->next;
  }

  free(sell_qs);
  free(buy_qs);
};