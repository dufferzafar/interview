
# Dynamic Programming

TODO: Add Anki cards for these

## Problems

* Coin Changing

    - Minimum no. of coins
    
    - Total no. of ways
        + `{1, 2}` & `{2, 1}` are same
        + Are different
    
    - Doubts
        + When will greedy work or not?
        + What if we didn't have infinite supply of coins?

* Longest Increasing Subsequence

    - Monotonically Increasing, Decreasing
    - Non Decreasing etc.

    - ? - Increasing then Decreasing - **Bitonic**

    - DP Solution in O(n^2)

    - ? - Another one in O(n log n)
    
    - Doubts
        + `LIS(s) == LCS(s, sorted(s))` ?

* Longest Common Subsequence

    - O(n^2) space and time

* Longest Palindromic Subsequence

    - O(n^2) - Like LCS
        + Can be reduced to O(1) space

    - Manacher's Algorithm
        + O(n)
        + Tricky

* Maximum Subset Sum
    
    - O(n) space & time

    - Kadane's Algorithm
        + O(n) time but O(1) space

    - Variants
        + Only consider non-adjacent elements



## Resources

* Types of DP
    - http://codeforces.com/blog/entry/325

* DP on Trees
    - https://codeforces.com/blog/entry/20935

* DP Optimizations (advanced)
    - http://codeforces.com/blog/entry/8219

* Geeks for Geeks Questions

* Topcoder Tutorials

* Bitmasks
    - https://codeforces.com/blog/entry/18169
    - http://codeforces.com/blog/entry/337
    - https://www.hackerearth.com/practice/algorithms/dynamic-programming/bit-masking/tutorial/

https://www.topcoder.com/community/competitive-programming/tutorials/assignment-problem-and-hungarian-algorithm/
