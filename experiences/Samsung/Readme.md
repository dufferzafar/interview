
# Samsung

* Profile: Software Developer
* Posting in: Bangalore
* CTC: 22 LPA, Gross: 15 LPA

## Coding Round

_On: Friday, 28 September 2018_

### Platform & Setup

* Test was on a custom software that runs only on Windows
    - We also had to install Visual Studio 2017 (for C/C++)

    - The software takes complete control of your system

        + Kills all applications except 
            * Notepad
            * Calculator
            * Visual Studio (for C/C++)
            * Eclipse (for Java)

* We knew before hand that we had 3 hours to do 1 question.
    - Only 5 submissions on their test cases were allowed 

* Only C/C++/Java were allowed (no Python)
    - In these languages, only IO libraries were allowed
    - No containers
        + So, no STL vectors, maps, strings in C++
    - So we were required to implement everything by ourselves

### Test

**Duration** : 3 hours

**Question** : 

Two-coloring problem: Detect whether a graph can be painted with two colors (where adjacent vertices are painted with different colors.)

**Experience** :

This was a simple enough question that only required a traversal of the graph. We were expecting something a bit harder tbh, so I had to double check with [Harish](https://github.com/hthuwal) that this was an easy question.

Harish was sitting right beside me btw, we were both whispering to each other. How do you prevent that, Samsung!?

The biggest challenge in their test was the shitty environment. For the first 15 minutes or so, we tried to get Visual Studio running - which didn't work. So we just coded in their pathetic editor.

The other big challenge was of course, the lack of a stdlib. I was stuck for 10 minutes or so because I just couldn't figure out what I'll need to implement for this etc.

I then began coding as if I were doing it in C++ with STL and I had all the data structures. With that assumption, things started falling into place. It quickly became clear, that I only needed an adjacency matrix and stack. So I made a few big global arrays, for representing the graph, maintaining a stack etc. Rest was straight-forward DFS.

Harish finished this in an hour or so, and I got pretty anxious when he did, because I hadn't run my code even once till then. He kept sitting even after finishing just to help me out. I confirmed a few things from him and submitted my code - it showed that only 4/10 test cases passed!

They had provided a sample input file too (but no sample outputs, so you didn't know what your code _should_ produce as output!) but because Harish was still right beside me, this was easy! I just looked at his machine and noted what his output was. I quickly figured out what the issue was. Fixed it and my code started producing the same output as Harish's, so I submitted once again, and all 10 cases passed. So. Fucking. Relieved.

Even though my code worked, and all test cases passed - I absolutely hated how it _looked_. Their editor was horrible and I couldn't move around quickly so I didn't bother creating functions etc. and just kept on increasing indent levels of the code with loops inside loops - something I would never do if I had a decent editor.

**Learnings** :

* Ought to do a few questions in C
    - Just to see how things are done without STL

* If there is some boilerplate code
    - Read it, understand what it does at a high level
    - and then just fucking remove it
    - Don't try to make your code compatible with theirs
    - Just do everything from scratch!
