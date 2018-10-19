/**
 * Google CodeJam Kickstart Round A 2018
 *
 * Problem A: Even Digits
 *
 * https://code.google.com/codejam/contest/9234486/dashboard
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long lli;

bool is_beautiful(lli N) {
    bool is = true;

    for (; N; N /= 10) {
        is &= ((N % 10) % 2 == 0);
    }

    return is;
}

int bruteforce(lli N) {
    for(int i = 0; i <= N; ++i)
        if (is_beautiful(N-i) || is_beautiful(N+i))
            return i;

    return 0;
}

int main() {

    int t = 1;
    int T; cin >> T;

    int N;

    while (t <= T) {
        cin >> N;
        cout << "Case #" << t << ": "
             << bruteforce(N)
             << endl;
        t++;
    }

    return 0;
}
