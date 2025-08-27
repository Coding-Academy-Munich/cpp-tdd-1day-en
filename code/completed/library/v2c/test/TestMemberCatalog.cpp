// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "MemberCatalog.h"
#include "Utils.h"
#include <catch2/catch_test_macros.hpp>

using namespace library::v2c;

TEST_CASE("MemberCatalog: members can be found", "[member-catalog]")
{
    MemberCatalog members;
    members.Add(1, std::make_unique<RegularMemberType>(), "John Doe", "123 Main Street",
        MakeYearMonthDay(1980, 7, 12));
    members.Add(2, std::make_unique<RegularMemberType>(), "Jane Doe", "123 Main Street",
        MakeYearMonthDay(1960, 2, 3), "Software Engineer");

    SECTION("Find member by ID")
    {
        auto member {members.FindById(1)};
        REQUIRE(member != nullptr);
        REQUIRE(member->GetId() == 1);
        REQUIRE(member->GetName() == "John Doe");
    }

    SECTION("Find non-existing member by ID")
    {
        auto member {members.FindById(3333)};
        REQUIRE(member == nullptr);
    }

    SECTION("Find member by name")
    {
        auto member {members.FindByName("Jane Doe")};
        REQUIRE(member != nullptr);
        REQUIRE(member->GetId() == 2);
        REQUIRE(member->GetName() == "Jane Doe");
    }

    SECTION("Find member by birthday")
    {
        auto member {members.FindByBirthday(MakeYearMonthDay(1960, 2, 3))};
        REQUIRE(member != nullptr);
        REQUIRE(member->GetId() == 2);
        REQUIRE(member->GetName() == "Jane Doe");
    }

    SECTION("Find member by address")
    {
        auto member {members.FindByAddress("123 Main Street")};
        REQUIRE(member != nullptr);
        REQUIRE(member->GetId() == 1);
        REQUIRE(member->GetName() == "John Doe");
    }

    SECTION("Find member by occupation")
    {
        auto member {members.FindByOccupation("Software Engineer")};
        REQUIRE(member != nullptr);
        REQUIRE(member->GetId() == 2);
        REQUIRE(member->GetName() == "Jane Doe");
    }
}
