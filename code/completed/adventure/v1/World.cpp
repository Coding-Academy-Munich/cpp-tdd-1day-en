// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "World.h"

#include <utility>

namespace adventure::v1 {

World::World(const std::vector<data::LocationData>& locationData,
    std::string initialLocationName)
    : locations {}
    , initialLocationName {std::move(initialLocationName)}
{
    locations.reserve(locationData.size());
    for (const auto& location : locationData) {
        locations.emplace(location.name, location);
    }
}

World::World(const std::vector<data::LocationData>& locationData)
    : World {locationData, locationData[0].name}
{
}

const std::unordered_map<std::string, Location>& World::GetLocations() const
{
    return locations;
}

const std::string& World::GetInitialLocationName() const { return initialLocationName; }

std::ostream& operator<<(std::ostream& os, const World& world)
{
    os << "World with locations "
       << "[";
    std::string separator {};
    for (const auto& [name, location] : world.GetLocations()) {
        os << separator << name;
        separator = ", ";
    }
    os << "] and initial location '" << world.GetInitialLocationName() << "'";
    return os;
}
}
