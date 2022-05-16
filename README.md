# Genetic_AI
 Evolutionary Algorithms in UE4_LOGS

The puropse of this is to understand how agents can evolve to solve computational problems with very simple rules to evolve.
This algorithm begins with random alphabets and get closer by each generation to output the goal english sentance.

This resource shows some of the most important strategies and problems, evolutionary algorithms solve.
https://openai.com/blog/evolution-strategies/

The idea is to generate random agents, each with their own alphabets and assign a fitness score to each agent.
In this case if an agent at a certain poistion corelate to correct alphabet in that locaiton then it has a higher fitness value.

At each generation we have 100 agents and only the agents with the best fitness score survive to produce offsprings.
The offspring will have DNA identical to the parents with a chance of mutation.
