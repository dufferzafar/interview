/**
 * https://www.hackerrank.com/challenges/sherlock-and-anagrams/
 */

#include <bits/stdc++.h>

using namespace std;

int sherlockAndAnagrams(string s) {

    // Mistake 2 (big): Was taking a set, and not keeping track of counts
    unordered_map< string, int > hash;
    int pairs = 0;

    for(int start = 0; start < s.length(); ++start) {
        // Mistake 1: Was starting len at 0 and not subtracting start from length
        for(int len = 1; len <= s.length() - start; ++len) {

            // Sorted substring
            string sub = s.substr(start, len);
            sort(begin(sub), end(sub));

            if (hash.count(sub))
                pairs += hash[sub];

            // operator[] inserts 0 if doesn't already exist
            hash[sub]++;
        }
    }

    return pairs;
}


/*
Pseudo-python:

    for substr in s:

        ss = sorted(substr)

        if ss in set:
            cnt++

        set.insert(ss)
*/
