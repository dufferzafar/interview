/**
 *
 * https://www.hackerrank.com/challenges/triple-sum/problem
 *
 Can be done in two lines of Python:

 def triplets(a, b, c):
    a, b, c = sorted(set(a)), sorted(set(b)), sorted(set(c))
    return sum([bisect(a, x) * bisect(c, x) for x in reversed(b)])
 */

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// O(n^3) bruteforce but O( nb * (log na + log nc) )
long triplets(vector<int> a, vector<int> b, vector<int> c) {

    long naq, ncq;
    long ans = 0;

    // Creating a set sorts & removes duplicates
    // Note: unordered_set won't work here - because we need sorted
    // Mistake : Did not take into account repeated numbers
    set<int> sa(begin(a), end(a));
    set<int> sb(begin(b), end(b));
    set<int> sc(begin(c), end(c));

    // Convert back to vectors
    // We need this so we can have O(1) index calculation
    // sets won't work as std::distance on sets is O(n)
    a.assign(begin(sa), end(sa));

    // a = vector<int>(begin(sa), end(sa));

    b.assign(begin(sb), end(sb));
    c.assign(begin(sc), end(sc));

    // Mistake : Read the question in a haste
    // assumed one was lower_bound, other upper_bound
    // while both have same condition on q

    for (auto& q : b) {
        // Mistake: Was using lower_bound before, which is wrong for this problem!
        auto pos = upper_bound(begin(a), end(a), q);
        naq = distance(begin(a), pos);
        // naq = pos - begin(a);

        pos = upper_bound(begin(c), end(c), q);
        ncq = distance(begin(c), pos);
        // ncq = pos - begin(c);

        ans += naq * ncq;

        // cerr << "q : " << q
        //      << " naq: " << naq
        //      << " ncq: " << ncq
        //      << " total: " << ans
        //      << endl;
    }

    return ans;
}
