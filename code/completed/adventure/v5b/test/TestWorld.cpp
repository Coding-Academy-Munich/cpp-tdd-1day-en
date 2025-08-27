// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include "World.h"
#include "WorldFactory.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure;

TEST_CASE("Test World", "[world]")
{
    SECTION("Test construction from data")
    {
        v5b::World world {v5b::WorldFactory::create(data::simpleLocationDataVector)};

        SECTION("Basic features")
        {
            REQUIRE(world.GetLocations().size() == 2);
            REQUIRE(world.GetLocation("Room 1").GetName() == "Room 1");
            REQUIRE(world.GetLocation("Room 2").GetName() == "Room 2");
            REQUIRE(world.GetInitialLocationName() == "Room 1");
        }
    }
}