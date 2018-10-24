/**
 * LeetCode 214. Shortest Palindrome
 *
 * https://leetcode.com/problems/shortest-palindrome/
 *
 * ---
 *
 * In this problem, insertions can only be made at the beginning of the string.
 *
 * There is a variation in which characters can be inserted anywhere in the string
 * that requires DP!
 *
 * https://www.geeksforgeeks.org/minimum-insertions-to-form-a-palindrome-dp-28/
 */
#include <bits/stdc++.h>

using namespace std;

vector<int> LPS(string pat) {
    int m = (int) pat.length();

    // int lps[m] = {0};
    vector<int> lps(m, 0);

    for (int k = 0, q = 1; q < m; ++q) {

        while (k > 0 && pat[k] != pat[q])
            k = lps[k-1];

        if (pat[k] == pat[q])
            k++;

        lps[q] = k;
    }

    cout << "LPS: "; for (auto& l : lps) cout << l << " "; cout << endl;

    return lps;

}

string shortest_palindrome(string s) {
    int n = s.length();

    if (s.empty())
        return "";
    else if ((int) s.length() == 1)
        return s;

    string rev = s;
    reverse(begin(s), end(s));

    // Build LPS array byt appending reverse of string to the string itself
    vector<int> lps = LPS(s + "#" + rev);

    int skip = lps.back();

    // cout << "skip " << skip << endl;

    // Skip
    string e = rev.substr(0, n-skip+1);

    return e + s;
}

int main() {

    // string s = "ababaca";
    // string s = "abcddcba";

    string s = "abcabcabc";
    LPS(s);

    s = "abcabcab";
    LPS(s);

    s = "abcdefabc";
    LPS(s);

    // string s = "abcd";
    // string s = "aacecaaa";
    // cout << shortest_palindrome(s);

    // cout << endl;
}
