/**
 * A binary tree built with pointers
 */

#include <iostream>
#include <string>

#include "binary-pointers.h"

using namespace std;

int main() {

    BinaryTree<int> t;

    // "4 2 6 1 3 5 7"
    // Build a tree manually
    t.root = new Node<int> {4};
    t.root->left = new Node<int> {2};
    t.root->right = new Node<int> {6};

    t.root->left->left = new Node<int> {1};
    t.root->left->right = new Node<int> {3};

    t.root->right->left = new Node<int> {5};
    t.root->right->right = new Node<int> {7};

    // In-order traversal of the tree
    cout << t;

    return 0;
}
