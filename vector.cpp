#include <iostream>
#include <vector>

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
    print_vector(v1);

    // Filled with squares
    vector<int> v2;
    for (int i = 0; i < 10; ++i) {
        v2.push_back(i * i);
    }
    print_vector(v2);

}
