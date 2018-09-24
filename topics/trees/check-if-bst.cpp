/**
 * Check whether a given tree is a Binary Search Tree
 *
 * https://www.hackerrank.com/challenges/ctci-is-binary-search-tree/
 *
 * Methods:
 *
 *  1.
 *        Perform in-order traversal       O(n)
 *    and Check if output is sorted        O(n)
 *
 *  2.
 *        At every node, apply the given definition of BST    O(n*n)
 *
 *  3.
 *        Send min, max with the recrusive calls
 *
 */

#include <iostream>

#include <functional>          // less, greater

#include "binary-pointers.h"

using namespace std;


// I'm unable to cleanly explain the functionality
/**
 * @brief           Returns true if every node of root's tree
 *                  holds true for the boolean comparator
 *
 * @param  compare  A boolean comparator: std::less, std::greater
 */
template<typename Comparator, typename T>
bool every_node_is(Comparator compare, Node<T>* root, int data) {

    // Vacously true?
    if(!root) return true;

    return
            compare(root->data, data)
            & every_node_is(compare, root->left, data)
            & every_node_is(compare, root->right, data)
    ;
}

template<typename T>
bool tree_is_BST(Node<T>* root) {

    // An empty tree is a BST
    if(!root) return true;

    // Oh, OCaml, I miss you :*
    return
            every_node_is(less<int>(), root->left, root->data)
            & every_node_is(greater<int>(), root->right, root->data)
            & tree_is_BST(root->left)
            & tree_is_BST(root->right)
    ;

    // Every node is said to be distinct, so we used 'less' and not 'less_equal'
}

///////////////////////////////////////////////////////////////////////////////

/**
 * Problem: Only checks immediate children and not entire left/right subtrees
 */
template<typename T>
bool tree_is_BST_naive(Node<T>* root) {

    // An empty tree is a BST
    if(!root)
        return true;

    bool is_this_node_bst = true;

    // Look before you leap
    if (root->left)
        is_this_node_bst &= root->left->data < root->data;
    if (root->right)
        is_this_node_bst &= root->right->data > root->data;

    // Conditions are < & > because all values have to be distinct
    // otherwise they would've been <= / >=

    // Behold, the power of recursion!
    return
            is_this_node_bst
            & tree_is_BST_naive(root->left)
            & tree_is_BST_naive(root->right);
}

///////////////////////////////////////////////////////////////////////////////

/**
 * Problem: Takes the min / max value with every call
 *
 * So only requires a single pass through the tree: O(n)
 */
template<typename T>
bool tree_is_BST_improved(Node<T>* root) {

    return false;
}

///////////////////////////////////////////////////////////////////////////////

int main() {

    BinaryTree<int> t;

    // Build a tree manually
    t.root = new Node<int> {3};
    t.root->left = new Node<int> {2};
    t.root->right = new Node<int> {6};

    t.root->left->left = new Node<int> {1};
    t.root->left->right = new Node<int> {4};

    t.root->right->left = new Node<int> {5};
    t.root->right->right = new Node<int> {7};

    // Prints "Is not BST"
    cout << (tree_is_BST_naive(t.root) ? "Is BST" : "Is not BST");

    cout << endl;

    // Prints "Is BST"
    cout << (tree_is_BST(t.root) ? "Is BST" : "Is not BST");

    return 0;
}
