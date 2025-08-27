// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include "Pawn.h"
#include "World.h"
#include "WorldFactory.h"
#include "actions/MoveAction.h"
#include "actions/SkipTurnAction.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure;

TEST_CASE("Test Pawn", "[pawn]")
{
    v4c::World world {v4c::WorldFactory::create(data::simpleLocationDataVector)};
    v4c::Location& room1 {world.GetLocation("Room 1")};
    v4c::Location& room2 {world.GetLocation("Room 2")};
    v4c::Pawn pawn {"Test Pawn", room1};

    SECTION("Test Perform for skip turn")
    {
        v4c::SkipTurnAction action {};
        REQUIRE(pawn.GetLocation() == room1);

        pawn.Perform(action);
        REQUIRE(pawn.GetLocation() == room1);
    }

    SECTION("Test move actions")
    {
        v4c::MoveAction moveNorthAction {"north"};
        v4c::MoveAction moveEastAction {"east"};

        SECTION("Test Perform for valid move")
        {
            REQUIRE(pawn.GetLocation() == room1);
            pawn.Perform(moveNorthAction);
            REQUIRE(pawn.GetLocation() == room2);
        }

        SECTION("Test Perform for invalid move")
        {
            REQUIRE_THROWS(pawn.Perform(moveEastAction));
        }

        SECTION("Test PerformIfPossible for valid move")
        {
            REQUIRE(pawn.GetLocation() == room1);
            pawn.PerformIfPossible(moveNorthAction);
            REQUIRE(pawn.GetLocation() == room2);
        }

        SECTION("Test PerformIfPossible for invalid move")
        {
            REQUIRE(pawn.GetLocation() == room1);
            pawn.PerformIfPossible(moveEastAction);
            REQUIRE(pawn.GetLocation() == room1);
        }
    }
}