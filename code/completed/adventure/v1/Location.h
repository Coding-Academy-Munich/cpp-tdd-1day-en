// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V1_LOCATION_H
#define COMPLETED_ADVENTURE_V1_LOCATION_H

#include "LocationData.h"
#include <ostream>
#include <string>

namespace adventure::v1 {

class Location {
public:
    Location(std::string name, std::string description);
    explicit Location(const data::LocationData& locationData);

    [[nodiscard]] const std::string& GetName() const;
    [[nodiscard]] const std::string& GetDescription() const;

private:
    std::string name;
    std::string description;
};

std::ostream& operator<<(std::ostream& os, const Location& location);
}

#endif // COMPLETED_ADVENTURE_V1_LOCATION_H
