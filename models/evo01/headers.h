#ifndef EVO01_H
#define EVO01_H

// headers
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include "../../simagents.h"
#include "../../utils/intmath.h"
#include "types.h"

// functions
int get_n_states();
int get_n_market_states();
size_t get_actiontable_size();
size_t get_buyselltable_size();
void init_agents(info_t *info);
void sim_init(info_t *info);
int get_stockpile_state(uint8_t stockpile);
int get_wallet_state(uint8_t wallet);
int get_tree_state(uint8_t tree_age);
int get_buysell_state(int n_sellers, int n_buyers);
int food_from_tree(uint8_t tree_age);
void harvest_action(agent_t *agent_ptr);
void plant_action(agent_t *agent_ptr);
void sell_action(agent_t *agent_ptr, info_t *info);
void buy_action(agent_t *agent_ptr, info_t *info);
int get_agent_state(agent_t *agent_ptr, info_t *info);
int get_action_from_table(agent_t *agent_ptr, info_t *info, uint8_t **table,
        int (*state_f)(agent_t*, info_t*), int n_actions);
int get_agent_action(agent_t *agent_ptr, info_t *info);
int get_market_state(agent_t *agent_ptr, info_t *info);
int get_sell_action(agent_t *agent_ptr, info_t *info);
int get_buy_action(agent_t *agent_ptr, info_t *info);
void take_action(agent_t *agent_ptr, info_t *info);
void kill_agent(agent_t *agent_ptr);
void buy_and_sell(info_t *info);
void end_of_step(info_t *info);
int get_num_alive(info_t *info);
void agent_actions(info_t *info);
void sim_step(info_t *info);
void sim_generation(info_t *info);

#endif