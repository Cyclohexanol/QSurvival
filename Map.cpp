// I HOPE THIS IS WHAT YOU WERE LOOKING FOR, IF NOT PLEASE TELL ME.
// I AM TRYING TO BE ON THE SMAE PAGE AS YOU SO I AM ALSO WRTING SOME OTHER CODE TO DO THIS DIFFERENTLY.

#include <iostream>
#include <string>

#define GRID_SIZE 10

using namespace std;


int main (int argc, char *argv[])

{
  char grid[GRID_SIZE][GRID_SIZE];
  int number = 1;

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
          grid[i][j] = to_string(number).c_str()[0];
          number += 1;
        }
    }
        printf("\n----------------------------------------\n");

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
          printf(" %c *", grid[i][j]);
        }
        printf("\n----------------------------------------\n");
    }
    return 0;
}
