#include <iostream>
#include <bits/stdc++.h>

//Write a function is_prime which takes as input a number 'n' < 10^15 and outputs true if it is prime and false if it not
using namespace std;

bool is_prime(long long int n) {

    if (n <= 1) return false;
    else if (n == 2 || n == 3) return true;

    else if (n % 2 == 0) return false;

    for(int i = 3; i <= sqrt(n); i += 2) {
        if(n % i == 0) return false;
    }

    return true;

}

#ifndef RunTests


int main()
{

}

#endif
