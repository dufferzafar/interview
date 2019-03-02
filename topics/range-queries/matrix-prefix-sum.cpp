/**
 * LeetCode 304. Range Sum Query 2D - Immutable
 *
 * https://leetcode.com/problems/range-sum-query-2d-immutable/
 *
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

class NumMatrix {

    vvi pre;

public:
    NumMatrix(vvi mat) {

        int r = mat.size();

        if (!r) return;

        int c = mat[0].size();

        // int pre[r][c];
        pre = vvi(r, vi(c, 0));

        cout << r << c;

        // Calculate first row & column sum
        int rsum = 0;
        for(int i = 0; i < r; ++i) {
            rsum += mat[0][i]; pre[0][i] = rsum;
        }

        int csum = 0;
        for(int i = 0; i < c; ++i) {
            csum += mat[i][0]; pre[i][0] = csum;
        }

        for(int i = 1; i < r; ++i) {
            for(int j = 1; j < c; ++j) {
                pre[i][j] = mat[i][j] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
            }
        }

        for(int i = 0; i < r; ++i) {
            for(int j = 0; j < c; ++j) {
                cout << pre[i][j];
            }
        }
    }

    int sumRegion(int r1, int c1, int r2, int c2) {

        int ans = pre[r2][c2];

        if (c1 > 0)
            ans -= pre[r2][c1-1];
        if (r1 > 0)
            ans -= pre[r1-1][c2];

        if (r1 > 0 && c1 > 0)
            ans += pre[r1-1][c1-1];

        return ans;

    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */


 class NumMatrix {
private:
    int row, col;
    vector<vector<int>> sums;
public:
    NumMatrix(vector<vector<int>> matrix) {
        row = matrix.size();
        col = row>0 ? matrix[0].size() : 0;
        sums = vector<vector<int>>(row+1, vector<int>(col+1, 0));
        for(int i=1; i<=row; i++) {
            for(int j=1; j<=col; j++) {
                sums[i][j] = matrix[i-1][j-1] +
                             sums[i-1][j] + sums[i][j-1] - sums[i-1][j-1] ;
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return sums[row2+1][col2+1] - sums[row2+1][col1] - sums[row1][col2+1] + sums[row1][col1];
    }
};
