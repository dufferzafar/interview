#include <bits/stdc++.h>

using namespace std;


int nCr(int n, int r) {
    int dp[n+1][r+1];

    // C(n, 0)
    for(int i = 0 ; i <= n; ++i)
        dp[i][0] = 1;

    for(int i = 1; i <= r; ++i)
        dp[0][i] = 0;

    // C(0, r)
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= r; ++j) {
            dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
        }
    }

    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= r; ++j) {

            cout << dp[i][j] << " ";

        }
        cout << endl;
    }

    return dp[n][r];
}

int main() {

    nCr(5, 5);

    return 0;
}
