// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Member.h"
#include <catch2/catch_test_macros.hpp>

using namespace library::v1;

TEST_CASE("Test RegularMemberType")
{
    SECTION("Test ToString()")
    {
        RegularMemberType type {};
        REQUIRE(type.ToString() == "regular member");
    }
}

TEST_CASE("Test Member")
{
    auto dateOfBirth {std::chrono::year_month_day {
        std::chrono::year {1999}, std::chrono::month {10}, std::chrono::day {2}}};
    Member johnDoe {1, std::make_unique<RegularMemberType>(), "John Doe",
        {"Home, sweet home."}, dateOfBirth};
    Member janeDoe {2, std::make_unique<RegularMemberType>(), "Jane Doe",
        {"Home, sweet home."}, dateOfBirth, "Software Engineer"};

    SECTION("Test operator==()")
    {
        REQUIRE(johnDoe == johnDoe);
        REQUIRE(janeDoe == janeDoe);
        REQUIRE(johnDoe != janeDoe);
    }

    SECTION("Test operator<<() for missing occupation")
    {
        std::ostringstream os;
        os << johnDoe;
        REQUIRE(os.str()
            == "Member{id: 1, name: John Doe, address: \"Home, sweet home.\", "
               "birthday: 1999-10-02, occupation: unknown, type: regular member}");
    }

    SECTION("Test operator<<() when occupation is available")
    {
        std::ostringstream os;
        os << janeDoe;
        REQUIRE(os.str()
            == "Member{id: 2, name: Jane Doe, address: \"Home, sweet home.\", "
               "birthday: 1999-10-02, occupation: Software Engineer, type: regular "
               "member}");
    }
}
