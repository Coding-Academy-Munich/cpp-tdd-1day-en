// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Pawn.h"

#include <utility>

namespace adventure::v4b {

Pawn::Pawn(std::string name, Location* location)
    : name(std::move(name))
    , location(location)
{
}

void Pawn::Perform(Action action, const std::string& direction)
{
    switch (action) {
    case Action::Move:
        location = &location->GetConnectedLocation(direction);
        break;
    case Action::SkipTurn:
        break;
    }
}

void Pawn::PerformIfPossible(Action action, const std::string& direction)
{
    try {
        Perform(action, direction);
    } catch (const std::out_of_range&) {
        // Ignore the exception.
    }
}

} // adventure::v4b
