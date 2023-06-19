// Insipration taken from https://youtu.be/rKGq9AlfPR4?list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp
// If the execution time of threaded case is higher or equal, then try compling with clang++ instead of g++
// Build type : Release (without -g), -std=c++11, -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

std::vector<int> buffer;
std::mutex m;
std::condition_variable cond;
int buffer_capacity = 50;

void producer(int val)
{
    while (val)
    {
        std::unique_lock<std::mutex> lock(m);
        // release lock in case buffer is full and wait for it to be consumed (sleep and wait for notify_one() or notify_all() for condition variable)
        // keep the lock only if there is still some space left in buffer
        // that is why we need unique_lock (for it to be unlocked when needed to release)
        cond.wait(lock, []{ return buffer.size() < buffer_capacity;});
        buffer.push_back(val);
        std::cout << "Produced: " << val-- << std::endl;
        lock.unlock();
        cond.notify_one();
    }
}

void consumer()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(m);
        cond.wait(lock, []{ return buffer.size() > 0;}); // there should be something to consume
        int val = buffer.back();
        buffer.pop_back();
        std::cout << "Consumed: " << val << std::endl;
        lock.unlock();
        cond.notify_one();
    }
}

int main()
{
    std::thread t1(producer, 150);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}