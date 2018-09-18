/**
 * https://www.hackerrank.com/challenges/luck-balance/
 */

#include <bits/stdc++.h>

using namespace std;

// Complete the luckBalance function below.
int luckBalance(int k, vector<vector<int>> contests) {

    // Our answer
    int balance = 0;

    // Fill this with luck values of important contests
    vector<int> imp_luck;

    for( auto c : contests ) {
        int luck = c[0], important = c[1];

        if ( important )
            imp_luck.push_back(luck);
        else
            // Can lose all non-important matches, so balance increases
            balance += luck;
    }

    // Small values first
    sort(begin(imp_luck), end(imp_luck));

    // Mistake (big! - found only by unlocking a testcase - was segfaulting before)
    // Handles the cases where imp_luck may be empty or smaller than k size
    k = min(k, (int) imp_luck.size());

    // Can lose k matches, so bigger k values add to balance
    balance += std::accumulate(end(imp_luck) - k, end(imp_luck), 0);

    // Will have to win remaining, so smaller n-k values deduct from balance
    balance -= std::accumulate(begin(imp_luck), end(imp_luck) - k, 0);

    return balance;
}
