// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#define CATCH_CONFIG_MAIN
#include "fizz_buzz.h"

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>

TEST_CASE ("Tests for say_number")
{
    SECTION ("numbers not divisible by 3 or 5")
    {
        REQUIRE(say_number(1) == "1");
        REQUIRE(say_number(2) == "2");
        REQUIRE(say_number(4) == "4");
    }

    SECTION ("numbers divisible by 3 but not 5")
    {
        REQUIRE(say_number(3) == "Fizz");
        REQUIRE(say_number(6) == "Fizz");
    }

    SECTION ("numbers divisible by 5 but not 3")
    {
        REQUIRE(say_number(5) == "Buzz");
        REQUIRE(say_number(10) == "Buzz");
    }

    SECTION ("numbers divisible by both 3 and 5")
    {
        REQUIRE(say_number(15) == "FizzBuzz");
        REQUIRE(say_number(30) == "FizzBuzz");
    }
}

TEST_CASE ("test for fizz_buzz")
{
    std::stringstream output;
    std::string result{"1\n2\nFizz\n4\nBuzz\nFizz\n7\n8\nFizz\n"
                       "Buzz\n11\nFizz\n13\n14\nFizzBuzz\n16\n"};

    fizz_buzz(output, 16);
    REQUIRE(output.str() == result);
}
