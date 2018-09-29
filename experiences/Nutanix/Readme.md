
# Nutanix

* Profile: Member of Technical Staff
* Posting in: Bangalore
* CTC: 39LPA, Gross: 20LPA (B.Tech), 21LPA (M.Tech)

## Coding Round

_On: Thursday 27 September 2018_

**Platform** : HackerRank. C/C++/Java/Python (& others) were allowed

**Duration** : 1 hour 30 minutes

**Questions** : [Screenshots of the questions (PDF)](https://github.com/hthuwal/iitd-placements-experience/blob/master/Nutanix/coding-exam.pdf)

1. _Didn't even read fully._

2. Construct a binary tree from its given inorder and postorder traversals, and then check what "shape" the tree takes. 

[My code for this problem](nutanix-tree-inorder-postorder-shape.cpp)

**Experience** :

I only read the first two lines of Q 1 and realised it would be hard. Q 2 on the other hand seemed straight-forward, so without thinking much, I began coding. In C++ - only because I had implemented a binary tree before in C++ and knew the recursive structure of the code.

At first, I was trying to do things the "right" way - using iterators and what not - which is obviously _not_ the fast way, so I had to ditch that approach and write code that felt hacky.

My choice of C++ did come to bite me in the ass. Since the traversals were given as strings, I required the substring function - and I had totally forgotten the API. So my 15 minutes were spent figuring out what arguments to pass to substring. HackerRank's GDB backtraces & intellisense were really helpful!

I finished up the code when there were only 5 minutes remaining, and ran it to find that all test cases passed!

I had very low hopes from this exam, and had came with the expectation that I wouldn't even be able to do any question. So I felt pretty happy to have done one.

---

When discussing this with Harish, I learned that the "trick" in this question was to not even build the tree and look for patterns in the given traversals itself. This approach was just some string processing and wouldn't really take much time to code.

**Learning** :

* Think on paper before you code!

    - If I would've thought about the problem on paper I might have seen the patterns, which would save me a lot of time!

    - The first solution that you think of may not be the best
        + If the problem doesn't seem to require much thought, then you're probably wrong.
        + THINK!

* Solve a few questions in Python as well

    - If I were doing this in Python, substring would just be slicing
        + and wouldn't have taken 15 minutes!

    - Standard stuff like Linked Lists, Graphs etc.
    - And if the platform allows Python - just use it!
        + Use C++ only if Python isn't allowed.

* Enable HackerRank's Intellisense
    - It proved useful in the test
