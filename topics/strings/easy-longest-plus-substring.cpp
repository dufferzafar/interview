/**
 * A string S of + and - is given.
 *
 * You have to find the length of longest substring containing only +.
 * For eg. S= --++++-+-++ here (+),(++),(+++),(++++) are the valid substrings consist of only (+).
 * But the longest substring is (++++), you have to return length i.e in this case it is 4.
 *
 */

#include <bits/stdc++.h>
using namespace std;


int longest_plus(string s) {
    int pcnt = 0, maxpcnt = 0;

    // Similar to Kadane's algorithm
    for(auto c : s) {

        if (c == '+') {
            pcnt++;
        }
        else {
            maxpcnt = max(pcnt, maxpcnt);
            pcnt = 0;
        }

    }

    return maxpcnt;
}

int main( ) {

    string s;

    s = "--++++-+-++";
    cout << s << " " << longest_plus(s) << endl;

    s = "-----------";
    cout << s << " " << longest_plus(s) << endl;

    s = "--++++--+--+++++++--";
    cout << s << " " << longest_plus(s) << endl;

    return 0;
}
