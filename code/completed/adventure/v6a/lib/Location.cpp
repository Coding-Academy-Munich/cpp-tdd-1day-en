// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include <utility>

namespace adventure::v6a {
Location::Location(std::string name, std::string description)
    : name_ {std::move(name)}, description_ {std::move(description)} { }

Location::Location(const data::LocationData& locationData)
    : Location {locationData.name, locationData.description} { }

const Location& Location::GetConnectedLocation(const std::string& direction) const {
    return *connectedLocations_.at(direction);
}

Location& Location::GetConnectedLocation(const std::string& direction) {
    return *connectedLocations_.at(direction);
}

void Location::SetConnectedLocation(const std::string& direction, Location& location) {
    connectedLocations_[direction] = &location;
}

std::vector<std::string> Location::GetConnectedDirections() const {
    std::vector<std::string> result {};
    result.reserve(connectedLocations_.size());
    for (const auto& [direction, location] : connectedLocations_) {
        result.push_back(direction);
    }
    return result;
}

bool Location::operator==(const Location& rhs) const {
    return name_ == rhs.name_ && description_ == rhs.description_;
}
bool Location::operator!=(const Location& rhs) const { return !(rhs == *this); }

std::ostream& operator<<(std::ostream& os, const Location& location) {
    os << "Location with name '" << location.GetName() << "' and Description '"
       << location.GetDescription() << "'";
    return os;
}
} // namespace adventure::v6a