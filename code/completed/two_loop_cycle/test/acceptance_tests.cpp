// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "todo_list.h"

#include <catch2/catch_test_macros.hpp>

using namespace tlc_sk;

// The two following acceptance tests have equal functionality but are written in
// different styles.

// The first test shows the traditional Catch2 testing style.
// The second test is written using BDD style (Given/When/Then).

// Traditional Catch2 style
TEST_CASE("Managing a todo list (traditional style)", "[TodoList]")
{
    // Arrange
    TodoList list;

    SECTION("Adding tasks and completing them")
    {
        // Act 1: Add tasks
        list.add_task("Implement Two-Loop TDD");
        list.add_task("Write workshop slides");

        // Assert 1
        auto tasks1 = list.get_tasks();
        REQUIRE(tasks1.size() == 2);
        REQUIRE(tasks1[0].description == "Implement Two-Loop TDD");
        REQUIRE(tasks1[0].completed == false);

        // Act 2: Complete a task
        list.mark_as_complete("Write workshop slides");
        // Assert 2
        auto tasks2 = list.get_tasks();
        auto completed_task =
            std::find_if(tasks2.begin(), tasks2.end(), [](const Task& task)
                         { return task.description == "Write workshop slides"; });

        REQUIRE(completed_task != tasks2.end());
        REQUIRE(completed_task->completed == true);
    }
}

// BDD style using SCENARIO/GIVEN/WHEN/THEN
SCENARIO("Managing a todo list", "[TodoList][BDD]")
{
    GIVEN("An empty todo list")
    {
        TodoList list;

        WHEN("I add two tasks")
        {
            list.add_task("Implement Two-Loop TDD");
            list.add_task("Write workshop slides");

            THEN("The list should contain both tasks")
            {
                auto tasks = list.get_tasks();
                REQUIRE(tasks.size() == 2);
                REQUIRE(tasks[0].description == "Implement Two-Loop TDD");
                REQUIRE(tasks[0].completed == false);
            }

            AND_WHEN("I mark one task as complete")
            {
                list.mark_as_complete("Write workshop slides");

                THEN("That task should be marked as completed")
                {
                    auto tasks = list.get_tasks();
                    auto completed_task = std::find_if(
                        tasks.begin(), tasks.end(), [](const Task& task)
                        { return task.description == "Write workshop slides"; });
                    REQUIRE(completed_task != tasks.end());
                    REQUIRE(completed_task->completed == true);
                }
                AND_THEN("The other task should remain incomplete")
                {
                    auto tasks = list.get_tasks();
                    auto incomplete_task = std::find_if(
                        tasks.begin(), tasks.end(), [](const Task& task)
                        { return task.description == "Implement Two-Loop TDD"; });

                    REQUIRE(incomplete_task != tasks.end());
                    REQUIRE(incomplete_task->completed == false);
                }
            }
        }
    }
}
