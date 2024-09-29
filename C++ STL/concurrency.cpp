#include <iostream>
#include <atomic>
#include <mutex>
#include <thread>

using namespace std;

#include "benchmark/benchmark.h"

// atomic

// mutex
// timed_mutex
// recursive_mutex
// shared_mutex

// std::lock, shared_lock, unique_lock, 
// scoped_lock - uses std::lock() to lock multiple mutexes
// lock_guard - can only lock one mutex

// condition variable

void using_atomics()
{
    // Demonstrate use of atomics via multiple threads
    // int a = 0;
    atomic<int> a(0);

    auto incr = [&a] {
        for (int i = 0; i < 1000; i++)
        {
            a++;
        }
    };

    thread t1(incr);
    thread t2(incr);

    t1.join();
    t2.join();

    // The value of a should be 2000000
    // cout << "Value of a (using atomics): " << a << endl;
}

void using_mutex()
{
    // Demonstrate use of mutex via multiple threads
    int a = 0;
    mutex m;
    mutex n;

    auto incr = [&a, &m] {
        for (int i = 0; i < 1000; i++)
        {
            // lock_guard<mutex> lock(m);
            // m.lock();
            std::scoped_lock<mutex> lock(m, n);

            a++;

            // m.unlock();
        }
    };

    thread t1(incr);
    thread t2(incr);

    t1.join();
    t2.join();

    // The value of a should be 2000000
    // cout << "Value of a (using mutex): " << a << endl;
}

void using_sempaphores()
{
    // Demonstrate use of semaphores via multiple threads

}

static void BM_using_atomics(benchmark::State &state)
{
    for (auto _ : state)
    {
        using_atomics();
    }
}

static void BM_using_mutex(benchmark::State &state)
{
    for (auto _ : state)
    {
        using_mutex();
    }
}

BENCHMARK(BM_using_atomics);
BENCHMARK(BM_using_mutex);
BENCHMARK_MAIN();

// int main()
// {
//     using_atomics();
//     using_mutex();
//     return 0;
// }
