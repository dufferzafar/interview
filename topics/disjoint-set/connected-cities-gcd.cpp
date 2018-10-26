/**
 * Flipkart - IIT Kanpur - 2018 - Question 3
 *
 * https://www.hackerrank.com/contests/hack-it-to-win-it-paypal/challenges/q4-traveling-is-fun/copy
 *
 * -----
 *
 * Currently, O(n^2) - Passes 6/13 cases.
 *
 * Better method: https://github.com/kaushal02/interview-coding-problems/blob/master/travelingIsFun.cpp
 */

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

struct DSU {
    vector<int> par, sz;

    DSU(int n): par(n), sz(n, 1) {
        iota(begin(par), end(par), 0);
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

// int gcd(int a, int b) { if (!b) return a; return (b, a % b); }

vi connectedCities(int n, int g, vi& org, vi& dst) {

    DSU dsu(n);

    // O(n**2) bad loop!
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            if (__gcd(i+1, j+1) > g) {
                dsu.Union(i, j);
            }
        }

    vi res;

    int q = org.size();
    for(int i = 0; i < q; ++i) {
        if (dsu.Find(--org[i]) == dsu.Find(--dst[i]))
            res.push_back(1);
        else
            res.push_back(0);
    }

    return res;
}

int main() {
    int n; cin >> n;
    int g; cin >> g;
    int originCities_cnt;
    cin >> originCities_cnt;

    vector<int> originCities(originCities_cnt);
    for(int originCities_i = 0; originCities_i < originCities_cnt; originCities_i++){
        cin >> originCities[originCities_i];
    }

    int destinationCities_cnt;
    cin >> destinationCities_cnt;
    vector<int> destinationCities(destinationCities_cnt);
    for(int destinationCities_i = 0; destinationCities_i < destinationCities_cnt; destinationCities_i++){
        cin >> destinationCities[destinationCities_i];
    }

    vector <int> res = connectedCities(n, g, originCities, destinationCities);
    for (ssize_t i = 0; i < res.size(); i++) {
        cout << res[i] << (i != res.size() - 1 ? "\n" : "");
    }
    cout << endl;


    return 0;
}
