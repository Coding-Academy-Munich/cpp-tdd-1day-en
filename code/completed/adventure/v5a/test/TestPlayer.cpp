// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include "Player.h"
#include "World.h"
#include "WorldFactory.h"
#include "actions/MoveAction.h"
#include "actions/SkipTurnAction.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure;

TEST_CASE("Test Player", "[player]")
{
    v5a::World world {v5a::WorldFactory::create(data::simpleLocationDataVector)};
    v5a::Location& room1 {world.GetLocation("Room 1")};
    v5a::Location& room2 {world.GetLocation("Room 2")};
    v5a::Player player {"Test Player", room1};

    SECTION("Test Perform for skip turn")
    {
        v5a::SkipTurnAction action {};
        REQUIRE(GetLocation(player) == room1);

        player.Perform(action);
        REQUIRE(GetLocation(player) == room1);
    }

    SECTION("Test move actions")
    {
        v5a::MoveAction moveNorthAction {"north"};
        v5a::MoveAction moveEastAction {"east"};

        SECTION("Test Perform for valid move")
        {
            REQUIRE(GetLocation(player) == room1);
            player.Perform(moveNorthAction);
            REQUIRE(GetLocation(player) == room2);
        }

        SECTION("Test Perform for invalid move")
        {
            REQUIRE_THROWS(player.Perform(moveEastAction));
        }

        SECTION("Test PerformIfPossible for valid move")
        {
            REQUIRE(GetLocation(player) == room1);
            player.PerformIfPossible(moveNorthAction);
            REQUIRE(GetLocation(player) == room2);
        }

        SECTION("Test PerformIfPossible for invalid move")
        {
            REQUIRE(GetLocation(player) == room1);
            player.PerformIfPossible(moveEastAction);
            REQUIRE(GetLocation(player) == room1);
        }
    }
}