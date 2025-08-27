// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "SkipTurnAction.h"

namespace adventure::v5c {

std::string SkipTurnAction::Description() const { return "Skip one turn."; }

ActionTagSet SkipTurnAction::Tags() const { return {ActionTag::SkipTurn}; }

void SkipTurnAction::Perform(Player& instigator) const { }
bool SkipTurnAction::Equals(const Action& other) const
{
    return dynamic_cast<const SkipTurnAction*>(&other) != nullptr;
}

} // namespace adventure::v5c