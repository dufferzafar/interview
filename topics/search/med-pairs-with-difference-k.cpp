#include <bits/stdc++.h>

using namespace std;

// Iterative binary search
// returns true if goal is in arr
bool bsearch(vector<int>& vec, int goal) {

    int beg, mid, end;

    beg = 0, end = vec.size();

    while (beg <= end) {
        mid = beg + (end - beg) / 2;

        if (goal == vec[mid])
            return true;
        else if (goal < vec[mid])
            end = mid - 1;
        else
            beg = mid + 1;
    }

    return false;
}

// Complete the pairs function below.
int pairs(int k, vector<int> arr) {

    // Our answer
    int pairs = 0;

    // Ascending order
    sort(begin(arr), end(arr));

    for (auto x : arr)
        // if (binary_search(begin(arr), end(arr), x - k))
        if (bsearch(arr, x - k))
            ++pairs;

    return pairs;
}
