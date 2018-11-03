
# Graphs

## Representation

* Adjacency Matrix
    - O(1) check whether their is a 

* Adjacency List (linked)
    - `list`, `unordered_map` etc. in C++

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

    - A\*

    - Bellman Ford

    - Floyd Warshall

* Minimum Spanning Tree
    
    - Prim
    
    - Kruskal

## Problems

## Snippets

Representation:

```cpp
vvi adjm(n, vi(n, 0));
unordered_map< int, vi > adjl;

vi adjl[n];
```

```python
adjm = [ 0 * n for _ in range(n) ]
adjl = defaultdict(list)
```

## Notes

* Don't use adjacency matrix for DFS/BFS/Dijkstra/Prim etc.
    - Where you only need to go over each neighbor
    - Instead use an adjacency list

* Initial values of the adjacency matrix matter!
    - `0` - What if the weight itself is 0?
    - `INT_MAX` - May wraparound if you add a number to it
    - `-1` - Still needs if checks

    - Moral of the story: look at the input ranges to decide on what to use.

* Ensure that you're using the right indexing for nodes
    - Sometimes, the question will use 1-based indexing for a graph's vertices
    - So they'll say there is an edge between nodes `6 -> 14`
    - But if you're storing that in a 0-based adjacency matrix
        + You'll have to update entry `mat[5][13]`

    - There've also been cases where the question says it uses 1-based indexing but their input code was doing the 1-based to 0-based index conversion

    - You can either convert the edges / vertex numbers to 0-based format
    - Or change your algorithms to be 1-based

* Ensure that you're considering multiple edges 
    - between same pair of vertices
    - Usually only need to store the minimum weight edge etc.

* Figure out if the graph can be implicitly represented in the input data
    - Example inputs:
        + A given Grid of numbers
        + Numbers and some operations on them
            * Increment, Decrement, Double etc.

    - No need to build an explicity Adjacency List / Matrix representation

### Searching: DFS/BFS

* There are two ways of visiting a node:
    - After popping it off
        + Simpler, but doesn't have parent-child info

    - Before pushing it on
        + Does have the parent-child info
        + Which is required when doing weight updates etc.

<!-- Figure out from the question if you need to maintain a separate graph data structure or will the given input be enough? -->

**BFS**

* TODO: Which questions fall here?
* How to figure out if a question requires DFS or BFS?

* TODO: Notes from the Topcoder Solution PDF - on BFS

**DFS**

### Dijkstra

* Requires a priority queue (heap)
* Can be done in a lot of ways in C++

* Best way is to use `set` (instead of heap) as it is easier to code!
    - Ordered `set` is a Red Black BST
    - All operations are `O(log n)`

* A visited array is not required because the invariant guarantees that weights won't be updated for older nodes

### Prim

* Similar implementation as Dijkstra (using `set`)

* Two changes
    - Weight checking and update is different
    - A visited array is now required

* Why is a shortest path tree not an MST?
    - Why can't MST be found using Dijkstra?

    - Three node example
        + Hauz Khas -> Rajeev Chowk -> Noida
        + Hauz Khas -> Noida
        + Shortest path starting from HK 

    - [CS.SE](https://cs.stackexchange.com/questions/18797/minimum-spanning-tree-vs-shortest-path)
