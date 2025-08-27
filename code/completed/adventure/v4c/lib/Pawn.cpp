// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Pawn.h"
#include "Action.h"

#include <stdexcept>
#include <utility>

namespace adventure::v4c {

Pawn::Pawn(std::string name, const Location& location)
    : name(std::move(name))
    , location(&location)
{
}

void Pawn::Perform(Action& action) { action.Perform(*this); }

void Pawn::PerformIfPossible(Action& action)
{
    try {
        Perform(action);
    } catch (const std::out_of_range&) {
        // Ignore the exception.
    }
}

void Pawn::MoveToLocation(const Location& newLocation)
{
    this->location = &newLocation;
}

} // namespace adventure::v4c
