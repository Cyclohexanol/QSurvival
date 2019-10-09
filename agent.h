#ifndef __AGENT_H__
#define __AGENT_H__

class Agent {
	private:

		static final int nbActions, initThirst, initEnergy, initHunger;

		std::queue<char> actions;
		int thrist, hunger, energy;
		bool alive;

	public:
		Agent();
		Agent(Agent parent, bool mutate);
		bool live(Map map);
		void reset();
};

#endif
