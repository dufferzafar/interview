/**
 * Google CodeJam Kickstart Round G 2018
 *
 * Problem A: Product Triplets
 */

#include <bits/stdc++.h>

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

using namespace std;

typedef long long lli;
typedef vector<int> vi;
typedef vector<vi> vvi;

int bruteforce(vi& nums) {
    lli ax, ay, az;

    int n = nums.size();
    int count = 0;

    for(int x = 0; x < n; ++x)
    {
        for(int y = x+1; y < n; ++y)
        {
            for(int z = y+1; z < n; ++z)
            {
                ax = nums[x]; ay = nums[y]; az = nums[z];


                if (ax == ay * az || ay == az * ax || az == ax * ay) {
                    cerr << " (" << ax << " " << ay << " " << az << ") ";
                    // cerr << " (" << ax << " " << ay << " " << az << ") ";
                    count++;
                }
            }
        }
    }

    return count;
}


int main() {

    int t = 1;
    int T; cin >> T;

    int N; int n;

    while (t <= T) {
        cin >> N;

        vi nums;

        while (N--) {
            cin >> n;
            nums.push_back(n);
        }

        cout << "Case #" << t << ": "
             << bruteforce(nums)
             << endl;

        t++;
    }

    return 0;
}
