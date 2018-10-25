/*
Given n items, each with value, count and cost.
Find the minimum cost to spend to get a total value >= S.
*/

#include<bits/stdc++.h>
using namespace std;


void knapsack(vector<int> val, vector<int> cnt, vector<int> cost, int S) {
    int n = val.size();

    int dp[5][30005];

    memset(dp, 62, sizeof(dp));

    dp[0][0] = 0;

    for (int i=0; i<n; i++) {
        for (int k=0; k<=S; k++) {
            for (int j=0; j<=cnt[i]; j++) {

                if (k+j*val[i] > S) {
                    dp[i+1][S] = min(dp[i+1][S], dp[i][k] + j*cost[i]);
                    break;
                }

                dp[i+1][k+j*val[i]] = min(dp[i+1][k+j*val[i]], dp[i][k] + j*cost[i]);

            }
        }
    }

    if (dp[n][S] > (1<<29)) {
        printf("-1\n");
    }
    else {
        printf("%d\n",dp[n][S]);
    }
}
