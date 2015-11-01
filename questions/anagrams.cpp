#include <iostream>

#include <vector>
#include <map>
#include <string>

#include <sstream>

#include <algorithm>

#define iter(v) typeof(v.begin())

using namespace std;

// Utility Functions

string trim(string const &str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

typedef vector<string> strings;

// Print a vector!
void print_vector(strings vec) {
    for (iter(vec) it = vec.begin();
        it != vec.end();
        ++it) {
        cout << *it << ", ";
    }
}

// Core
vector<strings> ClubAnagrams(strings inp) {

    map<string, strings> dict;

    for (iter(inp) it = inp.begin();
        it != inp.end();
        ++it) {

        string item = *it;
        sort(item.begin(), item.end());

        dict[item].push_back(*it);
    }

    vector<strings> rv;

    for (iter(dict) it = dict.begin();
        it != dict.end();
        ++it) {

        if ((*it).second.size() > 1) {
            rv.push_back((*it).second);
        }
    }

    return rv;
}

int main(int argc, char const *argv[]) {

    strings input;
    istringstream stream("debitcard, elvis, silent, badcredit, lives, freedom, listen, levis");

    // Parse a comma separated string and
    // build a vector of strings
    string tok;
    while (getline(stream, tok, ',')) {
        input.push_back(trim(tok));
    }

    vector<strings> output = ClubAnagrams(input);

    // Print groups
    for (iter(output) it = output.begin();
        it != output.end();
        ++it) {
        print_vector(*it);
        cout << endl;
    }

    return 0;
}
