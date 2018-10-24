#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define piii pair<int, pair<int, int> >
#define vpi vector<pii>

#define INF INT_MAX

typedef long long lli;
typedef vector<int> vi;
typedef vector<vi> vvi;

int grid[101][101];
int dist[101][101];

int N, M, E, SR, SC, TR, TC;

int djcnt = 0;

int dijsktra(int sr, int sc, int tr, int tc) {

    set<piii> heap;
    dist[sr][sc] = 0;
    heap.insert({0, {sr, sc}});

    int d, ui, uj;


    while (!heap.empty()) {

        // Min node
        auto top = *heap.begin();
        heap.erase(heap.begin());
        djcnt++;

        // cerr << "HS: " << heap.size() << endl;

        d = top.first;
        ui = top.second.first;
        uj = top.second.second;

        // cerr << "P " << ui << " " << uj << endl;

        if (ui == tr and uj == tc)
            return d;

        vector<pii> nbrs;

        {

        int ni, nj;

        ni = ui + 1; nj = uj;
        if (ni < N && nj < M && grid[ni][nj] != -100000)
            nbrs.push_back({ni, nj});

        ni = ui - 1; nj = uj;
        if (ni >= 0 && ni < N && nj < M && grid[ni][nj] != -100000)
            nbrs.push_back({ni, nj});

        ni = ui; nj = uj + 1;
        if (ni < N && nj < M && grid[ni][nj] != -100000)
            nbrs.push_back({ni, nj});

        ni = ui; nj = uj - 1;
        if (nj >= 0 && ni < N && nj < M && grid[ni][nj] != -100000)
            nbrs.push_back({ni, nj});

        }

        for(auto& nbr : nbrs)
        {

            int ni = nbr.first;
            int nj = nbr.second;

            // cerr << "N " << ni << " " << nj << endl;

            if (dist[ni][nj] > dist[ui][uj] - grid[ni][nj])
            {

                auto fnd = heap.find({dist[ni][nj], {ni, nj}});
                if (fnd != heap.end()) heap.erase(fnd);

                dist[ni][nj] = dist[ui][uj] - grid[ni][nj];

                heap.insert({dist[ni][nj], {ni, nj}});
            }
        }

    }

    return INT_MAX;
}

int main() {

    int t = 1;
    int T; cin >> T;

    int g;

    lli shortest, ans;

    while (t <= T) {

        memset(grid, 0, sizeof(grid));
        // memset(dist, INT_MAX, sizeof(dist));

        cin >> N >> M >> E >> SR >> SC >> TR >> TC;

        SR--; SC--; TR--; TC--;

        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                cin >> g;
                grid[i][j] = g;
                dist[i][j] = INT_MAX;
            }
        }


        // for(int i = 0; i < N; ++i) {
        //     for(int j = 0; j < M; ++j) {
        //         cout << grid[i][j] << " ";
        //     }
        //     cout << endl;
        // }


        shortest = dijsktra(SR, SC, TR, TC);

        ans = -1;

        if (shortest <= E)
            ans = E-shortest;

        cout << "Case #" << t << ": "
             << ans
             << endl;

        t++;

        // cerr << "Total steps in Dijkstra: " << djcnt << " " << endl;
    }

    return 0;
}
