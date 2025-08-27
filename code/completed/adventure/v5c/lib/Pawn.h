// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#ifndef COMPLETED_ADVENTURE_V5C_LIB_PAWN_H
#define COMPLETED_ADVENTURE_V5C_LIB_PAWN_H

#include "actions/SkipTurnAction.h"
#include <string>

namespace adventure::v5c {

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

} // namespace adventure::v5c

#endif // COMPLETED_ADVENTURE_V5C_LIB_PAWN_H
