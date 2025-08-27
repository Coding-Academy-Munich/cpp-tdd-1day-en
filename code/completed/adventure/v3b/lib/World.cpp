// Copyright (c) 2023-2024 Dr. Matthias Hölzl. All rights reserved.

#include "World.h"

#include <utility>

namespace adventure::v3b
{

World::World(
    const std::vector<data::LocationData>& locationDataVector,
    std::string initialLocationName
)
    : locations{}, initialLocationName{std::move(initialLocationName)}
{
    locations.reserve(locationDataVector.size());
    for (const auto& locationData : locationDataVector)
    {
        locations.emplace(locationData.name, locationData);
    }
    for (const auto& locationData : locationDataVector)
    {
        for (const auto& [direction, target] : locationData.connections)
        {
            GetLocation(locationData.name)
                .SetConnectedLocation(direction, GetLocation(target));
        }
    }
}

World::World(const std::vector<data::LocationData>& locationDataVector)
    : World{locationDataVector, locationDataVector[0].name}
{}

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

std::ostream& operator<<(std::ostream& os, const World& world)
{
    os << "World\n"
       << "  locations: [";
    std::string separator{};
    for (const auto& [name, location] : world.GetLocations())
    {
        os << separator << name;
        separator = ", ";
    }
    os << "]\n"
       << "  initial location: " << world.GetInitialLocationName();
    return os;
}
} // namespace adventure::v3b
