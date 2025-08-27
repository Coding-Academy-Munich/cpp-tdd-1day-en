// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include "Pawn.h"
#include "World.h"
#include "WorldFactory.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure;

TEST_CASE("Test Pawn", "[pawn]")
{
    v4b::World world {v4b::WorldFactory::create(data::simpleLocationDataVector)};
    v4b::Location& room1 {world.GetLocation("Room 1")};
    v4b::Location& room2 {world.GetLocation("Room 2")};
    v4b::Pawn pawn {"Test Pawn", &room1};

    SECTION("Test PerformAction for skip turn")
    {
        REQUIRE(pawn.GetLocation() == room1);
        pawn.Perform(v4b::Action::SkipTurn, "");
        REQUIRE(pawn.GetLocation() == room1);
    }

    SECTION("Test PerformAction for valid move")
    {
        REQUIRE(pawn.GetLocation() == room1);
        pawn.Perform(v4b::Action::Move, "north");
        REQUIRE(pawn.GetLocation() == room2);
    }

    SECTION("Test PerformAction for invalid move")
    {
        REQUIRE_THROWS(pawn.Perform(v4b::Action::Move, "east"));
    }

    SECTION("Test PerformActionIfPossible for valid move")
    {
        REQUIRE(pawn.GetLocation() == room1);
        pawn.PerformIfPossible(v4b::Action::Move, "north");
        REQUIRE(pawn.GetLocation() == room2);
    }

    SECTION("Test PerformActionIfPossible for invalid move")
    {
        REQUIRE(pawn.GetLocation() == room1);
        pawn.PerformIfPossible(v4b::Action::Move, "east");
        REQUIRE(pawn.GetLocation() == room1);
    }
}