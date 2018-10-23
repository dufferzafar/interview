/**
 * Test: memset vs std::fill
 *
 * Result: Fuck memset, use std::fill
 */

#include <bits/stdc++.h>
using namespace std;

int main() {

    int n = 10;
    int dp[n];

    memset(dp, 0, sizeof(dp));
    for(int i = 0; i < n; ++i) cout << dp[i] << " "; cout << endl;

    memset(dp, 1, sizeof(dp));
    for(int i = 0; i < n; ++i) cout << dp[i] << " "; cout << endl;

    cout << "----" << endl;

    memset(dp, INT_MIN, sizeof(dp));
    for(int i = 0; i < n; ++i) cout << dp[i] << " "; cout << endl;

    memset(dp, INT_MAX, sizeof(dp));
    for(int i = 0; i < n; ++i) cout << dp[i] << " "; cout << endl;

    cout << "----" << endl;

    fill(dp, dp + 10, 0);
    for(int i = 0; i < n; ++i) cout << dp[i] << " "; cout << endl;

    fill(dp, dp + 10, 16);
    for(int i = 0; i < n; ++i) cout << dp[i] << " "; cout << endl;

    cout << "----" << endl;

    fill(dp, dp + 10, INT_MIN);
    for(int i = 0; i < n; ++i) cout << dp[i] << " "; cout << endl;

    fill(dp, dp + 10, INT_MAX);
    for(int i = 0; i < n; ++i) cout << dp[i] << " "; cout << endl;

    return 0;
}
