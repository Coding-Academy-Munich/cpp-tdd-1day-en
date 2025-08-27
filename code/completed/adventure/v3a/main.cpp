// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "LocationData.h"
#include "World.h"
#include <iostream>

using namespace adventure::data;
using namespace adventure::v3a;

int main()
{
    World world = World(simpleLocationDataVector);
    std::cout << world << '\n';
    world = World(dungeonLocationDataVector);
    std::cout << world << '\n';

    return 0;
}
