// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "leap_year.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

SCENARIO ("A year is not a leap year")
{
    GIVEN ("A year that is not divisible by 4")
    {
        THEN ("It is not a leap year")
        {
            CHECK(!is_leap_year(1983));
            CHECK_FALSE(is_leap_year(2021));
        }
    }
    GIVEN ("A year that is divisible by 100 but not 400")
    {
        THEN ("It is not a leap year")
        {
            CHECK_FALSE(is_leap_year(1900));
        }
    }
}

SCENARIO ("A year is a leap year")
{
    GIVEN ("A year that is divisible by 4 but not 100")
    {
        THEN ("It is a leap year")
        {
            REQUIRE(is_leap_year(1984));
        }
    }
    GIVEN ("A year that is divisible by 400")
    {
        THEN ("It is a leap year")
        {
            REQUIRE(is_leap_year(2000));
        }
    }
}

SCENARIO ("A year is not a leap year (parametric)")
{
    GIVEN ("A year that is not a leap year")
    {
        int year{GENERATE(1983, 2021, 1900)};
        THEN (std::to_string(year) + " is not a leap year")
        {
            CHECK_FALSE(is_leap_year(year));
        }
    }
}

SCENARIO ("A year is or is not a leap year")
{
    GIVEN ("A year and its leap-year status")
    {
        auto [year, expected] = GENERATE(table<int, bool>({
            {1983, false},
            {2021, false},
            {1900, false},
            {1984, true},
            {2000, true},
        }));
        THEN ("is_leap_year(" + std::to_string(year) +
              ") == " + (expected ? "true" : "false"))
        {
            CHECK(is_leap_year(year) == expected);
        }
    }
}
