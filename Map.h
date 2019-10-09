#ifndef __MAP_H__
#define __MAP_H__

#define GRID_SIZE 10

class Map {
	private:
		char ** grid;

	public:

		Map();

		void print();
		char getCell(int x, int y);
};

#endif
