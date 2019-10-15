#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "agent.h"
#include "map.h"
#include "simulation.h"

using namespace std;

#define POPULATION_SIZE 100
#define GENERATIONS 10

void Simulation::printWorld(Agent * a, Map * m) {
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
}

void Simulation::run(bool log) {
	Map * m = new Map();

	queue<Agent *> simPop;
	Agent * a;

	int gens = 0;
	std::cout << "How many generations would you like to run (1-10000)? ";
	std::cin >> gens;

	if(gens < 1 || gens > 10000) gens = GENERATIONS;

	for (size_t i = 0; i < POPULATION_SIZE; i++) {
		a = new Agent();
		Simulation::population.push_back(a);
		simPop.push(a);
	}

	runGeneration(simPop,m,log);

	std::cout << "--------------------" << '\n';
	std::cout << "Gen 1" << '\n';
	std::cout << "Best agent : " << population.front()->getID() << " --  Score : " << population.front()->getScore() << '\n';
	std::cout << "--------------------" << '\n';

	Agent * parent;

	for (size_t i = 1; i < gens; i++) {

		parent = population.front();
		population.pop_front();
		population.push_back(parent);
		simPop.push(parent);
		for (size_t i = 0; i < 9; i++) {
			a = new Agent(parent,true);
			Simulation::population.push_back(a);
			simPop.push(a);
		}


		for (size_t i = 0; i < 8; i++) {
			parent = population.front();
			population.pop_front();
			population.push_back(parent);
			for (size_t i = 0; i < 5; i++) {
				a = new Agent(parent,true);
				Simulation::population.push_back(a);
				simPop.push(a);
			}
		}


		for (size_t i = 0; i < 10; i++) {
			a = new Agent();
			Simulation::population.push_back(a);
			simPop.push(a);
		}

		for (size_t i = 0; i < 20; i++) {
			a = new Agent();
			Simulation::population.push_back(a);
			simPop.push(a);
		}

		runGeneration(simPop,m,log);

		std::cout << "Gen " << i+1 << '\n';
		std::cout << "Best agent : " << population.front()->getID() << " --  Score : " << population.front()->getScore() << '\n';
		std::cout << "--------------------" << '\n';
	}

	std::cout << "Would you like to view best agent's life? [y/n]" << '\n';
	char answer;
	std::cin >> answer;
	if(answer == 'y') {
		a = population.front();
		a->reset();
		while(a->isAlive() && !a->emptyQueue()) {
			system("clear");
			a->live(m,true);
			printWorld(a,m);
			usleep(50000);
		}
	}
}

void Simulation::runGeneration(std::queue<Agent *> simPop, Map * m, bool log) {

	Agent * a;

	while(!simPop.empty()) {
		a = simPop.front();
		while(a->isAlive() && !a->emptyQueue()) {
			if(log) system("clear");
			a->live(m,false);
		}

		if(log) std::cout << "ID : " << a->getID() << " -- Score : " << a->getScore() << '\n';

		simPop.pop();
	}

	population.sort([](Agent * a1, Agent * a2) {return a1->getScore() > a2->getScore();});
	population.resize(100);
}


int main() {
	Simulation * s = new Simulation();
	s->run(false);

}
