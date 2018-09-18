#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the getMinimumCost function below.
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
    int buys = 2;
    int start = 0;

    while(remaining > 0) {

        cout << "Cost: " << cost << "\n";

        // This tries to buy the first k flowers again & again
        // (is that correct?)
        cost += std::accumulate(begin(c) + start, begin(c) + start + remaining, 0,
                               [buys](int x, int y){
                                   cout << "Buys: " << buys << "\n";
                                   return x + buys*y;
                               });

        ++buys;

        remaining -= k;
        start += k;
    }

    return cost;
}
