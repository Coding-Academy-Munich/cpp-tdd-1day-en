// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V4C_LIB_PAWN_H
#define COMPLETED_ADVENTURE_V4C_LIB_PAWN_H

#include "actions/SkipTurnAction.h"
#include <string>

namespace adventure::v4c {

class Action;
class Location;

class Pawn {
public:
    Pawn(std::string name, const Location& location);

    void Perform(Action& action);
    void PerformIfPossible(Action& action);

    [[nodiscard]] const std::string& GetName() const { return name; }
    [[nodiscard]] const Location& GetLocation() const { return *location; }

    void MoveToLocation(const Location& newLocation);

private:
    std::string name;
    const Location* location;
};

} // namespace adventure::v4c

#endif // COMPLETED_ADVENTURE_V4C_LIB_PAWN_H
