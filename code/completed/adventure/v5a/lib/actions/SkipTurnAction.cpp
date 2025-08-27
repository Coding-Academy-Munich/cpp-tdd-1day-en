// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "SkipTurnAction.h"

namespace adventure::v5a {

std::string SkipTurnAction::Description() const { return "Skip one turn."; }

const std::unordered_set<ActionKind>& SkipTurnAction::Tags() const
{
    static const std::unordered_set<ActionKind> tags {ActionKind::SkipTurn};
    return tags;
}

void SkipTurnAction::Perform(Player& instigator) const { }

} // namespace adventure::v5a