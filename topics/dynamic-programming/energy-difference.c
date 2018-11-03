/*
 * Samsung Delhi IITD 2018
 *
 * Initially you have H amount of energy and D distance to travel. You may travel
 * with any of the given 5 speeds. But you may only travel in units of 1 km. For
 * each km distance traveled, you will spend corresponding amount of energy.
 *
 * e.g. the given speeds are:
 *
 * Cost of traveling 1 km: [4, 5, 2, 3, 6]
 * Time taken to travel 1 km: [200, 210, 230, 235, 215]
 *
 * Find minimum time required to cover total D km with remaining H >= 0
 * 1 <= H <= 4000
 * 1 <= D <= 1000
 *
 * ---
 *
 * https://github.com/kaushal02/interview-coding-problems/blob/master/energyDifference.cpp
 *
 */

#include <stdio.h>
#include <limits.h>

int N, H, D;
int energy[5];
int   time[5];

// dp[i][j] stores the minimum time required
// to travel j kms with i initial energy
int dp[4005][1005];

int min(int a, int b) {
    return a < b ? a : b;
}

int min_time() {

    for(int i = 0; i <= H; ++i) {
        for(int j = 0; j <= D; ++j) {

            // Base case: No energy or No distance
            if (i == 0 || j == 0)
                dp[i][j] = 0;

            else {
                dp[i][j] = INT_MAX;

                // Choices
                for(int k = 0; k < N; ++k) {
                    if (i >= energy[k] && dp[i-energy[k]][j-1] != INT_MAX)
                        dp[i][j] = min(dp[i][j], time[k] + dp[i-energy[k]][j-1]);
                }

            }

        }
    }

    // for(int i = 0; i <= H; ++i) {
    //     for(int j = 0; j <= D; ++j) {

    //         printf("%d ", dp[i][j]);

    //     }

    //     printf("\n");
    // }


    return dp[H][D];
}


int main() {

    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        scanf("%d", &energy[i]);
    }

    for (int i = 0; i < N; ++i) {
        scanf("%d", &time[i]);
    }

    scanf("%d", &H);
    scanf("%d", &D);

    // ----

    // printf("%d %d %d \n", N, H, D);

    // for(int i = 0; i < N; ++i) {
    //     printf("%d ", energy[i]);
    //     printf("%d ", time[i]);
    // }

    printf("%d", min_time());

    return 0;
}
