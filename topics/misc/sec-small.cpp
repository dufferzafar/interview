/*
    Find the second smallest number in an array.

    @kwikadi asked me this question and when I said it'll be pretty easy he made me code it,
    and sure enough, it turned out to be quite tricky and took me way more time than I had originally thought.
*/

#include <stdio.h>

// Assumes arr[] has two distinct numbers?
int second_smallest(int arr[], int len) {

    // Smallest and the second smallest numbers
    int min; int min2;

    // Assume first element is the min & the 2nd min
    // (only possible when there's a single element?)
    // (base case of the induction proof?),
    min = min2 = arr[0];

    // Let's go (in an alto?)
    for (int i = 1; i < len; ++i) {
        if (arr[i] < min) {
            min2 = min;
            min = arr[i];
        } else if (arr[i] < min2) {
            min2 = arr[i];
        } else if (min == min2 && arr[i] > min2) {
            min2 = arr[i];
        }
    }

    return min2;
}

int main() {

    int arr[5] = {2, 1, 3, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);

    printf("Second smallest: %d \n", second_smallest(arr, len));

    return 0;
}
