/**
 * https://www.hackerrank.com/challenges/angry-children/
 */

#include <bits/stdc++.h>

using namespace std;

int maxMin(int k, vector<int> arr) {

    // Small values first
    sort(begin(arr), end(arr));

    // Differences of chunks of K size
    vector<int> chunks;
            // Mistake: Off-by-one error of i
    for (int i = 0; i < arr.size() - k + 1; ++i)
        chunks.push_back(arr[i+k-1] - arr[i]);

    return *min_element(begin(chunks), end(chunks));

}

// auto result = minmax_element(begin(arr), begin(arr)+k);
// int mn = *result.first, mx = *result.second;
