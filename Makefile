sim: simulation.o agent.o map.o
	g++ -o sim simulation.o agent.o map.o

simulation.o: simulation.cpp agent.cpp map.cpp
	g++ -std=c++11 -stdlib=libc++ -c simulation.cpp

map.o: map.cpp
	g++ -std=c++11 -stdlib=libc++ -c map.cpp

agent.o: agent.cpp map.cpp
	g++ -std=c++11 -stdlib=libc++ -c agent.cpp
