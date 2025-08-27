// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "prime_factors.h"

#include <iostream>
#include <sstream>

std::vector<long> prime_factors::compute_prime_factors(long n)
{
    std::vector<long> result{};

    for (long factor{2}; factor <= n; ++factor)
    {
        while (n % factor == 0)
        {
            result.push_back(factor);
            n /= factor;
        }
    }

    return result;
}

std::string prime_factors::format_primes(const std::vector<long>& primes)
{
    std::stringstream result;
    std::string prefix{""};

    for (const int prime : primes)
    {
        result << prefix << std::to_string(prime);
        prefix = ", ";
    }

    return result.str();
}

void prime_factors::compute_and_write_primes(long n, std::ostream& os = std::cout)
{
    const std::vector<long> prime_factors(compute_prime_factors(n));

    os << "The primes of " << n << " are: " << format_primes(prime_factors);
}
