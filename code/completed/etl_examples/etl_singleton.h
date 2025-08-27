// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ETL_EXAMPLES_ETL_SINGLETON_H
#define COMPLETED_ETL_EXAMPLES_ETL_SINGLETON_H

#include "etl/singleton.h"

class GameEngine
{
public:
    void load_level();
    void load_characters();
    void run();

private:
    bool level_loaded{false};
    bool characters_loaded{false};
};

using GameEngineSingleton = etl::singleton<GameEngine>;

#endif // COMPLETED_ETL_EXAMPLES_ETL_SINGLETON_H
