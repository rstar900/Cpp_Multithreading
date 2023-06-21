// Insipration taken from https://youtu.be/ruYGFYTRbe8?list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp
// If the execution time of threaded case is higher or equal, then try compling with clang++ instead of g++
// Build type : Release (without -g), -std=c++11, -pthread

#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void thread1()
{
    while(1)
    {
        std::lock(m1, m2); // it tries different permutations and if not possible releases the lock
        // the below locking can cause deadlock
        //m1.lock();
        //m2.lock();
        std::cout << "Task A" << std::endl;
        m1.unlock();
        m2.unlock();
    }
}

void thread2()
{
    while(1)
    {
        std::lock(m2, m1);
        // the below locking can cause deadlock
        //m2.lock();
        //m1.lock();
        std::cout << "Task B" << std::endl;
        m2.unlock();
        m1.unlock();
    }
}

int main()
{
    std::thread t1(thread1);
    std::thread t2(thread2);
    t1.join();
    t2.join();
}