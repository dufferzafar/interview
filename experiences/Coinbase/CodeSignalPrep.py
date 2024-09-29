"""
https://leetcode.com/discuss/interview-experience/923447/coinbase-sde-bay-area-2020-reject

Location: Bay area
YOE: 5+

Round 1: Simulate a File system. Basically a trie question. You can add a file or directory. But you can't add an invalid path for /a/b/c/d.txt can not be added unless you have a, b, c as directories.

On-site
Round 1: System Design. Design Slack. Question regarding how will you mark the message read. API + storage layer (main focus), how will you push notifications. How will you show "someone is typing.." kinda feature.

Round 2: Bar raiser - Values and stuff. Explain one thing of your choice in less than 2 min or so.

Round 3: Pair programming - You are given a grid of size 6x7. Two player drop a coin from the top. They select the column (initially the selection is dumb or random) The coin will fall in the bottom most hole available in that column. The player wins if there are 4 coins of the same color in a row or column or diagonal (up or down)
Follow up: Add some intelligence in the players to select the column optimally.
How will you make the game generic so that it can check for 16 points in a row/column/diagonal
How will you handle a huge grid

Round 4: Pair Programming - You given data set in the form of list of <curr1 - curr2 - ask - bid> ask means how much curr2 do you have to spend to buy 1 unit of curr1 and bid is how much of curr2 will you get if you sell 1 unit of curr1.

Now given any two currencies x and y. Find the best conversion rate. Basically a graph problem you will have to traverse all paths from x to y because you want the best conversion rate.

follow up - Rather than hardcoding the data use two apis - 1.) https://api.pro.coinbase.com/products to get the id like USD-EUR aka currency pair and 2.) https://api.pro.coinbase.com/products/" + id + "/book to fetch the ask and bid price for each one of them. response = request.get(url) is enough to handle the GET calls + response.json() is enough to parse the response.

Result: Reject
"""


class Solution:
    chars = {
        "2": "abc",
        "3": "def",
        "4": "ghi",
        "5": "jkl",
        "6": "mno",
        "7": "pqrs",
        "8": "tuv",
        "9": "wxyz",
    }
    def letterCombinations(self, digits: str):
        if not digits:
            return []
        
        suff = self.letterCombinations(digits[1:]) or [""]
        res = []
        for d in self.chars[digits[0]]:
            for s in suff:
                res.append(d+s)
        
        return res
            

##### Q1
# Use a heap to keep track of the largest elements. Include the index in each heap element so we know when to remove them.
# We "lazily" delete elements from the heap - it'll only get removed if it surfaces to the top of the heap. This way, we always have a valid maximum.
# Time Complexity: O(N * lg(N)), Space Complexity: O(N).
# Note that it isn't O(N * lg(K)) time because the size of the heap is not capped at K due to lazy deletion.
from heapq import heappush, heappop

class Solution:
    def maxSlidingWindow(self, nums, k):
        heap = []
        ret = []
        for i,num in enumerate(nums):
            heappush(heap, (-num, i))
            while heap and heap[0][1] <= (i - k):
                heappop(heap)

            if i >= (k - 1):
                ret.append(-heap[0][0])
            
        return ret

##### Q2
# It takes O(N) time to check if a divisor is correct, and if a divisor D works, then all divisors greater than D will certainly work.
# Use binary search to find the optimal choice. Note that it is possible that there may be no divisor that works, but the problem statement guarantees that won't happen.
# Time Complexity: O(N * lg(max(nums)), Space Complexity: O(1).
from math import ceil

class Solution:
    def feasible(self, nums, threshold, divisor):
        return sum(ceil(num / divisor) for num in nums) <= threshold
        
    def smallestDivisor(self, nums, threshold):
        i, j = 1, max(nums)
        
        while i < j - 1:
            m = (i + j) // 2
            
            if self.feasible(nums, threshold, m):
                j = m
            else:
                i = m + 1
                
        return i if self.feasible(nums, threshold, i) else j


