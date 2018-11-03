
# LeetCode - Easy - Dynamic Programming

https://leetcode.com/tag/dynamic-programming/

## 746. Min Cost Climbing Stairs

https://leetcode.com/problems/min-cost-climbing-stairs

On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to reach the top of the floor, and you can either start from the step with index 0, or the step with index 1. 

```cpp
int minCostClimbingStairs(vector<int>& cost) {
    
    int n = cost.size();
    
    // dp[i] denotes the min cost of reaching ith floor?
    int dp[n+1];
 
    dp[0] = cost[0]; dp[1] = cost[1];
    
    for(int i = 2; i < n; ++i) 
        dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
    
    
    dp[n] = min(dp[n-1], dp[n-2]);
    
    return dp[n];
}
```

## 70. Climbing Stairs

https://leetcode.com/problems/climbing-stairs

You are climbing a stair case. It takes n steps to reach to the top. Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

```cpp
int climbStairs(int n) {

    if (n == 1) return 1;
    if (n == 2) return 2;
    
    // dp[i] denotes the no. of ways of reaching i+1 the step!        
    int dp[n];
    
    dp[0] = 1;
    dp[1] = 2;
    
    for(int i = 2; i < n; ++i) 
        dp[i] = dp[i-1] + dp[i-2];
    
    return dp[n-1];
}
```

## 53. Maximum Subarray

https://leetcode.com/problems/maximum-subarray

Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

```cpp

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        
        int n = nums.size();
        
        if (!n) return 0;
        
        int dp1[n];
        int dp2[n];
  
        // Max Sum including this number
        dp1[0] = nums[0];

        // Max Sum so far
        dp2[0] = nums[0];
        
        for(int i = 1; i < n; ++i) {
            dp1[i] = nums[i] + max(0, dp1[i-1]);
            dp2[i] = max(dp1[i], dp2[i-1]);
        }
        
        return dp2[n-1];
    }
};
```

**Kadane's Algorithm:**

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        
        int n = nums.size();
        
        if (!n) return 0;
        
        int max_including_this = nums[0];
        int max_so_far = nums[0];
        
        for(int i = 1; i < n; ++i) {
            max_including_this = nums[i] + max(0, max_including_this);
            max_so_far = max(max_so_far, max_including_this);
        }
        
        return max_so_far;
    }
};
```

## 198. House Robber

https://leetcode.com/problems/house-robber

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night. Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        
        int n = nums.size();
        
        if (!n) return 0;
        if (n == 1) return nums[0];
        
        // dp[i] = max non adj sum in arr[:i]
        int dp[n];
        
        dp[0] = nums[0];
        dp[1] = max(dp[0], nums[1]);
        
        for(int i = 2; i < n; ++i) {
            dp[i] = max(nums[i] + dp[i-2], dp[i-1]);
        }
        
        return dp[n-1];
    }
};
```

## 303. Range Sum Query - Immutable

https://leetcode.com/problems/range-sum-query-immutable

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive. You may assume that the array does not change. There are many calls to sumRange function.

```cpp
class NumArray {
    // Standard prefix sums
    vector<int> pre;
    
public:
    NumArray(vector<int> nums) {
        int n = nums.size();
        
        if (!n) return; //?
        
        pre = vector<int>(n, 0);
            
        int sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += nums[i];
            pre[i] = sum;
        }
    }
    
    int sumRange(int i, int j) {
        if (i == 0) 
            return pre[j];
        else
            return pre[j] - pre[i-1]; 
    }
};
```

## 118. Pascal's Triangle

https://leetcode.com/problems/pascals-triangle/description/

Pascal's triangle via nCr.

```cpp
class Solution {
public:
    vector<vector<int>> generate(int n) {
        int dp[n+1][n+1];
        
        vector< vector<int> > ans;
        vector<int> row;

        // C(n, 0)
        for(int i = 0; i <= n; ++i)
            dp[i][0] = 1;

        // C(0, r)
        for(int i = 1; i <= n; ++i)
            dp[0][i] = 0;

        // Calculate nCr
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
            }
        }

        // Lower diagonal matrix of nCr's dp is the Pascal's Triangle
        for(int i = 0; i < n; ++i) {
            row.clear();
            
            for(int j = 0; j <= i; ++j) 
                row.push_back(dp[i][j]);
            
            ans.push_back(row);
        }

        return ans;
    }
};
```
