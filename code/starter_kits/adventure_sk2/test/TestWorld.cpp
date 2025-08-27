// Created by Dr. Matthias Hölzl on 01/10/2023.
// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include "World.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure_sk2;

TEST_CASE("Test World", "[world]")
{
    SECTION("Test construction from data")
    {
        World world { data::simpleLocations };
        REQUIRE(world.GetLocations().size() == 2);
        REQUIRE(world.GetLocation("Room 1").GetName() == "Room 1");
        REQUIRE(world.GetLocation("Room 2").GetName() == "Room 2");
        REQUIRE(world.GetInitialLocationName() == "Room 1");
    }
}