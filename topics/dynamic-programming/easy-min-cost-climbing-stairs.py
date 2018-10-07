
# 746. Min Cost Climbing Stairs
# https://leetcode.com/problems/min-cost-climbing-stairs/description/

class Solution:
    def minCostClimbingStairs(self, c):
        """
        :type cost: List[int]
        :rtype: int
        """

        # State:

        # DP[i] stores the cost of reaching i-th stair
        # so DP[i] will always include arr[i]

        # State reduction is possible - only last two values are accessed

        dp = [0] * len(c)

        # dp[0:2] = c[0:2]
        dp[0] = c[0]
        dp[1] = c[1]

        for i in range(2, len(c)):
            dp[i] = c[i] + min(dp[i-1], dp[i-2])

        # We imagine an extra step at the end that can be reached only in two ways
        # either by coming from 1 step down or from 2 steps down
        return min(dp[-1], dp[-2])
