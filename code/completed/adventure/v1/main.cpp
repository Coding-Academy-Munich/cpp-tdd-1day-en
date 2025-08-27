// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "LocationData.h"
#include "World.h"
#include <iostream>

using namespace adventure;

int main()
{
    v1::World world = v1::World(data::simpleLocationDataVector);
    std::cout << world << '\n';
    for (const auto& [name, location] : world.GetLocations()) {
        std::cout << location << '\n';
    }

    return 0;
}
