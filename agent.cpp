#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
#include "Map.h"

using namespace std;

int Agent::nbActions = 10000;
int Agent::initThirst = 500;
int Agent::initHunger = 2000;
int Agent::initEnergy = 5000;

Agent::Agent() {
	srand (time(NULL));
	int a = 0;

	for (size_t i = 0; i < Agent::nbActions; i++) {
		a = rand() % 8;

		switch(a) {
			case(0):
				actions.push('u');
				break;
			case(1):
				actions.push('d');
				break;
			case(2):
				actions.push('l');
				break;
			case(3):
				actions.push('r');
				break;
			case(4):
				actions.push('s');
				break;
			case(5):
				actions.push('e');
				break;
			case(6):
				actions.push('d');
				break;
			case(7):
				actions.push('_');
				break;
			default:
				actions.push('_');
		}
	}

	reset();
}

Agent::Agent(Agent parent, bool mutate) {
	actions

	reset();
}

bool live(Map map) {
	// TODO
	return true;
}
void reset() {
	thirst = Agent::initThirst;
	hunger = Agent::initHunger;
	energy = Agent::initEnergy;
	alive = true;
}
