
# 53. Maximum Subarray
# https://leetcode.com/problems/maximum-subarray/description/


class Solution:
    def maxSubArray(self, nums):

        if not nums:
            return 0

        # Kadane's Algorithm

        max_including = nums[0]
        max_so_far = max_including

        for i in range(1, len(nums)):
            max_including = nums[i] + max(0, max_including)
            max_so_far = max(max_so_far, max_including)

        return max_so_far
