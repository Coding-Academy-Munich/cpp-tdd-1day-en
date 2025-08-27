// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Action.h"
#include <iostream>
#include <vector>

namespace adventure::v5b {

const std::unordered_set<ActionTag>& Action::Tags() const
{
    static const std::unordered_set<ActionTag> tags {};
    return tags;
}

std::ostream& operator<<(std::ostream& os, const Action& action)
{
    os << action.Description();
    return os;
}

std::ostream& operator<<(std::ostream& os, const ActionVec& action)
{
    os << "actions:";
    for (const auto& a : action) {
        os << "\n  " << a->Description();
    }
    return os;
}

bool operator==(const Action& lhs, const Action& rhs) { return lhs.Equals(rhs); }

bool operator!=(const Action& lhs, const Action& rhs) { return !(lhs == rhs); }

ActionVec ActionsWithTag(const ActionVec& actions, ActionTag tag)
{
    ActionVec result;
    for (const auto& action : actions) {
        const std::unordered_set<ActionTag>& tags = action->Tags();
        if (tags.find(tag) != tags.end()) {
            result.push_back(action);
        }
    }
    return result;
}

ActionVec ActionsWithoutTag(const ActionVec& actions, ActionTag tag)
{
    ActionVec result;
    for (const auto& action : actions) {
        const std::unordered_set<ActionTag>& tags = action->Tags();
        if (tags.find(tag) == tags.end()) {
            result.push_back(action);
        }
    }
    return result;
}

} // namespace adventure::v5b
