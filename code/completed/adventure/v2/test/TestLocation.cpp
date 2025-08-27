// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure;

TEST_CASE("Test Location", "[location]")
{
    SECTION("Test construction from data")
    {
        static const char* const expected
            = "You are in a bright room. There is a door to the north.";

        v2::Location location { data::simpleLocationDataVector[0] };
        REQUIRE(location.GetName() == "Room 1");
        REQUIRE(location.GetDescription() == expected);
    }
}