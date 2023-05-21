// Insipration taken from https://youtu.be/TPVH_coGAQs?list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp
// I use terms concurrent and parallel because when running threads on separate cores it should run parallely,
// but in case they are run on the same core, they will run concurrently and will not offer any performance gain (but loss)

#include <iostream>
#include <thread>
#include <chrono>

using ull = unsigned long long;

ull even_sum = 0;
ull  odd_sum = 0;

void evenSum(ull start, ull end)
{
    for (ull i{start}; i <= end; i++)
    {
        if(!(i & 1))
        {
            even_sum += i;
        }
    }
} 

void oddSum(ull start, ull end)
{
    for (ull i{start}; i <= end; i++)
    {
        if(i & 1)
        {
            odd_sum += i;
        }
    }
} 

int main()
{
    ull start = 0;
    ull end = 1900000000;

    // Running the functions sequentially
    auto start_time = std::chrono::high_resolution_clock::now();
    evenSum(start, end);
    oddSum(start, end);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_seq = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Sum of even numbers : " << even_sum << ", Sum of odd numbers: " << odd_sum << std::endl;
    std::cout << "Duration of sequential execution: " << duration_seq.count() / 1000000 << " seconds" << std::endl;  // need to convert duration into a printable integer value
    std::cout << "-------------------------------------------------------------------------------------------------\n\n";

    // Running the functions simultaneously / concurrently in separate threads
    odd_sum = 0;
    even_sum = 0;
    start_time = std::chrono::high_resolution_clock::now();
    // Create and start threads
    std::thread t1(evenSum, start, end);
    std::thread t2(oddSum, start, end);
    // Need to wait for threads to finish
    t1.join();
    t2.join();
    // Now calculate the duration and fetch the results
    end_time = std::chrono::high_resolution_clock::now();
    auto duration_conc = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Sum of even numbers : " << even_sum << ", Sum of odd numbers: " << odd_sum << std::endl;
    std::cout << "Duration of parallel / concurrent execution: " << duration_conc.count() / 1000000 << " seconds" << std::endl;  // need to convert duration into a printable integer value
    std::cout << "-------------------------------------------------------------------------------------------------\n\n";
}