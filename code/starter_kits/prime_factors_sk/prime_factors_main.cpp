// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include <iostream>
#include <string>

#include "prime_factors.h"

int main(int argc, char** argv)
{

    const long number_to_factor{argc >= 2 ? std::stol(argv[1]) : 100L};
    std::cout << "I don't know how to factor, yet.\n"
              << "Please fix me.\n";
}