## Text Justification of Paragraphs
"""
You are formatting the text on a newspaper page. You have to align the text on the page properly. The text is provided to you in the following format:
paragraphs is an array of paragraphs, where each paragraph is represented as an array containing portions of text.
width represents the maximum number of characters each line of the newspaper page can include.
Your task is to produce a newspaper page according to the following specifications:
Start a new line for each paragraph, paragraphs[i]. Add all paragraph words paragraphs[i][j] in order. When words are together on a line, they should be separated by 1 space.
Every paragraph word paragraphs[i][j] is guaranteed to contain only lowercase and uppercase English letters.
You can't break up words. So, if adding the next word would cause you to exceed width, you will need to start a new line and add the word there.
You may end up with leftover space on a line if the size of the text that fit on the line (including separating spaces) is less than width. If this happens, align the text to the center by adding spaces around it:
If the amount of leftover space on the line is even, add an equal number of spaces before and after the text.
If the amount of leftover space on the line is odd, add an equal number of spaces before and after the text. You'll have an extra space left over; add it after the text.
Include a rectangular border of asterisks (* characters) around the top, bottom, left, and right edges of the resulting newspaper page. These characters don't count towards the width but are added for aesthetic reasons.
Return the resulting newspaper page as an array of strings. It is guaranteed that it is possible to format the paragraphs as described.
Example
For paragraphs = [["hello", "world"], ["How", "areYou", "doing"], ["Please", "look", "and", "align", "to", "the", "center"]] and width = 16, the output should be
solution(paragraphs, width) = ["*****************",
" hello world ",
"How areYou doing",
"Please look and ",
" align to the ",
" center ",
"***************"]

Let's consider all paragraphs:
paragraphs[0] = ["hello", "world"]
Both words fit on one line with a combined length of 11, including the separating space.
Since width = 16, there are 16 - 11 = 5 leftover spaces on the line. We'll need to align the text to center.
Because 5 is odd, the line should have 2 leading spaces and 3 trailing spaces.
So the result for this paragraph is the line " hello world "
paragraphs[1] = ["How", "areYou", "doing"].
All three words fit on one line with a length of 16, including separating spaces.
There are no leftover spaces, so the result is "How areYou doing".
paragraphs[2] = ["Please look", "and align", "to center"]
The words "Please", "look", "and", and "align" are too long to combine (the result would have a length of 21 > 16), so we'll start a new line with "align".
Furthermore, the words "align", "to", "the", and "center" would have a combined length of 19 > 16 which is also too long, so "center" will also be on a new line.
Per line, the amount of leftover space is 1, 4, and 10. The result of this paragraph is therefore:
"Please look and "
" align to the "
" center "

To create the border, we'll add an asterisk (* character) to the beginning and end of each line, and we'll also add a string of width + 2 asterisks before the first paragraph and after the last paragraph.
Input/Output
[execution time limit] 0.5 seconds (cpp)
[input] array.array.string paragraphs
An array of arrays of strings representing text for the newspaper page.
Guaranteed constraints:
1 ≤ paragraphs.length ≤ 20,
1 ≤ paragraphs[i].length ≤ 10,
1 ≤ paragraphs[i][j].length ≤ width.
[input] integer width
An integer representing the width of the newspaper page.
Guaranteed constraints:
5 ≤ width ≤ 50.
[output] array.string
Return the resulting newspaper page as array of strings, in which the ith string represents the ith line of the newspaper page.
"""
def format_line(line, width):
    left_over_space = width - len(line) + 1
    if left_over_space % 2 == 0:
        line = "*" + " "*(left_over_space // 2) + line[:-1] + " "*(left_over_space // 2) + "*"
    else:
        line = "*" + " "*(left_over_space // 2) + line[:-1] + " "*(left_over_space // 2 + 1) + "*"    
    return line

def align(paragraphs, width):
    lines = ["*"*width]
    for paragraph in paragraphs:
        line = ""
        curr_len = 0
        for word in paragraph:
            if curr_len + len(word) == width:
                lines.append(f"*{line}{word}*")
                line = ""
                curr_len = 0
            elif curr_len + len(word) < width:
                line += word + " "
                curr_len += len(word) + 1
            else:
                line = format_line(line, width)
                lines.append(line)
                line = word + " "
                curr_len = len(word) + 1
        lines.append(format_line(line, width))
    lines.append("*"*width)
    return lines
