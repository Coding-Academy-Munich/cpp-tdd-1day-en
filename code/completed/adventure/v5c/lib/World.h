// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5C_WORLD_H
#define COMPLETED_ADVENTURE_V5C_WORLD_H

#include "Location.h"
#include <ostream>
#include <string>
#include <unordered_map>

namespace adventure::v5c {

class World {
public:
    World(const World&) = delete;
    World(World&&) noexcept = default;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = default;

    [[nodiscard]] const Location& GetLocation(const std::string& name) const;
    [[nodiscard]] Location& GetLocation(const std::string& name);
    [[nodiscard]] Location& GetInitialLocation();

    [[nodiscard]] const std::unordered_map<std::string, Location>& GetLocations() const;
    [[nodiscard]] const std::string& GetInitialLocationName() const;

private:
    explicit World(std::string initialLocationName);
    friend class WorldFactory;

    std::unordered_map<std::string, Location> locations;
    std::string initialLocationName;
};

const Location& GetInitialLocation(const World& world);

std::ostream& operator<<(std::ostream& os, const World& world);
} // namespace adventure::v5c

#endif // COMPLETED_ADVENTURE_V5C_WORLD_H
