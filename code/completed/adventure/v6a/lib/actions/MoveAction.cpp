// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "MoveAction.h"
#include "ActionTag.h"
#include "Location.h"
#include "Player.h"

#include <utility>

namespace adventure::v6a {

MoveAction::MoveAction(std::string direction) : direction_(std::move(direction)) { }

std::string MoveAction::Description() const {
    return "Move the player " + direction_ + ".";
}

ActionTagSet MoveAction::Tags() const { return {ActionTag::Move}; }

void MoveAction::Perform(Player& instigator) const {
    MoveToLocation(
        instigator, GetLocation(instigator).GetConnectedLocation(direction_));
}

bool MoveAction::Equals(const Action& other) const {
    if (const auto& other_move_action {dynamic_cast<const MoveAction*>(&other)}) {
        return direction_ == other_move_action->direction_;
    }
    return false;
}

} // namespace adventure::v6a