// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "QuitAction.h"
#include <string>

namespace adventure::v5b {
std::string QuitAction::Description() const { return "Exit the game"; }

const std::unordered_set<ActionTag>& QuitAction::Tags() const
{
    static const std::unordered_set<ActionTag> tags {ActionTag::Quit};
    return tags;
}

void QuitAction::Perform(Player& instigator) const { throw QuitGameException(); }

bool QuitAction::Equals(const Action& other) const
{
    return dynamic_cast<const QuitAction*>(&other) != nullptr;
}

} // namespace adventure::v5b