/**
 * https://www.hackerrank.com/challenges/an-interesting-game-1/
 */

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Count number of max's from left to right
string gamingArray(vector<int> arr) {

    int mx = arr[0];
    int cnt = 1;

    for (auto el : arr) {
        if (el > mx) {
            mx = el;
            ++cnt;
        }
    }

    cerr << cnt << endl;

    return (cnt % 2 == 0) ? "ANDY" : "BOB";
}
