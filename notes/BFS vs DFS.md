
# BFS vs DFS

Goal: understand the fundamental difference between the two graph search algorithms.

## BFS

* Sorted in edge length?

* Queue

* **Is it possible to do this via Recursion?**

## DFS

* Explore one edge direction?

* Stack
    - Using Recursion - call stack 

    - Or manual C++ `<stack>`
        + Prefer this as it gives more control
        + And prevents against StackOverflow
    
            * Limit of Python / C++ call stack?

## Misc.

* **Visited array**:
    - To see if every node has to be processed once, twice etc
    - If once, bool array. Else int array.
