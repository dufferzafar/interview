# Leetcode 121. Best Time to Buy and Sell Stock
# https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

class Solution:
    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """

        if not prices:
            return 0


        mn = prices[0]
        mx = 0


        for p in prices[1:]:
            if mn < p:
                mx = max(mx, p-mn)
            mn = min(p, mn)

        return mx

