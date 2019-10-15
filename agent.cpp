#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "agent.h"

using namespace std;

#define X 25
#define Y 25

int Agent::idCount = 0;
int Agent::nbActions = 2000;
int Agent::initThirst = 500;
int Agent::initHunger = 2000;
int Agent::initEnergy = 5000;

Agent::Agent() {
	id = Agent::idCount++;
	score = 0;
	int a = 0;

	for (size_t i = 0; i < Agent::nbActions; i++) {
		actions.push_back(randAction());
	}

	reset();
}

Agent::Agent(Agent * parent, bool mutate) {

	score = 0;
	id = Agent::idCount++;

	bool mut;

	for (size_t i = 0; i < parent->actions.size(); i++) {
		mut = rand() % 4 == 0;
		if(!mut || !mutate) actions.push_back(parent->actions[i]);
		else {
			actions.push_back(randAction());
		}
	}

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
			energy -= 10;
			hunger -= 5;
			break;
		case('d'):
			if(m->getCell(x+1,y) == Areas::Land) x += 1;
			energy -= 10;
			hunger -= 5;
			break;
		case('l'):
			if(m->getCell(x,y-1) == Areas::Land) y -= 1;
			energy -= 10;
			hunger -= 5;
			break;
		case('r'):
			if(m->getCell(x,y+1) == Areas::Land) y += 1;
			energy -= 10;
			hunger -= 5;
			break;
		case('s'):
			energy += 20;
			if(energy > initEnergy) energy = initEnergy;
			break;
		case('e'):
			if(m->getCell(x-1,y) == Areas::Food || m->getCell(x+1,y) == Areas::Food || m->getCell(x,y-1)
				== Areas::Food || m->getCell(x,y+1) == Areas::Food) {
				hunger += 100;
				energy -= 10;
				if(hunger > initHunger) hunger = initHunger;
			}
			break;
		case('w'):
			if(m->getCell(x-1,y) == Areas::Water || m->getCell(x+1,y) == Areas::Water || m->getCell(x,y-1)
				== Areas::Water || m->getCell(x,y+1) == Areas::Water) {
				thirst += 250;
				energy -= 10;
				if(thirst > initThirst) thirst = initThirst;
			}
			break;
		default:
			break;
	}

	if(log) std::cout << a << " [" << x << "," << y << "] * id - " << id <<" * : energy - "
		<< energy <<" | thirst - "<< thirst <<" | hunger - "<< hunger << "\n";

	return true;
}

void Agent::reset() {
	thirst = Agent::initThirst;
	hunger = Agent::initHunger;
	energy = Agent::initEnergy;
	alive = true;
	x = X;
	y = Y;
	while(!actionsQueue.empty()) actionsQueue.pop();

	for (size_t i = 0; i < actions.size(); i++) {
		actionsQueue.push(actions[i]);
	}
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

int Agent::getID() {
	return id;
}

char Agent::randAction() {
	int a = rand() % 8;

	switch(a) {
		case(0):
			return 'u';
		case(1):
			return 'd';
		case(2):
			return 'l';
		case(3):
			return 'r';
		case(4):
			return 's';
		case(5):
			return 'e';
		case(6):
			return 'w';
		case(7):
			return '_';
		default:
			return '_';
	}
}
