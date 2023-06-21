// Insipration taken from https://youtu.be/eTMY5zXits8?list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp
// If the execution time of threaded case is higher or equal, then try compling with clang++ instead of g++
// Build type : Release (without -g), -std=c++11, -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <future>

using ull = unsigned long long;

// With std::async, no need to create a promise and future. It takes care of it
ull OddSum(ull start, ull end)
{
    std::cout << "OddSum Thread ID: " << std::this_thread::get_id() << std::endl;
    ull sum{};

    for (ull i{start}; i < end; ++i)
    {
        if (i & 1)
            sum += i;
    }

    // we return as we normally would
    return sum ;
}

int main()
{
    ull start {}, end {1900000000};

    std::cout << "Main Thread ID: " << std::this_thread::get_id() << std::endl;

    // if we use std::launch::deferred, it uses the same thread (Try changing and check the thread id. It should be same in case of deferred as the main thread)
    std::future<ull> f = std::async(std::launch::async ,OddSum, start, end); 

    // waiting for or querying result with the help of future object
    ull result = f.get();

    std::cout << "Result: " << result << std::endl;

    return 0;
}