
# LeetCode - Medium - Dynamic Programming

## 304. Range Sum Query 2D - Immutable

https://leetcode.com/problems/range-sum-query-2d-immutable/

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

```cpp
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

        // Calculate first row & column sum
        int rsum = 0;
        for(int i = 0; i < r; ++i) {
            rsum += mat[0][i]; 
            pre[0][i] = rsum;
        }
    
        int csum = 0;
        for(int i = 0; i < c; ++i) {
            csum += mat[i][0]; 
            pre[i][0] = csum;
        }
    
        for(int i = 1; i < r; ++i) {
            for(int j = 1; j < c; ++j) {
                pre[i][j] = mat[i][j] + 
                            pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
            }
        }          
    }
    
    int sumRegion(int r1, int c1, int r2, int c2) {
        return pre[r2][c2] - pre[r2][c1-1] - pre[r1-1][c2] + pre[r1-1][c1-1];
        
    }
};
```
## 279. Perfect Squares

https://leetcode.com/problems/perfect-squares/
    
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

```cpp
class Solution {
    
    bool is_square(int n) {
        // https://stackoverflow.com/questions/1549941/perfect-square-and-perfect-cube
        int a = (int) sqrt((double) n);
        return a * a == n || (a+1) * (a+1) == n;
    }
    
public:
    int numSquares(int n) {
        int dp[n+1];

        for(int i = 1; i <= n; ++i) {

            dp[i] = INT_MAX;
            
            if (is_square(i)) {
                dp[i] = 1;
                continue;
            }
            
            for(int j = 1; j <= (int) sqrt(i); ++j) {
                dp[i] = min(dp[i], dp[i-(j*j)] + 1);
            }
            
        }
        
        return dp[n];
    }
};
```

## Decode Ways

https://leetcode.com/problems/decode-ways/

A message containing letters from A-Z is being encoded to numbers using the following mapping: 'A' -> 1, 'B' -> 2 ... 'Z' -> 26. Given a non-empty string containing only digits, determine the total number of ways to decode it.

```cpp
class Solution {
public:
int numDecodings(string s) {
    
    int n = s.length();
    
    int dp[n];
    
    // Base!        
    if (s[0] == '0')
        dp[0] = 0;
    else
        dp[0] = 1;
    
    for(int i = 1; i < n; ++i) 
    {
        if(s[i] == '0') 
        {
            if(s[i-1] == '1' || s[i-1] == '2') 
            {
                if (i == 1)   
                    dp[i] = 1;
                else
                    dp[i] = dp[i-2];
            }
            else
                dp[i] = 0;
        }
        else 
        {
            if ((s[i-1] == '1') || (s[i-1] == '2' && s[i] <= '6')) 
            {
                if (i == 1)
                    dp[i] = dp[i-1] + 1;
                else
                    dp[i] = dp[i-1] + dp[i-2];
            }
            else
                dp[i] = dp[i-1];
        }
    }
    
    return dp[n-1];
}
};
```
