// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Pawn.h"

#include <utility>

namespace adventure::v4a {

Pawn::Pawn(std::string name, Location* location)
    : name(std::move(name))
    , location(location)
{
}

void Pawn::Move(const std::string& direction)
{
    location = &location->GetConnectedLocation(direction);
}

void Pawn::MoveIfPossible(const std::string& direction)
{
    try {
        Move(direction);
    } catch (const std::out_of_range&) {
        // Ignore the exception.
    }
}

} // adventure::v4a
