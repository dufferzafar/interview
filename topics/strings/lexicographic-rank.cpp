/**
 * Microsoft
 *
 * https://www.interviewbit.com/problems/sorted-permutation-rank/
 */

#include <bits/stdc++.h>
using namespace std;

#define mod 1000003
#define frange 256

int facts[frange];

void precalc_facts() {
    facts[0] = facts[1] = 1;
    for(int i = 2; i < frange; ++i) {
        facts[i] = (i * facts[i-1]) % mod;
    }
}

int Solution::findRank(string str)
{
    // Pre-calculate all factorials
    precalc_facts();

    // Frequency Counts
    // Since no letter repeats - this'll be 0/1
    int freq[256] = {0};
    for (auto ch : str)
        freq[ch]++;

    int rank = 1;

    int n = str.length();
    for (int i = 0; i < n; ++i) {

        // Count letters smaller than the current one
        int cnt = 0;
        for(int j = 0; j < str[i]; ++j) {
            cnt += freq[j];
        }

        rank = (rank + (cnt * facts[n-i-1]) % mod) % mod;

        // Remove this character from count
        freq[str[i]] = 0;

    }

    return rank;
}
