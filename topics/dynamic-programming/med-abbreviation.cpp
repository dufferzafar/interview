#include <bits/stdc++.h>

using namespace std;

typedef vector< int > vi;
typedef vector< vi > vvi;

bool is_abbr(string a, string b) {

    // Similar to LCS?
    // Different starting conditions than LCS

    int m = a.length();
    int n = b.length();

    // Will only store 0 / 1 - so can be vector of bools
    // +1 because of the empty length string
    vvi dp( m+1, vi(n+1, 0));


    // Entire first column will be 1 as the two strings
    // can always be made equal if the second string is emtpy
    // (by just deleting all characters in the first string)

    // Mistake : Didn't read the question properly
    // Turns out, only lower case can be deleted
    // so the first string can be deleted only if it has ALL lower letters

    dp[0][0] = 1;  // Empty strings are equal

    for(int i = 1; i <= m; ++i)
        dp[i][0] = dp[i-1][0] && islower(a[i-1]);

    // Go over each string in increasing length
    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= n; ++j) {

            if (a[i-1] == b[j-1])
                dp[i][j] = dp[i-1][j-1];

            else if (islower(a[i-1])) {
                if(toupper(a[i-1]) == b[j-1])
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-1];
                else
                    dp[i][j] = dp[i-1][j];
            }

        }
    }

    // for(int i = 0; i <= m; ++i) {
    //     for(int j = 0; j <= n; ++j)
    //         cerr << dp[i][j] << " ";
    //     cerr << endl;
    // }

    return dp[m][n];
}


int main() {

    int q; cin >> q;

    string a, b;
    while(q--) {
        cin >> a >> b;

        if (is_abbr(a, b)) cout << "YES";
        else               cout << "NO";

        cout << endl;
    }

    return 0;
}
