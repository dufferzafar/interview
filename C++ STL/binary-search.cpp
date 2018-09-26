#include <iostream>
#include <algorithm>

#include <vector>

using namespace std;

template <typename itr , typename T>
int binary_search_idx(itr beg, itr end, T val) {
    itr res = std::lower_bound(beg, end, val);

    if (!(res == end) && !(val < *res))
        return std::distance(beg, res);

    return -1;
}

int main() {
    vector<int> vec {3, 5, 7, 9, 11, 18};

    cout << "Vector: ";
    for(auto& v : vec) cout << v << " "; cout << endl;

    int f;
    cout << "Enter element to find: "; cin >> f;

    cout << f << " is at index "
         << binary_search_idx(begin(vec), end(vec), f);
}
