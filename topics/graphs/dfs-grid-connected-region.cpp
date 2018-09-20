/**
 * https://www.hackerrank.com/challenges/ctci-connected-cell-in-a-grid/
 *
 * TODO: How would I do this with BFS?
 */
#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

typedef pair<int, int> pii;

// Complete the maxRegion function below.
int maxRegion(vvi& grid) {

    // Size of the grid
    int n = grid.size();
    int m = grid[0].size();

    // Will store the sizes of regions
    // Since we only need to return the size of the maximum region
    // and not where it begins, we don't store the indices!
    vi region_sizes;

    // Visited matrix
    vvi visited(n, vi(m, 0));

    // Stack used for DFS - stores cell coordinates of the grid
    stack<pii> S;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {

            // Don't start search at a 0-cell
            // or one that has already been visited
            if (!grid[i][j] || visited[i][j])
                continue;

            // A new region begins here
            int region = 0;

            S.push(make_pair(i, j));

            // DFS Begins
            while(!S.empty()) {

                // Mistake 1: Used stack::front instead of top!
                pii cell = S.top(); S.pop();
                int ci = cell.first, cj = cell.second;

                // If this cell has already been seen before, just skip?
                if (visited[ci][cj])
                    continue;

                // cerr << "Cell: " << ci << ", " << cj << endl;

                // Visit this cell
                visited[ci][cj] = true;

                // Each new cell increases the size by 1
                ++region;

                // Each cell has 8 neighboring cells
                // Push indices of those whose value is 1
                for (int ioff = -1; ioff <= 1; ++ioff)
                    for (int joff = -1; joff <= 1; ++joff) {

                        // Coordinates of the neighbor
                        int ni = ci + ioff, nj = cj + joff;

                        // Skip if either of them goes out of grid boundaries
                        if (ni < 0 || nj < 0 || ni >= n || nj >= m)
                            continue;

                        // Mistake 2: Was pushing 0 cells too
                        // Got so side-tracked with all the other conditions
                        // that I forgot the main one
                        if (!grid[ni][nj] || visited[ni][nj])
                            continue;

                        S.push(make_pair(ni, nj));
                    }
            }

            // A new region is found whenever DFS finishes
            region_sizes.push_back(region);
        }
    }

    // cerr << "Region Sizes: ";
    // for(auto& i : region_sizes) cerr << i << " ";
    // cerr << endl;

    return *max_element(region_sizes.begin(), region_sizes.end());
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> grid(n);
    for (int i = 0; i < n; i++) {
        grid[i].resize(m);

        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int res = maxRegion(grid);

    fout << res << "\n";

    fout.close();

    return 0;
}
