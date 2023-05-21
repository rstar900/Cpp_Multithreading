// https://youtu.be/q3-5sDe6lzg?list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp
// If the execution time of threaded case is higher or equal, then try compling with clang++ instead of g++
// Build type : Release (without -g), -std=c++11, -pthread

#include <iostream>
#include <thread>
#include <chrono>

void fn(int x)
{
    for (int i{}; i < x; i++)
    {
        std::cout << "Hello: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main()
{
    std::thread t1(fn, 3); // will not run till completion, because we detach and do not wait for it to finish

    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Once detach() is called the thread object separates from thread and becomes independent of main()
    // it cannot be joined or detached again
    t1.detach();

    // detach() or join() cannot be called more than once,
    // so check if it is still joinable() before doing so
    if (t1.joinable())
        t1.detach();
}