/**
 *
 * Travelling salesman problem using Dynamic Porgramming with Bitmasks
 *
 * https://www.spoj.com/problems/PESADA04/
 *
 * ----
 *
 */

#include <stdio.h>
#include <limits.h>

int N;

int wt[15][15];

// Number of set bits in n
int nsb(int n) {
    int cnt = 0;
    while(n) {
        n &= n-1;
        cnt++;
    }
    return cnt;
}

// Is the ith bit set in n?
int is_set(int n, int i) {
    return (n >> i) & 1;
}

// Minimum of two numbers
int min(int a, int b) {
    return a < b ? a : b;
}

///////////////////////////////////////////////////////////


int tsp_min_cost() {

    int subsets = 1 << N;

    // dp[sub][i] stores the minimum cost
    // of starting from source - travelling through all nodes in sub
    // and ending at node i
    int dp[subsets+5][N+5];

    // Source node
    int src = 0;

    for(int sub = 0; sub < subsets; ++sub) {
        for(int node = 0; node < N; ++node) {

            // Source bit isn't even set
            // this subset doesn't even contain source
            // (not gonna consider this)
            if (!is_set(sub, src))
                dp[sub][node] = INT_MAX;

            // ONLY Source bit is set
            else if(nsb(sub) == 1)
                dp[sub][node] = 0;

            // Source & some other bits are set
            else {
                dp[sub][node] = INT_MAX;

                for(int nbr = 0; nbr < N; ++nbr) {
                    // If the subset contains node
                    // We look for a path that doesn't go through the node
                    // But ends at one of its negihbors
                    // This is the last edge of the path
                    if (nbr != node && is_set(sub, node) && is_set(sub, nbr) && dp[sub ^ (1 << node)][nbr] != INT_MAX)
                        dp[sub][node] = min(dp[sub][node], dp[sub ^ (1 << node)][nbr] + wt[nbr][node]);
                }
            }
        }
    }


    // A subset visiting all nodes - all bits 1
    int all = subsets - 1;

    int cost = INT_MAX;
    for(int node = 1; node < N; ++node) {
        cost = min(cost, dp[all][node] + wt[node][src]);
    }

    return cost;
}

int main() {

    int T;
    scanf("%d", &T);

    while(T--) {

        scanf("%d", &N);
        N++;

        // Read in the weight matrix
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if (i != j) {
                    scanf("%d", &wt[i][j]);
                } else {
                    wt[i][j] = 0;
                }
            }
        }

        // Travelling Salesman Problem
        printf("%d\n", tsp_min_cost());
    }

    return 0;
}
