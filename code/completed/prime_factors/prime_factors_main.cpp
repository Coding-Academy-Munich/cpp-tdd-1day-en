// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include <iostream>
#include <string>

#include "prime_factors.h"

using namespace prime_factors;

int main(int argc, char** argv)
{
    const int number_to_factor{argc >= 2 ? std::stoi(argv[1]) : 100};
    compute_and_write_primes(number_to_factor, std::cout);
}
