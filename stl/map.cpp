#include <iostream>

#include <stdint.h>

#include <map>
#include <unordered_map>

using namespace std;

int main() {

    // Empty string -> string vector
    // Push random stuff

    std::unordered_map<uint256, std::pair<int, char>> test;

    test[3] = std::make_pair(8, 'a');

    std::cout << "Map Size: " << test.size();

    // Iterate
    // over keys
    // over values
    // over (key, value) pairs

    // Standard Map Functions

    // A List (Vector) of Maps
}
