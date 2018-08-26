========
Overview
========

This project is a framework for running time-step simulations of
interactions between large numbers of agents.

Models
------
The simulation program can run models from the models directory. Each
model should be a .c file defining, at a minimum, an agent type, an
initializer function run before the simulation begins, and a step
function to be run at each step of the simulation.

All functions and variables in the model's .c file should be declared
with the ``static`` specifier so that they will only be linked
internally. The only externally linked identifier should be a model_t 
instance that holds pointers to the init and step functions as well
as a size_t with the size of the agent type.

.. code:: c

 typedef struct sim {
  void (*init_f)(void *simu);
  void (*step_f)(void *simu);
  size_t agent_size;
 } model_t;

Running a simulation
--------------------
Simulations are run from the command line by passing in three
arguments: 1) the name of the model, 2) the number of agents to
create, and 3) the number of time steps to run for.

The simulation function creates a sim_t instance:

.. code:: c

 typedef struct sim_info {
  model_t sim;
  void *agents;
  int n_agents;
  int n_steps;
  int current_step;
 } sim_t;

It allocates memory for the agents array then passes the sim_t
to the model's init function. It then runs the model's step function
for the number of steps in n_steps.

Data output is handled in the step function (currently at least...).