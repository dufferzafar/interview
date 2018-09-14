#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int getMinimumCost(int k, vector<int> c) {

    // Our answer
    long cost = 0;

    // Small values first
    sort(begin(c), end(c));

    int n = c.size();

    // Handles that case when k is greater than n etc.
    // (we have more people than flowers - pick em all!)
    k = min(k, n);

    // Each person first picks the k largest flowers
    cost += std::accumulate(end(c) - k, end(c), 0);

    // Each person now picks the first smallest flowers
    // (but the cost is calculated in a weird way)
    // TODO: will need to do this in a loop - while (k < n)
    int remaining = n-k;

    while(remaining > 0) {
        cost += std::accumulate(begin(c), begin(c) + remaining, 0,
                               [](int x, int y){ return x + 2*y; });

        remaining -= k;
    }

    return cost;
}
