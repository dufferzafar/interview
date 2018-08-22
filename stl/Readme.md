
# Standard Template Library


## Containers

* Sequences
    - `vector`
    - `list`
    - `deque`
    - `arrays`
    - `forward_list`

* Adaptors
    - `queue`
    - `priority_queue`
    - `stack`

* Associative
    - `set`
    - `multiset`
    - `map`
    - `multimap`


## `<algorithms>`

http://www.cplusplus.com/reference/algorithm/

* Sorting
    - `sort(beg, end)`
    - `stable_sort()`
    - `partial_sort()`
        + Partition over Pivot

* Fold
    - `accumulate(beg, end, identity_element)`
        + By default, sums numbers

    - `accumulate(beg, end, identity_element, func)`

* Map
    - `transform(i_beg, i_end, o_beg, func)`
    - `transform(i_beg, i_end, i2_beg, o_beg, func)`

* `reverse(beg, end)`

* Searching

    - `find(beg, end, elem)`
        + Returns `.end()` if not found

    - `binary_search(beg, end, needle)`

    - `count(beg, end, elem)`

    - `max_element(beg, end)`
    - `min_element(beg, end)`

    - `lower_bound()`
    - `upper_bound()`

* Permutations
    - `next_permutation`
    - `prev_permutation`

    - `lexicographical_compare`

* `vec.erase(position)`

<!-- * `vec.erase( unique(vec.begin, vec.end), vec.end() );` -->


## `<utility>`

* Pair



## Misc.

* Iterators

* Functors
    - "classes that overload the function call operator"
