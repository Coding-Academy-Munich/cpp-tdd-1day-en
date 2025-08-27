// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Pawn.h"
#include "Action.h"

#include <stdexcept>
#include <utility>

namespace adventure::v6a {

Pawn::Pawn(std::string name, const Location& location)
    : name_(std::move(name)), location_(&location) { }

void Pawn::MoveToLocation(const Location& newLocation) {
    this->location_ = &newLocation;
}

} // namespace adventure::v6a
