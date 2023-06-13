// Insipration taken from https://youtu.be/NsqqWDQHldo?list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp
// If the execution time of threaded case is higher or equal, then try compling with clang++ instead of g++
// Build type : Release (without -g), -std=c++11, -pthread

#include <iostream>
#include <thread>
#include <mutex>

int x{};
std::mutex m;

void increment(int thread_no)
{
    // by default like a lock_guard, but can be manually unlocked (hence, used for condition variable wait())
    // by using std::defer_lock, is not automatically locked
    // can by recursively locked, time stuff like try_lock_for(), etc.
    std::unique_lock<std::mutex> lock(m, std::defer_lock);
    lock.lock();
    for (int i{}; i < 10; ++i)
    {
        std::cout << "T" << thread_no << " :" << ++x << "\n";        
    }
    // lock.unlock(); // can do but no need as by default unlock() at end of scope (but can be called earlier as well)
}

int main()
{
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);
    t1.join();
    t2.join();
}