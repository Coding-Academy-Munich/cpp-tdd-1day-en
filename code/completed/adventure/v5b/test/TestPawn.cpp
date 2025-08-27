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
    v5b::World world {v5b::WorldFactory::create(data::simpleLocationDataVector)};
    v5b::Location& room1 {world.GetLocation("Room 1")};
    v5b::Location& room2 {world.GetLocation("Room 2")};
    v5b::Pawn pawn {"Test Pawn", room1};
}