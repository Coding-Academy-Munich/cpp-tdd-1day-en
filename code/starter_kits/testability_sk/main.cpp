// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include <iostream>

#include "testability_sk.h"

using namespace testability_sk;

void print_header(const std::string_view title)
{

    std::cout << std::string(20, '-') << ' ' << title << std::endl;
}
int main()
{
    print_header("count()");
    for (int i = 0; i < 3; ++i)
    {
        std::cout << count() << std::endl;
    }

    print_header("Switch::toggle()");
    Switch s;
    for (int i = 0; i < 3; ++i)
    {
        s.toggle();
    }

    print_header("print_fib()");
    print_fib(5);
}
