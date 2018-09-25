/**
 * https://www.hackerrank.com/challenges/find-the-nearest-clone/
 *
 * Was previously stuck on this as I was trying to do things in a single BFS.
 *
 * Harish then suggested to run multiple BFSs from different nodes
 * and keep track of minimum after each run.
 */
#include <bits/stdc++.h>

using namespace std;

typedef long long int LLI;

// Question talks about shortest paths and each edge has weight 1 - so we BFS!

// Mistake 1 (big): Question indexes nodes from 1, while I'm using 0 based !!

int findShortest(int graph_nodes,
                 vector<int>& graph_from,
                 vector<int>& graph_to,
                 vector<long>& colors,
                 long src_color)
{
    // Convert their shitty graph representation to our adjlist
    unordered_map<int, vector<int>> nbors;

    for (int i = 0; i < graph_from.size(); ++i) {
        nbors[graph_from[i]].push_back(graph_to[i]);
        nbors[graph_to[i]].push_back(graph_from[i]);
    }

    // Answer
    int shortest = INT_MAX;

    // Start from nodes of src_color
    // If there are no such nodes - there won't be any BFS
    for(int start = 0; start < graph_nodes; ++start) {

        if (colors[start] == src_color) {

            cerr << "Starting BFS from: " << start << endl;

            // At each node - store how far it is from a node of src_color
            // All nodes are at inifinite distance at starting
            // A BFS will iteratively improve this
            queue< int > Q;
            vector< int > distance(graph_nodes, INT_MAX);
            vector< int > visited(graph_nodes, 0);

            // Single source shortest path between nodes of same color?
            Q.push(start); distance[start] = 0;
            while(!Q.empty()) {
                int node = Q.front(); Q.pop();
                for(auto& nxt : nbors[node]) {
                    if (visited[nxt]) continue;
                    visited[nxt] = true;
                    distance[nxt] = 1 + distance[node];
                    Q.push(nxt);
                }
            }

            // for(auto& d : distance) cerr << d << " "; cerr << endl;

            // Find shortest distance of src_color nodes
            for(int i = 0; i < graph_nodes; ++i) {
                if (i != start && colors[i] == src_color)
                    shortest = min(shortest, distance[i]);
            }

            // Early Quitting - as soon as a value of 1 is found
            if (shortest == 1) return 1;
        }
    }

    // If there is no path, then the question demands -1
    return (shortest == INT_MAX) ? -1 : shortest;
}

int main() {

    // Mistake : Wasn't reading in n & m
    int n, m;
    cin >> n >> m;

    // Mistake : Had declared vectors that depended on n before even reading n / m
    // Edges are 1 based - need to convert
    vector<int> graph_from(m), graph_to(m);
    for(int i = 0; i < m; ++i) {
        cin >> graph_from[i] >> graph_to[i];
        --graph_from[i]; --graph_to[i];
    }

    // Colors are 0 based
    vector<long> colors(n);
    for(int i = 0; i < n; ++i) {
        cin >> colors[i];
    }

    long src_color;
    cin >> src_color;

    cout << findShortest(n, graph_from, graph_to, colors, src_color) << endl;

    return 0;
}
