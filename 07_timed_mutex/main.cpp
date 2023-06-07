// Insipration taken from https://youtu.be/x0sHzDyETUc?list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp
// If the execution time of threaded case is higher or equal, then try compling with clang++ instead of g++
// Build type : Release (without -g), -std=c++11, -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int x{};
std::timed_mutex m;

void increment(int thread_no)
{
    auto now = std::chrono::steady_clock::now(); // just the current time for using try_lock_until()

    //if(m.try_lock_for(std::chrono::seconds(2))) // wait for a duration
    if(m.try_lock_until(now + std::chrono::seconds(2))) // wait till exact time
    {
        std::cout << thread_no << " Acquired lock, incrementing x\n";
        ++x;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // try to make it larger or equal to 2 seconds to see that other thread times out
        m.unlock();
    }
    else
    {
        std::cout << thread_no << " Cannot acquire lock, timed out\n";
    }
}

int main()
{
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();

    std::cout << "Value of x is " << x << std::endl;
}