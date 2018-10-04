#!/bin/python3

# Question from HourRank 30
# https://www.hackerrank.com/contests/hourrank-30/challenges/video-conference

# class TrieNode: array of TrieNode*
# dict(char -> dict)

from collections import defaultdict


class Trie():

    def __init__(self):
        self.root = dict()                  # char -> dict( of chars)
        self.counts = defaultdict(int)      # name -> frequency

    def insert(self, name):

        prefix = ""

        node = self.root
        for c in name:

            if c in node:
                prefix += c
            else:
                node[c] = dict()

            node = node[c]

        return prefix


if __name__ == '__main__':

    n = int(input().strip())
    names = [input().rstrip() for _ in range(n)]

    T = Trie()

    for name in names:

        prefix = T.insert(name)
        T.counts[name] += 1

        if prefix != name:
            print(name[0:len(prefix) + 1])
        else:
            if T.counts[name] > 1:
                print(name, T.counts[name])
            else:
                print(name)
