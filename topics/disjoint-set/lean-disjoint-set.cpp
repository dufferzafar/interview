/*
A lean implementation of a Disjoint-Set datastructure.

Has both WQU & PC, resulting in O(1) amortized time per operation.

Taken from:
https://github.com/kaushal02/interview-coding-problems/blob/master/travelingIsFun.cpp
*/

#include <bits/stdc++.h>
using namespace std;
// #define int long long

struct DSU {
    vector<int> par, sz;

    DSU(int n): par(n), sz(n, 1) {
        // iota(begin(par), end(par), 0);
        for (int i = 0; i < n; i++) {
            par[i] = i;
        }
    }

    // Path Compression using recursion magic
    int Find(int a) {
        if (a == par[a]) return a;
        return par[a] = Find(par[a]);
    }

    // Weighted Quick Union
    void Union(int a, int b) {
        a = Find(a);
        b = Find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        sz[a] += sz[b];
        par[b] = a;
    }
};
