// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "recipes.h"
#include <iostream>

using namespace recipes;

int main()
{
    RecipeBook book;
    book.addRecipe(
        Recipe("recipe 1", {"ingredient 1", "ingredient 2"}, "instructions...", 5)
    );
    book.addRecipe(Recipe("recipe 2", {"ingredient 1", "ingredient 3"}, "do this...", 4));
    book.addRecipe(Recipe("recipe 3", {"ingredient 2", "ingredient 3"}, "do that...", 3));

    auto recipe2{book.getRecipeByName("recipe 2")};
    std::cout << "Recipe 2: " << recipe2.getName() << '\n';

    auto recipes{book.getRecipesWithIngredient("ingredient 2")};
    std::cout << "Recipes with ingredient 2:\n";
    for (const auto& recipe : recipes)
    {
        std::cout << "  Recipe: " << recipe.getName() << '\n';
    }

    recipes = book.getRecipesWithRating(4);
    std::cout << "Recipes with rating 4:\n";
    for (const auto& recipe : recipes)
    {
        std::cout << "  Recipe: " << recipe.getName() << '\n';
    }

    recipes = book.getRecipesByRatingBetterThan(4);
    std::cout << "Recipes with rating 4 or better:\n";
    for (const auto& recipe : recipes)
    {
        std::cout << "  Recipe: " << recipe.getName() << '\n';
    }
}
