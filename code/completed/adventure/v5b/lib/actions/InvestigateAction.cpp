// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "InvestigateAction.h"

namespace adventure { namespace v5b {
    std::string InvestigateAction::Description() const
    {
        return "Investigate the current location.";
    }

    const std::unordered_set<ActionTag>& InvestigateAction::Tags() const
    {
        static const std::unordered_set<ActionTag> tags {
            ActionTag::Investigate, ActionTag::Aggressive};
        return tags;
    }

    void InvestigateAction::Perform(Player& instigator) const { }
    bool InvestigateAction::Equals(const Action& other) const
    {
        return dynamic_cast<const InvestigateAction*>(&other) != nullptr;
    }
}} // namespace adventure::v5b