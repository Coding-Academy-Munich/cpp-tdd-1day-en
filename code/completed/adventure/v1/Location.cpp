// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include <utility>

namespace adventure::v1 {
Location::Location(std::string name, std::string description)
    : name {std::move(name)}
    , description {std::move(description)}
{
}

Location::Location(const data::LocationData& locationData)
    : Location {locationData.name, locationData.description}
{
}

const std::string& Location::GetName() const { return name; }
const std::string& Location::GetDescription() const { return description; }

std::ostream& operator<<(std::ostream& os, const Location& location)
{
    os << "Location with name '" << location.GetName() << "' and Description '"
       << location.GetDescription() << "'";
    return os;
}
} // namespace adventure::v1