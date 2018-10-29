/**
 * Microsoft
 *
 * Path distance between two nodes.
 *
 * https://practice.geeksforgeeks.org/problems/min-distance-between-two-given-nodes-of-a-binary-tree/1
 */

struct Node
{
    int data;
    Node* left, * right;
};

int dist(Node* root, int a) {
    if (!root)
        return -1;

    if (root->data == a)
        return 0;

    int l = dist(root->left, a);
    if (l != -1)
        return 1 + l;

    int r = dist(root->right, a);
    if (r != -1)
        return 1 + r;

    return -1;
}

int lca(Node* root, int a, int b) {
    if (!root)
        return -1;

    if (root->data == a || root->data == b)
        return root->data;

    int l = lca(root->left, a, b);
    int r = lca(root->right, a, b);

    if (l != -1 && r !=-1)
        return root->data;
    else if (l != -1)
        return l;
    else if (r != -1)
        return r;

    return -1;
}

/* Should return minimum distance between a and b in a tree with given root*/
int findDist(Node* root, int a, int b) {
    int ld = dist(root, a);
    int rd = dist(root, b);
    int LCA = lca(root, a, b);
    return ld + rd - 2 * dist(root, LCA);
}
