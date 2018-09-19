/*
 * Code taken from Wikipedia:
 * https://en.wikipedia.org/wiki/Erase-remove_idiom
 */

// Use g++ -std=c++11 or clang++ -std=c++11 to compile.

#include <algorithm> // remove and remove_if
#include <iostream>
#include <vector> // the general-purpose vector container

using namespace std;

bool is_odd(int i) { return (i % 2) != 0; }

void print(const vector<int> &vec) {
    for (const auto& i: vec)
        cout << i << ' ';
}

int main()
{
  // initialises a vector that holds the numbers from 0-9.
  vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
   print(v); cout << " - Vector V" << endl;

  // removes all elements with the value 5
  v.erase( remove( v.begin(), v.end(), 5 ), v.end() );
   print(v); cout << " - Vector V (with 5 erased)" << endl;

  // removes all odd numbers
  auto rem = remove_if(v.begin(), v.end(), is_odd);
   print(v); cout << " - Vector V (with odd numbers removed)" << endl;

   v.erase( remove_if(v.begin(), v.end(), is_odd), v.end() );
   print(v); cout << " - Vector V (with odd numbers erased)" << endl;

  return 0;
}

/*
Output:
0 1 2 3 4 5 6 7 8 9
0 1 2 3 4 6 7 8 9
0 2 4 6 8
*/
