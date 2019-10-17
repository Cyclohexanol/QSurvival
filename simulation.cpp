#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "agent.h"
#include "map.h"
#include "simulation.h"

using namespace std;

// Population size per generation
#define POPULATION_SIZE 100

// Default number of generations used in the simulation
#define GENERATIONS 1000

void Simulation::printWorld(Agent * a, Map * m) {

	// Print rows
	char c;
	for (size_t i = 0; i < m->getRow(); i++)
	{
		// Print columns
		for (size_t j=0; j < m->getCol(); j++)
		{
			// Print agent current cell
			if(i == a->getX() && j == a->getY()) cout << "☺ ";
			else {
				// Print food cell
				if(m->getCell(i,j) == Food) c = 'F';
				// Print water cell
				else if(m->getCell(i,j) == Water) c = '~';
				// Print land cell
				else c = '.';

				cout <<c<<" ";
			}

		}
		cout<<endl;
	}
}

void Simulation::run(bool log) {
	Map * m = new Map();

	// Queue of agents to run the simulation on for a generation
	queue<Agent *> simPop;

	// Temporary agent placeholder
	Agent * a;

	// Ask for the number of generations to simulate
	int gens = 0;
	std::cout << "How many generations would you like to run (1-10000)? ";
	std::cin >> gens;

	// Check for valid input, set to default if invalid
	if(gens < 1 || gens > 10000) gens = GENERATIONS;

	// Generate first generation of agents
	for (size_t i = 0; i < POPULATION_SIZE; i++) {
		a = new Agent();
		// Add agent to population
		Simulation::population.push_back(a);
		// Add agent to simulation queue
		simPop.push(a);
	}

	float avgScore;

	// Run simulation on each agent of the generation (contained in simPop)
	avgScore = runGeneration(simPop,m,log);

	// Print results of first generation
	std::cout << "--------------------" << '\n';
	std::cout << "Gen 1" << '\n';
	std::cout << "Average score : " << avgScore << '\n';
	std::cout << "Best agent : " << population.front()->getID() << " --  Score : " << population.front()->getScore() << '\n';
	std::cout << "--------------------" << '\n';

	// Temporary agent placeholder
	Agent * parent;

	// Iterate through all generations
	for (size_t i = 1; i < gens; i++) {

		// Add fittest agent to next generation
		parent = population.front();
		population.pop_front();
		population.push_back(parent);
		simPop.push(parent);

		// Generate 9 offsprings of fittest agent of last generation
		for (size_t i = 0; i < 9; i++) {
			a = new Agent(parent,true);
			Simulation::population.push_back(a);
			simPop.push(a);
		}

		// Generate 5 offsprings for each of the 1-16 fittest agents of last generation
		for (size_t i = 0; i < 16; i++) {
			parent = population.front();
			population.pop_front();
			population.push_back(parent);
			// Generate the 5 offsprings
			for (size_t i = 0; i < 5; i++) {
				a = new Agent(parent,true);
				Simulation::population.push_back(a);
				simPop.push(a);
			}
		}

		// Generate 10 fully random agents for this generation
		for (size_t i = 0; i < 10; i++) {
			a = new Agent();
			Simulation::population.push_back(a);
			simPop.push(a);
		}

		// Run the simulation on every agent in simulation
		avgScore = runGeneration(simPop,m,log);

		// Print result of current generation
		std::cout << "Gen " << i+1 << '\n';
		std::cout << "Average score : " << avgScore << '\n';
		std::cout << "Best agent : " << population.front()->getID() << " --  Score : " << population.front()->getScore() << '\n';
		std::cout << "--------------------" << '\n';
	}

	// Ask to display the life of the fittest agent
	std::cout << "Would you like to view best agent's life? [y/n]" << '\n';
	char answer;
	std::cin >> answer;

	// If answered yes, display the life of the fittest agent
	if(answer == 'y') {
		int turns = 1;
		a = population.front();
		a->reset();
		while(a->isAlive() && !a->emptyQueue()) {
			system("clear");
			a->live(m,true);
			printWorld(a,m);
			std::cout << "Turn : " << turns++ << '\n';
			int fps = 30;
			usleep(1000000/fps);
		}
	}
}

float Simulation::runGeneration(std::queue<Agent *> simPop, Map * m, bool log) {

	Agent * a;
	int size = simPop.size();
	int totalScore = 0;

	// Loop on all agents queued for the generation
	while(!simPop.empty()) {
		// Get the first agent of the queue
		a = simPop.front();

		// Run the each life step until the agent is dead or has an empty action queue
		while(a->isAlive() && !a->emptyQueue()) {
			if(log) system("clear");
			a->live(m,false);
		}

		totalScore += a->getScore();

		// Print the step information if log is activated
		if(log) std::cout << "ID : " << a->getID() << " -- Score : " << a->getScore() << '\n';

		// Pop the current agent out of the list
		simPop.pop();
	}

	// Sort the population from fittest to less fit
	population.sort([](Agent * a1, Agent * a2) {return a1->getScore() > a2->getScore();});

	// Only keep the 100 fittest agent of the population to free memory
	population.resize(100);

	return (float)totalScore / size;
}


int main() {

	// Create a new simulation
	Simulation * s = new Simulation();

	// Run the simulation
	s->run(false);

}
