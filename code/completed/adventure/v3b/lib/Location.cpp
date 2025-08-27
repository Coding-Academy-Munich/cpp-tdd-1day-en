// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include <utility>

namespace adventure::v3b {
Location::Location(std::string name, std::string description)
    : name {std::move(name)}
    , description {std::move(description)}
{
}

Location::Location(const data::LocationData& locationData)
    : Location {locationData.name, locationData.description}
{
}

const Location& Location::GetConnectedLocation(const std::string& direction) const
{
    return *connectedLocations.at(direction);
}

void Location::SetConnectedLocation(const std::string& direction, Location& location)
{
    connectedLocations[direction] = &location;
}

std::vector<std::string> Location::GetConnectedDirections() const
{
    std::vector<std::string> result {};
    result.reserve(connectedLocations.size());
    for (const auto& [direction, location] : connectedLocations) {
        result.push_back(direction);
    }
    return result;
}

bool Location::operator==(const Location& rhs) const
{
    return name == rhs.name && description == rhs.description;
}

bool Location::operator!=(const Location& rhs) const { return !(rhs == *this); }

std::ostream& operator<<(std::ostream& os, const Location& location)
{
    os << "Location with name '" << location.GetName() << "' and Description '"
       << location.GetDescription() << "'";
    return os;
}
} // namespace adventure::v3b