
## Pieces
Simulations consist of a number of agents that interact with each other and an
environment over a series of steps.

### Agents
An agent consists of an internal state and some method of determining an action
to take. On each time step, the agent:

1. receives a set of signals from the environment;
2. updates its internal state with this new information; and
3. sends a set of signals to the environment indicating an action.

### Environment
The environment is the global state of the simulation as well as a series of
rules for sending and reveing signals from agents and for updating its state.
It also sends output signals to the user. On each time step, the environment:

1. sends appropriate input signals to each of the agents;
2. receives outputs signals from each of the agents;
3. updates the global state after all signals have been received; and
4. sends an output signal to the user.
