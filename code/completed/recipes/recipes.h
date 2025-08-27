// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef RECIPES_H
#define RECIPES_H

#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace recipes
{

class Recipe
{
public:
    Recipe(
        std::string name, const std::vector<std::string>& ingredients,
        std::string instructions, std::optional<int> rating = std::nullopt
    )
        : name_{std::move(name)},
          ingredients_{ingredients},
          instructions_{std::move(instructions)},
          rating_{rating}
    {}

    std::string getName() const { return name_; }

    const std::vector<std::string>& getIngredients() const { return ingredients_; }

    std::string getInstructions() const { return instructions_; }

    std::optional<int> getRating() const { return rating_; }

private:
    std::string name_;
    std::vector<std::string> ingredients_;
    std::string instructions_;
    std::optional<int> rating_;
};

class RecipeBook
{
public:
    void addRecipe(Recipe thing) { recipes_.push_back(thing); }

    Recipe getRecipeByName(const std::string& name);

    std::vector<Recipe> getRecipesWithIngredient(const std::string& bbb);

    std::vector<Recipe> getRecipesWithRating(int ddd);

    std::vector<Recipe> getRecipesByRatingBetterThan(int ddd);

private:
    std::vector<Recipe> recipes_;
};
} // namespace recipes

#endif // RECIPES_H
