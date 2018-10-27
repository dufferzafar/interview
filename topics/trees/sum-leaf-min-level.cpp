/**
 * Microsoft: Sum of leaf nodes at minimum level.
 *
 * https://www.geeksforgeeks.org/sum-leaf-nodes-minimum-level/
 *
 * ---
 *
 * 1. Single pass - using a map<int, int> : height - sum
 *
 * 2. Two pass - find min leaf level, sum leaves at that level
 */
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};

// -----------------------------------------------------
// 1. Single pass - using a map<int, int> : height - sum
// -----------------------------------------------------

map<int, int> sum;

void leaf_sum(Node* root, int ht)
{
    if (!root) return;

    if(!root->left && !root->right)
        sum[ht] += root->data;

    leaf_sum(root->left,  ht+1);
    leaf_sum(root->right, ht+1);
}

int min_leaf_sum(Node* root)
{
    // Mistake: Wasn't clearing the map between runs
    sum.clear();

    if (!root) return 0;

    leaf_sum(root, 0);

    return (*sum.begin()).second;
}

// -----------------------------------------------------------
// 2. Two pass - find min leaf level, sum leaves at that level
// -----------------------------------------------------------

int min_leaf_level(Node* root, int ht) {
    if (!root) return INT_MAX;

    if (!root->left && !root->right)
        return ht;

    return min( min_leaf_level(root->left, ht+1),
                min_leaf_level(root->right, ht+1));
}

int sum_leaf_level(Node* root, int ht) {
    if (!root) return 0;

    if (!root->left && !root->right && !ht)
        return root->data;

    return sum_leaf_level(root->left, ht-1) +
           sum_leaf_level(root->right, ht-1);
}

int min_leaf_sum(Node* root) {
    int ht = min_leaf_level(root, 0);
    return sum_leaf_level(root, ht);
}
