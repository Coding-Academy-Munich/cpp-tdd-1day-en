// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "MoveAction.h"
#include "Location.h"
#include "Player.h"

#include <utility>

namespace adventure::v5b {

MoveAction::MoveAction(std::string direction)
    : direction(std::move(direction))
{
}

std::string MoveAction::Description() const
{
    return "Move the player " + direction + ".";
}

const std::unordered_set<ActionTag>& MoveAction::Tags() const
{
    static const std::unordered_set<ActionTag> tags {ActionTag::Move};
    return tags;
}

void MoveAction::Perform(Player& instigator) const
{
    MoveToLocation(instigator, GetLocation(instigator).GetConnectedLocation(direction));
}

bool MoveAction::Equals(const Action& other) const
{
    if (const auto& other_move_action {dynamic_cast<const MoveAction*>(&other)}) {
        return direction == other_move_action->direction;
    }
    return false;
}

} // namespace adventure::v5b