// This example will only work on Windows.

#include <iostream>
#include <thread>
#include <conio.h>
#include <Windows.h>

std::string displayString("");

// For some reason the optimizations take away the displayString from this thread. So need to pass by reference
void displayFunc(std::string& displayString)
{
    int oldStringLen{};

    while (true)
    {
        if (displayString.size() != oldStringLen)
        {
            system("cls");
            std::cout << "Your string: " << displayString << "\n";
            std::cout << "String size: " << displayString.size() << "\n";
            oldStringLen = displayString.size();
        }
    }
}

int main()
{

    // initialize display
    std::cout << "Your string: " << displayString << std::endl;
    std::cout << "String size: " << displayString.size() << std::endl;

    // Separate thread for displaying displayString and it's length
    std::thread displayThread(displayFunc, std::ref(displayString));

    // Main thread will register key presses and manipulate DisplayString
    while (true)
    {   
        if (_kbhit())
        {
            char key = _getch();

            if (key == 8) // 8 is ascii code for Backspace key
            {

                if (!displayString.empty())
                {
                    displayString.pop_back();
                }
            }
            else
            {
                displayString.push_back(key);
            }
        }
    }
}

