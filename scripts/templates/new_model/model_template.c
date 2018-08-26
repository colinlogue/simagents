#include "headers.h"


#include "params.c"

void sim_init(sim_t *sim_p) {
	// add init function here
}

void sim_step(sim_t *sim_p) {
	// add step function here
}

model_t <<LABEL>>;
<<LABEL>>.init_f = sim_init;
<<LABEL>>.step_f = sim_step;
<<LABEL>>.agent_size = sizeof(agent_t);