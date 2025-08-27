// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include <list>


#include "todo_list.h"

#include <catch2/catch_test_macros.hpp>

#include "catch2/internal/catch_list.hpp"

using namespace tlc_sk;

TEST_CASE("Unit tests")
{
    SECTION("New todo list is empty")
    {
        TodoList todo_list;
        REQUIRE(todo_list.get_tasks().size() == 0);
    }

    SECTION("Add task adds correct task")
    {
        TodoList todo_list;
        todo_list.add_task("Test adding a task");
        REQUIRE(todo_list.get_tasks().size() == 1);
        REQUIRE(todo_list.get_tasks()[0].description == "Test adding a task");
    }

    SECTION("Task is initially not completed")
    {
        TodoList todo_list;
        todo_list.add_task("Test adding a task");
        REQUIRE(todo_list.get_tasks()[0].completed == false);
    }

    SECTION("Mark task as complete works")
    {
        TodoList todo_list;
        todo_list.add_task("Test marking a task as complete");
        todo_list.mark_as_complete("Test marking a task as complete");
        REQUIRE(todo_list.get_tasks()[0].completed == true);
    }
}
