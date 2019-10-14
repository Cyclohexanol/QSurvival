#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "agent.h"

using namespace std;

#define X 10
#define Y 10

int Agent::nbActions = 1000;
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
				actions.push('w');
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

Agent::Agent(Agent * parent, bool mutate) {
	/*Iterator<char> itr = parent->actions.iterator();

	while (itr.hasNext()) {
		actions.push(itr.next());
	}*/

	reset();
}

bool Agent::live(Map * m, bool log) {

	if(!alive) return false;

	thirst -= 2;
	hunger -= 2;
	energy -= 2;
	score++;

	if(thirst <= 0 || hunger <= 0 || energy <= 0) {
		if(log) std::cout << "DEAD ! : score - "<< score << " | energy - " << energy <<" | thirst - "<< thirst <<" | hunger - "<< hunger << '\n';
		return alive = false;
	}


	char a = actionsQueue.front();
	actionsQueue.pop();

	switch (a) {
		case('u'):
			if(m->getCell(x-1,y) == Areas::Land) x -= 1;
			break;
		case('d'):
			if(m->getCell(x+1,y) == Areas::Land) x += 1;
			break;
		case('l'):
			if(m->getCell(x,y-1) == Areas::Land) y -= 1;
			break;
		case('r'):
			if(m->getCell(x,y+1) == Areas::Land) y += 1;
			break;
		case('s'):
			energy += 20;
			if(energy > initEnergy) energy = initEnergy;
			break;
		case('e'):
			if(m->getCell(x-1,y) == Areas::Food || m->getCell(x+1,y) == Areas::Food || m->getCell(x,y-1)
				== Areas::Food || m->getCell(x,y+1) == Areas::Food) {
				hunger += 100;
				if(hunger > initHunger) hunger = initHunger;
			}
			break;
		case('w'):
			if(m->getCell(x-1,y) == Areas::Water || m->getCell(x+1,y) == Areas::Water || m->getCell(x,y-1)
				== Areas::Water || m->getCell(x,y+1) == Areas::Water) {
				thirst += 250;
				if(thirst > initThirst) thirst = initThirst;
			}
			break;
		default:
			break;
	}

	if(log) std::cout << a << " [" << x << "," << y << "] : energy - " << energy <<" | thirst - "<< thirst <<" | hunger - "<< hunger << "\n";

	return true;
}

void Agent::reset() {
	thirst = Agent::initThirst;
	hunger = Agent::initHunger;
	energy = Agent::initEnergy;
	alive = true;
	x = X;
	y = Y;
	score = 0;
	actionsQueue = actions;
}

bool Agent::isAlive() {
	return alive;
}

bool Agent::emptyQueue() {
	return actionsQueue.empty();
}

int Agent::getX() {
	return x;
}

int Agent::getY() {
	return y;
}

int Agent::getScore() {
	return score;
}

/*
int main() {
	Map * m = new Map(20,20);

	Agent * a = new Agent();

	while(a->isAlive() && !a->emptyQueue()) {
		system("clear");
		a->live(m);

	  char c;
	  for (size_t i = 0; i < m->getRow(); i++)
	  {
	    for (size_t j=0; j < m->getCol(); j++)
	    {
				if(i == a->getX() && j == a->getY()) cout << "☺ ";
				else {
					if(m->getCell(i,j) == Food) c = 'F';
		      else if(m->getCell(i,j) == Water) c = '~';
		      else c = '.';
		      cout <<c<<" ";
				}

	    }
	    cout<<endl;
	  }

		usleep(100000);

	}


	return 0;
}*/
