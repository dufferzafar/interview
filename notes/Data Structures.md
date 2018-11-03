
# Data Structures

* **Dynamic Arrays**

    - Implement the `vector` interface 
        + Using normal arrays & pointers
        + `insert`, `delete` etc.

    - Table doubling for amortized constant time?

* **Linked Lists**

    - Singly / Doubly
    - Implement with tail pointer (& without)

    - Insertion
        + At beginning
        + At n'th position

    - Deletion
        + At n'th position

    - Reversal

* **Stack**

    - Infix, Prefix, Postfix
        + Conversion
        + Evaluation

* **Queue**

    - Using linked lists / arrays
    
    - Interface
        + `push_back`, `pop_front`

---

* **Hash Table**
    
    - Collision Resolution
        + Chaining
        + Open Addressing

    - Table doubling

    - Interface
        + `insert(k, v)`, `find(k)`, `delete(k)`

## Trees

* Construction

* Implementation

    - Using arrays
        + `2*i`, `2*i + 1`

    - Pointers (linked list)
        + `struct Node`, `struct Node* left`, `right`

* Traversal

    - BFS
        + Level Order

    - DFS
        + Pre-order
        + In-order
        + Post-order

* **Binary Search Trees**

    - Interface
        + `insert`, `find`, `delete`
        + `min`, `max`

* **Heaps**

    - Min / Max

    - Priority Queue interface

    - `build_heap`
    - `heapify`
    - `heap_sort`

* **Self-balancing Trees**

    - **Treaps**

    - **AVL Trees**

    - **Red Black Trees**

    - **B-Trees**

    - **Splay Trees**

    - **Skip Lists**


* **Segment Trees**

    - Building one from static array
    - Inserting a new item
    - Range updates
    
    - _Why is query O(log n)?_

    - [What are the differences between segment trees interval trees binary indexed tree?](https://stackoverflow.com/questions/17466218/what-are-the-differences-between-segment-trees-interval-trees-binary-indexed-t/17504505)

* **Tries**

* **Disjoint-Set, Union-Find**

## Graphs

* Implementation

    - Objects & Pointers
        + `struct Vertex`, `struct Edge`

    - Adjacency Matrix
        + When <code>e = O(v<sup>2</sup>)</code>

    - Adjacency List

    - Adjacency Map (dict)

    - Pros / Cons of each
        + Tradeoffs
        + When to use which?
        + [Skiena's Video](https://youtu.be/OiXxhDrFruw?t=3220)

* Traversal / Search
    - BFS
    - DFS
    - When to apply which?

    - DFS Based?
        + Cycle Detection
        + Topological Sorting
        + Strongly Connected Components
        + Bipartite Detection

* **Shortest Paths**
    - Dijkstra
    - Bellman Ford
    - Floyd Warshall

* **Minimum Spanning Tree**
    - Prim
    - Kruskal

* Network Flows

* Max Flow
* Min Cut

* Advanced
    - [Speeding Up Dijkstra - MIT](https://youtube.com/watch?v=CHvQ3q_gJ7E)
    - [Algorithms on Graphs - Coursera](https://www.coursera.org/learn/algorithms-on-graphs)

    - A\*
    - Bi-directional
        + Dijkstra
        + A\*

    - [Advanced Data Structures Course - MIT 2012](https://www.youtube.com/playlist?list=PLUl4u3cNGP61hsJNdULdudlRL493b-XZf)

## Others

* Policy Based Data Structures in C++
    - https://www.youtube.com/watch?v=7uvLZGkeDEg

    - https://www.geeksforgeeks.org/policy-based-data-structures-g/
    - https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/

    - https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/tutorial.html

    - Applications
        + [A faster alternative to unordered_map](https://codeforces.com/blog/entry/60737)
