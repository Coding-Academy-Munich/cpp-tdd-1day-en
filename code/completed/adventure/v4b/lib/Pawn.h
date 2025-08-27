// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ADVENTURE_V4B_LIB_PAWN_H
#define COMPLETED_ADVENTURE_V4B_LIB_PAWN_H

#include "Location.h"
#include <string>

namespace adventure::v4b {

enum class Action { Move, SkipTurn };

class Pawn {
public:
    Pawn(std::string name, Location* location);

    void Perform(Action action, const std::string& direction);
    void PerformIfPossible(Action action, const std::string& direction);

    [[nodiscard]] const std::string& GetName() const { return name; }
    [[nodiscard]] const Location& GetLocation() const { return *location; }

private:
    std::string name;
    const Location* location;
};

} // namespace adventure::v4b

#endif // COMPLETED_ADVENTURE_V4B_LIB_PAWN_H
