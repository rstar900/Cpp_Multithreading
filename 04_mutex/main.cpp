// Insipration taken from https://youtu.be/eZ8yKZo-PGw?list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp
// If the execution time of threaded case is higher or equal, then try compling with clang++ instead of g++
// Build type : Release (without -g), -std=c++11, -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

static int x {}; // Shared variable initialized to 0 (no need of static, but still just to ensure)
std::mutex m; // Mutex needed to access critical region

// try commenting m.lock() and m.unlock() statements
// It may or may not increment to 2 in that case
void increment()
{
    m.lock();   // Start of Critical Region
    ++x;        // Critical Region
    m.unlock(); // End of Critical Region
}

int main()
{

    std::cout << "Value of x before t1 and t2 started : " << x << std::endl; // should be 0

    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Value of x after t1 and t2 finished executing : " << x << std::endl; // should be 2
}