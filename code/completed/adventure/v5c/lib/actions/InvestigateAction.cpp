// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "InvestigateAction.h"
#include "ActionTag.h"

namespace adventure::v5c {
std::string InvestigateAction::Description() const
{
    return "Investigate the current location.";
}

ActionTagSet InvestigateAction::Tags() const
{
    return {ActionTag::Investigate, ActionTag::Aggressive};
}

void InvestigateAction::Perform(Player& instigator) const { }

bool InvestigateAction::Equals(const Action& other) const
{
    return dynamic_cast<const InvestigateAction*>(&other) != nullptr;
}
} // namespace adventure::v5c