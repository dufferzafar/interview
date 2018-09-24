/**
 * https://www.hackerrank.com/challenges/ctci-ice-cream-parlor/
 *
 * My solution:
 *
 *  1. Build a (value, index) array - O(n) space & time
 *  2. Sort the array - O(nlogn)
 *  3. Find the two values that equal to a sum - O(n)
 *
 * Better solution?
 *
 *  1. Use a map <cost, index> - O(n) space
 *  2. Make one pass over the data - O(n)
 *
 */
#include <bits/stdc++.h>

using namespace std;

void whatFlavors_sort(vector<int> cost, int money) {

    // Convert cost vector to (val, idx) vector
    vector < pair<int, int> > cost_idx;
    for(int i = 0; i < cost.size(); ++i)
        cost_idx.push_back(make_pair(cost[i], i));


    // Sort by value
    sort(begin(cost_idx), end(cost_idx));

    // Linear algorithm to find numbers that equal a sum
    int l = 0, r = cost_idx.size() - 1;
    while ( l <= r ) {
        int sum =  cost_idx[l].first + cost_idx[r].first;
        if      (sum < money) ++l;
        else if (sum > money) --r;
        else /* (sum == money) */ {

            int idxL = cost_idx[l].second, idxR = cost_idx[r].second;
            // Mistake : Smaller id first, Larger id second
            cout << 1 + min(idxL, idxR) << " " << 1 + max(idxL, idxR) << endl;

            // Mistake : Didn't put in a break, so it was infinite looping
            break;
        }
    }
}

void whatFlavors_map(vector<int> cost, int money) {

    // Cost -> Index
    unordered_map<int, int> cost_pos;

    for(int i = 0; i < cost.size(); ++i) {

        if (cost_pos.count(cost[i]))
            cout << 1 + min(i, cost_pos[cost[i]]) <<  " "
                 << 1 + max(i, cost_pos[cost[i]]) << "\n";
        else
            cost_pos[money - cost[i]] = i;

    }
}
