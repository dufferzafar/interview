
# Number Theory

* GCD
    - C++: `__gcd(a, b)`

* Primality checking
    - Simple test: `O(sqrt(n))` 
    - Fermat's Little Theorem test
        + Requires `modexp(a, b, m)`

* Sieve of Eratosthenes
    - Simple sieving
        + Till `sqrt(n)`

    - Segmented / Block sieving

## Links

* Segmented Sieve
    - https://primesieve.org/segmented_sieve.html
    - https://programmingpraxis.com/2011/10/14/the-first-n-primes/

    - https://codereview.stackexchange.com/questions/153447/segmented-sieve-of-eratosthenes
    - https://www.geeksforgeeks.org/segmented-sieve/