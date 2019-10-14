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
}

int main() {
	Simulation * s = new Simulation();
	s->run(false);
}
