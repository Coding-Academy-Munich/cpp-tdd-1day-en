// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "World.h"

#include <utility>

namespace adventure::v5a {

World::World(std::string initialLocationName)
    : locations {}
    , initialLocationName {std::move(initialLocationName)}
{
}

const std::unordered_map<std::string, Location>& World::GetLocations() const
{
    return locations;
}

const std::string& World::GetInitialLocationName() const { return initialLocationName; }

const Location& World::GetLocation(const std::string& name) const
{
    return locations.at(name);
}

Location& World::GetLocation(const std::string& name) { return locations.at(name); }

Location& World::GetInitialLocation() { return GetLocation(GetInitialLocationName()); }

const Location& GetInitialLocation(const World& world)
{
    return world.GetLocation(world.GetInitialLocationName());
}

std::ostream& operator<<(std::ostream& os, const World& world)
{
    os << "World\n"
       << "  locations: [";
    std::string separator {};
    for (const auto& [name, location] : world.GetLocations()) {
        os << separator << name;
        separator = ", ";
    }
    os << "]\n"
       << "  initial location: " << world.GetInitialLocationName();
    return os;
}
} // namespace adventure::v5a
