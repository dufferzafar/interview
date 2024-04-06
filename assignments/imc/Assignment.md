## General test requirements and instructions

Thank you in advance for taking the time and efforts to complete below assignments.

Once you have completed the assignments, please return your solutions in a ZIP-orRAR-file.

Your solutions will then be reviewed by our team of Engineers.

General test requirements and instructions:
• You have 72 hours to complete the test;
• Make sure we can compile and run your code;
• Please just send the code, not a Visual Studio project or something similar.

## Assignment 1 - Coding assignment

Paper-Rock-Scissors is a game for two players. Each player simultaneously opens his/her hand to display a symbol:
• Fist equals rock
• Open hand equals paper
• Showing the index and middle finger equals scissors.

The winner is determined by the following schema:
• paper beats (wraps) rock
• rock beats (blunts) scissors
• scissors beats (cuts) paper.

Write a Program that plays Paper-Scissors-Rock between the computer and a real player. You should be able to play the game n times before the program exits.

We require you to apply the following object-oriented programming paradigms to your solution:
• Good encapsulation
• Separation of concerns
• Polymorphism
• Testable design

If you are unfamiliar with the above principles, we recommend you look them up.

In addition, your program must be well-behaving (e.g., no memory leaks) and you must provide a simple unit test.

## Assignment 2 - Problem identifying assignment

Attached you will find a C++ file containing a generic class, ConcurrentQueue, and a small test for said class.

When run, the test will segfault on most systems almost immediately.
Explain exactly how this segfault happens, step by step.
Go deeper than generic terms like "you're doing X, that can cause problems", explain exactly how X causes problems in this specific scenario.

We expect an explanation of 250 words, but if you can do it in fewer words, great. Your explanation should not be more than 1000 words.

If you want to compile the problem, please make sure to enable c++11 language features.
For example, with clang: `clang++ -std=c++11 ConcurrentQueue.cpp -o test `

Good luck! And enjoy!
