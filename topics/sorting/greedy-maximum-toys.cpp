#include <bits/stdc++.h>

using namespace std;

// Complete the maximumToys function below.
// TODO: Prove why Greedy works for this problem
int maximumToys(vector<int> prices, int k) {

    // Sort the prices in increasing order
    // (this is the greedy strategy)
    sort(begin(prices), end(prices));

    int toys = 0;
    for (auto p : prices) {
        k -= p;      // Picking a toy means paying the price

        if (k >= 0)  // If I had money to pick up the toy
            ++toys;
        else         // Money exhausted - no point looking at other toys
            break;
    }

    return toys;
}
