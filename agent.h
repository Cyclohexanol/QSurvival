#ifndef __AGENT_H__
#define __AGENT_H__

#include "map.h"

class Agent {
	private:

		int thirst, hunger, energy, x, y, score;
		std::queue<char> actions, actionsQueue;
		bool alive;


	public:
		static int nbActions, initThirst, initEnergy, initHunger;
		Agent();
		Agent(Agent * parent, bool mutate);
		bool live(Map * m, bool log);
		void reset();
		bool emptyQueue();
		bool isAlive();
		int getX();
		int getY();
		int getScore();
};

#endif
