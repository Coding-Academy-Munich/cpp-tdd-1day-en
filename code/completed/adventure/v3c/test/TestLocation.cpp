// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include "World.h"
#include "WorldFactory.h"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <string>

using namespace std::string_literals;

using namespace adventure;

TEST_CASE("Test Location", "[location]")
{
    SECTION("Test construction from data")
    {
        SECTION("Basic features")
        {
            static const char* const expectedDescription
                = "You are in a bright room. There is a door to the north.";

            v3c::Location location {data::simpleLocationDataVector[0]};
            REQUIRE(location.GetName() == "Room 1");
            REQUIRE(location.GetDescription() == expectedDescription);
        }

        SECTION("Connections for simple location data")
        {
            v3c::World world {
                v3c::WorldFactory::create(data::simpleLocationDataVector)};
            const auto& room1 {world.GetLocation("Room 1")};
            const auto& room2 {world.GetLocation("Room 2")};

            SECTION("Connected Locations")
            {
                REQUIRE(room1.GetConnectedLocation("north") == room2);
                REQUIRE(room2.GetConnectedLocation("south") == room1);
                REQUIRE_THROWS(room1.GetConnectedLocation("south"));
            }

            SECTION("Connected Directions")
            {
                REQUIRE(room1.GetConnectedDirections().size() == 1);
                REQUIRE(room1.GetConnectedDirections() == std::vector {"north"s});
            }
        }

        SECTION("Connections for dungeon")
        {
            v3c::World world {v3c::WorldFactory::create(data::dungeonLocationDataVector)};

            const auto& vestibule {world.GetLocation("Vestibule")};
            const auto& entranceHall {world.GetLocation("Entrance Hall")};
            const auto& darkCorridor {world.GetLocation("Dark Corridor")};
            const auto& brightlyLitCorridor {
                world.GetLocation("Brightly Lit Corridor")};
            const auto& treasureChamber {world.GetLocation("Treasure Chamber")};

            SECTION("Connected Locations")
            {
                REQUIRE(vestibule.GetConnectedLocation("north") == entranceHall);
                REQUIRE(entranceHall.GetConnectedLocation("west") == darkCorridor);
                REQUIRE(
                    entranceHall.GetConnectedLocation("east") == brightlyLitCorridor);
                REQUIRE(entranceHall.GetConnectedLocation("south") == vestibule);
                REQUIRE(darkCorridor.GetConnectedLocation("west") == treasureChamber);
                REQUIRE(darkCorridor.GetConnectedLocation("east") == entranceHall);
                REQUIRE(
                    brightlyLitCorridor.GetConnectedLocation("west") == entranceHall);
                REQUIRE(treasureChamber.GetConnectedLocation("east") == darkCorridor);
            }

            SECTION("Connected Directions")
            {
                REQUIRE(vestibule.GetConnectedDirections() == std::vector {"north"s});
                std::vector<std::string> entranceHallDirections {
                    entranceHall.GetConnectedDirections()};
                std::sort(entranceHallDirections.begin(), entranceHallDirections.end());
                REQUIRE(
                    entranceHallDirections == std::vector {"east"s, "south"s, "west"s});
            }
        }
    }
}
