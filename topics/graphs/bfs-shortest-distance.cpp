/**
 * Straightforward BFS on a graph
 *
 * https://www.hackerrank.com/challenges/ctci-bfs-shortest-reach/
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

// Is it better to store this as a matrix or as adjacency list?
class Graph {
    int nV;

    vvi adjmat;
    unordered_map< int, vi > adjlist;

    public:
        Graph(int n) {
            nV = n;

            // Initialise
            adjmat = vvi(n, vi(n, 0));

        }

        void add_edge(int u, int v) {
            // Undirected graphs have edges in both directions
            adjmat[u][v] = 1;
            adjmat[v][u] = 1;

            adjlist[u].push_back(v);
            adjlist[v].push_back(u);
        }

        vector<int> shortest_reach(int start) {

            // This is the vector we have to build
            // It also acts as the "visited" array
            vector<int> reach(nV, -1);

            // BFS
            queue< int > Q;

            // Seed the queue with our starting point
            Q.push(start); reach[start] = 0;

            // Go till all nodes reachable from start aren't reached
            while (!Q.empty()) {
                int node = Q.front(); Q.pop();

                // Skip nodes that have already been visited before
                // Mistake 3: Nodes are visited before pushing them onto the queu
                // So a check here won't work
                // if (reach[node] > 0)  continue;

                // Push all neighbors of this node onto queue
                // Mistake 4: Was iterating over neighbors via

                // for (int nxt = 0; nxt < nV; ++nxt) {
                for (auto& nxt : adjlist[node]) {

                    // If nxt has already been reached before - skip!
                    if (reach[nxt] > 0)
                        continue;

                    // Reach calculation is being done here
                    // because this is where we know about the parent-child
                    // relation between nodes.
                    reach[nxt] = reach[node] + 6;
                    Q.push(nxt);
                }

            }

            // Mistake 1: Was removing the source entry here again
            // Mistake 2: Was offsetting for 0 based indexing
            // While both of these things have been done by the calling code
            return reach;
        }

};

int main() {
    int queries;
    cin >> queries;

    for (int t = 0; t < queries; t++) {

        int n, m;
        cin >> n;
        // Create a graph of size n where each edge weight is 6:
        Graph graph(n);
        cin >> m;
        // read and set edges
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            // add each edge to the graph
            graph.add_edge(u, v);
        }
        int startId;
        cin >> startId;
        startId--;
        // Find shortest reach from node s
        vector<int> distances = graph.shortest_reach(startId);

        for (int i = 0; i < distances.size(); i++) {
            if (i != startId) {
                cout << distances[i] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
