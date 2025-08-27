// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include "World.h"
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <algorithm>

using namespace adventure;
using namespace std::string_literals;

TEST_CASE("Test World", "[world]")
{
    SECTION("Test construction from data")
    {
        v3a::World world {data::simpleLocationDataVector};

        SECTION("Basic features")
        {
            REQUIRE(world.GetLocations().size() == 2);
            REQUIRE(world.GetLocation("Room 1").GetName() == "Room 1");
            REQUIRE(world.GetLocation("Room 2").GetName() == "Room 2");
            REQUIRE(world.GetInitialLocationName() == "Room 1");
        }

        SECTION("Connection Creation")
        {
            auto& connections = world.GetConnections();

            const v3a::Location& room1 {world.GetLocation("Room 1")};
            const v3a::Location& room2 {world.GetLocation("Room 2")};
            const v3a::Connection northConnection {&room1, "north"s, &room2};
            const v3a::Connection southConnection {&room2, "south"s, &room1};

            REQUIRE(connections.size() == 2);
            REQUIRE(std::find(connections.cbegin(), connections.cend(), northConnection)
                != connections.cend());
            REQUIRE(std::find(connections.cbegin(), connections.cend(), southConnection)
                != connections.cend());
        }

        SECTION("Connection Query")
        {
            const v3a::Location& room1 {world.GetLocation("Room 1")};
            const v3a::Location& room2 {world.GetLocation("Room 2")};

            REQUIRE(world.GetConnectedLocation(room1, "north") == room2);
            REQUIRE(world.GetConnectedLocation(room2, "south") == room1);
        }
    }
}