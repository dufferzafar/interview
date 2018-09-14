#include <bits/stdc++.h>

using namespace std;

// Complete the minimumAbsoluteDifference function below.
int minimumAbsoluteDifference(vector<int> arr) {

    // Difference between two numbers will be minimum
    // if they lie "close" to each other on the number line
    // So we first sort, and then find difference of adjacent numbers
    sort(begin(arr), end(arr));

    // Comes from the <numeric> header
    vector<int> diff;
    adjacent_difference(begin(arr), end(arr),
                        back_inserter(diff));

    // First element of diff is arr[0] so we skip it
    return *min_element(begin(diff) + 1, end(diff));
}
