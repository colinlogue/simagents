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
Run `python scripts/new_model.py <<LABEL>>` where <<LABEL>> is the name of the
model you would like to create.