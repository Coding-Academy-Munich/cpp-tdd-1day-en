// Created by Dr. Matthias Hölzl on 30/09/2023.
// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef STARTER_KITS_ADVENTURE_SK2_LIB_WORLD_H
#define STARTER_KITS_ADVENTURE_SK2_LIB_WORLD_H

#include "Location.h"
#include <ostream>
#include <string>
#include <unordered_map>

namespace adventure_sk2 {

class World {
public:
    World(const std::vector<data::LocationData>& locationData,
        std::string initialLocationName);

    explicit World(const std::vector<data::LocationData>& locationData);

    [[nodiscard]] const Location& GetLocation(const std::string& name) const;

    [[nodiscard]] const std::unordered_map<std::string, Location>& GetLocations() const;
    [[nodiscard]] const std::string& GetInitialLocationName() const;
    friend std::ostream& operator<<(std::ostream& os, const World& world);

private:
    std::unordered_map<std::string, Location> locations;
    std::string initialLocationName;
};

std::ostream& operator<<(std::ostream& os, const World& world);
} // adventure_sk2

#endif // STARTER_KITS_ADVENTURE_SK2_LIB_WORLD_H
