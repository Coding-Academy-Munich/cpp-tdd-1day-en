// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "recipes_sk.h"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace recipes_sk
{

One Many::getThing(const std::string& aaa)
{
    for (auto& thing : foo)
    {
        if (thing.getAaa() == aaa)
        {
            return thing;
        }
    }
    throw std::runtime_error("Recipe " + aaa + " not found!");
}

std::vector<One> Many::getThings1(const std::string& bbb)
{
    std::vector<One> result;
    for (auto& thing : foo)
    {
        auto& thingBbb{thing.getBbb()};
        if (std::find(std::cbegin(thingBbb), std::cend(thingBbb), bbb) !=
            std::cend(thingBbb))
        {
            result.push_back(thing);
        }
    }
    return result;
}

std::vector<One> Many::getThings2(int ddd)
{
    std::vector<One> result;
    for (auto& thing : foo)
    {
        if (thing.getDdd() == ddd)
        { // Assuming One has a getter for ddd
            result.push_back(thing);
        }
    }
    return result;
}

std::vector<One> Many::getThings3(int ddd)
{
    std::vector<One> result;
    for (auto& thing : foo)
    {
        std::optional<int> dddValue = thing.getDdd();
        if (dddValue && *dddValue >= ddd)
        {
            result.push_back(thing);
        }
    }
    return result;
}
} // namespace recipes_sk
