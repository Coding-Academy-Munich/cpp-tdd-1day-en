// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "game.h"

int main()
{
    std::vector<adv::Room> rooms{
        {"Grand Hall",
         "You are in the Grand Hall. It is a vast, echoing chamber."},
        {"Armoury",
         "You are in the Armoury. Racks of dusty weapons line the walls."}};
    adv::Game game{rooms};
    game.run();
}
