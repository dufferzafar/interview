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

    int p1 = 31, m1 = 1e9+9;
    int p2 = 53, m2 = 1e9+7;

    // Pre-compute powers of p
    int powp1[n+1]; powp1[0] = 1;
    int powp2[n+1]; powp2[0] = 1;
    for(int i = 1; i < n; ++i) {
        powp1[i] = (powp1[i-1] * p1) % m1;
        powp2[i] = (powp2[i-1] * p2) % m2;
    }

    // Store the hashes
    // unordered_set doesn't work with pair<int, int>
    set< pair<int, int> > SET;

    // Rolling hash
    for(int i = 0; i < n; ++i) {

        int h1 = 0, h2 = 0, k = 0;

        for(int j = i; j < n; ++j) {
            h1 = (h1 + ((s[j] - 'a' + 1) * powp1[k++]) % m1) % m1;
            h2 = (h2 + ((s[j] - 'a' + 1) * powp2[k++]) % m2) % m2;
            SET.insert({h1, h2});
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
