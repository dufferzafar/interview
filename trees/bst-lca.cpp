/**
 * Lowest Common Ancestor (LCA) in Binary Search Tree (BST)
 *
 * https://www.hackerrank.com/challenges/binary-search-tree-lowest-common-ancestor/
 *
 * TODO: LCA for a normal tree?
 */

Node* lca(Node *root, int v1, int v2) {
    if (!root)
        return nullptr;

    // The values go separate ways at this node
    if (
        (v1 <= root->data) && (v2 >= root->data) ||
        (v1 >= root->data) && (v2 <= root->data)
    )
            return root;

    // Check if LCA is in left subtree
    Node* left = lca(root->left, v1, v2);
    if (left) return left;

    // It has to be in the right subtree now
    Node* right = lca(root->right, v1, v2);
    return right;
}

// https://www.hackerrank.com/challenges/binary-search-tree-lowest-common-ancestor/forum/comments/73223
Node* lca_cleaner(Node* root, int v1,int v2)
{
    // Both v1, v2 lie in left subtree
    // (so LCA will be there too)
    if(v1 < root->data && v2 < root->data)
        return lca(root->left, v1, v2);

    // Both v1, v2 lie in right subtree
    if(v1 > root->data && v2 > root->data)
        return lca(root->right, v1, v2);

    // Values split at this node - LCA!
    return root;
}
