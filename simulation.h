#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <list>
#include <queue>

class Simulation {

	private:
		std::list<Agent *> population;
		void runGeneration(std::queue<Agent *> simPop, Map * m, bool log);

	public:
		void run(bool log);
		void printWorld(Agent * a, Map * m);

};

#endif
