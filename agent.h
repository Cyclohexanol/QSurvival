#ifndef __AGENT_H__
#define __AGENT_H__

class Agent {
	private:

		std::queue<char> actions, actionsQueue;
		int thirst, hunger, energy, x, y;
		bool alive;

	public:
		static int nbActions, initThirst, initEnergy, initHunger;
		Agent();
		Agent(Agent * parent, bool mutate);
		bool live();
		void reset(int x, int y);
};

#endif
