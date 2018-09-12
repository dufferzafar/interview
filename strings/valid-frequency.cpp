/**
 * https://www.hackerrank.com/challenges/sherlock-and-valid-string/
 *
 * Method:
 *
 * Hashing, O(n)
 */

#include <bits/stdc++.h>

using namespace std;

// Complete the isValid function below.
// BUG: Has multiple issues currently
string isValid(string s) {

    // Frequency counts of each character
    // TODO: Should be replaced with an unordered_map
    // because for characters that don't exist - this is 0
    vector<int> freq(26, 0);
    for (auto c : s ) { ++freq[ c - 'a' ]; }

    // BUG: What if first entry is 0
    int fst = freq[0];

    int faults = 0;

    for (auto i : freq) {
        if (  i
            && i != fst )
            // ^ This condition doesn't take into account the
            // difference between i & fst (which should be <= 1?)
            ++faults;
    }

    if (faults <= 1)
        return "YES";
    else
        return "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
