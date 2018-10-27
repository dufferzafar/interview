/**
 * Microsoft: IIT Roorkee
 *
 * Minimum no. of characters to append to the string such that it will become palindrome.
 *
 * ---
 *
 * This is very similar to:
 * https://leetcode.com/problems/shortest-palindrome/
 *
 * Except that in that problem we had to prepend characters
 * while here we have to append.
 */

#include <bits/stdc++.h>
using namespace std;

// Mistake: was doing: #define all(x) begin(s), end(s)
// (variable on left was x while on right was s!)
#define all(x) begin(x), end(x)
typedef vector<int> vi;

vector<int> LPS(string p) {

    int n = p.length();
    vi lps(n);

    for(int k = 0, q = 1; q < n; ++q) {

        while(k > 0 && p[k] != p[q])
            k = lps[k-1];

        if (p[k] == p[q])
            k++;

        lps[q] = k;
    }

    // for (auto l : lps) cout << l << " "; cout << endl;
    return lps;
}

// Trick: String + Sentinel + Reverse
string palindrome_prepend(string s) {
    int n = s.length();
    if (n == 0 or n == 1) return s;

    // Mistake: Was writing reverse(all(s))!
    string rev(s); reverse(all(rev));

    vi L = LPS(s + "$" + rev);

    return rev.substr(0, n-L.back());
}

// Trick: Reverse + Sentinel + String
string palindrome_append(string s) {
    int n = s.length();
    if (n == 0 or n == 1) return s;

    string rev(s); reverse(all(rev));

    vi L = LPS(rev + "#" + s);

    return rev.substr(L.back());
}

bool is_palindrome(string s) {
    int n = s.length();

    for(int i = 0, j = n-1; i < j; ++i, --j) {
        if (s[i] != s[j])
            return false;
    }

    return true;
}

int main() {

    string s;

    s = "ababc";
    // for (auto l : LPS(s)) cout << l << " "; cout << endl;

    cout << "String: " << s
         << endl
         << "Prepend: " << palindrome_prepend(s)
         << endl
         << "Is Palindrome: " << is_palindrome(palindrome_prepend(s) + s)
         << endl << endl
    ;

    cout << "String: " << s
         << endl
         << "Prepend: " << palindrome_append(s)
         << endl
         << "Is Palindrome: " << is_palindrome(s + palindrome_append(s))
         << endl << endl
    ;

    return 0;
}
