// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "LocationData.h"
#include "Pawn.h"
#include "World.h"
#include "WorldFactory.h"
#include <iostream>

using namespace adventure::data;
using namespace adventure::v4c;

int main()
{
    World world = WorldFactory::create(simpleLocationDataVector);
    std::cout << world << '\n';
    world = WorldFactory::create(dungeonLocationDataVector);
    std::cout << world << '\n';
    Pawn pawn {"Test Pawn", GetInitialLocation(world)};

    return 0;
}
