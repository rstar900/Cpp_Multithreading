// Insipration taken from https://youtu.be/hCvc9y39RDw?list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp
// If the execution time of threaded case is higher or equal, then try compling with clang++ instead of g++
// Build type : Release (without -g), -std=c++11, -pthread

#include <iostream>
#include <thread>

// functor
class SayHello
{
public:
    void operator()(const std::string name)
    {
        std::cout << "Hello " << name << " from a functor!\n";
    }
};

// class with static and non-static function
class ExampleClass
{
public:    
    void say_hello(const std::string name)
    {
        std::cout << "Hello " << name << " from a class member function!\n";
    }

    static void say_hello_static(const std::string name);
};

void ExampleClass::say_hello_static(const std::string name)
{
     std::cout << "Hello " << name << " from a class static function!\n";
}

// lambda 
auto say_hello_lambda = [](const std::string name)
{
     std::cout << "Hello " << name << " from a lambda function!\n";
};

// regular function
void say_hello_regular(const std::string name)
{
    std::cout << "Hello " << name << " from a regular function!\n";
}

int main()
{
    SayHello sh;
    ExampleClass obj;

    // Creating threads for different types of functions
    std::thread t1((SayHello()), "USER"); // Building a SayHello functor object in-place
    std::thread t2(sh, "USER"); // using the sh object of the SayHello functor
    std::thread t3(&ExampleClass::say_hello_static, "USER");
    std::thread t4(&ExampleClass::say_hello, &obj, "USER");
    std::thread t5(say_hello_lambda, "USER");
    std::thread t6(say_hello_regular, "USER");
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
}