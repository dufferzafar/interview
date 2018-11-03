/**
 * Maximum of all windows of size K of an array.
 *
 * ---
 *
 * Approaches:
 *
 * 1. <set>
 * 3. <priority_queue> - with lazy delete
 * 2. <deque>
 *
 */


#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;

vi max_window(vi& arr, int k) {

    vi res;
    int n = arr.size();

    // Stores only the indices
    deque<int> dq;

    for(int i = 0; i < n; ++i) {

        // If the deque contains something
        if (i >= k)
            res.push_back(arr[dq.front()]);

        // Remove all indices that don't fall in the window
        while(!dq.empty() && dq.front() <= i-k)
            dq.pop_front();

        // Remove all numbers smaller than arr[i]
        while(!dq.empty() && arr[dq.back()] <= arr[i])
            dq.pop_back();

        // Add this element
        dq.push_back(i);

    }

    res.push_back(arr[dq.front()]);

    return res;
}

int main() {

    int T, N, K, num;

    vi nums;

    cin >> T;
    while(T--) {

        cin >> N >> K;
        nums.clear();

        while(N--) {
            cin >> num;
            nums.push_back(num);
        }

        max_window(nums, K);

        for(auto &n : max_window(nums, K))
            cout << n << " ";
        cout << endl;
    }

    return 0;
}
