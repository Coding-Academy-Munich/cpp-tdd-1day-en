// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Pawn.h"

#include <stdexcept>
#include <utility>

namespace adventure::v5a {

Pawn::Pawn(std::string name, const Location& location)
    : name(std::move(name))
    , location(&location)
{
}

void Pawn::MoveToLocation(const Location& newLocation)
{
    this->location = &newLocation;
}

} // namespace adventure::v5a
