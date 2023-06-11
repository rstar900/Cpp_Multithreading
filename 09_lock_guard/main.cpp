// Insipration taken from https://youtu.be/ACoYnEzjEz4
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
        std::lock_guard<std::recursive_mutex> lg(m); // lock_guard wraps the lock and unlock in the scope, so no need to call lock() and unlock()
        recursion_demo(n-1);
        std::cout << "Thread 1 : " << ++x << std::endl;
    }
}

void loop_demo(int n)
{
    for (int i{1}; i <= n; ++i)
    {
        std::lock_guard<std::recursive_mutex> lg(m);
        std::cout  << "Thread 2 : " << x++ << std::endl;
    }
}

int main()
{
    std::thread t1(recursion_demo, 10);
    std::thread t2(loop_demo, 10);
    t1.join();
    t2.join();
}