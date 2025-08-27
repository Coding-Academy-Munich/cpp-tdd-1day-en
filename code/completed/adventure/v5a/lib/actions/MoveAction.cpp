// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "MoveAction.h"
#include "Location.h"
#include "Player.h"

#include <utility>

namespace adventure::v5a {

MoveAction::MoveAction(std::string direction)
    : direction(std::move(direction))
{
}

std::string MoveAction::Description() const
{
    return "Move the player " + direction + ".";
}

const std::unordered_set<ActionKind>& MoveAction::Tags() const
{
    static const std::unordered_set<ActionKind> tags {ActionKind::Move};
    return tags;
}

void MoveAction::Perform(Player& instigator) const
{
    MoveToLocation(instigator, GetLocation(instigator).GetConnectedLocation(direction));
}

} // namespace adventure::v5a