
# Strings

* Hashing
    - Rolling Hashes
        + Polynomial
            * `m = 9+1e9 or 7+1e9`
            * `p=31 or 53 or 101`
                - Depending on lowercase / uppercase alphabet
            * To reduce the probability of collision
                - Use two hashes
    
    - Applications
        + Rabin-Karp matching

    - Questions
        + Number of Distinct substrings of a string
        + Most frequent substring of length X
            * [SO Post](https://stackoverflow.com/questions/4484440/the-most-frequent-substring-of-length-x)

* Prefix function

    - Applications
        + Knuth-Morris-Pratt matching

    - Questions
        + Min. insertions at beginning to form palindrome
        + Can the string be written as (prefix)^k

## Links

* Hashing
    - [Rolling hash, Rabin Karp, palindromes, rsync and others](https://www.infoarena.ro/blog/rolling-hash)
    - [Caclulate hash of substring using prefix hashes](https://codeforces.com/blog/entry/12919)
    - [String Hashing + Binary Search Questions](https://codeforces.com/blog/entry/12388)

    - Questions
        + https://www.geeksforgeeks.org/palindrome-substring-queries/
