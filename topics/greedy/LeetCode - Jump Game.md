
# LeetCode - Greedy

## 55. Jump Game

Given an array of non-negative integers, you are initially positioned at the first index of the array. Each element in the array represents your maximum jump length at that position. Determine if you are able to reach the last index.

**Dynamic Programming:** 

O(N) space | O(N<sup>2</sup>) time

```cpp
class Solution {
public:
    int jump(vector<int>& nums) {

        int n = nums.size();
        
        if (!n) return 0;
        
        int dp[n];

        for(int i = 0; i < n; ++i)
            dp[i] = INT_MAX;
        
        dp[0] = 0;
        
        for(int i = 0; i < n; ++i) {
            for(int j = 1; j <= nums[i]; ++j) {
                if (i + j < n)
                    dp[i+j] = min(dp[i+j], dp[i] + 1);
            }
        }

        return dp[n-1];
    }
};
```

**Greedy:**

O(1) space | O(N) time

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) 
    {
        int n = nums.size();

        int fuel = nums[0];
        
        int reach = true;
        for(int i = 1; i < n; ++i) 
        {
            
            if (fuel) {
                fuel = max(fuel - 1, nums[i]);                
            } else {
                reach = false; 
                break;
            }     
        }
        
        return reach;
    }
};
```

## 45. Jump Game II

**Dynamic Programming:** 

O(1) space | O(N<sup>2</sup>) time - TLE!

Given an array of non-negative integers, you are initially positioned at the first index of the array. Each element in the array represents your maximum jump length at that position. Your goal is to reach the last index in the minimum number of jumps.

```cpp
class Solution {
public:
    int jump(vector<int>& nums) {

        int n = nums.size();
        
        if (!n) return 0;
        
        int dp[n];

        for(int i = 0; i < n; ++i)
            dp[i] = INT_MAX;
        
        dp[0] = 0;
        
        for(int i = 0; i < n; ++i) {
            for(int j = 1; j <= nums[i]; ++j) {
                if (i + j < n)
                    dp[i+j] = min(dp[i+j], dp[i] + 1);
            }
        }
        
        return dp[n-1];
    }
};
```

**Greedy:**

```cpp
class Solution {
public:
    int jump(vector<int>& nums) {

        int n = nums.size();
        
        int jumps = 1;
        
        int dp[n] = {0};
        dp[0] = nums[0];
        
        for(int i = 1; i < n; ++i) 
        {
            dp[i] = max(dp[i-1] - 1, nums[i]);
        }
        
        for(int i = 0; i < n; ++i) {
            if (i + dp[i] >= n-1)
                
        }
        
        return jumps;
    }
};
```
