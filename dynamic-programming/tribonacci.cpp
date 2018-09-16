/**
 * https://www.hackerrank.com/challenges/ctci-recursive-staircase/
 */

#include <bits/stdc++.h>

using namespace std;

unordered_map<int, int> memo = {
    {1, 1},
    {2, 2},
    {3, 4},
};

// Tribonacci Numbers
int stepPerms(int n) {
    if (!memo.count(n))
        memo[n] = stepPerms(n-1) + stepPerms(n-2) + stepPerms(n-3);

    return memo[n] % 10000000007;
}
