#include <bits/stdc++.h>

using namespace std;

// Complete the hourglassSum function below.
int hourglassSum(vector<vector<int>> arr) {
    // We could keep track of maximum ourselves, but STL!
    vector<int> sums;

    // Go-to each index and calculate sum of the hourglass
    // starting at that index
    for(int i = 0; i < arr.size() - 2; ++i) {
        for(int j = 0; j < arr[i].size() - 2; ++j) {
            sums.push_back(
                arr[i]  [j] + arr[i]  [j+1] + arr[i]  [j+2]
                            + arr[i+1][j+1] +
                arr[i+2][j] + arr[i+2][j+1] + arr[i+2][j+2]
            );
        }
    }

    // max_element returns an iterator - * dereferences it!
    return *max_element(begin(sums), end(sums));
}
