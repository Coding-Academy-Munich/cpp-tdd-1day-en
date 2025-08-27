// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "recipes_sk.h"
#include <catch2/catch_test_macros.hpp>

using namespace recipes_sk;

TEST_CASE ("Recipe")
{
    SECTION ("Has no rating by default")
    {
        One recipe{"Test Recipe", {}, ""};
        CHECK(recipe.getDdd() == std::nullopt);
    }
}

TEST_CASE ("Recipe Book")
{
    Many book;
    book.addThing(One("recipe 1", {"ingredient 1", "ingredient 2"}, "instructions...", 5));
    book.addThing(One("recipe 2", {"ingredient 1", "ingredient 3"}, "do this...", 4));
    book.addThing(One("recipe 3", {"ingredient 2", "ingredient 3"}, "do that...", 3));

    SECTION ("Get recipe by name")
    {
        auto recipe2{book.getThing("recipe 2")};
        CHECK(recipe2.getAaa() == "recipe 2");
    }

    SECTION ("Get recipes by ingredient")
    {
        auto recipes{book.getThings1("ingredient 2")};
        CHECK(recipes.size() == 2);
        CHECK(recipes[0].getAaa() == "recipe 1");
        CHECK(recipes[1].getAaa() == "recipe 3");
    }

    SECTION ("Get recipes by rating")
    {
        auto recipes{book.getThings2(4)};
        CHECK(recipes.size() == 1);
        CHECK(recipes[0].getAaa() == "recipe 2");
    }

    SECTION ("Get recipes by rating or better")
    {
        auto recipes{book.getThings3(4)};
        CHECK(recipes.size() == 2);
        CHECK(recipes[0].getAaa() == "recipe 1");
        CHECK(recipes[1].getAaa() == "recipe 2");
    }
}