// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.


#include <future>

#include "fixtures.h"
#include "test_utils.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "game.h"

using namespace Catch::Matchers;

// Initial version of the test:
//
// SCENARIO("Story 1: Starting the Game")
// {
//     GIVEN("A new game")
//     {
//         adv::Game game{};
//
//         WHEN("I start the game")
//         {
//             // ReSharper disable once CppTooWideScope
//             const CoutRedirect cout_redirect{};
//             game.run();
//
//             THEN("I see the specified text")
//             {
//                 CHECK_THAT(cout_redirect.str(),
//                            StartsWith("You are in the Grand Hall. "
//                                       "It is a vast, echoing chamber."));
//             }
//         }
//     }
// }

// Second version of the test, running game in a different thread to avoid
// blocking.

SCENARIO("Story 1: Starting the Game")
{
    GIVEN("A new game")
    {
        CoutRedirect cout_redirect{};
        CinRedirect cin_redirect{};
        cin_redirect.stream() << "bye\n";
        adv::Game game{create_rooms()};

        WHEN("I start the game")
        {
            game.run();

            THEN("I see the specified text")
            {
                CHECK_THAT(cout_redirect.str(),
                           StartsWith("You are in the Grand Hall. "
                                      "It is a vast, echoing chamber."));
            }
        }
    }
}


SCENARIO("Story 2: Moving to a Connected Room")
{
    GIVEN("A game where I am in the Grand Hall")
    {
        CoutRedirect cout_redirect{};
        CinRedirect cin_redirect{};
        cin_redirect.stream() << "north\n" << "bye\n";

        adv::Game game{create_rooms()};
        REQUIRE(game.current_room().name() == "Grand Hall");

        game.run();

        WHEN("I enter the command to move north")
        {
            THEN("I see the specified text")
            {
                CHECK_THAT(
                    cout_redirect.str(),
                    ContainsSubstring("You are in the Armoury. "
                                      "Racks of dusty weapons line the walls."));
            }
        }
    }
}
