// Insipration taken from https://youtu.be/UgcyOBUaR6M?list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp
// If the execution time of threaded case is higher or equal, then try compling with clang++ instead of g++
// Build type : Release (without -g), -std=c++11, -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int x {}; // Shared variable initialized to 0
std::mutex m; // Mutex needed to access critical region

void increment(int thread_no)
{
    while(true)
    {
        // Since std::mutex::try_lock() is non blocking, we can do other tasks in the meantime (printing the lock status in this case)
        // It is much like polling but without blocking other activities
        if (m.try_lock())
        {   // Start of critical section
            std::cout << "Thread " << thread_no << " acquired the lock\n"; // not want to flush the output immediately (so no std::endl)
            ++x;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            m.unlock();
            // end of critical section
            return;
        }
        else
        {
            std::cerr << "Thread " << thread_no << " is waiting for the lock\n";
            std::this_thread::sleep_for(std::chrono::seconds(1)); // We don't want to flood console with too many messages
        }
    }
}

int main()
{
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);
    t1.join();
    t2.join();
    std::cout << "Result of x: " << x << std::endl; // result of x should be 2
}