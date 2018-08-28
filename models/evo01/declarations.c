// market functions
static int get_n_market_states();
static int get_buysell_state(int, int);
static int get_market_state(agent_t *, info_t *);
static int get_sell_action(agent_t *, info_t *);
static int get_buy_action(agent_t *, info_t *);
static void buy_and_sell(info_t *);

// model functions
static int get_n_states();
static size_t get_actiontable_size();
static size_t get_buyselltable_size();
static void init_agents(info_t *);
static void sim_init(info_t *);
static int get_stockpile_state(uint8_t );
static int get_wallet_state(uint8_t );
static int get_tree_state(uint8_t );
static int food_from_tree(uint8_t );
static void harvest_action(agent_t *);
static void plant_action(agent_t *);
static void sell_action(agent_t *, info_t *);
static void buy_action(agent_t *, info_t *);
static int get_agent_state(agent_t *, info_t *);
static int get_action_from_table(agent_t *, info_t *, uint8_t **, int (*state_f)(agent_t*, info_t*), int);
static int get_agent_action(agent_t *, info_t *);
static void take_action(agent_t *, info_t *);
static void kill_agent(agent_t *);
static void end_of_step(info_t *);
static int get_num_alive(info_t *);
static void agent_actions(info_t *);
static void sim_step(info_t *);
static void sim_generation(info_t *);
static int do_the_thing();
static void init_f(sim_t *sim_p);
static void step_f(sim_t *sim_p);