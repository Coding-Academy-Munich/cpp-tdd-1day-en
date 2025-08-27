// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "recipes.h"
#include <catch2/catch_test_macros.hpp>

using namespace recipes;

TEST_CASE ("Recipe")
{
    SECTION ("Has no rating by default")
    {
        Recipe recipe{"Test Recipe", {}, ""};
        CHECK(recipe.getRating() == std::nullopt);
    }
}

TEST_CASE ("Recipe Book")
{
    RecipeBook book;
    book.addRecipe(
        Recipe("recipe 1", {"ingredient 1", "ingredient 2"}, "instructions...", 5)
    );
    book.addRecipe(Recipe("recipe 2", {"ingredient 1", "ingredient 3"}, "do this...", 4));
    book.addRecipe(Recipe("recipe 3", {"ingredient 2", "ingredient 3"}, "do that...", 3));

    SECTION ("Get recipe by name")
    {
        auto recipe2{book.getRecipeByName("recipe 2")};
        CHECK(recipe2.getName() == "recipe 2");
    }

    SECTION ("Get recipes by ingredient")
    {
        auto recipes{book.getRecipesWithIngredient("ingredient 2")};
        CHECK(recipes.size() == 2);
        CHECK(recipes[0].getName() == "recipe 1");
        CHECK(recipes[1].getName() == "recipe 3");
    }

    SECTION ("Get recipes by rating")
    {
        auto recipes{book.getRecipesWithRating(4)};
        CHECK(recipes.size() == 1);
        CHECK(recipes[0].getName() == "recipe 2");
    }

    SECTION ("Get recipes by rating or better")
    {
        auto recipes{book.getRecipesByRatingBetterThan(4)};
        CHECK(recipes.size() == 2);
        CHECK(recipes[0].getName() == "recipe 1");
        CHECK(recipes[1].getName() == "recipe 2");
    }
}