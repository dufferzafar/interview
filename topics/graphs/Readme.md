
# Graphs

## Implementation

* Adjacency Matrix
    - O(1) check whether their is a 

* Adjacency List (linked)

* OOP: `Vertex`, `Edge` classes
    - Pointers to objects etc.

## Algorithms


* Search
    - BFS
        + `<queue>`

    - DFS
        + `<stack>`
        + Recursive

* Shortest Paths

    - Dijkstra
        + `<priority_queue>`

    - A\*

    - Bellman Ford

    - Floyd Warshall

* Minimum Spanning Tree
    - Prim
    - Kruskal

## Notes

* Always ensure you're using the right indexing
    - Sometimes, the question will use 1-based indexing for a graph's vertices
    - So they'll say there is an edge between nodes `6 -> 14`
    - But if you're storing that in a 0-based adjacency matrix
        + You'll have to update entry `mat[5][13]`

* There've also been cases where the question says it uses 1-based indexing but 

* You can either convert the edges / vertex numbers to 0-based format
* Or change your algorithms to be 1-based

**DFS/BFS**

* There are two ways of visiting a node:
    - After popping it off
        + Simpler, but doesn't have parent-child info

    - Before pushing it on
        + Does have

* See if the graph can be implicitly represented in the input data?

    - Inputs could be Grid etc.
    - Do you need to convert it into an Adjacency List / Matrix?

<!-- Figure out from the question if you need to maintain a separate graph data structure or will the given input be enough? -->


**BFS**

* TODO: Which questions fall here?
* How to figure out if a question requires DFS or BFS

* TODO: Notes from the Topcoder Solution PDF - on BFS

**DFS**

* 



