// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "prime_factors.h"

#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std::string_literals;
using namespace prime_factors;

TEST_CASE ("compute_prime_factors()")
{
    SECTION ("compute_prime_factors(2) returns [2]")
    {
        std::vector<long> expected{2L};

        CHECK(compute_prime_factors(2L) == expected);
    }

    SECTION ("compute_prime_factors(3) returns [3]")
    {
        std::vector<long> expected{3L};

        CHECK(compute_prime_factors(3L) == expected);
    }

    SECTION ("compute_prime_factors(4) returns [2, 2]")
    {
        std::vector<long> expected{2L, 2L};

        CHECK(compute_prime_factors(4L) == expected);
    }

    SECTION ("compute_prime_factors(5) returns [5]")
    {
        std::vector<long> expected{5L};

        CHECK(compute_prime_factors(5L) == expected);
    }
}

bool is_prime(long n)
{
    for (long factor = 2; factor < n; ++factor)
    {
        if (n % factor == 0)
        {
            return false;
        }
    }
    return true;
}

long multiply_elements(const std::vector<long>& v)
{
    return std::accumulate(v.begin(), v.end(), 1, std::multiplies<>());
}

// Use the tag [slow] to include the test.
TEST_CASE ("Pseudo-parametric/property-based test case", "[.][slow]")
{
    for (long i = 1; i < 1000L; ++i)
    {
        std::vector<long> result = compute_prime_factors(i);
        CHECK(multiply_elements(result) == i);
        CHECK(std::is_sorted(result.begin(), result.end()));

        for (const long n : result)
        {
            CHECK(is_prime(n));
        }
    }
}

TEST_CASE ("format_primes()")
{
    SECTION ("formats an empty vector correctly")
    {
        CHECK(format_primes(std::vector<long>{}) == ""s);
    }
    SECTION ("formats a vector with one element correctly")
    {
        std::vector<long> unit{2L};
        std::string expected{"2"s};
        CHECK(format_primes(unit) == expected);
    }
    SECTION ("formats a vector with two elements correctly")
    {
        std::vector<long> unit{2L, 5L};
        std::string expected{"2, 5"s};
        CHECK(format_primes(unit) == expected);
    }
    SECTION ("formats a vector with five elements correctly")
    {
        std::vector<long> unit{2L, 2L, 5L, 7L, 11L};
        std::string expected{"2, 2, 5, 7, 11"s};
        CHECK(format_primes(unit) == expected);
    }
}

TEST_CASE ("compute_and_write_primes()")
{
    SECTION ("prints the correct output for 100")
    {
        std::string expected{"The primes of 100 are: 2, 2, 5, 5"s};
        std::stringstream os{};
        compute_and_write_primes(100, os);
        CHECK(os.str() == expected);
    }
}