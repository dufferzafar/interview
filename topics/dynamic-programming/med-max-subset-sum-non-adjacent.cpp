#include <bits/stdc++.h>

using namespace std;

int maxSubsetSum(vector<int> arr) {

    vector <int> max_sum(arr.size());
    max_sum[0] = arr[0];

    // Mistake : Was considering only arr[1]
    // max_sum[1] = arr[1];
    max_sum[1] = max(arr[1], arr[0]);

    for(int i = 2; i < arr.size(); ++i) {
        // Mistake : Was ignoring negative values, but what if all are negative?
        // int me = max(arr[i], 0);
        max_sum[i] = max(max(arr[i], arr[i] + max_sum[i-2]), max_sum[i-1]);
    }

    // Last element contains the max till there
    return max_sum.back();
}
