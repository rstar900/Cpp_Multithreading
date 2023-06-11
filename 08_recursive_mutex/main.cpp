// Insipration taken from https://youtu.be/yCYU2k77E4A
// If the execution time of threaded case is higher or equal, then try compling with clang++ instead of g++
// Build type : Release (without -g), -std=c++11, -pthread

#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex m;
int x{};

void recursion_demo(int n)
{
    if (n == 0)
    {
        return;
    }
    else
    {
        m.lock(); // locking multiple times by the same thread possible (without recursive mutex it will be blocked on this call)
        recursion_demo(n-1);
        std::cout << "Thread 1 : " << ++x << std::endl;
        m.unlock(); // Needs to be unlocked exactly the amount of times it is locked
    }
}

void loop_demo(int n)
{
    for (int i{1}; i <= n; ++i)
    {
        m.lock();
        std::cout  << "Thread 2 : " << x++ << std::endl;
        m.unlock();
    }
}

int main()
{
    std::thread t1(recursion_demo, 10);
    std::thread t2(loop_demo, 10);
    t1.join();
    t2.join();
}