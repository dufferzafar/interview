#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int N, M;
int W[405][405];
int dp[405][405];

int main() {

    int x, y, r, q, a, b;

    cin >> N >> M;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if (i == j)
                W[i][j] = 0;
            else
                W[i][j] = INT_MAX;
        }
    }

    for(int i = 0; i < M; ++i) {
        cin >> x >> y >> r;
        W[--x][--y] = r;
    }

    //////////////////////////////////////////
    //           Floyd Warshall             //
    //////////////////////////////////////////


    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if (i == j)
                dp[i][j] = 0;
            else
                dp[i][j] = W[i][j];
        }
    }

    // The order has to be k, i, j
    // Otherwise, it'll silently fail
    for(int k = 0; k < N; ++k) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if (i != j && dp[i][k] != INT_MAX && dp[k][j] != INT_MAX)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }

    //////////////////////////////////////////

    cin >> q;
    for(int i = 0; i < q; ++i) {
        cin >> a >> b;
        --a; --b;

        if(dp[a][b] == INT_MAX)
            cout << -1;
        else
            cout << dp[a][b];

        cout << endl;
    }

    return 0;
}
