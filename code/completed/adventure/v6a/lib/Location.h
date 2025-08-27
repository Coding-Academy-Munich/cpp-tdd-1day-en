// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V6A_LOCATION_H
#define COMPLETED_ADVENTURE_V6A_LOCATION_H

#include "LocationData.h"
#include <ostream>
#include <string>

namespace adventure::v6a {

class Location {
public:
    Location(std::string name, std::string description);
    explicit Location(const data::LocationData& locationData);

    [[nodiscard]] const std::string& GetName() const { return name_; }
    [[nodiscard]] const std::string& GetDescription() const { return description_; }

    [[nodiscard]] const Location& GetConnectedLocation(
        const std::string& direction) const;
    [[nodiscard]] Location& GetConnectedLocation(const std::string& direction);
    void SetConnectedLocation(const std::string& direction, Location& location);
    [[nodiscard]] std::vector<std::string> GetConnectedDirections() const;

    bool operator==(const Location& rhs) const;
    bool operator!=(const Location& rhs) const;

private:
    std::string name_;
    std::string description_;
    std::unordered_map<std::string, Location*> connectedLocations_ {};
};

std::ostream& operator<<(std::ostream& os, const Location& location);
} // namespace adventure::v6a

#endif // COMPLETED_ADVENTURE_V6A_LOCATION_H
