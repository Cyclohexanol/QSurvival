//This is just a test that i was doing to check the working of a map on a table.
//I am working on making a 1D map currently so i will let you know soon.

#include <iostream>
#include <iterator>
#include <map>
using namespace std:

int main()
{
 map<int, char> map1;
 map<int, char>::iterator cursor;
  map1[1] = 'a';
  map2[2] = 'b';

 map.begin();
  cout << "Container \n";
  cout << "Key\telements \n";

 for (cursor = map1.begin(); cursor != map1.end(); cursor++)

{
  cout << cursor->first;
  cout << '\t' << cursor->second << "\n" <<endl;
}

map1.insert({3, 'c'});
  cout << "New container \n";
  cout << "Key\tElements \n";

for (cursor = map1.begin(); cursor != map1.end(); cursor++)

{
  cout << cursor->first;
  cout<< '\t' << cursor->second <<"\n" <<endl;
}

}

