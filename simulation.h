#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <list>
#include <queue>

class Simulation {

	private:
		// Population of all agents used in the simulation
		std::list<Agent *> population;

		// Run the simulation on all agents of the life cycle
		void runGeneration(std::queue<Agent *> simPop, Map * m, bool log);

	public:
		// Run the entire simulation
		void run(bool log);

		// Print the map and actions of an agent for an entire life cycle 
		void printWorld(Agent * a, Map * m);

};

#endif
