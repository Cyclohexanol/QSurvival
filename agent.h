#ifndef __AGENT_H__
#define __AGENT_H__

#include "map.h"
#include <queue>
#include <vector>

class Agent {
	private:

		// Agent stats, position, fitness score and unique id
		int thirst, hunger, energy, x, y, score, id;

		// Static list of actions. Used to creat the queue and pass on to next generation
		std::vector<char> actions;

		// Queue of actions, front gets pop every life cycle
		std::queue<char> actionsQueue;

		// Agent state
		bool alive;

		// Generates a random action by returning one of height char
		char randAction();


	public:
		// Initial & maximum agent stats and incremental ID counter
		static int nbActions, initThirst, initEnergy, initHunger, idCount;

		// Constructor with fully randomized action
		Agent();

		// Constructor with actions inherited from parent with random mutations
		Agent(Agent * parent, bool mutate);

		// Live one life cycle of agent
		bool live(Map * m, bool log);

		// Reset the agent to inital state
		void reset();

		// Check whether the action queue is empty
		bool emptyQueue();

		// Return whether the agent is alive
		bool isAlive();

		// Return agent X position
		int getX();

		// Return agent Y position
		int getY();

		// Return agent fitness score position
		int getScore();

		// Return agent ID position
		int getID();
};



#endif
