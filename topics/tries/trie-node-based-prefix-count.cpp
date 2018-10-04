/**
 * Standard Trie Problem: A data-structre to store and find contacts.
 *
 * https://www.hackerrank.com/challenges/contacts/
 */

#include <bits/stdc++.h>

using namespace std;

// typedef struct TrieNode TrieNode;
struct TrieNode {
    map< char, TrieNode* > children;
    int prefix_cnt = 0;
    bool wordend = false;
};

class Trie {

    TrieNode* root;

public:

    Trie() {
        root = new TrieNode();
    }

    // Walk down the tree, creating new nodes as you go
    void add(string word) {
        TrieNode* cur = this->root;
        for (char& ch : word) {
            if (!cur->children[ch])
                cur->children[ch] = new TrieNode();

            cur = cur->children[ch];
            cur->prefix_cnt++;
        }
        cur->wordend = true;
    }

    int find(string prefix) {
        TrieNode* cur = this->root;
        for (char& ch : prefix) {
            cur = cur->children[ch - 'a'];
            if (!cur) return 0;
        }
      return cur->prefix_cnt;
    }

    // Print the entire tree
    void _print(TrieNode* root, string word) {
        if (!root->children.size() || root->wordend)
            cerr << word << endl;
        for (auto& child : root->children)
            _print(child.second, word + child.first);
    }

    void print() { _print(this->root, ""); }
};

int main() {

    // Alphabet is a-z, so size 26 array at each node
    // A trie of depth 21, and fanout 26
    Trie T;

    int n;  string op, arg;
    cin >> n;

    // This is required because we're mixing cin & getline
    // ptr was still on the 1st line, so we come to 2nd line
    // by ignoring character till \n
    cin.ignore(1, '\n');

    while(n--) {

        getline(cin, op, ' ');
        getline(cin, arg);

        if (op == "add")
            T.add(arg);
        else
            cout << T.find(arg) << endl;

    }

    T.print();

    return 0;
}
