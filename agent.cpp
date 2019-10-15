#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "agent.h"

using namespace std;

// Initial agent pos
#define X 25
#define Y 25

// Initiate static varaibles
int Agent::idCount = 0;
int Agent::nbActions = 2000;
int Agent::initThirst = 500;
int Agent::initHunger = 2000;
int Agent::initEnergy = 5000;

Agent::Agent() {
	// Set id and increase global counter
	id = Agent::idCount++;

	// Initiate score to 0
	score = 0;

	// Generate random action vector
	for (size_t i = 0; i < Agent::nbActions; i++) {
		actions.push_back(randAction());
	}

	// Initate all other fields
	reset();
}

Agent::Agent(Agent * parent, bool mutate) {

	// Initiate score to 0
	score = 0;

	// Set id and increase global counter
	id = Agent::idCount++;

	bool mut;

	// Loop through parents action vector
	for (size_t i = 0; i < parent->actions.size(); i++) {
		// Get a random bool with 1/4 probability of true
		mut = rand() % 4 == 0;

		// Mutate the current action if mut == true and add it to the action vector
		if(!mut || !mutate) actions.push_back(parent->actions[i]);
		else {
			// Add the parent's action to the offsprings action vector
			actions.push_back(randAction());
		}
	}

	// Initate all other fields
	reset();
}

bool Agent::live(Map * m, bool log) {

	// If agent is dead, return
	if(!alive) return false;

	// Decrease current stats for this life step and add 1 to score
	thirst -= 2;
	hunger -= 2;
	energy -= 2;
	score++;

	// Check for dead agent
	if(thirst <= 0 || hunger <= 0 || energy <= 0) {
		if(log) std::cout << "DEAD ! : score - "<< score << " | energy - " << energy <<" | thirst - "<< thirst <<" | hunger - "<< hunger << '\n';
		return alive = false;
	}

	// Get current action from the queue
	char a = actionsQueue.front();
	// Pop the action from the queue
	actionsQueue.pop();

	// Apply action
	switch (a) {
		// Move up
		case('u'):
			if(m->getCell(x-1,y) == Areas::Land) x -= 1;
			energy -= 10;
			hunger -= 5;
			break;
		// move down
		case('d'):
			if(m->getCell(x+1,y) == Areas::Land) x += 1;
			energy -= 10;
			hunger -= 5;
			break;
		// Move left
		case('l'):
			if(m->getCell(x,y-1) == Areas::Land) y -= 1;
			energy -= 10;
			hunger -= 5;
			break;
		// Move right
		case('r'):
			if(m->getCell(x,y+1) == Areas::Land) y += 1;
			energy -= 10;
			hunger -= 5;
			break;
		// Sleep
		case('s'):
			energy += 20;
			if(energy > initEnergy) energy = initEnergy;
			break;
		// Eat
		case('e'):
			// Check for neighboring food cell
			if(m->getCell(x-1,y) == Areas::Food || m->getCell(x+1,y) == Areas::Food || m->getCell(x,y-1)
				== Areas::Food || m->getCell(x,y+1) == Areas::Food) {
				hunger += 100;
				energy -= 10;
				if(hunger > initHunger) hunger = initHunger;
			}
			break;
		// Drink
		case('w'):
			// Check for neighboring water cell
			if(m->getCell(x-1,y) == Areas::Water || m->getCell(x+1,y) == Areas::Water || m->getCell(x,y-1)
				== Areas::Water || m->getCell(x,y+1) == Areas::Water) {
				thirst += 250;
				energy -= 10;
				if(thirst > initThirst) thirst = initThirst;
			}
			break;
		// Do nothing
		default:
			break;
	}

	// Log current step info if log is true
	if(log) std::cout << a << " [" << x << "," << y << "] * id - " << id <<" * : energy - "
		<< energy <<" | thirst - "<< thirst <<" | hunger - "<< hunger << "\n";

	return true;
}

void Agent::reset() {
	// Set feilds to initial state
	thirst = Agent::initThirst;
	hunger = Agent::initHunger;
	energy = Agent::initEnergy;
	alive = true;
	x = X;
	y = Y;

	// Empty current action queue
	while(!actionsQueue.empty()) actionsQueue.pop();

	// Add actions to the queue
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

	// Randomize a number from 0-7
	int a = rand() % 8;

	switch(a) {
		// Move up
		case(0):
			return 'u';
		// Move down
		case(1):
			return 'd';
		// Move left
		case(2):
			return 'l';
		// Move right
		case(3):
			return 'r';
		// Sleep
		case(4):
			return 's';
		// Eat
		case(5):
			return 'e';
		// Drink
		case(6):
			return 'w';
		// Do nothing
		case(7):
			return '_';
		// Default to do nothing
		default:
			return '_';
	}
}
