// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include "action.h"

namespace adv
{
bool Action::equals(const Action& rhs) const
{
    return false;
}

bool operator==(const Action& lhs, const Action& rhs)
{
    return lhs.equals(rhs);
}

MoveAction::MoveAction(const std::string& direction) : direction_{direction}
{
}

bool MoveAction::equals(const Action& rhs) const
{
    const auto& other = dynamic_cast<const MoveAction&>(rhs);
    return direction_ == other.direction_;
}
} // namespace adv
