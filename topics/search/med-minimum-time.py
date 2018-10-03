"""
https://www.hackerrank.com/challenges/minimum-time-required

A different kind of binary search problem.
"""


import sys


def cerr(*args):
    print(*args, file=sys.stderr)


def bsearch(machines, goal, lo, hi):

    cerr(machines, goal, lo, hi)

    while lo <= hi:
        day = lo + (hi - lo) // 2
        items = sum(day // m for m in machines)

        cerr("lo:", lo, "hi:", hi, "day:", day, "items:", items)

        # Even if the answer is found, we keep going left
        # because we have to find the minimum no. of days

        if items >= goal:
            hi = day - 1
        else:
            lo = day + 1

    return lo


if __name__ == '__main__':
    n, goal = list(map(int, input().strip().split()))
    machines = list(map(int, input().strip().split()))

    # TODO: Could improve the initial lo, hi estimates
    print(bsearch(machines, goal, 1, max(machines) * goal))
