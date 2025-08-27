// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include "Pawn.h"
#include "Player.h"
#include "World.h"
#include "WorldFactory.h"
#include "actions/ErrorAction.h"
#include "actions/InvestigateAction.h"
#include "actions/MoveAction.h"
#include "actions/QuitAction.h"
#include "actions/SkipTurnAction.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure::v5b;
using namespace adventure::data;

TEST_CASE("Test Action::Description()", "[actions]")
{
    World world {WorldFactory::create(simpleLocationDataVector)};
    Location& room1 {world.GetLocation("Room 1")};
    Location& room2 {world.GetLocation("Room 2")};
    Pawn pawn {"Test Pawn", room1};
    Player player {"Test Player", room1, PlayerStrategy::LastAction};

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

TEST_CASE("Test Action equality")
{
    REQUIRE(ErrorAction() == ErrorAction());
    REQUIRE(InvestigateAction() == InvestigateAction());
    REQUIRE(MoveAction("north") == MoveAction("north"));
    REQUIRE(QuitAction() == QuitAction());
    REQUIRE(SkipTurnAction() == SkipTurnAction());

    REQUIRE(ErrorAction() != InvestigateAction());
    REQUIRE(ErrorAction() != MoveAction("north"));
    REQUIRE(ErrorAction() != QuitAction());
    REQUIRE(ErrorAction() != SkipTurnAction());

    REQUIRE(InvestigateAction() != MoveAction("north"));
    REQUIRE(InvestigateAction() != QuitAction());
    REQUIRE(InvestigateAction() != SkipTurnAction());

    REQUIRE(MoveAction("north") != MoveAction("south"));
    REQUIRE(MoveAction("north") != QuitAction());
    REQUIRE(MoveAction("north") != SkipTurnAction());

    REQUIRE(QuitAction() != SkipTurnAction());
}
