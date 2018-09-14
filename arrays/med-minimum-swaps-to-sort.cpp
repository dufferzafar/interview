#include <bits/stdc++.h>

using namespace std;

/*
 * Uses selection sort which is known to result in minimum swaps?
 *
 * Issue: this is O(n^2)
 */
int min_swaps_selection_sort(vector<int> arr) {

    int swaps = 0;

    // Algorithm: Make n passes, find minimum, swap
    // Invariant: arr[:i-1] is sorted?
    int min, tmp;
    int n = arr.size();

    // Make n passes to make arr[:n-1] sorted
    for (int i = 0; i < n; ++i) {

        // Find minimum in arr[i:]
        min = i; // assume this index stores the minimum
        for (int j = i; j < n; ++j) {
            if (arr[j] < arr[min])
                min = j;
        }

        // Swap only if idx has been changed
        if (min != i) {
            tmp = arr[min]; arr[min] = arr[i]; arr[i] = tmp;

            ++swaps;
        }
    }

    return swaps;
}
