## Assignment 2 – Code review

**What changes would you suggest in a code review?**

* Remove exceptions:
    * So that clients can decide to deal with the situation as they see fit
    * Change API from `void push()` to `bool push()`
        * returning false when a push fails rather than throwing an exception
    * We should also rename this to `tryPush` to make the best-effort nature more explicit

* Change API from `T& pop()` to `bool pop(T&)`
    * Rather than returning `mEmpty` when there is nothing to pop, we return `false`
    * When the queue actually has an item, it is copied and passed by the reference argument
        * Copy is required to fix the return-by-reference bug that currently exists!
    * Also, the consumer won't have to check against `mEmpty` if it ever needs to check whether a valid item has been popped

* Add documentation & comments
    * Begin with a description of the class & what each function tries to do
    * Clarify some of the choices being made
        * for eg. `mRingModMask` is being instead of modulus operation by `mSize`
        * to ensure correct wrap-around in the ring-buffer

**Would you check in your code like this?**

No I wouldn't, I would make the following improvements:

* Add some basicc test cases:
    * Something as simple as running a fixed number of iterations from two threads so you have a count of how many items were pushed / popped and then asserting that it is indeed the case might be a good start!

* I would also add some benchmarks for this code so we measure the performance of this mutex based approach
    * It'll help us keep track of whether any changes (like going lock-free with atomics) we make are improvements or regressions
    * We could also compare our implementation's performance with third-party queues

* Finally, I wouldn't check-in my code as a single `.cpp` file!
    * The queue is meant to be used by other client code so it should go in a separate `.h` file

**Do you think the code is clean?**

* Even though the code has bugs & makes some questionable choices (highlighted in the code-review question above) the code does feel clean to me - the functions are short & crisp.

**Do you see room for improving the performance without breaking thread safety?**

* Yes, I think we can make this work with atomic variables:
    * We should be able to use `atomic<uint64t> mReadPtr` & `atomic<uint64t> mWritePtr`
    * To support multiple producers & preventing them from writing to the same index we'll also need a `atomic<uint64t> threadWritePtr`
    * The mutex will end up being replaced by these atomics & a few compare_exchange_strong operations involved during `push`

In the latest release of the software it was discovered that the queue has a bug:
a segmentation fault occurs while trying to execute one of the tasks in the queue.

An example case has been implemented in the main function of the file that can reproduce the problem (at least on our systems, it could be dependent on how fast the tasks get executed and how the threads will be scheduled on other systems).

Please answer the following questions as clear and concise as possible:

**What steps would you take to find the bug?**

* If the application segfaults, we can run it with a debugger
    * However, debuggers are usually of limited use with concurrent code involving race conditions
    * Even though we might have a stack trace of all threads, it might not be immediately obvious why the issue is happening as there is an inherent delay associated with multi-threaded code, as the stack trace points to where the symptom showed up, not where the problem actually happened
    * In the past I've had some luck with the `rr` debugger which allows debugging to happen in reverse, so I've set data watch-points & then ran

* For this concurrent code however we should instead build & run our code with `ThreadSanitizer`
    * It's very easy to use on "simple" cases like testing a thread-safe data-structure
    * TSAN helped me point towards the various races that were happening in the code

* Another strategy that might work with version-controlled code is using `git bisect`
    * As mentioned above the bug started appearing in the latest version
    * If we are aware of some older version that works properly we can write a test script & run bisect to do a binary search on the commit space
    * This will give us the first patch that introduced the bug
    * So we might only have to review a short patch rather than the entire code!

* Finally, nothing beats a thorough manual review
    * If tests don't already exist we could start adding them as we review the code

**If you can find the bug, what fix would you suggest?**

* The bug is in the implementation of the `pop` function
    * We're returning the popped element by reference `const T&` so it may happen that by the time consumer makes use of the returned value a producer might have overriden that location

* To fix this we should instead return a copy either by `T pop()` or as mentioned above `bool pop(T&)` where a copy is made while setting the reference!
    * This should make the code work for a single producer & a single consumer

* For multiple producers, we need to look at the `push` function and realize that `busyWaitForPush` is called without the lock being held so two producers might find the same slot available and then push an element each, while one overwrites the other before it can be consumed by the consumer thread

**Write a proper test case to prove that the bug is solved (may be in pseudo code) preferably in a deterministic matter?**

* The test case might look something like:
    * Use a global `int counter`
    * Start a producer which runs a fixed number of loop iteration (like 1 Million)
    * And pushes Functor like: `[&] { counter++; }`
    * The consumer pops the Functor & runs it - thereby actually incrementing the counter
    * At the end we assert that the counter's count is the same as the loop iteration of the producer

**If you cannot find the bug, how would you go about testing the thread safety of the class? Give an example of such a test (may be in pseudo code).**

* As mentioned above, `ThreadSanitizer` is a good way of getting insight into the thread safety of a class

* Apart from that I would make the above test case mentioned run with multiple producers to create a stress scenario thereby increasing the chances of hitting the bug
    * Threads could even be increased to a number more than CPU cores
