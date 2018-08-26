# simagents
Framework for running agent based simulations

## Running the simulation
To run the simulation from the command line, pass three arguments: 1) the label of the model you wish to run, 2) the number of agents to create, and 3) the number of time steps to run the simulation for. So to run the test model with 4 agents for 8 time steps, call `./simulation test 4 8`.

## Creating new models
To add a new model:
1. create a .c file in the models directory
2. In that file, add (at a minimum) an agent type definition, a function to call to initialize the model at the start of the simulation and another function that is called at each time step.
3. Add `#include "../simagents.h"` to the top of the file in order to use the model_t type.
4. Initialize a model_t instance (outside of any functions so that it can be externally linked) with the init and step functions and the size of the agent type.
5. Declare the model_t instance in the models.h file.
6. Edit the get_sim_from_str function in models.c to recognize the label for your model when it is called in argv and return the model_t instance from your model file.

TDL: Automate updating the models.c and models.h files so that just creating an appropriate .c file in the models directory will make it available after compiling
