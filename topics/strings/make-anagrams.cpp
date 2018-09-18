/**
 * https://www.hackerrank.com/challenges/ctci-making-anagrams/
 *
 * Methods:
 *
 *      1. O(n^2) - Loop over both strings to find matching characters
 *
 *      2. O(n) - Hashing & Counting frequencies
 */

#include <bits/stdc++.h>

using namespace std;

// Complete the makeAnagram function below.
int makeAnagram(string a, string b) {

    // Need element by reference so it can be modified inplace
    // If character is same in both strings, then mark it as "deleted"
    for ( auto& ca : a )
        for ( auto& cb : b )
            if (ca == cb) {
                ca = cb = '-';
            }

    // Count all characters in the strings that are not '-'
    // (i.e. - which are different)
    int ans = 0;

    for( auto ca : a )
        ans += (ca == '-') ? 0 : 1;

    for( auto cb : b )
        ans += (cb == '-') ? 0 : 1;

    return ans;
}

// https://www.hackerrank.com/challenges/ctci-making-anagrams/forum/comments/190202
int number_needed(string a, string b) {
    vector<int> freq(26, 0);

    for (auto c : a)   ++freq[c - 'a'];
    for (auto c : b)   --freq[c - 'a'];

    int count = 0;
    for (auto val : freq)
        count += abs(val);

    return count;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string a;
    getline(cin, a);

    string b;
    getline(cin, b);

    int res = makeAnagram(a, b);

    fout << res << "\n";

    fout.close();

    return 0;
}
