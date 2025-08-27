// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Utils.h"
#include <catch2/catch_test_macros.hpp>

using namespace library::v2a;

TEST_CASE("Test MakeYearMonthDay()", "[utils]")
{
    SECTION("Test MakeYearMonthDay()")
    {
        auto date {MakeYearMonthDay(2023, 10, 2)};
        REQUIRE(date.year() == std::chrono::year {2023});
        REQUIRE(date.month() == std::chrono::month {10});
        REQUIRE(date.day() == std::chrono::day {2});
    }
}

TEST_CASE("Test JoinVector struct", "[utils]")
{
    SECTION("Output empty vector")
    {
        std::vector<std::string> v;
        std::ostringstream os;
        os << JoinVector {v};

        REQUIRE(os.str() == "[]");
    }

    SECTION("Output string vector")
    {
        std::vector<std::string> v {"alpha", "beta", "gamma"};
        std::ostringstream os;
        os << JoinVector {v};

        REQUIRE(os.str() == "[alpha, beta, gamma]");
    }

    SECTION("Output int vector")
    {
        std::vector<int> v {1, 2, 3};
        std::ostringstream os;
        os << JoinVector {v};

        REQUIRE(os.str() == "[1, 2, 3]");
    }

    SECTION("Output with custom separator")
    {
        std::vector<std::string> v {"alpha", "beta", "gamma"};
        std::ostringstream os;
        os << JoinVector {v, "; "};

        REQUIRE(os.str() == "[alpha; beta; gamma]");
    }

    SECTION("Output with custom prefix and suffix")
    {
        std::vector<std::string> v {"alpha", "beta", "gamma"};
        std::ostringstream os;
        os << JoinVector {v, "; ", "(", ")"};

        REQUIRE(os.str() == "(alpha; beta; gamma)");
    }
}
