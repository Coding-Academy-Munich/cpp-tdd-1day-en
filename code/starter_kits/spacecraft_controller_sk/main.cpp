// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include <chrono>
#include <iostream>
#include <thread>

#include "spacecraft_command_controller.h"

void print_and_pause(const std::string_view text)
{
    std::cout << text;
    std::cout.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds{250});
}

int main()
{
    for (int remaining{10}; remaining > 0; --remaining)
    {
        print_and_pause(std::to_string(remaining));
        for (int i{0}; i < 3; ++i)
        {
            print_and_pause(".");
        }
    }
    std::cout << "Blast off!\n";
}
