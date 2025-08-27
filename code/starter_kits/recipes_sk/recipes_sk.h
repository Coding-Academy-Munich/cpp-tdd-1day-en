// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef RECIPES_SK_H
#define RECIPES_SK_H

#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace recipes_sk
{

// A single recipe
class One
{
public:
    One(std::string aaa, const std::vector<std::string>& bbb, std::string ccc,
        std::optional<int> ddd = std::nullopt)
        : aaa{std::move(aaa)}, bbb{bbb}, ccc{std::move(ccc)}, ddd{ddd}
    {}

    // Return the name of the recipe
    std::string getAaa() const { return aaa; }

    // Return the list of ingredients
    const std::vector<std::string>& getBbb() const { return bbb; }

    // Return the instructions
    std::string getCcc() const { return ccc; }

    // Return the rating
    std::optional<int> getDdd() const { return ddd; }

private:
    std::string aaa;              // name
    std::vector<std::string> bbb; // list of ingredients
    std::string ccc;              // instructions
    std::optional<int> ddd;       // rating
};

// A Book with recipes
class Many
{
private:
    // List of recipes
    std::vector<One> foo;

public:
    // Add a recipe
    void addThing(One thing) { foo.push_back(thing); }

    // Return a recipe by name
    One getThing(const std::string& aaa);

    // Return all recipes with a given ingredient
    std::vector<One> getThings1(const std::string& bbb);

    // Return all recipes with a rating equal to ddd
    std::vector<One> getThings2(int ddd);

    // Return all recipes with a rating greater or equal to ddd
    std::vector<One> getThings3(int ddd);
};

} // namespace recipes_sk

#endif // RECIPES_SK_H
