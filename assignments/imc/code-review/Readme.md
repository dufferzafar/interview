## Assignment 2 – Code review

Included in the attached cpp file is an implementation of a concurrent queue.

The intention is to use this queue in a high performance trading system where one consumer will execute tasks submitted to the concurrent queue by multiple producers.

The assumption is that the consumer can handle events faster than that the producers can produce them, otherwise behaviour is undefined.

Please answer the following questions as clear and concise as possible:

* What changes would you suggest in a code review?

* Would you check in your code like this?

* Do you think the code is clean?

* Do you see room for improving the performance without breaking thread safety?

In the latest release of the software it was discovered that the queue has a bug:
a segmentation fault occurs while trying to execute one of the tasks in the queue.

An example case has been implemented in the main function of the file that can reproduce the problem (at least on our systems, it could be dependent on how fast the tasks get executed and how the threads will be scheduled on other systems).

Please answer the following questions as clear and concise as possible:

* What steps would you take to find the bug?

* If you can find the bug, what fix would you suggest?

* Write a proper test case to prove that the bug is solved (may be in pseudo code)
    * Preferably in a deterministic matter?

* If you cannot find the bug, how would you go about testing the thread safety of the class?
    * Give an example of such a test (may be in pseudo code).

* If you want to compile the problem please make sure to enable c++11 language features.
    * For example with clang: `clang++ -std=c++11 ConcurrentQueue.cpp -o test`
