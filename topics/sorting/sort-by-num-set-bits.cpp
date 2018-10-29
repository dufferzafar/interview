#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)

typedef vector<int> vi;

// Calculate number of set bits in an integer
int nsb(int n) {
    int b = 0;
    while(n) {
        b += (n % 2);
        n /= 2;
    }
    return b;
}

// Global state to keep track of NSBs in an integer
unordered_map<int, int> NSB;

void precalc_nsb(vi& nums) {
    for(auto &n : nums) {
        if (NSB.count(n) == 0)
            NSB[n] = nsb(n);
    }
}

// Sort in descending order by NSB
bool set_bits_comp(int a, int b) {
    return NSB[a] > NSB[b];
}

int main() {

    int T; cin >> T;
    int N, num;

    while(T--) {
        cin >> N;
        vi nums;

        while(N--) {
            cin >> num;
            nums.push_back(num);
        }

        // Calculate NSB for all nums
        precalc_nsb(nums);

        // The question asked for a stable sort
        stable_sort(all(nums), set_bits_comp);

        for(auto &n : nums)
            cout << n << " ";

        cout << endl;
    }

    return 0;
}
