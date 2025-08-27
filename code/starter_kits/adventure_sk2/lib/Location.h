// Created by Dr. Matthias Hölzl on 30/09/2023.
// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef STARTER_KITS_ADVENTURE_SK2_LIB_LOCATION_H
#define STARTER_KITS_ADVENTURE_SK2_LIB_LOCATION_H

#include "LocationData.h"
#include <ostream>
#include <string>

namespace adventure_sk2 {

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

} // adventure_sk2

#endif // STARTER_KITS_ADVENTURE_SK2_LIB_LOCATION_H
