// I HOPE THIS IS WHAT YOU WERE LOOKING FOR, IF NOT PLEASE TELL ME.
// I AM TRYING TO BE ON THE SMAE PAGE AS YOU SO I AM ALSO WRTING SOME OTHER CODE TO DO THIS DIFFERENTLY.
#include "Map.h"
#include <iostream>
#include <string>

using namespace std;

Map::Map() {

  grid = new char *[10];
  for (size_t i = 0; i < 10; i++) {
    grid[i] = new char[10];
  }

  int number = 1;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
          grid[i][j] = to_string(number).c_str()[0];
          number += 1;
        }
    }

}

void Map::print() {
  printf("\n----------------------------------------\n");

for (int i = 0; i < 10; i++)
{
  for (int j = 0; j < 10; j++)
  {
    printf(" %c *", grid[i][j]);
  }
  printf("\n----------------------------------------\n");
}
}

char Map::getCell(int x, int y) {
  return '_';
}
