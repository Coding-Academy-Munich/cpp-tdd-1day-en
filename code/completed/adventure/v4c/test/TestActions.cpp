// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include "Pawn.h"
#include "WorldFactory.h"
#include "actions/MoveAction.h"
#include "actions/SkipTurnAction.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure::v4c;

TEST_CASE("Test Action Descriptions", "[actions]")
{

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
