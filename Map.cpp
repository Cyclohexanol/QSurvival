#include "map.h"
#include <iostream>
#include <string>

using namespace std;

Map::Map(int x, int y)

{
  row=y;
  col=x;
  grid.resize(x*y);
  addArea(x,y,Land);
  addArea(7,7,Water);
  addArea(3,3,Food,col-4,row-4);
  addArea(3,3,Food,col-8,row-17);
}

void Map::addArea(int x, int y, Areas a, int offset_x, int offset_y)

{
  for (size_t i = offset_x; i < offset_x+x; i++)
  {
    for (size_t j = offset_y; j< offset_y+y; j++)
    {
      setCell(i,j,a);
    }
  }
}

void Map::setCell(int x, int y, Areas a)

{
  if (x>=col)
  {return;}
  if (y>=row)
  {return;}

  grid[x*col+y]=a;
}

void Map::print()

{
  char c;
  for (size_t i = 0; i < row; i++)
  {
    for (size_t j=0; j< col; j++)
    {
      if(getCell(i,j) == Food) c = 'F';
      else if(getCell(i,j) == Water) c = 'W';
      else c = 'L';
      cout <<c<<" ";
    }
    cout<<endl;
  }
}

Areas Map::getCell(int x, int y)

{
  if (x < 0 || x>=col){return OutOfArea;}
  if (y < 0 || y>=row){return OutOfArea;}

  return grid[x*col+y];
}

int Map::getCol() {
   return col;
}

int Map::getRow() {
   return row;
}

/*
int main (int argc, char *argv[])

{
  int col=20;
  int row=20;

  Map *m = new Map(col,row);

  m->print();

    return 0;
}*/
