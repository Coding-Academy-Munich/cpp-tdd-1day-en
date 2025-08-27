// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V3A_WORLD_H
#define COMPLETED_ADVENTURE_V3A_WORLD_H

#include "Location.h"
#include <ostream>
#include <string>
#include <unordered_map>

namespace adventure::v3a {

struct Connection {
    const Location* from;
    std::string direction;
    const Location* to;

    Connection(
        const Location* pLocation, std::string basicString, const Location* pLocation1);
    bool operator==(const Connection& rhs) const;
    bool operator!=(const Connection& rhs) const;
};

class World {
public:
    World(const std::vector<data::LocationData>& locationDataVector,
        std::string initialLocationName);

    explicit World(const std::vector<data::LocationData>& locationDataVector);
    World(const World&) = delete;
    World(World&&) noexcept = default;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = default;

    [[nodiscard]] const Location& GetLocation(const std::string& name) const;
    [[nodiscard]] const std::vector<Connection>& GetConnections() const;
    [[nodiscard]] const Location& GetConnectedLocation(
        const Location& location, const std::string& direction) const;

    [[nodiscard]] const std::unordered_map<std::string, Location>& GetLocations() const;
    [[nodiscard]] const std::string& GetInitialLocationName() const;

private:
    std::unordered_map<std::string, Location> locations;
    std::string initialLocationName;
    std::vector<Connection> connections;
};

std::ostream& operator<<(std::ostream& os, const World& world);
} // namespace adventure::v3a

#endif // COMPLETED_ADVENTURE_V3A_WORLD_H
