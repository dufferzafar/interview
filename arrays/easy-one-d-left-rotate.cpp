#include <bits/stdc++.h>

using namespace std;

// Complete the rotLeft function below.
vector<int> rotLeft(vector<int> a, int d) {

    // Method 1: Single line STL solution
    // rotate(begin(a), begin(a) + d, end(a)); return a;

    // Method 2: Make rotLeft1(vector) and call it d times
    // d single rotations will result in an O(n*d) algorithm
    // (essentially O(n^2) - which is bad for the given ranges)

    // Python version:
    // rotLeft = lambda (arr, d): arr[d:] + arr[:d]

    // Method 3: Using std::copy
    // Strictly linear algorithm.

    // 1 - Copy first d ints to a temporary - O(d)
    vector<int> tmp(d); // d sized vector
    std::copy(begin(a), begin(a)+d, begin(tmp));

    // 2 - Move data internally to front - O(n-d)
    std::copy(begin(a)+d, end(a), begin(a));

    // 3 - Copy back the first d ints - O(d)
    std::copy(begin(tmp), end(tmp), end(a)-d);

    // Twist:

    // What if d is negative? and we want to rotate right?
    // Step 1 would require start/end changes
    // Step 3 will be done before 2.

    return a;
}
