#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>

#include <cstdio>   // stdin redirection
#include <utility>  // pair

#include "util.h"

using namespace std;

// Some typdefs for easy coding
typedef int item;
typedef vector<item> row;
typedef vector<row> matrix;

bool undirected_cycle(matrix adj) {
    // Assume that no cycles exist
    bool cycle = false;

    // Will store the visited vertices
    vector<bool> visited(adj.size()+1, false);

    // Store predecessors of vertices
    row previous(adj.size()+1, -1);

    // Auxillary Used to process items
    stack<item> Q;

    // Visit Source
    Q.push(1);
    visited[1] = true;

    while(! Q.empty() ) {
        int u = Q.top();
        Q.pop();

        for(row::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
            item v = *it;

            if (!visited[v]) {
                visited[v] = true;
                previous[v] = u;
                Q.push(v);
            }
            else if (v != previous[u]) {
                cout << u << " ==> " << v << endl;
                cycle = true;
            }
        }
    }

    return cycle;
}

int main() {
    // Uncomment this to take input from stdin
    freopen("graph_2.txt", "r", stdin);

    // Number of vertices and edges
    int n_v, n_e;
    cin >> n_v >> n_e;

    // Adjacency matrix of the graph
    matrix adj(n_v+1);

    // This is how edges are represented in the input
    int src, dest, wt;

    // Read all the edges
    for (int i = 0; i < n_e; ++i) {
        cin >> src >> dest;
        adj[src].push_back(dest);
    }

    // This is the starting vertex
    cin >> src;

    // Print the graph's adjacency matrix
    print_graph(adj);

    if (undirected_cycle(adj))
        cout << endl << "Graph contains a Cycle.";
    else
        cout << endl << "Graph does not contains a Cycle.";

    return 0;
}
