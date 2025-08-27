// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "Action.h"
#include <iostream>
#include <vector>

namespace adventure::v5a {

const std::unordered_set<ActionKind>& Action::Tags() const
{
    static const std::unordered_set<ActionKind> tags {};
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

} // namespace adventure::v5a
