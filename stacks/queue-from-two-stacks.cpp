#include <bits/stdc++.h>

using namespace std;

class MyQueue {

    stack<int> pusher, popper;

    // Goal: push into one stack, pop from the another?
    // What if popping makes it empty?

    // Move content from pusher to popper
    void rebalance() {
        while(!pusher.empty()) {
            popper.push(pusher.top());
            pusher.pop();
        }
        // Popper may still be empty (if pusher was empty)
    }

    public:
        void push(int x) {
            pusher.push(x);
        }

        void pop() {
            if (popper.empty())
                rebalance();

            popper.pop();
        }

        int front() {
            if (popper.empty())
                rebalance();

            return popper.top();
        }
};
