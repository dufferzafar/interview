/**
 * https://www.hackerrank.com/challenges/dijkstrashortreach
 */

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;

// Graph
int N, M;
int wt[3000+1][3000+1];

vi dijkstra(int src) {

    vi dist(N+1, INT_MAX);
    dist[src] = 0;

    set<pii> Q;
    Q.insert({dist[src], src});

    while(!Q.empty()) {

        auto node = *Q.begin();
        Q.erase(Q.begin());

        int u = node.second;

        // Visit all neighbors
        for(int v = 1; v <= N; ++v) {

            if (wt[u][v] != 0) {

                // Relax u -> v edge
                if (dist[v] > dist[u] + wt[u][v]) {

                    // Mistake 1: Was removing even if it didn't exist in set
                    // Erase from the set only it doesn't already exist
                    // Could also do: if (dist[v] != INT_MAX)
                    auto fnd = Q.find({dist[v], v});
                    if (fnd != Q.end()) Q.erase(fnd);

                    dist[v] = dist[u] + wt[u][v];

                    Q.insert({dist[v], v});
                }

            }

        }

    }

    return dist;
}

int main() {
    // Fast IO!
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T;  cin >> T;
    int i, j, w;
    int s;

    while (T--) {
        memset(wt, 0, sizeof(wt));

        cin >> N >> M;

        while (M--) {
            cin >> i >> j >> w;

            // Mistake 2 : Wasn't considering the duplicate edges between same pair of vertices
            if (wt[i][j] != 0)
                wt[i][j] = min(wt[i][j], w);
            else
                wt[i][j] = w;

            wt[j][i] = wt[i][j];
        }

        cin >> s;

        vi dist = dijkstra(s);
        for(int i = 1; i <= N; ++i) {
            if (i != s)
                cout << (dist[i] == INT_MAX ? -1 : dist[i]) << " ";
        }
        cout << endl;
    }
}
