#include <bits/stdc++.h>

using namespace std;

int maxSubsetSum(vector<int> arr) {

    // People just name their arrays "DP"
    vector <int> dp(arr.size());
    dp[0] = arr[0];

    // Mistake : Was considering only arr[1]
    // dp[1] = arr[1];
    dp[1] = max(arr[1], arr[0]);

    for(int i = 2; i < arr.size(); ++i) {
        // Mistake : Was ignoring negative values, but what if all are negative?
        // int me = max(arr[i], 0);
        dp[i] = max(max(arr[i], arr[i] + dp[i-2]), dp[i-1]);
    }

    // Last element contains the max till there
    // BUG: Will the last element always be maximum or should I take last two elements?
    return dp.back();
}
