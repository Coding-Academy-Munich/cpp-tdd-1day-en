// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "cout_redirect.h"
#include "fun_state_interact.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <vector>

using Catch::Matchers::ContainsSubstring;

TEST_CASE ("Testing return value of a pure function")
{
    // No arrange necessary
    // Act
    int result{add(1, 2)};
    // Assert
    REQUIRE(result == 3);

    // Or
    REQUIRE(add(1, 2) == 3);
}

TEST_CASE ("Testing stateful class")
{
    // Arrange
    Adder adder;
    // Act
    adder.add(1, 2);
    // Assert
    REQUIRE(adder.get_result() == 3);
}

// Need a spy to test the interaction
struct AdderSpy : public AbstractAdder
{
    std::vector<std::pair<int, int>> calls;

    void add(int x, int y) override { calls.push_back({x, y}); };
};

TEST_CASE ("Testing interaction with a class")
{
    // Arrange
    AdderSpy mock_adder;
    InteractionAdder interaction_adder{mock_adder};

    // Act
    interaction_adder.add(1, 2);

    // Assert
    REQUIRE(mock_adder.calls.size() == 1);
    REQUIRE(mock_adder.calls[0].first == 1);
    REQUIRE(mock_adder.calls[0].second == 2);
}

TEST_CASE ("Testing interaction with function with side effects")
{
    CoutRedirect cr;
    add_and_print(1, 2);

    REQUIRE_THAT(cr.get_output(), ContainsSubstring("3"));
}
