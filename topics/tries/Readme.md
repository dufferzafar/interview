
# Trie

## Operations

* Insert
* Find

* Print 
    - All words in the trie are just root to leaf paths 

    - If using a sorted children repr (`map` or `vector`)
        + the words are printed in a sorted order 

* Delete
    - Simple
        + Just decrement `word_cnt` 
        + Without actually freeing nodes

    - Recursive
        + Frees up nodes while moving up?

* Compress?

## C++

The heart of the trie, is its node structure:

```cpp
struct TrieNode {
    int words_ending = 0;

    <type> children;    
};
```

There are many ways of storing the children: vector, unordered_map, map.

```cpp
vector< TrieNode* > children;
    
unordered_map< char, TrieNode* > children;
    
map< char, TrieNode* > children;
```

* `vector`
    - Requires pre-initialsation (`vector.resize(alphabet_size)`)
    - Requires indexing via `ch - 'a'`
    - Is implicitly sorted by character index
    - Wastes spaces by storing `nullptrs`
        + Especially at leaves
        + So if alphabet size is large, will waste a ton!

* `map` or `unordered_map`
    - Indexing is a bit simpler
    - Don't store `nullptrs`

    - `map` is sorted by character keys
        + while `unordered_map` is not
        + this matters when printing words in sorted order

## Python

If no extra functionality is desired, then a trie is just a `dict` of `dict` of `dict` ...

The keys of the dicts are characters while the values of dicts themselves.

If things like prefix count are required, we can build a similar node structure as in C++.

## Links

* http://www.techiedelight.com/memory-efficient-trie-implementation-using-map-insert-search-delete/
