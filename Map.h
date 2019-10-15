#ifndef __MAP_H__
#define __MAP_H__
#include <vector> // Using vector to be able to resize the array according to the input.

enum Areas // Using enum to pre define the data type.

{
  Land=1,
	Water=2,
  Food=3,
	OutOfArea=-1
};

// Creating the class for the Grid/Map.

class Map

{
	private:

		std::vector<Areas> grid; // Applying the vector
		int row;
		int col;

		void addArea(int x, int y, Areas v, int offset_x=0, int offset_y=0); // Using offsets to limit the premacies
    void setCell(int x, int y, Areas a);

	public:

		Map();

		void print();
		Areas getCell(int x, int y);
    int getCol();
    int getRow();

};

#endif
