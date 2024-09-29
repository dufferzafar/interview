#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <exception>

std::mutex mutex1, mutex2;

void ThreadA()
{
    mutex2.lock();
    throw std::runtime_error("Exception in ThreadA");
    mutex1.lock();
    mutex2.unlock();
    mutex1.unlock();
}

void ThreadB()
{
    mutex1.lock();
    throw std::runtime_error("Exception in ThreadB");
    mutex2.lock();
    mutex1.unlock();
    mutex2.unlock();
}

int main()
{
    try {
        std::thread t1( ThreadA );
        std::thread t2( ThreadB );
        t1.join();
        t2.join();
    } catch (const std::runtime_error& ex) {
        std::cout << "Caught in main: " << ex.what() << "\n";
    }
    return 0;
}
