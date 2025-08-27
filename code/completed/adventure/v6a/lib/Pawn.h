// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#ifndef COMPLETED_ADVENTURE_V6A_LIB_PAWN_H
#define COMPLETED_ADVENTURE_V6A_LIB_PAWN_H

#include "actions/SkipTurnAction.h"
#include <string>

namespace adventure::v6a {

class Action;
class Location;

class Pawn {
public:
    Pawn(std::string name, const Location& location);

    [[nodiscard]] const std::string& GetName() const { return name_; }
    [[nodiscard]] const Location& GetLocation() const { return *location_; }

    void MoveToLocation(const Location& newLocation);

private:
    std::string name_;
    const Location* location_;
};

} // namespace adventure::v6a

#endif // COMPLETED_ADVENTURE_V6A_LIB_PAWN_H
