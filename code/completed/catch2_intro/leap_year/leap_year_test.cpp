// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "leap_year.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEST_CASE ("A year is not a leap year")
{
    SECTION ("if it is not divisible by 4")
    {
        CHECK(!is_leap_year(1983));
        CHECK_FALSE(is_leap_year(2021));
    }
    SECTION ("if it is divisible by 100 but not 400")
    {
        CHECK_FALSE(is_leap_year(1900));
    }
}

TEST_CASE ("A year is a leap year")
{
    SECTION ("if it is divisible by 4 but not 100")
    {
        REQUIRE(is_leap_year(1984));
    }
    SECTION ("if it is divisible by 400")
    {
        REQUIRE(is_leap_year(2000));
    }
}

TEST_CASE ("A year is not a leap year (parametric)")
{
    int year{GENERATE(1983, 2021, 1900)};
    CHECK_FALSE(is_leap_year(year));
}

TEST_CASE ("A year is a leap year (parametric)")
{
    int year{GENERATE(1984, 2000)};
    SECTION ("For " + std::to_string(year))
    {
        REQUIRE(is_leap_year(year));
    }
}

std::string leap_year_section_title(int year, bool is_leap_year)
{
    return std::to_string(year) + " is " + (is_leap_year ? "" : "not ") + "a leap year";
}

TEST_CASE ("A year is or is not a leap year (parametric)")
{
    auto [year, expected] = GENERATE(table<int, bool>({
        {1983, false},
        {2021, false},
        {1900, false},
        {1984, true},
        {2000, true},
    }));
    SECTION (leap_year_section_title(year, expected))
    {
        CHECK(is_leap_year(year) == expected);
    }
}