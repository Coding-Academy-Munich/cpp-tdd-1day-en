// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V1_WORLD_H
#define COMPLETED_ADVENTURE_V1_WORLD_H

#include "Location.h"
#include <ostream>
#include <string>
#include <unordered_map>

namespace adventure::v1 {

class World {
public:
    World(const std::vector<data::LocationData>& locationData,
        std::string initialLocationName);

    explicit World(const std::vector<data::LocationData>& locationData);

    [[nodiscard]] const std::unordered_map<std::string, Location>& GetLocations() const;
    [[nodiscard]] const std::string& GetInitialLocationName() const;

private:
    std::unordered_map<std::string, Location> locations;
    std::string initialLocationName;
};

std::ostream& operator<<(std::ostream& os, const World& world);
} // namespace adventure::v1

#endif // COMPLETED_ADVENTURE_V1_WORLD_H
