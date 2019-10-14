#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "agent.h"
#include "map.h"
#include "simulation.h"

using namespace std;

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
	Map * m = new Map(20,20);

	Agent * a = new Agent();

	while(a->isAlive() && !a->emptyQueue()) {
		if(log) system("clear");
		a->live(m,log);

		if(log){
			printWorld(a,m);

			usleep(100000);
		}
	}

	std::cout << "Score : " << a->getScore() << '\n';
}

int main() {
	Simulation * s = new Simulation();
	s->run(true);

}
