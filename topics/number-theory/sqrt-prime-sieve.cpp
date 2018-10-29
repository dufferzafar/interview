/**
 * sqrt(N) Sieve of Eratosthenes
 *
 * TODO: Segmented Sieve to count the number of primes
 * till large n.
 */

#include <bits/stdc++.h>
using namespace std;

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
