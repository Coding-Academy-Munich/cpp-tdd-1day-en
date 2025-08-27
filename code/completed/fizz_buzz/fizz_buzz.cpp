// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "fizz_buzz.h"

#include <iostream>
#include <string>

std::string say_number(int n)
{
    if (n % 15 == 0)
    {
        return "FizzBuzz";
    }
    if (n % 5 == 0)
    {
        return "Buzz";
    }
    if (n % 3 == 0)
    {
        return "Fizz";
    }
    return std::to_string(n);
}

void fizz_buzz(std::ostream& os, int n)
{
    for (int i = 1; i <= n; ++i)
    {
        os << say_number(i) << std::endl;
    }
}

void fizz_buzz(int n) { fizz_buzz(std::cout, n); }
