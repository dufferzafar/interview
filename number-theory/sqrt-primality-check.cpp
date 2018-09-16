#include <bits/stdc++.h>

using namespace std;

// Complete the primality function below.
string primality(int n) {
    // Base cases
    if (n == 1) return "Not prime";
    if (n == 2 || n == 3) return "Prime";

    // All multiples of 2
    if (n % 2 == 0) return "Not prime";

    // See if a number divides
    // Mistake: Equal to sqrt(n) and not less than! - Handles a number which is of form p * p?
    for(int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0)
            return "Not prime";
    }

    return "Prime";
}
