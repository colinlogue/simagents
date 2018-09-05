#include "headers.h"


#include "params.c"


static void sim_init(sim_t *sim_p) {
	// add init function here
}

static void sim_step(sim_t *sim_p) {
	// add step function here
}

extern model_t *build_simtest(void *sim_init(sim_t), void *sim_step(sim_t), size_t);