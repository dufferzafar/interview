
# Harness

* Profile: MTS
* Posting in: Bangalore
* CTC: 

## Online Test

Platform: HackerRank
Time: 1 hr
Questions: 10 MCQs (C program output, Java etc.) + 2 Coding

**Q2**: Number of distinct substrings of a string.

Had already discussed this problem before. Knew that a straight-up bruteforce (N<sup>3</sup>) would fail. Still coded it - 5/10 cases passed. Now I had to implement a Rolling Hash, but I still skipped to the first question.

**Q1**: Mobile number keypad - No. of possible words.

Had also seen this problem before. Didn't really remember the solution, but could see that it was DP. First coded it 

Some cases passed. Realized I hadn't dealt with spaces in the string. Made a quick fix - wasn't sure if it would work - but it did :)

**Q2**: Had ~10 minutes left when I came back to the question. Implemented a rolling hash, but it was giving wrong answer on sample test cases themselves. Time was up, so couldn't really do anything.

I was just happy that I solved the first one. Probably my first real DP question in a live test.

---

After the test, we realized that the right way for Q2 wasn't rolling hashing either because N was O(10<sup>5</sup>) so even an O(N<sup>2</sup>) would fail. 

But, Fai is Fai. 

He passed all the cases by adding a simple heuristic - he assumed that a string larger than some length would never repeat. Which would make the algorithm O(N*K) (where K was 10<sup>8</sup> / N.)

---

## Mistakes

* Didn't attempt all the MCQs
    - I left them because they used Java
        + and I thought it was better to leave than attempt
    - But, there was no negative marking!

* Wasn't super confident of my DP
