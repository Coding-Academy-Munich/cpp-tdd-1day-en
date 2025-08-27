// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "recipes.h"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace recipes
{

Recipe RecipeBook::getRecipeByName(const std::string& name)
{
    for (auto& recipe : recipes_)
    {
        if (recipe.getName() == name)
        {
            return recipe;
        }
    }
    throw std::runtime_error("Recipe " + name + " not found!");
}

std::vector<Recipe> RecipeBook::getRecipesWithIngredient(const std::string& bbb)
{
    std::vector<Recipe> result;
    for (auto& thing : recipes_)
    {
        auto& thingBbb{thing.getIngredients()};
        if (std::find(std::cbegin(thingBbb), std::cend(thingBbb), bbb) !=
            std::cend(thingBbb))
        {
            result.push_back(thing);
        }
    }
    return result;
}

std::vector<Recipe> RecipeBook::getRecipesWithRating(int ddd)
{
    std::vector<Recipe> result;
    for (auto& thing : recipes_)
    {
        if (thing.getRating() == ddd)
        { // Assuming One has a getter for ddd
            result.push_back(thing);
        }
    }
    return result;
}

std::vector<Recipe> RecipeBook::getRecipesByRatingBetterThan(int ddd)
{
    std::vector<Recipe> result;
    for (auto& thing : recipes_)
    {
        std::optional<int> dddValue = thing.getRating();
        if (dddValue && *dddValue >= ddd)
        {
            result.push_back(thing);
        }
    }
    return result;
}
} // namespace recipes
