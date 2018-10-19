/**
 * Leetcode 307. Range Sum Query - Mutable
 * https://leetcode.com/problems/range-sum-query-mutable/
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class NumArray {

    int n;
    vi arr;
    vi tree;

public:
    NumArray(vi nums) {
        arr = nums;
        n = (int) arr.size();

        if (!nums.empty()) {
            // Allocate space for a tree & then build it
            // TODO: Why does the size have to be 3x? Isn't 2x okay?
            tree = vi(4 * n, 0);
            _build(0, 0, n-1);
        }

    }

    // Is the range inclusive? Y
    // Is the tree array 1 indexed? or 0 indexed? 0
    // Do the number of elements have to be a power of 2?
    void _build(int ti, int tl, int tr) {

        if (tl == tr) {
            tree[ti] = arr[tl];
            return;
        }

        // My children
        int lc = 1 + 2*ti;
        int rc = 2 + 2*ti;

        // Inclusive range
        int m = (tl + tr) / 2;

        // Post-order traversal
        _build(lc, tl, m);
        _build(rc, m+1, tr);

        tree[ti] = tree[lc] + tree[rc];
    }

    void _update(int ti, int tl, int tr, int ai, int val) {

        // This index lies outside of my responsibility
        if (tl > ai or tr < ai)
            return;

        // Will tl & tr be equal to ai?
        if (tl == tr) {
            tree[ti] = val;
            return;
        }

        int lc = 1 + 2*ti;
        int rc = 2 + 2*ti;

        int m = (tl + tr) / 2;
        _update(lc, tl, m, ai, val);
        _update(rc, m+1, tr, ai, val);

        // Update myself based on values of my children
        tree[ti] = tree[lc] + tree[rc];
    }

    void update(int i, int val) {
        _update(0, 0, n-1, i, val);
    }

    int _sum(int ti, int tl, int tr, int al, int ar) {

        // [tl, tr] Lies totally outside range [al, ar]
        if (tl > ar or tr < al)
            return 0;

        // [tl, tr] Lies totally inside range [al, ar]
        if (tl >= al and tr <= ar)
            return tree[ti];

        int lc = 1 + 2*ti;
        int rc = 2 + 2*ti;
        int tm = (tl + tr) / 2;

        return   _sum(lc, tl  , tm, al, ar)
               + _sum(rc, tm+1, tr, al, ar);
    }

    int sumRange(int i, int j) {
        return _sum(0, 0, n-1, i, j);
    }

};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */
