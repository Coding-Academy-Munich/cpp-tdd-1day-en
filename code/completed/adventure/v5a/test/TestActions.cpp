// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include "Pawn.h"
#include "Player.h"
#include "World.h"
#include "WorldFactory.h"
#include "actions/MoveAction.h"
#include "actions/SkipTurnAction.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure::v5a;
using namespace adventure::data;

TEST_CASE("Test Action Descriptions", "[actions]")
{
    World world {WorldFactory::create(simpleLocationDataVector)};
    Location& room1 {world.GetLocation("Room 1")};
    Location& room2 {world.GetLocation("Room 2")};
    Pawn pawn {"Test Pawn", room1};
    Player player {"Test Player", room1};

    SECTION("SkipTurnAction")
    {
        SkipTurnAction action {};
        REQUIRE(action.Description() == "Skip one turn.");
    }

    SECTION("MoveAction")
    {
        MoveAction moveNorthAction {"north"};
        MoveAction moveEastAction {"east"};

        REQUIRE(moveNorthAction.Description() == "Move the player north.");
        REQUIRE(moveEastAction.Description() == "Move the player east.");
    }
}
