// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include <catch2/catch_test_macros.hpp>

#include "action.h"
#include "fixtures.h"
#include "game.h"

SCENARIO("Unit tests for Story 1")
{
    GIVEN("A new game")
    {
        adv::Game game{create_rooms()};

        THEN("The description of the current room is as specified")
        {
            CHECK(
                game.current_room().description() ==
                "You are in the Grand Hall. It is a vast, echoing chamber.");
        }
    }
}

SCENARIO("Unit tests for Story 2")
{
    GIVEN("A game where I am in the Grand Hall")
    {
        adv::Game game{create_rooms()};
        REQUIRE(game.current_room().name() == "Grand Hall");

        WHEN("I perform the command to move north")
        {
            game.perform(adv::MoveAction("north"));
            THEN("I am in the Armoury")
            {
                CHECK(game.current_room().name() == "Armoury");
            }
        }

        THEN("The command to move north creates a MoveAction")
        {
            const auto result = game.parse_command("move north");
            CHECK(*result == adv::MoveAction("north"));
        }
    }
}
