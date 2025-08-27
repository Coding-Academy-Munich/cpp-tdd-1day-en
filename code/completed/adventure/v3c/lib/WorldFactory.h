// Copyright (c) 2023-2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V3C_LIB_WORLDFACTORY_H
#define COMPLETED_ADVENTURE_V3C_LIB_WORLDFACTORY_H

#include "LocationData.h"
#include "World.h"
#include <string>
#include <vector>

namespace adventure::v3c
{

class WorldFactory
{
public:
    static World create(
        const std::vector<data::LocationData>& locationDataVector,
        const std::string& initialLocationName
    );

    static World create(const std::vector<data::LocationData>& locationDataVector);
};
} // namespace adventure::v3c

#endif // COMPLETED_ADVENTURE_V3C_LIB_WORLDFACTORY_H
