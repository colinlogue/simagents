=================
Three Goods model
=================

This model simulates interactions between a number of agents
who each have a preference for one of three types of goods.
Each agent starts with a random amount of each good and a
randomly determined preference for one of them. At each time
step, agents are divided into random pairs to trade. If the
two agents each have a good that the other wants, they will
exchange them. If only one has a good that the other wants,
then they will try to exchange it for the third good (the one
that neither has a preference for). If neither has a good that
the other wants, or if they have the same preferences, or if
they are unable to trade, then there is no effect.

At each time step the total utility is calculated as the sum
over each agent of the amount of good that that agent has that
they have a preference for.

Agent model
-----------

:int id: A unique identifier for the agent.
:int amts[3]: An array of ints representing the amount of each
  good the agent has. Randomly initialized over (0, 4).
:int pref: Represents the index of the amts array holding the
  good that the agent prefers. Chosen randomly.


