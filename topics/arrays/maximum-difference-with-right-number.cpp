/**
 * You are given an array A (distinct elements) of size N.
 *
 * Find out the maximum difference between any two elements such that larger element appears after the smaller number in A.
 *
 * ---
 *
 * https://practice.geeksforgeeks.org/problems/maximum-difference/
 */


#include <stdio.h>
#include <limits.h>

int arr[10000005];

int main() {
    int T;
    scanf("%d", &T);

    while(T--) {

        int N;
        scanf("%d", &N);

        for(int i = 0; i < N; ++i) {
            scanf("%d", &arr[i]);
        }

        int max_diff = INT_MIN;
        int max_so_far = INT_MIN;

        // Start from right and take differences with
        // max from right
        for(int i = N-1; i >= 0; --i)
        {
            if (arr[i] > max_so_far)
                max_so_far = arr[i];

            int diff = max_so_far - arr[i];

            if (diff > max_diff)
                max_diff = diff;
        }

        if (max_diff == 0)
            max_diff = -1;

        printf("%d\n", max_diff);
    }

    return 0;
}
