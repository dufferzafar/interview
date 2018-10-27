/**
 * Microsoft: IIT Roorkee
 * Maximum sum when no two elements are adjacent.
 *
 * ---
 *
 * O(n) space:  int dp[n]
 *              dp[i] = max(dp[i-1], nums[i] + dp[i-2]);
 *
 * O(1) space:  int incl = nums[0], excl = 0, excl_new;
 *              excl_new = max(incl, excl);
 *              incl = incl + nums[i];
 *              excl = excl_new;
 */
#include <bits/stdc++.h>
using namespace std;


typedef vector<int> vi;

int max_sum_linear_space(vi& nums) {
    int n = nums.size();

    if (!n) return 0;
    else if (n == 1) return nums[0];

    int dp[n];
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    for(int i = 2; i < n; ++i) {
        dp[i] = max(dp[i-1], nums[i] + dp[i-2]);
    }

    // Mistake: Was returning dp[n]
    return dp[n-1];
}

int max_sum_const_space(vi& nums) {
    int n = nums.size();

    if (!n) return 0;

    int incl = nums[0], excl = 0, excl_new = 0;

    for(int i = 1; i < n; ++i) {
        excl_new = max(incl, excl);
        incl = excl + nums[i];
        excl = excl_new;
    }

    return max(incl, excl);
}


int main() {

    int T; cin >> T;
    int n, num;

    vector<int> nbrs;

    while(T--) {

        cin >> n;
        nbrs.clear();

        while(n--) {
            cin >> num;
            nbrs.push_back(num);
        }

        // cout << max_sum_linear_space(nbrs) << endl;
        cout << max_sum_const_space(nbrs) << endl;

    }

    return 0;
}
