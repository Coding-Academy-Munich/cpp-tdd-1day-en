// Created by Dr. Matthias Hölzl on 01/10/2023.
// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure_sk2;

TEST_CASE("Test Location", "[location]")
{
    SECTION("Test construction from data")
    {
        static const char* const expected
            = "You are in a bright room. There is a door to the north.";

        Location location { data::simpleLocations[0] };
        REQUIRE(location.GetName() == "Room 1");
        REQUIRE(location.GetDescription() == expected);
    }
}