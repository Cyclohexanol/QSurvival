#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "agent.h"
##include "map.h"

using namespace std;

#define X 5
#define Y 5

int Agent::nbActions = 100;
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

	reset(X,Y);
}

Agent::Agent(Agent * parent, bool mutate) {
	/*Iterator<char> itr = parent->actions.iterator();

	while (itr.hasNext()) {
		actions.push(itr.next());
	}*/

	reset(X,Y);
}

bool Agent::live(map m) {

	if(!alive) return false;

	thirst -= 2;
	hunger -= 2;
	energy -= 2;

	if(thirst <= 0 || hunger <= 0 || energy <= 0) {
		return alive = false;
	}

	char a = actionsQueue.pop();

	switch (a) {
		case('u'):
			if(m.getCell(x-1,y) == Land) x -= 1;
			break;
		case('d'):
			if(m.getCell(x+1,y) == Land) x += 1;
			break;
		case('l'):
			if(m.getCell(x,y-1) == Land) y -= 1;
			break;
		case('r'):
			if(m.getCell(x,y+1) == Land) y += 1;
			break;
		case('s'):
			energy += 20;
			if(energy > initEnergy) energy = initEnergy;
			break;
		case('e'):
			if(getCell(x-1,y) == Food || getCell(x+1,y) == Food || getCell(x,y-1) == Food || getCell(x,y+1) == Food) {
				hunger += 100;
				if(hunger > initHunger) hunger = initHunger;
			}
			break;
		case('d'):
			if(getCell(x-1,y) == Water || getCell(x+1,y) == Water || getCell(x,y-1) == Water || getCell(x,y+1) == Water) {
				thirst += 250;
				if(thirst > initThirst) thirst = initThirst;
			}
			break;
		default:
			break;
	}

	std::cout << a << " ";

	return true;
}

void Agent::reset(int x, int y) {
	thirst = Agent::initThirst;
	hunger = Agent::initHunger;
	energy = Agent::initEnergy;
	alive = true;
	x = x;
	y = y;
	actionsQueue = actions;
}

int main() {
	return 0;
}
