// Copyright (c) 2023-2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V3B_WORLD_H
#define COMPLETED_ADVENTURE_V3B_WORLD_H

#include "Location.h"
#include <ostream>
#include <string>
#include <unordered_map>

namespace adventure::v3b
{

class World
{
public:
    World(
        const std::vector<data::LocationData>& locationDataVector,
        std::string initialLocationName
    );
    explicit World(const std::vector<data::LocationData>& locationDataVector);

    World(const World&) = delete;
    World(World&&) noexcept = default;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = default;

    [[nodiscard]] const Location& GetLocation(const std::string& name) const;
    [[nodiscard]] Location& GetLocation(const std::string& name);

    [[nodiscard]] const std::unordered_map<std::string, Location>& GetLocations() const;
    [[nodiscard]] const std::string& GetInitialLocationName() const;

private:
    std::unordered_map<std::string, Location> locations;
    std::string initialLocationName;
};

std::ostream& operator<<(std::ostream& os, const World& world);
} // namespace adventure::v3b

#endif // COMPLETED_ADVENTURE_V3B_WORLD_H
