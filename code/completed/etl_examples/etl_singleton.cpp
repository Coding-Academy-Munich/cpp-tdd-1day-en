// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "etl_singleton.h"
#include <iostream>

void GameEngine::load_level()
{
    std::cout << "Loading the game level\n";
    level_loaded = true;
}

void GameEngine::load_characters()
{
    std::cout << "Loading the game characters\n";
    characters_loaded = true;
}

void GameEngine::run()
{
    if (!level_loaded) {
        std::cerr << "Level not loaded\n";
        return;
    }
    if (!characters_loaded) {
        std::cerr << "Characters not loaded\n";
        return;
    }
    std::cout << "Running the game engine\n";
}
