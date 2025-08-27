// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "World.h"

#include <utility>

namespace adventure::v3a {

Connection::Connection(const Location* from, std::string direction, const Location* to)
    : from {from}
    , direction {std::move(direction)}
    , to {to}
{
}

bool Connection::operator==(const Connection& rhs) const
{
    return from == rhs.from && direction == rhs.direction && to == rhs.to;
}

bool Connection::operator!=(const Connection& rhs) const { return !(rhs == *this); }

World::World(const std::vector<data::LocationData>& locationDataVector,
    std::string initialLocationName)
    : locations {}
    , initialLocationName {std::move(initialLocationName)}
{
    locations.reserve(locationDataVector.size());
    for (const auto& locationData : locationDataVector) {
        locations.emplace(locationData.name, locationData);
    }
    for (const auto& locationData : locationDataVector) {
        for (const auto& [direction, target] : locationData.connections) {
            connections.emplace_back(
                &locations.at(locationData.name), direction, &locations.at(target));
        }
    }
}

World::World(const std::vector<data::LocationData>& locationDataVector)
    : World {locationDataVector, locationDataVector[0].name}
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
const std::vector<Connection>& World::GetConnections() const { return connections; }

const Location& World::GetConnectedLocation(
    const Location& location, const std::string& direction) const
{
    for (const auto& [from, dir, to] : connections) {
        if (from == &location && dir == direction) {
            return *to;
        }
    }
    throw std::runtime_error {"No such connection"};
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
       << "  initial location: " << world.GetInitialLocationName() << "\n"
       << "  connections:\n";
    for (const auto& [from, direction, to] : world.GetConnections()) {
        os << "    " << from->GetName() << " --" << direction << "--> " << to->GetName()
           << "\n";
    }
    return os;
}
} // namespace adventure::v3a
