/**
 * https://www.hackerrank.com/challenges/primsmstsub
 */

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;

// Graph
int N, M;
int wt[3000+1][3000+1];

vi prim(int src) {

    // Should be called "chosen" / "processed" ?
    vi visited(N+1, 0);
    visited[src] = 1;

    vi dist(N+1, INT_MAX);
    dist[src] = 0;

    set<pii> Q;
    Q.insert({dist[src], src});

    while(!Q.empty()) {

        auto node = *Q.begin();
        Q.erase(Q.begin());

        int u = node.second;
        visited[u] = 1;

        // Visit all neighbors
        for(int v = 1; v <= N; ++v) {

            if (wt[u][v] != -1) {

                // Relax u -> v edge
                if (dist[v] > wt[u][v] && !visited[v]) {

                    auto fnd = Q.find({dist[v], v});
                    if (fnd != Q.end()) Q.erase(fnd);

                    dist[v] = wt[u][v];

                    Q.insert({dist[v], v});
                }

            }

        }

    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int i, j, w;
    int s;

    // Mistake : Was using 0 as default weight
    memset(wt, -1, sizeof(wt));

    cin >> N >> M;

    while (M--) {
        cin >> i >> j >> w;

        if (wt[i][j] != -1)
            wt[i][j] = min(wt[i][j], w);
        else
            wt[i][j] = w;

        wt[j][i] = wt[i][j];
    }

    cin >> s;

    vi dist = prim(s);

    long long sum = 0;
    for(int i = 1; i <= N; ++i) {
        sum += (long long) dist[i];
    }
    cout << sum << endl;
}
