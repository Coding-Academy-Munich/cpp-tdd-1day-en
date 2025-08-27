// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V5B_LIB_PAWN_H
#define COMPLETED_ADVENTURE_V5B_LIB_PAWN_H

#include "actions/SkipTurnAction.h"
#include <string>

namespace adventure::v5b {

class Action;
class Location;

class Pawn {
public:
    Pawn(std::string name, const Location& location);

    [[nodiscard]] const std::string& GetName() const { return name; }
    [[nodiscard]] const Location& GetLocation() const { return *location; }

    void MoveToLocation(const Location& newLocation);

private:
    std::string name;
    const Location* location;
};

} // namespace adventure::v5b

#endif // COMPLETED_ADVENTURE_V5B_LIB_PAWN_H
