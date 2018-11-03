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
    int n = pat.length();

    vector<int> lps(n, 0);

    for (int k = 0, q = 1; q < n; ++q)
    {
        while (k > 0 && pat[k] != pat[q])
            k = lps[k-1];

        if (pat[k] == pat[q])
            k++;

        lps[q] = k;
    }

    // cout << "LPS: "; for (auto& l : lps) cout << l << " "; cout << endl;

    return lps;
}

string shortestPalindrome(string s) {
    int n = s.length();

    if (s.empty())
        return "";
    else if ((int) s.length() == 1)
        return s;

    string rev(s); reverse(begin(rev), end(rev));

    // Build LPS array byt appending reverse of string to the string itself
    string trick = s + "#" + rev;
    vector<int> lps = LPS(trick);

    string e = rev.substr(0, n - lps.back());

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
