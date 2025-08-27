// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "etl_singleton.h"
#include <iostream>
#include <random>

void set_up_level()
{

    GameEngine& engine(GameEngineSingleton::instance());
    engine.load_level();
    std::cout << "Setting up the game level\n";
}

void set_up_characters()
{
    GameEngine& engine(GameEngineSingleton::instance());
    engine.load_characters();
    std::cout << "Setting up the game characters\n";
}

bool set_up_level_first()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    return dis(gen);
}

int main()
{
    GameEngineSingleton::create();

    if (set_up_level_first()) {
        set_up_level();
        set_up_characters();
    } else {
        set_up_characters();
        set_up_level();
    }
    GameEngineSingleton::instance().run();
}