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

//////////////////////////////////////////////////////////////

vector<bool> sieve;
vector<int> primes;

void build_sieve(int n) {
    sieve.resize(n+1, true);
    sieve[0] = sieve[1] = false;

    for(int i = 2; i <= sqrt(n); ++i) {
        if(sieve[i]) {
            for(int j = i*i; j <= n; j += i)
                sieve[j] = false;
        }
    }

    for(int i = 2; i <= n; ++i) {
        if (sieve[i])
            primes.push_back(i);
    }
}


string primality_sieve(int n) {
    if (n == 1) return "Not prime";
    if (n == 2 || n == 3) return "Prime";

    // Build a sieve of size sqrt(n)
    build_sieve(ceil(sqrt(n)));

    for(auto p : primes)
        if (n % p == 0)
            return "Not prime";

    return "Prime";
}
