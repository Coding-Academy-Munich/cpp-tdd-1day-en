// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include "Pawn.h"
#include "World.h"
#include "WorldFactory.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure;

TEST_CASE("Test Pawn", "[pawn]")
{
    v5a::World world {v5a::WorldFactory::create(data::simpleLocationDataVector)};
    v5a::Location& room1 {world.GetLocation("Room 1")};
    v5a::Location& room2 {world.GetLocation("Room 2")};
    v5a::Pawn pawn {"Test Pawn", room1};
}