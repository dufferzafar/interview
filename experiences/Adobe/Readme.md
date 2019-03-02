
# Adobe

* Profile: MTS
* Posting in: Bangalore
* CTC: 

## Online Test

Platform: HackerRank
Questions: 3
Time: 90 Minutes

**Q1**: 

Couldn't understand what the question was.

Tried to do a bunch of things. Only 3/11 test cases passed.

Fai couldn't finish this question as well, and feels that it is incorrect.

**Q2**: 

Simple graph problem, where the shortest path from node 1 to N was asked. First thought this was BFS but since edges had different weights, it later turned out to be Dijkstra.

I looked at harish's laptop, saw a function named 'dijkstra' and realised I was going the right way.

Used a set to implement Dijkstra because that is what I've done before - but maybe a `<priority_queue>` based implementaiton can be typed faster? (it most definitely would be more similar to BFS - replace a queue with a priority_queue).

Had made a few minor mistakes in the first go, but quickly fixed them and passed all cases!

**Q3**: 

It looked like a convex hull before, but since the shape was fixed to be a square - it was easier.

Quickly realised that one of the cases would be when `K = N` i.e we have to select all the watchtowers and the resulting square is easy to find.

Coded this up and passed 5/13 cases.

## Mistakes

* Should've tried to think of a bruteforce for Q3.

Maybe this didn't happen because I haven't done any question of this sort before.
