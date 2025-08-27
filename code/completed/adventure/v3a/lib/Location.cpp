// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Location.h"
#include <utility>

namespace adventure::v3a {
Location::Location(std::string name, std::string description)
    : name {std::move(name)}
    , description {std::move(description)}
{
}

Location::Location(const data::LocationData& locationData)
    : Location {locationData.name, locationData.description}
{
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
} // namespace adventure::v3a