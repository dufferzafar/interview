#include <iostream>
#include <vector>

using namespace std;

// Print Generic Vectors
template <typename T>
void print_vector(const vector<T>& v) {
    for (typename vector<T>::const_iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it;

        if (it != v.end() - 1)
            cout << ", ";
    }
    cout << endl;
}

int main() {

    // Initialized with characters
    vector<char> v1 = {'S', 'H', 'A', 'D', 'A', 'B'};
    print_vector(v1);

    // Filled with squares
    vector<int> v2;
    for (int i = 0; i < 10; ++i) {
        v2.push_back(i * i);
    }
    print_vector(v2);

}
