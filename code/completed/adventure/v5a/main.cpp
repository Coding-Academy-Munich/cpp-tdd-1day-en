// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "LocationData.h"
#include "Player.h"
#include "World.h"
#include "WorldFactory.h"
#include "actions/MoveAction.h"
#include <iostream>

using namespace adventure::data;
using namespace adventure::v5a;

int main()
{
    World world {WorldFactory::create(dungeonLocationDataVector)};
    Player player {"Test Player", world.GetInitialLocation()};
    std::cout << player << '\n';
    std::cout << player.GetPossibleActions() << '\n';
    player.TakeTurn();
    std::cout << player << '\n';

    return 0;
}
