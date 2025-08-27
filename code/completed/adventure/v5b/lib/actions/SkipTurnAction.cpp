// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "SkipTurnAction.h"

namespace adventure::v5b {

std::string SkipTurnAction::Description() const { return "Skip one turn."; }

const std::unordered_set<ActionTag>& SkipTurnAction::Tags() const
{
    static const std::unordered_set<ActionTag> tags {ActionTag::SkipTurn};
    return tags;
}

void SkipTurnAction::Perform(Player& instigator) const { }
bool SkipTurnAction::Equals(const Action& other) const
{
    return dynamic_cast<const SkipTurnAction*>(&other) != nullptr;
}

} // namespace adventure::v5b