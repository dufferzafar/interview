/**
 * A straight-forward Disjoint-Set problem
 *
 * https://www.hackerrank.com/challenges/merging-communities/
 *
 * Since we had to return sizes of each set for the question,
 * this uses Union by weight (size)
 *
 * Without weighted union, 7 test cases were passing and 3 were failing.
 * With it, all 10 passed.
 *
 * This happens because WU alone results in a complexity of O(m log n)
 * for queries - which is good enough for most cases?
 *
 * To further improve things, Path Splitting is implemented,
 * which according to Wiki (and Tarjan et. al.) is more efficient than
 * Path Compression.
 *
 * This essentially makes the structure optimal - with each operation
 * being O(1) amortized.
 */
#include <bits/stdc++.h>

using namespace std;


class DisjointSet {

    // Used to maintain a tree like structure
    vector<int> parent;

    // Size of each tree - used for weighted union
    // We could also use "rank" - the height of the trees
    vector<int> size;

    public:

    DisjointSet(int N) {
        // In the beginning each element is its own parent
        // So we have N single element trees
        // Do note that in this question element 0 is useless
        for (int i = 0; i <= N; ++i) {
            parent.push_back(i);
            size.push_back(1);
        }
    }

    // Return the root of x's tree
    int Root(int x) {
        int prev;

        // Only root is its own parent
        while(parent[x] != x) {
            // Path Splitting: Simpler than Path Compression
            // https://en.wikipedia.org/wiki/Disjoint-set_data_structure#Path_splitting
            prev = x;
            x = parent[x];
            parent[prev] = parent[x];
        }

        return parent[x];
    }

    // Find is just an alias of Root
    int Find(int x) {
        return size[Root(x)];
    }

    // Merge two trees

    // Naive Approach: Just merge the trees without any heuristic
    // Better: Weighted Union
    void Union(int u, int v) {
        // Find roots of both elements
        int pu = Root(u), pv = Root(v);

        // Mistake : Was missing this check
        // If the roots are already same, we don't have to do anything
        if (pu == pv)
            return;

        // Find which tree has more nodes
        // Could use swap to simplify this
        int smaller, bigger;
        if (size[pu] < size[pv]) {
            smaller = pu;  bigger = pv;
        } else {
            smaller = pv;  bigger = pu;
        }

        // Weighted Union: Merge smaller tree into bigger tree
        parent[smaller] = bigger;
        size[bigger] += size[smaller];
    }
};


int main() {
    int N, Q;
    cin >> N >> Q;

    char op;
    int x, u, v;

    DisjointSet DS(N);

    while(Q--) {
        cin >> op;
        if (op == 'Q') {
            cin >> x;
            cout << DS.Find(x) << endl;
        } else {
            cin >> u >> v;
            DS.Union(u, v);
        }
    }

    return 0;
}
