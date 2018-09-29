#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

// Passing in a nullptr at the beginning
// Could be improved by passing indices
Node* build_tree(string inord, string postord)
{
    // Basecase?
    if (!inord.length())
        return nullptr;

    Node* root = new Node();
    root->data = postord.back();

    // Find location in inorder
    auto ditr = std::find(begin(inord), end(inord), root->data);
    int dloc = ditr - inord.begin();

    // Could be replaced!
    string inord_left  = inord.substr(0, dloc);
    string inord_right = inord.substr(dloc + 1);
    string postord_left = postord.substr(0, inord_left.length());
    string postord_right = postord.substr(inord_left.length(), inord_right.length());

    root->left = build_tree(inord_left, postord_left);
    root->right = build_tree(inord_right, postord_right);

    return root;
}

bool is_forward(Node* root, int& cnt) {
    Node* cur = root;

    if (!cur)
        return true;

    if (cur->right)
        return false;

    while(cur->left) {
        cur = cur->left;
        cnt++;

        if (cur->right)
            return false;
    }

    return true;
}

bool is_backward(Node* root, int& cnt) {
    Node* cur = root;

    if (!cur)
        return true;

    if (cur->left)
        return false;

    while(cur->right) {
        cur = cur->right;
        cnt++;

        if (cur->left)
            return false;
    }

    return true;
}

bool is_caret(Node* root) {

    // What if single node?

    if (!root)
        return true;

    int fwdcnt = 0, bwdcnt = 0;
    bool fwd = is_forward(root->left, fwdcnt);
    bool bwd = is_backward(root->right, bwdcnt);

    return fwd && bwd && (fwdcnt == bwdcnt);
}

bool is_less(Node* root) {
    Node* cur = root;

    if (!cur)
        return true;

    // What to do?
    if (cur->right)
        return false;

    int fwdcnt = 0, bwdcnt = 0;

    // fwdcnt++;
    while(cur->left) {
        cur = cur->left;
        fwdcnt++;

        // Found middle node!
        if (cur->right) {

            bwdcnt++; // Middle node counts in both bwd & fwd
            bool bwd = is_backward(cur->right, bwdcnt);

            return bwd && (fwdcnt == bwdcnt);

            break;
        }
    }

    return false;
}

bool is_greater(Node* root) {
    Node* cur = root;

    if (!cur)
        return true;

    // What to do?
    if (cur->left)
        return false;

    int fwdcnt = 0, bwdcnt = 0;

    // fwdcnt++;
    while(cur->right) {
        cur = cur->right;
        bwdcnt++;

        // Found middle node!
        if (cur->left) {

            fwdcnt++; // Middle node counts in both bwd & fwd
            bool fwd = is_forward(cur->left, fwdcnt);

            return fwd && (fwdcnt == bwdcnt);

            break;
        }
    }

    return false;
}


char tree_shape(Node* root) {
    int cnt = 0;
    if (is_forward(root, cnt))
        return '/';
    else if (is_backward(root, cnt))
        return '\\';
    else if (is_caret(root))
        return '^';
    else if (is_less(root))
        return '<';
    else if (is_greater(root))
        return '>';

    return '#';
}

void tree_inorder(Node* root) {
    if (!root) return;
    tree_inorder(root->left);
    cerr << root->data << "";
    tree_inorder(root->right);
}

void tree_postorder(Node* root) {
    if (!root) return;
    tree_postorder(root->left);
    tree_postorder(root->right);
    cerr << root->data << "";
}

int main() {

    string inord, postord;
    lli N;

    char shape;

    // Number of test cases: 1e7!!
    cin >> N;

    while(N--) {

        cin >> inord >> postord;

        Node* root = build_tree(inord, postord);

        // Have confirmed that the trees are being build correctly!
        // cerr << "Tree Inorder : "; tree_inorder(root); cerr << endl;
        // cerr << "Tree Postorder : "; tree_postorder(root); cerr << endl;

        shape = tree_shape(root);

        cout << shape << endl;
    }

    return 0;
}
