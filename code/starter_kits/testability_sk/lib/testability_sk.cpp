// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include <iostream>

#include "testability_sk.h"


namespace testability_sk
{

    int count()
    {
        static int c = 0;
        return c++;
    }

    void Switch::toggle()
    {
        state_ = state_ == State::OFF ? State::ON : State::OFF;
        std::cout << "Switch is " << (state_ == State::OFF ? "OFF" : "ON")
                  << std::endl;
    }

    void print_fib(int n)
    {
        int a{0};
        int b{1};
        for (int i{0}; i < n; ++i)
        {
            std::cout << "fib(" << i << ") = " << b << std::endl;
            const int tmp{a};
            a = b;
            b = tmp + b;
        }
    }

} // namespace testability_sk
