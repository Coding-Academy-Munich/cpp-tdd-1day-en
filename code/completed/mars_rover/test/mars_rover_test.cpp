#include <memory>
#include <catch2/catch_test_macros.hpp>

#include "mars_rover.h"

using namespace rover;

// This test file is structured to follow the TDD "Red-Green-Refactor" cycle.
// Each TEST_CASE represents a small, incremental step in functionality.

TEST_CASE("1. Rover Initialization", "[rover]")
{
    // RED: This test fails initially because the Rover class doesn't exist.
    // GREEN: Create the Rover class with a constructor that sets a default state.
    // REFACTOR: The initial implementation is simple; no refactoring needed yet.

    auto grid = std::make_shared<Grid>(100, 100);
    Rover rover(grid);

    REQUIRE(rover.getPosition() == Point{0, 0});
    REQUIRE(rover.getDirection() == Direction::N);
}

TEST_CASE("2. Rover Can Turn", "[rover]")
{
    auto grid = std::make_shared<Grid>(100, 100);
    Rover rover(grid, {0, 0}, Direction::N);

    SECTION("Turning right cycles through directions N -> E -> S -> W -> N")
    {
        // RED: This test fails because there's no way to send a 'R' command.
        // GREEN: Implement an executeCommands method and add logic for 'R'.
        // REFACTOR: The turning logic might start as a messy if-else. Refactor to
        // a switch statement.

        rover.executeCommands("R");
        REQUIRE(rover.getDirection() == Direction::E);
        rover.executeCommands("R");
        REQUIRE(rover.getDirection() == Direction::S);
        rover.executeCommands("R");
        REQUIRE(rover.getDirection() == Direction::W);
        rover.executeCommands("R");
        REQUIRE(rover.getDirection() == Direction::N);
    }

    SECTION("Turning left cycles through directions N -> W -> S -> E -> N")
    {
        // RED: This test fails as the 'L' command is not yet implemented.
        // GREEN: Add the 'L' case to the command handler.
        // REFACTOR: The turning logic should now be robust. An enum for Direction
        // is a good refactor.

        rover.executeCommands("L");
        REQUIRE(rover.getDirection() == Direction::W);
        rover.executeCommands("L");
        REQUIRE(rover.getDirection() == Direction::S);
        rover.executeCommands("L");
        REQUIRE(rover.getDirection() == Direction::E);
        rover.executeCommands("L");
        REQUIRE(rover.getDirection() == Direction::N);
    }
}

TEST_CASE("3. Rover Can Move Forward", "[rover]")
{
    auto grid = std::make_shared<Grid>(100, 100);

    SECTION("Moves North")
    {
        // RED: Fails because the 'M' command isn't implemented.
        // GREEN: Add logic to change the rover's position based on its direction.
        // REFACTOR: The initial movement logic is likely simple and fine for now.

        Rover rover(grid, {10, 10}, Direction::N);
        rover.executeCommands("M");
        REQUIRE(rover.getPosition() == Point{10, 11});
    }

    SECTION("Moves South")
    {
        Rover rover(grid, {10, 10}, Direction::S);
        rover.executeCommands("M");
        REQUIRE(rover.getPosition() == Point{10, 9});
    }

    SECTION("Moves East")
    {
        Rover rover(grid, {10, 10}, Direction::E);
        rover.executeCommands("M");
        REQUIRE(rover.getPosition() == Point{11, 10});
    }

    SECTION("Moves West")
    {
        Rover rover(grid, {10, 10}, Direction::W);
        rover.executeCommands("M");
        REQUIRE(rover.getPosition() == Point{9, 10});
    }
}

TEST_CASE("4. Rover Can Execute a Sequence of Commands", "[rover]")
{
    // This test ensures that the command processing loop works correctly.
    auto grid = std::make_shared<Grid>(100, 100);
    Rover rover(grid, {5, 5}, Direction::N);

    // A more complex sequence of commands to test the whole system together.
    rover.executeCommands("RMMMLM");

    // Expected path:
    // Start at {5,5} N
    // R -> {5,5} E
    // M -> {6,5} E
    // M -> {7,5} E
    // M -> {8,5} E
    // L -> {8,5} N
    // M -> {8,6} N
    REQUIRE(rover.getPosition() == Point{8, 6});
    REQUIRE(rover.getDirection() == Direction::N);
}


TEST_CASE("5. Rover Wraps Around the Grid Edges", "[rover][design-driver]")
{
    // *** THIS IS THE KEY TEST CASE FOR DRIVING DESIGN ***
    // RED: This test will fail. The rover will move to y=10 or x=10, not y=0 or
    // x=0. The existing Rover design has no concept of a "grid boundary".
    //
    // GREEN: The simplest way to make this pass is to add grid dimensions to the
    // Rover's move() method. But that feels wrong.
    //
    // REFACTOR: This test reveals a design flaw. The Rover shouldn't be
    // responsible for knowing the rules of the world. This is the "Aha!" moment
    // where you introduce the Grid class. The Rover now asks the Grid where to go
    // next. The Rover class is simplified: it just knows how to turn and ask to
    // move. The Grid class is created: it knows the boundaries and how to wrap
    // positions. This leads to a much better, more decoupled design.

    auto grid = std::make_shared<Grid>(10, 10);

    SECTION("Wraps from North to South edge")
    {
        Rover rover(grid, {5, 9}, Direction::N);
        rover.executeCommands("M");
        REQUIRE(rover.getPosition() == Point{5, 0});
    }

    SECTION("Wraps from South to North edge")
    {
        Rover rover(grid, {5, 0}, Direction::S);
        rover.executeCommands("M");
        REQUIRE(rover.getPosition() == Point{5, 9});
    }

    SECTION("Wraps from East to West edge")
    {
        Rover rover(grid, {9, 5}, Direction::E);
        rover.executeCommands("M");
        REQUIRE(rover.getPosition() == Point{0, 5});
    }

    SECTION("Wraps from West to East edge")
    {
        Rover rover(grid, {0, 5}, Direction::W);
        rover.executeCommands("M");
        REQUIRE(rover.getPosition() == Point{9, 5});
    }
}
