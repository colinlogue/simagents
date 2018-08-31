# simagents
Framework for running agent based simulations

## Running the simulation
To run the simulation from the command line, pass three arguments: 1) the label
of the model you wish to run, 2) the number of agents to create, and 3) the
number of time steps to run the simulation for. So to run the test model with 4
agents for 8 time steps, call `./simulation test 4 8`.

TDL: better param passing from shell

## Creating a new model
There is a python script for initializing a new model in the models directory.
<<<<<<< HEAD
Run `python scripts/new_model.py <<LABEL>>` where <<LABEL>> is the name of the
model you would like to create.

## Running a simulation
The `main` function parses the command line argument to obtain the name of the
model to be used (passed to a hash dict to return the model's build function)
as well as any parameters passed to the model to override its defaults.

1. `init_simulation` processes the command line arguments and returns a `sim_t`.
2. That `sim_t` is passed to run_simulation, which 