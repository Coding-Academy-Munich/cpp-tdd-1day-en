// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "cout_redirect.h"
#include "state_machine.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

using Catch::Matchers::ContainsSubstring;

TEST_CASE ("StateMachine")
{
    StateMachine unit;

    SECTION ("State after [insert coin -> select drink] is DrinkDelivered")
    {
        // Act
        unit.insert_coin();
        unit.select_drink();

        // Assert
        // Cannot access state directly. Use take_drink() to move back to initial state
        // and check that correct output is delivered
        CoutRedirect cr;
        unit.take_drink();
        REQUIRE_THAT(cr.get_output(), ContainsSubstring("Enjoy your drink!"));
    }

    SECTION ("State after [select drink -> insert coin] is DrinkDelivered")
    {
        // Act
        unit.select_drink();
        unit.insert_coin();

        // Assert
        CoutRedirect cr;
        unit.take_drink();
        REQUIRE_THAT(cr.get_output(), ContainsSubstring("Enjoy your drink!"));
    }
}

struct StateChangeNotifier : StateNotifier
{
    void notify(State state) override { states.push_back(state); }
    std::vector<State> states;
};

TEST_CASE ("ObservableStateMachine")
{
    StateChangeNotifier notifier;
    ObservableStateMachine unit{notifier};

    SECTION ("State after [insert coin -> select drink] is DrinkDelivered")
    {
        // Act
        unit.insert_coin();
        unit.select_drink();

        // Assert
        REQUIRE(notifier.states.back() == State::DrinkDelivered);
    }

    SECTION ("State after [select drink -> insert coin] is DrinkDelivered")
    {
        // Act
        unit.select_drink();
        unit.insert_coin();

        // Assert
        REQUIRE(notifier.states.back() == State::DrinkDelivered);
    }
}