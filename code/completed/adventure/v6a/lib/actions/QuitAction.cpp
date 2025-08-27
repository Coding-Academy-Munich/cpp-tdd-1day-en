// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "QuitAction.h"
#include "ActionTag.h"
#include <string>

namespace adventure::v6a {
std::string QuitAction::Description() const { return "Exit the game"; }

ActionTagSet QuitAction::Tags() const { return {ActionTag::Quit}; }

void QuitAction::Perform(Player& instigator) const { throw QuitGameException(); }

bool QuitAction::Equals(const Action& other) const
{
    return dynamic_cast<const QuitAction*>(&other) != nullptr;
}

} // namespace adventure::v6a