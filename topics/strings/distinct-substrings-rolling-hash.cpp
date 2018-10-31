/**
 * Count the number of distinct substrings of a string.
 *
 * Via straight-up bruteforce or rolling hash.
 */

#include <bits/stdc++.h>
using namespace std;


int bruteforce(string s) {
    unordered_set<string> SET;

    int n = s.length();
    for(int i = 0; i < n; ++i) {
        for(int j = 1; j <= n - i + 1; ++j) {
            SET.insert(s.substr(i, j));
        }
    }

    return SET.size();
}


int rolling_hash(string s) {

    int n = s.length();

    int p = 31, m = 1e9+7;

    // Pre-compute powers of p
    int powp[n+1]; powp[0] = 1;
    for(int i = 1; i < n; ++i) {
        powp[i] = (powp[i-1] * p) % m;
    }

    // Store the hashes
    unordered_set<int> SET;

    // Rolling hash
    for(int i = 0; i < n; ++i) {

        int h = 0, k = 0;

        for(int j = i; j < n; ++j) {
            h = (h + (s[j] * powp[k++]) % m) % m;
            SET.insert(h);
        }
    }

    return SET.size();
}


int main() {

    string str;

    cout << "Enter string: "; cin >> str; cout << endl;
    cout << "Number of distinct substrings: " << endl;
    cout << "Bruteforce: " << bruteforce(str) << endl;
    cout << "Rolling Hash: " << rolling_hash(str) << endl << endl;

    cout << "Press Ctrl+D to abort"; cin >> str;

    return 0;
}
