// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include "Player.h"
#include "World.h"
#include "WorldFactory.h"
#include "actions/ErrorAction.h"
#include "actions/InvestigateAction.h"
#include "actions/MoveAction.h"
#include "actions/QuitAction.h"
#include "actions/SkipTurnAction.h"
#include <catch2/catch_test_macros.hpp>

using namespace adventure::data;
using namespace adventure::v5b;

TEST_CASE("Test Player in simple world", "[player]")
{
    World world {WorldFactory::create(simpleLocationDataVector)};
    Location& room1 {world.GetLocation("Room 1")};
    Location& room2 {world.GetLocation("Room 2")};
    Player player {"Test Player", room1, PlayerStrategy::LastAction};

    SECTION("Test GetName()") { REQUIRE(GetName(player) == "Test Player"); }
    SECTION("Test GetLocation()") { REQUIRE(GetLocation(player) == room1); }

    SECTION("Actions")
    {
        MoveAction moveNorthAction {"north"};
        MoveAction moveSouthAction {"south"};
        InvestigateAction investigateAction {};
        SkipTurnAction skipTurnAction {};
        QuitAction quitAction {};
        ErrorAction errorAction {};

        SECTION("Test GetPossibleActions() for non-interactive player")
        {
            const auto& actions {player.GetPossibleActions()};
            REQUIRE(actions.size() == 3);
            REQUIRE(*actions[0] == moveNorthAction);
            REQUIRE(*actions[1] == investigateAction);
            REQUIRE(*actions[2] == skipTurnAction);
        }

        SECTION("Test GetPossibleActions() for interactive player")
        {
            const auto interactivePlayer {
                Player("Test Player", room1, PlayerStrategy::Interactive)};
            const auto& actions {interactivePlayer.GetPossibleActions()};
#ifndef NDEBUG
            REQUIRE(actions.size() == 5);
#else
            REQUIRE(actions.size() == 4);
#endif
            REQUIRE(*actions[0] == moveNorthAction);
            REQUIRE(*actions[1] == investigateAction);
            REQUIRE(*actions[2] == skipTurnAction);
            REQUIRE(*actions[3] == quitAction);
#ifndef NDEBUG
            REQUIRE(*actions[4] == errorAction);
#endif
        }
    }

    SECTION("Test IsInteractive()")
    {
        REQUIRE(player.IsInteractive() == false);
        const Player& interactivePlayer
            = Player("Test Player", room1, PlayerStrategy::Interactive);
        REQUIRE(interactivePlayer.IsInteractive() == true);
    }

    SECTION("Test Perform for skip turn")
    {
        SkipTurnAction action {};
        REQUIRE(GetLocation(player) == room1);

        player.Perform(action);
        REQUIRE(GetLocation(player) == room1);
    }

    SECTION("Test Perform for error action")
    {
        ErrorAction action {};
        REQUIRE_THROWS_AS(player.Perform(action), std::runtime_error);
    }

    SECTION("Test Perform for QuitAction")
    {
        QuitAction action {};
        REQUIRE_THROWS_AS(player.Perform(action), QuitGameException);
    }

    SECTION("Test move actions")
    {
        MoveAction moveNorthAction {"north"};
        MoveAction moveEastAction {"east"};

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