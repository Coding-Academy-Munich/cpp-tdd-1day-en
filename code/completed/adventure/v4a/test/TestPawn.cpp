// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include "Pawn.h"
#include "World.h"
#include "WorldFactory.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure;

TEST_CASE("Test Pawn", "[pawn]")
{
    v4a::World world {v4a::WorldFactory::create(data::simpleLocationDataVector)};
    v4a::Location& room1 {world.GetLocation("Room 1")};
    v4a::Location& room2 {world.GetLocation("Room 2")};
    v4a::Pawn pawn {"Test Pawn", &room1};

    SECTION("Test Move for valid move")
    {
        REQUIRE(pawn.GetLocation() == room1);
        pawn.Move("north");
        REQUIRE(pawn.GetLocation() == room2);
    }

    SECTION("Test Move for invalid move") { REQUIRE_THROWS(pawn.Move("east")); }

    SECTION("Test MoveIfPossible for valid move")
    {
        REQUIRE(pawn.GetLocation() == room1);
        pawn.MoveIfPossible("north");
        REQUIRE(pawn.GetLocation() == room2);
    }

    SECTION("Test MoveIfPossible for invalid move")
    {
        REQUIRE(pawn.GetLocation() == room1);
        pawn.MoveIfPossible("east");
        REQUIRE(pawn.GetLocation() == room1);
    }
}