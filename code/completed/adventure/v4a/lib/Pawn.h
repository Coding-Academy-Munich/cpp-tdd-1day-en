// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V4A_LIB_PAWN_H
#define COMPLETED_ADVENTURE_V4A_LIB_PAWN_H

#include "Location.h"
#include <string>

namespace adventure::v4a {

class Pawn {
public:
    Pawn(std::string name, Location* location);

    void Move(const std::string& direction);
    void MoveIfPossible(const std::string& direction);

    [[nodiscard]] const std::string& GetName() const { return name; }
    [[nodiscard]] const Location& GetLocation() const { return *location; }
    [[nodiscard]] Location& GetLocation() { return *location; }

private:
    std::string name;
    Location* location;
};

} // namespace adventure::v4a

#endif // COMPLETED_ADVENTURE_V4A_LIB_PAWN_H
