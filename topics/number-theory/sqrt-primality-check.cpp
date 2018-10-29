/**
 * https://www.hackerrank.com/challenges/ctci-big-o/problem
 */
#include <bits/stdc++.h>

using namespace std;

string primality_sqrt(int n) {

    // Negative, Zero etc aren't defined to be prime
    if (n <= 1) return "Not prime";

    // Good guys
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
