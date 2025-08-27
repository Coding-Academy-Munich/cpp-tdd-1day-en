// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "MoveAction.h"
#include "Location.h"
#include "Pawn.h"

#include <utility>

namespace adventure::v4c {

MoveAction::MoveAction(std::string direction)
    : direction(std::move(direction))
{
}

std::string MoveAction::Description() const
{
    return "Move the player " + direction + ".";
}

void MoveAction::Perform(Pawn& instigator)
{
    instigator.MoveToLocation(instigator.GetLocation().GetConnectedLocation(direction));
}
} // namespace adventure::v4c