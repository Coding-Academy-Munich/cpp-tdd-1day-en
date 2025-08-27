// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "LocationData.h"
#include "World.h"
#include <iostream>

using namespace adventure;

int main()
{
    v2::World world = v2::World(data::simpleLocationDataVector);
    std::cout << world << '\n';
    for (const auto& [name, location] : world.GetLocations()) {
        std::cout << location << '\n';
    }
    std::cout << world.GetLocation("Room 1") << '\n';
    std::cout << world.GetLocation("Room 2") << '\n';

    return 0;
}
