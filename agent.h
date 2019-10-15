#ifndef __AGENT_H__
#define __AGENT_H__

#include "map.h"
#include <queue>
#include <vector>

class Agent {
	private:

		int thirst, hunger, energy, x, y, score, id;
		std::queue<char> actionsQueue;
		std::vector<char> actions;
		bool alive;
		char randAction();


	public:
		static int nbActions, initThirst, initEnergy, initHunger, idCount;
		Agent();
		Agent(Agent * parent, bool mutate);
		bool live(Map * m, bool log);
		void reset();
		bool emptyQueue();
		bool isAlive();
		int getX();
		int getY();
		int getScore();
		int getID();
};



#endif
