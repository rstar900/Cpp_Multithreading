// Insipration taken from https://youtu.be/r-PDHNWYdes?list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp
// If the execution time of threaded case is higher or equal, then try compling with clang++ instead of g++
// Build type : Release (without -g), -std=c++11, -pthread

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int x {}, y{}; // Shared variables x and y initialized to 0
std::mutex m1, m2; // Mutexes needed to access critical region

void incrementXY(std::mutex& m, int& xy, const char* var)
{
    // increment x or y 5 times
    for (int i{}; i < 5; ++i)
    {
        m.lock(); 
        ++xy;
        std::cout << var << " incremented by 1\n";
        m.unlock(); 
        std::this_thread::sleep_for(std::chrono::seconds(2)); // for simulating some time delay before locking again 
    }
}

// this will consume both x and y and increment it's own local variable equal to x + y
void consumer()
{
    int x_plus_y {}; // this is the local variable
    int count {5}; // Max number of times we need to increment

    while (true)
    {

        if (!count) // Max increments done, then end
        {
            break;
        }

        int lock_result = std::try_lock(m1, m2);

        if (lock_result == -1) // success in locking both m1 and m2
        {
            if (x != 0 && y != 0)
            {
                x_plus_y += x + y;
                x = 0;
                y = 0;
                --count;
                std::cout << "Consumer incremented x_plus_y\n"; 
            }

        	else
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                // if x or y are still 0 even after this wait period, that means they no longer need to be incremented
                if (x == 0 || y == 0)
                {
                    break;
                }
            }

            // need to unlock all locked mutexes manually
            m1.unlock();
            m2.unlock();
        }
        else
        {
            // coz std::try_lock will return first 0 indexed mutex not locked
            std::cout << "Consumer could not lock mutex m" << lock_result + 1 << "\n"; 
        }

        std::this_thread::sleep_for(std::chrono::seconds(2)); // we don't want to flood the console

    }

    std::cout << "Consumer ends : x_plus_y is equal to " << x_plus_y << "\n";
    return;
}

int main()
{
    std::thread t1(incrementXY, std::ref(m1), std::ref(x), "x"); // std::ref mandatory if some prameters are to be passed by reference
    std::thread t2(incrementXY,std::ref(m2), std::ref(y), "y");
    std::thread t3(consumer);
    t1.join();
    t2.join();
    t3.join();
}
