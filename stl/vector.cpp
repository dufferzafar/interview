#include <iostream>
#include <vector>

#include <cstdlib>      // for rand
#include <algorithm>    // for sort, find

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

using namespace std;

// Print Generic Vectors
template <typename T>
void print_vector(const vector<T>& v) {
    for (typeof(v.begin()) it = v.begin(); it != v.end(); ++it) {
        cout << *it;

        if (it != v.end() - 1)
            cout << ", ";
    }
    cout << endl;
}

int main() {

    // Initialized with characters
    const char characters[] = {'S', 'H', 'A', 'D', 'A', 'B'};
    vector<char> v1(characters, characters+6);
    cout << "Vector of chars: "; print_vector(v1); cout << endl;

    // Filled with squares
    vector<int> v2;
    for (int i = 0; i < 10; ++i) {
        v2.push_back(rand() % 1000);
    }

    // Sorting
    sort(all(v2));
    cout << "Vector of random integers (sorted - ascending): "; print_vector(v2); cout << endl;

    sort(rall(v2));
    cout << "Vector of random integers (sorted - descending): "; print_vector(v2); cout << endl;

    // Check whether an element exists
    int number;
    cout << "Enter a number to find: ";
    cin >> number;

    if (find(all(v2), number) != v2.end()) {
        cout << "Found!" << endl;
    } else {
        cout << "Not Found!" << endl;
    }

    // Matrix
    vector< vector<int> matrix;
    vector<int> row;
    for (int i = 0; i < 10; ++i) {
        v3.push_back(rand() % 1000);
    }
}
