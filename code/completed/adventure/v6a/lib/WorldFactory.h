// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V6A_LIB_WORLDFACTORY_H
#define COMPLETED_ADVENTURE_V6A_LIB_WORLDFACTORY_H

#include "LocationData.h"
#include "World.h"
#include <string>
#include <vector>

namespace adventure::v6a {

class WorldFactory {
public:
    static World create(const std::vector<data::LocationData>& locationDataVector,
        const std::string& initialLocationName);

    static World create(const std::vector<data::LocationData>& locationDataVector);
};
} // namespace adventure::v6a

#endif // COMPLETED_ADVENTURE_V6A_LIB_WORLDFACTORY_H
