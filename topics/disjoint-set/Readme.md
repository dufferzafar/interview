
# Disjoint Set

or Union-Find Data Structure.

## Implementation

* Parent Array
    - Used to maintain elements in a tree

* Naive
    - Quick-Find
    - Quick-Union

* Union by Rank / Union by Size

* Path Compression
    - Actually, we perform _Path Splitting_
        + Supposed to be easier
        + TODO: See exactly what Splitting does


* Time complexity
    - for m operations on a set of size n

    - Only using Weighted Union 
        + `n + m log n`

    - Only using Path Compression
        + `n + m log n`

    - Using both Weighted Union & Path Compression
        + `n + m log* n`
        + So essentially m operations are performed in O(m) time
            * O(1) amortized!

## Applications

* Kruskal's Algorithm

* Connected components of a graph

    - Build a Disjoint Set of Size V - `O(V)`
    - Perform union for each edge - `O(E)`
    - Loop over the set to find all roots - `O(V)`
        + `idx where parent[idx] == idx`

    - What is the benefit of this over DFS / BFS?
        + Don't even have to store edge information?
        + Can just process things "sonline"

## References

* Time complexity analysis of Union-Find
    - https://www.slideshare.net/WeiLi73/time-complexity-of-union-find-55858534

* Wikipedia
    - https://en.wikipedia.org/wiki/Disjoint-set_data_structure

* CLRS Chapter

* CP Algorithms
    - https://cp-algorithms.com/data_structures/disjoint_set_union.html
