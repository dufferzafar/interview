/**
 * Standard Trie Problem: A data-structre to store and find contacts.
 *
 * https://www.hackerrank.com/challenges/contacts/
 */

#include <bits/stdc++.h>

using namespace std;

// typedef struct TrieNode TrieNode;
struct TrieNode {

    vector< TrieNode* > children;

    // At no point do we store what "character" a node represents
    // that is understood from the implicit ordering
    // 'a' is 0 and so on.

    // The number of words in Trie having this prefix
    int prefixes;

    // Signifies whether a word ends at this node or not
    bool word_end;

    // Resize children upon being constructed
    // all nodes would be nullptrs!
    TrieNode() {
        children.resize(26);
        prefixes = 0;
        word_end = false;
    }

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
            if (!cur->children[ch - 'a'])
                cur->children[ch - 'a'] = new TrieNode();

            cur = cur->children[ch - 'a'];
            cur->prefixes++;
        }
    }

    int find(string prefix) {
        TrieNode* cur = this->root;
        for (char& ch : prefix) {
            cur = cur->children[ch - 'a'];
            if (!cur) return 0;
        }
      return cur->prefixes;
    }
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

    return 0;
}
