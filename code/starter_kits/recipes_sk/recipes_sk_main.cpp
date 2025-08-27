// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "recipes_sk.h"
#include <iostream>

using namespace recipes_sk;

int main()
{
    Many book;
    book.addThing(One("recipe 1", {"ingredient 1", "ingredient 2"}, "instructions...", 5));
    book.addThing(One("recipe 2", {"ingredient 1", "ingredient 3"}, "do this...", 4));
    book.addThing(One("recipe 3", {"ingredient 2", "ingredient 3"}, "do that...", 3));

    auto recipe2{book.getThing("recipe 2")};
    std::cout << "Recipe 2: " << recipe2.getAaa() << '\n';

    auto recipes{book.getThings1("ingredient 2")};
    std::cout << "Recipes with ingredient 2:\n";
    for (const auto& recipe : recipes)
    {
        std::cout << "  Recipe: " << recipe.getAaa() << '\n';
    }

    recipes = book.getThings2(4);
    std::cout << "Recipes with rating 4:\n";
    for (const auto& recipe : recipes)
    {
        std::cout << "  Recipe: " << recipe.getAaa() << '\n';
    }

    recipes = book.getThings3(4);
    std::cout << "Recipes with rating 4 or better:\n";
    for (const auto& recipe : recipes)
    {
        std::cout << "  Recipe: " << recipe.getAaa() << '\n';
    }
}
