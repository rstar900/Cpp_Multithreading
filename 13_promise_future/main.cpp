// Insipration taken from https://youtu.be/XDZkyQVsbDY?list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp
// If the execution time of threaded case is higher or equal, then try compling with clang++ instead of g++
// Build type : Release (without -g), -std=c++11, -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <future>

using ull = unsigned long long;

void OddSum(std::promise<ull>&& p, ull start, ull end)
{
    ull sum{};

    for (ull i{start}; i < end; ++i)
    {
        if (i & 1)
            sum += i;
    }

    // we only need the promise on the function side
    p.set_value(sum);
    return;
}

int main()
{
    ull start {}, end {1900000000};

    // We create a promise object
    // Which we use to get a future object
    // and move promise to function and keep the 
    // future with us. This way we can return values from thread functions

    std::promise<ull> p;
    std::future<ull> f = p.get_future(); // we only use this on calling side

    std::thread t(OddSum, std::move(p), start, end);

    // waiting for or querying result with the help of future object
    ull result = f.get();

    std::cout << "Result: " << result << std::endl;

    t.join(); // just to avoid "terminate called without an active exception" error

    return 0;
}