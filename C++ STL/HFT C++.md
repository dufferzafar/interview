# Preparing for HFT Interviews with focus on C++

* Implement smart pointers
    * Basic
        * https://lokiastari.com/posts/Smart-Pointer-UniquePointer
        * `unique_ptr`
        * `shared_ptr`
    
    * Make them thread safe?

    * Policy based smart pointers
        * [WG Paper 2004](https://www.open-std.org/Jtc1/sc22/wg21/docs/papers/2004/n1681.pdf)
        * [axter smartptr library 2006](http://axter.com/smartptr/)
        * https://drdobbs.com/smart-pointers-reloaded/184403875

## Design Principles

* SOLID
    * Single Responsibility
    * Open/Close
    * Liskov Substitution
    * Interface Segregation
    * Dependency Inversion

## Data structures

* LRU Cache
    * LeetCode C++
        * `unordered_map` + `std::list`
            * https://godbolt.org/z/a6XTf9
            * https://liorsinai.github.io/coding/2020/11/13/lru-cache.html
    * Good to know
        * Research points to better algorithms
        * [CLOCK](https://www.codeproject.com/Articles/5314559/Multi-Level-Cache-that-Does-Up-To-A-Billion-Lookup)

* Facebook's folly
* Google's abseil

* Intel tbb

* Thread safe queue
* Lock-free
* Cache oblivious

## Networks

* Implement network server
    * TCP / UDP
    * Single threaded
    * Multi threaded
        * Using async API / coroutines?

    * Based on tower's dispatcher model!

* Kernel Bypass Networking
    * Packet mmap
    * pf_ring
        * Separate kernel module
        * [Documentation](https://www.ntop.org/guides/pf_ring/get_started/git_installation.html)

    * DPDK
    * RDMA

    * Refs
        * https://blog.cloudflare.com/kernel-bypass
        * https://blog.cloudflare.com/how-to-receive-a-million-packets
        * https://blog.cloudflare.com/how-to-achieve-low-latency

## Sanitizers

* Address
* Undefined Behavior
* Thread

## Talks

* Timur CppNow 2023
    * Part 1 - [Slides](https://github.com/boostcon/cppnow_presentations_2023/blob/main/cppnow_slides/What_Is_Low_Latency_Cpp_Part1.pdf)
    * Part 2 - [Slides](https://github.com/boostcon/cppnow_presentations_2023/blob/main/cppnow_slides/What_Is_Low_Latency_Cpp_Part2.pdf)

## Other references

* Optimizing Manuals
    * [Optimizing C++](https://www.agner.org/optimize/optimizing_cpp.pdf)
    * https://www.agner.org/optimize/#manuals
