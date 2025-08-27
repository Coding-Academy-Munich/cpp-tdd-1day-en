// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Action.h"
#include "ActionTag.h"
#include <iostream>
#include <vector>

namespace adventure::v5c {

ActionTagSet Action::Tags() const { return {}; }

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
        if (action->Tags().Contains(tag)) {
            result.push_back(action);
        }
    }
    return result;
}

ActionVec ActionsWithoutTag(const ActionVec& actions, ActionTag tag)
{
    ActionVec result;
    for (const auto& action : actions) {
        if (action->Tags().Contains(tag)) {
            result.push_back(action);
        }
    }
    return result;
}

} // namespace adventure::v5c
