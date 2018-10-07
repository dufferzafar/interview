/**
 * A string is said to be a child of a another string if it can be formed
 *  by deleting 0 or more characters from the other string.
 *
 * Given two strings of equal length, what's the longest string that can be constructed
 *  such that it is a child of both?
 *
 * https://www.hackerrank.com/challenges/common-child/
 */

#include <bits/stdc++.h>

using namespace std;

// int vectors for storing the LCS
typedef vector< int > vi;
typedef vector< vi > vvi;

// Length of the Longest Common Subsequence
int commonChild(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();

    // Initialise an m+1 x n+1 matrix with 0s
    // +1 because of 0 length string - the base case of LCS
    // If either of the string has 0 lent
    vvi LCS(m+1, vi(n+1, 0));

    // TODO: Also store the solution - the string itself

    // TODO: Only store the last two rows instead of the entire matrix

    // Bottom-up for loop
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j) {

            if (s1[i-1] == s2[j-1])
                LCS[i][j] = 1 + LCS[i-1][j-1];
            else
                LCS[i][j] = max(LCS[i][j-1], LCS[i-1][j]);
        }

    return LCS[m][n];
}
