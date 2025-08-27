// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

#include "SelectLastAction.h"

namespace adventure::v5c {

ActionPtr SelectLastAction::SelectAction(
    const Player& player, const ActionVec& actions) const
{
    return actions.back();
}

} // namespace adventure::v5c