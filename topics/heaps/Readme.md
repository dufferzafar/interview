
# heaps

a tree with with the property that root is greater (for max-heaps) than both of its children.

has a very direct use in priority queues.

## doubts

* n-ary heap?

* other applications

* are heaps particularly suited for computing order related measures in online / streaming data?
    - TODO: Confirm this!
    - what other data structures / algorithms can be used?

## implementation

- `build_heap`
    + O(n)
        * Careful mathematical argument

- `heapify`
    + O(log n)

- `heap_sort`
    + O(log n)

## questions

* `K-th largest string`
* `Online median`
