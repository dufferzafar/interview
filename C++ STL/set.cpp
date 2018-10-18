#include <bits/stdc++.h>

using namespace std;

int main() {

    set<int> S = {1,2,3,4};

    for (auto el : S) cout << el << " ";
    cout << endl;

    auto p = S.find(2);
    S.erase(p);

    for (auto el : S) cout << el << " ";
    cout << endl;

    // Tries to remove an inexistent element - fails!
    p = S.find(10);
    S.erase(p);

    for (auto el : S) cout << el << " ";
    cout << endl;

    return 0;
}
