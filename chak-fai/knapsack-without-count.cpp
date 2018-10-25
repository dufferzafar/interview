/*
Traditional knapsack. n items with value and cost(weight). Each item can be used once.
Find the minimum cost so that sum of value >= S
*/

#include<bits/stdc++.h>
using namespace std;

void traditional_knapsack(vector<int> val, vector<int> cost, int S) {
    int n = val.size();

    int dp[5][30005];

    memset(dp,62,sizeof(dp));
    dp[0][0] = 0;

    for (int i=0; i<n; i++) {
        for (int k=0; k<=S; k++) {
            dp[i+1][k] = dp[i][k];
            if (k+val[i] > S) {
                dp[i+1][S] = min(dp[i+1][S], dp[i][k] + cost[i]);
                break;
            }
            dp[i+1][k+val[i]] = min(dp[i+1][k+val[i]], dp[i][k] + cost[i]);
        }
    }

    if (dp[n][S] > (1<<29)) {
        printf("-1\n");
    }
    else {
        printf("%d\n",dp[n][S]);
    }
}
