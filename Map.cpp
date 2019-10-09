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
  for (size_t i = 0; i < row; i++)
  {
    for (size_t j=0; j< col; j++)
    {
      cout <<getCell(i,j)<<" ";
    }
    cout<<endl;
  }
}

char Map::getCell(int x, int y)

{
  if (x>=col){return 'x';}
  if (y>=row){return 'x';}

  if (grid[x*col+y]==Water){return 'W';}
  if (grid[x*col+y]==Food){return 'F';}
  return 'L';
}

int main (int argc, char *argv[])

{
  int col=20;
  int row=20;

  Map *m = new Map(col,row);

  m->addArea(7,7,Water);
  m->addArea(3,3,Food,col-4,row-4);
  m->addArea(3,3,Food,col-8,row-17);
  m->print();

  cout<<endl;
  cout<<endl;
  cout<< "Well there you go Ambroise, it took me a while to read and understand but tadaaaa :)\n";
  cout<<endl;
  
    return 0;
}
