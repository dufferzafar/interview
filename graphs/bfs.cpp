#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>

#include <cstdio>   // stdin redirection
#include <utility>  // pair

using namespace std;

// Some typdefs for easy coding
typedef int item;
typedef vector<item> row;
typedef vector<row> matrix;

void print_graph(matrix adj) {
    for (int i = 1; i < adj.size(); ++i)
    {
        cout << i << " -> ";
        for(row::iterator it = adj[i].begin(); it != adj[i].end(); ++it)
        {
            cout << *it << " | ";
        }
        cout << endl;
    }
}

int main() {
    // Uncomment this to take input from stdin
    freopen("graph_1.txt", "r", stdin);

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
    // print_graph(adj);

    // Will store the visited vertices
    vector<bool> visited(n_v+1, false);

    // Auxillary Used to process items
    queue<item> Q; // BFS
    // stack<item> Q; // DFS

    // Visit Source
    Q.push(src);
    visited[src] = true;

    while(! Q.empty() ) {

        int u = Q.front();  // BFS
        // int u = Q.top();    // DFS

        Q.pop();

        for(row::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
            item v = *it;
            if (!visited[v]) {
                visited[v] = true;
                Q.push(v);
            }
        }

        // Visit v
        cout << u;
        if (!Q.empty())
            cout << " -> ";
    }

    return 0;
}
