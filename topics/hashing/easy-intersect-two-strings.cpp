#include <bits/stdc++.h>

using namespace std;

// Complete the twoStrings function below.
string twoStrings(string s1, string s2) {

    // Just have to check if the intersection is not null?
    // Python: return bool(set(s1) & set(s2))

    // Method 1: Hash s1 - loop-up s2 - O(s1+s2) time, O(s1) time

    std::unordered_set<char> s1_set(begin(s1), end(s1));

    for( auto c : s2 )
        if (s1_set.count(c))
            return "YES";

    return "NO";

    /*

    Was trying to do something like Python's version
    but this got very tricky, very fast!

    std::vector<char> s1_set(begin(s1), end(s1));
    std::vector<char> s2_set(begin(s2), end(s2));
    std::vector<char> common(100);

    sort(begin(s1_set), end(s1_set));
    sort(begin(s2_set), end(s2_set));

    std::set_intersection(begin(s1_set), end(s1_set),
                          begin(s2_set), end(s2_set),
                          begin(common));

    return (common.empty() ? "NO" : "YES");

    */
}
