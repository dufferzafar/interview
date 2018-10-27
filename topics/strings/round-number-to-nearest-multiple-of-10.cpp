/**
 * Microsoft - IIIT Delhi
 * https://practice.geeksforgeeks.org/problems/nearest-multiple-of-10/0
 *
 * ---
 *
 * Took me longer than I expected.
 */
#include <bits/stdc++.h>
using namespace std;

string round10(string s) {

    int n = s.length();
    int l = s[n-1] - '0';

    // Last digit is <= 5
    if (l <= 5) {
        s[n-1] = '0';
        return s;
    }

    // Last digit is > 5
    else {
        s[n-1] = '0';

        // Start from right:
        // if digit is 9: change to 0 & continute
        // else: increment & stop.
        int carry = 1;
        for(int i = n-2; i >= 0; --i) {
            int d = s[i] - '0';

            if (d == 9) {
                s[i] = '0';
                continue;
            }
            else {
                s[i] = '0' + d + 1;
                carry = 0;
                // Mistake 1: Forgot break
                break;
            }
        }

        // If there's still a carry left, insert 1 at beginning of the string
        if (carry)
            s.insert(0, 1, '1');
    }

    return s;
}

int main() {

    int T;
    cin >> T;

    string s;

    while(T--) {
        cin >> s;

        cout << round10(s) << endl;
    }

    return 0;
}
