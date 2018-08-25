=====================
Evolutionary Learning
=====================
This model uses a genetic algorithm to refine reinforcement learning parameters
for agents. Agents are generated from a genotype which defines their rate of
exploration vs exploitation as well as the internal rewards they experience at
any given state.

.. code::c

 typedef struct {
   uint8_t explore;
 }


At each time step, each agent decides an action to take by consulting its
state-action table to determine the values of the four actions it can take. It
adds its explore value to each value and then makes a weighted random choice.

Agent actions
-------------
1. Harvest - converts the oldest tree to food, based on the age of the tree.
2. Plant - plants a tree to grow food. There are four spots to plant trees.
3. Sell - adds the agent to the list of sellers for this turn.
4. Buy - adds the agent to the list of buyers for this turn.

+----------+---------------+
| Tree age | Food produced |
+==========+===============+
| 1 turn   | 0 food        |
+----------+---------------+
| 2 turns  | 1 food        |
+----------+---------------+
| 3 turns  | 3 food        |
+----------+---------------+
| 4+ turns | 5 food        |
+----------+---------------+

Selling and buying
------------------
Sellers set the minimum price they will sell for and buyers set the maximum price they will buy for. There are 