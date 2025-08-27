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
    v6a::World world {v6a::WorldFactory::create(data::simpleLocationDataVector)};
    v6a::Location& room1 {world.GetLocation("Room 1")};
    v6a::Location& room2 {world.GetLocation("Room 2")};
    v6a::Pawn pawn {"Test Pawn", room1};
}