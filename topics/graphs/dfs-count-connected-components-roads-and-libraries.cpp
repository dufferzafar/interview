/**
 * https://www.hackerrank.com/challenges/torque-and-development/
 *
 * Use DFS to count the number of connected components
 *
 * No. of libraries = No. of connected components
 * No. roads = sum( Size of each connected component - 1 )
 *           = n - No. of components
 *
 * ----
 *
 * A better solution is by disjoint sets - to count the number of
 * connected components - that is strictly O(E) ?
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long int LLI;

// Mistake 3 (HUGE): Was not using long ints
LLI roadsAndLibraries(LLI& n, LLI& c_lib, LLI& c_road,  vector< pair<int, int> >& edges)
{
    // Best case scenario
    if (c_lib <= c_road)
        return n * c_lib;

    // Convert their cities representation to an adjacency list?
    vector< vector< int > > nbors(n+1);
    // unordered_map<int, vector<int>> nbors;

    // Mistake 2 (big) : Was only adding one of the edges
    // Whereas it's given that this is an unconnected graph
    for (auto& edge : edges) {
        nbors[edge.first].push_back(edge.second);
        nbors[edge.second].push_back(edge.first);
    }

    // Store the number of connected components in the graph
    int components = 0;

    // Standard DFS Data Structures
    stack<int> S; vector<int> visited(n+1, 0);

    // May have to start at each node
    // Mistake 1 (big) : Was using 0-based indexing for nodes
    // While the question uses 1-based
    for (int start = 1; start <= n; ++start) {

        // Don't start a DFS at an already visited node
        if (visited[start]) continue;

        // A new component begins at each DFS
        ++components;

        // DFS
        S.push(start);                               // Seed the DFS
        while(!S.empty()) {                          // Go till Stack becomes empty
            int node = S.top(); S.pop();             // Pop a node
            if (visited[node]) continue;             // Skip if already visited
            visited[node] = true;                    // Mark visited
            for(auto& n : nbors[node]) S.push(n);    // Push all neighbors
        }
    }

    LLI nlib = components, nroad = n - components;

    return nlib * c_lib + nroad * c_road;;
}

int main() {

    // Number of test cases
    int T;

    // Per test case information
    LLI n, m, c_lib, c_road;
    vector< pair<int, int> > edges;

    // Represents an edge
    int u, v;

    // T test cases
    cin >> T;
    while(T--) {

        cin >> n >> m >> c_lib >> c_road;

        edges.clear();
        while(m--) {
            cin >> u >> v;
            edges.push_back(make_pair(u, v));
        }

        cout << roadsAndLibraries(n, c_lib, c_road, edges) << endl;
    }


    return 0;
}
